# Bug Report — BanSystem / BanChatCommands / DiscordBridge / SMLWebSocket

Generated after a complete read of all ~35 source files (~10 000 lines of production C++).
Files audited: BanDatabase, BanEnforcer, BanRestApi, BanAuditLog, BanSyncClient,
BanWebSocketPusher, BanDiscordNotifier, BanDiscordSubsystem (DiscordBridge),
DiscordBridgeSubsystem, BanChatCommands, MuteRegistry, PlayerWarningRegistry,
PlayerNoteRegistry, PlayerSessionRegistry, ScheduledBanRegistry, BanAppealRegistry,
SMLWebSocketClient, SMLWebSocketRunnable.

---

## 🔴 HIGH — Data integrity bugs

### BDB-1 · `RemoveBanByUid` / `RemoveBanById` split-brain on save failure
**File:** `BanSystem/Private/BanDatabase.cpp`  
**Symptom:** When `SaveToFile()` fails after the entry has already been erased from the
in-memory `Bans` map, the function returns `false`. Consequences:
- The ban is **gone from memory** (will reappear after next server restart when the file is re-loaded).
- `OnBanRemoved` is **never broadcast** → Discord notifications, BanSyncClient peer-sync, and
  BanDiscordSubsystem moderation-log entries are all silently skipped.
- The calling REST handler (`DELETE /bans/:uid`) receives `false` and returns HTTP 500, giving
  the operator a false impression that the ban still exists and nothing changed.
- No audit log entry is written for the unban.

**Root cause:** The point of no return (`Bans.Remove(...)`) occurs before the disk write. If
the disk write fails, the code issues an early `return false` inside the lock scope without
rolling back the in-memory removal.

**Fix:** Either (a) rollback the removal from `Bans` before returning `false`, or (b) treat a
successful memory removal + failed save as a partial success and still fire `OnBanRemoved`, but
return a separate error flag to the caller.

**Symmetric issue:** `AddBan` / `AddBanSkipIfPermanentExists` have the opposite problem: if
`SaveToFile()` fails the new entry is already present in the in-memory `Bans` map and
`ActiveBanCount` was incremented, but `OnBanAdded` is not broadcast and the caller receives
`false`. Subsequent `GET /bans` queries will return this "ghost ban" until the server restarts
and the file (which never recorded it) is re-loaded.

---

## 🟠 MEDIUM — Logic / notification correctness bugs

### REST-UNNOTIFY-1 · REST API counterpart-unban removes records silently (no Discord notification)
**File:** `BanSystem/Private/BanRestApi.cpp` — `RestApiRemoveCounterpartBans()`  
**Symptom:** When a ban is removed via the REST API (`DELETE /bans/:uid` or `DELETE /bans/ip/:ip`),
`RestApiRemoveCounterpartBans` removes the linked EOS ↔ IP counterpart bans by calling
`DB->RemoveBanByUid(LinkedUid)` for each one. It does **not** call
`FBanDiscordNotifier::NotifyBanRemoved` for those counterpart entries. The equivalent function
in BanChatCommands (`BanChat::RemoveCounterpartBans`) correctly calls `NotifyBanRemoved` for
each counterpart.

**Impact:** When an operator unbans a player via the REST API, only the primary ban fires a
Discord/webhook notification. Counterpart IP or EOS bans are removed silently. Moderation
dashboards and webhook logs will show an incomplete unban record.

**Fix:** After each successful `DB->RemoveBanByUid(LinkedUid)` call, add
`FBanDiscordNotifier::NotifyBanRemoved(LinkedUid, ...)`.

---

### BCC-CHATBAN-NONOTIFY · `DoBan` in BanChatCommands fires `NotifyBanCreated` before counterpart bans are created
**File:** `BanChatCommands/Private/Commands/BanChatCommands.cpp`, `DoBan()` ~line 618–641  
**Symptom:** After a ban is added, `AddCounterpartBans(...)` creates the linked IP or EOS
counterpart bans. Each counterpart ban fires its own `OnBanAdded` delegate, which causes
`BanDiscordSubsystem::BanAddedHandle` to mirror them into the moderation log. However, the
primary ban's **explicit** `FBanDiscordNotifier::NotifyBanCreated(Entry)` webhook call fires
before counterpart bans are created, so external webhook consumers (e.g. ban-log bots) receive
the primary ban notification without any guaranteed ordering relative to counterpart records.

**Severity:** Low in practice (counterpart bans arrive fractions of a millisecond later) but
creates an ordering dependency that could matter for automated integrations.

---

### MR-1 · `MuteRegistry` ignores `UBanSystemConfig::DatabasePath`
**File:** `BanChatCommands/Private/MuteRegistry.cpp` — `GetRegistryPath()`  
**Symptom:** Returns the hardcoded path
`FPaths::ProjectSavedDir() / "BanChatCommands" / "mutes.json"` regardless of the
`DatabasePath` key in `DefaultBanSystem.ini`. Every other BanSystem registry
(`BanDatabase`, `BanAuditLog`, `BanAppealRegistry`, etc.) respects `DatabasePath`.

**Impact:** An admin who relocates the ban database directory via `DatabasePath` will find that
`mutes.json` remains at the old default location. If a server restart occurs after the move,
mute records will silently appear to be empty (file not found = empty registry).

**Fix:** Change `GetRegistryPath()` to read `UBanSystemConfig::DatabasePath` the same way
other registries do, e.g.:
```cpp
const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
const FString Base = (Cfg && !Cfg->DatabasePath.IsEmpty())
    ? Cfg->DatabasePath : FPaths::ProjectSavedDir();
return FPaths::Combine(Base, TEXT("BanChatCommands"), TEXT("mutes.json"));
```

---

### PWR-1 · `AddWarning(const FWarningEntry&)` silently overwrites caller's `WarnDate`
**File:** `BanSystem/Private/PlayerWarningRegistry.cpp` — `AddWarning(const FWarningEntry&)`  
**Symptom:** The struct overload of `AddWarning` was added specifically to preserve a custom
`Points` value (the comment says so). However, it also unconditionally overwrites
`Entry.WarnDate = FDateTime::UtcNow()`, discarding any date the caller set. If a caller
pre-populates `WarnDate` (e.g. an import/sync path trying to preserve historical timestamps),
that date is silently replaced with the current time.

**Fix:** Only assign `FDateTime::UtcNow()` to `WarnDate` if the caller left it default
(`FDateTime(0)`), or document clearly that this overload always stamps the current time and
rename/deprecate accordingly.

---

## 🟡 LOW — Edge cases and cosmetic bugs

### DBS-WHITELIST-OPENROLE · Whitelist button approval grants implicit access to everyone when role is unconfigured
**File:** `DiscordBridge/Private/DiscordBridgeSubsystem.cpp` — whitelist button handler
(`wl_approve` path, `HandleDispatch` → button component handler)  
**Symptom:**
```cpp
bHasRole = WhitelistConfig.WhitelistCommandRoleId.IsEmpty();
```
When `WhitelistCommandRoleId` is empty (not configured), `bHasRole` is set to `true`, granting
any Discord user who can see and click the whitelist-approval button implicit approval authority.

**Impact:** In a server where `WhitelistCommandRoleId` is intentionally left blank (e.g. the
operator did not realise it controls approval gating), any Discord user — including untrusted
members — can approve whitelist applications by clicking the button. This is a security
misconfiguration pitfall.

**Recommendation:** Log a warning at startup when `WhitelistCommandRoleId` is empty and the
whitelist feature is enabled, making the "allow-all" behaviour explicit.

---

### BCC-PIE · Command cooldown statics persist across PIE sessions
**File:** `BanChatCommands/Private/Commands/BanChatCommands.cpp`  
**Symptom:** The anonymous-namespace helper functions `IsOnCooldown`, `IsBanRateLimited`, and
`GetOrMakeCommandCooldown` use function-local `static` variables
(`static TMap<FString, FDateTime> CommandCooldowns`,
`static TMap<FString, TArray<FDateTime>> AdminBanTimestamps`, etc.).

In a real dedicated server process, this is fine — there is exactly one game instance. In
**Play In Editor** (PIE) multi-session testing, all game instances in the same process share
these statics. A cooldown set in PIE session 1 will affect PIE session 2.

**Impact:** Affects development / QA testing only. No impact on shipped dedicated servers.

---

### NOTES-API · `GET /notes` REST endpoint returns count only, not content
**File:** `BanSystem/Private/BanRestApi.cpp` — `GET /notes` handler  
**Symptom:** The handler uses `FArrayProperty` reflection to read the `Notes` array from
`UPlayerNoteRegistry` (a subsystem that lives in the BanChatCommands module) to retrieve only
the count. It returns:
```json
{ "count": 42, "notes": [], "info": "Note count is accurate. Full note data is accessible via BanChatCommands module directly." }
```
The `notes` array is always empty. External REST clients querying `/notes` cannot retrieve
note content.

**Impact:** Any API integration that expects note data via REST silently receives an empty
array. The comment in the response explains the limitation but does not prevent silent failures
in automated consumers.

**Recommendation:** Either implement proper serialization of note entries via the reflection
path (same as the count read), or clearly document this as a known limitation in API docs.

---

### SWR-1 · Non-atomic `bConnected` check + enqueue in SMLWebSocket (documented)
**File:** `SMLWebSocket/Private/SMLWebSocketRunnable.cpp` — `EnqueueText` / `EnqueueBinary`  
**Symptom:** `EnqueueText` checks `bConnected` (std::atomic) and then enqueues the message.
A disconnect between the check and the enqueue causes the message to be silently dropped when
`CleanupConnection` drains the queue.

**Impact:** Rare transient message drop during disconnect. The code includes a comment
documenting this as a known limitation:
> "NOTE: The bConnected check and the Enqueue call below are not atomic."

**Recommendation:** Document this explicitly in the API docs (e.g. `SendText` header comment).
Callers that cannot afford silent drops should subscribe to `OnConnectionError`/`OnClosed` and
retry.

---

### BDB-LINKBANS · `LinkBans` leaves in-memory cross-links on save failure
**File:** `BanSystem/Private/BanDatabase.cpp` — `LinkBans()`  
**Symptom:** Same pattern as BDB-1: `LinkBans` updates both ban entries' `LinkedUids` arrays
in-memory, then calls `SaveToFile()`. If the save fails, the in-memory cross-links exist but
are not persisted. After a server restart, the cross-links are gone (file state wins).

**Impact:** Lower severity than BDB-1 because linked bans still exist individually and
enforcement is not affected; only the cross-link relationship is lost, which affects unban
cascade behaviour.

---

## 🔵 DESIGN NOTES (not bugs, but worth reviewing)

### DESIGN-1 · `BanEnforcer::AlreadyNotifiedExpiredBanUids` is correctly pruned
The `AlreadyNotifiedExpiredBanUids` TSet was initially a concern for unbounded growth, but
`BanEnforcer::Initialize` subscribes to `UBanDatabase::OnBanRemoved` (line ~282) and removes
each UID from the set when its ban is deleted. **No memory leak.** ✅

### DESIGN-2 · `CachedConnectionPuids/IPs/Versions` maps are correctly pruned
`NotifyPlayerLogout` hook (BanEnforcer.cpp ~line 193) evicts the specific disconnecting
player's entry AND prunes all GC-stale TWeakObjectPtr keys in one pass. **No memory leak.** ✅

### DESIGN-3 · CSS DS FUniqueNetIdRepl not dereferenced
The code correctly avoids `operator->` on `FUniqueNetIdRepl` on CSS DS where the inner
TSharedPtr holds a raw EOS handle. The fallback PUID path via `CachedConnectionPuids`
(PreLogin hook) is sound. ✅

### DESIGN-4 · BanSyncClient "consume-once" pattern
The `PeerAppliedBanUids` TSet correctly suppresses re-broadcasting of peer-sourced ban events
without creating an echo loop. Timing is safe because both the `Add()` and `Remove()` paths
run on the game thread. ✅

### DESIGN-5 · Discord Gateway heartbeat reconnect path
When `bPendingHeartbeatAck` is `false` at the point the one-shot jitter heartbeat fires
(meaning the first heartbeat could not be sent), the repeating heartbeat ticker is not
installed. `SendHeartbeat()` will have already called `Connect()` to force a reconnect.
`HandleHello` will reinstall the ticker on the new session. **No heartbeat dead-lock.** ✅

### DESIGN-6 · `POST /appeals` rate-limit static state
The static `AppealSubmissions` array and `AppealRateMutex` inside the `POST /appeals` handler
(BanRestApi.cpp ~line 2042) share state across all invocations, which is correct for a global
rate limit. However, these statics accumulate entries for the lifetime of the process. The
`RemoveAll` prune runs on every request, so growth is bounded by the rate-limit window (max 5
entries per 60 s). **No memory leak.** ✅

---

## Summary table

| ID | Severity | Component | Short description |
|----|----------|-----------|-------------------|
| BDB-1 | 🔴 HIGH | BanDatabase | Split-brain removal on save failure |
| BDB-ADD-1 | 🔴 HIGH | BanDatabase | Ghost addition on save failure (symmetric) |
| REST-UNNOTIFY-1 | 🟠 MEDIUM | BanRestApi | Counterpart unban skips Discord notifications |
| BCC-CHATBAN-NONOTIFY | 🟠 MEDIUM | BanChatCommands | Ban notification fires before counterpart bans exist |
| MR-1 | 🟠 MEDIUM | MuteRegistry | `GetRegistryPath` ignores `DatabasePath` config |
| PWR-1 | 🟠 MEDIUM | PlayerWarningRegistry | `AddWarning(struct)` overwrites caller's `WarnDate` |
| DBS-WHITELIST-OPENROLE | 🟡 LOW | DiscordBridgeSubsystem | Empty `WhitelistCommandRoleId` grants approval to everyone |
| BCC-PIE | 🟡 LOW | BanChatCommands | Cooldown statics bleed across PIE sessions |
| NOTES-API | 🟡 LOW | BanRestApi | `GET /notes` always returns empty `notes` array |
| SWR-1 | 🟡 LOW | SMLWebSocketRunnable | Non-atomic disconnect check (documented) |
| BDB-LINKBANS | 🟡 LOW | BanDatabase | `LinkBans` cross-links not rolled back on save failure |

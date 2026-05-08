# Bug Report — BanSystem / BanChatCommands / DiscordBridge / SMLWebSocket

Generated after a complete read of all ~35 source files (~10 000 lines of production C++).
Files audited: BanDatabase, BanEnforcer, BanRestApi, BanAuditLog, BanSyncClient,
BanWebSocketPusher, BanDiscordNotifier, BanDiscordSubsystem (DiscordBridge),
DiscordBridgeSubsystem, BanChatCommands, MuteRegistry, PlayerWarningRegistry,
PlayerNoteRegistry, PlayerSessionRegistry, ScheduledBanRegistry, BanAppealRegistry,
SMLWebSocketClient, SMLWebSocketRunnable.

---

## ✅ FIXED — Round 59

### BDB-1 · `RemoveBanByUid` / `RemoveBanById` split-brain on save failure ✅ FIXED
**Fix:** Added rollback `Bans.Add(OutEntry)` immediately after the failed `SaveToFile()` call in both
`RemoveBanByUid` and `RemoveBanById`. Memory and disk now stay in sync; `OnBanRemoved` is only
broadcast after a confirmed successful disk write.

### BDB-ADD-1 · Ghost addition on `AddBan` save failure (symmetric) ✅ FIXED
**Fix:** Added rollback `Bans.RemoveAll(...)` for the newly-added entry in all three `AddBan` /
`AddBanSkipIfPermanentExists` overloads when `SaveToFile()` fails. `OnBanAdded` remains gated on
`bSaved`, so no spurious notifications fire.

### BDB-LINKBANS · `LinkBans` cross-links not rolled back on save failure ✅ FIXED
**Fix:** Added rollback loop that calls `LinkedUids.RemoveSingle(...)` on both entries when
`SaveToFile()` fails, ensuring the in-memory cross-link state matches the on-disk state.

### REST-UNNOTIFY-1 · REST API counterpart-unban removes records silently ✅ FIXED
**Fix:** `RestApiRemoveCounterpartBans` now calls `RemoveBanByUid(Uid, OutEntry)` (capturing the
removed entry) and immediately follows with `FBanDiscordNotifier::NotifyBanRemoved(...)` for every
successfully removed counterpart ban, matching `BanChat::RemoveCounterpartBans`.

### MR-1 · `MuteRegistry` ignores `UBanSystemConfig::DatabasePath` ✅ FIXED
**Fix:** `MuteRegistry::GetRegistryPath()` now reads `UBanSystemConfig::Get()->DatabasePath`
(same pattern as `BanAuditLog`, `PlayerWarningRegistry`, etc.). Added `#include "BanSystemConfig.h"`.

### MR-2 · `PlayerNoteRegistry` ignores `UBanSystemConfig::DatabasePath` ✅ FIXED
**Fix:** Same fix applied to `PlayerNoteRegistry::GetRegistryPath()`. Both BanChatCommands
registries now respect the admin-configured `DatabasePath`.

### PWR-1 · `AddWarning(FWarningEntry)` silently overwrites caller's `WarnDate` ✅ FIXED
**Fix:** The unconditional `Entry.WarnDate = FDateTime::UtcNow()` is now guarded:
`if (Entry.WarnDate == FDateTime(0)) Entry.WarnDate = FDateTime::UtcNow();`
Callers that pre-populate `WarnDate` (e.g. import/sync paths) now have their timestamp preserved.

### DBS-WHITELIST-OPENROLE · Empty `WhitelistCommandRoleId` grants approval to everyone ✅ FIXED
**Fix:** Changed `bool bHasRole = WhitelistConfig.WhitelistCommandRoleId.IsEmpty();` to
`bool bHasRole = false;`. When no role is configured, only the guild owner (already handled by
the explicit `GuildOwnerId` check below) can approve whitelist applications.

### NOTES-API · `GET /notes` always returned empty `notes` array ✅ FIXED
**Fix:** The handler now uses `FScriptArrayHelper` + `FStructProperty` iteration to read all
`FPlayerNoteEntry` fields (`id`, `uid`, `playerName`, `note`, `addedBy`, `noteDate`) via UE
property reflection and builds a proper JSON array — without a hard module dependency on
BanChatCommands.

---

## ✅ FIXED — Round 60

### BUG-4 · `PruneExpiredBans` no rollback + spurious notifications on save failure ✅ FIXED
**Severity:** High  
**Fix:** Added `Bans.Append(Expired)` rollback and `Expired.Reset()` inside the lock block when
`SaveToFile()` fails. This keeps in-memory state consistent with the on-disk file (matching the
pattern used by `AddBan`, `RemoveBanByUid`, and `LinkBans`). Clearing `Expired` before exiting
the lock also prevents the outer broadcast block from firing spurious `OnBanRemoved` /
`NotifyBanExpired` events for entries whose removal was never persisted.

### BUG-1 · `POST /bans` temp-ban path uses wrong overload + racy second `GetBanByUid` ✅ FIXED
**Severity:** Medium  
**Fix:** Replaced the 2-arg `AddBanSkipIfPermanentExists(Entry, bSkippedPerm)` call (which doesn't
return the saved entry) and the subsequent `GetBanByUid` second-lookup (TOCTOU window) with the
3-arg overload `AddBanSkipIfPermanentExists(Entry, &Saved, &bSkippedPerm)`. The response now
carries the correct database-assigned `id` in all cases without an intermediate lookup.

### BUG-2 · `PATCH /bans/:uid` silently ignores negative `durationMinutes` ✅ FIXED
**Severity:** Medium  
**Fix:** Captured the boolean return value of `TryGetNumberField` into `bHasDuration`. Added a
pre-check that returns `400` with a clear error message when `bHasDuration && DurationMinutesDbl < 0.0`.
Callers now get an explicit error instead of a silent no-op `200 OK`.

### BUG-9 · `BanSyncClient` silently re-bans player after concurrent unban ✅ FIXED
**Severity:** Low  
**Fix:** Changed `DB->RemoveBanByUid(Uid, /*bSilent=*/true); bWasUpdate = true;` to
`bWasUpdate = DB->RemoveBanByUid(Uid, /*bSilent=*/true);`. If a concurrent admin unban already
removed the entry before peer-sync reached the `RemoveBanByUid` call, the return value is `false`,
`bWasUpdate` stays `false`, and `NotifyBanCreated` fires when the entry is re-added — creating an
audit trail instead of a silent re-ban.

---

## ✅ FIXED — Round 61

### BUG-61-1 · peer ban edits could silently unban on update failure ✅ FIXED
**Severity:** High  
**Fix:** Replaced the remove-then-readd peer-edit path with `DB->UpdateBan(...)` so updates happen
in place. If the row disappears concurrently, sync falls back to the add path; if persistence fails
and the old row still exists, the handler now aborts instead of overwriting it with a misleading
`OnBanAdded` flow.

### BUG-61-2 · due scheduled bans could re-fire after a post-apply save failure ✅ FIXED
**Severity:** High  
**Fix:** `ApplyScheduledBan` now detects when the scheduled ban was already durably applied earlier
by matching the active ban’s UID/reason/admin/category/permanence and remaining lifetime. Retries
after a failed `Pending` save now just clear the stale scheduled entry instead of extending the ban,
re-kicking the player, or re-firing Discord/audit side effects.

### BUG-61-3 · `POST /scheduled` returned `201` even when scheduling failed ✅ FIXED
**Severity:** Medium  
**Fix:** The REST handler now validates `NewEntry.Id > 0` after `AddScheduled(...)`. Failed writes
return `500 Failed to create scheduled ban` and skip the success audit log.

### BUG-61-4 · whitelist audit entries were only in-memory until the next unrelated save ✅ FIXED
**Severity:** Medium  
**Fix:** `SetEnabled`, `AddPlayer`, and `RemovePlayer` now append the audit entry before the same
`Save_Locked()` that persists the whitelist mutation, and roll back both the whitelist state and
`AuditLog` snapshot if the save fails.

### BUG-61-5 · reconnect flush dropped queued WebSocket messages on enqueue failure ✅ FIXED
**Severity:** Medium  
**Fix:** `USMLWebSocketClient::Internal_OnConnected` now keeps any text/binary payloads whose
`EnqueueText` / `EnqueueBinary` call fails during reconnect flush, instead of unconditionally
emptying both pending queues.

### BUG-61-6 · persisted `nextId = 0` exhaustion sentinel revived as `1` on reload ✅ FIXED
**Severity:** Low  
**Fix:** The loaders for `BanDatabase`, `BanAuditLog`, `BanAppealRegistry`, `PlayerWarningRegistry`,
`ScheduledBanRegistry`, and `PlayerNoteRegistry` now preserve stored `0` as the exhausted sentinel
instead of clamping it back to `1`, preventing post-restart ID reuse after counter exhaustion.

---

## ✅ FIXED — Round 62 (Deep Pass 3)

### DP3-1 · `AddBan` / `AddBanSkipIfPermanentExists` split-brain on ID exhaustion ✅ FIXED
**Severity:** Medium  
**Fix:** All three upsert overloads removed `OldEntry` from `Bans` before checking `NextId == 0`. The
`return false` early exit now restores `OldEntry` with `if (bHadOldEntry) Bans.Add(OldEntry)` before
returning, keeping the in-memory array consistent with the on-disk file when the ID counter is exhausted.

### DP3-2 · `ScheduledBanRegistry::Tick` discards `RetryCount` increments on `SaveToFile` failure ✅ FIXED
**Severity:** Medium  
**Fix:** The `Pending = PrevPending` rollback after a failed `SaveToFile()` previously threw away all
`RetryCount` increments that had been applied during the tick, preventing the 5-attempt drop-cap from
ever being reached under sustained disk failure. The rollback now re-applies the incremented
`RetryCount` values from `FailedEntries` back into `PrevPending` before restoring, so the cap
advances correctly even when saves fail.

### DP3-3 · `HandleWarnCommand` warn-escalation tier selection picks wrong tier ✅ FIXED
**Severity:** Medium  
**Fix:** `HandleWarnCommand` used the old `BestThreshold` algorithm that collapses both `PointThreshold`
(e.g. 50 points) and `WarnCount` (e.g. 5 warnings) onto the same `int32` and compares raw integers.
When mixed-unit tiers are configured this picks the tier with the largest number, not the most-severe
ban. Replaced with the `DurationMinutes`-severity comparison already used in `BanChatCommands.cpp`
and `TicketSubsystem.cpp`: permanent tiers (`DurationMinutes == 0`) beat all finite durations; among
finite durations, the longer ban wins.

### DP3-4 · `ExecutePanelWarn` warn-escalation tier selection picks wrong tier ✅ FIXED
**Severity:** Medium  
**Fix:** Identical stale `BestThreshold` algorithm in the admin-panel warn path. Applied the same
`DurationMinutes`-severity replacement described in DP3-3.

---

## 🟡 NOT FIXED — Low / dev-only

### BCC-PIE · Command cooldown statics persist across PIE sessions
**Severity:** Low — affects development/QA only; no impact on shipped dedicated servers.
**Reason not fixed:** Static maps are intentional for per-process rate-limiting; fixing this
would complicate the production path for a dev-only scenario.

### SWR-1 · Non-atomic `bConnected` check + enqueue in SMLWebSocket (documented)
**Severity:** Low / rare transient drop; already documented in code.
**Reason not fixed:** The code comment already documents this as a known limitation; fixing it
would require a mutex-based approach that adds overhead to the hot path.

### BCC-CHATBAN-NONOTIFY · Ban notification fires before counterpart bans exist
**Severity:** Low in practice (sub-millisecond ordering difference).
**Reason not fixed:** Reordering the notification after `AddCounterpartBans` would require
refactoring the notification contract; the practical impact on automated integrations is minimal.

---

## Summary table

| ID | Severity | Component | Fixed |
|----|----------|-----------|-------|
| BDB-1 | 🔴 HIGH | BanDatabase | ✅ Round 59 |
| BDB-ADD-1 | 🔴 HIGH | BanDatabase | ✅ Round 59 |
| BDB-LINKBANS | 🟡 LOW | BanDatabase | ✅ Round 59 |
| REST-UNNOTIFY-1 | 🟠 MEDIUM | BanRestApi | ✅ Round 59 |
| MR-1 | 🟠 MEDIUM | MuteRegistry | ✅ Round 59 |
| MR-2 | 🟠 MEDIUM | PlayerNoteRegistry | ✅ Round 59 |
| PWR-1 | 🟠 MEDIUM | PlayerWarningRegistry | ✅ Round 59 |
| DBS-WHITELIST-OPENROLE | 🟡 LOW | DiscordBridgeSubsystem | ✅ Round 59 |
| NOTES-API | 🟡 LOW | BanRestApi | ✅ Round 59 |
| BCC-PIE | 🟡 LOW | BanChatCommands | ❌ Dev-only, not fixed |
| SWR-1 | 🟡 LOW | SMLWebSocketRunnable | ❌ Documented known limitation |
| BCC-CHATBAN-NONOTIFY | 🟠 MEDIUM | BanChatCommands | ❌ Ordering, minimal impact |
| BUG-4 | 🔴 HIGH | BanDatabase | ✅ Round 60 |
| BUG-1 | 🟠 MEDIUM | BanRestApi | ✅ Round 60 |
| BUG-2 | 🟠 MEDIUM | BanRestApi | ✅ Round 60 |
| BUG-9 | 🟡 LOW | BanSyncClient | ✅ Round 60 |
| DP3-1 | 🟠 MEDIUM | BanDatabase | ✅ Round 62 |
| DP3-2 | 🟠 MEDIUM | ScheduledBanRegistry | ✅ Round 62 |
| DP3-3 | 🟠 MEDIUM | BanDiscordSubsystem | ✅ Round 62 |
| DP3-4 | 🟠 MEDIUM | BanDiscordSubsystem | ✅ Round 62 |

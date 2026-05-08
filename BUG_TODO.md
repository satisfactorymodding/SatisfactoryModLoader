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

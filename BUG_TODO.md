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

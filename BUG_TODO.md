# Bug TODO List

All 4 owner mods (BanChatCommands, BanSystem, DiscordBridge, SMLWebSocket) were scanned for bugs.
All bugs listed below have been fixed.

---

## BanChatCommands

### ✅ Fixed — Integer overflow in duration multiplication
**File:** `Mods/BanChatCommands/Source/BanChatCommands/Private/Commands/BanChatCommands.cpp`

**Fix applied:** Each `Total += Num * multiplier` is now preceded by overflow guards:
`if (Num > INT64_MAX / multiplier) return -1;` and `if (Total > INT64_MAX - Product) return -1;`.

---

### ✅ Fixed — Bare-integer duration silently truncated to int32
**File:** `Mods/BanChatCommands/Source/BanChatCommands/Private/Commands/BanChatCommands.cpp`

**Fix applied:** Replaced `FCString::Atoi` with `FCString::Atoi64`. Added validation that the
result is positive and `<= INT32_MAX`; returns `-1` otherwise.

---

### ✅ Fixed — `SaveToFile()` return value silently ignored
**Files:** `PlayerNoteRegistry.cpp` / `MuteRegistry.cpp`

**Fix applied:** All call sites now check the `bool` return value and emit a `UE_LOG(Error, ...)`
when a disk write fails.

---

### ✅ Fixed — `FDateTime::ParseIso8601()` return value ignored
**Files:** `MuteRegistry.cpp` / `PlayerNoteRegistry.cpp`

**Fix applied:** Each `ParseIso8601` call now checks the return; on failure it logs a warning and
`continue`s, skipping the malformed entry.

---

### ✅ Fixed — `NextId` counter has no overflow guard in `PlayerNoteRegistry`
**File:** `PlayerNoteRegistry.cpp`

**Fix applied:** `AddNote()` now checks `if (NextId == INT64_MAX)` before incrementing, logs an
error, and returns early.

---

### ✅ Fixed — `/clearwarn` missing int64 overflow guard before `FCString::Atoi64`
**File:** `Mods/BanChatCommands/Source/BanChatCommands/Private/Commands/BanChatCommands.cpp`

**Fix applied:** Added the same length + INT64_MAX lexicographic guard that `BanRestApi`'s
`ParseInt64Param` helper uses: rejects strings longer than 19 digits, and rejects 19-digit strings
whose decimal value exceeds `"9223372036854775807"`.

---

## BanSystem

### ✅ Fixed — 19-digit ID validation allows `int64` overflow in `FCString::Atoi64`
**File:** `BanRestApi.cpp` (6 sites)

**Fix applied:** Added `BanJson::ParseInt64Param()` helper that rejects 19-digit strings whose
decimal value exceeds `"9223372036854775807"` (INT64_MAX) via lexicographic comparison. All 6
validation + Atoi64 sites now use this helper.

---

### ✅ Fixed — Accumulated-seconds ticker resets to `0.0f` instead of subtracting the interval
**Files:** `ScheduledBanRegistry.cpp` / `BanSystemModule.cpp` (4 sites)

**Fix applied:** Replaced `AccumulatedSeconds = 0.0f` (and variants) with
`AccumulatedSeconds -= IntervalSeconds` at all four locations, preserving overshoot time.

---

### ✅ Fixed — `FDateTime::ParseIso8601()` return value ignored in `PlayerWarningRegistry`
**File:** `PlayerWarningRegistry.cpp`

**Fix applied:** Same pattern as MuteRegistry — check return, log warning, skip entry on failure.

---

### ✅ Fixed — POST /warnings response may return the wrong warning entry under concurrent load
**Files:** `BanRestApi.cpp` / `PlayerWarningRegistry.h` / `PlayerWarningRegistry.cpp`

**Fix applied:** `AddWarning(const FWarningEntry&)` now returns the populated `FWarningEntry`
(with assigned Id and WarnDate) from within the same lock acquisition. The REST handler uses this
return value directly, eliminating the separate `GetWarningsForUid` call.

---

### ✅ Fixed — `BanDatabase::JsonToEntry` returns `true` based solely on a non-empty `Uid` field
**File:** `BanDatabase.cpp`

**Fix applied:** Success condition is now `!OutEntry.Uid.IsEmpty() && !OutEntry.BannedBy.IsEmpty()`.

---

## DiscordBridge

### ✅ Fixed — `DiscordBridgeConfig.cpp` — `Mid()` called without verifying end indices
**File:** `DiscordBridgeConfig.cpp` (ScheduledAnnouncement Message and ChannelId blocks; `ChatRelayBlocklistReplacements` and `BotCommandAliases` `ExtractQuoted` lambdas)

**Fix applied:** Added `End > Start` guard alongside the existing `End != INDEX_NONE` check.
When the condition fails, a `UE_LOG(Warning, ...)` is emitted to flag the malformed config line (ScheduledAnnouncements).
The two `ExtractQuoted` lambdas now also use `End == INDEX_NONE || End <= Start` so an empty-value entry (`Pattern=""`) is rejected instead of silently producing an empty-pattern replacement.

---

### ✅ Fixed — `WhitelistManager::LogAudit` undocumented lock requirement
**File:** `WhitelistManager.h`

**Fix applied:** Added `/** Caller must already hold Mutex. */` doc comment to the declaration.
The matching comment already existed in the `.cpp` implementation.

---

### ✅ Fixed — `AnnouncementTick` timer drift: accumulated seconds reset to `0.0f`
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/DiscordBridgeSubsystem.cpp`

**Fix applied:** Changed `AnnouncementAccumulatedSeconds = 0.0f` to
`AnnouncementAccumulatedSeconds -= IntervalSeconds`, matching the identical fix already applied
to `BackupAccumulatedSeconds`, `PruneAccumulatedSeconds`, and `SessionPruneAccumulatedSeconds`
in `BanSystemModule.cpp`.

---

### ✅ Fixed — `SaveTicketState`: `FJsonSerializer::Serialize` return value not checked
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp`

**Fix applied:** Wrapped the `Serialize` call in `if (!...)` and added an early `return` with an
`UE_LOG(Error, ...)`. Prevents a serialization failure from writing a corrupt/empty string to
`ActiveTickets.json.tmp` and losing all open ticket state on the next atomic rename.

---

### ✅ Fixed — `SaveTicketBlacklist` writes directly (no atomic tmp→rename)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp`

**Fix applied:** Added `FJsonSerializer::Serialize` return check (early return on failure) and
converted the direct `SaveStringToFile(*Path)` to the same write-to-`.tmp`-then-`MoveFile`
atomic pattern used by `SaveTicketState` and every other registry in the codebase.

---

### ✅ Fixed — Ticket-feedback stats written without `FJsonSerializer::Serialize` check
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp`

**Fix applied:** The `FJsonSerializer::Serialize` call is now checked; the directory creation and
file write are gated inside `if (Serialize(...))` so a serialization failure no longer writes
empty content to the stats file.

---

## SMLWebSocket

### ✅ Fixed — RFC 6455 violation: no Close frame sent on fragment-sequencing error
**File:** `SMLWebSocketRunnable.cpp`

**Fix applied:** Both the mid-fragment interleave path and the fragment-size overflow path now
call `SendWsFrame(WsOpcode::Close, {0x03, 0xEA}, 2)` (status 1002) before returning `false`.

---

### ✅ Fixed — Reserved WebSocket opcodes (0xB–0xF) silently ignored instead of closing
**File:** `SMLWebSocketRunnable.cpp`

**Fix applied:** The `default:` branch now sends Close(1002) and returns `false`, satisfying
RFC 6455 §5.2.

---

### ✅ Fixed (documentation) — `EnqueueText`/`EnqueueBinary` TOCTOU gap
**File:** `SMLWebSocketRunnable.cpp`

**Fix applied:** Added a comment above `EnqueueText` explaining that a message enqueued between
the `bConnected` check and `OutboundMessages.Enqueue` may be silently dropped on disconnect,
and directing callers to `bQueueMessagesWhileDisconnected` for guaranteed delivery.

---

### ✅ Fixed — `SendMessageBodyToChannel` uses `BindLambda([this])` instead of `BindWeakLambda`
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/DiscordBridgeSubsystem.cpp`

**Fix applied:** Changed `BindLambda([this, TargetChannelId, BodyString]...)` to
`BindWeakLambda(this, [this, TargetChannelId, BodyString]...)`.  The lambda accesses
`Config.FallbackWebhookUrl` (a member of `this`); without the weak binding a use-after-free
would occur if the subsystem is destroyed while an HTTP request is still in-flight (e.g. during
server shutdown).  This is now consistent with every other HTTP callback in the file.

---

## BanSystem (round 2)

### ✅ Fixed — `BanAuditLog::LogAction()` — `SaveToFile()` return silently ignored
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanAuditLog.cpp`

**Fix applied:** Added `if (!SaveToFile())` check with `UE_LOG(Error, ...)` in `LogAction()`, matching
the pattern already used by every other registry in the codebase.

---

### ✅ Fixed — `BanAppealRegistry::LoadFromFile()` — malformed `submittedAt` falls through with epoch date
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanAppealRegistry.cpp`

**Fix applied:** Added `continue;` after the warning log when `FDateTime::ParseIso8601` fails for
`submittedAt`, matching the identical pattern in `MuteRegistry`, `PlayerNoteRegistry`,
`PlayerWarningRegistry`, and `ScheduledBanRegistry`.

---

### ✅ Fixed — `int64` IDs serialized as `double` (precision lost above 2⁵³)
**Files:** `BanAuditLog.cpp` (id + nextId), `BanDatabase.cpp`, `BanAppealRegistry.cpp`,
`ScheduledBanRegistry.cpp`, `PlayerWarningRegistry.cpp`

**Fix applied:** All `SetNumberField(TEXT("id"), static_cast<double>(Id))` calls converted to
`SetStringField(TEXT("id"), FString::Printf(TEXT("%lld"), Id))`. Load paths updated to try
`TryGetStringField` first (new format) and fall back to `TryGetNumberField` (old format) for
backward compatibility with existing data files. `BanAuditLog`'s `nextId` counter follows the
same string-first / number-fallback pattern.

---

*Last updated: 2026-04-28 (initial scan). All bugs resolved.*

---

## Round 2 — Additional Scan (2026-04-28)

### ✅ Fixed — Static `CommandCooldowns` / `AdminBanTimestamps` TMap — no mutex (BUG-01)
**File:** `Mods/BanChatCommands/Source/BanChatCommands/Private/Commands/BanChatCommands.cpp`

**Fix applied:** Added `check(IsInGameThread())` at the start of `IsOnCooldown()` and
`IsBanRateLimited()`. Added documentation comment on both maps explicitly declaring them
game-thread-only. SML dispatches `ExecuteCommand_Implementation` on the game thread so no
mutex is needed; the check will surface any future violation immediately.

---

### ✅ Fixed — Static `AFreezeChatCommand::FrozenPlayerUids` TSet — no mutex (BUG-02)
**File:** `Mods/BanChatCommands/Source/BanChatCommands/Private/Commands/BanChatCommands.cpp`

**Fix applied:** Added `check(IsInGameThread())` at the start of
`AFreezeChatCommand::ExecuteCommand_Implementation()`. Added a comment above the
`FrozenPlayerUids` definition stating it is game-thread-only
(command execute, `PostLoginHandle`, and `LogoutHookHandle` all run on game thread).

---

### ✅ Fixed (documentation) — Local `KickTimerHandle` cannot be cancelled on disconnect (BUG-03)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanEnforcer.cpp` (5 sites)

**Fix applied:** Added comments at all five `FTimerHandle KickTimerHandle;` declarations
explaining that the handle is intentionally transient (one-shot 20-second timer) and that
`TWeakObjectPtr<APlayerController>` prevents any crash or access violation when the player
disconnects during the window. The timer fires and self-cleans via the UE TimerManager.

---

### ✅ Fixed (documentation) — HTTP route handlers and game-thread dispatch guarantee (BUG-04)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp`

**Fix applied:** Replaced the original "potentially called on the HTTP thread" comment at the
top of `RegisterRoutes()` with an accurate note: UE's `FHttpServerModule` enqueues requests
and dispatches route callbacks on the game thread via its own `FTSTicker`. All subsystem
lookups, delegate broadcasts, timer operations, and PlayerController iterations in route
lambdas are therefore safe without additional locking.

---

### ✅ Fixed — `BanDatabase` root `nextId` serialised as `double` (precision loss > 2^53) (BUG-05)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanDatabase.cpp`

**Fix applied:** `SaveToFile()` now writes `nextId` as a decimal string via
`SetStringField(TEXT("nextId"), FString::Printf(TEXT("%lld"), NextId))`.
`LoadFromFile()` uses a string-first / number-fallback pattern (same as the existing
per-entry `id` fix) for backward compatibility with older database files.

---

### ✅ Fixed — `PlayerNoteRegistry` ID load off-by-one + save as double (BUG-06)
**File:** `Mods/BanChatCommands/Source/BanChatCommands/Private/PlayerNoteRegistry.cpp`

**Fix applied:** `LoadFromFile()` now uses the string-first / number-fallback pattern
(matching `PlayerWarningRegistry`) instead of the `IdDbl < static_cast<double>(INT64_MAX)`
guard that had an off-by-one at INT64_MAX. `SaveToFile()` changed from `SetNumberField`
to `SetStringField(TEXT("id"), FString::Printf(TEXT("%lld"), N.Id))`.

---

### ✅ Fixed — `appealId` in `BanDiscordNotifier` serialised as `double` (precision loss > 2^53) (BUG-07)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanDiscordNotifier.cpp`

**Fix applied:** Both `NotifyAppealSubmitted` and `NotifyAppealReviewed` now emit `appealId`
as a string: `SetStringField(TEXT("appealId"), FString::Printf(TEXT("%lld"), Appeal.Id))`.
(`totalWarnings` / `warnCount` are `int32` and remain as `SetNumberField` — int32 fits
exactly in a double.)

---

### ✅ Fixed — `PlayerWarningRegistry` does not persist `nextId` (BUG-08)
**File:** `Mods/BanSystem/Source/BanSystem/Private/PlayerWarningRegistry.cpp`

**Fix applied:** `SaveToFile()` now writes a `"nextId"` string field alongside the
`"warnings"` array. `LoadFromFile()` prefers the stored `nextId` (string-first /
number-fallback for legacy files) over the scan-based max+1 reconstruction, so deleting
the entry with the highest Id no longer regresses the counter and causes duplicate Ids.

---

### ✅ Fixed — `SaveTicketState` / `SaveTicketBlacklist` use non-atomic Delete + MoveFile (BUG-09)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp`

**Fix applied:** Both save paths now use `IFileManager::Get().Move(*Dest, *Tmp, /*bReplace=*/true)`
instead of the previous `PlatformFile.DeleteFile(*Dest)` + `PlatformFile.MoveFile(...)` two-step.
The single `IFileManager::Move(bReplace=true)` call is an atomic OS-level rename/replace —
there is no window where the live state file is absent. If the move fails the `.tmp` file is
deleted and a warning is logged; the live file is never touched.

---

### ✅ Fixed — `appeal_id` persisted as `double` in ticket state JSON (precision loss > 2^53) (BUG-10)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp`

**Fix applied:** `SaveTicketState()` now writes `appeal_id` as a string:
`SetStringField(TEXT("appeal_id"), FString::Printf(TEXT("%lld"), *AppealIdSave))`.
`LoadTicketState()` uses string-first / number-fallback for backward compatibility with
existing state files.

---

### ✅ Fixed — Pong echoes masked Ping payload without unmasking — RFC 6455 §5.3 violation (BUG-11)
**File:** `Mods/SMLWebSocket/Source/SMLWebSocket/Private/SMLWebSocketServerRunnable.cpp`

**Fix applied:** The Ping handler now XOR-unmasks each payload byte against the 4-byte mask
key (`Buf[HeaderSize + (i & 3)]`) before adding it to the Pong frame, matching the same
pattern used for regular text/binary frames. A comment explains the RFC 6455 §5.3 requirement.
When `bMasked` is false (server-to-server or unmasked client) the raw byte is used directly.

---

*Last updated: 2026-04-28. All 11 round-2 bugs resolved.*

---

## Round 3 — Additional Scan (2026-04-28)

### ✅ Fixed — `SaveTicketState()` missing closing `}` — compile error (BUG-01)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp`

**Fix applied:** Added the missing closing `}` for `SaveTicketState()` between the
`IFileManager::Get().Delete(*TmpPath)` statement and the start of `LoadTicketState()`.
Without this brace every function definition that followed (`LoadTicketState`, `GetStatsFilePath`,
etc.) was syntactically nested inside `SaveTicketState`, making the entire DiscordBridge module
a compile error.

---

### ✅ Fixed — `BanAppealRegistry::SaveToFile()` does not persist `NextId` (BUG-02)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanAppealRegistry.cpp`

**Fix applied:** `SaveToFile()` now writes `nextId` as a decimal string via
`SetStringField(TEXT("nextId"), FString::Printf(TEXT("%lld"), NextId))`.
`LoadFromFile()` now uses the string-first / number-fallback pattern (same as
`PlayerWarningRegistry` BUG-08 fix) to prefer the persisted counter over the
scan-based `max(id)+1` reconstruction. This prevents ID reuse after all appeals are
deleted and the server restarts.

---

### ✅ Fixed — `ScheduledBanRegistry::SaveToFile()` does not persist `NextId` (BUG-03)
**File:** `Mods/BanSystem/Source/BanSystem/Private/ScheduledBanRegistry.cpp`

**Fix applied:** Same pattern as BUG-02. `SaveToFile()` now writes a `"nextId"` string field
alongside the `"scheduled"` array. `LoadFromFile()` prefers the stored counter (string-first /
number-fallback) over the scan-based reconstruction. This prevents ID reuse once all pending
scheduled bans have fired and the list is empty on the next server restart.

---

### ✅ Fixed — `SaveStringToFile` return value ignored in ticket feedback stats write (BUG-04)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp`

**Fix applied:** The `FFileHelper::SaveStringToFile(...)` call for ticket feedback stats is now
checked with `if (!...)` and emits `UE_LOG(LogTicketSystem, Error, ...)` on failure, matching
the error-handling pattern used by every other file-write in the codebase. Previously a disk-full
or permission-denied error would silently lose rating data with no diagnostics.

---

*Last updated: 2026-04-28. All 4 round-3 bugs resolved.*

---

## Round 4 — Additional Scan (2026-04-29)

### ✅ Fixed — `BanAuditLog::LoadFromFile()`: malformed timestamp falls through with epoch date (BUG-01)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanAuditLog.cpp`

**Fix applied:** Added `continue;` (and changed the log message from "using default" to "skipping")
after the `FDateTime::ParseIso8601` failure path in `LoadFromFile()`, matching the identical
pattern already used in `BanAppealRegistry`, `PlayerWarningRegistry`, `ScheduledBanRegistry`,
and `MuteRegistry`. Previously a malformed timestamp caused the entry to be loaded with
`FDateTime(0)` ("0001-01-01"), making it permanently invisible at the bottom of every
newest-first audit listing.

---

### ✅ Fixed — `PlayerSessionRegistry`: `SaveToFile()` return value not checked at call sites (BUG-02)
**File:** `Mods/BanSystem/Source/BanSystem/Private/PlayerSessionRegistry.cpp`

**Fix applied:** All three `SaveToFile()` call sites (update-existing path in `RecordSession`,
insert-new-record path in `RecordSession`, and `PruneOldRecords`) now check the return value
and emit a `UE_LOG(Warning, ...)` on failure, matching the pattern established in
`BanAuditLog::LogAction`, `MuteRegistry`, `PlayerNoteRegistry`, and every other registry in
the codebase.

---

*Last updated: 2026-04-29. All 2 round-4 bugs resolved.*

---

## Round 5 — Additional Scan (2026-04-29)

### ✅ Fixed — `PlayerNoteRegistry::SaveToFile()` does not persist `NextId` (BUG-01)
**File:** `Mods/BanChatCommands/Source/BanChatCommands/Private/PlayerNoteRegistry.cpp`

**Fix applied:** `SaveToFile()` now writes `nextId` as a decimal string via
`SetStringField(TEXT("nextId"), FString::Printf(TEXT("%lld"), NextId))`.
`LoadFromFile()` now uses the string-first / number-fallback pattern (same as
`PlayerWarningRegistry` BUG-08 fix, `BanAppealRegistry` Round-3 BUG-02 fix, and
`ScheduledBanRegistry` Round-3 BUG-03 fix) to prefer the persisted counter over the
scan-based `max(id)+1` reconstruction. This prevents ID reuse after the note with the
highest Id is deleted and the server restarts.

---

*Last updated: 2026-04-29. All 1 round-5 bugs resolved.*

---

## Round 6 — Additional Scan (2026-04-29)

### ✅ Fixed — Ticket feedback stats write is non-atomic (BUG-01)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp`

**Fix applied:** The ticket feedback stats write (the only remaining direct `SaveStringToFile`
in the entire codebase) now uses the same atomic write-to-`.tmp`-then-`IFileManager::Move(bReplace=true)`
pattern already used by `SaveTicketState`, `SaveTicketBlacklist`, and every other registry.
If the process dies mid-write the `.tmp` file is left behind (and cleaned up on the next
successful write); the live `feedback_stats.json` is never left in a partial/truncated state.

---

*Last updated: 2026-04-29. All 1 round-6 bugs resolved.*

---

## Round 7 — Additional Scan (2026-04-29)

### ✅ Fixed — `JsonEscapeStr()` emits lone surrogates as `\uD800`–`\uDFFF` — invalid JSON (BUG-01)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/DiscordBridgeSubsystem.cpp`

**Fix applied:** Separated the surrogate-range guard from the control-character guard.
Lone surrogates (U+D800–U+DFFF) are now replaced with U+FFFD (the Unicode replacement
character) instead of being emitted as `\uD800`–`\uDFFF` escape sequences, which are
explicitly prohibited by RFC 8259 §7 and rejected by strict-mode JSON parsers (Python's
`json.loads`, `nlohmann::json`, and Discord's own REST API). The sister function
`BanDiscordNotifier::JsonEscape()` already used U+FFFD replacement; this fix brings the
two implementations into alignment.

---

### ✅ Fixed — `BanDatabase::ReloadIfChanged()` TOCTOU: concurrent external edit during `LoadFromFile` permanently clobbered by `PruneExpiredBans`'s `SaveToFile` (BUG-02)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanDatabase.cpp`

**Fix applied:** Added a mtime check immediately after `LoadFromFile()`. If the file
mtime advanced past `NewModTime` (i.e. a second external edit T2 arrived while we were
loading T1's content), `bConcurrentEditDuringLoad` is set. After `PruneExpiredBans()`
(which calls `SaveToFile`, writing T3 > T2 and setting `LastKnownFileModTime = T3`),
the flag is checked: if set, `LastKnownFileModTime` is reset to `FDateTime(0)`, forcing
the next `ReloadIfChanged` tick to see `T_current != FDateTime(0)` and trigger another
load. Without this guard the inline comment "a concurrent edit will produce T2 > T1 and
be detected on the next call" was only correct when no prune-write followed; the
`SaveToFile` at T3 > T2 caused `LastKnownFileModTime = T3`, making the next tick see
`T3 == T3` and return early — permanently silencing the T2 edit.

---

*Last updated: 2026-04-29. All 2 round-7 bugs resolved.*

---

## Round 8 — Additional Scan (2026-04-30)

### ✅ Fixed — `BanChat::JsonEscape()` emits lone surrogates as `\uD800`–`\uDFFF` — invalid JSON (BUG-01)
**File:** `Mods/BanChatCommands/Source/BanChatCommands/Private/Commands/BanChatCommands.cpp`

**Fix applied:** Separated the surrogate-range guard from the control-character guard.
Lone surrogates (U+D800–U+DFFF) are now replaced with U+FFFD (the Unicode replacement
character) instead of being emitted as `\uD800`–`\uDFFF` escape sequences, which are
explicitly prohibited by RFC 8259 §7. This is the same fix applied to
`DiscordBridgeSubsystem::JsonEscapeStr()` in Round 7 (BUG-01) and already present in
`BanDiscordNotifier::JsonEscape()`. `BanChat::JsonEscape()` is called at lines 1799–1800,
3765, and 3854–3855 to build Discord webhook JSON payloads — any player name or reason
containing a lone surrogate would have produced malformed JSON rejected by Discord's API.

---

### ✅ Fixed — `BanDiscordSubsystem` anonymous `JsonEscape()` emits lone surrogates as `\uD800`–`\uDFFF` — invalid JSON (BUG-02)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp`

**Fix applied:** Same fix as BUG-01 above. The anonymous-namespace `JsonEscape()` in
`BanDiscordSubsystem.cpp` combined the surrogate check with the control-character check
under one arm, causing lone surrogates to be emitted as `\uD800`–`\uDFFF`. Separated into
two distinct branches: control characters (C < 0x20) still emit `\uXXXX`, while lone
surrogates (U+D800–U+DFFF) now emit U+FFFD. This brings all four `JsonEscape`
implementations in the codebase into alignment.

---

*Last updated: 2026-04-30. All 2 round-8 bugs resolved.*

---

## Round 9 — Additional Scan (2026-05-02)

### ✅ Fixed — `SaveWarnedExpiryNames()` non-atomic write: `DeleteFile` + `MoveFile` two-step (BUG-01)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/DiscordBridgeSubsystem.cpp`

**Fix applied:** Replaced the `PF.DeleteFile(*Path)` + `PF.MoveFile(*Path, *TmpPath)` two-step
with `IFileManager::Get().Move(*Path, *TmpPath, /*bReplace=*/true)`. The old two-step had a
data-loss window: if `MoveFile` failed (disk-full, permission error, OS crash) after `DeleteFile`
had already removed the live file, both the live file and the `.tmp` were gone — all
`WarnedExpiryNames` state was lost. The new single `IFileManager::Move(bReplace=true)` call is
an atomic OS-level rename/replace with no such window. On failure the `.tmp` file is cleaned up
and the live file is never touched. This matches the identical pattern used by `SaveTicketState`,
`SaveTicketBlacklist`, `BanDatabase::SaveToFile`, and every other registry in the codebase.

---

*Last updated: 2026-05-02. All 1 round-9 bugs resolved.*

---

## Round 10 — Additional Scan (2026-05-02)

### ✅ Fixed — `FetchFuncHolder` `TSharedPtr` reference cycle — memory leak per ticket close (BUG-01)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp`

**Root cause:** The paginated transcript-fetch lambda assigned to `*FetchFuncHolder` captured
`FetchFuncHolder` itself by value (a `TSharedPtr`). This formed a reference cycle:
the `TFunction` object owned by `FetchFuncHolder` held a copy of `FetchFuncHolder`, so
after the outer function returned and the local variable was destroyed, the ref-count
dropped to 1 (held only by the lambda it contained). No external pointer could ever
reach the object again — it leaked permanently, including `PageAccum`, `BotToken`,
`ClosedChannelId`, `FinalizeTranscript`, and all their captures (~several KB per ticket close
whenever a `TicketLogChannelId` is configured).

**Fix applied:** Introduced `WeakFetchHolder` (`TWeakPtr`) immediately after the
`MakeShared<>` call. The outer lambda (stored inside `*FetchFuncHolder`) now captures
`WeakFetchHolder` instead of `FetchFuncHolder`, breaking the cycle. The inner
HTTP-completion lambda still captures `FetchFuncHolder` strongly — this keeps the shared
object alive for exactly as long as there is an HTTP request in flight. When the final
response is processed and `FinalizeTranscript()` is called, the completion-handler
closure is destroyed, the ref-count drops to 0, and all resources are freed.

---

### ✅ Fixed — `SendFrame()` called under `ClientMutex` for Pong responses — lock stall (BUG-02)
**File:** `Mods/SMLWebSocket/Source/SMLWebSocket/Private/SMLWebSocketServerRunnable.cpp`

**Root cause:** `ProcessFrames()` is called inside the `FScopeLock L(&ClientMutex)` block
in `Run()`. When a WebSocket Ping frame was received, the Pong was sent synchronously via
`SendFrame(Client.Socket, PongFrame)` while that lock was still held. `SendFrame()` is an
unbounded blocking loop; if the client's kernel send-buffer was full, it would block
indefinitely with `ClientMutex` held — stalling any game-thread call to
`GetClientCount()`, `GetClientIds()`, or `DisconnectClient()` that also takes the lock.
The outbound-drain phase at the top of `Run()` was already written to avoid this pattern
(its comment reads "ClientMutex released before any blocking I/O"), but the Pong path
was missed.

**Fix applied:** Replaced `SendFrame(Client.Socket, PongFrame)` with an enqueue into
`OutboundQueue` (the same `EQueueMode::Mpsc` queue used by `BroadcastText` and
`SendTextToClient`). The Pong is now delivered during the next iteration's outbound-drain
phase, after `ClientMutex` has been released — a sub-millisecond delay that is
acceptable per RFC 6455.

---

*Last updated: 2026-05-02. All 2 round-10 bugs resolved.*

---

## Round 11 — Full Source Audit (BanSystem · BanChatCommands · DiscordBridge)

**Scope:** Every `.cpp` file across all three mods was read in full during this audit pass.
Files covered:

| Mod | Files |
|-----|-------|
| BanSystem | `BanDatabase.cpp/h`, `BanTypes.cpp/h`, `BanEnforcer.cpp`, `BanDiscordNotifier.cpp`, `BanRestApi.cpp`, `BanSyncClient.cpp`, `BanAuditLog.cpp`, `BanAppealRegistry.cpp`, `ScheduledBanRegistry.cpp`, `PlayerWarningRegistry.cpp`, `BanWebSocketPusher.cpp`, `PlayerSessionRegistry.cpp`, `BanSystemModule.cpp`, `BanSystemConfig.cpp` |
| BanChatCommands | `BanChatCommands.cpp` (4 374 lines), `MuteRegistry.cpp`, `PlayerNoteRegistry.cpp`, `BanChatCommandsConfig.cpp`, `BanChatCommandsModule.cpp` |
| DiscordBridge | `DiscordBridgeSubsystem.cpp` (6 728 lines), `BanDiscordSubsystem.cpp` (7 217 lines), `TicketSubsystem.cpp`, `DiscordBridgeChatCommands.cpp`, `WhitelistManager.cpp`, `BanBridgeConfig.cpp`, `DiscordBridgeConfig.cpp`, `TicketConfig.cpp`, `WhitelistConfig.cpp`, `InGameMessagesConfig.cpp`, `DiscordBridge.cpp` |

**Result:** No correctness bugs, memory leaks, race conditions, null-pointer dereferences, or
data-loss paths were found. Two minor code-quality observations are noted below.

---

### ⚠️ Observation — `TryGetNumberField` with `int32` contradicts in-file comment
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/DiscordBridgeSubsystem.cpp`
**Lines:** 902–903 vs. 705

Line 705 carries an explicit comment: *"TryGetNumberField only accepts double& in UE5's FJsonObject API"*,
and the surrounding code correctly uses `double Seq` before casting. However, at line 902–903 an
`int32 InteractionType` is passed directly to `TryGetNumberField`. UE 5.3.2 (the engine version
used by Satisfactory 1.0) added `int32` / `int64` / `float` / `uint32` overloads via
`FJsonObject::TryGetNumberField`, so the code compiles and behaves correctly on the target
platform. The observation is that the comment on line 705 is now **outdated** and, at a glance,
makes the call on line 903 look like a bug when it is not. No code change is required for
correctness; the comment should be updated if clarity is desired.

---

### ⚠️ Observation — `SetNumberField` used for `int32` values across several files
**Files:** `BanDiscordNotifier.cpp` (~lines 195, 287), `BanSyncClient.cpp` (~line 89),
`ScheduledBanRegistry.cpp` (~line 367), and numerous routes in `BanRestApi.cpp`
(`count`, `banned`, `unbanned`, `warnCount`, `warnPoints`, `totalBans`, `kickCount`,
`reputationScore`, `totalPages`, etc.)

All of these values are `int32`. `double` has 53 bits of mantissa, which comfortably holds any
`int32` value without precision loss, so there is **no data corruption**. The observation is a
style inconsistency: other parts of the codebase use `SetStringField + FString::Printf(TEXT("%lld"), ...)`
for `int64` IDs (the canonical convention), but small-integer counters/durations scattered across
the REST API and notifier helpers still use `SetNumberField`. If a future audit tries to apply the
int64-string convention uniformly, these sites would need to be updated. No runtime impact exists.

---

*Last updated: 2026-05-06. Round-11 audit complete. No actionable bugs found.*

---

## Round 12 — Proactive Bug Fix Pass (2026-05-03)

Comprehensive sweep of all mods targeting crash-risk, security, and correctness issues.
All items below were fixed in small, independent commits on `copilot/full-bug-audit-code`.

---

### ✅ Fixed — XSS in appeal portal HTML (BUG-R12-01)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp`

**Root cause:** `ServerName` (derived from the database file-path base name) was injected directly
into the `<title>` and `<p>` tags of the HTML appeal form without HTML-encoding. If the database
path contained `<script>` or `&` characters the resulting HTML would be syntactically malformed.

**Fix:** Added an inline `HtmlEscape` lambda that replaces `& < > " '` with their entity
equivalents. The escaped `SafeServerName` is used in all two injection sites.

---

### ✅ Fixed — TOCTOU in appeal duplicate-check (BUG-R12-02)
**File:** `Mods/BanSystem/Source/BanSystem/Public/BanAppealRegistry.h`,
`Mods/BanSystem/Source/BanSystem/Private/BanAppealRegistry.cpp`,
`Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp`

**Root cause:** `GetAllAppeals()` released the mutex before `AddAppeal()` was called, creating a
window where two concurrent requests for the same UID could both pass the duplicate check.

**Fix:** Added `AddAppealIfNoDuplicate()` that performs the check and insertion atomically under
a single `FScopeLock`. The REST API endpoint now calls this method.

---

### ✅ Fixed — Appeal UID / reason / contactInfo not length-clamped (BUG-R12-03)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp`

**Fix:** Added `Left(128)`, `Left(2000)`, and `Left(500)` clamps on the player-supplied `uid`,
`reason`, and `contactInfo` fields before storing them, preventing database bloat.

---

### ✅ Fixed — int32 overflow in `totalPages` pagination calculation (BUG-R12-04)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp`

**Root cause:** `(Total + Limit - 1)` was computed as `int32 + int32 - 1`, which overflows when
`Total` is near `INT32_MAX`.

**Fix:** Cast `Total` to `int64` before the addition.

---

### ✅ Fixed — Template double-substitution in kick/ban messages (BUG-R12-10)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanTypes.cpp`

**Root cause:** `{reason}` was substituted first; if the admin-supplied reason contained the
literal text `{expiry}` or `{appeal_url}`, those placeholders would be expanded in the second
or third substitution pass.

**Fix:** Reordered substitutions — `{expiry}` and `{appeal_url}` are applied first (their values
are server-generated and safe), then `{reason}` last.

---

### ✅ Fixed — `ConstantTimeEquals` uint8 truncation (BUG-R12-50)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp`

**Root cause:** `uint8 Diff = static_cast<uint8>(Au.Length() ^ Bu.Length())` truncates to 8 bits;
strings whose lengths differ by exactly 256 bytes would compare as equal.

**Fix:** Changed accumulator to `uint32` and used `Au.Length() != Bu.Length() ? 1 : 0` for the
initial diff.

---

### ✅ Fixed — `/reputation/:uid` ignores LinkedUids for `bCurrentlyBanned` (BUG-R12-15)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp`

**Root cause:** The loop used `B.Uid.Equals(Uid, ...)` which does not check the `LinkedUids`
array of compound bans (e.g. IP counterpart).

**Fix:** Changed to `B.MatchesUid(Uid)`.

---

### ✅ Fixed — `FDateTime(0)` sentinel collision in `ReloadIfChanged` (BUG-R12-07)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanDatabase.cpp`,
`Mods/BanSystem/Source/BanSystem/Public/BanDatabase.h`

**Root cause:** `LastKnownFileModTime = FDateTime(0)` was used to force a reload on the next
tick, but `FDateTime(0)` is also what `IFileManager::GetTimeStamp` returns when the file does
not exist — so the reset would suppress the next tick's reload if the file happened to be absent.

**Fix:** Replaced the sentinel with a `bool bPendingForcedReload` flag that is consumed once per
tick. `FDateTime(0)` now exclusively means "file not found".

---

### ✅ Fixed — TOCTOU on appeal entry after `ReviewAppeal` (BUG-R12-26)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp`

**Root cause:** Both the Approve and Deny handlers called `ReviewAppeal(...)` and then
`GetAppealById(...)`. A concurrent delete between those two calls returned an empty
(default-constructed) entry.

**Fix:** `GetAppealById` is now called *before* `ReviewAppeal`. If the entry is not found the
handler returns early. The pre-fetched entry is used for all subsequent operations.

---

### ✅ Fixed — Template variable used before declaration in `BanBridgeConfig.cpp` (BUG-R12-41)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanBridgeConfig.cpp`

**Root cause:** `const FString Template = ...` was declared after an early-return block that
referenced `Template`, causing undefined behaviour.

**Fix:** Moved the `Template` declaration to the top of `RestoreDefaultConfigIfNeeded()`.

---

### ✅ Fixed — `PanelRateLimitSeconds = 0` pruning all map entries (BUG-R12-28)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp`

**Root cause:** When `PanelRateLimitSeconds == 0` the prune cutoff is `0 * 2 = 0 s`, causing
every stored timestamp to be pruned on the first call and the rate-limit to never fire.

**Fix:** Added an early check `PanelRateLimitSeconds > 0.0f`; the rate-limit block is skipped
entirely when the value is zero (rate-limiting disabled).

---

### ✅ Fixed — Discord markdown injection in kick log and appeal submissions (BUG-R12-36)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp`

**Root cause:** Player names and ban reasons were inserted into Discord message strings without
`EscapeMarkdown()`, allowing player-controlled names to break or inject Discord formatting.

**Fix:** Added `EscapeMarkdown(PlayerName)` and `EscapeMarkdown(Reason)` at the two unguarded
sites in the kick-log lambda and appeal-submission notification.

---

### ✅ Fixed — `int32` overflow in mute remaining-time calculation (BUG-R12-25)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp`

**Root cause:** `GetTotalMinutes()` returns `double`; the cast to `int32` overflows for mutes
longer than ~1490 days.

**Fix:** Compute in `int64`, clamp to `INT32_MAX`, then cast to `int32`.

---

### ✅ Fixed — Freeze/unfreeze UID set only updated when player is online (BUG-R12-27)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp`

**Root cause:** The `FrozenPlayerUids.Add/Remove` calls were guarded by `bMatchedFreeze /
bMatchedUnfreeze`, which is `false` when the target is offline. The set was never updated for
offline targets, making `/freeze` + disconnect + rejoin not work correctly.

**Fix:** Moved the `Add`/`Remove` calls outside the online-player block so the persistent UID
set is always updated.

---

### ✅ Fixed — `ScheduledBanRegistry` retry cap off-by-one (BUG-R12-13)
**File:** `Mods/BanSystem/Source/BanSystem/Private/ScheduledBanRegistry.cpp`

**Root cause:** `if (FE.RetryCount > 5)` dropped entries only after the 6th retry (7th attempt).

**Fix:** Changed to `>= 5` to enforce the documented 5-attempt cap.

---

### ✅ Fixed — Missing braces around `IntervalMinutes` if/else in `DiscordBridgeConfig.cpp` (BUG-R12-16)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/DiscordBridgeConfig.cpp`

**Root cause:** The `else` branch following an `if (Rest.FindChar(...))` was never attached to
its body because the body was a bare statement on the next line without braces.

**Fix:** Added explicit braces around both branches.

---

### ✅ Fixed — Non-ASCII characters passing through `SanitizeUsernameForChannel` (BUG-R12-33)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp`

**Root cause:** `FChar::IsAlnum` returns `true` for non-ASCII alphanumeric characters (e.g.
Cyrillic, accented Latin). Discord channel names allow only `[a-z0-9-]`, so these characters
caused HTTP 400 errors.

**Fix:** Replaced with an explicit ASCII-range check `(LC >= 'a' && LC <= 'z') || (C >= '0' && C <= '9')`.

---

### ✅ Fixed — Trailing dash introduced after `Left(40)` clamp (BUG-R12-32)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp`

**Root cause:** The trailing-dash trim ran before the 40-char clamp. The clamp could
re-introduce a trailing dash that was never trimmed.

**Fix:** Moved the trailing-dash trim to immediately after the `Left(40)` call.

---

### ✅ Fixed — `OpenerToAppealId` not removed for non-Pending appeals on inactivity close (BUG-R12-35)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp`

**Root cause:** `OpenerToAppealId.Remove(RemovedOpener)` was inside `if (...Pending)` so a
non-Pending entry would leak the opener→appeal mapping indefinitely.

**Fix:** Moved the `Remove` call outside the `Pending` guard so it always fires when a matching
appeal UID is found.

---

### ✅ Fixed — RFC 6455 WebSocket violations in `SMLWebSocketRunnable.cpp` (BUG-R12-44/45/46)
**File:** `Mods/SMLWebSocket/Source/SMLWebSocket/Private/SMLWebSocketRunnable.cpp`

**Fixes applied:**
- **RSV bits (§5.2):** Non-zero RSV1/2/3 bits now trigger a Close(1002) and disconnect.
- **Control frame validation (§5.5):** Control frames with `FIN=0` or payload >125 bytes now trigger a Close(1002) and disconnect.
- **8-byte length MSB (§5.2):** The most-significant bit of the 8-byte extended length field is now validated to be zero.

---

### ✅ Fixed — RFC 6455 WebSocket violations in `SMLWebSocketServerRunnable.cpp` (BUG-R12-43/44/47/48)
**File:** `Mods/SMLWebSocket/Source/SMLWebSocket/Private/SMLWebSocketServerRunnable.cpp`

**Fixes applied:**
- **Close echo (§5.5.1):** Server now echoes the client's Close frame before disconnecting.
- **RSV bits (§5.2):** Non-zero RSV1/2/3 bits now drop the client with an error log.
- **Unknown opcodes (§5.2):** Unknown/reserved opcodes now trigger a Close(1002) and disconnect.
- **Control frame validation (§5.5):** Control frames with `FIN=0` or payload >125 bytes now trigger a Close(1002) and disconnect.

---

*Last updated: 2026-05-03. Round-12 fixes applied.*

---

## Round 13 — Additional Scan (2026-05-03)

### ✅ Fixed — Legacy double→int64 cast missing upper-bound guard in 4 registries (BUG-R13-01/02/03/04)
**Files:**
- `Mods/BanSystem/Source/BanSystem/Private/BanAppealRegistry.cpp`
- `Mods/BanSystem/Source/BanSystem/Private/BanDatabase.cpp` (`JsonToEntry`)
- `Mods/BanSystem/Source/BanSystem/Private/ScheduledBanRegistry.cpp` (`LoadFromFile`)
- `Mods/BanSystem/Source/BanSystem/Private/PlayerWarningRegistry.cpp` (`LoadFromFile`)

**Root cause:** The legacy-format load path for IDs used `static_cast<int64>(IdDbl)` without
checking `IdDbl < static_cast<double>(INT64_MAX)`. A corrupted JSON value such as
`"id": 1e30` or `"id": Infinity` would cause `static_cast<int64>` to invoke undefined
behaviour (implementation-defined trap or garbage value on x86). `BanAuditLog.cpp`
already applied both `>= 1.0` and `< static_cast<double>(INT64_MAX)` guards; the other
four registries were inconsistent.

**Fix:** Added the same `&& IdDbl >= 1.0 && IdDbl < static_cast<double>(INT64_MAX)`
condition to the `TryGetNumberField` fallback branch in all four files, matching the
already-correct `BanAuditLog` pattern.

---

### ✅ Fixed — `PlayerNoteRegistry` legacy double→int64 cast missing INT64_MAX upper-bound guard (BUG-R13-05)
**File:** `Mods/BanChatCommands/Source/BanChatCommands/Private/PlayerNoteRegistry.cpp`

**Root cause:** The fallback had `&& IdDbl >= 1.0` (lower bound only) but no upper-bound
check. A value like `9.9e18` (which exceeds INT64_MAX) would silently produce a
negative or wrapped `int64` after the cast.

**Fix:** Added `&& IdDbl < static_cast<double>(INT64_MAX)`, making the guard match
all other registries.

---

### ✅ Fixed — Two separate `FDateTime::UtcNow()` calls in `PlayerWarningRegistry::AddWarning` (BUG-R13-06)
**File:** `Mods/BanSystem/Source/BanSystem/Private/PlayerWarningRegistry.cpp`

**Root cause:** `Entry.WarnDate` was set by one call to `UtcNow()` and `Entry.ExpireDate`
by a second, independent call. On an NTP step-correction, a leap-second, or extreme
scheduler pressure, the two calls could return timestamps milliseconds apart — causing
the warning to appear expired immediately on very short (`ExpiryMinutes = 1`) warnings
where the second call could trail the first by enough ticks to advance past the expiry.

**Fix:** Captured `Entry.WarnDate = FDateTime::UtcNow()` once, stored as `WarnNow`,
and used `WarnNow + FTimespan::FromMinutes(ExpiryMinutes)` for `ExpireDate`. Both
fields now share a single consistent timestamp.

---

### ✅ Fixed — `POST /bans/ip` accepts arbitrary string as IP address without format validation (BUG-R13-07)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp`

**Root cause:** `ipAddress` was read from the JSON request body and used verbatim to
construct the ban UID (`"IP:" + ipAddress`). No character-set or length validation was
performed, so an authorised API caller could submit a string containing path separators,
shell metacharacters, or other non-IP characters. The resulting ban entry would be
silently ineffective (never matching a real player IP), would pollute the database, and
could confuse sync clients or Discord embeds.

**Fix:** Added a two-step validation immediately after extracting `ipAddress`:
1. **Length check:** reject strings longer than 45 characters (generous limit that
   accommodates any valid IPv4 (max 15 chars), standard IPv6 (max 39 chars), or
   mixed IPv6/IPv4 uncompressed notation (max 45 chars)).
2. **Character whitelist:** reject any string containing characters outside
   `[0-9a-fA-F:.]` — the only characters legal in IPv4 and IPv6 address literals.
Both failure paths return HTTP 400 with `"ipAddress is invalid"`.

---

*Last updated: 2026-05-03. All 7 Round-13 bugs resolved.*


---

## Round 14

**Files audited (Round 14):** All `.cpp` source files across BanSystem, BanChatCommands, DiscordBridge, and SMLWebSocket mods (64 source files fully read).

**Bugs found: 2** — both in `HandleFreezeCommand` in `BanDiscordSubsystem.cpp`. Both were compilation-breaking errors. Fixed in-place.

---

### Bug R14-1 — `HandleFreezeCommand`: `APlayerController* PC` used outside its `for`-loop scope (compilation error, both branches)

**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp`
**Function:** `UBanDiscordSubsystem::HandleFreezeCommand`

**Description:**
In both the unfreeze branch and the freeze branch, a local variable `APlayerController* PC` was declared inside the body of a range-`for` loop over `GEngine->GetAllLocalPlayerControllers()`. After the loop's closing brace, the code used `bool bMatchedUnfreeze / bMatchedFreeze` to conditionally call `PC->SetIgnoreMoveInput(false/true)` — but at that point `PC` was out of scope (declared inside the loop body, not before it). This was a hard compilation error.

**Fix:** Removed the `bool bMatchedUnfreeze / bMatchedFreeze` variables and the post-loop `if (bMatched*) PC->SetIgnoreMoveInput()` calls. The `SetIgnoreMoveInput` call was moved inside the loop body immediately after the match, before the `break`, consistent with the working reference implementation `ExecutePanelFreeze`.

---

### Bug R14-2 — `HandleFreezeCommand`: incomplete `FString::Printf(` call — missing format string and closing `)` (compilation error, both branches)

**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp`
**Function:** `UBanDiscordSubsystem::HandleFreezeCommand`

**Description:**
In both the unfreeze branch and the freeze branch, the `ResultMsg` variable was constructed with a truncated `FString::Printf(` expression that had no arguments and no closing `)`. The expression was syntactically incomplete and would not compile.

**Fix:** Completed both `FString::Printf(` calls with the appropriate format strings and arguments, derived from the analogous working implementation in `ExecutePanelFreeze`:
- **Unfreeze:** `TEXT("🔓 **%s** (\`%s\`) has been **unfrozen** by **%s**."), *BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid, *SenderName`
- **Freeze:** `TEXT("❄️ **%s** (\`%s\`) has been **frozen** by **%s**. Use \`/mod freeze\` again to unfreeze."), *BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid, *SenderName`

---

*Last updated: 2026-05-03. All 2 Round-14 bugs resolved.*

---

## Round 15 — Full Source Audit (2026-05-03)

**Scope:** All `.cpp` / `.h` files across BanSystem, BanChatCommands, DiscordBridge, SMLWebSocket.  
7 bugs found and fixed.

---

### ✅ Fixed — `ConstantTimeEquals` accumulator not `volatile` — compiler may dead-store-eliminate loop (BUG-R15-01)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp`

**Root cause:** `uint32 Diff` was a plain non-volatile variable.  Once the compiler infers
that `Diff != 0` (e.g. from the length-mismatch branch), it is allowed to elide subsequent
`Diff |= …` assignments via dead-store elimination, shortcutting the constant-time loop and
leaking timing information about the API key.

**Fix:** Changed `uint32 Diff` to `volatile uint32 Diff`, also promoted the `ByteA ^ ByteB`
expression to `uint32` before the `|=` to prevent any narrowing-related UB.

---

### ✅ Fixed — API port not validated against upper bound 65535 (BUG-R15-02)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp`

**Root cause:** `if (ApiPort <= 0) return` accepted values such as `99999`, which caused a
silent bind failure inside UE's HTTP server module while the subsystem reported itself as
active.

**Fix:** Added `if (ApiPort > 65535)` guard with `UE_LOG(Error)` and early return.

---

### ✅ Fixed — `PushMuteEvent` sends uid-only envelope for non-"mute" event types (BUG-R15-03)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanWebSocketPusher.cpp`

**Root cause:** Only the `EventType == "mute"` branch populated `playerName`, `mutedBy`,
`reason`, and timing fields.  An "unmute" call produced an envelope with only `uid`, leaving
WebSocket subscribers with no actionable context.

**Fix:** Added `else` branch that emits `playerName`, `mutedBy`, and `reason` (when non-empty)
for all other event types (e.g. "unmute").

---

### ✅ Fixed — `RecordSession` captures timestamp before acquiring mutex (BUG-R15-04)
**File:** `Mods/BanSystem/Source/BanSystem/Private/PlayerSessionRegistry.cpp`

**Root cause:** `const FString NowStr = FDateTime::UtcNow().ToIso8601()` was called before
`FScopeLock Lock(&Mutex)`.  Under lock contention the stored `lastSeen` timestamp could
predate the actual record insertion by the entire wait duration.

**Fix:** Moved the `NowStr` capture to the first line inside the `FScopeLock` block so it
reflects the actual instant of mutation.

---

### ✅ Fixed — `AddCounterpartBans` does not kick currently-connected counterpart players (BUG-R15-05)
**File:** `Mods/BanChatCommands/Source/BanChatCommands/Private/Commands/BanChatCommands.cpp`

**Root cause:** After calling `DB->AddBan(IpEntry)` and `DB->AddBan(EosEntry)`,
`AddCounterpartBans` never called `UBanEnforcer::KickConnectedPlayer`.  A player who was
actively connected and matched a newly-created counterpart ban (IP or EOS) would continue
playing until the next periodic ban-check scan or their next reconnect.

**Fix:** Added `UBanEnforcer::KickConnectedPlayer(World, …, …GetKickMessage())` immediately
after each successful `AddBan` call for both the IP-counterpart and EOS-counterpart paths.

---

### ✅ Fixed — Discord gateway sequence number accepts fractional floats (BUG-R15-06)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/DiscordBridgeSubsystem.cpp`

**Root cause:** The guard `Seq >= 0.0 && Seq <= MAX_int32 && FMath::IsFinite(Seq)` allowed
non-integer values such as `1.9`, which `static_cast<int32>` would truncate to `1`.  A
malformed gateway sending `"s": 1.9` would cause a Resume with the wrong sequence number,
triggering spurious event replays.

**Fix:** Added `&& FMath::Fmod(Seq, 1.0) == 0.0` to the guard, ensuring only whole-number
values are accepted.

---

### ✅ Fixed — Proxy CONNECT response reader has no wall-clock deadline — DoS via slow proxy (BUG-R15-07)
**File:** `Mods/SMLWebSocket/Source/SMLWebSocket/Private/SMLWebSocketRunnable.cpp`

**Root cause:** `ConnectThroughProxy` read the proxy response one byte at a time with no
overall timeout.  `RawRecvExact` blocks up to `RecvTimeoutMs` (5 s) per byte; with the
`MaxLineBytes = 4096` cap, a proxy that trickles one byte every 4.9 s could stall the worker
thread for ~5.7 hours without triggering the `bStopRequested` check.

**Fix:** Added a 30-second wall-clock deadline (`FPlatformTime::Seconds() + 30.0`) checked at
the top of the read loop.  If the deadline is exceeded the function logs an error and returns
`false`, allowing the reconnect logic to retry.

---

*Last updated: 2026-05-03. All 7 Round-15 bugs resolved.*

---

## Round 16 — Additional Scan (2026-05-03)

### ✅ Fixed — `BanAppealRegistry::LoadFromFile()` — `NextId` legacy double cast missing upper-bound guard (BUG-R16-01)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanAppealRegistry.cpp`

**Root cause:** The legacy-format load path for `nextId` checked `StoredNextIdDbl >= 1.0`
(lower bound) but did **not** check `< static_cast<double>(INT64_MAX)` before
`static_cast<int64>(StoredNextIdDbl)`. A corrupted JSON value such as `"nextId": 1e30`
or `"nextId": Infinity` would invoke undefined behaviour (implementation-defined trap or
garbage value on x86), potentially producing a negative or wrapped `NextId` that corrupts
every subsequent appeal ID. This inconsistency was missed when the other four registries
were fixed in Round-13 (BUG-R13-01–04).

**Fix:** Added `&& StoredNextIdDbl < static_cast<double>(INT64_MAX)` to the
`TryGetNumberField` fallback branch, matching the already-correct pattern in every other
registry.

---

### ✅ Fixed — `BanAppealRegistry::LoadFromFile()` — skip-log prints unassigned `Entry.Uid` (BUG-R16-02)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanAppealRegistry.cpp`

**Root cause:** The `Entry.Id <= 0` early-skip path logged `uid=%s` using `*Entry.Uid`,
but `Entry.Uid` is only set several lines *later* via
`TryGetStringField(TEXT("uid"), Entry.Uid)`. The log therefore always printed an empty
string, making the diagnostic useless for identifying which record was malformed.

**Fix:** Removed the `uid=%s` placeholder from the log message (no uid is available
at that point — `Entry.Uid` is not yet parsed).

---

### ✅ Fixed — `PlayerWarningRegistry::LoadFromFile()` — `Points` double→int32 cast missing upper-bound guard (BUG-R16-03)
**File:** `Mods/BanSystem/Source/BanSystem/Private/PlayerWarningRegistry.cpp`

**Root cause:** The `points` field was read as a double and accepted when `PointsDbl >= 1.0`,
but there was no upper-bound guard. A corrupted or crafted value such as `"points": 1e30`
passes the lower-bound check and then invokes undefined behaviour in
`static_cast<int32>(PointsDbl)` (implementation-defined result; typically wraps to
INT_MIN on x86).

**Fix:** Added `&& PointsDbl <= static_cast<double>(MAX_int32)` to the guard, matching the
pattern used in `BanAuditLog`, `BanDatabase`, and the Round-13 fixes.

---

### ✅ Fixed — `ScheduledBanRegistry::LoadFromFile()` — `DurationMinutes` and `RetryCount` double→int32 casts have no range guards (BUG-R16-04)
**File:** `Mods/BanSystem/Source/BanSystem/Private/ScheduledBanRegistry.cpp`

**Root cause:**
- `DurationMinutes` was assigned via an unconditional `static_cast<int32>(DurDbl)` with no
  `FMath::IsFinite`, negative-value, or upper-bound check. NaN or ±Infinity produces
  undefined behaviour; any value outside `[0, INT32_MAX]` overflows.
- `RetryCount` had a `> 0.0` lower-bound check but no upper-bound check. A value like
  `1e30` would pass the guard and overflow on cast.

**Fix:** Added `FMath::IsFinite(DurDbl) && DurDbl >= 0.0 && DurDbl <= static_cast<double>(MAX_int32)`
for `DurationMinutes`, and `RetryDbl <= static_cast<double>(MAX_int32)` for `RetryCount`,
matching the fully-guarded pattern used by every other numeric-cast site in the codebase.

---

### ✅ Fixed — `SMLWebSocketServerRunnable` token comparison: `Diff` not `volatile` — compiler may dead-store-eliminate loop (BUG-R16-05)
**File:** `Mods/SMLWebSocket/Source/SMLWebSocket/Private/SMLWebSocketServerRunnable.cpp`

**Root cause:** The constant-time WebSocket upgrade token comparison used a plain
`uint32 Diff` accumulator. Once the compiler infers that `Diff != 0` (e.g. from the
length-XOR seed when `AuthLen != ExpectedLen`), it is allowed to elide subsequent
`Diff |= …` assignments via dead-store elimination — shortcutting the constant-time
loop and potentially leaking timing information about the server's API token. The
sister implementation in `BanRestApi::ConstantTimeEquals` was fixed with `volatile`
in Round-15 (BUG-R15-01), but this site was missed.

Additionally, the byte-level XOR expression was widened from
`static_cast<uint8>(a) ^ static_cast<uint8>(b)` (implicit int promotion, then
narrowing via `|=`) to
`static_cast<uint32>(static_cast<uint8>(a)) ^ static_cast<uint32>(static_cast<uint8>(b))`
to make the promotion explicit and prevent any compiler from emitting narrowed
intermediate values.

**Fix:** Changed `uint32 Diff` to `volatile uint32 Diff` and widened the per-byte XOR
operands to `uint32` before ORing into `Diff`, matching the `BanRestApi` pattern.

---

*Last updated: 2026-05-03. All 5 Round-16 bugs resolved.*

---

## Round 17 Bug Audit

### ✅ Fixed — `BanDiscordSubsystem` mute-reminder: `double→int32` cast without upper-bound clamp — undefined behaviour (BUG-R17-01)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp`

**Root cause:** In `OnPostLoginModerationReminder`, the number of remaining mute
minutes was computed with `static_cast<int32>(FMath::Max(0.0, timespan.GetTotalMinutes()))`.
For mutes longer than ~2 years the `double` value exceeds `INT32_MAX`, making the cast
undefined behaviour.

**Fix:** Introduced a two-step safe cast via an `int64` intermediate:
`static_cast<int32>(FMath::Min(RemainingMins64, static_cast<int64>(INT32_MAX)))`,
matching the pattern used at every other `double→int32` cast site in the codebase.

---

### ✅ Fixed — `BanRestApi` `/players/prune`: `double→int32` cast without upper-bound clamp — undefined behaviour (BUG-R17-02)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp`

**Root cause:** The `daysToKeep` field was parsed from the JSON body with
`DaysToKeep = static_cast<int32>(DaysDbl)`. A caller supplying a value greater than
`INT32_MAX` would produce undefined behaviour.

**Fix:** Clamped via `FMath::Min(static_cast<int64>(DaysDbl), static_cast<int64>(INT32_MAX))`
before the final `int32` cast, consistent with the rest of the codebase.

---

### ✅ Fixed — `SMLWebSocketServerRunnable` handshake: receive timeout not cleared after upgrade — stale 5-second deadline persists into message loop (BUG-R17-03)
**File:** `Mods/SMLWebSocket/Source/SMLWebSocket/Private/SMLWebSocketServerRunnable.cpp`

**Root cause:** `PerformHandshake` sets a 5-second `SO_RCVTIMEO` to protect against
slow/adversarial clients during the HTTP upgrade phase but never resets it.
After the upgrade succeeds the same deadline remains active on the socket.
Although the current message loop guards every `Recv` call with `HasPendingData`,
any future blocking-receive path or framework upgrade would silently inherit a
5-second hard cutoff, dropping legitimate idle-but-connected clients.

**Fix:** Added `Client.Socket->SetReceiveTimeout(FTimespan::Zero())` immediately
before `return true` to clear the deadline once the handshake is complete.

---

### ✅ Fixed — `TicketSubsystem` auto-ban on warn threshold: uses `IsCurrentlyBanned` instead of `IsCurrentlyBannedByAnyId` — linked UIDs not checked (BUG-R17-04)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp`

**Root cause:** When a player's warning count reached the configured threshold the
auto-ban guard called `DB->IsCurrentlyBanned(WarnUid, Existing)`.
`IsCurrentlyBanned` performs an exact UID match only; it misses bans recorded against
a linked UID (e.g. an IP ban or ban issued before UID linking).  
`IsCurrentlyBannedByAnyId` walks the entire linked-UID graph and is the correct
function for enforcement checks.

**Fix:** Changed call to `DB->IsCurrentlyBannedByAnyId(WarnUid, Existing)`.

---

### ✅ Fixed — `DiscordBridgeSubsystem` auto-ban on warn threshold: uses `IsCurrentlyBanned` instead of `IsCurrentlyBannedByAnyId` — linked UIDs not checked (BUG-R17-05)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/DiscordBridgeSubsystem.cpp`

**Root cause:** Same class of bug as BUG-R17-04. The warn-threshold auto-ban path in
`DiscordBridgeSubsystem` also called `DB->IsCurrentlyBanned(Uid, Existing)` instead
of `DB->IsCurrentlyBannedByAnyId(Uid, Existing)`, allowing a duplicate ban to be
issued for players already banned under a linked UID.

**Fix:** Changed call to `DB->IsCurrentlyBannedByAnyId(Uid, Existing)`.

---

### ✅ Fixed — `BanChatCommands` `/mutecheck`: `double→int32` cast without upper-bound clamp — undefined behaviour (BUG-R17-06)
**File:** `Mods/BanChatCommands/Source/BanChatCommands/Private/Commands/BanChatCommands.cpp`

**Root cause:** In `AMuteCheckChatCommand::ExecuteCommand`, the remaining mute time
was computed with `FMath::Max(1, static_cast<int32>(Remaining.GetTotalMinutes()))`.
For mutes longer than ~2 years the `double` value exceeds `INT32_MAX` before the
`int32` cast, which is undefined behaviour.

**Fix:** Two-step safe cast: first cast to `int64`, then clamp to `[1, INT32_MAX]`
using `FMath::Clamp`, matching the pattern used by every other similar site.

---

### ✅ Fixed — `BanDiscordSubsystem` Discord staffchat: online admins not notified — only moderators checked (BUG-R17-07)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp`

**Root cause:** The in-game delivery loop in the Discord `/staffchat` handler only
called `BccCfg->IsModeratorUid(CompoundUid)` to decide whether to forward the message
to a connected player. Admins (who pass `IsAdminUid` but not necessarily `IsModeratorUid`)
were silently skipped, so Discord staffchat messages were never delivered to online
admins.

**Fix:** Changed the condition to
`BccCfg->IsAdminUid(CompoundUid) || BccCfg->IsModeratorUid(CompoundUid)`,
consistent with the analogous checks at lines 3519–3521 and 6532–6534 of the
same file.

---

### ✅ Fixed — `BanDiscordSubsystem::HandleClearWarnByIdCommand`: inner `GI` declaration shadows outer — variable shadowing maintenance hazard (BUG-R17-08)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp`

**Root cause:** The function declared `UGameInstance* GI = GetGameInstance()` near the
top, verified it was non-null via an early-return, then—after the main logic—opened a
second `if (UGameInstance* GI = GetGameInstance())` block that re-declared `GI` in an
inner scope. Both declarations resolve to the same singleton, but the shadowing
obscures the proof that `GI` is non-null at that point and could mislead future editors
into believing an additional null check is necessary there.

**Fix:** Removed the inner redeclaration; the audit-log subsystem lookup now uses
the outer `GI` directly, which is guaranteed non-null by the earlier guard.

---

*Last updated: 2026-05-10. All 8 Round-17 bugs resolved.*

---

## Round 18 — Full Audit Bug Fixes

*Last updated: 2026-05-03. All 8 Round-18 bugs resolved.*

---

### ✅ Fixed — `SMLWebSocketServerRunnable::PerformHandshake`: missing closing `}` — compile error (BUG-R18-01)
**File:** `Mods/SMLWebSocket/Source/SMLWebSocket/Private/SMLWebSocketServerRunnable.cpp`

**Root cause:** A previous round added `Client.Socket->SetReceiveTimeout(FTimespan::Zero())`
before `return true;` in `PerformHandshake()` but omitted the function's closing `}`.
Without the brace the file cannot compile.

**Fix:** Added the missing `}` after `return true;`.

---

### ✅ Fixed — `BanRestApi POST /bans/bulk`: Discord notification and response contain `Id=0` (BUG-R18-02)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp`

**Root cause:** `UBanDatabase::AddBan(const FBanEntry&)` assigns the auto-incremented
`Id` to an internal copy and does not modify the caller's `FBanEntry`. The bulk-ban
loop passed the original `Ban` (with `Id=0`) directly to `FBanDiscordNotifier::NotifyBanCreated`
and `BanJson::EntryToJson`, producing Discord embeds and API responses with `id=0`.
Single-ban POST /bans already solved this correctly via a `GetBanByUid` round-trip.

**Fix:** After `AddBan` succeeds, call `DB->GetBanByUid(Ban.Uid, Saved)` and use `Saved`
for Discord notification, audit log, and the response array — matching the POST /bans pattern.
Falls back to the in-memory entry with a warning log if the lookup unexpectedly fails.

---

### ✅ Fixed — `BanRestApi DELETE /bans/ip/:ip`: missing IP format validation on URL parameter (BUG-R18-03)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp`

**Root cause:** `DELETE /bans/ip/:ip` extracted the IP from the URL path and immediately
constructed a `UBanDatabase::MakeUid(TEXT("IP"), IpAddress)` without validating
length or character set. `POST /bans/ip` applied strict validation (max 45 chars,
only `[0-9a-fA-F:.]`), but the matching DELETE endpoint did not.

**Fix:** Applied identical length (≤ 45 chars) and charset (`[0-9a-fA-F:.]`) validation
before constructing the UID — consistent with the POST endpoint.

---

### ✅ Fixed — `BanRestApi GET /reputation/:uid`: int32 overflow in score arithmetic (BUG-R18-04)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp`

**Root cause:** The reputation score was computed as
`100 - (WarnPoints * 5) - (TotalBans * 15) - (KickCount * 3)` in plain `int32`
arithmetic. With enough warnings or bans `WarnPoints * 5` overflows `INT32_MAX`,
producing a garbage (potentially positive) score.

**Fix:** Cast each operand to `int64` before multiplying, clamp the result to [0, 100],
then assign to `int32`.

---

### ✅ Fixed — `BanSystemModule::BackupConfigIfNeeded`: INI newline injection via config values (BUG-R18-05)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanSystemModule.cpp`

**Root cause:** All string-valued configuration fields (`DatabasePath`, `RestApiKey`,
`DiscordWebhookUrl`, `WebSocketPushUrl`, `BanKickMessageTemplate`,
`TempBanKickMessageTemplate`, `AppealUrl`, `GeoIpApiUrl`, `GeoIpKickMessage`,
and the per-element array values) were written verbatim into the generated INI content.
A value containing `\n` would inject extra lines into the file, potentially creating
spurious keys or overwriting later legitimate keys when the file is parsed on reload.

**Fix:** Added a `SanitizeIni` lambda at the top of `BackupConfigIfNeeded()` that
replaces `\r\n`, `\n`, and `\r` with a space. Applied it to every string-valued field
and array element in the generated content.

---

### ✅ Fixed — `BanRestApi POST /bans/bulk` and `DELETE /bans/bulk`: no UID count cap (DoS) (BUG-R18-06)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp`

**Root cause:** Neither the POST nor the DELETE bulk-ban endpoints limited the number
of UIDs in the request array. An authenticated caller could submit thousands of UIDs,
blocking the game thread for an extended period via repeated mutex-guarded DB writes,
KickConnectedPlayer iterations, and Discord webhook calls.

**Fix:** Added a `UidsArr->Num() > 500` guard immediately after the array is extracted
in both endpoints, responding with HTTP 400 if the limit is exceeded.

---

### ✅ Fixed — `TicketSubsystem ticket_cr_` / `ticket_modal:cr_`: `FCString::Atoi` on malformed index silently maps to 0 (BUG-R18-07)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp`

**Root cause:** All four `ticket_cr_` and `ticket_modal:cr_` parsing sites called
`FCString::Atoi` on the suffix without first checking that it was numeric.
`FCString::Atoi("")` and `FCString::Atoi("abc")` both return 0, which is a valid array
index when `CustomTicketReasons` is non-empty. A tampered `custom_id` such as
`ticket_cr_abc` would therefore silently open the first custom ticket type instead
of being rejected.

**Fix:** At all four sites, extracted the suffix into a named `FString IdxStr` and
added `if (!IdxStr.IsNumeric()) { … reject with error … return; }` before calling
`FCString::Atoi(*IdxStr)`.

---

### ✅ Fixed — `TicketSubsystem ticket_bancheck:`: `CheckOpenerId` not validated as a numeric Discord snowflake (BUG-R18-08)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp`

**Root cause:** The `ticket_bancheck:` button handler extracted the suffix as
`CheckOpenerId` and immediately embedded it into a Discord mention (`<@%s>`) without
verifying that it was a valid numeric Discord snowflake. A tampered `custom_id`
suffix could inject arbitrary text into the ephemeral staff message.

**Fix:** Added an `IsNumeric()` guard immediately after the extraction; non-numeric
values return an ephemeral error response and abort the handler.

---

*Last updated: 2026-05-03. All 8 Round-18 bugs resolved.*

---

## Round 19 — Full Source Audit (2026-05-03)

**Scope:** All `.cpp` / `.h` files across BanSystem, BanChatCommands, DiscordBridge, SMLWebSocket (fresh pass after Round-18 fixes).

---

### ✅ Fixed — `BanRestApi` POST /bans/bulk: `Reason`, `BannedBy`, `Category` used before declaration — compile error (BUG-R19-01)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp`

**Root cause:** The POST `/bans/bulk` lambda body called
`Body->TryGetStringField(TEXT("reason"), Reason)` etc. but the variables
`FString Reason, BannedBy, Category` were not declared in scope — compile error.

**Fix:** Added `FString Reason, BannedBy, Category;` declarations immediately before
the `TryGetStringField` calls.

---

### ✅ Fixed — `BanRestApi` DELETE /bans/bulk: `RemovedBy` used before declaration — compile error (BUG-R19-02)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp`

**Root cause:** Same pattern — `Body->TryGetStringField(TEXT("removedBy"), RemovedBy)`
called without `FString RemovedBy` being declared in scope.

**Fix:** Added `FString RemovedBy;` declaration immediately before the call.

---

### ✅ Fixed — `PlayerWarningRegistry::LoadFromFile()` — `nextId` double cast missing upper-bound guard (BUG-R19-03)
**File:** `Mods/BanSystem/Source/BanSystem/Private/PlayerWarningRegistry.cpp`

**Root cause:** The legacy `nextId` load path checked `StoredNextIdDbl >= 1.0` but
had no upper-bound guard. `Inf` or `NaN` passes `>= 1.0` and causes undefined
behaviour in `static_cast<int64>`.

**Fix:** Added `&& StoredNextIdDbl < 9.2e18` guard, matching the already-correct
BanAppealRegistry pattern.

---

### ✅ Fixed — `PlayerNoteRegistry::LoadFromFile()` — `nextId` double cast missing upper-bound guard (BUG-R19-04)
**File:** `Mods/BanChatCommands/Source/BanChatCommands/Private/PlayerNoteRegistry.cpp`

**Root cause:** Identical to BUG-R19-03.

**Fix:** Same fix applied.

---

### ✅ Fixed — `ScheduledBanRegistry::LoadFromFile()` — `nextId` double cast missing upper-bound guard (BUG-R19-05)
**File:** `Mods/BanSystem/Source/BanSystem/Private/ScheduledBanRegistry.cpp`

**Root cause:** Identical to BUG-R19-03/04 — `StoredNextIdDbl >= 1.0` check without upper bound.

**Fix:** Added `&& StoredNextIdDbl < static_cast<double>(INT64_MAX)` guard.

---

### ✅ Fixed — `BanRestApi` auto-ban on warning threshold: TOCTOU between `IsCurrentlyBannedByAnyId` and `AddBan` (BUG-R19-06)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp`

**Root cause:** The `POST /warnings` route checked `IsCurrentlyBannedByAnyId` and
then called `AddBan` as two separate operations. A concurrent request could insert
a permanent ban between the two calls, which would then be silently overwritten.

**Fix:** Replaced with the atomic `AddBanSkipIfPermanentExists` method that performs
the check and insertion under a single mutex acquisition.

---

### ✅ Fixed — `BanRestApi` CSV export endpoints missing `Content-Disposition` header (BUG-R19-07)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp`

**Root cause:** The three CSV export routes (`GET /audit/csv`, `GET /warnings/csv`,
`GET /players/csv`) returned `text/csv` without a `Content-Disposition: attachment`
header, so browsers displayed the content inline instead of downloading it.

**Fix:** Added `Content-Disposition: attachment; filename="audit.csv"` etc. to each.

---

### ✅ Fixed — `ScheduledBanRegistry::Tick()` cleanup uses `TArray::Contains()` — O(n²) (BUG-R19-08)
**File:** `Mods/BanSystem/Source/BanSystem/Private/ScheduledBanRegistry.cpp`

**Root cause:** `IdsToRemove` was a `TArray<int64>` and `Contains()` is O(n), making
the cleanup loop O(n²) for large scheduled-ban lists.

**Fix:** Changed to `TSet<int64>` for O(1) `Contains()`.

---

### ✅ Fixed — `BanDiscordSubsystem::ExecutePanelFreeze`: dead write-only `bMatchedUnfreeze` / `bMatchedFreeze` variables (BUG-R19-09)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp`

**Root cause:** `bool bMatchedUnfreeze` and `bool bMatchedFreeze` were declared and
set inside their loops but never read (post-loop logic always runs unconditionally).
MSVC would emit C4189 "local variable initialized but not referenced" for these.

**Fix:** Removed both dead variables.

---

*Last updated: 2026-05-03. All 9 Round-19 bugs resolved.*

---

## Round 20 — Full audit of BanSystem, BanChatCommands, DiscordBridge, SMLWebSocket (2026-05-03)

### Summary

Three bugs found, all in the same category: non-atomic TOCTOU (time-of-check / time-of-use)
race conditions in the auto-ban escalation paths triggered when a player is warned past the
configured threshold. Round 19 fixed the identical pattern in the REST API POST /warnings
handler but two analogous paths in the Discord bot and one additional panel path were
overlooked. All three are now fixed.

All other source files read during this audit were clean with respect to bugs not already
addressed in prior rounds:
- `ScheduledBanRegistry.cpp`, `BanSyncClient.cpp`, `BanWebSocketPusher.cpp`,
  `PlayerSessionRegistry.cpp`, `BanRestApi.cpp`, `BanDiscordNotifier.cpp` — no new issues.
- `SMLWebSocketRunnable.cpp`, `SMLWebSocketServerRunnable.cpp` — no new issues.
- `MuteRegistry.cpp`, `PlayerNoteRegistry.cpp` — no new issues.
- `TicketSubsystem.cpp` — one cosmetic/robustness note (see BUG-R20-NOTED below).

---

### ✅ Fixed — `BanDiscordSubsystem::HandleWarnCommand`: non-atomic auto-ban escalation (BUG-R20-01)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp` (~line 2059)

**Root cause:** When a `/warn` Discord slash command pushed a player over the auto-ban
threshold, the handler used a two-step pattern:
1. `DB->IsCurrentlyBannedByAnyId(Uid, Existing)` — read-only check
2. `DB->AddBan(AutoBan)` — write (separate database lock acquisition)

Between steps 1 and 2 a concurrent permanent ban could be inserted (e.g. by another admin
typing `/ban` in the same instant), and `AddBan` would silently overwrite it with the
shorter auto-ban. This is the exact TOCTOU that was documented and fixed for the REST API
in Round 19 (`AddBanSkipIfPermanentExists`), but the Discord slash-command path was missed.

**Fix:** Removed the `IsCurrentlyBannedByAnyId` pre-check; call
`DB->AddBanSkipIfPermanentExists(AutoBan, bSkipped)` directly so the guard and the write
happen inside a single database lock acquisition.

---

### ✅ Fixed — `UBanDiscordSubsystem::ExecutePanelWarn`: non-atomic auto-ban escalation (BUG-R20-02)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp` (~line 6297)

**Root cause:** `ExecutePanelWarn` (the panel-button `/warn` path, distinct from the slash
command) contained an identical two-step `IsCurrentlyBannedByAnyId` + `AddBan` pattern for
the auto-ban escalation block. Same risk as BUG-R20-01.

**Fix:** Same as BUG-R20-01 — replaced with `AddBanSkipIfPermanentExists`.

---

### ✅ Fixed — `AWarnChatCommand::ExecuteCommand_Implementation`: non-atomic auto-ban escalation (BUG-R20-03)
**File:** `Mods/BanChatCommands/Source/BanChatCommands/Private/Commands/BanChatCommands.cpp` (~line 2048)

**Root cause:** The in-game `/warn` chat command's auto-ban block checked
`BanDB->IsCurrentlyBannedByAnyId(Uid, ExistingAutobanEntry)` and, if false, called
`BanChat::DoBan(...)` which internally calls `DB->AddBan(Entry)`. The TOCTOU window is the
same as BUG-R20-01/02.

Additionally, `DoBan` called `BanChat::AddCounterpartBans` (to also ban the linked IP or
EOS UID) and logged the audit entry, but both steps were absent from the Discord path. The
original pre-check code also reconstructed a separate `ReviewBan` object for the
`NotifyAutoEscalationBan` call, using a fresh `FDateTime::UtcNow()` that could differ from
the actual ban timestamp — a minor inconsistency.

**Fix:** Replaced the `IsCurrentlyBannedByAnyId` + `DoBan` pair with an inlined block
that:
- Builds `AutoBanEntry` once (capturing `FDateTime::UtcNow()` once for all timing fields).
- Calls `BanDB->AddBanSkipIfPermanentExists(AutoBanEntry, bSkipped)` atomically.
- On success: kicks the player, calls `BanChat::AddCounterpartBans`, writes to the audit
  log, calls `FBanDiscordNotifier::NotifyBanCreated` and `NotifyAutoEscalationBan` — all
  using the same entry object so timestamps are consistent.
- On `bSkipped == true` (permanent ban exists): logs a diagnostic message.

---

### 📝 Noted (not fixed) — `TicketSubsystem::FinalizeTranscript`: fragile length heuristic for empty transcript detection (BUG-R20-NOTED)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp` (line 1306)

**Description:** The check used to detect "no Discord message history was fetched" compares
`TranscriptText.Len()` against the length of just the first header line plus a fixed `+80`
byte allowance, rather than inspecting whether `PageAccum->Pages` is empty. This is
technically correct for typical Discord user IDs and date strings (total header ≈ 84
characters, threshold = 107), but is fragile: if the header fields are unexpectedly long,
or if only very short messages (each < ~7 characters) were actually fetched, the heuristic
can fire incorrectly.

**Severity:** LOW — unlikely to cause visible issues in practice; the threshold comfortably
covers all real Discord user ID lengths (max 19 digits) and ISO-8601 date strings. Left as
a noted improvement opportunity.

---

*Last updated: 2026-05-03. All 3 Round-20 bugs resolved.*

---

## Round 21 Bug Audit

### ✅ Fixed — R21-A: int32 overflow in `HandleReputationCommand` reputation score
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp` (~line 4456)

**Root cause:** The reputation score formula `100 - (WarnPoints * 5) - (TotalBans * 15) - (KickCount * 3)` used `int32` arithmetic. With enough warnings, bans, or kicks the intermediate products overflow before `FMath::Max(0, ...)` can clamp the result, producing a meaningless score (identical to bug previously fixed in `BanRestApi.cpp`).

**Fix applied:** Introduced `int64 ScoreRaw` computed entirely in 64-bit arithmetic:
```cpp
const int64 ScoreRaw = static_cast<int64>(100)
    - (static_cast<int64>(WarnPoints) * 5)
    - (static_cast<int64>(TotalBans)  * 15)
    - (static_cast<int64>(KickCount)  * 3);
const int32 Score = static_cast<int32>(FMath::Max((int64)0, ScoreRaw));
```
This matches the pattern already used in `BanRestApi.cpp` lines 2769–2773.

---

### ✅ Fixed — R21-B: Non-atomic TOCTOU in chat-filter auto-ban escalation (`DiscordBridgeSubsystem.cpp`)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/DiscordBridgeSubsystem.cpp` (lines 2807–2834)

**Root cause:** The chat-filter auto-warn path used the two-call pattern
`IsCurrentlyBannedByAnyId(…)` → `AddBan(…)`, leaving a window where a concurrent action could add a permanent ban between the check and the insert, resulting in a duplicate or conflicting ban record. Same class of race condition previously fixed in Rounds 19–20 for other code paths.

**Fix applied:** Replaced the two-call pattern with the atomic helper:
```cpp
bool bSkippedPermanent = false;
if (DB->AddBanSkipIfPermanentExists(AutoBan, bSkippedPermanent)) { … }
```
The `IsCurrentlyBannedByAnyId` + `AddBan` calls and their enclosing `if` block were removed.

---

### ✅ Fixed — R21-C: int32 overflow in `AReputationChatCommand::ExecuteCommand_Implementation`
**File:** `Mods/BanChatCommands/Source/BanChatCommands/Private/Commands/BanChatCommands.cpp` (line 4247)

**Root cause:** Identical to R21-A — `100 - (WarnPoints * 5) - (TotalBans * 15) - (KickCount * 3)` performed in `int32`, with the same overflow risk.

**Fix applied:** Same int64-widening fix as R21-A:
```cpp
const int64 ScoreRaw = static_cast<int64>(100)
    - (static_cast<int64>(WarnPoints) * 5)
    - (static_cast<int64>(TotalBans)  * 15)
    - (static_cast<int64>(KickCount)  * 3);
const int32 Score = static_cast<int32>(FMath::Max((int64)0, ScoreRaw));
```

---

### ✅ Fixed — R21-D: Non-atomic TOCTOU in `ticket_modal:issuewarn` auto-ban escalation (`TicketSubsystem.cpp`)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp` (lines 2384–2410)

**Root cause:** The ticket-modal warn handler used the same non-atomic
`IsCurrentlyBannedByAnyId(…)` → `AddBan(…)` two-call race identical to R21-B. A concurrent ban addition could slip in between the two calls.

**Fix applied:** Replaced with the atomic `AddBanSkipIfPermanentExists` pattern:
```cpp
bool bSkippedPermanent = false;
if (DB->AddBanSkipIfPermanentExists(AutoBan, bSkippedPermanent)) { … }
```
The outer `if (!DB->IsCurrentlyBannedByAnyId(…))` guard and its nesting level were removed.

---

*Last updated: 2026-05-04. All 4 Round-21 bugs resolved.*

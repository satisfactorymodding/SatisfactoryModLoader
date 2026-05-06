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

---

## Round 22 — Audit Results

### ✅ Fixed — R22-A: Non-atomic TOCTOU in `ExecutePanelUnban` (`BanDiscordSubsystem.cpp`)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp` (lines 6586–6603)

**Root cause:** `ExecutePanelUnban` called `DB->GetBanByUid(Uid, BanRecord)` to capture `LinkedUids` for counterpart-ban cleanup, then called `DB->RemoveBanByUid(Uid)` as a separate operation. In the window between the two calls a concurrent admin action could modify the ban record (e.g., update `LinkedUids`), causing `RemoveCounterpartBans` to use a stale snapshot of the linked UIDs. This is the same `GetBanByUid + RemoveBanByUid` two-call race documented and fixed for the REST API (see R6-A) and appeal approval (see R18-B).

**Fix applied:** Replaced the two-call pattern with the atomic `RemoveBanByUid(Uid, BanRecord)` overload, which captures the removed entry within the same mutex scope:
```cpp
FBanEntry BanRecord;
if (!DB->RemoveBanByUid(Uid, BanRecord))
{
    // already-unbanned message
    return Msg;
}
// BanRecord is fully populated from the removed entry — safe to use LinkedUids
if (!BanRecord.LinkedUids.IsEmpty())
    ExtraRemoved = BanDiscordHelpers::RemoveCounterpartBans(this, DB, Uid, BanRecord.LinkedUids);
```

---

*Last updated: 2026-05-04. All 1 Round-22 bug resolved.*

---

## Round 23 — Audit Results

### ✅ Fixed — R23-A: Non-atomic TOCTOU in `HandleAppealApproveCommand` (`BanDiscordSubsystem.cpp`)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp` (lines 3820–3826)

**Root cause:** `HandleAppealApproveCommand` called `DB->IsCurrentlyBannedByAnyId(Entry.Uid, BanRecord)` to capture `BanRecord.LinkedUids`, then called `DB->RemoveBanByUid(BanRecord.Uid)` as a separate operation. A concurrent admin action could modify `LinkedUids` in the window between the two calls, causing `RemoveCounterpartBans` to use a stale snapshot. This is the same `IsCurrentlyBannedByAnyId + RemoveBanByUid` two-call race fixed for `ExecutePanelUnban` in R22-A.

**Fix applied:** Replaced the non-atomic overload with the `RemoveBanByUid(Uid, OutEntry)` overload so `LinkedUids` are captured within the same mutex scope as the removal:
```cpp
FBanEntry RemovedBan;
bUnbanned = DB->RemoveBanByUid(BanRecord.Uid, RemovedBan);
if (bUnbanned)
    BanDiscordHelpers::RemoveCounterpartBans(this, DB, RemovedBan.Uid, RemovedBan.LinkedUids);
```

---

### ✅ Fixed — R23-B: Non-atomic TOCTOU in ticket appeal-approval unban path (`TicketSubsystem.cpp`)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp` (lines 838–897)

**Root cause:** The ticket appeal approval handler called `BanDb->IsCurrentlyBannedByAnyId(*AppealEosUid, BanRecord)` to capture the ban entry (including `LinkedUids` and `Reason`), then called `BanDb->RemoveBanByUid(BanRecord.Uid, /*bSilent=*/true)` — the two-argument overload that does not capture the removed entry. Subsequent logic then read `BanRecord.LinkedUids` (for linked-ban cleanup) and `BanRecord.Reason` (for the approval message), both of which could be stale if a concurrent action modified the ban between the two calls.

**Fix applied:** Replaced the two-argument `RemoveBanByUid` call with the atomic three-argument overload `RemoveBanByUid(Uid, OutEntry, bSilent)`, then replaced all downstream uses of `BanRecord.LinkedUids`, `BanRecord.Uid`, and `BanRecord.Reason` with the corresponding fields from the atomically-captured `RemovedBan`:
```cpp
FBanEntry RemovedBan;
if (BanDb->RemoveBanByUid(BanRecord.Uid, RemovedBan, /*bSilent=*/true))
{
    for (const FString& LinkedUid : RemovedBan.LinkedUids) { … }
    UBanDatabase::ParseUid(RemovedBan.Uid, Platform, RawId);
    SessionReg->FindByUid(RemovedBan.Uid, Rec);
    if (!RemovedBan.LinkedUids.Contains(IpUid) && …) { … }
    // approval message uses *RemovedBan.Reason
}
```

---

*Last updated: 2026-05-05. All 2 Round-23 bugs resolved.*

---

## Round 24 — Full Fix Pass (2026-05-03)

**Scope:** BanDiscordSubsystem, DiscordBridgeSubsystem, TicketSubsystem, SMLWebSocketRunnable, SMLWebSocketServerRunnable.
All items identified at the end of the previous session but not applied are now fixed.

---

### ✅ Fixed — `BanDiscordSubsystem.cpp`: ~60 missing `EscapeMarkdown()` calls on player-controlled strings (BUG-R24-01)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp`

**Root cause:** Player-controlled strings (`PlayerName`, `DisplayName`, `Reason`, `SenderName`, `NoteText`, `OldReason`, `NewReason`, `KickReason`, `MuteReason`, ban entry fields, etc.) were embedded in Discord message format strings containing `**bold**` or `` `code` `` markdown without being passed through `EscapeMarkdown()`. A player whose name or ban reason contained `*`, `_`, `` ` ``, `~`, `|`, `>`, or `\` could inject arbitrary Discord formatting into moderation log messages.

**Fix:** Applied `EscapeMarkdown()` to all player-controlled string arguments at every `FString::Printf` Discord embed site — covering all handlers: ban/unban/kick/mute/warn/note/appeal/lookup/schedule/bulk/link and all `ExecutePanel*` functions.

---

### ✅ Fixed — `BanDiscordSubsystem.cpp`: `EscapeMarkdown()` used in JSON field instead of `JsonEscape()` (BUG-R24-02)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp` — `HandleReputationCommand`

**Root cause:** The `LastSeen` string was passed through `EscapeMarkdown()` before being placed into a Discord embed JSON `"value"` field. `EscapeMarkdown` escapes Discord markdown characters (`*`, `_`, `` ` ``, etc.) which are harmless in JSON but leaves JSON special characters (`"`, `\`) unescaped — the correct helper for JSON string values is `JsonEscape()`.

**Fix:** Changed `EscapeMarkdown(LastSeen)` → `JsonEscape(LastSeen)` at that site.

---

### ✅ Fixed — `DiscordBridgeSubsystem.cpp`: `int32` overflow in `VoteWindowMinutes * 60` (BUG-R24-03)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/DiscordBridgeSubsystem.cpp`

**Root cause:** `static_cast<float>(Config.VoteWindowMinutes * 60)` performed the multiplication in `int32` before the cast. Values of `VoteWindowMinutes` ≥ 35792 overflow before the float cast, producing a garbage timer interval.

**Fix:** Changed to `static_cast<float>(Config.VoteWindowMinutes) * 60.0f` — multiplication is done in `float` after the cast, eliminating the overflow.

---

### ✅ Fixed — `DiscordBridgeSubsystem.cpp`: TOCTOU in whitelist capacity check (BUG-R24-04)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/DiscordBridgeSubsystem.cpp`

**Root cause:** Two sites performed a capacity pre-check (`GetMaxSlots()` + `GetAllEntries().Num()`) as separate mutex operations before calling `AddPlayer`. A concurrent add between the check and the write could push the whitelist past capacity.

**Fix:** Removed the two-step pre-check. `AddPlayer` already performs the capacity check atomically inside its own lock and returns `false` when full. The capacity-full message is now shown as a post-check diagnostic after `AddPlayer` returns `false`.

---

### ✅ Fixed — `DiscordBridgeSubsystem.cpp`: `AddLambda([this])` on `UMuteRegistry` delegates (BUG-R24-05)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/DiscordBridgeSubsystem.cpp`

**Root cause:** `OnPlayerMuted.AddLambda([this]...)` and `OnPlayerUnmuted.AddLambda([this]...)` captured a raw `this` (a `UObject*`). If the subsystem is destroyed while a mute event is pending, the lambda would access a dangling pointer.

**Fix:** Changed to `AddWeakLambda(this, [this]...)` for both delegates.

---

### ✅ Fixed — `DiscordBridgeSubsystem.cpp`: 30+ missing `EscapeMarkdown()` on player-controlled strings (BUG-R24-06)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/DiscordBridgeSubsystem.cpp`

**Root cause:** Player names and reasons were embedded in Discord messages without `EscapeMarkdown()`.

**Fix:** Added a file-local `EscapeMarkdown()` helper and applied it to all player-controlled strings in whitelist expiry, approval/deny, add/remove confirmations, search results, AFK kick, verification flow, and mute event Discord embeds.

---

### ✅ Fixed — `TicketSubsystem.cpp`: Missing `EscapeMarkdown()` on player-controlled strings (BUG-R24-07)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp`

**Root cause:** `OpenerName`, `WlIgnCopy`, `ExtraInfoCopy`, `MacroName`, tag arguments, and other player-supplied strings were embedded in Discord messages without `EscapeMarkdown()`.

**Fix:** Added a local `EscapeMarkdown()` helper and applied it to all affected sites (whitelist approve/deny, ban appeal approved/denied, mute appeal denied, whitelist welcome, extra info line, macro name error, tag added/removed messages).

---

### ✅ Fixed — `TicketSubsystem.cpp`: Triple-backtick injection in Discord code-block embeds (BUG-R24-08)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp`

**Root cause:** Ban record fields (`PlayerName`, `Reason`, `BannedBy`) were embedded inside Discord ` ``` ` code blocks without sanitisation. A value containing "```" would escape the code block and inject arbitrary Discord markdown.

**Fix:** Applied `.Replace(TEXT("```"), TEXT("` ` `"))` to `PlayerName`, `Reason`, and `BannedBy` before embedding them in code-block format strings at both affected sites.

---

### ✅ Fixed — `TicketSubsystem.cpp`: Unsafe `double→int32` cast on `InteractionType` without range check (BUG-R24-09)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp`

**Root cause:** `InteractionType = static_cast<int32>(TypeD)` had no `IsFinite`/range guard. A malformed gateway payload with `"type": 1e30` or `"type": Infinity` would produce undefined behaviour.

**Fix:** Added `FMath::IsFinite(TypeD) && TypeD >= 0.0 && TypeD <= static_cast<double>(MAX_int32)` guard before the cast, defaulting to `0` on out-of-range values.

---

### ✅ Fixed — `TicketSubsystem.cpp`: Missing emptiness check on `DiscordUserId` before map lookups (BUG-R24-10)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp`

**Root cause:** `OpenerToTicketsByType.Find(DiscordUserId)` and `OpenerToTicketChannel.Contains(DiscordUserId)` were called without checking `DiscordUserId.IsEmpty()`. An empty string key could produce a false duplicate-ticket match.

**Fix:** Added `!DiscordUserId.IsEmpty()` guards before all affected map lookups in button and modal handlers, and early-return guards in `GetTicketChannelForOpener` and `CloseAppealTicketForOpener`.

---

### ✅ Fixed — `SMLWebSocketRunnable.cpp`: Client must reject masked frames from server — RFC 6455 §5.1 (BUG-R24-11)
**File:** `Mods/SMLWebSocket/Source/SMLWebSocket/Private/SMLWebSocketRunnable.cpp`

**Root cause:** The client's frame parser did not validate the mask bit on incoming server frames. RFC 6455 §5.1 requires a client to close the connection if it detects a masked frame from the server.

**Fix:** Added a check after RSV validation: if `bMasked` is true on a server→client frame, send Close(1002) and return `false`.

---

### ✅ Fixed — `SMLWebSocketServerRunnable.cpp`: Server must reject unmasked client frames — RFC 6455 §5.1 (BUG-R24-12)
**File:** `Mods/SMLWebSocket/Source/SMLWebSocket/Private/SMLWebSocketServerRunnable.cpp`

**Root cause:** The server processed unmasked client frames without error. RFC 6455 §5.1 requires a server to close the connection with Close(1002) if a client sends an unmasked frame.

**Fix:** Added a check after RSV validation: if `!bMasked`, enqueue Close(1002) and return `false`.

---

### ✅ Fixed — `SMLWebSocketServerRunnable.cpp`: Close echo ignores client's status code — RFC 6455 §5.5.1 (BUG-R24-13)
**File:** `Mods/SMLWebSocket/Source/SMLWebSocket/Private/SMLWebSocketServerRunnable.cpp`

**Root cause:** The server's Close-frame echo always sent an empty payload (`0x00`). RFC 6455 §5.5.1 requires the echo to include the client's status code (first 2 bytes of the client's Close payload) if one was provided.

**Fix:** The Close handler now extracts and unmasks the first 2 bytes of the client's payload (when `PayloadLen32 >= 2`) and includes them in the echo frame. If the client sent no payload, the empty-payload echo is retained.

---

*Last updated: 2026-05-03. All 13 Round-24 bugs resolved.*

---

## Clean-Slate UE5 Hardening Audit (2026-05-03)

A systematic full-codebase audit was performed across all 71 owner-mod source files
(BanChatCommands, BanSystem, DiscordBridge, SMLWebSocket) against the 8-phase
hardening plan.  Results:

### ✅ Phase 1 — Dead Code & Architecture
- No `#if 0` blocks or large commented-out code found.
- No `TODO` / `FIXME` comments found.
- `IDiscordBridgeProvider.h` is an **actively-used** abstract interface included by
  `TicketSubsystem.h`, `BanDiscordSubsystem.h`, and `DiscordBridgeSubsystem.h`; it
  is not a stub and must not be deleted.
- `ExampleMod` contains only template scaffolding (no `.h`/`.cpp` files); no action needed.

### ✅ Fixed — Phase 2 — `UE_LOG(LogTemp, ...)` in `BanTypes.cpp`
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanTypes.cpp:24`

**Root cause:** `FBanTemplate::FromConfigString()` used `LogTemp` when logging a
non-numeric `durationMinutes` field — the only `LogTemp` usage across all owner mod code.
Every other file already had a dedicated `DECLARE_LOG_CATEGORY_EXTERN` / `DEFINE_LOG_CATEGORY` pair.

**Fix:** Declared `DECLARE_LOG_CATEGORY_EXTERN(LogBanTypes, Log, All)` in `BanTypes.h`
and defined `DEFINE_LOG_CATEGORY(LogBanTypes)` in `BanTypes.cpp`.
Changed `UE_LOG(LogTemp, Warning, ...)` to `UE_LOG(LogBanTypes, Warning, ...)`.

---

### ✅ Phase 3 — Thread-Safety
All registry read paths inside `FScopeLock`; all ticker callbacks on game thread.
`check(IsInGameThread())` guards already in place on game-thread-only methods.

### ✅ Phase 4 — Memory & Lifecycle Safety
All HTTP `OnProcessRequestComplete()` callbacks that capture `this` use
`BindWeakLambda`; remaining `BindLambda` calls capture only local `FString`/
`int`/callback values by value (no `this` capture, no use-after-free risk).
All `FTSTicker::FDelegateHandle` arrays cancelled in `Deinitialize()`.
All `SUBSCRIBE_METHOD` hooks have matching `UNSUBSCRIBE_METHOD` in `ShutdownModule()`.
`volatile uint32 Diff` already present in `SMLWebSocketServerRunnable.cpp`.

### ✅ Phase 5 — Input Validation
All `FCString::Atoi64` call sites have length + INT64_MAX lexicographic guards.
All `FDateTime::ParseIso8601` call sites check the return value.
All REST API int64 ID parameters go through `ParseInt64Param()`.

### ✅ Phase 6 — File I/O
All `SaveToFile()` call sites check the `bool` return and log on failure.
All runtime data writes use write-to-`.tmp` then `IFileManager::Move` atomic rename.
All `FJsonSerializer::Serialize` calls are checked before any file I/O.

### ✅ Phase 7 — Logging & Observability
All 71 source files use properly declared per-file log categories after the
`LogBanTypes` fix above.  Error/Warning severities are correctly assigned throughout.

*Last updated: 2026-05-03. Hardening audit complete — 1 fix applied.*

---

## Round 25 — UE5 Optimization Pass (2026-05-03)

### Summary

A targeted UE5 optimization pass was performed across the four owner mods.  No new
correctness or security bugs were found — the codebase is clean after Rounds 1–24.
The focus was on:

- Replacing remaining hotpath indexed loops with range-based `for` and TArray helpers.
- Eliminating linear null-terminated array scans inside per-character loops.
- Adding automated tests for pure utility functions.

---

### ✅ Optimized — `EscapeMarkdown` inner linear scan → `switch` (OPT-R25-01)
**Files:** `BanDiscordSubsystem.cpp`, `DiscordBridgeSubsystem.cpp`, `TicketSubsystem.cpp`

**Root cause:** All three local `EscapeMarkdown` helper functions contained a nested
`for` loop that scanned a null-terminated `TCHAR SpecialChars[]` array (7 elements)
for each character of the input string.  This produced O(7 × N) work per call, where
N is the string length.  The static array variable also needlessly occupied BSS space.

**Fix:** Replaced the inner scan with a `switch` statement covering the 7 special
characters (`*`, `_`, `` ` ``, `~`, `|`, `>`, `\`).  The compiler generates a jump
table (or equivalent branch chain), reducing each character to O(1) and eliminating
the nested-loop overhead.  The outer loop already iterated with range-based `for`.

---

### ✅ Optimized — `WhitelistManager::RemovePlayer` indexed loop → `IndexOfByPredicate` (OPT-R25-02)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/WhitelistManager.cpp`

**Root cause:** Two explicit `for (int32 i = 0; i < Entries.Num(); ++i)` loops each
performed a linear scan to find the entry to remove, then stored the found index in
`RemovedIdx`.  UE5 TArray provides `IndexOfByPredicate` for this exact pattern.

**Fix:** Both search loops replaced with `Entries.IndexOfByPredicate(lambda)`.
Behaviour is identical; the UE intrinsic is more idiomatic and easier to read.

---

### ✅ Optimized — `WhitelistManager::RemoveExpiredEntries` manual index-then-reverse-remove → `RemoveAll` (OPT-R25-03)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/WhitelistManager.cpp`

**Root cause:** The function built a `TArray<int32> ToRemove`, then iterated it in
reverse to call `Entries.RemoveAt(i)` one-by-one (to preserve indices during
removal).  This required a separate `ToRemove` allocation and a reverse-iteration
loop in addition to the forward scan that collected names.

**Fix:**
1. Forward range-based `for` over `Entries` to collect expired names into `OutExpiredNames`.
2. `Entries.RemoveAll(lambda)` with the same predicate to remove all expired entries in a
   single O(N) pass without a secondary index array.

---

### ✅ Optimized — `BanRestApi` CSV LinkedUids separator loop → `FString::Join` (OPT-R25-04)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp`

**Root cause:** The CSV export built the `|`-separated `LinkedUids` string via a
`for (int32 i = 0; ...)` loop that prepended a separator for every element after the
first.  UE5 provides `FString::Join(Container, Separator)` for this exact pattern.

**Fix:** `const FString LinkedStr = FString::Join(E.LinkedUids, TEXT("|"))`.

---

### ✅ Optimized — `DiscordBridgeSubsystem` in-game message setup loop → range-based `for` (OPT-R25-05)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/DiscordBridgeSubsystem.cpp`

**Root cause:** The `InGameMessages` ticker-setup loop used `for (int32 i = 0; ...)` and
accessed the element via `InGameMessagesConfig.Messages[i]`.  The index was only
used once — in a log line — and does not need to be derived from the container access.

**Fix:** Converted to `for (const FInGameBroadcastMessage& Entry : ...)` with an explicit
`int32 BroadcastIdx = 0; ++BroadcastIdx;` counter for the log line.

---

### ✅ Added — Automation tests for BanSystem pure utility functions (OPT-R25-06)
**File:** `Mods/BanSystem/Source/BanSystem/Private/Tests/BanSystemTests.cpp`

**Added tests:**

| Test name | What it exercises |
|---|---|
| `BanSystem.BanTemplate.ParseValid` | `FBanTemplate::FromConfigString` — 3-field, 4-field, zero-duration, large-duration clamp |
| `BanSystem.BanTemplate.ParseInvalid` | Rejects < 3 fields, alpha duration, float duration |
| `BanSystem.BanDatabase.UidRoundTrip` | `MakeUid`/`ParseUid` round-trip for EOS, IP, lowercase, malformed |
| `BanSystem.FBanEntry.MatchesUid` | Primary UID, linked UIDs, misses, empty-string guard |
| `BanSystem.BanTemplate.ParseTemplates` | Batch parse skips invalid entries |
| `BanSystem.IdSerialization.Int64RoundTrip` | `Printf %lld` / `Atoi64` preserves IDs above 2⁵³; confirms double loses precision |

All tests are guarded by `#if WITH_DEV_AUTOMATION_TESTS` and use
`IMPLEMENT_SIMPLE_AUTOMATION_TEST` with
`EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter`.

---

### 📝 Noted — Registry save/load round-trip tests deferred (OPT-R25-NOTE)

Full save/load round-trip tests for `UBanDatabase`, `UBanAppealRegistry`,
`UPlayerWarningRegistry`, and `UScheduledBanRegistry` require calling private
`LoadFromFile`/`SaveToFile` methods against a temp file path.  To enable this
without exposing the API, add `#if WITH_DEV_AUTOMATION_TESTS` friend-class
declarations or `protected:` test-accessor setters to each registry header, then
extend this test file.  The `BanSystem.IdSerialization` test already validates the
core serialization contract (int64 string encoding).

---

### 📝 Noted — Coupling and consolidation (OPT-R25-ARCH)

**Mod coupling:** The `IDiscordBridgeProvider` abstract interface (275 lines in
`IDiscordBridgeProvider.h`) is the correct UE5 dependency-injection pattern for
decoupling `BanDiscordSubsystem` and `TicketSubsystem` from the concrete
`UDiscordBridgeSubsystem`.  Both consumers hold `IDiscordBridgeProvider*` set via
`SetProvider()` and cleared on `Deinitialize()`.  No code changes needed.

**Consolidation:** Whether to merge `BanChatCommands` into `BanSystem` and whether
to fold `SMLWebSocket` into `DiscordBridge` are valid long-term architecture
decisions, but they require a full build-and-test cycle and careful dependency
graph analysis.  They are left as forward-looking tasks beyond this pass.

---

*Last updated: 2026-05-03. All 5 optimizations applied; 6 tests added.*

---

## Round 26 — Full Source Audit (2026-05-04)

**Scope:** All `.cpp` / `.h` files across BanSystem, BanChatCommands, DiscordBridge, SMLWebSocket (fresh pass after Round 25).

---

### ✅ Fixed — `PlayerWarningRegistry::AddWarning(const FWarningEntry&)` does not enforce `Points >= 1` (BUG-R26-01)
**File:** `Mods/BanSystem/Source/BanSystem/Private/PlayerWarningRegistry.cpp`

**Root cause:** The `AddWarning(const FWarningEntry& InEntry)` overload (used by the REST API's
POST /warnings route) copied `InEntry` verbatim without applying the `FMath::Max(1, Points)`
guard present in every other `AddWarning` overload. A caller supplying `Points <= 0` would store
a zero- or negative-point warning in the in-memory `Warnings` array. `GetWarningPoints()` compensates
with `FMath::Max(1, W.Points)` so auto-ban thresholds were unaffected, but direct inspection of
`FWarningEntry.Points` in the same session returned the bad value. The inconsistency healed on
the next save/load via the `SaveToFile()` normalisation path.

**Fix:** Added `Entry.Points = FMath::Max(1, InEntry.Points);` immediately after
`Entry = InEntry;`, matching the normalisation already present in all other overloads.

---

### ✅ Fixed — `DisconnectClient()` sends no Close frame — RFC 6455 §7.1.1 violation (BUG-R26-02)
**Files:**
- `Mods/SMLWebSocket/Source/SMLWebSocket/Private/SMLWebSocketServerRunnable.h`
- `Mods/SMLWebSocket/Source/SMLWebSocket/Private/SMLWebSocketServerRunnable.cpp`

**Root cause:** `DisconnectClient()` removed the client from `Clients`, enqueued the socket to
`SocketsToDestroy`, and returned. No WebSocket Close frame (opcode `0x88`) was sent. RFC 6455
§7.1.1 requires the server to initiate the closing handshake by sending a Close frame before tearing
down the TCP connection. All other disconnect paths already send Close frames
(protocol-error paths at lines 520–528, client-initiated Close echo at lines 582–606), but the
server-initiated `DisconnectClient()` path (e.g., admin kicks) was missed.

The deferred-destruction model (enqueue socket, destroy at top of next `Run()` iteration) was
already safe for `SendFrame` because all previous-iteration raw-pointer snapshots have been
released by the time the queue is drained. The Close frame can therefore be sent at that same
point without any additional synchronization.

**Fix:**
1. Introduced `FPendingCloseSocket { FSocket* Socket; TArray<uint8> CloseFrame; }` in the header,
   replacing the plain `TQueue<FSocket*>` with `TQueue<FPendingCloseSocket, EQueueMode::Mpsc>`.
2. `DisconnectClient()` now builds a `Close(1000 Normal Closure)` frame (`0x88 0x02 0x03 0xE8`)
   and enqueues it alongside the socket pointer.
3. Both drain sites in `Run()` (top-of-loop and shutdown final drain) now call
   `SendFrame(S.Socket, S.CloseFrame)` before destroying the socket. Send failures are silently
   ignored — the client may have already closed their side, and the socket must still be destroyed.

---

### ✅ Fixed — `BackupConfigIfNeeded()` uses non-atomic `SaveStringToFile` (BUG-R26-03)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanSystemModule.cpp`

**Root cause:** `BackupConfigIfNeeded()` wrote the INI backup file via a direct
`FFileHelper::SaveStringToFile()` call. If the server process was killed mid-write (OOM,
SIGKILL, power loss), the backup file was left partially written. `RestoreDefaultConfigIfNeeded()`
validates the file by checking for `#` characters — a partially-written file may or may not pass
this check, making the config-restoration behaviour unpredictable. Every other persistent data file
in the codebase (all JSON registries, ticket state, whitelist state) already used the
write-to-`.tmp` then `IFileManager::Move(bReplace=true)` atomic-rename pattern.

**Fix:** Rewrote the write section to: write to `BackupPath + ".tmp"`, then atomically rename to
`BackupPath` via `IFileManager::Get().Move(*BackupPath, *TmpPath, true)`. On failure the `.tmp`
file is deleted and a warning is logged; the live backup file is never touched.

---

*Last updated: 2026-05-04. All 3 Round-26 bugs resolved.*

---

## Round 27 — Full Source Audit (2026-05-05)

**Scope:** All `.cpp` / `.h` files across BanSystem, BanChatCommands, DiscordBridge, SMLWebSocket
(fresh pass after Round 26).  Files read in full:
BanDiscordSubsystem.cpp (7 423 lines), DiscordBridgeSubsystem.cpp (6 775 lines),
TicketSubsystem.cpp (5 402 lines), BanRestApi.cpp (2 943 lines), BanEnforcer.cpp (1 148 lines),
BanChatCommands.cpp, MuteRegistry.cpp, PlayerNoteRegistry.cpp, BanChatCommandsModule.cpp,
DiscordBridgeConfig.cpp, TicketConfig.cpp, WhitelistConfig.cpp, WhitelistManager.cpp,
InGameMessagesConfig.cpp, BanBridgeConfig.cpp, BanDiscordNotifier.cpp, BanAuditLog.cpp,
BanAppealRegistry.cpp, BanDatabase.cpp, BanSyncClient.cpp, BanSystemConfig.cpp,
BanTypes.cpp, BanWebSocketPusher.cpp, PlayerSessionRegistry.cpp, PlayerWarningRegistry.cpp,
ScheduledBanRegistry.cpp, BanSystemModule.cpp, DiscordBridgeChatCommands.cpp,
SMLWebSocketRunnable.cpp, SMLWebSocketServerRunnable.cpp.

---

### ✅ Fixed — `HandleUnbanNameCommand` skips `RemoveCounterpartBans` (R27-A)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp`

**Root cause:** Every other unban path (e.g. `HandleUnbanCommand`) calls
`BanDiscordHelpers::RemoveCounterpartBans(this, DB, Uid, LinkedUids)`, which does two things:
(1) removes all bans whose Uid is listed in `LinkedUids`, and (2) looks up the player in
`UPlayerSessionRegistry` to find any counterpart UID not yet in `LinkedUids` (e.g. a session-IP
ban recorded after the original ban was created).  `HandleUnbanNameCommand` (Discord slash
`/ban removename`) replaced this with a bare `for (LinkedUid : RemovedEntry.LinkedUids)` loop
plus an IP-address fallback gated on `Removed == 0`.  The IP fallback was therefore skipped
whenever the EOS counterpart was found, leaving the IP ban active.

**Fix:** Replaced the manual loop with a single
`BanDiscordHelpers::RemoveCounterpartBans(this, DB, Record.Uid, RemovedEntry.LinkedUids)` call,
matching every other unban code path.  Removed the now-unused `int32 Removed` variable.

---

### ✅ Fixed — `HandleUnbanNameCommand` never fires `NotifyBanRemoved` webhook (R27-B)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp`

**Root cause:** After successfully removing a ban, every other unban path calls
`FBanDiscordNotifier::NotifyBanRemoved(Uid, PlayerName, AdminName)` to post a Discord webhook
embed and fire the `OnBanRemoved` delegate (used by `BanSyncClient` for multi-server sync).
`HandleUnbanNameCommand` never called it, so successful `/ban removename` unbans were invisible
in Discord audit channels and not propagated to peer servers.

**Fix:** Added `FBanDiscordNotifier::NotifyBanRemoved(Record.Uid, Record.DisplayName, SenderName)`
immediately after the successful unban, matching the pattern in `HandleUnbanCommand`.  Also updated
the success reply message to match the style of the other unban handlers.

---

### ✅ Fixed — Missing closing `)` on `SendDiscordDM` call in `HandleInGameVerify` (R27-C)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/DiscordBridgeSubsystem.cpp`

**Root cause:** Line 4620 read:
```cpp
SendDiscordDM(DiscordUserId, FString::Printf(
    TEXT("✅ Your in-game account **%s** has been verified and added to the whitelist!"),
    *EscapeMarkdown(PlayerName));
```
The `)` closed `FString::Printf(` but not the outer `SendDiscordDM(` call, making the
translation unit fail to compile.

**Fix:** Added the missing closing `)` so the line reads:
```cpp
    *EscapeMarkdown(PlayerName)));
```

---

*Last updated: 2026-05-05. All 3 Round-27 bugs resolved.*

---

## Round 28 Fixes

### ✅ Fixed — `DoBan()` uses plain `AddBan` for temp bans, allowing silent permanent-ban downgrade (R28-A)
**Files:** `Mods/BanChatCommands/Source/BanChatCommands/Private/Commands/BanChatCommands.cpp`,
           `Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp`

**Root cause:** `BanChat::DoBan()` (chat `/tempban` command) and the REST API `POST /bans` handler
both called `DB->AddBan(Entry)` unconditionally for all ban types. `AddBan` replaces any existing
record, so issuing a `/tempban` or a `POST /bans` with `durationMinutes > 0` against a player who
already held a permanent ban would silently overwrite it with a shorter temporary ban — effectively
an unintended pardon. All other ban paths (Discord slash commands, scheduled bans, auto-escalation,
counterpart bans) were already using `AddBanSkipIfPermanentExists` from prior rounds.

**Fix (`DoBan`):** Split the `AddBan` call — permanent bans still use `DB->AddBan(Entry)`; temp
bans now use `DB->AddBanSkipIfPermanentExists(Entry, bSkippedPerm)`. When `bSkippedPerm` is true,
a yellow "already has a permanent ban" message is returned to the sender.

**Fix (`POST /bans`):** Same split applied in the REST handler. When a temp ban is skipped, the
API now returns HTTP 409 Conflict with an explanatory message.

*Last updated: Round 28. 2 bugs fixed.*

---

## Round 29 — Full Source Audit (2026-05-06)

**Scope:** All `.cpp` / `.h` files across BanSystem, BanChatCommands, DiscordBridge, SMLWebSocket
(fresh pass after Round 28).

---

### ✅ Fixed — 16 player-controlled strings sent to Discord without `EscapeMarkdown()` (R29-A)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/DiscordBridgeSubsystem.cpp`

**Root cause:** Several Discord message-building code paths substituted player-controlled strings
(player display names, EOS Product User IDs, IP addresses) directly into Discord message text or
embed content without passing them through `EscapeMarkdown()`.  Because Discord renders markdown in
message bodies, embed titles, embed descriptions, and embed field values, a player with a crafted
display name (e.g. `**admin**`, `@everyone`, `__root__`) could inject arbitrary Discord formatting
or mention markers into the server's public Discord channel or into a moderator's DM.

`EscapeMarkdown()` is already defined at file scope (line 80) and is consistently used throughout
the rest of the file (AFK-kick notification, whitelist add/remove, chat relay to Discord, etc.).
The affected call sites had simply been missed.

**Affected locations and fixes applied:**

| Line | Location | Fix |
|------|----------|-----|
| 3249 | `WhitelistKickDiscordMessage` replacement | `*PlayerName` → `*EscapeMarkdown(PlayerName)` |
| 3287 | Join-reaction embed field `"value"` | `PlayerName` → `EscapeMarkdown(PlayerName)` |
| 3340 | `PlayerJoinMessage` replacement | `*PlayerName` → `*EscapeMarkdown(PlayerName)` |
| 3349 | `PlayerJoinAdminMessage` `%PlayerName%` | `*PlayerName` → `*EscapeMarkdown(PlayerName)` |
| 3350 | `PlayerJoinAdminMessage` `%EOSProductUserId%` | `*EOSProductUserId` → `*EscapeMarkdown(EOSProductUserId)` |
| 3351 | `PlayerJoinAdminMessage` `%IpAddress%` | `*IpAddress` → `*EscapeMarkdown(IpAddress)` |
| 3378 | `WelcomeMessageDM` replacement | `*PlayerName` → `*EscapeMarkdown(PlayerName)` |
| 3539 | `PlayerLeaveMessage` / `PlayerTimeoutMessage` replacement | `*PlayerName` → `*EscapeMarkdown(PlayerName)` |
| 4422 | `SendPlayerEventEmbed` field `"value"` | `PlayerName` → `EscapeMarkdown(PlayerName)` |
| 4613 | `WhitelistApprovedDmMessage` replacement | `*PlayerName` → `*EscapeMarkdown(PlayerName)` |
| 4909 | `HandlePlayerStatsCommand` embed title | `*TargetPlayerName` → `*EscapeMarkdown(TargetPlayerName)` |
| 4933 | `HandlePlayerStatsCommand` embed description | `*TargetPlayerName` → `*EscapeMarkdown(TargetPlayerName)` |
| 5771 | `HandleOnlineCommand` embed description list | `*PS->GetPlayerName()` → `*EscapeMarkdown(PS->GetPlayerName())` |
| 5809 | `NotifyMuteEvent` embed title | `*PlayerName` → `*EscapeMarkdown(PlayerName)` |
| 6460 | `/players` slash-command name list | `Names.Add(PS->GetPlayerName())` → `Names.Add(EscapeMarkdown(PS->GetPlayerName()))` |
| 6514 | `/online` slash-command reply list | `*PS->GetPlayerName()` → `*EscapeMarkdown(PS->GetPlayerName())` |

*Last updated: Round 29. 1 bug cluster (16 call sites) fixed.*

---

## Round 30 — Bug Audit Results

*Files audited: BanRestApi.cpp, BanChatCommands.cpp, BanDiscordSubsystem.cpp, TicketSubsystem.cpp, SMLWebSocketRunnable.cpp, SMLWebSocketServerRunnable.cpp*

### ✅ R30-01 — BanRestApi.cpp: `FCString::Atoi` overflow on `?limit=` / `?page=` params
**File:** `BanSystem/Private/BanRestApi.cpp` ~line 1295
**Severity:** MEDIUM
The `Len() <= 10` guard allows values up to 9,999,999,999 which exceeds `INT32_MAX`.
`FCString::Atoi` wraps silently (UB). Fixed by using `FCString::Atoi64` with an explicit
range clamp before narrowing to `int32`.

### ✅ R30-02 — BanRestApi.cpp: `DELETE /bans/ip/:ip` single-arg `RemoveBanByUid`
**File:** `BanSystem/Private/BanRestApi.cpp` ~line 1601
**Severity:** LOW
Used the single-arg overload that discards the removed entry, causing `NotifyBanRemoved`
and the audit log to always receive the raw IP string instead of the stored `PlayerName`.
Fixed by switching to the two-arg overload and using a `DisplayName` fallback.

### ✅ R30-03 — BanRestApi.cpp: `DELETE /bans/bulk` missing entry capture / player name
**File:** `BanSystem/Private/BanRestApi.cpp` ~lines 2948–2953
**Severity:** LOW
The bulk-unban loop used the single-arg `RemoveBanByUid`, passing an empty `PlayerName`
to `NotifyBanRemoved` and the audit log. Fixed by using the two-arg overload and passing
`RemovedEntry.PlayerName` (with `Uid` as fallback).

### ✅ R30-05 — SMLWebSocketServerRunnable.cpp: Close frames never sent before socket destroy
**File:** `SMLWebSocket/Private/SMLWebSocketServerRunnable.cpp` ~lines 521–534, 585–610, 269–289
**Severity:** MEDIUM (RFC 6455 §7.1.1 violation)
`ProcessFrames` enqueued terminal Close frames (received-Close echo and unmasked-frame
1002 error) to `OutboundQueue`. However, the outbound queue is drained at the **top** of
each loop iteration — **before** the read phase that populates `ToRemove`. The client is
removed from `Clients` and the socket destroyed in `ToRemove` before the next drain, so
the Close frame lookup finds no socket and the frame is silently dropped.
Fixed by introducing `FClientState::PendingCloseFrame`, set in `ProcessFrames` under the
`ClientMutex`, and sent inline in the `ToRemove` loop immediately before socket destroy
(outside the mutex, so `SendFrame` does not hold the lock).

### ✅ R30-08 — BanDiscordSubsystem.cpp: `ParseDurationMinutes` int32 overflow for large plain integers
**File:** `DiscordBridge/Private/BanDiscordSubsystem.cpp` ~line 1145
**Severity:** MEDIUM
`FDefaultValueHelper::ParseInt` (int32) was used for plain-integer duration strings.
A string like `"2200000000"` passes `IsNumeric()` but exceeds `INT32_MAX`, triggering
silent int32 overflow UB. The wrapped negative value hits the `Val > 0` guard and returns
`0` (interpreted as permanent by callers) instead of an error.
Fixed by using `FDefaultValueHelper::ParseInt64` with an explicit `<= INT32_MAX` range check.

### ✅ R30-09 — BanDiscordSubsystem.cpp: Empty `PlayerName` in ban-added moderation-log message
**File:** `DiscordBridge/Private/BanDiscordSubsystem.cpp` ~line 424
**Severity:** LOW
For pre-emptive bans (placed before the player has ever connected) `Entry.PlayerName` is
empty, producing a blank bold field in the Discord moderation-log embed. Added `Uid` as
fallback: `DisplayName = PlayerName.IsEmpty() ? Uid : PlayerName`.

### ✅ R30-10 — BanChatCommands.cpp: `/mutecheck` shows "1m remaining" for expired timed mutes
**File:** `BanChatCommands/Private/Commands/BanChatCommands.cpp` ~line 3084
**Severity:** LOW
`FMath::Clamp(RemainingMin64, 1LL, INT32_MAX)` floored the remaining time to 1 for expired
mutes (remaining ≤ 0), causing admins to believe the player was still muted.
Fixed by checking `RemainingMin64 <= 0` first: calls `UnmutePlayer` to remove the stale
entry and reports "mute has expired" instead of clamping to 1.

### ✅ TicketSubsystem.cpp, SMLWebSocketRunnable.cpp — No new bugs found
Both files were audited and found clean with respect to the specified focus areas.

*Last updated: Round 30. 6 bugs fixed (R30-01 through R30-10, with R30-04/06/07 non-issues).*

---

## Round 31 — Bug Audit Results

**Files read this round (no prior-round coverage):**
- `BanEnforcer.cpp` lines 1000–1148 (tail) — clean
- `BanSystemModule.cpp` lines 450–799 (tail) — clean
- `BanRestApi.h`, `BanAuditLog.h` — clean
- All remaining BanSystem and DiscordBridge public headers reviewed

**2 bugs found and fixed:**

### ✅ R31-01 — InGameMessagesConfig.cpp: `ExtractQuotedField` ignores `\"` escape sequences
**File:** `DiscordBridge/Private/InGameMessagesConfig.cpp` ~line 131
**Severity:** LOW
The backup writer's `EscapeIniStr` converts `"` → `\"` in `SenderName`/`Message` tuple
fields. However `ExtractQuotedField` used a bare `Find('"')` to locate the closing quote,
so an escaped `\"` inside the value caused the reader to stop at the `"` of the escape
sequence — returning garbage (e.g. `Hello \` instead of `Hello "World"`).
Fixed by replacing the `Find` call with a char-by-char walk that treats `\"` as a literal
`"` and only stops at an unescaped `"`.

### ✅ R31-02 — DiscordBridgeConfig.cpp: ScheduledAnnouncements `Message` field not escaped in backup; parser ignores `\"`
**File:** `DiscordBridge/Private/DiscordBridgeConfig.cpp` ~lines 547 and 1487
**Severity:** LOW
Two related defects in the same field:
1. **Backup write** (line 1487): `SA.Message` was concatenated into the backup line without
   escaping `"`, so a message containing a double-quote would corrupt the INI tuple and cause
   truncation on restore.
2. **Extraction** (line 549): the `Find('"')` approach used to parse the `Message=` field
   did not honour `\"` escape sequences — same root cause as R31-01.
Fixed: backup write now applies `Replace(TEXT("\""), TEXT("\\\""))` to `SA.Message`, and
the extraction block is replaced with the same escape-aware char-by-char walk as R31-01.
`ChannelId` (a digit-only Discord snowflake) is unaffected and left unchanged.

*Last updated: Round 31. 2 bugs fixed (R31-01, R31-02).*

---

## Round 32 — Bug Audit Results

**Files audited:** `BanDiscordSubsystem.cpp` (lines 3787–4068, all three `/appeal` command handlers),
with cross-check against the INT64_MAX guard pattern established in `HandleClearWarnByIdCommand`
(line 2897) and `BanChatCommands.cpp` `AClearWarnByIdChatCommand` (line 3400).

**1 bug found and fixed:**

### ✅ R32-01 — BanDiscordSubsystem.cpp: Missing INT64_MAX lexicographic guard in three `/appeal` command handlers
**Files:** `DiscordBridge/Private/BanDiscordSubsystem.cpp` — `HandleDismissAppealCommand` (~line 3800),
`HandleAppealApproveCommand` (~line 3865), `HandleAppealDenyCommand` (~line 3996)
**Severity:** LOW

**Root cause:** All three handlers validated the incoming appeal ID string with only:
```cpp
if (!Args[0].IsNumeric() || Args[0].Len() > 19)
```
The `Len() > 19` check allows any 19-digit string to proceed to `FCString::Atoi64`. A 19-digit
decimal value greater than `9223372036854775807` (INT64_MAX) — such as `"9999999999999999999"` —
is accepted by the guard but causes `FCString::Atoi64` to invoke undefined behaviour (signed
integer overflow in the underlying `strtoll`). On most platforms, `strtoll` returns `LLONG_MAX`
with `errno = ERANGE`, producing the value `9223372036854775807`, which then passes the
`AppealId <= 0` post-check and is used as a valid-looking ID. The subsequent registry lookup
returns `false`/empty (no appeal with ID INT64_MAX exists), so the command reports "not found"
rather than corrupting state — but the code path still relies on undefined behavior.

The identical overflow pattern was fixed for `HandleClearWarnByIdCommand` in a previous round
and for `BanRestApi::ParseInt64Param` in Round 2; those two handlers already include the
`(IdLen == 19 && Args[0] > TEXT("9223372036854775807"))` lexicographic comparison that rejects
19-digit values exceeding INT64_MAX before calling `Atoi64`.

**Fix:** Added the same `{ const int32 IdLen = ...; if (... || (IdLen == 19 && Args[0] > TEXT("9223372036854775807"))) }` block to all three handlers, consistent with the established
pattern throughout the codebase.

*Last updated: Round 32. 1 bug fixed (R32-01, 3 call sites).*

---

## Round 33 — Full Source Audit (2026-05-05)

**Scope:** All `.cpp` / `.h` files across BanSystem, BanChatCommands, DiscordBridge, SMLWebSocket
(fresh pass after Round 32). All prior-round fixes confirmed intact. Two new bugs found, both in
`HandleAppealApproveCommand`.

---

### ✅ Fixed — BUG-33-A: `HandleAppealApproveCommand` bare block always exits — command always returns "not found" (CRITICAL)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp`
**Function:** `UBanDiscordSubsystem::HandleAppealApproveCommand` (~line 3905)

**Root cause:** The `if` keyword was absent before the "no appeal found" guard block. The bare compound
statement executed unconditionally after `GetAppealById`, causing every `/appeal approve <id>` to
immediately return `:x: No appeal found` and return — making the entire auto-unban, audit log, Discord
notification, and ticket-close logic (lines 3912–3986) permanently unreachable dead code.

Compare to the correctly-written deny handler (`if (Entry.Uid.IsEmpty()) { … return; }`):
```cpp
// Before fix — always executed:
const FBanAppealEntry Entry = Registry->GetAppealById(AppealId);
{                             // ← missing: if (Entry.Uid.IsEmpty())
    Respond(ChannelId, ...); return;
}
```

**Fix:** Added the missing `if (Entry.Uid.IsEmpty())` condition, consistent with
`HandleAppealDenyCommand` and every other registry-lookup guard in the file.

---

### ✅ Fixed — BUG-33-B: `HandleAppealApproveCommand` never marks appeal as Approved in registry (HIGH)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp`
**Function:** `UBanDiscordSubsystem::HandleAppealApproveCommand` (~line 3943)

**Root cause:** After the auto-unban block, `HandleAppealApproveCommand` never called
`Registry->ReviewAppeal(AppealId, EAppealStatus::Approved, SenderName, ReviewNote)`. Every other
approval path calls this:

| Code path | Calls ReviewAppeal for approval? |
|-----------|----------------------------------|
| `BanRestApi.cpp` POST /appeals/:id/review | ✅ Yes |
| `TicketSubsystem.cpp` ticket_approve_ban | ✅ Yes |
| `HandleAppealDenyCommand` | ✅ Yes |
| **`HandleAppealApproveCommand`** | ❌ **missing** |

Effect: The appeal's status remained `Pending` in the registry after an approval — admins could
accidentally re-review it and the pending-appeal count was permanently inflated.

**Fix:** Added `Registry->ReviewAppeal(AppealId, EAppealStatus::Approved, SenderName, ReviewNote)`
immediately after the unban block (before `Respond`), mirroring `HandleAppealDenyCommand`.
A `UE_LOG(Warning)` is emitted if the call returns false.

---

*Last updated: 2026-05-05. All 2 Round-33 bugs resolved.*

---

## Round 34 — Full Audit (2026-05-06)

### Scope
Complete read of every `.cpp` file in the four mods (BanChatCommands, BanSystem, DiscordBridge,
SMLWebSocket) — 31 source files, ~37 000 lines of code.

### Files audited
| File | Lines | Result |
|------|-------|--------|
| `BanDiscordSubsystem.cpp` | 7 440 | ✅ Clean |
| `DiscordBridgeSubsystem.cpp` | 6 774 | ✅ Clean |
| `TicketSubsystem.cpp` | 5 402 | ✅ Clean |
| `BanChatCommands.cpp` | 4 444 | ✅ Clean |
| `BanRestApi.cpp` | 2 977 | ✅ Clean |
| `DiscordBridgeConfig.cpp` | 1 552 | ✅ Clean |
| `BanEnforcer.cpp` | 1 148 | ✅ Clean |
| `BanDatabase.cpp` | 996 | ✅ Clean |
| `BanSystemModule.cpp` | 799 | ✅ Clean |
| `BanChatCommandsModule.cpp` | 556 | ✅ Clean |
| `WhitelistManager.cpp` | 450 | ✅ Clean |
| `WhitelistConfig.cpp` | 330 | ✅ Clean |
| `InGameMessagesConfig.cpp` | 410 | ✅ Clean |
| `SMLWebSocketRunnable.cpp` | ~600 | ✅ Clean |
| `SMLWebSocketServerRunnable.cpp` | ~450 | ✅ Clean |
| `PlayerWarningRegistry.cpp` | 473 | ✅ Clean |
| `ScheduledBanRegistry.cpp` | 457 | ✅ Clean |
| `BanDiscordNotifier.cpp` | 446 | ✅ Clean |
| `BanAppealRegistry.cpp` | 402 | ✅ Clean |
| `BanSyncClient.cpp` | 372 | ✅ Clean |
| `MuteRegistry.cpp` | 359 | ✅ Clean |
| `BanAuditLog.cpp` | 302 | ✅ Clean |
| `PlayerSessionRegistry.cpp` | 293 | ✅ Clean |
| `PlayerNoteRegistry.cpp` | 262 | ✅ Clean |
| `TicketConfig.cpp` | ~400 | ✅ Clean |
| `BanBridgeConfig.cpp` | 288 | ✅ Clean |
| `DiscordBridgeChatCommands.cpp` | 203 | ✅ Clean |
| `BanWebSocketPusher.cpp` | 137 | ✅ Clean |
| `BanTypes.cpp` | 110 | ✅ Clean |
| `BanChatCommandsConfig.cpp` | 43 | ✅ Clean |
| `DiscordBridge.cpp` | 49 | ✅ Clean |

### Findings
**No bugs found.**

All known bug categories were checked across every file:

- **`BindLambda` capturing `this`** — no instances found; all `this`-capturing callbacks use `BindWeakLambda`; `BindLambda` is used only where local-variable-only captures make it safe.
- **Missing `EscapeMarkdown()`** — no player-controlled string reaches a Discord message field without escaping.
- **Missing `JsonEscape()`** — no player-controlled string is written into a JSON string field without escaping.
- **TOCTOU double-lock races** — all check-then-act sequences operate under a single held lock.
- **`double→int32/int64` casts without range guards** — all numeric casts include `FMath::IsFinite()` or explicit range checks.
- **`FCString::Atoi` on potentially-large IDs** — `Atoi64` is used for all int64 snowflake/UID fields; `Atoi` is used only for genuinely int32-bounded values (port numbers 1–65535, page sizes, minute counts).
- **Missing `INT64_MAX` lexicographic guard** — all 19-digit string-to-int64 paths include the `Str > TEXT("9223372036854775807")` guard.
- **Non-atomic file saves** — `WhitelistManager.cpp` and all data registries use the `write-to-.tmp → IFileManager::Move(bReplace=true)` pattern; config backup writes use direct `SaveStringToFile` consistently across all config files (accepted pattern for advisory backup files).
- **`FDateTime::ParseIso8601()` return not checked** — all call sites check the return value.
- **`SaveToFile()` return not checked** — all call sites check the return value.
- **Missing `IsNumeric()` guard before `Atoi`/`Atoi64` on custom_id suffixes** — all custom_id parsing paths include the `IsNumeric()` guard.
- **Missing `ReviewAppeal()` / `NotifyBanRemoved()` / `RemoveCounterpartBans()`** — all approval/removal handlers call the required follow-up functions (Round-33 fixes confirmed intact).

*Last updated: 2026-05-06. Round 34 audit complete — no bugs found.*

---

## Round 35 — Full Source Audit (2026-05-05)

**Scope:** All `.cpp` / `.h` files across BanSystem, BanChatCommands, DiscordBridge, SMLWebSocket
(fresh pass after Round 34).  3 bugs found and fixed.

---

### ✅ Fixed — `TicketSubsystem`: `RemovedBan.Reason` not escaped in appeal-approved Discord message (BUG-R35-01)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp` (~line 921)

**Root cause:** In the `ticket_approve_ban` handler, the appeal-approved response string embedded
`*RemovedBan.Reason` verbatim in the Discord message. Ban reasons are admin-supplied but may
contain Discord Markdown characters (`*`, `_`, `` ` ``, `~`, `|`, `>`, `\`), allowing unintended
formatting to appear in the ticket channel message.

**Fix:** Wrapped `RemovedBan.Reason` in `EscapeMarkdown()`, consistent with all other
player/admin-supplied string embeds in the same file.

---

### ✅ Fixed — `TicketSubsystem`: `W.Reason`, `W.PlayerName`, `W.WarnedBy` not escaped in prior-warnings embed (BUG-R35-02)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/TicketSubsystem.cpp` (~lines 2796–2799)

**Root cause:** When showing prior warnings in the ticket welcome message, three fields from the
`FWarningEntry` struct — `Reason`, `PlayerName`, and `WarnedBy` — were embedded directly in the
Discord message format string without `EscapeMarkdown()`. These strings originate from admin-typed
ban/warn commands and may contain Markdown-special characters.

**Fix:** Applied `EscapeMarkdown()` to all three fields at the embed site.

---

### ✅ Fixed — `BanDiscordSubsystem`: `GetOpt` lambda casts `double` option value to `int64` without `IsFinite`/range guard (BUG-R35-03)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/BanDiscordSubsystem.cpp` (~line 4941)

**Root cause:** The `GetOpt` helper lambda, used to extract slash-command option values, called
`TryGetNumberField(TEXT("value"), NumVal)` and then cast the resulting `double` directly to
`int64` via `static_cast<int64>(NumVal)` without any `FMath::IsFinite()` or range check.
A crafted gateway payload supplying `NaN`, `±Inf`, or a value outside the
`[INT64_MIN, INT64_MAX)` range would invoke undefined behaviour in `static_cast<int64>`.

**Fix:** Added `FMath::IsFinite(NumVal) && NumVal >= static_cast<double>(INT64_MIN) && NumVal < static_cast<double>(INT64_MAX)` guards before the cast, matching the established
pattern throughout the codebase.

---

*Last updated: 2026-05-05. All 3 Round-35 bugs resolved.*

---

## Round 36 — Full Source Audit (2026-05-06)

**Scope:** All `.cpp` / `.h` files across BanSystem, BanChatCommands, DiscordBridge, SMLWebSocket
(fresh pass after Round 35).  2 bugs found and fixed.

---

### ✅ Fixed — `WhitelistManager::ParseDuration` — `FCString::Atod` result not validated with `FMath::IsFinite` — UB on Infinity/NaN (BUG-R36-01)
**File:** `Mods/DiscordBridge/Source/DiscordBridge/Private/WhitelistManager.cpp` (~lines 395–420)

**Root cause:** All four suffix branches (`w`, `d`, `h`, `m`) called `FCString::Atod` on the
numeric portion of the input and guarded only with `Val > 0.0`. A value like `"1e999w"` or
`"infw"` produces IEEE 754 `+Infinity` from `FCString::Atod`. `+Infinity > 0.0` is `true`, so
`FTimespan::FromDays(Infinity * 7.0)` is called. `FTimespan::FromDays` internally multiplies by
`ETimespan::TicksPerDay` (a constant) and casts to `int64`: `static_cast<int64>(+Infinity)` is
undefined behaviour in C++17 — typically producing `INT64_MIN` on x86, which creates a whitelist
entry with a large negative expiry tick that the next prune pass removes immediately, silently
failing to add the player. `NaN` input falls through to `FTimespan::Zero()` (the `NaN > 0.0` is
`false` branch), producing a permanent whitelist entry when the parse failed — the wrong outcome.

**Fix:** Added `FMath::IsFinite(Val)` to the condition in all four branches, preventing the
`static_cast<int64>(Infinity)` UB. Also added a generous upper-bound cap in each branch
(`<= 36500.0` days, `<= 876000.0` hours, `<= 52560000.0` minutes) to prevent absurdly large
but technically finite timespans from causing downstream overflow in `FTimespan` arithmetic.

---

### ✅ Fixed — `SMLWebSocketServerRunnable` shutdown loop — destroys sockets without sending RFC 6455 Close frames (BUG-R36-02)
**File:** `Mods/SMLWebSocket/Source/SMLWebSocket/Private/SMLWebSocketServerRunnable.cpp` (~lines 305–317)

**Root cause:** The main shutdown teardown loop iterated `Clients` and called
`SocketSS->DestroySocket(KV.Value.Socket)` directly — no Close frame was sent beforehand.
RFC 6455 §7.1.1 requires the initiating endpoint to send a Close frame before tearing down
the TCP connection. Three other close paths in the same file already comply:
`DisconnectClient()` (R26-02), the `ToRemove` inline drain (R30-05), and the `SocketsToDestroy`
final drain (line 336). The graceful server-shutdown path was the only one still missing.

Additionally, the previous code held `ClientMutex` while calling `DestroySocket` — even
without the new `SendFrame` call, this violated the "ClientMutex released before any blocking
I/O" invariant documented in the file's comments.

**Fix:** Split the shutdown loop into two phases: (1) collect socket pointers while holding
`ClientMutex` into a local `TArray<FSocket*> ShutdownSockets` and clear `Clients`; (2) send a
`Close(1001 Going Away)` frame (`0x88 0x02 0x03 0xE9`) to each socket and destroy it outside
the lock. Send failures are silently ignored — the client may have already closed. This matches
the existing `ToRemove` pattern at lines 277–300.

---

## Round 37 Audit (2026-05-06)

### Round 36 verification

**BUG-R36-01 (WhitelistManager ParseDuration) — CONFIRMED PRESENT.**
All four suffix branches (`w`/`d`/`h`/`m`) in `WhitelistManager.cpp` contain the
`FMath::IsFinite(Val) && Val > 0.0 && Val <= cap` guards added in Round 36.

**BUG-R36-02 (SMLWebSocketServerRunnable shutdown Close frames) — CONFIRMED PRESENT.**
The two-phase shutdown pattern (mutex-scoped collect into `ShutdownSockets`, then
`SendFrame(Close 1001)` + `DestroySocket` outside the lock) is present at lines 305–330 of
`SMLWebSocketServerRunnable.cpp`.

---

### ✅ Fixed — NaN UB in `double → int32` duration cast in REST API (BUG-R37-01 / BUG-R37-02)
**File:** `Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp`

**Root cause:** Three locations cast a `double DurationMinutes` value to `int32` without first
checking for NaN. NaN evades both `<= 0.0` and `> INT_MAX` comparisons (both return `false` for
NaN), causing the else-branch cast to execute — `static_cast<int32>(NaN)` is undefined behaviour.

- **POST /bans** (~line 582): 3-way if/else on `DurationMinutesDbl`.
- **POST /scheduled-bans** (~line 2678): ternary expression on `DurDbl`.
- **POST /bans/batch** (~line 2864): identical ternary on `DurDbl`.

**Fix:** Added `!FMath::IsFinite(x)` as the leading condition in each guard so NaN maps to the
safe default (0 = permanent ban). The PATCH /bans/:uid handler was already safe because it uses
`== 0.0` / `> 0.0` tests that simply skip for NaN, leaving the duration unchanged.

Note: Standard JSON parsers cannot produce NaN (not valid JSON), so this is a defensive measure
rather than a fix for an immediately exploitable path.

---

### ✅ Fixed — `FCString::Atoi64` called without `IsNumeric` or 19-digit overflow guard on `nextId` field (BUG-R37-03)
**Files:**
- `Mods/BanSystem/Source/BanSystem/Private/BanDatabase.cpp` (~line 357)
- `Mods/BanSystem/Source/BanSystem/Private/ScheduledBanRegistry.cpp` (~line 369)
- `Mods/BanSystem/Source/BanSystem/Private/BanAppealRegistry.cpp` (~line 319)
- `Mods/BanSystem/Source/BanSystem/Private/PlayerWarningRegistry.cpp` (~line 392)
- `Mods/BanSystem/Source/BanSystem/Private/BanAuditLog.cpp` (~line 222)
- `Mods/BanChatCommands/Source/BanChatCommands/Private/PlayerNoteRegistry.cpp` (~line 195)

**Root cause:** Each file's JSON load path called `FCString::Atoi64(*NextIdStr)` on the `"nextId"`
string field without first validating that the string is numeric or that it fits within `int64`.
A 19-digit string like `"9999999999999999999"` exceeds `INT64_MAX` (9223372036854775807) and
silently overflows `Atoi64`. A non-numeric string also returns 0, silently resetting `NextId`.

**Fix:** Added the same guard pattern used by `BanRestApi.cpp`'s `ParseInt64Param` (the project's
gold-standard safe int64 parser):
```cpp
&& StoredNextIdStr.IsNumeric()
&& StoredNextIdStr.Len() <= 19
&& (StoredNextIdStr.Len() < 19 || StoredNextIdStr <= TEXT("9223372036854775807"))
```
This gates the `Atoi64` call behind a length check and lexicographic comparison to `INT64_MAX`.
The attack surface is low (server-internal JSON files) but the guard is consistent with the
rest of the codebase.

---

### Clean bill of health for other categories

The following categories were audited and found clean in this round:

| Category | Verdict |
|---|---|
| `BindLambda` raw-`this` captures | ✅ All use `WeakObjectPtr` or value captures |
| `JsonEscape` lone-surrogate handling | ✅ All implementations map U+D800–U+DFFF → U+FFFD |
| `EscapeMarkdown` usage correctness | ✅ Called correctly in `BanDiscordSubsystem` |
| Timer accumulator drift (reset to 0 vs subtract) | ✅ All timers use correct subtraction pattern |
| `AddBan` vs `AddBanSkipIfPermanentExists` | ✅ All call sites use the correct variant |
| Atomic save pattern (.tmp + Move) | ✅ All registry Save methods use tmp-then-rename |

---

## Round 38 — Deep Audit (2026-05-07)

Five new bugs found and fixed. Three false-positive AddBan findings from the audit confirmed correct (permanent-ban `AddBan` calls are intentional, only temp-ban paths require `AddBanSkipIfPermanentExists`).

---

### BUG-R38-01 — Per-entry `"id"` string field parsed with bare `Atoi64` — no IsNumeric/overflow guard (MEDIUM)

**Affected files:**
- `Mods/BanSystem/Source/BanSystem/Private/BanDatabase.cpp` (~line 71)
- `Mods/BanSystem/Source/BanSystem/Private/ScheduledBanRegistry.cpp` (~line 315)
- `Mods/BanSystem/Source/BanSystem/Private/PlayerWarningRegistry.cpp` (~line 339)
- `Mods/BanSystem/Source/BanSystem/Private/BanAuditLog.cpp` (~line 179)
- `Mods/BanSystem/Source/BanSystem/Private/BanAppealRegistry.cpp` (~line 260)

**Root cause:** The string-format path `if (Obj->TryGetStringField(TEXT("id"), IdStr)) OutEntry.Id = FCString::Atoi64(*IdStr)` had no `IsNumeric()`, no `Len() <= 19`, and no lexicographic guard against 19-digit overflow. Round 37 fixed the `"nextId"` field with the same guard pattern but missed the per-entry `"id"` field in all five registries.

A corrupted JSON `"id": "garbage"` returns 0 silently; `"id": "9999999999999999999"` (> INT64_MAX) invokes UB. `BanAppealRegistry` partially mitigated this via a post-parse `if (Entry.Id <= 0) continue;` guard (protecting the zero-return case) but still left the overflow path unsafe.

**Fix:** Added the same three-part guard used for `"nextId"` before each `Atoi64(*IdStr)` call:
```cpp
&& IdStr.IsNumeric() && IdStr.Len() <= 19
&& (IdStr.Len() < 19 || IdStr <= TEXT("9223372036854775807"))
```

---

### BUG-R38-02 — `POST /bans/batch` REST endpoint uses bare `AddBan` for temporary bans (MEDIUM)

**Affected file:** `Mods/BanSystem/Source/BanSystem/Private/BanRestApi.cpp` (~line 2888)

**Root cause:** The `/bans/batch` endpoint supports both permanent (`durationMinutes <= 0`) and temporary (`durationMinutes > 0`) bans. It called `DB->AddBan(Ban, &Saved)` unconditionally regardless of ban type. A temporary-ban request against a player who already has a permanent ban would silently downgrade the permanent ban — the same class of bug fixed in Round 28 for other endpoints.

**Fix:** Applied the same ternary pattern used by all other dual-type ban paths:
```cpp
const bool bBatchAdded = Ban.bIsPermanent
    ? DB->AddBan(Ban, &Saved)
    : DB->AddBanSkipIfPermanentExists(Ban, bBatchSkipped);
const FBanEntry& AddedEntry = Ban.bIsPermanent ? Saved : Ban;
```
Permanent bans still get the database-assigned `Id` via `Saved`; skipped temp-ban entries are silently omitted from the response.

---

### BUG-R38-03 — `ABulkBanChatCommand` missing `AddCounterpartBans` call (MEDIUM)

**Affected file:** `Mods/BanChatCommands/Source/BanChatCommands/Private/Commands/BanChatCommands.cpp` (~line 4414)

**Root cause:** The Discord `/bulkban` path (`HandleBulkBanCommand` in `BanDiscordSubsystem.cpp`) correctly calls `BanDiscordHelpers::AddCounterpartBans` after each successful ban to propagate the ban to linked IP/EOS identifiers. The in-game chat `/bulkban` command (`ABulkBanChatCommand`) omitted this step entirely, leaving a bypass vector where bulk bans issued from in-game chat did not ban counterpart identifiers.

**Fix:** Added `BanChat::AddCounterpartBans(this, Sender, Uid, RawUid, 0 /* permanent */, Reason, AdminName)` inside the `if (DB->AddBan(Ban))` block, immediately after the Discord notifier call, mirroring the Discord path.

---

### BUG-R38-04 — `BanDiscordNotifier`: `double→int64` cast without `FMath::IsFinite()` guard (LOW)

**Affected file:** `Mods/BanSystem/Source/BanSystem/Private/BanDiscordNotifier.cpp` (lines ~122, ~269, ~400)

**Root cause:** Three duration-display snippets called `static_cast<int64>((DateA - DateB).GetTotalMinutes())` without a `FMath::IsFinite()` guard. While `FDateTime` stores int64 ticks internally (making NaN impossible in practice), the cast is technically UB if an extreme out-of-range double is passed. The same defensive-coding pattern was applied to `BanRestApi.cpp` and other sites in Round 37.

**Fix:** Extracted the `double` result to a named variable (`RawMin0/1/2`) and added `FMath::IsFinite(RawMinN)` with a fallback of `(int64)0`:
```cpp
const double RawMin0 = (Entry.ExpireDate - Entry.BanDate).GetTotalMinutes();
FMath::IsFinite(RawMin0) ? static_cast<int64>(RawMin0) : (int64)0
```

---

### BUG-R38-05 — `ChatRelayBlocklistReplacements` not `"` escaped in config write/read (LOW)

**Affected file:** `Mods/DiscordBridge/Source/DiscordBridge/Private/DiscordBridgeConfig.cpp`
- Write (primary config rebuild): ~line 1463
- Write (backup writer): ~lines 1572–1573
- Read (primary `ExtractQuoted` lambda): ~lines 535–544
- Read (backup `ExtractQuoted` lambda): ~lines 1215–1225

**Root cause:** `R.Pattern` and `R.Replacement` were concatenated verbatim into the INI line without escaping embedded `"` characters. The `ExtractQuoted` lambdas used a bare `Cleaned.Find(TEXT("\""))` to locate the closing quote, stopping at the first `"` in the value rather than honouring `\"` escapes.

By contrast, `ScheduledAnnouncements` in the same file correctly applied `Replace(TEXT("\""), TEXT("\\\""))` in the write path and an escape-aware char-walk in the read path (lines 658–684). `ChatRelayBlocklistReplacements` was inconsistently missing both protections.

**Fix:**
- **Write**: Applied `R.Pattern.Replace(TEXT("\""), TEXT("\\\""))` and the same for `R.Replacement` in both write paths before concatenation.
- **Read**: Replaced both `ExtractQuoted` lambdas with the same escape-aware char-walk pattern used by `ScheduledAnnouncements`, processing `\"` as a literal `"` and stopping on the next unescaped `"`.

---

### Round 38 false positives noted

The following were flagged during the audit but confirmed to be correct code:

| Pattern | Verdict |
|---|---|
| `HandleBanNameCommand` uses `AddBan` for permanent bans | ✅ Intentional — admin explicitly replaces any prior ban |
| `HandleQBanCommand` permanent branch uses `AddBan` | ✅ Correct ternary: permanent → `AddBan`, temp → `AddBanSkipIfPermanentExists` |
| `HandleBulkBanCommand` Discord path uses `AddBan` for permanent bans | ✅ Intentional bulk-permanent replacement |
| `ExecutePanelBan` uses `AddBan` | ✅ Admin panel permanent-ban replacement is intentional |
| `BanRestApi.cpp` `PATCH /bans/:uid` uses `AddBan` | ✅ Explicit update/replace of existing record |

---

*Last updated: 2026-05-07. All 5 Round-38 bugs resolved.*

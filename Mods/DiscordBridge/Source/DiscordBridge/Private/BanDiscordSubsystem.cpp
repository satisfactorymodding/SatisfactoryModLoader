// Copyright Yamahasxviper. All Rights Reserved.

#include "BanDiscordSubsystem.h"

// BanSystem public API
#include "BanDatabase.h"
#include "BanEnforcer.h"
#include "BanTypes.h"
#include "BanSystemConfig.h"
#include "PlayerSessionRegistry.h"
#include "PlayerWarningRegistry.h"
#include "BanDiscordNotifier.h"
#include "BanAppealRegistry.h"
#include "BanAuditLog.h"
#include "ScheduledBanRegistry.h"

// BanChatCommands public API
#include "MuteRegistry.h"
#include "Commands/BanChatCommands.h"
#include "BanChatCommandsConfig.h"

// DiscordBridge config (ServerName for panel embed)
#include "DiscordBridgeConfig.h"
#include "TicketSubsystem.h"
#include "FGChatManager.h"

#include "Misc/DefaultValueHelper.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "ModLoading/ModLoadingLibrary.h"

// ─────────────────────────────────────────────────────────────────────────────
// Internal namespace helpers
// ─────────────────────────────────────────────────────────────────────────────

namespace BanDiscordHelpers
{
	/** Retrieve the UBanDatabase subsystem via the GameInstance. */
	static UBanDatabase* GetDB(const UBanDiscordSubsystem* Self)
	{
		UGameInstance* GI = Self ? Self->GetGameInstance() : nullptr;
		return GI ? GI->GetSubsystem<UBanDatabase>() : nullptr;
	}

	/** Retrieve the UPlayerSessionRegistry subsystem via the GameInstance. */
	static UPlayerSessionRegistry* GetRegistry(const UBanDiscordSubsystem* Self)
	{
		UGameInstance* GI = Self ? Self->GetGameInstance() : nullptr;
		return GI ? GI->GetSubsystem<UPlayerSessionRegistry>() : nullptr;
	}

	/** Format ban expiry for display in Discord messages. */
	static FString FormatExpiry(const FBanEntry& Entry)
	{
		if (Entry.bIsPermanent)
			return TEXT("never (permanent)");
		return Entry.ExpireDate.ToString(TEXT("%Y-%m-%d %H:%M:%S")) + TEXT(" UTC");
	}

	/** Join Arguments[StartIdx..] into a single space-separated string. */
	static FString JoinArgs(const TArray<FString>& Args, int32 StartIdx)
	{
		FString Result;
		for (int32 i = StartIdx; i < Args.Num(); ++i)
		{
			if (i > StartIdx) Result += TEXT(" ");
			Result += Args[i];
		}
		return Result;
	}

	/** Truncate a string to MaxLen chars and append "..." when truncated. */
	static FString Truncate(const FString& Str, int32 MaxLen)
	{
		if (Str.Len() <= MaxLen) return Str;
		return Str.Left(MaxLen - 3) + TEXT("...");
	}

	/** Extract compound UID ("EOS:<puid>") for a connected player controller. */
	static FString GetControllerUid(APlayerController* PC)
	{
		if (!PC || !PC->PlayerState)
			return FString();

		const FUniqueNetIdRepl& NetId = PC->PlayerState->GetUniqueId();
		if (NetId.IsValid() && NetId.GetType() != FName(TEXT("NONE")))
			return UBanDatabase::MakeUid(TEXT("EOS"), NetId.ToString().ToLower());

		const FString EosPuid = UBanEnforcer::ExtractEosPuidFromConnectionUrl(PC);
		if (!EosPuid.IsEmpty())
			return UBanDatabase::MakeUid(TEXT("EOS"), EosPuid.ToLower());

		return FString();
	}

	/**
	 * Escape characters that have special meaning in Discord markdown so that
	 * player names with *, _, `, ~, |, > or \ are rendered literally.
	 */
	static FString EscapeMarkdown(const FString& Text)
	{
		FString Out;
		Out.Reserve(Text.Len() + 8);
		for (TCHAR C : Text)
		{
			switch (C)
			{
			case TEXT('*'): case TEXT('_'): case TEXT('`'): case TEXT('~'):
			case TEXT('|'): case TEXT('>'): case TEXT('\\'): case TEXT('['):
			case TEXT(']'): case TEXT('#'):
				Out += TEXT('\\');
				break;
			default:
				break;
			}
			Out += C;
		}
		return Out;
	}

	/**
	 * Replace any triple-backtick sequence (```) in a string with a single
	 * backtick followed by a zero-width space and two more backticks so that
	 * player-controlled data inside a Discord ```…``` code fence cannot
	 * escape the fence and inject arbitrary markdown.
	 */
	static FString SanitizeForCodeBlock(const FString& S)
	{
		FString Out = S;
		Out.ReplaceInline(TEXT("```"), TEXT("`\u200B``"));
		return Out;
	}

	/**
	 * Format a duration in minutes as a compact human-readable string.
	 * Examples: 30 → "30m", 90 → "1h 30m", 1500 → "1d 1h".
	 * Returns "permanently" for 0 or negative values.
	 */
	static FString FormatDuration(int32 TotalMinutes)
	{
		if (TotalMinutes <= 0)
			return TEXT("permanently");

		const int32 Weeks = TotalMinutes / (60 * 24 * 7);
		const int32 Days  = (TotalMinutes % (60 * 24 * 7)) / (60 * 24);
		const int32 Hours = (TotalMinutes % (60 * 24)) / 60;
		const int32 Mins  = TotalMinutes % 60;

		FString R;
		if (Weeks > 0) { R += FString::Printf(TEXT("%dw"), Weeks); }
		if (Days  > 0) { if (!R.IsEmpty()) R += TEXT(" "); R += FString::Printf(TEXT("%dd"), Days);  }
		if (Hours > 0) { if (!R.IsEmpty()) R += TEXT(" "); R += FString::Printf(TEXT("%dh"), Hours); }
		if (Mins  > 0) { if (!R.IsEmpty()) R += TEXT(" "); R += FString::Printf(TEXT("%dm"), Mins);  }
		return R;
	}

	/**
	 * Look up the player's session record and return a string with EOS PUID
	 * and IP address suitable for appending to a ban confirmation message.
	 * Returns an empty string when no session record is found.
	 */
	static FString FormatPlayerLookup(const UBanDiscordSubsystem* Self,
	                                  const FString& Uid)
	{
		UPlayerSessionRegistry* Registry = GetRegistry(Self);
		if (!Registry) return FString();

		FPlayerSessionRecord Record;
		if (!Registry->FindByUid(Uid, Record)) return FString();

		FString Info;
		// Extract the raw EOS PUID from the compound UID.
		FString Platform, RawPuid;
		UBanDatabase::ParseUid(Record.Uid, Platform, RawPuid);
		if (!RawPuid.IsEmpty())
			Info += FString::Printf(TEXT("\nEOS PUID: `%s`"), *RawPuid);

		if (!Record.IpAddress.IsEmpty())
			Info += FString::Printf(TEXT("\nIP: `%s`"), *Record.IpAddress);

		if (!Record.LastSeen.IsEmpty())
			Info += FString::Printf(TEXT("\nLast seen: %s"), *Record.LastSeen);

		return Info;
	}

	// Number of bans shown per /ban list page.
	static constexpr int32 BanListPageSize = 10;

	/**
	 * Build a separator string of N "─" characters.
	 * NOTE: FString(TEXT("─"), N) only sets extra capacity, not repetitions,
	 * so we build the line explicitly.
	 */
	static FString SepLine(int32 N)
	{
		FString Out;
		Out.Reserve(N + 1);
		for (int32 i = 0; i < N; ++i)
			Out += TEXT("─");
		return Out;
	}

	/**
	 * After a primary ban for PrimaryUid has been committed, look up the
	 * player's other identifiers in the session registry and create matching
	 * ban records:
	 *  - EOS UID → also bans the IP address recorded for that UID.
	 *  - IP UID  → also bans every EOS UID that has connected from that IP.
	 * All newly created records are cross-linked via UBanDatabase::LinkBans().
	 * Returns a list of additionally created UIDs (for confirmation messages).
	 */
	static TArray<FString> AddCounterpartBans(const UBanDiscordSubsystem* Self,
	                                           UBanDatabase* DB,
	                                           const FString& PrimaryUid,
	                                           const FString& DisplayName,
	                                           const FString& Reason,
	                                           const FString& BannedBy,
	                                           bool bIsPermanent,
	                                           FDateTime ExpireDate)
	{
		TArray<FString> Added;
		if (!DB) return Added;

		UPlayerSessionRegistry* Registry = GetRegistry(Self);
		if (!Registry) return Added;

		FString Platform, RawId;
		UBanDatabase::ParseUid(PrimaryUid, Platform, RawId);

		// Capture the timestamp once so every counterpart ban shares the same BanDate.
		const FDateTime CounterpartNow = FDateTime::UtcNow();
		auto MakeEntry = [&](const FString& Uid, const FString& Plat,
		                     const FString& RawUid, const FString& Name) -> FBanEntry
		{
			FBanEntry E;
			E.Uid        = Uid;
			E.Platform   = Plat;
			E.PlayerUID  = RawUid;
			E.PlayerName = Name;
			E.Reason     = Reason;
			E.BannedBy   = BannedBy;
			E.BanDate    = CounterpartNow;
			E.bIsPermanent = bIsPermanent;
			E.ExpireDate   = ExpireDate;
			E.LinkedUids.Add(PrimaryUid);
			return E;
		};

		if (Platform == TEXT("EOS"))
		{
			FPlayerSessionRecord Rec;
			if (Registry->FindByUid(PrimaryUid, Rec) && !Rec.IpAddress.IsEmpty())
			{
				const FString IpUid = UBanDatabase::MakeUid(TEXT("IP"), Rec.IpAddress);
				FBanEntry IpEntry = MakeEntry(IpUid, TEXT("IP"), Rec.IpAddress, DisplayName);
				bool bIpSkipped = false;
				if (DB->AddBanSkipIfPermanentExists(IpEntry, bIpSkipped))
				{
					DB->LinkBans(PrimaryUid, IpUid);
					Added.Add(IpUid);
				}
				else if (bIpSkipped)
				{
					// Existing permanent IP ban takes precedence; still ensure the cross-link.
					DB->LinkBans(PrimaryUid, IpUid);
				}
			}
		}
		else if (Platform == TEXT("IP"))
		{
			TArray<FPlayerSessionRecord> Records = Registry->FindByIp(RawId);
			for (const FPlayerSessionRecord& Rec : Records)
			{
				if (Rec.Uid.IsEmpty()) continue;
				FString RecPlat, RecRawId;
				UBanDatabase::ParseUid(Rec.Uid, RecPlat, RecRawId);
				const FString RecName = Rec.DisplayName.IsEmpty() ? DisplayName : Rec.DisplayName;
				FBanEntry EosEntry = MakeEntry(Rec.Uid, RecPlat, RecRawId, RecName);
				bool bEosSkipped = false;
				if (DB->AddBanSkipIfPermanentExists(EosEntry, bEosSkipped))
				{
					DB->LinkBans(PrimaryUid, Rec.Uid);
					Added.Add(Rec.Uid);
				}
				else if (bEosSkipped)
				{
					// Existing permanent EOS ban takes precedence; still ensure the cross-link.
					DB->LinkBans(PrimaryUid, Rec.Uid);
				}
			}
		}
		return Added;
	}

	/**
	 * After removing the ban for PrimaryUid, remove all linked bans so no
	 * counterpart (IP or EOS) ban is left behind.
	 * Uses the LinkedUids collected from the ban entry before deletion and also
	 * checks the session registry for any unlinked counterparts.
	 * Returns the number of additional records removed.
	 */
	static int32 RemoveCounterpartBans(const UBanDiscordSubsystem* Self,
	                                    UBanDatabase* DB,
	                                    const FString& PrimaryUid,
	                                    const TArray<FString>& LinkedUids)
	{
		if (!DB) return 0;
		int32 Removed = 0;

		for (const FString& LinkedUid : LinkedUids)
		{
			if (DB->RemoveBanByUid(LinkedUid))
				++Removed;
		}

		UPlayerSessionRegistry* Registry = GetRegistry(Self);
		if (!Registry) return Removed;

		FString Platform, RawId;
		UBanDatabase::ParseUid(PrimaryUid, Platform, RawId);

		if (Platform == TEXT("EOS"))
		{
			FPlayerSessionRecord Rec;
			if (Registry->FindByUid(PrimaryUid, Rec) && !Rec.IpAddress.IsEmpty())
			{
				const FString IpUid = UBanDatabase::MakeUid(TEXT("IP"), Rec.IpAddress);
				if (!LinkedUids.Contains(IpUid) && DB->RemoveBanByUid(IpUid))
					++Removed;
			}
		}
		else if (Platform == TEXT("IP"))
		{
			TArray<FPlayerSessionRecord> Records = Registry->FindByIp(RawId);
			for (const FPlayerSessionRecord& Rec : Records)
			{
				if (Rec.Uid.IsEmpty()) continue;
				if (!LinkedUids.Contains(Rec.Uid) && DB->RemoveBanByUid(Rec.Uid))
					++Removed;
			}
		}
		return Removed;
	}

	/** Escape a string for embedding inside a JSON string literal.
	 *  Handles backslash, double-quote, newlines, tabs, carriage returns,
	 *  other control characters (U+0000–U+001F), and lone UTF-16 surrogates
	 *  (U+D800–U+DFFF) so the output is always well-formed JSON. */
	static FString JsonEscape(const FString& S)
	{
		FString Out;
		Out.Reserve(S.Len() + 8);
		for (int32 i = 0; i < S.Len(); ++i)
		{
			const TCHAR C = S[i];
			switch (C)
			{
			case TEXT('"'):  Out += TEXT("\\\""); break;
			case TEXT('\\'): Out += TEXT("\\\\"); break;
			case TEXT('\n'): Out += TEXT("\\n");  break;
			case TEXT('\r'): Out += TEXT("\\r");  break;
			case TEXT('\t'): Out += TEXT("\\t");  break;
			default:
				// RFC 8259 §7: control characters U+0000–U+001F must be escaped.
				if (C < 0x20)
					Out += FString::Printf(TEXT("\\u%04x"), static_cast<uint32>(C));
				// RFC 8259 §7: lone surrogate code-points U+D800–U+DFFF produce
				// invalid JSON.  Replace with U+FFFD (replacement character) so the
				// output is always valid JSON regardless of the content.
				else if (C >= 0xD800 && C <= 0xDFFF)
					Out += TEXT("\uFFFD");
				else
					Out += C;
				break;
			}
		}
		return Out;
	}
}

// ─────────────────────────────────────────────────────────────────────────────
// USubsystem lifetime
// ─────────────────────────────────────────────────────────────────────────────

bool UBanDiscordSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!Super::ShouldCreateSubsystem(Outer)) return false;
	return IsRunningDedicatedServer();
}

void UBanDiscordSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	FBanBridgeConfig::RestoreDefaultConfigIfNeeded();
	Config = FBanBridgeConfig::Load();

	// Cache the FDiscordBridgeConfig fields we reference at runtime so we
	// never hit the disk inside BuildPanelData() or PostModerationLog().
	{
		const FDiscordBridgeConfig DiscordCfg = FDiscordBridgeConfig::LoadOrCreate();
		CachedDiscordServerName  = DiscordCfg.ServerName;
		CachedBanEventsChannelId = DiscordCfg.BanEventsChannelId;
	}

	PostLoginHandle = FGameModeEvents::GameModePostLoginEvent.AddUObject(
		this, &UBanDiscordSubsystem::OnPostLoginModerationReminder);

	// Mirror non-bot bans to the bot's moderation log channel.
	// Bot-command bans (HandleBanCommand / ExecutePanelBan) already post themselves,
	// so the lambda skips while a Discord interaction is being processed.
	{
		TWeakObjectPtr<UBanDiscordSubsystem> WeakThis(this);
		BanAddedHandle = UBanDatabase::OnBanAdded.AddLambda(
			[WeakThis](const FBanEntry& Entry)
			{
				UBanDiscordSubsystem* Self = WeakThis.Get();
				if (!Self || !Self->CachedProvider) return;
				// Skip when a bot interaction is in flight — the command handler
				// already posts to the moderation log for that case.
				if (!Self->PendingInteractionToken.IsEmpty()) return;
				// Skip IP counterpart bans — they are implied by the primary EOS ban
				// and posting them would produce duplicate moderation-log entries.
				if (Entry.Platform == TEXT("IP")) return;

				// Use Uid as fallback when PlayerName is empty (e.g. pre-emptive bans
				// placed before the player has ever connected to the server).
				const FString DisplayName = Entry.PlayerName.IsEmpty() ? Entry.Uid : Entry.PlayerName;
				const FString DurationStr = Entry.bIsPermanent
					? TEXT("permanent")
					: BanDiscordHelpers::FormatDuration([&]() -> int32 {
					    const double TotalMins = (Entry.ExpireDate - Entry.BanDate).GetTotalMinutes();
					    if (!FMath::IsFinite(TotalMins) || TotalMins < 0.0) return 0;
					    return static_cast<int32>(FMath::Min(TotalMins, static_cast<double>(INT32_MAX)));
					}());
				const FString Msg = FString::Printf(
					TEXT("🔨 **%s** (`%s`) banned.\nReason: %s\nBy: %s | Duration: %s"),
					*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Entry.Uid,
					*BanDiscordHelpers::EscapeMarkdown(Entry.Reason),
					*BanDiscordHelpers::EscapeMarkdown(Entry.BannedBy), *DurationStr);
				Self->PostModerationLog(Msg);
			});
	}

	// Mirror ban record edits (reason changes, duration extensions, bannedBy updates)
	// that originate from in-game chat commands or the REST API to the moderation log.
	// Discord slash commands that call UpdateBan() set PendingInteractionToken and
	// post their own specific message, so this handler skips while a bot interaction
	// is in flight to avoid a duplicate generic "ban record updated" post.
	// IP counterpart bans are skipped (matching BanAddedHandle) to avoid duplicate posts.
	{
		TWeakObjectPtr<UBanDiscordSubsystem> WeakThis(this);
		BanUpdatedHandle = UBanDatabase::OnBanUpdated.AddLambda(
			[WeakThis](const FBanEntry& Entry)
			{
				UBanDiscordSubsystem* Self = WeakThis.Get();
				if (!Self || !Self->CachedProvider) return;
				// Skip when a bot interaction is in flight — the command handler
				// already posts a specific "reason updated" or "ban extended" message.
				if (!Self->PendingInteractionToken.IsEmpty()) return;
				// Skip IP counterpart bans — they are implied by the primary EOS edit.
				if (Entry.Platform == TEXT("IP")) return;

				const FString DurationStr = Entry.bIsPermanent
					? TEXT("permanent")
					: BanDiscordHelpers::FormatDuration([&]() -> int32 {
					    const double TotalMins = (Entry.ExpireDate - Entry.BanDate).GetTotalMinutes();
					    if (!FMath::IsFinite(TotalMins) || TotalMins < 0.0) return 0;
					    return static_cast<int32>(FMath::Min(TotalMins, static_cast<double>(INT32_MAX)));
					}());
				const FString Msg = FString::Printf(
					TEXT("✏️ **%s** (`%s`) ban record updated.\nReason: %s\nBy: %s | Duration: %s"),
					*BanDiscordHelpers::EscapeMarkdown(Entry.PlayerName), *Entry.Uid,
					*BanDiscordHelpers::EscapeMarkdown(Entry.Reason),
					*BanDiscordHelpers::EscapeMarkdown(Entry.BannedBy), *DurationStr);
				Self->PostModerationLog(Msg);
			});
	}

	// Mirror non-bot unbans (REST API / BanEnforcer expiry) to the moderation log.
	// The lambda is guarded by PendingInteractionToken so Discord slash unban
	// commands (which post their own message via Respond) don't double-post.
	// IP counterpart bans are skipped (matching BanAddedHandle) to prevent two
	// "unbanned" posts whenever an EOS+IP ban pair is removed together.
	{
		TWeakObjectPtr<UBanDiscordSubsystem> WeakThis(this);
		BanRemovedHandle = UBanDatabase::OnBanRemoved.AddLambda(
			[WeakThis](const FString& Uid, const FString& PlayerName)
			{
				UBanDiscordSubsystem* Self = WeakThis.Get();
				if (!Self || !Self->CachedProvider) return;
				if (!Self->PendingInteractionToken.IsEmpty()) return;
				// Skip IP counterpart bans — they are implied by the primary EOS
				// unban and posting them would produce duplicate moderation-log entries.
				// Parse the UID to get the Platform so the check is consistent with
				// BanAddedHandle and BanUpdatedHandle (which use Entry.Platform).
				{
					FString Platform, RawId;
					UBanDatabase::ParseUid(Uid, Platform, RawId);
					if (Platform == TEXT("IP")) return;
				}

				const FString DisplayName = PlayerName.IsEmpty() ? Uid : PlayerName;
				const FString Msg = FString::Printf(
					TEXT("✅ **%s** (`%s`) unbanned."), *BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid);
				Self->PostModerationLog(Msg);
			});
	}

	// Route in-game /warn and chat-filter auto-warns to per-player mod threads.
	// The delegate is a static member of UPlayerWarningRegistry so no subsystem
	// pointer is needed for subscription.  The PendingInteractionToken guard
	// prevents duplicate thread posts when a Discord slash /warn is in flight
	// (that handler already calls PostToPlayerModerationThread directly).
	{
		TWeakObjectPtr<UBanDiscordSubsystem> WeakThis(this);
		WarnAddedHandle = UPlayerWarningRegistry::OnWarningAdded.AddLambda(
			[WeakThis](const FWarningEntry& Entry)
			{
				UBanDiscordSubsystem* Self = WeakThis.Get();
				if (!Self || !Self->CachedProvider) return;
				if (!Self->PendingInteractionToken.IsEmpty()) return;
				if (Self->Config.ModerationLogChannelId.IsEmpty()) return;
				if (Entry.Uid.IsEmpty()) return;

				const FString WarnMsg = FString::Printf(
					TEXT("⚠️ **%s** (`%s`) warned.\nReason: %s\nBy: %s"),
					*BanDiscordHelpers::EscapeMarkdown(Entry.PlayerName), *Entry.Uid,
					*BanDiscordHelpers::EscapeMarkdown(Entry.Reason),
					*BanDiscordHelpers::EscapeMarkdown(Entry.WarnedBy));
				Self->PostToPlayerModerationThread(Entry.PlayerName, Entry.Uid, WarnMsg);
			});
	}

	// Route in-game /mute and /unmute (BanChatCommands) to per-player mod threads.
	// OnPlayerMuted / OnPlayerUnmuted are instance delegates on UMuteRegistry, so
	// we get the subsystem pointer first.  If BanChatCommands is not installed the
	// subsystem will be null and the subscription is simply skipped.
	{
		TWeakObjectPtr<UBanDiscordSubsystem> WeakThis(this);
		if (UGameInstance* GI = GetGameInstance())
		{
			if (UMuteRegistry* MuteReg = GI->GetSubsystem<UMuteRegistry>())
			{
				MutedEventHandle = MuteReg->OnPlayerMuted.AddLambda(
					[WeakThis](const FMuteEntry& Entry, bool bIsTimed)
					{
						UBanDiscordSubsystem* Self = WeakThis.Get();
						if (!Self || !Self->CachedProvider) return;
						if (!Self->PendingInteractionToken.IsEmpty()) return;
						if (Self->Config.ModerationLogChannelId.IsEmpty()) return;

						const FString DurStr = bIsTimed
							? FString::Printf(TEXT(" for **%s**"),
								  *BanDiscordHelpers::FormatDuration(
								      static_cast<int32>(FMath::Min(
								          FMath::Max((int64)0,
								              static_cast<int64>((Entry.ExpireDate - Entry.MuteDate).GetTotalMinutes())),
								          static_cast<int64>(INT32_MAX)))))
							: TEXT(" **indefinitely**");
						const FString MuteMsg = FString::Printf(
							TEXT("🔇 Muted **%s** (`%s`)%s.\nReason: %s\nBy: %s"),
							*BanDiscordHelpers::EscapeMarkdown(Entry.PlayerName), *Entry.Uid, *DurStr,
							*BanDiscordHelpers::EscapeMarkdown(Entry.Reason),
							*BanDiscordHelpers::EscapeMarkdown(Entry.MutedBy));
						Self->PostToPlayerModerationThread(Entry.PlayerName, Entry.Uid, MuteMsg);
					});

				UnmutedEventHandle = MuteReg->OnPlayerUnmuted.AddLambda(
					[WeakThis](const FString& Uid)
					{
						UBanDiscordSubsystem* Self = WeakThis.Get();
						if (!Self || !Self->CachedProvider) return;
						if (!Self->PendingInteractionToken.IsEmpty()) return;
						if (Self->Config.ModerationLogChannelId.IsEmpty()) return;

						// Attempt to resolve a display name for the thread lookup.
						FString PlayerName = Uid;
						if (UGameInstance* LiveGI = Self->GetGameInstance())
						{
							if (UPlayerSessionRegistry* Sessions =
									LiveGI->GetSubsystem<UPlayerSessionRegistry>())
							{
								FPlayerSessionRecord Record;
								if (Sessions->FindByUid(Uid, Record) && !Record.DisplayName.IsEmpty())
									PlayerName = Record.DisplayName;
							}
						}
						const FString UnmuteMsg = FString::Printf(
							TEXT("🔊 Unmuted **%s** (`%s`)."), *BanDiscordHelpers::EscapeMarkdown(PlayerName), *Uid);
						Self->PostToPlayerModerationThread(PlayerName, Uid, UnmuteMsg);
					});

				// Store a weak reference so Deinitialize() can remove the handles even
				// when GetGameInstance() returns null during world teardown ordering.
				BoundMuteRegistry = MuteReg;
			}
		}
	}

	// Route in-game /kick (BanChatCommands) to per-player mod threads.
	// The OnPlayerKickedLogged delegate is only broadcast when NotifyPlayerKicked()
	// receives a non-empty Uid; Discord slash-kick handlers omit the Uid so they
	// never trigger this subscriber — no PendingInteractionToken guard needed.
	{
		TWeakObjectPtr<UBanDiscordSubsystem> WeakThis(this);
		KickLoggedHandle = FBanDiscordNotifier::OnPlayerKickedLogged.AddLambda(
			[WeakThis](const FString& Uid, const FString& PlayerName,
			           const FString& Reason, const FString& KickedBy)
			{
				UBanDiscordSubsystem* Self = WeakThis.Get();
				if (!Self || !Self->CachedProvider) return;
				if (Self->Config.ModerationLogChannelId.IsEmpty()) return;

				const FString KickMsg = FString::Printf(
					TEXT("👢 Kicked **%s** (`%s`).\nReason: %s\nBy: %s"),
					*BanDiscordHelpers::EscapeMarkdown(PlayerName), *Uid,
					*BanDiscordHelpers::EscapeMarkdown(Reason), *BanDiscordHelpers::EscapeMarkdown(KickedBy));
				Self->PostToPlayerModerationThread(PlayerName, Uid, KickMsg);
			});
	}

	UE_LOG(LogBanDiscord, Log,
	       TEXT("BanDiscordSubsystem: Initialized. Waiting for Discord provider via SetProvider()."));
}

void UBanDiscordSubsystem::Deinitialize()
{
	FGameModeEvents::GameModePostLoginEvent.Remove(PostLoginHandle);
	PostLoginHandle.Reset();

	if (BanAddedHandle.IsValid())
	{
		UBanDatabase::OnBanAdded.Remove(BanAddedHandle);
		BanAddedHandle.Reset();
	}
	if (BanUpdatedHandle.IsValid())
	{
		UBanDatabase::OnBanUpdated.Remove(BanUpdatedHandle);
		BanUpdatedHandle.Reset();
	}
	if (BanRemovedHandle.IsValid())
	{
		UBanDatabase::OnBanRemoved.Remove(BanRemovedHandle);
		BanRemovedHandle.Reset();
	}
	if (WarnAddedHandle.IsValid())
	{
		UPlayerWarningRegistry::OnWarningAdded.Remove(WarnAddedHandle);
		WarnAddedHandle.Reset();
	}
	if (UMuteRegistry* MuteReg = BoundMuteRegistry.Get())
	{
		MuteReg->OnPlayerMuted.Remove(MutedEventHandle);
		MuteReg->OnPlayerUnmuted.Remove(UnmutedEventHandle);
	}
	else if (UGameInstance* GI = GetGameInstance())
	{
		if (UMuteRegistry* FallbackReg = GI->GetSubsystem<UMuteRegistry>())
		{
			FallbackReg->OnPlayerMuted.Remove(MutedEventHandle);
			FallbackReg->OnPlayerUnmuted.Remove(UnmutedEventHandle);
		}
	}
	MutedEventHandle.Reset();
	UnmutedEventHandle.Reset();
	BoundMuteRegistry.Reset();
	if (KickLoggedHandle.IsValid())
	{
		FBanDiscordNotifier::OnPlayerKickedLogged.Remove(KickLoggedHandle);
		KickLoggedHandle.Reset();
	}

	SetProvider(nullptr);
	Super::Deinitialize();
}

// ─────────────────────────────────────────────────────────────────────────────
// Provider injection
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::SetProvider(IDiscordBridgeProvider* InProvider)
{
	// Guard: no-op when setting the same provider twice.
	if (InProvider == CachedProvider)
		return;

	// Unsubscribe from the old provider.
	if (CachedProvider && InteractionDelegateHandle.IsValid())
	{
		CachedProvider->UnsubscribeInteraction(InteractionDelegateHandle);
		InteractionDelegateHandle.Reset();
	}

	// Detach raw-message listener before clearing the provider.
	if (CachedProvider && RawMessageDelegateHandle.IsValid())
	{
		CachedProvider->UnsubscribeRawMessage(RawMessageDelegateHandle);
		RawMessageDelegateHandle.Reset();
	}

	// Detach in-game staff-chat listener.
	if (StaffChatDelegateHandle.IsValid())
	{
		AStaffChatCommand::OnInGameStaffChat.Remove(StaffChatDelegateHandle);
		StaffChatDelegateHandle.Reset();
	}

	// Unbind appeal-submitted notification when clearing the provider.
	if (AppealSubmittedDelegateHandle.IsValid())
	{
		UBanAppealRegistry::OnBanAppealSubmitted.Remove(AppealSubmittedDelegateHandle);
		AppealSubmittedDelegateHandle.Reset();
	}

	CachedProvider = InProvider;

	// Subscribe to the new provider.
	if (CachedProvider)
	{
		TWeakObjectPtr<UBanDiscordSubsystem> WeakThis(this);

		InteractionDelegateHandle = CachedProvider->SubscribeInteraction(
			[WeakThis](const TSharedPtr<FJsonObject>& InteractionObj)
			{
				if (UBanDiscordSubsystem* Self = WeakThis.Get())
					Self->OnDiscordInteraction(InteractionObj);
			});

		// Bind to appeal-submitted notifications so new appeals are posted to Discord.
		AppealSubmittedDelegateHandle = UBanAppealRegistry::OnBanAppealSubmitted.AddLambda(
			[WeakThis](const FBanAppealEntry& Entry)
			{
				UBanDiscordSubsystem* Self = WeakThis.Get();
				if (!Self || !Self->CachedProvider)
					return;

				const FString& ChannelId = Self->Config.ModerationLogChannelId;
				if (ChannelId.IsEmpty())
					return;

				const FString SubmittedStr = Entry.SubmittedAt.ToIso8601();
				const FString Reason       = Entry.Reason.IsEmpty()      ? TEXT("(none)") : Entry.Reason;
				const FString Contact      = Entry.ContactInfo.IsEmpty() ? TEXT("(none)") : Entry.ContactInfo;

				const FString Message = FString::Printf(
					TEXT(":scales: **New Ban Appeal Submitted**\n")
					TEXT("**ID:** #%lld\n")
					TEXT("**UID:** %s\n")
					TEXT("**Contact:** %s\n")
					TEXT("**Submitted:** %s\n")
					TEXT("**Reason:** %s\n\n")
					TEXT("Use `/appeal approve %lld` to unban or `/appeal deny %lld` to dismiss."),
					Entry.Id, *Entry.Uid,
					*BanDiscordHelpers::EscapeMarkdown(Contact), *SubmittedStr,
					*BanDiscordHelpers::EscapeMarkdown(Reason),
					Entry.Id, Entry.Id);

				Self->Respond(ChannelId, Message);
			});

		UE_LOG(LogBanDiscord, Log,
		       TEXT("BanDiscordSubsystem: Discord provider injected; "
		            "ban commands are %s."),
		       (Config.AdminRoleId.IsEmpty() && Config.ModeratorRoleId.IsEmpty())
		           ? TEXT("DISABLED (neither AdminRoleId nor ModeratorRoleId is set)")
		           : TEXT("enabled"));

		// ── Staff-chat bridge ─────────────────────────────────────────────────

		// In-game → Discord: mirror /staffchat messages to StaffChatChannelId.
		StaffChatDelegateHandle = AStaffChatCommand::OnInGameStaffChat.AddLambda(
			[WeakThis](const FString& SenderName, const FString& Message)
			{
				UBanDiscordSubsystem* Self = WeakThis.Get();
				if (!Self || !Self->CachedProvider) return;

				if (Self->Config.StaffChatChannelId.IsEmpty())
				{
					// Bot is running but the staff-chat Discord channel is not
					// configured. Notify the sender in-game so they are not left
					// silently without a Discord mirror.
					UGameInstance* GI = Self->GetGameInstance();
					UWorld* World = GI ? GI->GetWorld() : nullptr;
					if (World)
					{
						for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
						{
							APlayerController* PC = It->Get();
							if (!PC || !PC->PlayerState) continue;
							if (PC->PlayerState->GetPlayerName().Equals(SenderName, ESearchCase::IgnoreCase))
							{
								PC->ClientMessage(
									TEXT("[StaffChat] Discord mirror is not configured. "
									     "Set StaffChatChannelId in DefaultBanBridge.ini to enable."));
								break;
							}
						}
					}
					return;
				}

				const FString Formatted = FString::Printf(
					TEXT("[In-Game Staff] %s: %s"),
					*BanDiscordHelpers::EscapeMarkdown(SenderName),
					*BanDiscordHelpers::EscapeMarkdown(Message));
				Self->CachedProvider->SendDiscordChannelMessage(
					Self->Config.StaffChatChannelId, Formatted);
			});

		// Discord → in-game: relay human messages from StaffChatChannelId to staff.
		RawMessageDelegateHandle = CachedProvider->SubscribeRawMessage(
			[WeakThis](const TSharedPtr<FJsonObject>& MsgObj)
			{
				UBanDiscordSubsystem* Self = WeakThis.Get();
				if (!Self || !Self->CachedProvider) return;
				if (!MsgObj.IsValid()) return;
				if (Self->Config.StaffChatChannelId.IsEmpty()) return;

				// Only process messages from the configured staff-chat channel.
				FString MsgChannelId;
				if (!MsgObj->TryGetStringField(TEXT("channel_id"), MsgChannelId))
					return;
				if (MsgChannelId != Self->Config.StaffChatChannelId)
					return;

				// Skip bot messages (including the bot's own in-game echo posts).
				const TSharedPtr<FJsonObject>* AuthorPtr = nullptr;
				if (!MsgObj->TryGetObjectField(TEXT("author"), AuthorPtr) || !AuthorPtr)
					return;
				bool bIsBot = false;
				(*AuthorPtr)->TryGetBoolField(TEXT("bot"), bIsBot);
				if (bIsBot) return;

				// Extract display name: nick > global_name > username.
				FString DisplayName;
				const TSharedPtr<FJsonObject>* MemberPtr = nullptr;
				if (MsgObj->TryGetObjectField(TEXT("member"), MemberPtr) && MemberPtr)
					(*MemberPtr)->TryGetStringField(TEXT("nick"), DisplayName);
				if (DisplayName.IsEmpty())
					if (!(*AuthorPtr)->TryGetStringField(TEXT("global_name"), DisplayName)
					    || DisplayName.IsEmpty())
						(*AuthorPtr)->TryGetStringField(TEXT("username"), DisplayName);
				if (DisplayName.IsEmpty())
					DisplayName = TEXT("Discord Staff");

				// Extract message content.
				FString Content;
				if (!MsgObj->TryGetStringField(TEXT("content"), Content) || Content.IsEmpty())
					return;

				const FString Formatted = FString::Printf(
					TEXT("[Discord Staff] %s: %s"), *DisplayName, *Content);

				// Deliver to all online admin/moderator players.
				const UBanChatCommandsConfig* BccCfg = UBanChatCommandsConfig::Get();
				UWorld* World = Self->GetGameInstance()
					? Self->GetGameInstance()->GetWorld() : nullptr;
				if (!World) return;

				for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
				{
					APlayerController* PC = It->Get();
					if (!PC) continue;
					APlayerState* PS = PC->GetPlayerState<APlayerState>();
					if (!PS) continue;

					FString PUIDStr;
					if (const FUniqueNetIdRepl& Id = PS->GetUniqueId();
					    Id.IsValid() && Id.GetType() != FName(TEXT("NONE")))
					{
						// On CSS DS the EOS identity's ToString() returns the raw
						// 32-char PUID directly (no "EOS:" prefix). No ParseUid
						// stripping is needed here.
						PUIDStr = Id.ToString();
					}
					else
					{
						PUIDStr = UBanEnforcer::ExtractEosPuidFromConnectionUrl(PC);
					}

					if (PUIDStr.IsEmpty()) continue;
					const FString CompoundUid = TEXT("EOS:") + PUIDStr.ToLower();
					if (BccCfg && BccCfg->IsModeratorUid(CompoundUid))
						PC->ClientMessage(Formatted);
				}
			});

		// Feature 9: Auto-post the panel to AdminPanelChannelId on startup.
		// Empty AuthorId bypasses the per-user rate-limit.
		if (!Config.AdminPanelChannelId.IsEmpty())
		{
			HandlePanelCommand(Config.AdminPanelChannelId,
			                   FString(), FString(), TArray<FString>(),
			                   TEXT("Server Startup"), FString());
		}
	}
}

// ─────────────────────────────────────────────────────────────────────────────
// Authorisation / extraction helpers
// ─────────────────────────────────────────────────────────────────────────────

TArray<FString> UBanDiscordSubsystem::ExtractMemberRoles(const TSharedPtr<FJsonObject>& MessageObj)
{
	TArray<FString> Roles;
	const TSharedPtr<FJsonObject>* MemberPtr = nullptr;
	if (!MessageObj->TryGetObjectField(TEXT("member"), MemberPtr) || !MemberPtr)
		return Roles;

	const TArray<TSharedPtr<FJsonValue>>* RolesArray = nullptr;
	if (!(*MemberPtr)->TryGetArrayField(TEXT("roles"), RolesArray) || !RolesArray)
		return Roles;

	for (const TSharedPtr<FJsonValue>& RoleVal : *RolesArray)
	{
		FString RoleId;
		if (RoleVal->TryGetString(RoleId))
			Roles.Add(RoleId);
	}
	return Roles;
}

FString UBanDiscordSubsystem::ExtractSenderName(const TSharedPtr<FJsonObject>& MessageObj)
{
	// Priority: server nickname > global_name > username
	FString Name;
	const TSharedPtr<FJsonObject>* MemberPtr = nullptr;
	if (MessageObj->TryGetObjectField(TEXT("member"), MemberPtr) && MemberPtr)
		(*MemberPtr)->TryGetStringField(TEXT("nick"), Name);

	if (Name.IsEmpty())
	{
		const TSharedPtr<FJsonObject>* AuthorPtr = nullptr;
		if (MessageObj->TryGetObjectField(TEXT("author"), AuthorPtr) && AuthorPtr)
		{
			if (!(*AuthorPtr)->TryGetStringField(TEXT("global_name"), Name) || Name.IsEmpty())
				(*AuthorPtr)->TryGetStringField(TEXT("username"), Name);
		}
	}

	return Name.IsEmpty() ? TEXT("Discord Admin") : Name;
}

FString UBanDiscordSubsystem::ExtractSenderId(const TSharedPtr<FJsonObject>& MessageObj)
{
	FString UserId;
	const TSharedPtr<FJsonObject>* MemberPtr = nullptr;
	if (MessageObj->TryGetObjectField(TEXT("member"), MemberPtr) && MemberPtr)
	{
		const TSharedPtr<FJsonObject>* UserPtr = nullptr;
		if ((*MemberPtr)->TryGetObjectField(TEXT("user"), UserPtr) && UserPtr)
			(*UserPtr)->TryGetStringField(TEXT("id"), UserId);
	}
	if (UserId.IsEmpty())
	{
		const TSharedPtr<FJsonObject>* AuthorPtr = nullptr;
		if (MessageObj->TryGetObjectField(TEXT("author"), AuthorPtr) && AuthorPtr)
			(*AuthorPtr)->TryGetStringField(TEXT("id"), UserId);
	}
	return UserId;
}

bool UBanDiscordSubsystem::IsAdminMember(const TArray<FString>& Roles) const
{
	return Config.IsAdminRole(Roles);
}

bool UBanDiscordSubsystem::IsModeratorMember(const TArray<FString>& Roles) const
{
	return Config.IsModeratorRole(Roles);
}

FString UBanDiscordSubsystem::ResolveStaffPrefix(const TArray<FString>& Roles) const
{
	if (IsAdminMember(Roles))    return TEXT("[Admin]");
	if (IsModeratorMember(Roles)) return TEXT("[Moderator]");
	return TEXT("[Staff]");
}

void UBanDiscordSubsystem::Respond(const FString& ChannelId, const FString& Message)
{
	if (!CachedProvider) return;
	// Always post to the command channel so the result is visible to all mods.
	if (!ChannelId.IsEmpty())
		CachedProvider->SendDiscordChannelMessage(ChannelId, Message);
	// Also send as an ephemeral follow-up to the slash command interaction so
	// the admin sees the result inline even if they missed the channel message.
	if (!PendingInteractionToken.IsEmpty())
		CachedProvider->FollowUpInteraction(PendingInteractionToken, Message, /*bEphemeral=*/true);
}

FString UBanDiscordSubsystem::GetCurrentAuditAdminUid(const FString& FallbackName) const
{
	if (!PendingAuthorId.IsEmpty())
		return FString::Printf(TEXT("Discord:%s"), *PendingAuthorId);
	return FallbackName;
}

void UBanDiscordSubsystem::BroadcastInGameModerationNotice(const FString& Message) const
{
	if (Message.IsEmpty()) return;
	const UGameInstance* GI = GetGameInstance();
	UWorld* World = GI ? GI->GetWorld() : nullptr;
	if (!World) return;

	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
	{
		if (APlayerController* PC = It->Get())
			PC->ClientMessage(Message);
	}
}

void UBanDiscordSubsystem::SendInGameModerationNoticeToUid(const FString& Uid, const FString& Message) const
{
	if (Uid.IsEmpty() || Message.IsEmpty()) return;
	const UGameInstance* GI = GetGameInstance();
	UWorld* World = GI ? GI->GetWorld() : nullptr;
	if (!World) return;

	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (!PC) continue;
		if (BanDiscordHelpers::GetControllerUid(PC).Equals(Uid, ESearchCase::IgnoreCase))
		{
			PC->ClientMessage(Message);
			break;
		}
	}
}

void UBanDiscordSubsystem::OnPostLoginModerationReminder(AGameModeBase* GameMode,
                                                          APlayerController* Controller)
{
	if (!Controller || !Controller->PlayerState) return;
	if (GameMode && Controller->GetWorld() != GameMode->GetWorld()) return;

	const FString Uid = BanDiscordHelpers::GetControllerUid(Controller);
	if (Uid.IsEmpty()) return;

	const FString Name = Controller->PlayerState->GetPlayerName();
	UGameInstance* GI = GetGameInstance();
	if (!GI) return;

	if (UMuteRegistry* MuteReg = GI->GetSubsystem<UMuteRegistry>())
	{
		FMuteEntry MuteEntry;
		if (MuteReg->GetMuteEntry(Uid, MuteEntry))
		{
			FString MuteStatus;
			if (MuteEntry.bIsIndefinite)
			{
				MuteStatus = TEXT("indefinitely");
			}
			else
			{
				const int64 RemainingMins64 = static_cast<int64>(FMath::Max(
					0.0, (MuteEntry.ExpireDate - FDateTime::UtcNow()).GetTotalMinutes()));
			const int32 RemainingMins = static_cast<int32>(FMath::Min(RemainingMins64, static_cast<int64>(INT32_MAX)));
				MuteStatus = FString::Printf(
					TEXT("for %s more (until %s UTC)"),
					*BanDiscordHelpers::FormatDuration(RemainingMins),
					*MuteEntry.ExpireDate.ToString(TEXT("%Y-%m-%d %H:%M:%S")));
			}

			Controller->ClientMessage(FString::Printf(
				TEXT("[Moderation] @%s you are currently muted %s. Reason: %s. Muted by: %s."),
				*Name, *MuteStatus, *MuteEntry.Reason, *MuteEntry.MutedBy));
		}
	}

	if (UPlayerWarningRegistry* WarnReg = GI->GetSubsystem<UPlayerWarningRegistry>())
	{
		const int32 WarnCount = WarnReg->GetWarningCount(Uid);
		if (WarnCount > 0)
		{
			// Apply the same WarnDecayDays cutoff that GetWarningCount() uses so
			// the "latest reason" reflects only active (non-decayed) warnings.
			const UBanSystemConfig* WarnSysCfg = UBanSystemConfig::Get();
			const int32 DecayDays = WarnSysCfg ? WarnSysCfg->WarnDecayDays : 0;
			const FDateTime DecayCutoff = (DecayDays > 0)
				? FDateTime::UtcNow() - FTimespan::FromDays(static_cast<double>(DecayDays))
				: FDateTime::MinValue();

			TArray<FWarningEntry> Warnings = WarnReg->GetWarningsForUid(Uid);
			const FWarningEntry* Latest = nullptr;
			for (const FWarningEntry& Entry : Warnings)
			{
				if (Entry.IsExpired()) continue;
				if (DecayDays > 0 && Entry.WarnDate < DecayCutoff) continue;
				if (!Latest || Entry.WarnDate > Latest->WarnDate)
					Latest = &Entry;
			}

			if (Latest)
			{
				Controller->ClientMessage(FString::Printf(
					TEXT("[Moderation] @%s you have %d active warning(s). Latest reason: %s (by %s on %s UTC)."),
					*Name, WarnCount, *Latest->Reason, *Latest->WarnedBy,
					*Latest->WarnDate.ToString(TEXT("%Y-%m-%d %H:%M:%S"))));
			}
			else
			{
				Controller->ClientMessage(FString::Printf(
					TEXT("[Moderation] @%s you have %d active warning(s) on record."),
					*Name, WarnCount));
			}
		}
	}
}

// ─────────────────────────────────────────────────────────────────────────────
// Target resolution
// ─────────────────────────────────────────────────────────────────────────────

bool UBanDiscordSubsystem::IsValidEOSPUID(const FString& Id)
{
	if (Id.Len() != 32) return false;
	for (TCHAR C : Id)
		if (!FChar::IsHexDigit(C)) return false;
	return true;
}

bool UBanDiscordSubsystem::IsValidIPQuery(const FString& Query)
{
	// Accept explicit "IP:<addr>" prefix.
	FString Platform, RawId;
	UBanDatabase::ParseUid(Query, Platform, RawId);
	if (Platform == TEXT("IP") && !RawId.IsEmpty())
		return true;

	// For bare addresses (no colon prefix), require the string to look like a
	// numeric IPv4 address: every character must be a digit or '.', and the
	// string must contain at least one dot.  This rejects player names such as
	// "player.name" that happen to contain a dot but are clearly not IP addresses.
	if (Platform == TEXT("UNKNOWN") && Query.Contains(TEXT(".")))
	{
		for (TCHAR C : Query)
		{
			if (!FChar::IsDigit(C) && C != TEXT('.'))
				return false;
		}
		return true;
	}
	return false;
}

int32 UBanDiscordSubsystem::ParseDurationMinutes(const FString& DurationStr)
{
	if (DurationStr.IsEmpty()) return 0;

	// "perm" / "permanent" → 0 (used by callers as "permanent/indefinite")
	const FString Lower = DurationStr.ToLower();
	if (Lower == TEXT("perm") || Lower == TEXT("permanent")) return 0;

	// Plain integer — assume minutes.
	if (DurationStr.IsNumeric())
	{
		// Use int64 parsing to avoid silent int32 overflow UB for large values
		// (e.g., "2200000000" > INT32_MAX wraps to a negative int32 in ParseInt,
		// which would be misinterpreted as an invalid or near-epoch duration).
		int64 Val64 = 0;
		if (FDefaultValueHelper::ParseInt64(DurationStr, Val64) && Val64 > 0 && Val64 <= static_cast<int64>(INT32_MAX))
			return static_cast<int32>(Val64);
		return 0;
	}

	// Multi-token compound string: e.g. "2h30m", "1d12h", "1w2d", "2h 30m".
	// Each token is <digits><unit> where unit ∈ {w, d, h, m}.
	// Spaces between tokens are allowed and skipped.
	// Use int64 for intermediate accumulation to avoid overflow for large values.
	int64 Total = 0;
	bool bHadToken = false;
	const TCHAR* p = *Lower;

	while (*p)
	{
		// Skip any whitespace between tokens (e.g. "2h 30m").
		while (*p == TEXT(' ') || *p == TEXT('\t')) ++p;
		if (!*p) break;

		if (!FChar::IsDigit(*p)) return 0;

		int64 Num = 0;
		while (*p && FChar::IsDigit(*p))
		{
			// Guard against int64 overflow during digit accumulation.
			if (Num > INT64_MAX / 10) return 0;
			Num = Num * 10 + (*p - TEXT('0'));
			++p;
		}

		if (!*p) return 0; // digits without a trailing unit

		const TCHAR Unit = *p;
		++p;

		int64 Multiplier = 1;
		if      (Unit == TEXT('w')) Multiplier = 10080;
		else if (Unit == TEXT('d')) Multiplier = 1440;
		else if (Unit == TEXT('h')) Multiplier = 60;
		else if (Unit == TEXT('m')) Multiplier = 1;
		else return 0;

		// Guard against int64 overflow in Num * Multiplier.
		if (Multiplier > 1 && Num > INT64_MAX / Multiplier) return 0;
		const int64 Product = Num * Multiplier;

		// Guard against int64 overflow in Total + Product.
		if (Total > INT64_MAX - Product) return 0;
		Total += Product;

		bHadToken = true;
	}

	if (!bHadToken || Total <= 0) return 0;
	// Cap at INT32_MAX to avoid truncation when converting back to int32.
	return static_cast<int32>(FMath::Min(Total, static_cast<int64>(INT32_MAX)));
}

bool UBanDiscordSubsystem::ResolveTarget(const FString& Arg,
                                          FString& OutUid,
                                          FString& OutDisplayName,
                                          FString& OutErrorMsg) const
{
	// 1. Raw 32-character hex EOS PUID.
	if (IsValidEOSPUID(Arg))
	{
		const FString Lower = Arg.ToLower();
		OutUid         = UBanDatabase::MakeUid(TEXT("EOS"), Lower);
		OutDisplayName = Lower;

		// Try to enrich with a real name from the session registry.
		if (UPlayerSessionRegistry* Registry = BanDiscordHelpers::GetRegistry(this))
		{
			FPlayerSessionRecord Record;
			if (Registry->FindByUid(OutUid, Record) && !Record.DisplayName.IsEmpty())
				OutDisplayName = Record.DisplayName;
		}
		return true;
	}

	// 2. Compound UID: "EOS:<32hex>".
	{
		FString Platform, RawId;
		UBanDatabase::ParseUid(Arg, Platform, RawId);
		if (Platform == TEXT("EOS") && IsValidEOSPUID(RawId))
		{
			const FString Lower = RawId.ToLower();
			OutUid         = UBanDatabase::MakeUid(TEXT("EOS"), Lower);
			OutDisplayName = Lower;

			if (UPlayerSessionRegistry* Registry = BanDiscordHelpers::GetRegistry(this))
			{
				FPlayerSessionRecord Record;
				if (Registry->FindByUid(OutUid, Record) && !Record.DisplayName.IsEmpty())
					OutDisplayName = Record.DisplayName;
			}
			return true;
		}

		// 2.5 IP UID: "IP:<address>" — used for explicit IP bans.
		if (Platform == TEXT("IP") && !RawId.IsEmpty())
		{
			OutUid         = UBanDatabase::MakeUid(TEXT("IP"), RawId);
			OutDisplayName = RawId;
			return true;
		}
	}

	// 3. Display-name substring lookup against the PlayerSessionRegistry.
	//    This covers both currently-connected players (BanEnforcer records sessions
	//    on join) and players seen in previous server sessions.
	UPlayerSessionRegistry* Registry = BanDiscordHelpers::GetRegistry(this);
	if (!Registry)
	{
		OutErrorMsg = FString::Printf(
			TEXT("❌ PlayerSessionRegistry is unavailable. "
			     "Use an EOS PUID directly (32-char hex or `EOS:<puid>`)."));
		return false;
	}

	TArray<FPlayerSessionRecord> Matches = Registry->FindByName(Arg);

	if (Matches.IsEmpty())
	{
		const int32 TotalRecords = Registry->GetCount();
		if (TotalRecords == 0)
		{
			OutErrorMsg = FString::Printf(
				TEXT("❌ No player found matching `%s`.\n"
				     "⚠️ The session registry is **empty** — no players have connected to the server "
				     "since BanSystem was installed.\n"
				     "💡 To ban a player who has not yet connected, use their EOS PUID directly:\n"
				     "`/ban add player:<32-char-hex-PUID>`\n"
				     "Find the PUID in the server log (`BanEnforcer: cached EOS PUID …`) or your "
				     "server admin panel."),
				*BanDiscordHelpers::EscapeMarkdown(Arg));
		}
		else
		{
			OutErrorMsg = FString::Printf(
				TEXT("❌ No player found matching `%s` in the session registry (%d record(s)).\n"
				     "Check the spelling or use the player's EOS PUID directly:\n"
				     "`/ban add player:<32-char-hex-PUID>`"),
				*BanDiscordHelpers::EscapeMarkdown(Arg), TotalRecords);
		}
		return false;
	}

	if (Matches.Num() > 1)
	{
		// Build a short list of matching names to help the admin narrow down.
		FString MatchList;
		const int32 ShowCount = FMath::Min(Matches.Num(), 5);
		for (int32 i = 0; i < ShowCount; ++i)
		{
			if (i > 0) MatchList += TEXT(", ");
			MatchList += FString::Printf(TEXT("`%s`"), *BanDiscordHelpers::EscapeMarkdown(Matches[i].DisplayName));
		}
		if (Matches.Num() > ShowCount)
			MatchList += FString::Printf(TEXT(", +%d more"), Matches.Num() - ShowCount);

		OutErrorMsg = FString::Printf(
			TEXT("❌ Ambiguous name `%s` — %d players match: %s. "
			     "Use an EOS PUID to target a specific player."),
			*BanDiscordHelpers::EscapeMarkdown(Arg), Matches.Num(), *MatchList);
		return false;
	}

	OutUid         = Matches[0].Uid;
	OutDisplayName = Matches[0].DisplayName;
	return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// /ban add / /ban temp
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleBanCommand(const TArray<FString>& Args,
                                             const FString& ChannelId,
                                             const FString& SenderName,
                                             bool bTemporary,
                                             const FString& StaffPrefix)
{
	const FString CmdName = bTemporary ? TEXT("/ban temp") : TEXT("/ban add");

	if (!CachedProvider) return;

	UBanDatabase* DB = BanDiscordHelpers::GetDB(this);
	if (!DB)
	{
		Respond(ChannelId,
			TEXT("❌ BanSystem is not available on this server."));
		return;
	}

	// Validate minimum argument count.
	// /ban add:  <target> [reason]          → 1 arg minimum
	// /ban temp: <target> <minutes> [reason] → 2 args minimum
	const int32 MinArgs = bTemporary ? 2 : 1;
	if (Args.Num() < MinArgs)
	{
		const FString Usage = bTemporary
			? TEXT("Usage: `/ban temp <PUID|name> <duration> [reason]`\nDuration: `30m`, `2h`, `1d`, `1w` or plain minutes")
			: TEXT("Usage: `/ban add <PUID|name> [reason]`");
		Respond(ChannelId, Usage);
		return;
	}

	// Resolve target.
	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	// Parse duration for /ban temp.
	// Accepts plain integers (minutes) and shorthand suffixes: 30m, 2h, 1d, 1w, 2h30m, etc.
	int32 DurationMinutes = 0;
	int32 ReasonStartIdx  = 1;
	if (bTemporary)
	{
		DurationMinutes = ParseDurationMinutes(Args[1]);
		if (DurationMinutes <= 0)
		{
			Respond(ChannelId,
				TEXT("❌ `<duration>` must be a positive value "
				     "(e.g. `60`, `30m`, `1h`, `2h30m`, `1d`, `1w`).\n"
				     "Usage: `/ban temp <PUID|name> <duration> [reason]`"));
			return;
		}
		ReasonStartIdx = 2;
	}

	const FString Reason = BanDiscordHelpers::JoinArgs(Args, ReasonStartIdx);

	// Build the ban entry.
	FBanEntry Entry;
	Entry.Uid        = Uid;
	UBanDatabase::ParseUid(Uid, Entry.Platform, Entry.PlayerUID);
	Entry.PlayerName = DisplayName;
	Entry.Reason     = Reason.IsEmpty() ? TEXT("No reason given") : Reason;
	Entry.BannedBy   = SenderName;
	const FDateTime Now = FDateTime::UtcNow();
	Entry.BanDate    = Now;

	if (bTemporary)
	{
		Entry.bIsPermanent = false;
		Entry.ExpireDate   = Now + FTimespan::FromMinutes(DurationMinutes);
	}
	else
	{
		Entry.bIsPermanent = true;
		Entry.ExpireDate   = FDateTime(0);
	}

	// For temporary bans, use AddBanSkipIfPermanentExists so we never silently
	// downgrade an existing permanent ban to a shorter temporary one.
	bool bSkippedPerm = false;
	const bool bBanAdded = Entry.bIsPermanent
		? DB->AddBan(Entry)
		: DB->AddBanSkipIfPermanentExists(Entry, bSkippedPerm);
	if (!bBanAdded)
	{
		if (bSkippedPerm)
		{
			Respond(ChannelId, FString::Printf(
				TEXT("⚠️ **%s** already has a permanent ban — the temporary ban was not applied."),
				*BanDiscordHelpers::EscapeMarkdown(DisplayName)));
		}
		else
		{
			Respond(ChannelId,
				TEXT("❌ Failed to write the ban to the database. Check server logs."));
		}
		return;
	}

	// Kick if the player is currently connected.
	if (UWorld* World = GetGameInstance() ? GetGameInstance()->GetWorld() : nullptr)
		UBanEnforcer::KickConnectedPlayer(World, Uid, Entry.GetKickMessage());

	// Also ban the counterpart identifier (IP↔EOS) so every identity is blocked.
	const TArray<FString> ExtraUids = BanDiscordHelpers::AddCounterpartBans(
		this, DB, Uid, DisplayName, Entry.Reason, SenderName,
		Entry.bIsPermanent, Entry.ExpireDate);
	// Notify the webhook feed so Discord-slash bans appear alongside panel/REST bans.
	FBanDiscordNotifier::NotifyBanCreated(Entry);

	// Format confirmation message.
	const FString SafeName = BanDiscordHelpers::EscapeMarkdown(DisplayName);
	const FString LookupInfo = BanDiscordHelpers::FormatPlayerLookup(this, Uid);
	FString Msg;
	if (bTemporary)
	{
		Msg = FString::Printf(
			TEXT("✅ **%s** (`%s`) has been temporarily banned for **%s**.\n"
			     "Expires: %s\nReason: %s\nBanned by: %s"),
			*SafeName, *Uid, *BanDiscordHelpers::FormatDuration(DurationMinutes),
			*BanDiscordHelpers::FormatExpiry(Entry),
			*BanDiscordHelpers::EscapeMarkdown(Entry.Reason),
			*BanDiscordHelpers::EscapeMarkdown(SenderName));
	}
	else
	{
		Msg = FString::Printf(
			TEXT("✅ **%s** (`%s`) has been **permanently** banned.\n"
			     "Reason: %s\nBanned by: %s"),
			*SafeName, *Uid,
			*BanDiscordHelpers::EscapeMarkdown(Entry.Reason),
			*BanDiscordHelpers::EscapeMarkdown(SenderName));
	}
	Msg += LookupInfo;

	if (ExtraUids.Num() > 0)
	{
		Msg += FString::Printf(TEXT("\nAlso banned: `%s`"),
			*FString::Join(ExtraUids, TEXT("`, `")));
	}

	UE_LOG(LogBanDiscord, Log, TEXT("BanDiscordSubsystem: %s banned %s (%s). Reason: %s"),
	       *SenderName, *DisplayName, *Uid, *Entry.Reason);

	// Write to audit log so Discord-issued bans appear alongside in-game and REST bans.
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
		{
			const FString ActionType = bTemporary ? TEXT("tempban") : TEXT("ban");
			AuditLog->LogAction(ActionType, Uid, DisplayName, GetCurrentAuditAdminUid(SenderName), SenderName, Entry.Reason);
		}
	}

	Respond(ChannelId, Msg);
	const FString InGameBanNotice = bTemporary
		? FString::Printf(
			TEXT("%s Temporarily banned @%s for %s. Reason: %s. By: %s."),
			*StaffPrefix, *DisplayName, *BanDiscordHelpers::FormatDuration(DurationMinutes), *Entry.Reason, *SenderName)
		: FString::Printf(
			TEXT("%s Permanently banned @%s. Reason: %s. By: %s."),
			*StaffPrefix, *DisplayName, *Entry.Reason, *SenderName);
	SendInGameModerationNoticeToUid(Uid, InGameBanNotice);
	PostToPlayerModerationThread(DisplayName, Uid, Msg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /ban remove
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleUnbanCommand(const TArray<FString>& Args,
                                               const FString& ChannelId,
                                               const FString& SenderName,
                                               const FString& StaffPrefix)
{
	if (!CachedProvider) return;

	UBanDatabase* DB = BanDiscordHelpers::GetDB(this);
	if (!DB)
	{
		Respond(ChannelId,
			TEXT("❌ BanSystem is not available on this server."));
		return;
	}

	if (Args.IsEmpty())
	{
		Respond(ChannelId,
			TEXT("Usage: `/ban remove <PUID>`\nPUID can be a 32-char hex string or `EOS:<puid>`."));
		return;
	}

	// Resolve to a compound UID.
	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	// Atomically capture the ban record and remove it in one mutex scope,
	// eliminating the TOCTOU window that existed when GetBanByUid() and
	// RemoveBanByUid() were called as two separate operations.
	FBanEntry BanRecord;
	if (!DB->RemoveBanByUid(Uid, BanRecord))
	{
		// No ban record was found in the database for this UID.  That means the
		// player is already not banned (the file may have been absent or the ban
		// was never persisted).  Report this as a non-fatal note so an admin can
		// always clear a stale or missing-file situation.
		const FString Msg = FString::Printf(
			TEXT("ℹ️ No active ban record found for **%s** (`%s`) — the player is already unbanned.\nUnbanned by: %s"),
			*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
			*BanDiscordHelpers::EscapeMarkdown(SenderName));

		UE_LOG(LogBanDiscord, Log,
		       TEXT("BanDiscordSubsystem: %s issued /ban remove for %s (%s) — no record in DB (already clear)."),
		       *SenderName, *DisplayName, *Uid);

		Respond(ChannelId, Msg);
		PostToPlayerModerationThread(DisplayName, Uid, Msg);
		return;
	}

	// Remove counterpart bans (linked UIDs + session registry lookup).
	// RemoveBanByUid() returned true above, so BanRecord is fully populated.
	const int32 ExtraRemoved =
		BanDiscordHelpers::RemoveCounterpartBans(this, DB, Uid, BanRecord.LinkedUids);

	FBanDiscordNotifier::NotifyBanRemoved(Uid, DisplayName, SenderName);

	FString Msg = FString::Printf(
		TEXT("✅ Ban removed for **%s** (`%s`).\nUnbanned by: %s"),
		*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
		*BanDiscordHelpers::EscapeMarkdown(SenderName));

	if (ExtraRemoved > 0)
		Msg += FString::Printf(TEXT("\nAlso removed %d linked ban(s)."), ExtraRemoved);

	UE_LOG(LogBanDiscord, Log,
	       TEXT("BanDiscordSubsystem: %s unbanned %s (%s)."),
	       *SenderName, *DisplayName, *Uid);

	// Write to audit log so Discord-issued unbans appear alongside REST/in-game unbans.
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
			AuditLog->LogAction(TEXT("unban"), Uid, DisplayName, GetCurrentAuditAdminUid(SenderName), SenderName, TEXT(""));
	}

	Respond(ChannelId, Msg);
	SendInGameModerationNoticeToUid(Uid, FString::Printf(
		TEXT("%s Unbanned @%s. By: %s."),
		*StaffPrefix, *DisplayName, *SenderName));
	PostToPlayerModerationThread(DisplayName, Uid, Msg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /ban check
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleBanCheckCommand(const TArray<FString>& Args,
                                                  const FString& ChannelId)
{
	if (!CachedProvider) return;

	UBanDatabase* DB = BanDiscordHelpers::GetDB(this);
	if (!DB)
	{
		Respond(ChannelId,
			TEXT("❌ BanSystem is not available on this server."));
		return;
	}

	if (Args.IsEmpty())
	{
		Respond(ChannelId,
			TEXT("Usage: `/ban check <PUID|name>`"));
		return;
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	// Reload from disk before checking so manual edits take immediate effect.
	DB->ReloadIfChanged();

	FBanEntry Entry;
	const bool bBanned = DB->IsCurrentlyBannedByAnyId(Uid, Entry);

	FString Msg;
	if (bBanned)
	{
		Msg = FString::Printf(
			TEXT("🔨 **%s** (`%s`) is **currently banned**.\n"
			     "Reason: %s\n"
			     "Banned by: %s\n"
			     "Ban date: %s UTC\n"
			     "Expires: %s"),
			*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
			*BanDiscordHelpers::EscapeMarkdown(Entry.Reason),
			*BanDiscordHelpers::EscapeMarkdown(Entry.BannedBy),
			*Entry.BanDate.ToString(TEXT("%Y-%m-%d %H:%M:%S")),
			*BanDiscordHelpers::FormatExpiry(Entry));

		if (Entry.LinkedUids.Num() > 0)
		{
			Msg += FString::Printf(TEXT("\nLinked UIDs: `%s`"),
			                       *FString::Join(Entry.LinkedUids, TEXT("`, `")));
		}
	}
	else
	{
		// Check if there is any record at all (expired ban).
		FBanEntry AnyEntry;
		if (DB->GetBanByUid(Uid, AnyEntry))
		{
			Msg = FString::Printf(
				TEXT("✅ **%s** (`%s`) is **not currently banned**.\n"
				     "(An expired ban record exists — reason: %s, expired: %s)"),
				*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
				*BanDiscordHelpers::EscapeMarkdown(AnyEntry.Reason),
				*BanDiscordHelpers::FormatExpiry(AnyEntry));
		}
		else
		{
			Msg = FString::Printf(
				TEXT("✅ **%s** (`%s`) is **not banned**."),
				*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid);
		}
	}

	// Append player session lookup (EOS PUID + IP).
	Msg += BanDiscordHelpers::FormatPlayerLookup(this, Uid);

	Respond(ChannelId, Msg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /ban list
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleBanListCommand(const TArray<FString>& Args,
                                                 const FString& ChannelId)
{
	if (!CachedProvider) return;

	UBanDatabase* DB = BanDiscordHelpers::GetDB(this);
	if (!DB)
	{
		Respond(ChannelId,
			TEXT("❌ BanSystem is not available on this server."));
		return;
	}

	DB->ReloadIfChanged();
	TArray<FBanEntry> ActiveBans = DB->GetActiveBans();

	if (ActiveBans.IsEmpty())
	{
		Respond(ChannelId, TEXT("✅ No active bans."));
		return;
	}

	// Determine the requested page (1-indexed).
	int32 Page = 1;
	if (Args.Num() > 0)
		FDefaultValueHelper::ParseInt(Args[0], Page);
	if (Page < 1) Page = 1;

	const int32 Total      = ActiveBans.Num();
	const int32 TotalPages = FMath::DivideAndRoundUp(Total, BanDiscordHelpers::BanListPageSize);
	if (Page > TotalPages) Page = TotalPages;

	const int32 StartIdx = (Page - 1) * BanDiscordHelpers::BanListPageSize;
	const int32 EndIdx   = FMath::Min(StartIdx + BanDiscordHelpers::BanListPageSize, Total);

	FString Body;
	Body.Reserve(1600);

	// Fixed-width header.
	Body += TEXT("```\n");
	Body += FString::Printf(TEXT("%-4s  %-22s  %-16s  %-20s  %s\n"),
	                        TEXT("ID"), TEXT("UID (truncated)"),
	                        TEXT("Name"), TEXT("Expires"), TEXT("Reason"));
	Body += BanDiscordHelpers::SepLine(80) + TEXT("\n");

	for (int32 i = StartIdx; i < EndIdx; ++i)
	{
		const FBanEntry& E = ActiveBans[i];

		// Truncate UID display to keep lines manageable.
		const FString UidShort = BanDiscordHelpers::Truncate(E.Uid, 22);
		const FString NameShort = BanDiscordHelpers::SanitizeForCodeBlock(BanDiscordHelpers::Truncate(E.PlayerName, 16));
		const FString ExpiryShort = E.bIsPermanent
			? TEXT("permanent")
			: E.ExpireDate.ToString(TEXT("%m-%d %H:%M UTC"));
		const FString ReasonShort = BanDiscordHelpers::SanitizeForCodeBlock(BanDiscordHelpers::Truncate(E.Reason, 28));

		Body += FString::Printf(TEXT("%-4lld  %-22s  %-16s  %-20s  %s\n"),
		                        E.Id, *UidShort, *NameShort, *ExpiryShort, *ReasonShort);
	}

	Body += TEXT("```");

	const FString Header = FString::Printf(
		TEXT("**Active Bans — Page %d/%d (%d total)**\n"),
		Page, TotalPages, Total);

	FString Msg = Header + Body;

	// Safety clamp: Discord messages are limited to 2000 characters.
	// If the body is too long, strip back to a safe point and close the code
	// fence properly so Discord does not render a dangling/mismatched block.
	if (Msg.Len() > 1990)
	{
		// Reserve space for the truncation notice + closing fence (≈ 22 chars).
		Msg = Msg.Left(1968) + TEXT("\n...(truncated)\n```");
	}

	Respond(ChannelId, Msg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /player history
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandlePlayerHistoryCommand(const TArray<FString>& Args,
                                                       const FString& ChannelId)
{
	if (!CachedProvider) return;

	if (Args.IsEmpty())
	{
		Respond(ChannelId,
			TEXT("Usage: `/player history <name|PUID|IP>`"));
		return;
	}

	UPlayerSessionRegistry* Registry = BanDiscordHelpers::GetRegistry(this);
	if (!Registry)
	{
		Respond(ChannelId,
			TEXT("❌ PlayerSessionRegistry is not available on this server."));
		return;
	}

	const FString Query = Args[0];
	TArray<FPlayerSessionRecord> Results;

	// Compound UID or raw PUID lookup.
	FString Platform, RawId;
	UBanDatabase::ParseUid(Query, Platform, RawId);
	if (Platform == TEXT("EOS") && IsValidEOSPUID(RawId))
	{
		FPlayerSessionRecord Record;
		if (Registry->FindByUid(UBanDatabase::MakeUid(TEXT("EOS"), RawId.ToLower()), Record))
			Results.Add(Record);
	}
	else if (IsValidEOSPUID(Query))
	{
		FPlayerSessionRecord Record;
		if (Registry->FindByUid(UBanDatabase::MakeUid(TEXT("EOS"), Query.ToLower()), Record))
			Results.Add(Record);
	}
	else if (IsValidIPQuery(Query))
	{
		// Strip the "IP:" prefix if present before querying.
		const FString IpQuery = (Platform == TEXT("IP")) ? RawId : Query;
		Results = Registry->FindByIp(IpQuery);
	}
	else
	{
		Results = Registry->FindByName(Query);
	}

	if (Results.IsEmpty())
	{
		Respond(ChannelId,
			FString::Printf(TEXT("⚠️ No session records found for `%s`."), *Query));
		return;
	}

	// Limit output to avoid exceeding Discord's 2000-char limit.
	constexpr int32 MaxResults = 10;
	const int32 ShowCount = FMath::Min(Results.Num(), MaxResults);

	FString Body;
	Body.Reserve(1600);
	Body += TEXT("```\n");
	Body += FString::Printf(TEXT("%-16s  %-40s  %-15s  %-20s\n"),
	                        TEXT("Name"), TEXT("UID"), TEXT("IP"), TEXT("Last Seen (UTC)"));
	Body += BanDiscordHelpers::SepLine(97) + TEXT("\n");

	for (int32 i = 0; i < ShowCount; ++i)
	{
		const FPlayerSessionRecord& R = Results[i];
		const FString NameShort = BanDiscordHelpers::Truncate(R.DisplayName, 16);
		const FString UidShort  = BanDiscordHelpers::Truncate(R.Uid, 40);
		const FString IpShort   = R.IpAddress.IsEmpty() ? TEXT("—") : BanDiscordHelpers::Truncate(R.IpAddress, 15);
		const FString LastSeen  = BanDiscordHelpers::Truncate(R.LastSeen, 20);
		Body += FString::Printf(TEXT("%-16s  %-40s  %-15s  %s\n"),
		                        *NameShort, *UidShort, *IpShort, *LastSeen);
	}
	Body += TEXT("```");

	FString Header = FString::Printf(
		TEXT("**Player History for `%s`** (%d record(s))\n"),
		*Query, Results.Num());

	if (Results.Num() > MaxResults)
	{
		Header += FString::Printf(TEXT("_(Showing first %d of %d results)_\n"), MaxResults, Results.Num());
	}

	FString Msg = Header + Body;
	if (Msg.Len() > 1990)
		Msg = Msg.Left(1940) + TEXT("\n...(truncated)```");

	Respond(ChannelId, Msg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /mod kick
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleKickCommand(const TArray<FString>& Args,
                                              const FString& ChannelId,
                                              const FString& SenderName,
                                              const FString& StaffPrefix)
{
	if (!CachedProvider) return;

	if (Args.IsEmpty())
	{
		Respond(ChannelId, TEXT("Usage: `/mod kick <PUID|name> [reason]`"));
		return;
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	const FString Reason = (Args.Num() > 1) ? BanDiscordHelpers::JoinArgs(Args, 1) : TEXT("Kicked by Discord admin");

	UGameInstance* GI = GetGameInstance();
	UWorld* World = GI ? GI->GetWorld() : nullptr;
	if (!World)
	{
		Respond(ChannelId,
			TEXT("❌ No active game world found. Is the server running?"));
		return;
	}

	const bool bKicked = UBanEnforcer::KickConnectedPlayer(World, Uid, Reason);
	if (bKicked)
	{
		FBanDiscordNotifier::NotifyPlayerKicked(DisplayName, Reason, SenderName);

		// Write to audit log so Discord-issued kicks appear alongside in-game kicks.
		if (GI)
		{
			if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
				AuditLog->LogAction(TEXT("kick"), Uid, DisplayName, GetCurrentAuditAdminUid(SenderName), SenderName, Reason);
		}

		FString KickMsg = FString::Printf(
			TEXT("✅ Kicked **%s** (`%s`).\nReason: %s\nKicked by: %s"),
			*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
			*BanDiscordHelpers::EscapeMarkdown(Reason),
			*BanDiscordHelpers::EscapeMarkdown(SenderName));
		KickMsg += BanDiscordHelpers::FormatPlayerLookup(this, Uid);
		Respond(ChannelId, KickMsg);
		SendInGameModerationNoticeToUid(Uid, FString::Printf(
			TEXT("%s Kicked @%s. Reason: %s. By: %s."),
			*StaffPrefix, *DisplayName, *Reason, *SenderName));
		PostToPlayerModerationThread(DisplayName, Uid, KickMsg);
	}
	else
	{
		Respond(ChannelId,
			FString::Printf(TEXT("⚠️ Player **%s** (`%s`) is not currently connected."),
				*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid));
	}
}

// ─────────────────────────────────────────────────────────────────────────────
// /mod mute / /mod unmute
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleMuteCommand(const TArray<FString>& Args,
                                              const FString& ChannelId,
                                              const FString& SenderName,
                                              bool bMute,
                                              const FString& StaffPrefix)
{
	if (!CachedProvider) return;

	if (Args.IsEmpty())
	{
		Respond(ChannelId,
			bMute
			? TEXT("Usage: `/mod mute <PUID|name> [duration] [reason]`\nDuration: 30m, 2h, 1d, 1w or plain minutes")
			: TEXT("Usage: `/mod unmute <PUID|name>`"));
		return;
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	UGameInstance* GI = GetGameInstance();
	UMuteRegistry* MuteReg = GI ? GI->GetSubsystem<UMuteRegistry>() : nullptr;
	if (!MuteReg)
	{
		Respond(ChannelId,
			TEXT("❌ Mute commands require the BanChatCommands mod to be installed."));
		return;
	}

	if (!bMute)
	{
		if (!MuteReg->UnmutePlayer(Uid))
		{
			Respond(ChannelId,
				FString::Printf(TEXT("⚠️ **%s** (`%s`) is not currently muted."),
					*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid));
			return;
		}

		// Write to audit log so Discord-issued unmutes appear alongside in-game unmutes.
		if (GI)
		{
			if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
				AuditLog->LogAction(TEXT("unmute"), Uid, DisplayName, GetCurrentAuditAdminUid(SenderName), SenderName, TEXT(""));
		}

		const FString UnmuteMsg = FString::Printf(
			TEXT("✅ Unmuted **%s** (`%s`).\nUnmuted by: %s"),
			*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
			*BanDiscordHelpers::EscapeMarkdown(SenderName));
		Respond(ChannelId, UnmuteMsg);
		SendInGameModerationNoticeToUid(Uid, FString::Printf(
			TEXT("%s Unmuted @%s. By: %s."),
			*StaffPrefix, *DisplayName, *SenderName));
		PostToPlayerModerationThread(DisplayName, Uid, UnmuteMsg);
		return;
	}

	// Parse optional [duration].
	// Accepts raw integers (minutes) as well as human-readable suffixes:
	// 30m, 2h, 1d, 1w — matching the formats accepted by the admin panel.
	int32 ReasonStart = 1;
	int32 Minutes = 0;
	if (Args.Num() > 1)
	{
		const int32 Parsed = ParseDurationMinutes(Args[1]);
		if (Parsed > 0)
		{
			Minutes = Parsed;
			ReasonStart = 2;
		}
	}
	const FString Reason = (Args.Num() > ReasonStart)
		? BanDiscordHelpers::JoinArgs(Args, ReasonStart)
		: TEXT("Muted by Discord admin");

	MuteReg->MutePlayer(Uid, DisplayName, Reason, SenderName, Minutes);

	const FString DurStr = (Minutes > 0)
		? FString::Printf(TEXT(" for **%s**"), *BanDiscordHelpers::FormatDuration(Minutes))
		: TEXT(" **indefinitely**");

	const FString MuteMsg = FString::Printf(
		TEXT("🔇 Muted **%s** (`%s`)%s.\nReason: %s\nMuted by: %s"),
		*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid, *DurStr,
		*BanDiscordHelpers::EscapeMarkdown(Reason),
		*BanDiscordHelpers::EscapeMarkdown(SenderName));

	// Write to audit log so Discord-issued mutes appear alongside in-game mutes.
	if (UBanAuditLog* AuditLog = GI ? GI->GetSubsystem<UBanAuditLog>() : nullptr)
		AuditLog->LogAction(TEXT("mute"), Uid, DisplayName, GetCurrentAuditAdminUid(SenderName), SenderName, Reason);
	Respond(ChannelId, MuteMsg);
	SendInGameModerationNoticeToUid(Uid, FString::Printf(
		TEXT("%s Muted @%s%s. Reason: %s. By: %s."),
		*StaffPrefix, *DisplayName, *DurStr, *Reason, *SenderName));
	PostToPlayerModerationThread(DisplayName, Uid, MuteMsg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /warn add
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleWarnCommand(const TArray<FString>& Args,
                                              const FString& ChannelId,
                                              const FString& SenderName,
                                              const FString& StaffPrefix)
{
	if (!CachedProvider) return;

	if (Args.Num() < 2)
	{
		Respond(ChannelId, TEXT("Usage: `/warn add <PUID|name> <reason...>`"));
		return;
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	const FString Reason = BanDiscordHelpers::JoinArgs(Args, 1);

	UGameInstance* GI = GetGameInstance();
	UPlayerWarningRegistry* WarnReg = GI ? GI->GetSubsystem<UPlayerWarningRegistry>() : nullptr;
	if (!WarnReg)
	{
		Respond(ChannelId,
			TEXT("❌ The warn command requires the BanSystem mod to be installed."));
		return;
	}

	WarnReg->AddWarning(Uid, DisplayName, Reason, SenderName);
	const int32 WarnCount  = WarnReg->GetWarningCount(Uid);
	const int32 WarnPoints = WarnReg->GetWarningPoints(Uid);

	FBanDiscordNotifier::NotifyWarningIssued(Uid, DisplayName, Reason, SenderName, WarnCount);

	// Write to audit log so Discord-issued warns appear alongside in-game and REST warns.
	if (GI)
	{
		if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
			AuditLog->LogAction(TEXT("warn"), Uid, DisplayName, GetCurrentAuditAdminUid(SenderName), SenderName, Reason);
	}

	// Auto-ban escalation — mirrors BanRestApi and BanChatCommands warn paths.
	{
		const UBanSystemConfig* SysCfg = UBanSystemConfig::Get();
		if (SysCfg && GI)
		{
			int32 BanDurationMinutes = -1;
			if (SysCfg->WarnEscalationTiers.Num() > 0)
			{
				// Apply the most severe tier that has been reached.
				// Compare by DurationMinutes: 0 means permanent (most severe);
				// among temporary bans, the longest duration wins.
				// This avoids the old BestThreshold comparison which mixed
				// point-threshold and warn-count values numerically (incomparable units).
				for (const FWarnEscalationTier& Tier : SysCfg->WarnEscalationTiers)
				{
					const bool bHit = (Tier.PointThreshold > 0)
						? (WarnPoints >= Tier.PointThreshold)
						: (WarnCount  >= Tier.WarnCount);
					if (!bHit) continue;

					const bool bMoreSevere = (BanDurationMinutes < 0)
						|| (BanDurationMinutes != 0 && (Tier.DurationMinutes == 0
							|| Tier.DurationMinutes > BanDurationMinutes));
					if (bMoreSevere)
						BanDurationMinutes = Tier.DurationMinutes;
				}
			}
			else if (SysCfg->AutoBanWarnCount > 0 && WarnCount >= SysCfg->AutoBanWarnCount)
			{
				BanDurationMinutes = SysCfg->AutoBanWarnMinutes;
			}

			if (BanDurationMinutes >= 0)
			{
				if (UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>())
				{
					// Use AddBanSkipIfPermanentExists so the check-and-add is
					// atomic under the database lock, eliminating the TOCTOU
					// window that existed when IsCurrentlyBannedByAnyId and
					// AddBan were called as two separate steps.
					FBanEntry AutoBan;
					AutoBan.Uid        = Uid;
					UBanDatabase::ParseUid(Uid, AutoBan.Platform, AutoBan.PlayerUID);
					AutoBan.PlayerName   = DisplayName;
					AutoBan.Reason       = TEXT("Auto-banned: reached warning threshold");
					AutoBan.BannedBy     = SenderName;
					const FDateTime AutoNow1 = FDateTime::UtcNow();
					AutoBan.BanDate      = AutoNow1;
					AutoBan.bIsPermanent = (BanDurationMinutes <= 0);
					AutoBan.ExpireDate   = AutoBan.bIsPermanent
						? FDateTime(0)
						: AutoNow1 + FTimespan::FromMinutes(BanDurationMinutes);
					bool bSkipped = false;
					if (DB->AddBanSkipIfPermanentExists(AutoBan, bSkipped))
					{
						if (UWorld* World = GI->GetWorld())
							UBanEnforcer::KickConnectedPlayer(World, Uid, AutoBan.GetKickMessage());
						BanDiscordHelpers::AddCounterpartBans(this, DB, Uid, DisplayName,
							AutoBan.Reason, SenderName, AutoBan.bIsPermanent, AutoBan.ExpireDate);
						FBanDiscordNotifier::NotifyBanCreated(AutoBan);
						FBanDiscordNotifier::NotifyAutoEscalationBan(AutoBan, WarnCount);
						if (UBanAuditLog* AL = GI->GetSubsystem<UBanAuditLog>())
							AL->LogAction(TEXT("ban"), Uid, DisplayName,
								GetCurrentAuditAdminUid(SenderName), SenderName, AutoBan.Reason);
					}
				}
			}
		}
	}

	const FString WarnMsg = FString::Printf(
		TEXT("⚠️ Warned **%s** (`%s`).\nReason: %s\nTotal warnings: **%d**\nWarned by: %s"),
		*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
		*BanDiscordHelpers::EscapeMarkdown(Reason), WarnCount,
		*BanDiscordHelpers::EscapeMarkdown(SenderName));
	Respond(ChannelId, WarnMsg);
	SendInGameModerationNoticeToUid(Uid, FString::Printf(
		TEXT("%s Warned @%s. Reason: %s. Total warnings: %d. By: %s."),
		*StaffPrefix, *DisplayName, *Reason, WarnCount, *SenderName));
	PostToPlayerModerationThread(DisplayName, Uid, WarnMsg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /mod announce
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleAnnounceCommand(const TArray<FString>& Args,
                                                  const FString& ChannelId,
                                                  const FString& SenderName)
{
	if (!CachedProvider) return;

	if (Args.IsEmpty())
	{
		Respond(ChannelId, TEXT("Usage: `/mod announce <message...>`"));
		return;
	}

	const FString Message = BanDiscordHelpers::JoinArgs(Args, 0);

	UGameInstance* GI = GetGameInstance();
	UWorld* World = GI ? GI->GetWorld() : nullptr;
	if (!World)
	{
		Respond(ChannelId,
			TEXT("❌ No active game world found. Is the server running?"));
		return;
	}

	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC) PC->ClientMessage(FString::Printf(TEXT("[Announcement] %s"), *Message));
	}

	const FString AnnounceConfirm = FString::Printf(
		TEXT("📢 Announcement sent to all in-game players:\n> %s\nSent by: %s"),
		*BanDiscordHelpers::EscapeMarkdown(Message),
		*BanDiscordHelpers::EscapeMarkdown(SenderName));
	Respond(ChannelId, AnnounceConfirm);
	PostModerationLog(AnnounceConfirm);
}

// ─────────────────────────────────────────────────────────────────────────────
// /ban removename
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleUnbanNameCommand(const TArray<FString>& Args,
                                                   const FString& ChannelId,
                                                   const FString& SenderName)
{
	if (!CachedProvider) return;

	UBanDatabase* DB = BanDiscordHelpers::GetDB(this);
	if (!DB)
	{
		Respond(ChannelId,
			TEXT("❌ BanSystem is not available on this server."));
		return;
	}

	if (Args.IsEmpty())
	{
		Respond(ChannelId,
			TEXT("Usage: `/ban removename <name_substring>`"));
		return;
	}

	UPlayerSessionRegistry* Registry = BanDiscordHelpers::GetRegistry(this);
	if (!Registry)
	{
		Respond(ChannelId,
			TEXT("❌ PlayerSessionRegistry is not available."));
		return;
	}

	const FString NameQuery = BanDiscordHelpers::JoinArgs(Args, 0);
	TArray<FPlayerSessionRecord> Matches = Registry->FindByName(NameQuery);

	if (Matches.IsEmpty())
	{
		Respond(ChannelId,
			FString::Printf(TEXT("❌ No session record found for name `%s`."), *BanDiscordHelpers::EscapeMarkdown(NameQuery)));
		return;
	}
	if (Matches.Num() > 1)
	{
		FString List;
		const int32 Show = FMath::Min(Matches.Num(), 5);
		for (int32 i = 0; i < Show; ++i)
		{
			if (i > 0) List += TEXT(", ");
			List += FString::Printf(TEXT("`%s`"), *BanDiscordHelpers::EscapeMarkdown(Matches[i].DisplayName));
		}
		if (Matches.Num() > Show)
			List += FString::Printf(TEXT(", +%d more"), Matches.Num() - Show);
		Respond(ChannelId,
			FString::Printf(TEXT("❌ Ambiguous name `%s` — %d matches: %s. Use `/ban remove <PUID>` instead."),
				*BanDiscordHelpers::EscapeMarkdown(NameQuery), Matches.Num(), *List));
		return;
	}

	const FPlayerSessionRecord& Record = Matches[0];

	// Remove EOS ban atomically, capturing LinkedUids for counterpart cleanup.
	FBanEntry RemovedEntry;
	if (!DB->RemoveBanByUid(Record.Uid, RemovedEntry))
	{
		Respond(ChannelId,
			FString::Printf(TEXT("⚠️ No active ban found for **%s** (`%s`)."),
				*BanDiscordHelpers::EscapeMarkdown(Record.DisplayName), *Record.Uid));
		return;
	}

	// Remove counterpart bans (linked UIDs + session-registry IP lookup).
	const int32 ExtraRemoved =
		BanDiscordHelpers::RemoveCounterpartBans(this, DB, Record.Uid, RemovedEntry.LinkedUids);

	// Notify webhook / OnBanRemoved delegate (same as every other unban path).
	FBanDiscordNotifier::NotifyBanRemoved(Record.Uid, Record.DisplayName, SenderName);

	FString Msg = FString::Printf(
		TEXT("✅ Ban removed for **%s** (`%s`).\nUnbanned by: %s"),
		*BanDiscordHelpers::EscapeMarkdown(Record.DisplayName),
		*Record.Uid,
		*BanDiscordHelpers::EscapeMarkdown(SenderName));

	if (ExtraRemoved > 0)
		Msg += FString::Printf(TEXT("\nAlso removed %d linked ban(s)."), ExtraRemoved);
	UE_LOG(LogBanDiscord, Log, TEXT("BanDiscordSubsystem: %s unbanname %s (%s)."),
		*SenderName, *Record.DisplayName, *Record.Uid);

	// Write to audit log so Discord-issued removename unbans appear alongside other unbans.
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
			AuditLog->LogAction(TEXT("unban"), Record.Uid, Record.DisplayName,
				GetCurrentAuditAdminUid(SenderName), SenderName, TEXT(""));
	}

	Respond(ChannelId, Msg);
	PostModerationLog(Msg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /ban byname
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleBanNameCommand(const TArray<FString>& Args,
                                                 const FString& ChannelId,
                                                 const FString& SenderName)
{
	if (!CachedProvider) return;

	UBanDatabase* DB = BanDiscordHelpers::GetDB(this);
	if (!DB)
	{
		Respond(ChannelId,
			TEXT("❌ BanSystem is not available on this server."));
		return;
	}

	if (Args.IsEmpty())
	{
		Respond(ChannelId,
			TEXT("Usage: `/ban byname <name_substring> [reason]`"));
		return;
	}

	UPlayerSessionRegistry* Registry = BanDiscordHelpers::GetRegistry(this);
	if (!Registry)
	{
		Respond(ChannelId,
			TEXT("❌ PlayerSessionRegistry is not available."));
		return;
	}

	TArray<FPlayerSessionRecord> Matches = Registry->FindByName(Args[0]);
	if (Matches.IsEmpty())
	{
		Respond(ChannelId,
			FString::Printf(TEXT("❌ No session record found for name `%s`."), *BanDiscordHelpers::EscapeMarkdown(Args[0])));
		return;
	}
	if (Matches.Num() > 1)
	{
		FString List;
		const int32 Show = FMath::Min(Matches.Num(), 5);
		for (int32 i = 0; i < Show; ++i)
		{
			if (i > 0) List += TEXT(", ");
			List += FString::Printf(TEXT("`%s`"), *BanDiscordHelpers::EscapeMarkdown(Matches[i].DisplayName));
		}
		if (Matches.Num() > Show)
			List += FString::Printf(TEXT(", +%d more"), Matches.Num() - Show);
		Respond(ChannelId,
			FString::Printf(TEXT("❌ Ambiguous name `%s` — %d matches: %s. Use `/ban add <PUID>` instead."),
				*BanDiscordHelpers::EscapeMarkdown(Args[0]), Matches.Num(), *List));
		return;
	}

	const FPlayerSessionRecord& Record = Matches[0];
	const FString Reason = (Args.Num() > 1)
		? BanDiscordHelpers::JoinArgs(Args, 1)
		: TEXT("No reason given");

	int32 Banned = 0;

	// Ban EOS PUID — declared outside the block so we can call GetKickMessage() below.
	FBanEntry EosEntry;
	EosEntry.Uid        = Record.Uid;
	UBanDatabase::ParseUid(Record.Uid, EosEntry.Platform, EosEntry.PlayerUID);
	EosEntry.PlayerName = Record.DisplayName;
	EosEntry.Reason     = Reason;
	EosEntry.BannedBy   = SenderName;
	const FDateTime BanNow = FDateTime::UtcNow();
	EosEntry.BanDate    = BanNow;
	EosEntry.bIsPermanent = true;
	EosEntry.ExpireDate   = FDateTime(0);
	bool bEosSkipped = false;
	if (DB->AddBanSkipIfPermanentExists(EosEntry, bEosSkipped))
	{
		++Banned;
		FBanDiscordNotifier::NotifyBanCreated(EosEntry);
	}
	else if (bEosSkipped)
	{
		Respond(ChannelId,
			FString::Printf(TEXT("⚠️ **%s** (`%s`) already has a permanent ban — no duplicate record created."),
				*BanDiscordHelpers::EscapeMarkdown(Record.DisplayName), *Record.Uid));
		return;
	}
	else
	{
		// SaveToFile failed — no persistent ban was written; do not kick.
		Respond(ChannelId, TEXT("❌ Failed to write ban to the database. Check server logs."));
		return;
	}

	// Also ban IP if recorded.
	FString IpUid;
	if (!Record.IpAddress.IsEmpty())
	{
		IpUid = UBanDatabase::MakeUid(TEXT("IP"), Record.IpAddress);
		FBanEntry IpEntry;
		IpEntry.Uid        = IpUid;
		IpEntry.Platform   = TEXT("IP");
		IpEntry.PlayerUID  = Record.IpAddress;
		IpEntry.PlayerName = Record.DisplayName;
		IpEntry.Reason     = Reason;
		IpEntry.BannedBy   = SenderName;
		IpEntry.BanDate    = BanNow;
		IpEntry.bIsPermanent = true;
		IpEntry.ExpireDate   = FDateTime(0);
		IpEntry.LinkedUids.Add(Record.Uid);
		bool bIpSkipped = false;
		if (DB->AddBanSkipIfPermanentExists(IpEntry, bIpSkipped))
		{
			++Banned;
			// Cross-link the EOS ban.
			DB->LinkBans(Record.Uid, IpUid);
			FBanDiscordNotifier::NotifyBanCreated(IpEntry);
		}
	}

	// Kick if currently connected — use the actual ban entry so the player sees the real reason.
	if (UWorld* World = GetGameInstance() ? GetGameInstance()->GetWorld() : nullptr)
		UBanEnforcer::KickConnectedPlayer(World, Record.Uid, EosEntry.GetKickMessage());

	const FString SafeName = BanDiscordHelpers::EscapeMarkdown(Record.DisplayName);
	FString Msg = FString::Printf(
		TEXT("✅ Banned **%s** (`%s`) — %d record(s) added.\nReason: %s\nBanned by: %s"),
		*SafeName, *Record.Uid, Banned,
		*BanDiscordHelpers::EscapeMarkdown(Reason),
		*BanDiscordHelpers::EscapeMarkdown(SenderName));

	// Show EOS PUID.
	FString ByNamePlatform, ByNameRawPuid;
	UBanDatabase::ParseUid(Record.Uid, ByNamePlatform, ByNameRawPuid);
	if (!ByNameRawPuid.IsEmpty())
		Msg += FString::Printf(TEXT("\nEOS PUID: `%s`"), *ByNameRawPuid);

	if (!IpUid.IsEmpty())
		Msg += FString::Printf(TEXT("\nIP ban: `%s`"), *IpUid);
	else if (!Record.IpAddress.IsEmpty())
		Msg += FString::Printf(TEXT("\nIP: `%s` (not IP-banned)"), *Record.IpAddress);

	UE_LOG(LogBanDiscord, Log, TEXT("BanDiscordSubsystem: %s banname %s (%s). Reason: %s"),
		*SenderName, *Record.DisplayName, *Record.Uid, *Reason);

	// Write to audit log so Discord-issued byname bans appear alongside other bans.
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
			AuditLog->LogAction(TEXT("ban"), Record.Uid, Record.DisplayName,
				GetCurrentAuditAdminUid(SenderName), SenderName, Reason);
	}

	Respond(ChannelId, Msg);
	PostModerationLog(Msg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /ban reason
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleBanReasonCommand(const TArray<FString>& Args,
                                                   const FString& ChannelId,
                                                   const FString& SenderName)
{
	if (!CachedProvider) return;

	UBanDatabase* DB = BanDiscordHelpers::GetDB(this);
	if (!DB)
	{
		Respond(ChannelId,
			TEXT("❌ BanSystem is not available on this server."));
		return;
	}

	if (Args.Num() < 2)
	{
		Respond(ChannelId,
			TEXT("Usage: `/ban reason <PUID|name> <new reason...>`"));
		return;
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	// Initial read — used only to obtain the primary UID and old reason for the
	// response message.  The actual mutation is performed inside UpdateBan() which
	// holds the database lock for the full read-modify-write, closing the TOCTOU
	// window that existed with AddBan().
	FBanEntry Entry;
	if (!DB->GetBanByUid(Uid, Entry))
	{
		Respond(ChannelId,
			FString::Printf(TEXT("⚠️ No ban record found for **%s** (`%s`)."),
				*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid));
		return;
	}

	const FString OldReason  = Entry.Reason;
	const FString NewReason  = BanDiscordHelpers::JoinArgs(Args, 1);
	const FString PrimaryUid = Entry.Uid;

	FBanEntry Updated;
	if (!DB->UpdateBan(PrimaryUid, [&NewReason](FBanEntry& E) { E.Reason = NewReason; }, Updated))
	{
		// The ban was removed between the check above and the atomic update
		// (concurrent unban or expiry).
		Respond(ChannelId,
			FString::Printf(TEXT("⚠️ **%s** (`%s`) — ban was removed before the reason could be updated."),
				*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid));
		return;
	}

	// Write to audit log so Discord-issued reason updates appear alongside other changes.
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
			AuditLog->LogAction(TEXT("banreason"), Uid, DisplayName,
				GetCurrentAuditAdminUid(SenderName), SenderName, Updated.Reason);
	}

	const FString Msg = FString::Printf(
		TEXT("✅ Ban reason updated for **%s** (`%s`).\nOld reason: %s\nNew reason: %s\nUpdated by: %s"),
		*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
		*BanDiscordHelpers::EscapeMarkdown(OldReason),
		*BanDiscordHelpers::EscapeMarkdown(Updated.Reason),
		*BanDiscordHelpers::EscapeMarkdown(SenderName));
	Respond(ChannelId, Msg);
	PostModerationLog(Msg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /ban link / /ban unlink
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleLinkBansCommand(const TArray<FString>& Args,
                                                  const FString& ChannelId,
                                                  const FString& SenderName,
                                                  bool bLink)
{
	if (!CachedProvider) return;

	UBanDatabase* DB = BanDiscordHelpers::GetDB(this);
	if (!DB)
	{
		Respond(ChannelId,
			TEXT("❌ BanSystem is not available on this server."));
		return;
	}

	const FString CmdName = bLink ? TEXT("/ban link") : TEXT("/ban unlink");
	if (Args.Num() < 2)
	{
		Respond(ChannelId,
			FString::Printf(TEXT("Usage: `%s <UID1> <UID2>`"), *CmdName));
		return;
	}

	// Resolve both arguments to compound UIDs.
	FString Uid1, Name1, Err1;
	FString Uid2, Name2, Err2;
	if (!ResolveTarget(Args[0], Uid1, Name1, Err1))
	{
		Respond(ChannelId, Err1);
		return;
	}
	if (!ResolveTarget(Args[1], Uid2, Name2, Err2))
	{
		Respond(ChannelId, Err2);
		return;
	}

	if (Uid1.Equals(Uid2, ESearchCase::IgnoreCase))
	{
		Respond(ChannelId,
			TEXT("❌ Both UIDs are the same; no change made."));
		return;
	}

	const bool bOk = bLink ? DB->LinkBans(Uid1, Uid2) : DB->UnlinkBans(Uid1, Uid2);
	if (!bOk)
	{
		Respond(ChannelId,
			bLink
			? TEXT("⚠️ Could not link bans. Ensure both UIDs have ban records.")
			: TEXT("⚠️ No link found between those UIDs."));
		return;
	}

	const FString Verb = bLink ? TEXT("linked") : TEXT("unlinked");
	const FString Msg = FString::Printf(
		TEXT("✅ Successfully %s `%s` and `%s`.\nBy: %s"),
		*Verb, *Uid1, *Uid2,
		*BanDiscordHelpers::EscapeMarkdown(SenderName));
	Respond(ChannelId, Msg);
	PostModerationLog(Msg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /ban extend
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleExtendBanCommand(const TArray<FString>& Args,
                                                   const FString& ChannelId,
                                                   const FString& SenderName)
{
	if (!CachedProvider) return;

	UBanDatabase* DB = BanDiscordHelpers::GetDB(this);
	if (!DB)
	{
		Respond(ChannelId,
			TEXT("❌ BanSystem is not available on this server."));
		return;
	}

	if (Args.Num() < 2)
	{
		Respond(ChannelId,
			TEXT("Usage: `/ban extend <PUID|name> <duration>`\nDuration: `30m`, `2h`, `1d`, `1w` or plain minutes"));
		return;
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	const int32 Minutes = ParseDurationMinutes(Args[1]);
	if (Minutes <= 0)
	{
		Respond(ChannelId,
			TEXT("❌ `<duration>` must be a positive value (e.g. `60`, `30m`, `2h`, `1d`)."));
		return;
	}

	FBanEntry Entry;
	if (!DB->IsCurrentlyBannedByAnyId(Uid, Entry))
	{
		Respond(ChannelId,
			FString::Printf(TEXT("⚠️ **%s** (`%s`) is not currently banned."),
				*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid));
		return;
	}

	if (Entry.bIsPermanent)
	{
		Respond(ChannelId,
			FString::Printf(TEXT("⚠️ **%s** has a **permanent** ban — cannot extend."),
				*BanDiscordHelpers::EscapeMarkdown(DisplayName)));
		return;
	}

	// Perform the extend atomically inside UpdateBan() so that:
	// 1. The new expiry is computed relative to the freshest known expiry (not
	//    a stale snapshot), and
	// 2. If the ban is removed between the check above and the write (concurrent
	//    unban or expiry), UpdateBan() returns false instead of re-creating the ban.
	const FString PrimaryUid   = Entry.Uid;
	const int32   MinutesToAdd = Minutes;

	FBanEntry Updated;
	if (!DB->UpdateBan(PrimaryUid,
		[MinutesToAdd](FBanEntry& E)
		{
			// Re-check under the DB lock: if a concurrent operation upgraded this ban to
			// permanent, we must not silently downgrade it back to temporary.
			if (E.bIsPermanent) return;
			const FDateTime BaseTime = FMath::Max(E.ExpireDate, FDateTime::UtcNow());
			E.ExpireDate   = BaseTime + FTimespan::FromMinutes(MinutesToAdd);
			E.bIsPermanent = false;
		},
		Updated))
	{
		// Ban was removed concurrently (unban, prune, or expiry).
		Respond(ChannelId,
			FString::Printf(TEXT("⚠️ **%s** (`%s`) is no longer banned — the ban may have expired. Cannot extend."),
				*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid));
		return;
	}

	// If a concurrent upgrade to permanent happened inside UpdateBan, abort.
	if (Updated.bIsPermanent)
	{
		Respond(ChannelId,
			FString::Printf(TEXT("⚠️ **%s** has a **permanent** ban (upgraded concurrently) — cannot extend."),
				*BanDiscordHelpers::EscapeMarkdown(DisplayName)));
		return;
	}

	// Write to audit log so Discord-issued extend operations appear alongside in-game extends.
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
			AuditLog->LogAction(TEXT("extend"), Uid, DisplayName, GetCurrentAuditAdminUid(SenderName), SenderName,
				FString::Printf(TEXT("Extended by %s -> new expiry %s UTC"),
					*BanDiscordHelpers::FormatDuration(Minutes),
					*Updated.ExpireDate.ToString(TEXT("%Y-%m-%d %H:%M:%S"))));
	}

	const FString Msg = FString::Printf(
		TEXT("✅ Extended ban for **%s** (`%s`) by **%s**.\nNew expiry: %s UTC\nBy: %s"),
		*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
		*BanDiscordHelpers::FormatDuration(Minutes),
		*Updated.ExpireDate.ToString(TEXT("%Y-%m-%d %H:%M:%S")),
		*BanDiscordHelpers::EscapeMarkdown(SenderName));
	Respond(ChannelId, Msg);
	PostModerationLog(Msg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /ban duration
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleDurationCommand(const TArray<FString>& Args,
                                                  const FString& ChannelId)
{
	if (!CachedProvider) return;

	UBanDatabase* DB = BanDiscordHelpers::GetDB(this);
	if (!DB)
	{
		Respond(ChannelId,
			TEXT("❌ BanSystem is not available on this server."));
		return;
	}

	if (Args.IsEmpty())
	{
		Respond(ChannelId,
			TEXT("Usage: `/ban duration <PUID|name>`"));
		return;
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	FBanEntry Entry;
	if (!DB->IsCurrentlyBannedByAnyId(Uid, Entry))
	{
		Respond(ChannelId,
			FString::Printf(TEXT("✅ **%s** (`%s`) is not currently banned."),
				*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid));
		return;
	}

	FString DurStr;
	if (Entry.bIsPermanent)
	{
		DurStr = TEXT("**permanent**");
	}
	else
	{
		const FTimespan Remaining = Entry.ExpireDate - FDateTime::UtcNow();
		if (Remaining.GetTicks() <= 0)
		{
			DurStr = TEXT("expired (ban will be pruned on next check)");
		}
		else
		{
			const double RawMins = Remaining.GetTotalMinutes();
			const int32 TotalMins = (FMath::IsFinite(RawMins) && RawMins > 0.0)
				? static_cast<int32>(FMath::Min(static_cast<int64>(RawMins), static_cast<int64>(INT32_MAX)))
				: 0;
			DurStr = FString::Printf(TEXT("**%s** remaining (expires %s UTC)"),
				*BanDiscordHelpers::FormatDuration(TotalMins),
				*Entry.ExpireDate.ToString(TEXT("%Y-%m-%d %H:%M:%S")));
		}
	}

	Respond(ChannelId,
		FString::Printf(TEXT("⏱️ **%s** (`%s`) — ban duration: %s"),
			*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid, *DurStr));
}

// ─────────────────────────────────────────────────────────────────────────────
// /warn list
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleWarningsCommand(const TArray<FString>& Args,
                                                  const FString& ChannelId)
{
	if (!CachedProvider) return;

	if (Args.IsEmpty())
	{
		Respond(ChannelId,
			TEXT("Usage: `/warn list <PUID|name>`"));
		return;
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	UGameInstance* GI = GetGameInstance();
	UPlayerWarningRegistry* WarnReg = GI ? GI->GetSubsystem<UPlayerWarningRegistry>() : nullptr;
	if (!WarnReg)
	{
		Respond(ChannelId,
			TEXT("❌ The warnings system requires the BanSystem mod to be installed."));
		return;
	}

	TArray<FWarningEntry> Warnings = WarnReg->GetWarningsForUid(Uid);
	if (Warnings.IsEmpty())
	{
		Respond(ChannelId,
			FString::Printf(TEXT("✅ No warnings on record for **%s** (`%s`)."),
				*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid));
		return;
	}

	FString Body;
	Body.Reserve(1600);
	Body += TEXT("```\n");
	Body += FString::Printf(TEXT("%-4s  %-20s  %-12s  %s\n"),
		TEXT("ID"), TEXT("Date (UTC)"), TEXT("By"), TEXT("Reason"));
	Body += BanDiscordHelpers::SepLine(72) + TEXT("\n");

	const int32 ShowMax = FMath::Min(Warnings.Num(), 15);
	for (int32 i = 0; i < ShowMax; ++i)
	{
		const FWarningEntry& W = Warnings[i];
		const FString DateStr  = W.WarnDate.ToString(TEXT("%m-%d %H:%M"));
		const FString ByShort  = BanDiscordHelpers::SanitizeForCodeBlock(BanDiscordHelpers::Truncate(W.WarnedBy, 12));
		const FString ReasonSh = BanDiscordHelpers::SanitizeForCodeBlock(BanDiscordHelpers::Truncate(W.Reason, 40));
		Body += FString::Printf(TEXT("%-4lld  %-20s  %-12s  %s\n"),
			W.Id, *DateStr, *ByShort, *ReasonSh);
	}
	Body += TEXT("```");

	FString Header = FString::Printf(
		TEXT("**Warnings for %s** (`%s`) — %d total\n"),
		*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid, Warnings.Num());
	if (Warnings.Num() > ShowMax)
		Header += FString::Printf(TEXT("_(Showing first %d)_\n"), ShowMax);

	FString Msg = Header + Body;
	if (Msg.Len() > 1990)
		Msg = Msg.Left(1940) + TEXT("\n...(truncated)```");
	Respond(ChannelId, Msg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /warn clearall
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleClearWarnsCommand(const TArray<FString>& Args,
                                                    const FString& ChannelId,
                                                    const FString& SenderName)
{
	if (!CachedProvider) return;

	if (Args.IsEmpty())
	{
		Respond(ChannelId,
			TEXT("Usage: `/warn clearall <PUID|name>`"));
		return;
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	UGameInstance* GI = GetGameInstance();
	UPlayerWarningRegistry* WarnReg = GI ? GI->GetSubsystem<UPlayerWarningRegistry>() : nullptr;
	if (!WarnReg)
	{
		Respond(ChannelId,
			TEXT("❌ The warnings system requires the BanSystem mod to be installed."));
		return;
	}

	const int32 Removed = WarnReg->ClearWarningsForUid(Uid);

	// Write to audit log so Discord-issued warning clears appear alongside in-game ones.
	if (GI)
	{
		if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
			AuditLog->LogAction(TEXT("clearwarns"), Uid, DisplayName,
				GetCurrentAuditAdminUid(SenderName), SenderName,
				FString::Printf(TEXT("Cleared %d warning(s)"), Removed));
	}

	const FString Msg = FString::Printf(
		TEXT("✅ Cleared **%d** warning(s) for **%s** (`%s`).\nBy: %s"),
		Removed,
		*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
		*BanDiscordHelpers::EscapeMarkdown(SenderName));
	Respond(ChannelId, Msg);
	PostModerationLog(Msg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /warn clearone (by ID)
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleClearWarnByIdCommand(const TArray<FString>& Args,
                                                       const FString& ChannelId,
                                                       const FString& SenderName)
{
	if (!CachedProvider) return;

	if (Args.IsEmpty())
	{
		Respond(ChannelId,
			TEXT("Usage: `/warn clearone <warning_id>`\nSee warning IDs with `/warn list <player>`."));
		return;
	}

	int64 WarnId = 0;
	{
		// Guard against non-numeric input and int64 overflow (same pattern as
		// AClearWarnByIdChatCommand and BanRestApi::ParseInt64Param).
		const int32 IdLen = Args[0].Len();
		if (!Args[0].IsNumeric() || IdLen > 19 ||
			(IdLen == 19 && Args[0] > TEXT("9223372036854775807")))
		{
			Respond(ChannelId,
				TEXT("❌ `<warning_id>` must be a positive integer."));
			return;
		}
		WarnId = FCString::Atoi64(*Args[0]);
		if (WarnId <= 0)
		{
			Respond(ChannelId,
				TEXT("❌ `<warning_id>` must be a positive integer."));
			return;
		}
	}

	UGameInstance* GI = GetGameInstance();
	UPlayerWarningRegistry* WarnReg = GI ? GI->GetSubsystem<UPlayerWarningRegistry>() : nullptr;
	if (!WarnReg)
	{
		Respond(ChannelId,
			TEXT("❌ The warnings system requires the BanSystem mod to be installed."));
		return;
	}

	if (!WarnReg->DeleteWarningById(WarnId))
	{
		Respond(ChannelId,
			FString::Printf(TEXT("⚠️ No warning found with ID `%lld`."), WarnId));
		return;
	}

	// Write to audit log so Discord-issued warning deletions appear alongside in-game ones.
	if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
		AuditLog->LogAction(TEXT("deletewarn_id"),
			FString::Printf(TEXT("warning#%lld"), WarnId), TEXT(""),
			GetCurrentAuditAdminUid(SenderName), SenderName,
			FString::Printf(TEXT("Deleted warning id %lld"), WarnId));

	const FString Msg = FString::Printf(
		TEXT("✅ Deleted warning #%lld.\nBy: %s"), WarnId,
		*BanDiscordHelpers::EscapeMarkdown(SenderName));
	Respond(ChannelId, Msg);
	PostModerationLog(Msg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /player note
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleNoteCommand(const TArray<FString>& Args,
                                              const FString& ChannelId,
                                              const FString& SenderName)
{
	if (!CachedProvider) return;

	if (Args.Num() < 2)
	{
		Respond(ChannelId,
			TEXT("Usage: `/player note <PUID|name> <text...>`"));
		return;
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	UGameInstance* GI = GetGameInstance();
	UPlayerNoteRegistry* NoteReg = GI ? GI->GetSubsystem<UPlayerNoteRegistry>() : nullptr;
	if (!NoteReg)
	{
		Respond(ChannelId,
			TEXT("❌ Player notes require the BanChatCommands mod to be installed."));
		return;
	}

	const FString NoteText = BanDiscordHelpers::JoinArgs(Args, 1);
	NoteReg->AddNote(Uid, DisplayName, NoteText, SenderName);

	Respond(ChannelId,
		FString::Printf(TEXT("📝 Note added for **%s** (`%s`).\nNote: %s\nAdded by: %s"),
			*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
			*BanDiscordHelpers::EscapeMarkdown(NoteText),
			*BanDiscordHelpers::EscapeMarkdown(SenderName)));
}

// ─────────────────────────────────────────────────────────────────────────────
// /player notes
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleNotesCommand(const TArray<FString>& Args,
                                               const FString& ChannelId)
{
	if (!CachedProvider) return;

	if (Args.IsEmpty())
	{
		Respond(ChannelId,
			TEXT("Usage: `/player notes <PUID|name>`"));
		return;
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	UGameInstance* GI = GetGameInstance();
	UPlayerNoteRegistry* NoteReg = GI ? GI->GetSubsystem<UPlayerNoteRegistry>() : nullptr;
	if (!NoteReg)
	{
		Respond(ChannelId,
			TEXT("❌ Player notes require the BanChatCommands mod to be installed."));
		return;
	}

	TArray<FPlayerNoteEntry> Notes = NoteReg->GetNotesForUid(Uid);
	if (Notes.IsEmpty())
	{
		Respond(ChannelId,
			FString::Printf(TEXT("📝 No notes on record for **%s** (`%s`)."),
				*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid));
		return;
	}

	FString Body;
	Body.Reserve(1400);
	Body += TEXT("```\n");

	const int32 ShowMax = FMath::Min(Notes.Num(), 10);
	for (int32 i = 0; i < ShowMax; ++i)
	{
		const FPlayerNoteEntry& N = Notes[i];
		const FString DateStr = N.NoteDate.ToString(TEXT("%Y-%m-%d %H:%M"));
		Body += FString::Printf(TEXT("[%s] %s — by %s: %s\n"),
			*DateStr,
			*FString::Printf(TEXT("#%lld"), N.Id),
			*BanDiscordHelpers::Truncate(N.AddedBy, 16),
			*BanDiscordHelpers::Truncate(N.Note, 60));
	}
	Body += TEXT("```");

	FString Header = FString::Printf(
		TEXT("**Notes for %s** (`%s`) — %d total\n"),
		*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid, Notes.Num());
	FString Msg = Header + Body;
	if (Msg.Len() > 1800)
		Msg = Msg.Left(1750) + TEXT("\n...(truncated)```");
	// Append player session lookup (EOS PUID + IP).
	Msg += BanDiscordHelpers::FormatPlayerLookup(this, Uid);

	Respond(ChannelId, Msg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /ban reason
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleReasonCommand(const TArray<FString>& Args,
                                                const FString& ChannelId)
{
	if (!CachedProvider) return;

	UBanDatabase* DB = BanDiscordHelpers::GetDB(this);
	if (!DB)
	{
		Respond(ChannelId,
			TEXT("❌ BanSystem is not available on this server."));
		return;
	}

	if (Args.IsEmpty())
	{
		Respond(ChannelId,
			TEXT("Usage: `/ban reason <UID>`"));
		return;
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	FBanEntry Entry;
	if (!DB->GetBanByUid(Uid, Entry))
	{
		Respond(ChannelId,
			FString::Printf(TEXT("✅ No ban record found for `%s`."), *Uid));
		return;
	}

	Respond(ChannelId,
		FString::Printf(TEXT("🔨 **%s** (`%s`) — ban reason: %s\n(Banned by: %s on %s UTC)"),
			*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
			*BanDiscordHelpers::EscapeMarkdown(Entry.Reason),
			*BanDiscordHelpers::EscapeMarkdown(Entry.BannedBy),
			*Entry.BanDate.ToString(TEXT("%Y-%m-%d %H:%M:%S"))));
}

// ─────────────────────────────────────────────────────────────────────────────
// /admin reloadconfig
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleReloadConfigCommand(const FString& ChannelId,
                                                      const FString& SenderName)
{
	if (!CachedProvider) return;

	Config = FBanBridgeConfig::Load();

	// Also refresh the cached FDiscordBridgeConfig fields so BuildPanelData()
	// and PostModerationLog() see any changes to ServerName / BanEventsChannelId.
	{
		const FDiscordBridgeConfig DiscordCfg = FDiscordBridgeConfig::LoadOrCreate();
		CachedDiscordServerName  = DiscordCfg.ServerName;
		CachedBanEventsChannelId = DiscordCfg.BanEventsChannelId;
	}

	UE_LOG(LogBanDiscord, Log,
		TEXT("BanDiscordSubsystem: Config reloaded by %s."), *SenderName);

	Respond(ChannelId,
		TEXT(":white_check_mark: BanBridge config reloaded."));
}

// ─────────────────────────────────────────────────────────────────────────────
// /mod ban
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleModBanCommand(const TArray<FString>& Args,
                                                const FString& ChannelId,
                                                const FString& SenderName)
{
	if (!CachedProvider) return;

	UBanDatabase* DB = BanDiscordHelpers::GetDB(this);
	if (!DB)
	{
		Respond(ChannelId,
			TEXT("❌ BanSystem is not available on this server."));
		return;
	}

	if (Args.IsEmpty())
	{
		Respond(ChannelId,
			TEXT("Usage: `/mod ban <PUID|name> [reason]`"));
		return;
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	// Use the ModBanDurationMinutes from BanChatCommandsConfig when available,
	// otherwise fall back to the classic 30-minute default.
	int32 DurationMinutes = 30;
	if (const UBanChatCommandsConfig* BccCfg = UBanChatCommandsConfig::Get())
		DurationMinutes = FMath::Max(1, BccCfg->ModBanDurationMinutes);

	const FString Reason = (Args.Num() > 1)
		? BanDiscordHelpers::JoinArgs(Args, 1)
		: TEXT("No reason given");

	FBanEntry Entry;
	Entry.Uid          = Uid;
	UBanDatabase::ParseUid(Uid, Entry.Platform, Entry.PlayerUID);
	Entry.PlayerName   = DisplayName;
	Entry.Reason       = Reason;
	Entry.BannedBy     = SenderName;
	const FDateTime TempBanNow1 = FDateTime::UtcNow();
	Entry.BanDate      = TempBanNow1;
	Entry.bIsPermanent = false;
	Entry.ExpireDate   = TempBanNow1 + FTimespan::FromMinutes(DurationMinutes);

	// HandleModBanCommand always issues a temporary ban; use AddBanSkipIfPermanentExists
	// to prevent silently downgrading an existing permanent ban.
	bool bModBanSkipped = false;
	if (!DB->AddBanSkipIfPermanentExists(Entry, bModBanSkipped))
	{
		if (bModBanSkipped)
		{
			Respond(ChannelId, FString::Printf(
				TEXT("⚠️ **%s** already has a permanent ban — the mod temp-ban was not applied."),
				*BanDiscordHelpers::EscapeMarkdown(DisplayName)));
		}
		else
		{
			Respond(ChannelId,
				TEXT("❌ Failed to write the ban to the database."));
		}
		return;
	}

	if (UWorld* World = GetGameInstance() ? GetGameInstance()->GetWorld() : nullptr)
		UBanEnforcer::KickConnectedPlayer(World, Uid, Entry.GetKickMessage());

	// Also ban the counterpart identifier (IP↔EOS).
	const TArray<FString> ExtraUids = BanDiscordHelpers::AddCounterpartBans(
		this, DB, Uid, DisplayName, Entry.Reason, SenderName,
		Entry.bIsPermanent, Entry.ExpireDate);

	FString Msg = FString::Printf(
		TEXT("🔨 **%s** (`%s`) has been banned for **%s** (mod action).\n"
		     "Expires: %s UTC\nReason: %s\nBanned by: %s"),
		*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
		*BanDiscordHelpers::FormatDuration(DurationMinutes),
		*Entry.ExpireDate.ToString(TEXT("%Y-%m-%d %H:%M:%S")),
		*BanDiscordHelpers::EscapeMarkdown(Reason),
		*BanDiscordHelpers::EscapeMarkdown(SenderName));
	Msg += BanDiscordHelpers::FormatPlayerLookup(this, Uid);

	if (ExtraUids.Num() > 0)
		Msg += FString::Printf(TEXT("\nAlso banned: `%s`"),
			*FString::Join(ExtraUids, TEXT("`, `")));

	UE_LOG(LogBanDiscord, Log,
		TEXT("BanDiscordSubsystem: %s modban %s (%s) for %d min. Reason: %s"),
		*SenderName, *DisplayName, *Uid, DurationMinutes, *Reason);

	// Write to audit log so Discord-issued mod bans appear alongside other bans.
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
			AuditLog->LogAction(TEXT("tempban"), Uid, DisplayName,
				GetCurrentAuditAdminUid(SenderName), SenderName, Reason);
	}

	FBanDiscordNotifier::NotifyBanCreated(Entry);
	Respond(ChannelId, Msg);
	PostModerationLog(Msg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /mod tempmute
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleTempMuteCommand(const TArray<FString>& Args,
                                                  const FString& ChannelId,
                                                  const FString& SenderName,
                                                  const FString& StaffPrefix)
{
	if (!CachedProvider) return;

	if (Args.Num() < 2)
	{
		Respond(ChannelId,
			TEXT("Usage: `/mod tempmute <PUID|name> <duration> [reason]`\nDuration: `30m`, `2h`, `1d`, `1w` or plain minutes"));
		return;
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	const int32 Minutes = ParseDurationMinutes(Args[1]);
	if (Minutes <= 0)
	{
		Respond(ChannelId,
			TEXT("❌ `<duration>` must be a positive value (e.g. `60`, `30m`, `2h`, `1d`)."));
		return;
	}

	UGameInstance* GI = GetGameInstance();
	UMuteRegistry* MuteReg = GI ? GI->GetSubsystem<UMuteRegistry>() : nullptr;
	if (!MuteReg)
	{
		Respond(ChannelId,
			TEXT("❌ Mute commands require the BanChatCommands mod to be installed."));
		return;
	}

	const FString Reason = (Args.Num() > 2)
		? BanDiscordHelpers::JoinArgs(Args, 2)
		: TEXT("Timed mute via Discord");

	MuteReg->MutePlayer(Uid, DisplayName, Reason, SenderName, Minutes);

	// Write to audit log so Discord-issued timed mutes appear alongside other mutes.
	if (UBanAuditLog* AuditLog = GI ? GI->GetSubsystem<UBanAuditLog>() : nullptr)
		AuditLog->LogAction(TEXT("mute"), Uid, DisplayName, GetCurrentAuditAdminUid(SenderName), SenderName, Reason);

	const FString DurStr = BanDiscordHelpers::FormatDuration(Minutes);
	const FString Msg = FString::Printf(
		TEXT("🔇 Timed mute applied to **%s** (`%s`) for **%s**.\nReason: %s\nMuted by: %s"),
		*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid, *DurStr,
		*BanDiscordHelpers::EscapeMarkdown(Reason),
		*BanDiscordHelpers::EscapeMarkdown(SenderName));
	Respond(ChannelId, Msg);
	SendInGameModerationNoticeToUid(Uid, FString::Printf(
		TEXT("%s Timed mute applied to @%s for %s. Reason: %s. By: %s."),
		*StaffPrefix, *DisplayName, *DurStr, *Reason, *SenderName));
	PostToPlayerModerationThread(DisplayName, Uid, Msg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /mod mutecheck
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleMuteCheckCommand(const TArray<FString>& Args,
                                                   const FString& ChannelId)
{
	if (!CachedProvider) return;

	if (Args.IsEmpty())
	{
		Respond(ChannelId,
			TEXT("Usage: `/mod mutecheck <PUID|name>`"));
		return;
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	UGameInstance* GI = GetGameInstance();
	UMuteRegistry* MuteReg = GI ? GI->GetSubsystem<UMuteRegistry>() : nullptr;
	if (!MuteReg)
	{
		Respond(ChannelId,
			TEXT("❌ Mute commands require the BanChatCommands mod to be installed."));
		return;
	}

	FMuteEntry Entry;
	if (!MuteReg->GetMuteEntry(Uid, Entry))
	{
		Respond(ChannelId,
			FString::Printf(TEXT("🔊 **%s** (`%s`) is **not currently muted**."),
				*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid));
		return;
	}

	FString ExpiryStr;
	if (Entry.bIsIndefinite)
	{
		ExpiryStr = TEXT("**indefinitely**");
	}
	else
	{
		const FTimespan Remaining = Entry.ExpireDate - FDateTime::UtcNow();
		const double RawMinsM = Remaining.GetTotalMinutes();
		const int64 TotalMinsI64 = (FMath::IsFinite(RawMinsM) && RawMinsM > 0.0)
			? FMath::Min(static_cast<int64>(RawMinsM), static_cast<int64>(INT32_MAX))
			: 0LL;
	const int32 TotalMins = static_cast<int32>(TotalMinsI64);
		ExpiryStr = FString::Printf(TEXT("for **%s** more (expires %s UTC)"),
			*BanDiscordHelpers::FormatDuration(TotalMins),
			*Entry.ExpireDate.ToString(TEXT("%Y-%m-%d %H:%M:%S")));
	}

	Respond(ChannelId,
		FString::Printf(TEXT("🔇 **%s** (`%s`) is muted %s.\nReason: %s\nMuted by: %s"),
			*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
			*ExpiryStr,
			*BanDiscordHelpers::EscapeMarkdown(Entry.Reason),
			*BanDiscordHelpers::EscapeMarkdown(Entry.MutedBy)));
}

// ─────────────────────────────────────────────────────────────────────────────
// /mod mutelist
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleMuteListCommand(const FString& ChannelId)
{
	if (!CachedProvider) return;

	UGameInstance* GI = GetGameInstance();
	UMuteRegistry* MuteReg = GI ? GI->GetSubsystem<UMuteRegistry>() : nullptr;
	if (!MuteReg)
	{
		Respond(ChannelId,
			TEXT("❌ Mute commands require the BanChatCommands mod to be installed."));
		return;
	}

	TArray<FMuteEntry> Mutes = MuteReg->GetAllMutes();
	if (Mutes.IsEmpty())
	{
		Respond(ChannelId, TEXT("🔊 No players are currently muted."));
		return;
	}

	FString Body;
	Body.Reserve(1400);
	Body += TEXT("```\n");
	Body += FString::Printf(TEXT("%-18s  %-30s  %-18s  %s\n"),
		TEXT("Name"), TEXT("UID (truncated)"), TEXT("Expires"), TEXT("Reason"));
	Body += BanDiscordHelpers::SepLine(80) + TEXT("\n");

	const int32 ShowMax = FMath::Min(Mutes.Num(), 15);
	for (int32 i = 0; i < ShowMax; ++i)
	{
		const FMuteEntry& M = Mutes[i];
		const FString NameSh   = BanDiscordHelpers::SanitizeForCodeBlock(BanDiscordHelpers::Truncate(M.PlayerName, 18));
		const FString UidSh    = BanDiscordHelpers::Truncate(M.Uid, 30);
		const FString ExpirySh = M.bIsIndefinite
			? TEXT("permanent")
			: M.ExpireDate.ToString(TEXT("%m-%d %H:%M UTC"));
		const FString ReasonSh = BanDiscordHelpers::SanitizeForCodeBlock(BanDiscordHelpers::Truncate(M.Reason, 24));
		Body += FString::Printf(TEXT("%-18s  %-30s  %-18s  %s\n"),
			*NameSh, *UidSh, *ExpirySh, *ReasonSh);
	}
	Body += TEXT("```");

	FString Header = FString::Printf(TEXT("**Muted Players — %d total**\n"), Mutes.Num());
	if (Mutes.Num() > ShowMax)
		Header += FString::Printf(TEXT("_(Showing first %d)_\n"), ShowMax);

	FString Msg = Header + Body;
	if (Msg.Len() > 1990)
		Msg = Msg.Left(1940) + TEXT("\n...(truncated)```");
	Respond(ChannelId, Msg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /mod tempunmute
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleTempUnmuteCommand(const TArray<FString>& Args,
                                                    const FString& ChannelId,
                                                    const FString& SenderName,
                                                    const FString& StaffPrefix)
{
	if (!CachedProvider) return;

	if (Args.IsEmpty())
	{
		Respond(ChannelId,
			TEXT("Usage: `/mod tempunmute <PUID|name>`"));
		return;
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	UGameInstance* GI = GetGameInstance();
	UMuteRegistry* MuteReg = GI ? GI->GetSubsystem<UMuteRegistry>() : nullptr;
	if (!MuteReg)
	{
		Respond(ChannelId,
			TEXT("❌ Mute commands require the BanChatCommands mod to be installed."));
		return;
	}

	FMuteEntry Entry;
	if (!MuteReg->GetMuteEntry(Uid, Entry))
	{
		Respond(ChannelId,
			FString::Printf(TEXT("⚠️ **%s** (`%s`) is not currently muted."),
				*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid));
		return;
	}

	if (Entry.bIsIndefinite)
	{
		Respond(ChannelId,
			FString::Printf(
				TEXT("❌ **%s** has an indefinite mute, not a timed one. Use `/mod unmute` instead."),
				*BanDiscordHelpers::EscapeMarkdown(DisplayName)));
		return;
	}

	MuteReg->UnmutePlayer(Uid);

	if (UBanAuditLog* AuditLog = GI ? GI->GetSubsystem<UBanAuditLog>() : nullptr)
		AuditLog->LogAction(TEXT("unmute"), Uid, DisplayName, GetCurrentAuditAdminUid(SenderName), SenderName, TEXT("Timed mute lifted early"));

	const FString UnmuteMsg = FString::Printf(
		TEXT("🔊 Timed mute lifted from **%s** (`%s`) early.\nUnmuted by: %s"),
		*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
		*BanDiscordHelpers::EscapeMarkdown(SenderName));
	Respond(ChannelId, UnmuteMsg);
	SendInGameModerationNoticeToUid(Uid, FString::Printf(
		TEXT("%s Timed mute lifted for @%s. By: %s."),
		*StaffPrefix, *DisplayName, *SenderName));
	PostToPlayerModerationThread(DisplayName, Uid, UnmuteMsg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /mod mutereason
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleMuteReasonCommand(const TArray<FString>& Args,
                                                    const FString& ChannelId,
                                                    const FString& SenderName,
                                                    const FString& StaffPrefix)
{
	if (!CachedProvider) return;

	if (Args.Num() < 2)
	{
		Respond(ChannelId,
			TEXT("Usage: `/mod mutereason <PUID|name> <new reason...>`"));
		return;
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	UGameInstance* GI = GetGameInstance();
	UMuteRegistry* MuteReg = GI ? GI->GetSubsystem<UMuteRegistry>() : nullptr;
	if (!MuteReg)
	{
		Respond(ChannelId,
			TEXT("❌ Mute commands require the BanChatCommands mod to be installed."));
		return;
	}

	const FString NewReason = BanDiscordHelpers::JoinArgs(Args, 1);

	if (!MuteReg->UpdateMuteReason(Uid, NewReason))
	{
		Respond(ChannelId,
			FString::Printf(TEXT("⚠️ **%s** (`%s`) is not currently muted."),
				*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid));
		return;
	}

	// Write to audit log so Discord-issued mute reason updates appear alongside in-game changes.
	if (UBanAuditLog* AuditLog = GI ? GI->GetSubsystem<UBanAuditLog>() : nullptr)
		AuditLog->LogAction(TEXT("mutereason"), Uid, DisplayName,
			GetCurrentAuditAdminUid(SenderName), SenderName, NewReason);

	const FString Msg = FString::Printf(
		TEXT("✏️ Mute reason updated for **%s** (`%s`).\nNew reason: %s\nUpdated by: %s"),
		*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
		*BanDiscordHelpers::EscapeMarkdown(NewReason),
		*BanDiscordHelpers::EscapeMarkdown(SenderName));
	Respond(ChannelId, Msg);
	SendInGameModerationNoticeToUid(Uid, FString::Printf(
		TEXT("%s Updated mute reason for @%s. New reason: %s. By: %s."),
		*StaffPrefix, *DisplayName, *NewReason, *SenderName));
	PostModerationLog(Msg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /mod stafflist
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleStaffListCommand(const FString& ChannelId)
{
	if (!CachedProvider) return;

	const UBanChatCommandsConfig* BccCfg = UBanChatCommandsConfig::Get();
	if (!BccCfg)
	{
		Respond(ChannelId,
			TEXT("❌ Staff list requires the BanChatCommands mod to be installed."));
		return;
	}

	UGameInstance* GI = GetGameInstance();
	UWorld* World = GI ? GI->GetWorld() : nullptr;
	if (!World)
	{
		Respond(ChannelId,
			TEXT("❌ No active game world found."));
		return;
	}

	TArray<FString> Admins;
	TArray<FString> Mods;

	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (!PC) continue;

		APlayerState* PS = PC->GetPlayerState<APlayerState>();
		if (!PS) continue;

		FString PUIDStr;
		if (const FUniqueNetIdRepl& Id = PS->GetUniqueId();
		    Id.IsValid() && Id.GetType() != FName(TEXT("NONE")))
		{
			PUIDStr = Id.ToString();
			// Strip the "EOS:" prefix for the config check.
			FString Platform, RawId;
			UBanDatabase::ParseUid(PUIDStr, Platform, RawId);
			if (Platform == TEXT("EOS"))
				PUIDStr = RawId;
		}
		else
		{
			PUIDStr = UBanEnforcer::ExtractEosPuidFromConnectionUrl(PC);
		}

		if (PUIDStr.IsEmpty()) continue;
		const FString CompoundUid = TEXT("EOS:") + PUIDStr.ToLower();
		const FString PlayerName  = PS->GetPlayerName();

		if (BccCfg->IsAdminUid(CompoundUid))
			Admins.Add(BanDiscordHelpers::EscapeMarkdown(PlayerName));
		else if (BccCfg->IsModeratorUid(CompoundUid))
			Mods.Add(BanDiscordHelpers::EscapeMarkdown(PlayerName));
	}

	if (Admins.IsEmpty() && Mods.IsEmpty())
	{
		Respond(ChannelId,
			TEXT("📋 No staff are currently online."));
		return;
	}

	FString Msg = TEXT("📋 **Online Staff:**\n");
	if (!Admins.IsEmpty())
		Msg += FString::Printf(TEXT("🛡️ **Admins:** %s\n"), *FString::Join(Admins, TEXT(", ")));
	if (!Mods.IsEmpty())
		Msg += FString::Printf(TEXT("🔧 **Moderators:** %s\n"), *FString::Join(Mods, TEXT(", ")));

	Respond(ChannelId, Msg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /mod staffchat
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleStaffChatCommand(const TArray<FString>& Args,
                                                   const FString& ChannelId,
                                                   const FString& SenderName)
{
	if (!CachedProvider) return;

	if (Args.IsEmpty())
	{
		Respond(ChannelId,
			TEXT("Usage: `/mod staffchat <message...>`"));
		return;
	}

	const UBanChatCommandsConfig* BccCfg = UBanChatCommandsConfig::Get();
	if (!BccCfg)
	{
		Respond(ChannelId,
			TEXT("❌ Staff chat requires the BanChatCommands mod to be installed."));
		return;
	}

	UGameInstance* GI = GetGameInstance();
	UWorld* World = GI ? GI->GetWorld() : nullptr;
	if (!World)
	{
		Respond(ChannelId,
			TEXT("❌ No active game world found."));
		return;
	}

	const FString Message = BanDiscordHelpers::JoinArgs(Args, 0);
	const FString Formatted = FString::Printf(TEXT("[Discord Staff] %s: %s"), *SenderName, *Message);

	int32 DeliveredTo = 0;
	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (!PC) continue;

		APlayerState* PS = PC->GetPlayerState<APlayerState>();
		if (!PS) continue;

		FString PUIDStr;
		if (const FUniqueNetIdRepl& Id = PS->GetUniqueId();
		    Id.IsValid() && Id.GetType() != FName(TEXT("NONE")))
		{
			PUIDStr = Id.ToString();
			FString Platform, RawId;
			UBanDatabase::ParseUid(PUIDStr, Platform, RawId);
			if (Platform == TEXT("EOS")) PUIDStr = RawId;
		}
		else
		{
			PUIDStr = UBanEnforcer::ExtractEosPuidFromConnectionUrl(PC);
		}

		if (PUIDStr.IsEmpty()) continue;
		const FString CompoundUid = TEXT("EOS:") + PUIDStr.ToLower();
		if (BccCfg->IsAdminUid(CompoundUid) || BccCfg->IsModeratorUid(CompoundUid))
		{
			PC->ClientMessage(Formatted);
			++DeliveredTo;
		}
	}

	Respond(ChannelId,
		FString::Printf(TEXT("📨 Staff message delivered to **%d** online staff member(s)."), DeliveredTo));
}

// ─────────────────────────────────────────────────────────────────────────────
// Moderation log
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::PostModerationLog(const FString& Message) const
{
	if (!CachedProvider) return;

	FString TargetChannelId = Config.ModerationLogChannelId;
	if (TargetChannelId.IsEmpty() || TargetChannelId == TEXT("0"))
	{
		// Fall back to FDiscordBridgeConfig::BanEventsChannelId (cached at
		// Initialize() to avoid a disk read on every moderation log entry).
		TargetChannelId = CachedBanEventsChannelId;
	}
	if (TargetChannelId.IsEmpty() || TargetChannelId == TEXT("0")) return;

	CachedProvider->SendDiscordChannelMessage(TargetChannelId, Message);
}

// ─────────────────────────────────────────────────────────────────────────────
// /appeal list
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleAppealsCommand(const FString& ChannelId)
{
	if (!CachedProvider) return;

	UBanAppealRegistry* Registry =
		GetGameInstance() ? GetGameInstance()->GetSubsystem<UBanAppealRegistry>() : nullptr;

	if (!Registry)
	{
		Respond(ChannelId,
			TEXT(":x: BanAppealRegistry is not available (BanSystem may not be installed)."));
		return;
	}

	const TArray<FBanAppealEntry> Appeals = Registry->GetAllAppeals();

	if (Appeals.IsEmpty())
	{
		Respond(ChannelId,
			TEXT(":white_check_mark: No pending ban appeals."));
		return;
	}

	constexpr int32 MaxShow = 10;
	const int32 TotalCount  = Appeals.Num();
	const int32 ShowCount   = FMath::Min(TotalCount, MaxShow);

	FString Reply = FString::Printf(
		TEXT(":scales: **Pending Ban Appeals (%d):**\n"), TotalCount);

	for (int32 i = 0; i < ShowCount; ++i)
	{
		const FBanAppealEntry& A = Appeals[i];
		const FString DateStr = A.SubmittedAt.ToString(TEXT("%Y-%m-%d"));
		const FString Reason  = A.Reason.IsEmpty() ? TEXT("(none)") : A.Reason.Left(100);
		const FString Contact = A.ContactInfo.IsEmpty() ? TEXT("(none)") : A.ContactInfo.Left(80);

		Reply += FString::Printf(
			TEXT("`#%lld` uid=%s | contact: %s | submitted: %s | reason: %s\n"),
			A.Id,
			*BanDiscordHelpers::EscapeMarkdown(A.Uid),
			*BanDiscordHelpers::EscapeMarkdown(Contact),
			*DateStr,
			*BanDiscordHelpers::EscapeMarkdown(Reason));
	}

	if (TotalCount > MaxShow)
	{
		Reply += FString::Printf(TEXT("*(+%d more)*"), TotalCount - MaxShow);
	}

	Respond(ChannelId, Reply.TrimEnd());
}

// ─────────────────────────────────────────────────────────────────────────────
// /appeal dismiss <id>
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleDismissAppealCommand(const TArray<FString>& Args,
                                                       const FString& ChannelId,
                                                       const FString& SenderName)
{
	if (!CachedProvider) return;

	if (Args.IsEmpty())
	{
		Respond(ChannelId,
			TEXT("Usage: `/appeal dismiss <id>`"));
		return;
	}

	// Guard against int64 overflow: Atoi64 is undefined for strings longer than
	// 19 digits, and a 19-digit string can still exceed INT64_MAX.  Same check
	// used by HandleClearWarnByIdCommand and BanRestApi::ParseInt64Param.
	{
		const int32 IdLen = Args[0].Len();
		if (!Args[0].IsNumeric() || IdLen > 19 ||
			(IdLen == 19 && Args[0] > TEXT("9223372036854775807")))
		{
			Respond(ChannelId,
				TEXT(":x: Invalid appeal ID. Must be a positive integer."));
			return;
		}
	}

	const int64 AppealId = FCString::Atoi64(*Args[0]);
	if (AppealId <= 0)
	{
		Respond(ChannelId,
			TEXT(":x: Invalid appeal ID. Must be a positive integer."));
		return;
	}

	UBanAppealRegistry* Registry =
		GetGameInstance() ? GetGameInstance()->GetSubsystem<UBanAppealRegistry>() : nullptr;

	if (!Registry)
	{
		Respond(ChannelId,
			TEXT(":x: BanAppealRegistry is not available (BanSystem may not be installed)."));
		return;
	}

	// Check existence BEFORE mutating registry state so we do not fire
	// ReviewAppeal on a non-existent ID and then respond with a failure.
	const FBanAppealEntry DismissEntry = Registry->GetAppealById(AppealId);
	if (DismissEntry.Uid.IsEmpty())
	{
		Respond(ChannelId,
			FString::Printf(TEXT(":x: No appeal found with ID `%lld`."), AppealId));
		return;
	}

	// Record the dismissal in the registry before deleting so the audit trail is preserved.
	Registry->ReviewAppeal(AppealId, EAppealStatus::Dismissed, SenderName, TEXT(""));
	Registry->DeleteAppeal(AppealId);

	UE_LOG(LogBanDiscord, Log,
	       TEXT("BanDiscordSubsystem: Appeal #%lld dismissed by '%s'."),
	       AppealId, *SenderName);

	Respond(ChannelId,
		FString::Printf(TEXT(":white_check_mark: Appeal `#%lld` dismissed."), AppealId));

	// Notify the moderation webhook — build a copy with the final reviewed status
	// so the embed shows "Dismissed" rather than "Pending".
	FBanAppealEntry ReviewedEntry = DismissEntry;
	ReviewedEntry.Status     = EAppealStatus::Dismissed;
	ReviewedEntry.ReviewedBy = SenderName;
	FBanDiscordNotifier::NotifyAppealReviewed(ReviewedEntry);
}

// ─────────────────────────────────────────────────────────────────────────────
// /appeal approve <id>
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleAppealApproveCommand(const TArray<FString>& Args,
                                                       const FString& ChannelId,
                                                       const FString& SenderName)
{
	if (!CachedProvider) return;

	if (Args.IsEmpty())
	{
		Respond(ChannelId,
			TEXT("Usage: `/appeal approve <id> [note...]`"));
		return;
	}

	// Guard against int64 overflow: Atoi64 is undefined for strings longer than
	// 19 digits, and a 19-digit string can still exceed INT64_MAX.  Same check
	// used by HandleClearWarnByIdCommand and BanRestApi::ParseInt64Param.
	{
		const int32 IdLen = Args[0].Len();
		if (!Args[0].IsNumeric() || IdLen > 19 ||
			(IdLen == 19 && Args[0] > TEXT("9223372036854775807")))
		{
			Respond(ChannelId,
				TEXT(":x: Invalid appeal ID. Must be a positive integer."));
			return;
		}
	}

	const int64 AppealId = FCString::Atoi64(*Args[0]);
	if (AppealId <= 0)
	{
		Respond(ChannelId,
			TEXT(":x: Invalid appeal ID. Must be a positive integer."));
		return;
	}

	FString ReviewNote;
	for (int32 i = 1; i < Args.Num(); ++i)
	{
		if (i > 1) ReviewNote += TEXT(" ");
		ReviewNote += Args[i];
	}

	UGameInstance* GI = GetGameInstance();
	UBanAppealRegistry* Registry = GI ? GI->GetSubsystem<UBanAppealRegistry>() : nullptr;
	if (!Registry)
	{
		Respond(ChannelId,
			TEXT(":x: BanAppealRegistry is not available (BanSystem may not be installed)."));
		return;
	}

	// Capture the entry BEFORE calling ReviewAppeal — GetAppealById after ReviewAppeal
	// can return a default-constructed empty entry if a concurrent delete races it.
	const FBanAppealEntry Entry = Registry->GetAppealById(AppealId);
	if (Entry.Uid.IsEmpty())
	{
		Respond(ChannelId,
			FString::Printf(TEXT(":x: No appeal found with ID `%lld`."), AppealId));
		return;
	}

	// Auto-unban the player on approval.
	// Use IsCurrentlyBannedByAnyId so that appeals submitted with a Discord:<id>
	// UID are matched against the EOS:<puid> ban record via its LinkedUids, then
	// remove by the primary ban UID + any counterparts — same pattern as /unban.
	UBanDatabase* DB = BanDiscordHelpers::GetDB(this);
	bool bUnbanned = false;
	FString UnbannedUid = Entry.Uid;
	if (DB && !Entry.Uid.IsEmpty())
	{
		FBanEntry BanRecord;
		if (DB->IsCurrentlyBannedByAnyId(Entry.Uid, BanRecord))
		{
			UnbannedUid = BanRecord.Uid;
			// Use the atomic RemoveBanByUid overload so LinkedUids are captured
			// within the same mutex scope as the removal, eliminating the TOCTOU
			// window where a concurrent action could modify LinkedUids between
			// IsCurrentlyBannedByAnyId and RemoveBanByUid (same race fixed for
			// ExecutePanelUnban in R22-A and the ticket appeal path in R23-A).
			FBanEntry RemovedBan;
			bUnbanned = DB->RemoveBanByUid(BanRecord.Uid, RemovedBan);
			if (bUnbanned)
			{
				BanDiscordHelpers::RemoveCounterpartBans(this, DB, RemovedBan.Uid, RemovedBan.LinkedUids);
				FBanDiscordNotifier::NotifyBanRemoved(RemovedBan.Uid, RemovedBan.PlayerName, SenderName);
			}
		}
		else
		{
			// Fallback: direct removal covers edge cases where the ban was stored
			// with a Discord UID (e.g. manually added entries).
			// Use the two-arg overload so we can fire NotifyBanRemoved with the
			// player name and clean up any linked counterpart bans.
			FBanEntry RemovedFallback;
			bUnbanned = DB->RemoveBanByUid(Entry.Uid, RemovedFallback);
			if (bUnbanned)
			{
				BanDiscordHelpers::RemoveCounterpartBans(this, DB, RemovedFallback.Uid, RemovedFallback.LinkedUids);
				FBanDiscordNotifier::NotifyBanRemoved(RemovedFallback.Uid, RemovedFallback.PlayerName, SenderName);
			}
		}
	}

	// Mark the appeal as Approved in the registry.  Must be called after the unban
	// so that the entry's status reflects the final outcome.  Mirrors the ReviewAppeal
	// call in HandleAppealDenyCommand (line ~4045) and BanRestApi (POST /appeals/:id/review).
	if (!Registry->ReviewAppeal(AppealId, EAppealStatus::Approved, SenderName, ReviewNote))
	{
		UE_LOG(LogBanDiscord, Warning,
			TEXT("BanDiscordSubsystem: ReviewAppeal(Approved) returned false for appeal #%lld"), AppealId);
	}

	const FString NoteStr = ReviewNote.IsEmpty() ? TEXT("") : FString::Printf(TEXT(" Note: %s"), *ReviewNote);
	const FString Msg = bUnbanned
		? FString::Printf(TEXT(":white_check_mark: Appeal `#%lld` **approved** — ban for `%s` removed.%s"), AppealId, *UnbannedUid, *NoteStr)
		: FString::Printf(TEXT(":white_check_mark: Appeal `#%lld` **approved** — no active ban found for `%s`.%s"), AppealId, *Entry.Uid, *NoteStr);

	Respond(ChannelId, Msg);
	PostModerationLog(FString::Printf(TEXT("%s approved appeal #%lld (uid=%s)%s"), *SenderName, AppealId, *UnbannedUid, *NoteStr));

	// Build a reviewed-entry copy with the correct final status so the webhook
	// does not show the pre-ReviewAppeal "Pending" value.
	{
		FBanAppealEntry ReviewedEntry = Entry;
		ReviewedEntry.Status     = EAppealStatus::Approved;
		ReviewedEntry.ReviewedBy = SenderName;
		ReviewedEntry.ReviewNote = ReviewNote;
		FBanDiscordNotifier::NotifyAppealReviewed(ReviewedEntry);
	}

	// Auto-close the associated ban-appeal ticket channel (if still open).
	// The Uid stored in the entry is "Discord:<userId>"; extract the user ID.
	if (Entry.Uid.StartsWith(TEXT("Discord:")))
	{
		const FString AppealDiscordId = Entry.Uid.Mid(FCString::Strlen(TEXT("Discord:")));
		if (!AppealDiscordId.IsEmpty())
		{
			if (GI)
			{
				if (UTicketSubsystem* TicketSys = GI->GetSubsystem<UTicketSubsystem>())
				{
					const FString Resolution = FString::Printf(
						TEXT(":white_check_mark: **Appeal approved** by %s. %s\n"
						     "This ticket has been automatically closed."),
						*BanDiscordHelpers::EscapeMarkdown(SenderName), *NoteStr);
					TicketSys->CloseAppealTicketForOpener(AppealDiscordId, Resolution);
				}
			}
		}
	}

	UE_LOG(LogBanDiscord, Log,
	       TEXT("BanDiscordSubsystem: Appeal #%lld approved by '%s' (uid=%s, unbanned=%s)."),
	       AppealId, *SenderName, *UnbannedUid, bUnbanned ? TEXT("yes") : TEXT("no"));
}

// ─────────────────────────────────────────────────────────────────────────────
// /appeal deny <id>
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleAppealDenyCommand(const TArray<FString>& Args,
                                                    const FString& ChannelId,
                                                    const FString& SenderName)
{
	if (!CachedProvider) return;

	if (Args.IsEmpty())
	{
		Respond(ChannelId,
			TEXT("Usage: `/appeal deny <id> [note...]`"));
		return;
	}

	// Guard against int64 overflow: Atoi64 is undefined for strings longer than
	// 19 digits, and a 19-digit string can still exceed INT64_MAX.  Same check
	// used by HandleClearWarnByIdCommand and BanRestApi::ParseInt64Param.
	{
		const int32 IdLen = Args[0].Len();
		if (!Args[0].IsNumeric() || IdLen > 19 ||
			(IdLen == 19 && Args[0] > TEXT("9223372036854775807")))
		{
			Respond(ChannelId,
				TEXT(":x: Invalid appeal ID. Must be a positive integer."));
			return;
		}
	}

	const int64 AppealId = FCString::Atoi64(*Args[0]);
	if (AppealId <= 0)
	{
		Respond(ChannelId,
			TEXT(":x: Invalid appeal ID. Must be a positive integer."));
		return;
	}

	FString ReviewNote;
	for (int32 i = 1; i < Args.Num(); ++i)
	{
		if (i > 1) ReviewNote += TEXT(" ");
		ReviewNote += Args[i];
	}

	UGameInstance* GI = GetGameInstance();
	UBanAppealRegistry* Registry = GI ? GI->GetSubsystem<UBanAppealRegistry>() : nullptr;
	if (!Registry)
	{
		Respond(ChannelId,
			TEXT(":x: BanAppealRegistry is not available (BanSystem may not be installed)."));
		return;
	}

	// Capture the entry BEFORE calling ReviewAppeal to avoid a TOCTOU where
	// GetAppealById after ReviewAppeal returns empty if a concurrent delete races it.
	const FBanAppealEntry Entry = Registry->GetAppealById(AppealId);
	if (Entry.Uid.IsEmpty())
	{
		Respond(ChannelId,
			FString::Printf(TEXT(":x: No appeal found with ID `%lld`."), AppealId));
		return;
	}

	// Use ReviewAppeal to record the denial with status/note.
	if (!Registry->ReviewAppeal(AppealId, EAppealStatus::Denied, SenderName, ReviewNote))
	{
		Respond(ChannelId,
			FString::Printf(TEXT(":x: No appeal found with ID `%lld`."), AppealId));
		return;
	}
	const FString NoteStr = ReviewNote.IsEmpty() ? TEXT("") : FString::Printf(TEXT(" Note: %s"), *ReviewNote);
	Respond(ChannelId,
		FString::Printf(TEXT(":x: Appeal `#%lld` **denied**.%s"), AppealId, *NoteStr));
	PostModerationLog(FString::Printf(TEXT("%s denied appeal #%lld (uid=%s)%s"), *SenderName, AppealId, *Entry.Uid, *NoteStr));

	// Build a reviewed-entry copy with the correct final status so the webhook
	// does not show the pre-ReviewAppeal "Pending" value.
	{
		FBanAppealEntry ReviewedEntry = Entry;
		ReviewedEntry.Status     = EAppealStatus::Denied;
		ReviewedEntry.ReviewedBy = SenderName;
		ReviewedEntry.ReviewNote = ReviewNote;
		FBanDiscordNotifier::NotifyAppealReviewed(ReviewedEntry);
	}

	// Auto-close the associated ban-appeal ticket channel (if still open).
	if (Entry.Uid.StartsWith(TEXT("Discord:")))
	{
		const FString AppealDiscordId = Entry.Uid.Mid(FCString::Strlen(TEXT("Discord:")));
		if (!AppealDiscordId.IsEmpty())
		{
			if (GI)
			{
				if (UTicketSubsystem* TicketSys = GI->GetSubsystem<UTicketSubsystem>())
				{
					const FString Resolution = FString::Printf(
						TEXT(":x: **Appeal denied** by %s.%s\n"
						     "This ticket has been automatically closed."),
						*BanDiscordHelpers::EscapeMarkdown(SenderName), *NoteStr);
					TicketSys->CloseAppealTicketForOpener(AppealDiscordId, Resolution);
				}
			}
		}
	}

	UE_LOG(LogBanDiscord, Log,
	       TEXT("BanDiscordSubsystem: Appeal #%lld denied by '%s'."), AppealId, *SenderName);
}

// ─────────────────────────────────────────────────────────────────────────────
// /player playtime
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandlePlaytimeCommand(const TArray<FString>& Args,
                                                  const FString& ChannelId)
{
	if (!CachedProvider) return;

	if (Args.IsEmpty())
	{
		Respond(ChannelId, TEXT("Usage: `/player playtime <player|PUID>`"));
		return;
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, FString::Printf(TEXT(":x: %s"), *ErrorMsg));
		return;
	}

	UGameInstance* GI = GetGameInstance();
	UPlayerSessionRegistry* Registry = GI ? GI->GetSubsystem<UPlayerSessionRegistry>() : nullptr;
	if (!Registry)
	{
		Respond(ChannelId,
			TEXT(":x: PlayerSessionRegistry is not available (BanSystem may not be installed)."));
		return;
	}

	FPlayerSessionRecord Record;
	const bool bFound = Registry->FindByUid(Uid, Record);

	FString Reply;
	if (!bFound || Record.LastSeen.IsEmpty())
	{
		Reply = FString::Printf(TEXT(":hourglass: No session record found for **%s** (`%s`)."),
			*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid);
	}
	else
	{
		// Check if the player is currently online by UID (more reliable than display name).
		bool bOnline = false;
		if (UWorld* World = GI->GetWorld())
		{
			for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
			{
				APlayerController* PC = It->Get();
				if (PC && BanDiscordHelpers::GetControllerUid(PC).Equals(Uid, ESearchCase::IgnoreCase))
				{
					bOnline = true;
					break;
				}
			}
		}

		Reply = FString::Printf(
			TEXT(":clock3: **%s** (`%s`)\n• **Last Seen:** %s UTC\n• **Status:** %s"),
			*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
			*BanDiscordHelpers::EscapeMarkdown(Record.LastSeen),
			bOnline ? TEXT("🟢 Online") : TEXT("🔴 Offline"));
	}

	Respond(ChannelId, Reply);
}

// ─────────────────────────────────────────────────────────────────────────────
// /admin say  — Discord → game broadcast as [ADMIN]
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleSayCommand(const TArray<FString>& Args,
                                             const FString& ChannelId,
                                             const FString& SenderName)
{
	if (!CachedProvider) return;

	if (Args.IsEmpty())
	{
		Respond(ChannelId, TEXT("Usage: `/admin say <message...>` — broadcasts as [ADMIN] in-game"));
		return;
	}

	UGameInstance* GI = GetGameInstance();
	UWorld* World = GI ? GI->GetWorld() : nullptr;
	if (!World)
	{
		Respond(ChannelId, TEXT(":x: No active game world found."));
		return;
	}

	const FString Message   = BanDiscordHelpers::JoinArgs(Args, 0);
	const FString Formatted = FString::Printf(TEXT("[ADMIN] %s: %s"), *SenderName, *Message);

	int32 Delivered = 0;
	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
	{
		if (APlayerController* PC = It->Get())
		{
			PC->ClientMessage(Formatted);
			++Delivered;
		}
	}

	Respond(ChannelId,
		FString::Printf(TEXT("📢 Admin broadcast delivered to **%d** player(s): *%s*"),
			Delivered, *BanDiscordHelpers::EscapeMarkdown(Message)));

	PostModerationLog(FString::Printf(TEXT("%s broadcast [ADMIN]: %s"), *SenderName, *Message));
}

// ─────────────────────────────────────────────────────────────────────────────
// /admin poll  — create a Discord poll embed
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandlePollCommand(const TArray<FString>& Args,
                                              const FString& ChannelId)
{
	if (!CachedProvider) return;

	// Build full text by joining args then splitting on "|".
	const FString FullText = BanDiscordHelpers::JoinArgs(Args, 0);
	TArray<FString> Parts;
	FullText.ParseIntoArray(Parts, TEXT("|"), true);
	for (FString& P : Parts) P.TrimStartAndEndInline();

	if (Parts.Num() < 3)
	{
		Respond(ChannelId,
			TEXT("Usage: `/admin poll <question> | <optionA> | <optionB> [| <optionC> ...]`\n"
			     "Example: `/admin poll Restart tonight? | Yes | No | Maybe`"));
		return;
	}

	const FString Question = Parts[0];
	const TArray<FString> Options(Parts.GetData() + 1, Parts.Num() - 1);

	if (Options.Num() < 2 || Options.Num() > 10)
	{
		Respond(ChannelId, TEXT(":x: A poll requires between 2 and 10 options."));
		return;
	}

	// Number emoji labels for options.
	static const TCHAR* NumEmoji[] = {
		TEXT("1️⃣"), TEXT("2️⃣"), TEXT("3️⃣"), TEXT("4️⃣"), TEXT("5️⃣"),
		TEXT("6️⃣"), TEXT("7️⃣"), TEXT("8️⃣"), TEXT("9️⃣"), TEXT("🔟")
	};

	FString FieldsJson;
	for (int32 i = 0; i < Options.Num(); ++i)
	{
		if (i > 0) FieldsJson += TEXT(",");
		const FString Label = FString::Printf(TEXT("%s %s"), NumEmoji[i],
			*BanDiscordHelpers::Truncate(Options[i], 1024));
		FieldsJson += FString::Printf(
			TEXT("{\"name\":\"%s\",\"value\":\"React with %s to vote\",\"inline\":false}"),
			*BanDiscordHelpers::JsonEscape(Label),
			NumEmoji[i]);
	}

	// Assemble embed payload.
	const FString EmbedJson = FString::Printf(
		TEXT("{\"embeds\":[{\"title\":\"📊 %s\",\"color\":5793266,\"fields\":[%s],"
		     "\"footer\":{\"text\":\"React to vote! Results visible on the reactions.\"},"
		     "\"timestamp\":\"%s\"}]}"),
		*BanDiscordHelpers::JsonEscape(Question),
		*FieldsJson,
		*FDateTime::UtcNow().ToIso8601());

	// Send as a proper JSON body so Discord renders the embed.
	// Respond() wraps its argument in {"content":"..."} which would display the
	// embed JSON as literal text instead of rendering it.
	TSharedPtr<FJsonObject> BodyObj;
	TSharedRef<TJsonReader<>> BodyReader = TJsonReaderFactory<>::Create(EmbedJson);
	if (FJsonSerializer::Deserialize(BodyReader, BodyObj) && BodyObj.IsValid())
	{
		CachedProvider->SendMessageBodyToChannel(ChannelId, BodyObj);
		if (!PendingInteractionToken.IsEmpty())
			CachedProvider->FollowUpInteraction(PendingInteractionToken,
				TEXT("✅ Poll posted."), /*bEphemeral=*/true);
	}
	else
	{
		Respond(ChannelId, TEXT(":x: Failed to build poll embed."));
	}
}

// ─────────────────────────────────────────────────────────────────────────────
// Thread-per-player moderation log
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::PostToPlayerModerationThread(const FString& PlayerName,
                                                         const FString& Uid,
                                                         const FString& Message)
{
	if (!CachedProvider) return;
	if (Config.ModerationLogChannelId.IsEmpty()) return;
	if (Config.ModerationLogChannelId == TEXT("0")) return;

	// Fast path: a thread for this player was already created in a prior call.
	if (const FString* CachedId = PlayerThreadIdCache.Find(Uid))
	{
		CachedProvider->SendDiscordChannelMessage(*CachedId, Message);
		return;
	}

	// Build the thread name: "PlayerName [EOS:xxx]" truncated to 100 chars.
	const FString ThreadName = BanDiscordHelpers::Truncate(
		FString::Printf(TEXT("%s [%s]"), *PlayerName, *Uid), 100);

	// Post a prefixed fallback to the main mod-log channel immediately so the
	// message is never lost, even if thread creation fails or is slow.
	const FString Prefixed = FString::Printf(
		TEXT("**[%s]** %s"), *BanDiscordHelpers::EscapeMarkdown(ThreadName), *Message);
	CachedProvider->SendDiscordChannelMessage(Config.ModerationLogChannelId, Prefixed);

	// Asynchronously create a Discord thread for this player so that future
	// moderation events are grouped per-player rather than posted inline.
	const FString ChanId = Config.ModerationLogChannelId;
	const FString UidKey = Uid;
	TWeakObjectPtr<UBanDiscordSubsystem> WeakThis(this);

	const FString MessageCopy = Message;
	CachedProvider->CreateDiscordThread(ChanId, ThreadName,
		[WeakThis, UidKey, MessageCopy](const FString& ThreadId)
		{
			UBanDiscordSubsystem* Self = WeakThis.Get();
			if (Self && !ThreadId.IsEmpty())
			{
				// Cache the thread so subsequent events go straight into it.
				Self->PlayerThreadIdCache.Add(UidKey, ThreadId);
				// Re-post the triggering message into the new thread so the first
				// moderation event is not absent from the per-player thread.
				if (Self->CachedProvider)
					Self->CachedProvider->SendDiscordChannelMessage(ThreadId, MessageCopy);
				UE_LOG(LogBanDiscord, Log,
				       TEXT("BanDiscordSubsystem: Created mod-log thread %s for player uid=%s."),
				       *ThreadId, *UidKey);
			}
		});
}

// ─────────────────────────────────────────────────────────────────────────────
// /ban schedule <player|PUID> <delay> [banDuration] [reason...]
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleScheduleBanCommand(const TArray<FString>& Args,
                                                     const FString& ChannelId,
                                                     const FString& SenderName)
{
	if (!CachedProvider) return;

	if (Args.Num() < 2)
	{
		Respond(ChannelId,
			TEXT("Usage: `/ban schedule <player|PUID> <delay> [banDuration] [reason...]`\n"
			     "Example: `/ban schedule BadPlayer 2h 1d Griefing`"));
		return;
	}

	UGameInstance* GI = GetGameInstance();
	UScheduledBanRegistry* SchReg = GI ? GI->GetSubsystem<UScheduledBanRegistry>() : nullptr;
	if (!SchReg)
	{
		Respond(ChannelId, TEXT(":x: ScheduledBanRegistry unavailable."));
		return;
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	// Parse delay.
	const int32 DelayMinutes = UBanDiscordSubsystem::ParseDurationMinutes(Args[1]);
	if (DelayMinutes <= 0)
	{
		Respond(ChannelId,
			FString::Printf(TEXT(":x: Invalid delay `%s`. Use format like `30m`, `2h`, `1d`."), *Args[1]));
		return;
	}

	// Optional ban duration.
	int32 BanDurationMinutes = 0;
	int32 ReasonIdx = 2;
	if (Args.Num() > 2)
	{
		const int32 Parsed = UBanDiscordSubsystem::ParseDurationMinutes(Args[2]);
		if (Parsed > 0)
		{
			BanDurationMinutes = Parsed;
			ReasonIdx = 3;
		}
		// ParseDurationMinutes("perm") returns 0 — treat as permanent.
		else if (Args[2] == TEXT("perm") || Args[2] == TEXT("permanent") || Args[2] == TEXT("0"))
		{
			BanDurationMinutes = 0;
			ReasonIdx = 3;
		}
	}

	FString Reason = TEXT("Scheduled ban");
	if (ReasonIdx < Args.Num())
		Reason = BanDiscordHelpers::JoinArgs(Args, ReasonIdx);

	const FDateTime EffectiveAt = FDateTime::UtcNow() + FTimespan::FromMinutes(DelayMinutes);
	FScheduledBanEntry Entry = SchReg->AddScheduled(Uid, DisplayName, Reason, SenderName, EffectiveAt, BanDurationMinutes);

	const FString DurStr = BanDurationMinutes == 0
		? TEXT("permanent")
		: BanDiscordHelpers::FormatDuration(BanDurationMinutes);
	Respond(ChannelId,
		FString::Printf(TEXT(":calendar: Scheduled ban **#%lld** for `%s` in **%s** (effective %s). Duration: %s. Reason: %s"),
			Entry.Id, *BanDiscordHelpers::EscapeMarkdown(DisplayName), *BanDiscordHelpers::FormatDuration(DelayMinutes),
			*EffectiveAt.ToString(TEXT("%Y-%m-%d %H:%M:%S")), *DurStr,
			*BanDiscordHelpers::EscapeMarkdown(Reason)));
}

// ─────────────────────────────────────────────────────────────────────────────
// /ban quick <templateSlug> <player|PUID>
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleQBanCommand(const TArray<FString>& Args,
                                              const FString& ChannelId,
                                              const FString& SenderName)
{
	if (!CachedProvider) return;

	const UBanSystemConfig* SysCfg = UBanSystemConfig::Get();
	if (!SysCfg || SysCfg->BanTemplates.IsEmpty())
	{
		Respond(ChannelId,
		TEXT(":x: No ban templates configured (`BanTemplates=` in DefaultBanSystem.ini)."));
		return;
	}

	// Parse pipe-delimited template strings into FBanTemplate structs.
	const TArray<FBanTemplate> Templates = FBanTemplate::ParseTemplates(SysCfg->BanTemplates);

	if (Args.IsEmpty())
	{
		FString List = TEXT("**Available ban templates:**\n");
		for (const FBanTemplate& T : Templates)
		{
			const FString DurStr = T.DurationMinutes == 0 ? TEXT("permanent") : BanDiscordHelpers::FormatDuration(T.DurationMinutes);
			List += FString::Printf(TEXT("`%s` — %s — %s\n"), *T.Slug, *DurStr, *T.Reason);
		}
		Respond(ChannelId, List);
		return;
	}

	if (Args.Num() < 2)
	{
		Respond(ChannelId,
		TEXT("Usage: `/ban quick <templateSlug> <player|PUID>`"));
		return;
	}

	const FString Slug = Args[0].ToLower();
	const FBanTemplate* Template = nullptr;
	for (const FBanTemplate& T : Templates)
	{
		if (T.Slug.ToLower() == Slug) { Template = &T; break; }
	}
	if (!Template)
	{
		Respond(ChannelId,
		FString::Printf(TEXT(":x: Unknown template `%s`. Use `/ban quick` to list templates."), *Slug));
		return;
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[1], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	UBanDatabase* DB = BanDiscordHelpers::GetDB(this);
	if (!DB)
	{
		Respond(ChannelId, TEXT(":x: Database unavailable."));
		return;
	}

	FBanEntry Ban;
	Ban.Uid        = Uid;
	UBanDatabase::ParseUid(Uid, Ban.Platform, Ban.PlayerUID);
	Ban.PlayerName      = DisplayName;
	Ban.Reason          = Template->Reason;
	Ban.BannedBy        = SenderName;
	const FDateTime TemplateBanNow = FDateTime::UtcNow();
	Ban.BanDate         = TemplateBanNow;
	Ban.Category        = Template->Category;
	Ban.bIsPermanent    = (Template->DurationMinutes <= 0);
	Ban.ExpireDate      = Ban.bIsPermanent
	? FDateTime(0)
	: TemplateBanNow + FTimespan::FromMinutes(Template->DurationMinutes);

	// For temporary templates, use AddBanSkipIfPermanentExists to prevent
	// silently downgrading an existing permanent ban.
	bool bQBanSkipped = false;
	const bool bQBanAdded = Ban.bIsPermanent
		? DB->AddBan(Ban)
		: DB->AddBanSkipIfPermanentExists(Ban, bQBanSkipped);
	if (!bQBanAdded)
	{
		if (bQBanSkipped)
		{
			Respond(ChannelId, FString::Printf(
				TEXT(":warning: **%s** already has a permanent ban — the template ban was not applied."),
				*BanDiscordHelpers::EscapeMarkdown(DisplayName)));
		}
		else
		{
			Respond(ChannelId, TEXT(":x: Failed to apply ban."));
		}
		return;
	}

	UGameInstance* GI = GetGameInstance();
	if (UWorld* W = GI ? GI->GetWorld() : nullptr)
	UBanEnforcer::KickConnectedPlayer(W, Uid, Ban.GetKickMessage());

	// Also ban counterpart identifiers (IP↔EOS).
	BanDiscordHelpers::AddCounterpartBans(this, DB, Uid, DisplayName,
	Template->Reason, SenderName, Ban.bIsPermanent, Ban.ExpireDate);

	FBanDiscordNotifier::NotifyBanCreated(Ban);
	if (UGameInstance* GI2 = GetGameInstance())
		if (UBanAuditLog* AL = GI2->GetSubsystem<UBanAuditLog>())
			AL->LogAction(TEXT("ban"), Uid, DisplayName, GetCurrentAuditAdminUid(SenderName), SenderName, Template->Reason);

	const FString DurStr = Ban.bIsPermanent ? TEXT("permanent") : BanDiscordHelpers::FormatDuration(Template->DurationMinutes);
	FString QBanMsg = FString::Printf(TEXT(":hammer: [%s] Banned **%s** (%s). Reason: %s. Duration: %s."),
	*Slug, *BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
	*BanDiscordHelpers::EscapeMarkdown(Template->Reason), *DurStr);
	QBanMsg += BanDiscordHelpers::FormatPlayerLookup(this, Uid);
	Respond(ChannelId, QBanMsg);
	PostModerationLog(QBanMsg);
}

// ─────────────────────────────────────────────────────────────────────────────
// /player reputation <player|PUID>
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleReputationCommand(const TArray<FString>& Args,
                                                    const FString& ChannelId)
{
	if (!CachedProvider) return;

	if (Args.IsEmpty())
	{
		Respond(ChannelId,
		TEXT("Usage: `/player reputation <player|PUID>`"));
		return;
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	UGameInstance* GI = GetGameInstance();
	UBanDatabase*           DB        = GI ? GI->GetSubsystem<UBanDatabase>() : nullptr;
	UPlayerWarningRegistry* WarnReg   = GI ? GI->GetSubsystem<UPlayerWarningRegistry>() : nullptr;
	UPlayerSessionRegistry* SessionReg= GI ? GI->GetSubsystem<UPlayerSessionRegistry>() : nullptr;
	UBanAuditLog*           AuditLog  = GI ? GI->GetSubsystem<UBanAuditLog>() : nullptr;

	const int32 WarnCount  = WarnReg  ? WarnReg->GetWarningCount(Uid)  : 0;
	const int32 WarnPoints = WarnReg  ? WarnReg->GetWarningPoints(Uid) : 0;

	int32 TotalBans = 0;
	bool  bCurrentlyBanned = false;
	if (DB)
	{
		// Use IsCurrentlyBannedByAnyId for accurate active-ban status (checks LinkedUids too).
		FBanEntry ActiveEntry;
		bCurrentlyBanned = DB->IsCurrentlyBannedByAnyId(Uid, ActiveEntry);
		for (const FBanEntry& B : DB->GetAllBans())
		{
			// Count bans where Uid is the primary UID or appears in LinkedUids.
			if (B.Uid.Equals(Uid, ESearchCase::IgnoreCase) || B.LinkedUids.Contains(Uid))
				++TotalBans;
		}
	}

	int32 KickCount = 0;
	if (AuditLog)
	{
		for (const FAuditEntry& E : AuditLog->GetEntriesForTarget(Uid))
		{
			if (E.Action == TEXT("kick")) ++KickCount;
		}
	}

	FString LastSeen = TEXT("unknown");
	if (SessionReg)
	{
		FPlayerSessionRecord Rec;
		if (SessionReg->FindByUid(Uid, Rec))
		{
			LastSeen    = Rec.LastSeen;
			if (!Rec.DisplayName.IsEmpty()) DisplayName = Rec.DisplayName;
		}
	}

	const int64 ScoreRaw = static_cast<int64>(100)
		- (static_cast<int64>(WarnPoints) * 5)
		- (static_cast<int64>(TotalBans)  * 15)
		- (static_cast<int64>(KickCount)  * 3);
	const int32 Score = static_cast<int32>(FMath::Max((int64)0, ScoreRaw));

	const int32 Color = Score >= 70 ? 3066993 : (Score >= 40 ? 16776960 : 15158332);

	const FString Fields = FString::Printf(
	TEXT("{\"name\":\"Score\",\"value\":\"%d/100\",\"inline\":true},"
     "{\"name\":\"Currently Banned\",\"value\":\"%s\",\"inline\":true},"
     "{\"name\":\"Warnings\",\"value\":\"%d (pts: %d)\",\"inline\":true},"
     "{\"name\":\"Total Bans\",\"value\":\"%d\",\"inline\":true},"
     "{\"name\":\"Kicks\",\"value\":\"%d\",\"inline\":true},"
     "{\"name\":\"Last Seen\",\"value\":\"%s\",\"inline\":false}"),
	Score,
	bCurrentlyBanned ? TEXT("YES") : TEXT("No"),
	WarnCount, WarnPoints, TotalBans, KickCount,
	*BanDiscordHelpers::JsonEscape(LastSeen));

	const FString EmbedJson = FString::Printf(
	TEXT("{\"embeds\":[{\"title\":\"🔍 Reputation: %s\",\"description\":\"`%s`\",\"color\":%d,\"fields\":[%s],\"timestamp\":\"%s\"}]}"),
	*BanDiscordHelpers::JsonEscape(DisplayName),
	*BanDiscordHelpers::JsonEscape(Uid),
	Color,
	*Fields,
	*FDateTime::UtcNow().ToIso8601());

	// Send as a proper JSON body so Discord renders the embed.
	// Respond() wraps its argument in {"content":"..."} which would display the
	// embed JSON as literal text instead of rendering it.
	TSharedPtr<FJsonObject> BodyObj;
	TSharedRef<TJsonReader<>> BodyReader = TJsonReaderFactory<>::Create(EmbedJson);
	if (FJsonSerializer::Deserialize(BodyReader, BodyObj) && BodyObj.IsValid())
	{
		CachedProvider->SendMessageBodyToChannel(ChannelId, BodyObj);
		if (!PendingInteractionToken.IsEmpty())
			CachedProvider->FollowUpInteraction(PendingInteractionToken,
				TEXT("✅ Reputation shown."), /*bEphemeral=*/true);
	}
	else
	{
		Respond(ChannelId, TEXT(":x: Failed to build reputation embed."));
	}
}

// ─────────────────────────────────────────────────────────────────────────────
// /ban bulk <PUID1> <PUID2> ... -- <reason>
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleBulkBanCommand(const TArray<FString>& Args,
                                                 const FString& ChannelId,
                                                 const FString& SenderName)
{
	if (!CachedProvider) return;

	if (Args.IsEmpty())
	{
		Respond(ChannelId,
		TEXT("Usage: `/ban bulk <PUID1> <PUID2> ... -- <reason>`"));
		return;
	}

	UBanDatabase* DB = BanDiscordHelpers::GetDB(this);
	if (!DB)
	{
		Respond(ChannelId, TEXT(":x: Database unavailable."));
		return;
	}

	// Split on "--".
	TArray<FString> Uids;
	FString Reason = TEXT("Bulk ban");
	int32 SepIdx = -1;
	for (int32 i = 0; i < Args.Num(); ++i)
	{
		if (Args[i] == TEXT("--")) { SepIdx = i; break; }
	}

	if (SepIdx >= 0 && SepIdx < Args.Num() - 1)
	{
		for (int32 i = 0; i < SepIdx; ++i)
			Uids.Add(Args[i]);

		Reason.Empty();
		for (int32 i = SepIdx + 1; i < Args.Num(); ++i)
		{
			if (i > SepIdx + 1) Reason += TEXT(" ");
			Reason += Args[i];
		}
	}
	else
	{
		Uids = Args;
		Uids.RemoveAll([](const FString& S){ return S == TEXT("--"); });
	}

	if (Uids.IsEmpty())
	{
		Respond(ChannelId, TEXT(":x: No UIDs provided."));
		return;
	}

	UGameInstance* GI = GetGameInstance();
	int32 BannedCount = 0;

	for (const FString& RawUid : Uids)
	{
		if (!IsValidEOSPUID(RawUid))
		{
			UE_LOG(LogBanDiscord, Warning, TEXT("BulkBan: skipping invalid PUID '%s'"), *RawUid);
			continue;
		}
		const FString Uid = UBanDatabase::MakeUid(TEXT("EOS"), RawUid.ToLower());

		FBanEntry Ban;
		Ban.Uid        = Uid;
		UBanDatabase::ParseUid(Uid, Ban.Platform, Ban.PlayerUID);
		Ban.PlayerName      = RawUid;
		Ban.Reason          = Reason;
		Ban.BannedBy        = SenderName;
		Ban.BanDate         = FDateTime::UtcNow();
		Ban.bIsPermanent    = true;
		Ban.ExpireDate      = FDateTime(0);

		if (DB->AddBan(Ban))
		{
			if (UWorld* W = GI ? GI->GetWorld() : nullptr)
				UBanEnforcer::KickConnectedPlayer(W, Uid, Ban.GetKickMessage());
			// Also ban counterpart identifiers (IP↔EOS).
			BanDiscordHelpers::AddCounterpartBans(this, DB, Uid, RawUid,
				Reason, SenderName, true, FDateTime(0));
			FBanDiscordNotifier::NotifyBanCreated(Ban);
			if (UGameInstance* GI2 = GetGameInstance())
				if (UBanAuditLog* AL = GI2->GetSubsystem<UBanAuditLog>())
					AL->LogAction(TEXT("ban"), Uid, RawUid, GetCurrentAuditAdminUid(SenderName), SenderName, Reason);
			++BannedCount;
		}
	}

	Respond(ChannelId,
		FString::Printf(TEXT(":hammer: Bulk ban complete: **%d/%d** players banned. Reason: %s"),
			BannedCount, Uids.Num(),
			*BanDiscordHelpers::EscapeMarkdown(Reason)));
	PostModerationLog(FString::Printf(TEXT("%s bulk-banned %d player(s). Reason: %s"),
		*SenderName, BannedCount, *Reason));
}

// ─────────────────────────────────────────────────────────────────────────────
// Slash command interaction handler
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::OnDiscordInteraction(const TSharedPtr<FJsonObject>& InteractionObj)
{
	if (!InteractionObj.IsValid() || !CachedProvider)
	{
		UE_LOG(LogBanDiscord, Warning,
       TEXT("BanDiscordSubsystem: OnDiscordInteraction skipped — "
            "InteractionObj is %s, CachedProvider is %s."),
       InteractionObj.IsValid() ? TEXT("valid") : TEXT("null"),
       CachedProvider ? TEXT("set") : TEXT("null"));
		return;
	}

	// Only handle APPLICATION_COMMAND interactions (type 2).
	double InteractionTypeD = 0.0;
	const bool bHasInteractionType = InteractionObj->TryGetNumberField(TEXT("type"), InteractionTypeD);
	const int32 InteractionType = (bHasInteractionType
		&& FMath::IsFinite(InteractionTypeD)
		&& InteractionTypeD >= 0.0
		&& InteractionTypeD <= static_cast<double>(MAX_int32)
		&& FMath::Fmod(InteractionTypeD, 1.0) == 0.0)
		? static_cast<int32>(InteractionTypeD)
		: 0;

	// Type 3 = MESSAGE_COMPONENT (button / select-menu clicks).
	if (InteractionType == 3)
	{
		HandlePanelButtonInteraction(InteractionObj);
		return;
	}

	// Type 5 = MODAL_SUBMIT.
	if (InteractionType == 5)
	{
		HandlePanelModalSubmit(InteractionObj);
		return;
	}

	// Only continue processing for APPLICATION_COMMAND (type 2) interactions.
	if (InteractionType != 2) return;

	// Extract the interaction token and set up a guard that clears
	// PendingInteractionToken when OnDiscordInteraction returns, ensuring
	// the member field is never stale between calls.
	{
		FString ExtractedToken;
		InteractionObj->TryGetStringField(TEXT("token"), ExtractedToken);
		PendingInteractionToken = ExtractedToken;
	}

	// Extract the interaction ID — passed explicitly to handlers that respond
	// directly (e.g. HandlePanelCommand sends an embed via RespondToInteractionWithBody).
	FString InteractionId;
	InteractionObj->TryGetStringField(TEXT("id"), InteractionId);

	// RAII guard: clears PendingInteractionToken and PendingAuthorId on any return path.
	struct FInteractionTokenGuard
	{
    FString& TokenRef;
    FString& AuthorIdRef;
    explicit FInteractionTokenGuard(FString& T, FString& A) : TokenRef(T), AuthorIdRef(A) {}
    ~FInteractionTokenGuard() { TokenRef = FString(); AuthorIdRef = FString(); }
	} TokenGuard(PendingInteractionToken, PendingAuthorId);

	// Extract channel_id early so error messages can be posted.
	FString ChannelId;
	InteractionObj->TryGetStringField(TEXT("channel_id"), ChannelId);

	// Commands are disabled when neither role is configured.
	if (Config.AdminRoleId.IsEmpty() && Config.ModeratorRoleId.IsEmpty())
	{
		UE_LOG(LogBanDiscord, Warning,
       TEXT("BanDiscordSubsystem: Slash command ignored — "
            "neither AdminRoleId nor ModeratorRoleId is set in DefaultBanBridge.ini."));
		if (!ChannelId.IsEmpty())
		{
			Respond(ChannelId,
    TEXT("❌ Ban commands are disabled — `AdminRoleId` is not configured.\n"
         "Set `AdminRoleId` in `DefaultBanBridge.ini` and restart the server."));
		}
		return;
	}

	// Extract command data.
	const TSharedPtr<FJsonObject>* CmdDataPtr = nullptr;
	if (!InteractionObj->TryGetObjectField(TEXT("data"), CmdDataPtr) || !CmdDataPtr)
	{
		UE_LOG(LogBanDiscord, Warning,
       TEXT("BanDiscordSubsystem: Slash command ignored — "
            "interaction payload has no 'data' field."));
		if (!ChannelId.IsEmpty())
    Respond(ChannelId, TEXT("❌ Could not parse the command. Please try again."));
		return;
	}

	FString CmdGroupName;
	(*CmdDataPtr)->TryGetStringField(TEXT("name"), CmdGroupName);
	CmdGroupName = CmdGroupName.ToLower();

	// Only handle groups that belong to BanDiscordSubsystem.
	static const TArray<FString> HandledGroups = {
		TEXT("ban"), TEXT("warn"), TEXT("mod"),
		TEXT("player"), TEXT("appeal"), TEXT("admin"),
	};
	if (!HandledGroups.Contains(CmdGroupName)) return;

	// Extract the subcommand and its option list.
	const TArray<TSharedPtr<FJsonValue>>* TopOpts = nullptr;
	(*CmdDataPtr)->TryGetArrayField(TEXT("options"), TopOpts);
	if (!TopOpts || TopOpts->IsEmpty())
	{
		UE_LOG(LogBanDiscord, Warning,
       TEXT("BanDiscordSubsystem: /%s interaction has no subcommand options."),
       *CmdGroupName);
		if (!ChannelId.IsEmpty())
		Respond(ChannelId,
    TEXT("❌ Could not parse the subcommand. Please try the command again."));
		return;
	}

	const TSharedPtr<FJsonObject>* SubCmdPtr = nullptr;
	if (!(*TopOpts)[0]->TryGetObject(SubCmdPtr) || !SubCmdPtr)
	{
		UE_LOG(LogBanDiscord, Warning,
       TEXT("BanDiscordSubsystem: /%s interaction subcommand object is malformed."),
       *CmdGroupName);
		if (!ChannelId.IsEmpty())
		Respond(ChannelId,
    TEXT("❌ Could not parse the subcommand. Please try the command again."));
		return;
	}

	FString SubCmdName;
	(*SubCmdPtr)->TryGetStringField(TEXT("name"), SubCmdName);
	SubCmdName = SubCmdName.ToLower();

	const TArray<TSharedPtr<FJsonValue>>* SubOpts = nullptr;
	(*SubCmdPtr)->TryGetArrayField(TEXT("options"), SubOpts);

	// Extract sender identity, channel, and roles.
	FString SenderName, AuthorId;
	TArray<FString> MemberRoles;

	const TSharedPtr<FJsonObject>* MemberPtr = nullptr;
	if (InteractionObj->TryGetObjectField(TEXT("member"), MemberPtr) && MemberPtr)
	{
		(*MemberPtr)->TryGetStringField(TEXT("nick"), SenderName);
		const TSharedPtr<FJsonObject>* UserPtr = nullptr;
		if ((*MemberPtr)->TryGetObjectField(TEXT("user"), UserPtr) && UserPtr)
		{
			(*UserPtr)->TryGetStringField(TEXT("id"), AuthorId);
			if (SenderName.IsEmpty())
			(*UserPtr)->TryGetStringField(TEXT("global_name"), SenderName);
			if (SenderName.IsEmpty())
			(*UserPtr)->TryGetStringField(TEXT("username"), SenderName);
		}
		const TArray<TSharedPtr<FJsonValue>>* RolesArr = nullptr;
		if ((*MemberPtr)->TryGetArrayField(TEXT("roles"), RolesArr) && RolesArr)
		{
			for (const TSharedPtr<FJsonValue>& RV : *RolesArr)
			{
				FString RId;
				if (RV->TryGetString(RId)) MemberRoles.Add(RId);
			}
		}
	}
	if (SenderName.IsEmpty()) SenderName = TEXT("Discord Admin");
	// Set PendingAuthorId so all audit-log calls within this interaction handler
	// can use GetCurrentAuditAdminUid() to produce "Discord:<snowflake>" instead
	// of the mutable display name (BDS-1).
	PendingAuthorId = AuthorId;
	if (ChannelId.IsEmpty())
	{
		UE_LOG(LogBanDiscord, Warning,
       TEXT("BanDiscordSubsystem: /%s %s — channel_id is empty, cannot respond."),
       *CmdGroupName, *SubCmdName);
		return;
	}

	// Helper: extract a named option value as a string (handles STRING and INTEGER types).
	auto GetOpt = [&](const FString& Name) -> FString
	{
		if (!SubOpts) return FString();
		for (const TSharedPtr<FJsonValue>& Opt : *SubOpts)
		{
			const TSharedPtr<FJsonObject>* ObjPtr = nullptr;
			if (!Opt->TryGetObject(ObjPtr) || !ObjPtr) continue;
			FString OptName;
			if (!(*ObjPtr)->TryGetStringField(TEXT("name"), OptName) ||
    !OptName.Equals(Name, ESearchCase::IgnoreCase)) continue;
			FString StrVal;
			if ((*ObjPtr)->TryGetStringField(TEXT("value"), StrVal)) return StrVal;
			double NumVal = 0.0;
			if ((*ObjPtr)->TryGetNumberField(TEXT("value"), NumVal) &&
				FMath::IsFinite(NumVal) &&
				NumVal >= static_cast<double>(INT64_MIN) &&
				NumVal <= static_cast<double>(INT64_MAX) &&
				FMath::Fmod(NumVal, 1.0) == 0.0)
			return FString::Printf(TEXT("%lld"), static_cast<int64>(NumVal));
			return FString();
		}
		return FString();
	};

	// Determine required permission level.
	// /mod subcommands are accessible to moderators; all others require admin.
	static const TArray<FString> ModOnlyCmds = {
		TEXT("kick"), TEXT("modban"), TEXT("mute"), TEXT("unmute"),
		TEXT("tempmute"), TEXT("tempunmute"), TEXT("mutecheck"), TEXT("mutelist"),
		TEXT("mutereason"), TEXT("announce"), TEXT("stafflist"), TEXT("staffchat"),
	};
	const bool bNeedsAdminOnly = (CmdGroupName != TEXT("mod")) || !ModOnlyCmds.Contains(SubCmdName);
	const bool bAuthorised     = bNeedsAdminOnly
	? IsAdminMember(MemberRoles)
	: IsModeratorMember(MemberRoles);

	if (!bAuthorised)
	{
		Respond(ChannelId,
		bNeedsAdminOnly
		? TEXT("❌ Admin role required for that command.")
		: TEXT("❌ Moderator role required for that command."));
		return;
	}

	// Resolve the role-aware in-game broadcast prefix once, reused by all handlers.
	const FString StaffPrefix = ResolveStaffPrefix(MemberRoles);

	// ── Route to the appropriate command handler ──────────────────────────────
	TArray<FString> Args;
	bool bHandled = true;

	if (CmdGroupName == TEXT("ban"))
	{
		if (SubCmdName == TEXT("add"))
		{
			Args.Add(GetOpt(TEXT("player")));
			const FString R = GetOpt(TEXT("reason")); if (!R.IsEmpty()) Args.Add(R);
			HandleBanCommand(Args, ChannelId, SenderName, false, StaffPrefix);
		}
		else if (SubCmdName == TEXT("temp"))
		{
			// Convert duration string (e.g. "2h") to minutes.
			const FString Player = GetOpt(TEXT("player"));
			const FString DurStr = GetOpt(TEXT("duration"));
			const int32 Minutes  = ParseDurationMinutes(DurStr);
			const FString Reason = GetOpt(TEXT("reason"));
			if (Minutes <= 0)
			{
				Respond(ChannelId,
					TEXT("❌ Invalid duration. Use formats like: `30m`, `2h`, `1d`, `1w`.\n"
					     "Usage: `/ban temp <PUID|name> <duration> [reason]`"));
				return;
			}
			Args.Add(Player);
			Args.Add(FString::FromInt(Minutes));
			if (!Reason.IsEmpty()) Args.Add(Reason);
			HandleBanCommand(Args, ChannelId, SenderName, true, StaffPrefix);
		}
		else if (SubCmdName == TEXT("remove"))
		{
			Args.Add(GetOpt(TEXT("uid")));
			HandleUnbanCommand(Args, ChannelId, SenderName, StaffPrefix);
		}
		else if (SubCmdName == TEXT("removename"))
		{
			Args.Add(GetOpt(TEXT("name")));
			HandleUnbanNameCommand(Args, ChannelId, SenderName);
		}
		else if (SubCmdName == TEXT("byname"))
		{
			Args.Add(GetOpt(TEXT("name")));
			const FString R = GetOpt(TEXT("reason")); if (!R.IsEmpty()) Args.Add(R);
			HandleBanNameCommand(Args, ChannelId, SenderName);
		}
		else if (SubCmdName == TEXT("check"))
		{
			Args.Add(GetOpt(TEXT("player")));
			HandleBanCheckCommand(Args, ChannelId);
		}
		else if (SubCmdName == TEXT("reason"))
		{
			Args.Add(GetOpt(TEXT("player")));
			Args.Add(GetOpt(TEXT("new_reason")));
			HandleBanReasonCommand(Args, ChannelId, SenderName);
		}
		else if (SubCmdName == TEXT("list"))
		{
			const FString P = GetOpt(TEXT("page")); if (!P.IsEmpty()) Args.Add(P);
			HandleBanListCommand(Args, ChannelId);
		}
		else if (SubCmdName == TEXT("extend"))
		{
			Args.Add(GetOpt(TEXT("player")));
			Args.Add(GetOpt(TEXT("duration")));
			HandleExtendBanCommand(Args, ChannelId, SenderName);
		}
		else if (SubCmdName == TEXT("duration"))
		{
			Args.Add(GetOpt(TEXT("player")));
			HandleDurationCommand(Args, ChannelId);
		}
		else if (SubCmdName == TEXT("link"))
		{
			Args.Add(GetOpt(TEXT("uid1")));
			Args.Add(GetOpt(TEXT("uid2")));
			HandleLinkBansCommand(Args, ChannelId, SenderName, true);
		}
		else if (SubCmdName == TEXT("unlink"))
		{
			Args.Add(GetOpt(TEXT("uid1")));
			Args.Add(GetOpt(TEXT("uid2")));
			HandleLinkBansCommand(Args, ChannelId, SenderName, false);
		}
		else if (SubCmdName == TEXT("schedule"))
		{
			Args.Add(GetOpt(TEXT("player")));
			Args.Add(GetOpt(TEXT("delay")));
			const FString BD = GetOpt(TEXT("ban_duration")); if (!BD.IsEmpty()) Args.Add(BD);
			const FString R  = GetOpt(TEXT("reason"));       if (!R.IsEmpty())  Args.Add(R);
			HandleScheduleBanCommand(Args, ChannelId, SenderName);
		}
		else if (SubCmdName == TEXT("quick"))
		{
			Args.Add(GetOpt(TEXT("template")));
			Args.Add(GetOpt(TEXT("player")));
			HandleQBanCommand(Args, ChannelId, SenderName);
		}
		else if (SubCmdName == TEXT("bulk"))
		{
			// Split the space-separated player list into individual UID args.
			const FString PlayersStr = GetOpt(TEXT("players"));
			const FString Reason     = GetOpt(TEXT("reason"));
			TArray<FString> PlayerTokens;
			PlayersStr.ParseIntoArrayWS(PlayerTokens);
			Args.Append(PlayerTokens);
			Args.Add(TEXT("--"));
			if (!Reason.IsEmpty()) Args.Add(Reason);
			HandleBulkBanCommand(Args, ChannelId, SenderName);
		}
		else { bHandled = false; }
	}
	else if (CmdGroupName == TEXT("warn"))
	{
		if (SubCmdName == TEXT("add"))
		{
			Args.Add(GetOpt(TEXT("player")));
			Args.Add(GetOpt(TEXT("reason")));
			HandleWarnCommand(Args, ChannelId, SenderName, StaffPrefix);
		}
		else if (SubCmdName == TEXT("list"))
		{
			Args.Add(GetOpt(TEXT("player")));
			HandleWarningsCommand(Args, ChannelId);
		}
		else if (SubCmdName == TEXT("clearall"))
		{
			Args.Add(GetOpt(TEXT("player")));
			HandleClearWarnsCommand(Args, ChannelId, SenderName);
		}
		else if (SubCmdName == TEXT("clearone"))
		{
			Args.Add(GetOpt(TEXT("warning_id")));
			HandleClearWarnByIdCommand(Args, ChannelId, SenderName);
		}
		else { bHandled = false; }
	}
	else if (CmdGroupName == TEXT("mod"))
	{
		if (SubCmdName == TEXT("kick"))
		{
			Args.Add(GetOpt(TEXT("player")));
			const FString R = GetOpt(TEXT("reason")); if (!R.IsEmpty()) Args.Add(R);
			HandleKickCommand(Args, ChannelId, SenderName, StaffPrefix);
		}
		else if (SubCmdName == TEXT("modban"))
		{
			Args.Add(GetOpt(TEXT("player")));
			const FString R = GetOpt(TEXT("reason")); if (!R.IsEmpty()) Args.Add(R);
			HandleModBanCommand(Args, ChannelId, SenderName);
		}
		else if (SubCmdName == TEXT("mute"))
		{
			Args.Add(GetOpt(TEXT("player")));
			const FString Mins = GetOpt(TEXT("minutes")); if (!Mins.IsEmpty()) Args.Add(Mins);
			const FString R    = GetOpt(TEXT("reason"));  if (!R.IsEmpty())    Args.Add(R);
			HandleMuteCommand(Args, ChannelId, SenderName, true, StaffPrefix);
		}
		else if (SubCmdName == TEXT("unmute"))
		{
			Args.Add(GetOpt(TEXT("player")));
			HandleMuteCommand(Args, ChannelId, SenderName, false, StaffPrefix);
		}
		else if (SubCmdName == TEXT("tempmute"))
		{
			Args.Add(GetOpt(TEXT("player")));
			Args.Add(GetOpt(TEXT("duration")));
			const FString R = GetOpt(TEXT("reason")); if (!R.IsEmpty()) Args.Add(R);
			HandleTempMuteCommand(Args, ChannelId, SenderName, StaffPrefix);
		}
		else if (SubCmdName == TEXT("tempunmute"))
		{
			Args.Add(GetOpt(TEXT("player")));
			HandleTempUnmuteCommand(Args, ChannelId, SenderName, StaffPrefix);
		}
		else if (SubCmdName == TEXT("mutecheck"))
		{
			Args.Add(GetOpt(TEXT("player")));
			HandleMuteCheckCommand(Args, ChannelId);
		}
		else if (SubCmdName == TEXT("mutelist"))
		{
			HandleMuteListCommand(ChannelId);
		}
		else if (SubCmdName == TEXT("mutereason"))
		{
			Args.Add(GetOpt(TEXT("player")));
			Args.Add(GetOpt(TEXT("new_reason")));
			HandleMuteReasonCommand(Args, ChannelId, SenderName, StaffPrefix);
		}
		else if (SubCmdName == TEXT("announce"))
		{
			Args.Add(GetOpt(TEXT("message")));
			HandleAnnounceCommand(Args, ChannelId, SenderName);
		}
		else if (SubCmdName == TEXT("stafflist"))
		{
			HandleStaffListCommand(ChannelId);
		}
		else if (SubCmdName == TEXT("staffchat"))
		{
			Args.Add(GetOpt(TEXT("message")));
			HandleStaffChatCommand(Args, ChannelId, SenderName);
		}
		else if (SubCmdName == TEXT("freeze"))
		{
			Args.Add(GetOpt(TEXT("player")));
			HandleFreezeCommand(Args, ChannelId, SenderName);
		}
		else { bHandled = false; }
	}
	else if (CmdGroupName == TEXT("player"))
	{
		// Note: /player stats is handled by DiscordBridgeSubsystem (not BanDiscordSubsystem).
		if (SubCmdName == TEXT("history"))
		{
			Args.Add(GetOpt(TEXT("query")));
			HandlePlayerHistoryCommand(Args, ChannelId);
		}
		else if (SubCmdName == TEXT("note"))
		{
			Args.Add(GetOpt(TEXT("player")));
			Args.Add(GetOpt(TEXT("text"))); // JoinArgs(Args, 1) in handler reassembles the text
			HandleNoteCommand(Args, ChannelId, SenderName);
		}
		else if (SubCmdName == TEXT("notes"))
		{
			Args.Add(GetOpt(TEXT("player")));
			HandleNotesCommand(Args, ChannelId);
		}
		else if (SubCmdName == TEXT("reason"))
		{
			Args.Add(GetOpt(TEXT("uid")));
			HandleReasonCommand(Args, ChannelId);
		}
		else if (SubCmdName == TEXT("playtime"))
		{
			Args.Add(GetOpt(TEXT("player")));
			HandlePlaytimeCommand(Args, ChannelId);
		}
		else if (SubCmdName == TEXT("reputation"))
		{
			Args.Add(GetOpt(TEXT("player")));
			HandleReputationCommand(Args, ChannelId);
		}
		// "stats" is intentionally absent — handled in DiscordBridgeSubsystem.
		else { bHandled = false; }
	}
	else if (CmdGroupName == TEXT("appeal"))
	{
		if (SubCmdName == TEXT("list"))
		{
			HandleAppealsCommand(ChannelId);
		}
		else if (SubCmdName == TEXT("dismiss"))
		{
			Args.Add(GetOpt(TEXT("id")));
			HandleDismissAppealCommand(Args, ChannelId, SenderName);
		}
		else if (SubCmdName == TEXT("approve"))
		{
			Args.Add(GetOpt(TEXT("id")));
			HandleAppealApproveCommand(Args, ChannelId, SenderName);
		}
		else if (SubCmdName == TEXT("deny"))
		{
			Args.Add(GetOpt(TEXT("id")));
			HandleAppealDenyCommand(Args, ChannelId, SenderName);
		}
		else { bHandled = false; }
	}
	else if (CmdGroupName == TEXT("admin"))
	{
		if (SubCmdName == TEXT("say"))
		{
			Args.Add(GetOpt(TEXT("message")));
			HandleSayCommand(Args, ChannelId, SenderName);
		}
		else if (SubCmdName == TEXT("poll"))
		{
			// Reconstruct the pipe-delimited string that HandlePollCommand expects
			// (JoinArgs(Args, 0) then split on "|").
			const FString Question = GetOpt(TEXT("question"));
			const FString Options  = GetOpt(TEXT("options")); // "Yes|No|Maybe"
			TArray<FString> OptTokens;
			Options.ParseIntoArray(OptTokens, TEXT("|"), true);
			FString PollText = Question;
			for (const FString& O : OptTokens)
			PollText += TEXT(" | ") + O.TrimStartAndEnd();
			Args.Add(PollText);
			HandlePollCommand(Args, ChannelId);
		}
		else if (SubCmdName == TEXT("reloadconfig"))
		{
			HandleReloadConfigCommand(ChannelId, SenderName);
		}
		else if (SubCmdName == TEXT("panel"))
		{
			HandlePanelCommand(ChannelId, InteractionId, PendingInteractionToken, MemberRoles, SenderName, AuthorId);
		}
		else if (SubCmdName == TEXT("clearchat"))
		{
			const FString R = GetOpt(TEXT("reason")); if (!R.IsEmpty()) Args.Add(R);
			HandleClearChatCommand(Args, ChannelId, SenderName);
		}
		else { bHandled = false; }
	}
	else { bHandled = false; }

	if (!bHandled)
	{
		UE_LOG(LogBanDiscord, Warning,
       TEXT("BanDiscordSubsystem: Unrecognised slash command /%s %s — no handler matched."),
       *CmdGroupName, *SubCmdName);
		Respond(ChannelId,
    FString::Printf(TEXT("❌ Unknown subcommand `/%s %s`."), *CmdGroupName, *SubCmdName));
	}
}

// ─────────────────────────────────────────────────────────────────────────────
// Admin panel — /admin panel
// ─────────────────────────────────────────────────────────────────────────────

TSharedPtr<FJsonObject> UBanDiscordSubsystem::BuildPanelData() const
{
	UGameInstance* GI = GetGameInstance();

	// Count currently connected players.
	int32 PlayerCount = 0;
	if (GI)
	{
		if (UWorld* World = GI->GetWorld())
		{
			for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
			{
				if (It->Get()) ++PlayerCount;
			}
		}
	}

	// Count active bans (Feature 11 dashboard).
	int32 ActiveBanCount = 0;
	if (UBanDatabase* DB = BanDiscordHelpers::GetDB(this))
		ActiveBanCount = DB->GetActiveBans().Num();

	// Count currently muted players (Feature 11 dashboard).
	int32 MutedCount = 0;
	if (UMuteRegistry* MuteReg = GI ? GI->GetSubsystem<UMuteRegistry>() : nullptr)
		MutedCount = MuteReg->GetAllMutes().Num();

	// Feature 7: Read ServerName from CachedDiscordServerName (populated in
	// Initialize() and kept in sync by HandleReloadConfigCommand / ExecutePanelReloadConfig)
	// to avoid reading the config file from disk on every panel refresh.
	const FString& ServerName = CachedDiscordServerName;

	// Build the embed object.
	TSharedPtr<FJsonObject> Embed = MakeShared<FJsonObject>();

	FString TitleStr = TEXT("🛡️ Server Admin Panel");
	if (!ServerName.IsEmpty())
		TitleStr = FString::Printf(TEXT("🛡️ %s — Admin Panel"), *ServerName);
	Embed->SetStringField(TEXT("title"), TitleStr);

	// Discord dynamic relative timestamp for the 15-minute button expiry window.
	const int64 ExpiryUnix = (FDateTime::UtcNow() + FTimespan::FromMinutes(15)).ToUnixTimestamp();

	Embed->SetStringField(TEXT("description"),
		FString::Printf(
			TEXT("**Online Players: %d**\n"
			     "Use the buttons below to manage the server.\n\n"
			     "⏳ Buttons expire <t:%lld:R> — press **🔄 Refresh** or run `/admin panel`."),
			PlayerCount, ExpiryUnix));
	Embed->SetNumberField(TEXT("color"), 3447003); // #3498DB — a solid Discord blue

	// Feature 11: Dashboard fields.
	TArray<TSharedPtr<FJsonValue>> EmbedFields;
	auto AddEmbedField = [&EmbedFields](const FString& Name, const FString& Value, bool bInline)
	{
		TSharedPtr<FJsonObject> F = MakeShared<FJsonObject>();
		F->SetStringField(TEXT("name"),   Name);
		F->SetStringField(TEXT("value"),  Value);
		F->SetBoolField  (TEXT("inline"), bInline);
		EmbedFields.Add(MakeShared<FJsonValueObject>(F));
	};
	AddEmbedField(TEXT("🟢 Online"),       FString::FromInt(PlayerCount), true);
	AddEmbedField(TEXT("🔨 Active Bans"),  FString::FromInt(ActiveBanCount), true);
	AddEmbedField(TEXT("🔇 Muted"),        FString::FromInt(MutedCount), true);
	Embed->SetArrayField(TEXT("fields"), EmbedFields);

	// ISO 8601 timestamp shown in the embed footer.
	Embed->SetStringField(TEXT("timestamp"), FDateTime::UtcNow().ToIso8601());

	// Look up the installed DiscordBridge mod version to display in the footer.
	FString DiscordBridgeVersion;
	if (GI)
	{
		if (UModLoadingLibrary* ModLib = GI->GetSubsystem<UModLoadingLibrary>())
		{
			FModInfo ModInfo;
			if (ModLib->GetLoadedModInfo(TEXT("DiscordBridge"), ModInfo))
				DiscordBridgeVersion = FString::Printf(TEXT(" v%s"), *ModInfo.Version.ToString());
		}
	}

	TSharedPtr<FJsonObject> Footer = MakeShared<FJsonObject>();
	const FString FooterText = ServerName.IsEmpty()
		? FString::Printf(TEXT("DiscordBridge%s Admin Panel"), *DiscordBridgeVersion)
		: FString::Printf(TEXT("DiscordBridge%s Admin Panel · %s"), *DiscordBridgeVersion, *ServerName);
	Footer->SetStringField(TEXT("text"), FooterText);
	Embed->SetObjectField(TEXT("footer"), Footer);

	// Helper: build a single Discord BUTTON component object.
	auto MakeButton = [](int32 Style, const FString& Label,
	                     const FString& CustomId) -> TSharedPtr<FJsonObject>
	{
		TSharedPtr<FJsonObject> Btn = MakeShared<FJsonObject>();
		Btn->SetNumberField(TEXT("type"),      2); // BUTTON
		Btn->SetNumberField(TEXT("style"),     Style);
		Btn->SetStringField(TEXT("label"),     Label);
		Btn->SetStringField(TEXT("custom_id"), CustomId);
		return Btn;
	};

	// Helper: wrap a list of buttons in an ACTION_ROW.
	auto MakeActionRow = [](const TArray<TSharedPtr<FJsonObject>>& Btns) -> TSharedPtr<FJsonObject>
	{
		TSharedPtr<FJsonObject> Row = MakeShared<FJsonObject>();
		Row->SetNumberField(TEXT("type"), 1); // ACTION_ROW
		TArray<TSharedPtr<FJsonValue>> BtnValues;
		for (const TSharedPtr<FJsonObject>& B : Btns)
			BtnValues.Add(MakeShared<FJsonValueObject>(B));
		Row->SetArrayField(TEXT("components"), BtnValues);
		return Row;
	};

	// Row 1 — moderator-level actions (kick, mute, unmute, announce, players).
	// Button styles: 1=blurple, 2=grey, 3=green, 4=red.
	TArray<TSharedPtr<FJsonObject>> Row1 = {
		MakeButton(2, TEXT("👢 Kick"),     TEXT("panel:kick")),
		MakeButton(2, TEXT("🔇 Mute"),     TEXT("panel:mute")),
		MakeButton(2, TEXT("🔊 Unmute"),   TEXT("panel:unmute")),
		MakeButton(1, TEXT("📢 Announce"), TEXT("panel:announce")),
		MakeButton(2, TEXT("👥 Players"),  TEXT("panel:players")),
	};

	// Row 2 — admin-level actions (ban, temp ban, warn, unban, ban list).
	TArray<TSharedPtr<FJsonObject>> Row2 = {
		MakeButton(4, TEXT("🔨 Ban"),      TEXT("panel:ban")),
		MakeButton(4, TEXT("⏱ Temp Ban"), TEXT("panel:tempban")),
		MakeButton(3, TEXT("⚠️ Warn"),    TEXT("panel:warn")),
		MakeButton(3, TEXT("🔓 Unban"),    TEXT("panel:unban")),
		MakeButton(2, TEXT("📋 Ban List"), TEXT("panel:banlist")),
	};

	// Row 3 — lookup tools (warn list, player history, ban check, mute check, mute list).
	TArray<TSharedPtr<FJsonObject>> Row3 = {
		MakeButton(2, TEXT("⚠️ Warns"),    TEXT("panel:warnlist")),
		MakeButton(1, TEXT("📜 History"),   TEXT("panel:history")),
		MakeButton(2, TEXT("🔍 Ban Check"), TEXT("panel:bancheck")),
		MakeButton(2, TEXT("🔇 Mute Chk"), TEXT("panel:mutecheck")),
		MakeButton(2, TEXT("📋 Mute List"), TEXT("panel:mutelist")),
	};

	// Row 4 — utility (staff list, reload config, refresh panel, pending appeals).
	TArray<TSharedPtr<FJsonObject>> Row4 = {
		MakeButton(2, TEXT("👮 Staff"),     TEXT("panel:stafflist")),
		MakeButton(2, TEXT("🔁 Reload"),    TEXT("panel:reload")),
		MakeButton(3, TEXT("🔄 Refresh"),   TEXT("panel:refresh")),
		MakeButton(2, TEXT("🔔 Appeals"),   TEXT("panel:appeals")),
	};

	// Row 5 — admin actions (freeze player, clear in-game chat).
	TArray<TSharedPtr<FJsonObject>> Row5 = {
		MakeButton(2, TEXT("❄️ Freeze"),    TEXT("panel:freeze")),
		MakeButton(2, TEXT("🧹 Clear Chat"), TEXT("panel:clearchat")),
	};

	TArray<TSharedPtr<FJsonValue>> Rows;
	Rows.Add(MakeShared<FJsonValueObject>(MakeActionRow(Row1)));
	Rows.Add(MakeShared<FJsonValueObject>(MakeActionRow(Row2)));
	Rows.Add(MakeShared<FJsonValueObject>(MakeActionRow(Row3)));
	Rows.Add(MakeShared<FJsonValueObject>(MakeActionRow(Row4)));
	Rows.Add(MakeShared<FJsonValueObject>(MakeActionRow(Row5)));

	// Assemble the top-level data object.
	TSharedPtr<FJsonObject> Data = MakeShared<FJsonObject>();
	Data->SetArrayField(TEXT("embeds"),
		TArray<TSharedPtr<FJsonValue>>{ MakeShared<FJsonValueObject>(Embed) });
	Data->SetArrayField(TEXT("components"), Rows);
	return Data;
}

void UBanDiscordSubsystem::HandlePanelCommand(const FString& ChannelId,
                                               const FString& InteractionId,
                                               const FString& InteractionToken,
                                               const TArray<FString>& MemberRoles,
                                               const FString& SenderName,
                                               const FString& AuthorId)
{
	if (!CachedProvider) return;

	// Feature 12: Per-user rate-limit.  Skip when AuthorId is empty (auto-post / tests)
	// or when PanelRateLimitSeconds == 0 (rate-limiting disabled).
	if (!AuthorId.IsEmpty() && PanelRateLimitSeconds > 0.0f)
	{
		const FDateTime Now = FDateTime::UtcNow();

		// Prune entries that are more than 2× the rate-limit age to keep the map bounded.
		{
			TArray<FString> ToRemove;
			const double PruneCutoffSec = PanelRateLimitSeconds * 2.0;
			for (auto& Pair : LastPanelPostByUser)
			{
				if ((Now - Pair.Value).GetTotalSeconds() > PruneCutoffSec)
					ToRemove.Add(Pair.Key);
			}
			for (const FString& K : ToRemove)
				LastPanelPostByUser.Remove(K);
		}

		if (const FDateTime* LastPost = LastPanelPostByUser.Find(AuthorId))
		{
			const float SecondsElapsed =
				static_cast<float>((Now - *LastPost).GetTotalSeconds());
			if (SecondsElapsed < PanelRateLimitSeconds)
			{
				const int32 SecsLeft =
					FMath::CeilToInt(PanelRateLimitSeconds - SecondsElapsed);
				if (!InteractionId.IsEmpty() && !InteractionToken.IsEmpty())
				{
					CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
						FString::Printf(
							TEXT("⏳ Please wait %d second(s) before using `/admin panel` again."),
							SecsLeft),
						/*bEphemeral=*/true);
				}
				return;
			}
		}
		LastPanelPostByUser.Add(AuthorId, Now);
	}

	// Determine the target channel.  When AdminPanelChannelId is set use that;
	// otherwise fall back to the channel the /admin panel command was issued in.
	const FString TargetChannel = Config.AdminPanelChannelId.IsEmpty()
		? ChannelId
		: Config.AdminPanelChannelId;

	TSharedPtr<FJsonObject> PanelData = BuildPanelData();

	if (!InteractionId.IsEmpty() && !InteractionToken.IsEmpty()
		&& (Config.AdminPanelChannelId.IsEmpty() || Config.AdminPanelChannelId == ChannelId))
	{
		// Respond to the slash command interaction directly with the embed
		// (type 4, non-ephemeral) so the panel appears inline with the command.
		CachedProvider->RespondToInteractionWithBody(InteractionId, InteractionToken,
			PanelData, /*bEphemeral=*/false);
	}
	else
	{
		// When AdminPanelChannelId differs from the command channel, post to
		// the configured channel and ack the command with an ephemeral note.
		CachedProvider->SendMessageBodyToChannel(TargetChannel, PanelData);
		if (!InteractionId.IsEmpty() && !InteractionToken.IsEmpty())
		{
			CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
				FString::Printf(TEXT("✅ Admin panel posted in <#%s>."), *TargetChannel),
				/*bEphemeral=*/true);
		}
	}

	UE_LOG(LogBanDiscord, Log,
	       TEXT("BanDiscordSubsystem: %s opened the admin panel (channel %s)."),
	       *SenderName, *TargetChannel);
}

// ─────────────────────────────────────────────────────────────────────────────
// Admin panel — button interaction handler (type 3)
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandlePanelButtonInteraction(const TSharedPtr<FJsonObject>& InteractionObj)
{
	if (!CachedProvider || !InteractionObj.IsValid()) return;

	FString InteractionId, InteractionToken, CustomId;
	InteractionObj->TryGetStringField(TEXT("id"),    InteractionId);
	InteractionObj->TryGetStringField(TEXT("token"), InteractionToken);

	if (InteractionId.IsEmpty() || InteractionToken.IsEmpty()) return;

	const TSharedPtr<FJsonObject>* DataPtr = nullptr;
	if (!InteractionObj->TryGetObjectField(TEXT("data"), DataPtr) || !DataPtr) return;
	(*DataPtr)->TryGetStringField(TEXT("custom_id"), CustomId);

	// Only handle buttons belonging to the admin panel.
	if (!CustomId.StartsWith(TEXT("panel:"))) return;

	const TArray<FString> MemberRoles = ExtractMemberRoles(InteractionObj);
	const FString SenderName          = ExtractSenderName(InteractionObj);

	const FString Action = CustomId.Mid(6); // strip "panel:"

	// Determine which permission tier the action requires.
	// Admin-level: ban, tempban, warn, banlist, reload, unban, warnlist, history.
	// Mod-level:   kick, mute, unmute, announce, players, stafflist, refresh,
	//              bancheck, mutecheck, mutelist, appeals.
	static const TArray<FString> AdminActions = {
		TEXT("ban"), TEXT("tempban"), TEXT("warn"), TEXT("banlist"), TEXT("reload"),
		TEXT("unban"), TEXT("warnlist"), TEXT("history"), TEXT("freeze"), TEXT("clearchat"),
	};
	static const TArray<FString> ModActions = {
		TEXT("kick"), TEXT("mute"), TEXT("unmute"), TEXT("announce"),
		TEXT("players"), TEXT("stafflist"), TEXT("refresh"),
		TEXT("bancheck"), TEXT("mutecheck"), TEXT("mutelist"), TEXT("appeals"),
	};

	const bool bNeedsAdmin = AdminActions.Contains(Action);
	const bool bNeedsMod   = ModActions.Contains(Action);

	if (bNeedsAdmin && !IsAdminMember(MemberRoles))
	{
		CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
			TEXT("❌ Admin role required for that action."), true);
		return;
	}
	if (bNeedsMod && !IsModeratorMember(MemberRoles))
	{
		CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
			TEXT("❌ Moderator role required for that action."), true);
		return;
	}
	if (!bNeedsAdmin && !bNeedsMod)
	{
		CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
			TEXT("❌ Unknown panel action."), true);
		return;
	}

	// ── Direct-action buttons — respond immediately ───────────────────────────

	if (Action == TEXT("banlist"))
	{
		const FString Result = ExecutePanelBanList();
		CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4, Result, true);
		return;
	}
	if (Action == TEXT("mutelist"))
	{
		const FString Result = ExecutePanelMuteList();
		CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4, Result, true);
		return;
	}
	if (Action == TEXT("players"))
	{
		const FString Result = ExecutePanelPlayers();
		CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4, Result, true);
		return;
	}
	if (Action == TEXT("stafflist"))
	{
		const FString Result = ExecutePanelStaffList();
		CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4, Result, true);
		return;
	}
	if (Action == TEXT("appeals"))
	{
		const FString Result = ExecutePanelAppeals();
		CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4, Result, true);
		return;
	}
	if (Action == TEXT("reload"))
	{
		const FString Result = ExecutePanelReloadConfig(SenderName);
		CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4, Result, true);
		PostModerationLog(Result);
		return;
	}
	// Feature 5: Refresh — post a fresh panel to the channel and ack the button.
	if (Action == TEXT("refresh"))
	{
		FString InteractionChannelId;
		InteractionObj->TryGetStringField(TEXT("channel_id"), InteractionChannelId);
		const FString TargetChannel = Config.AdminPanelChannelId.IsEmpty()
			? InteractionChannelId
			: Config.AdminPanelChannelId;
		TSharedPtr<FJsonObject> PanelData = BuildPanelData();
		CachedProvider->SendMessageBodyToChannel(TargetChannel, PanelData);
		CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
			TEXT("✅ Panel refreshed."), true);
		UE_LOG(LogBanDiscord, Log,
		       TEXT("BanDiscordSubsystem: [Panel] %s refreshed the panel (channel %s)."),
		       *SenderName, *TargetChannel);
		return;
	}

	// ── Modal-opening buttons ─────────────────────────────────────────────────

	// Helper lambda: build a field and add it to the array.
	auto AddField = [](TArray<FModalField>& Fields,
	                   const FString& Label, const FString& Id,
	                   const FString& Hint, bool bReq, bool bPara,
	                   int32 Min, int32 Max)
	{
		FModalField F;
		F.Label       = Label;
		F.CustomId    = Id;
		F.Placeholder = Hint;
		F.bRequired   = bReq;
		F.bParagraph  = bPara;
		F.MinLength   = Min;
		F.MaxLength   = Max;
		Fields.Add(F);
	};

	if (Action == TEXT("kick"))
	{
		TArray<FModalField> Fields;
		AddField(Fields, TEXT("Player name or EOS PUID"), TEXT("panel_player"),
			TEXT("Enter name or 32-char EOS PUID"), true,  false, 0, 100);
		AddField(Fields, TEXT("Reason (optional)"),       TEXT("panel_reason"),
			TEXT("Reason for kick"),                  false, false, 0, 200);
		CachedProvider->RespondWithMultiFieldModal(InteractionId, InteractionToken,
			TEXT("panel_modal:kick"), TEXT("Kick Player"), Fields);
		return;
	}
	if (Action == TEXT("mute"))
	{
		TArray<FModalField> Fields;
		AddField(Fields, TEXT("Player name or EOS PUID"),              TEXT("panel_player"),
			TEXT("Enter name or 32-char EOS PUID"),                true,  false, 0, 100);
		AddField(Fields, TEXT("Duration (e.g. 30m, 2h, 7d; blank = indefinite)"), TEXT("panel_duration"),
			TEXT("30m = 30 min, 2h = 2 hours, 7d = 7 days"),      false, false, 0, 20);
		AddField(Fields, TEXT("Reason (optional)"),                    TEXT("panel_reason"),
			TEXT("Reason for mute"),                               false, false, 0, 200);
		CachedProvider->RespondWithMultiFieldModal(InteractionId, InteractionToken,
			TEXT("panel_modal:mute"), TEXT("Mute Player"), Fields);
		return;
	}
	if (Action == TEXT("announce"))
	{
		TArray<FModalField> Fields;
		AddField(Fields, TEXT("Message to broadcast in-game"), TEXT("panel_message"),
			TEXT("Enter announcement text"), true, true, 1, 500);
		CachedProvider->RespondWithMultiFieldModal(InteractionId, InteractionToken,
			TEXT("panel_modal:announce"), TEXT("Broadcast Announcement"), Fields);
		return;
	}
	if (Action == TEXT("ban"))
	{
		TArray<FModalField> Fields;
		AddField(Fields, TEXT("Player name or EOS PUID"),    TEXT("panel_player"),
			TEXT("Enter name or 32-char EOS PUID"),      true,  false, 0, 100);
		AddField(Fields, TEXT("Reason (optional)"),          TEXT("panel_reason"),
			TEXT("Reason for permanent ban"),            false, false, 0, 200);
		AddField(Fields, TEXT("Type CONFIRM to proceed"),    TEXT("panel_confirm"),
			TEXT("CONFIRM"),                             true,  false, 7, 7);
		CachedProvider->RespondWithMultiFieldModal(InteractionId, InteractionToken,
			TEXT("panel_modal:ban"), TEXT("Ban Player (Permanent)"), Fields);
		return;
	}
	if (Action == TEXT("tempban"))
	{
		TArray<FModalField> Fields;
		AddField(Fields, TEXT("Player name or EOS PUID"),       TEXT("panel_player"),
			TEXT("Enter name or 32-char EOS PUID"),          true,  false, 0, 100);
		AddField(Fields, TEXT("Duration (e.g. 30m, 2h, 7d)"), TEXT("panel_duration"),
			TEXT("30m = 30 min, 2h = 2 hours, 7d = 7 days"), true,  false, 1, 20);
		AddField(Fields, TEXT("Reason (optional)"),             TEXT("panel_reason"),
			TEXT("Reason for temporary ban"),                false, false, 0, 200);
		CachedProvider->RespondWithMultiFieldModal(InteractionId, InteractionToken,
			TEXT("panel_modal:tempban"), TEXT("Temp-Ban Player"), Fields);
		return;
	}
	if (Action == TEXT("warn"))
	{
		TArray<FModalField> Fields;
		AddField(Fields, TEXT("Player name or EOS PUID"), TEXT("panel_player"),
			TEXT("Enter name or 32-char EOS PUID"), true, false, 0, 100);
		AddField(Fields, TEXT("Warning reason"),           TEXT("panel_reason"),
			TEXT("Reason for this warning"),        true, false, 1, 200);
		CachedProvider->RespondWithMultiFieldModal(InteractionId, InteractionToken,
			TEXT("panel_modal:warn"), TEXT("Warn Player"), Fields);
		return;
	}
	// Feature 4: Unban modal (admin).
	if (Action == TEXT("unban"))
	{
		TArray<FModalField> Fields;
		AddField(Fields, TEXT("Player name or EOS PUID"), TEXT("panel_player"),
			TEXT("Enter name or 32-char EOS PUID"), true, false, 0, 100);
		CachedProvider->RespondWithMultiFieldModal(InteractionId, InteractionToken,
			TEXT("panel_modal:unban"), TEXT("Unban Player"), Fields);
		return;
	}
	// Feature 4: Unmute modal (mod).
	if (Action == TEXT("unmute"))
	{
		TArray<FModalField> Fields;
		AddField(Fields, TEXT("Player name or EOS PUID"), TEXT("panel_player"),
			TEXT("Enter name or 32-char EOS PUID"), true, false, 0, 100);
		CachedProvider->RespondWithMultiFieldModal(InteractionId, InteractionToken,
			TEXT("panel_modal:unmute"), TEXT("Unmute Player"), Fields);
		return;
	}
	// Feature 6: Ban check modal (mod).
	if (Action == TEXT("bancheck"))
	{
		TArray<FModalField> Fields;
		AddField(Fields, TEXT("Player name or EOS PUID"), TEXT("panel_player"),
			TEXT("Enter name or 32-char EOS PUID"), true, false, 0, 100);
		CachedProvider->RespondWithMultiFieldModal(InteractionId, InteractionToken,
			TEXT("panel_modal:bancheck"), TEXT("Ban Check"), Fields);
		return;
	}
	// Warn list — show a player's warning history (admin).
	if (Action == TEXT("warnlist"))
	{
		TArray<FModalField> Fields;
		AddField(Fields, TEXT("Player name or EOS PUID"), TEXT("panel_player"),
			TEXT("Enter name or 32-char EOS PUID"), true, false, 0, 100);
		CachedProvider->RespondWithMultiFieldModal(InteractionId, InteractionToken,
			TEXT("panel_modal:warnlist"), TEXT("Warn List"), Fields);
		return;
	}
	// Player history — session records lookup (admin).
	if (Action == TEXT("history"))
	{
		TArray<FModalField> Fields;
		AddField(Fields, TEXT("Player name, EOS PUID, or IP"), TEXT("panel_player"),
			TEXT("Enter name, 32-char EOS PUID, or IP address"), true, false, 0, 100);
		CachedProvider->RespondWithMultiFieldModal(InteractionId, InteractionToken,
			TEXT("panel_modal:history"), TEXT("Player History"), Fields);
		return;
	}
	// Mute check — check a player's mute status (mod).
	if (Action == TEXT("mutecheck"))
	{
		TArray<FModalField> Fields;
		AddField(Fields, TEXT("Player name or EOS PUID"), TEXT("panel_player"),
			TEXT("Enter name or 32-char EOS PUID"), true, false, 0, 100);
		CachedProvider->RespondWithMultiFieldModal(InteractionId, InteractionToken,
			TEXT("panel_modal:mutecheck"), TEXT("Mute Check"), Fields);
		return;
	}
	// Freeze — toggle movement freeze for a player (admin).
	if (Action == TEXT("freeze"))
	{
		TArray<FModalField> Fields;
		AddField(Fields, TEXT("Player name or EOS PUID"), TEXT("panel_player"),
			TEXT("Enter name or 32-char EOS PUID"), true, false, 0, 100);
		CachedProvider->RespondWithMultiFieldModal(InteractionId, InteractionToken,
			TEXT("panel_modal:freeze"), TEXT("Freeze / Unfreeze Player"), Fields);
		return;
	}
	// Clear Chat — flush in-game chat (admin).
	if (Action == TEXT("clearchat"))
	{
		TArray<FModalField> Fields;
		AddField(Fields, TEXT("Reason (optional)"), TEXT("panel_reason"),
			TEXT("Reason for clearing chat"), false, false, 0, 200);
		CachedProvider->RespondWithMultiFieldModal(InteractionId, InteractionToken,
			TEXT("panel_modal:clearchat"), TEXT("Clear In-Game Chat"), Fields);
		return;
	}

	// Unknown panel button (should not occur in practice).
	CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
		TEXT("❌ Unknown panel button."), true);
}

// ─────────────────────────────────────────────────────────────────────────────
// Admin panel — modal-submit handler (type 5)
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandlePanelModalSubmit(const TSharedPtr<FJsonObject>& InteractionObj)
{
	if (!CachedProvider || !InteractionObj.IsValid()) return;

	FString InteractionId, InteractionToken;
	InteractionObj->TryGetStringField(TEXT("id"),    InteractionId);
	InteractionObj->TryGetStringField(TEXT("token"), InteractionToken);

	if (InteractionId.IsEmpty() || InteractionToken.IsEmpty()) return;

	const TSharedPtr<FJsonObject>* DataPtr = nullptr;
	if (!InteractionObj->TryGetObjectField(TEXT("data"), DataPtr) || !DataPtr) return;

	FString ModalId;
	(*DataPtr)->TryGetStringField(TEXT("custom_id"), ModalId);

	// Only handle modals belonging to the admin panel.
	if (!ModalId.StartsWith(TEXT("panel_modal:"))) return;

	const TArray<FString> MemberRoles = ExtractMemberRoles(InteractionObj);
	const FString SenderName          = ExtractSenderName(InteractionObj);
	const FString StaffPrefix         = ResolveStaffPrefix(MemberRoles);

	// Set PendingAuthorId so ExecutePanel* audit-log calls get the Discord
	// snowflake as adminUid (matching the slash-command path).
	PendingAuthorId = ExtractSenderId(InteractionObj);
	struct FPanelAuthorIdGuard
	{
		FString& Ref;
		explicit FPanelAuthorIdGuard(FString& R) : Ref(R) {}
		~FPanelAuthorIdGuard() { Ref = FString(); }
	} PanelAuthorGuard(PendingAuthorId);

	// Helper: extract a named text-input field from the nested components array.
	// Discord MODAL_SUBMIT structure:
	//   data.components[]         = ACTION_ROWs
	//   data.components[i].components[0]  = TEXT_INPUT
	auto GetField = [&DataPtr](const FString& FieldId) -> FString
	{
		const TArray<TSharedPtr<FJsonValue>>* Rows = nullptr;
		if (!(*DataPtr)->TryGetArrayField(TEXT("components"), Rows) || !Rows)
			return FString();
		for (const TSharedPtr<FJsonValue>& RowVal : *Rows)
		{
			const TSharedPtr<FJsonObject>* RowPtr = nullptr;
			if (!RowVal->TryGetObject(RowPtr) || !RowPtr) continue;
			const TArray<TSharedPtr<FJsonValue>>* FieldArr = nullptr;
			if (!(*RowPtr)->TryGetArrayField(TEXT("components"), FieldArr) || !FieldArr) continue;
			for (const TSharedPtr<FJsonValue>& FV : *FieldArr)
			{
				const TSharedPtr<FJsonObject>* FP = nullptr;
				if (!FV->TryGetObject(FP) || !FP) continue;
				FString FId;
				if (!(*FP)->TryGetStringField(TEXT("custom_id"), FId)) continue;
				if (!FId.Equals(FieldId, ESearchCase::IgnoreCase)) continue;
				FString FVal;
				(*FP)->TryGetStringField(TEXT("value"), FVal);
				return FVal.TrimStartAndEnd();
			}
		}
		return FString();
	};

	const FString Action = ModalId.Mid(12); // strip "panel_modal:"
	FString ResultMsg;
	bool bPostToModLog = false;

	if (Action == TEXT("kick"))
	{
		if (!IsModeratorMember(MemberRoles))
		{
			CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
				TEXT("❌ Moderator role required."), true);
			return;
		}
		const FString Player = GetField(TEXT("panel_player"));
		if (Player.IsEmpty())
		{
			ResultMsg = TEXT("❌ Player name or PUID is required.");
		}
		else
		{
			ResultMsg     = ExecutePanelKick(Player, GetField(TEXT("panel_reason")), SenderName, StaffPrefix);
			// Feature 10: FBanDiscordNotifier::NotifyPlayerKicked already handles logging.
			bPostToModLog = false;
		}
	}
	else if (Action == TEXT("mute"))
	{
		if (!IsModeratorMember(MemberRoles))
		{
			CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
				TEXT("❌ Moderator role required."), true);
			return;
		}
		const FString Player = GetField(TEXT("panel_player"));
		if (Player.IsEmpty())
		{
			ResultMsg = TEXT("❌ Player name or PUID is required.");
		}
		else
		{
			ResultMsg     = ExecutePanelMute(Player, GetField(TEXT("panel_duration")),
			                                GetField(TEXT("panel_reason")), SenderName, StaffPrefix);
			bPostToModLog = !ResultMsg.StartsWith(TEXT("❌")) && !ResultMsg.StartsWith(TEXT("⚠️"));
		}
	}
	else if (Action == TEXT("announce"))
	{
		if (!IsModeratorMember(MemberRoles))
		{
			CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
				TEXT("❌ Moderator role required."), true);
			return;
		}
		const FString Message = GetField(TEXT("panel_message"));
		if (Message.IsEmpty())
		{
			ResultMsg = TEXT("❌ Message is required.");
		}
		else
		{
			ResultMsg     = ExecutePanelAnnounce(Message, SenderName);
			bPostToModLog = !ResultMsg.StartsWith(TEXT("❌"));
		}
	}
	else if (Action == TEXT("ban"))
	{
		if (!IsAdminMember(MemberRoles))
		{
			CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
				TEXT("❌ Admin role required."), true);
			return;
		}
		// Feature 8: Confirmation guard for permanent ban.
		const FString Confirm = GetField(TEXT("panel_confirm"));
		if (!Confirm.Equals(TEXT("CONFIRM"), ESearchCase::IgnoreCase))
		{
			CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
				TEXT("❌ Permanent ban cancelled — you must type **CONFIRM** exactly in the confirmation field."),
				true);
			return;
		}
		const FString Player = GetField(TEXT("panel_player"));
		if (Player.IsEmpty())
		{
			ResultMsg = TEXT("❌ Player name or PUID is required.");
		}
		else
		{
			ResultMsg = ExecutePanelBan(Player, GetField(TEXT("panel_reason")), SenderName, StaffPrefix);
			// Feature 10: FBanDiscordNotifier::NotifyBanCreated already posts to
			// ModerationLogChannelId, so skip the duplicate plain-text log here.
			bPostToModLog = false;
		}
	}
	else if (Action == TEXT("tempban"))
	{
		if (!IsAdminMember(MemberRoles))
		{
			CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
				TEXT("❌ Admin role required."), true);
			return;
		}
		const FString Player   = GetField(TEXT("panel_player"));
		const FString Duration = GetField(TEXT("panel_duration"));
		if (Player.IsEmpty() || Duration.IsEmpty())
		{
			ResultMsg = TEXT("❌ Player and duration are required.");
		}
		else
		{
			ResultMsg = ExecutePanelTempBan(Player, Duration,
			                               GetField(TEXT("panel_reason")), SenderName, StaffPrefix);
			// Feature 10: FBanDiscordNotifier::NotifyBanCreated already handles logging.
			bPostToModLog = false;
		}
	}
	else if (Action == TEXT("warn"))
	{
		if (!IsAdminMember(MemberRoles))
		{
			CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
				TEXT("❌ Admin role required."), true);
			return;
		}
		const FString Player = GetField(TEXT("panel_player"));
		const FString Reason = GetField(TEXT("panel_reason"));
		if (Player.IsEmpty() || Reason.IsEmpty())
		{
			ResultMsg = TEXT("❌ Player and reason are required.");
		}
		else
		{
			ResultMsg = ExecutePanelWarn(Player, Reason, SenderName, StaffPrefix);
			// Feature 10: FBanDiscordNotifier::NotifyWarningIssued already handles logging.
			bPostToModLog = false;
		}
	}
	// Feature 4: Unban (admin).
	else if (Action == TEXT("unban"))
	{
		if (!IsAdminMember(MemberRoles))
		{
			CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
				TEXT("❌ Admin role required."), true);
			return;
		}
		const FString Player = GetField(TEXT("panel_player"));
		if (Player.IsEmpty())
		{
			ResultMsg = TEXT("❌ Player name or PUID is required.");
		}
		else
		{
			ResultMsg     = ExecutePanelUnban(Player, SenderName, StaffPrefix);
			bPostToModLog = !ResultMsg.StartsWith(TEXT("❌")) && !ResultMsg.StartsWith(TEXT("ℹ️"));
		}
	}
	// Feature 4: Unmute (mod).
	else if (Action == TEXT("unmute"))
	{
		if (!IsModeratorMember(MemberRoles))
		{
			CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
				TEXT("❌ Moderator role required."), true);
			return;
		}
		const FString Player = GetField(TEXT("panel_player"));
		if (Player.IsEmpty())
		{
			ResultMsg = TEXT("❌ Player name or PUID is required.");
		}
		else
		{
			ResultMsg     = ExecutePanelUnmute(Player, SenderName, StaffPrefix);
			bPostToModLog = !ResultMsg.StartsWith(TEXT("❌")) && !ResultMsg.StartsWith(TEXT("⚠️"));
		}
	}
	// Feature 6: Ban check (mod).
	else if (Action == TEXT("bancheck"))
	{
		if (!IsModeratorMember(MemberRoles))
		{
			CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
				TEXT("❌ Moderator role required."), true);
			return;
		}
		const FString Player = GetField(TEXT("panel_player"));
		if (Player.IsEmpty())
		{
			ResultMsg = TEXT("❌ Player name or PUID is required.");
		}
		else
		{
			ResultMsg     = ExecutePanelBanCheck(Player);
			bPostToModLog = false; // read-only, no log needed
		}
	}
	// Warn list (admin).
	else if (Action == TEXT("warnlist"))
	{
		if (!IsAdminMember(MemberRoles))
		{
			CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
				TEXT("❌ Admin role required."), true);
			return;
		}
		const FString Player = GetField(TEXT("panel_player"));
		if (Player.IsEmpty())
		{
			ResultMsg = TEXT("❌ Player name or PUID is required.");
		}
		else
		{
			ResultMsg     = ExecutePanelWarnList(Player);
			bPostToModLog = false; // read-only
		}
	}
	// Player history (admin).
	else if (Action == TEXT("history"))
	{
		if (!IsAdminMember(MemberRoles))
		{
			CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
				TEXT("❌ Admin role required."), true);
			return;
		}
		const FString Player = GetField(TEXT("panel_player"));
		if (Player.IsEmpty())
		{
			ResultMsg = TEXT("❌ Player name, PUID, or IP is required.");
		}
		else
		{
			ResultMsg     = ExecutePanelHistory(Player);
			bPostToModLog = false; // read-only
		}
	}
	// Mute check (mod).
	else if (Action == TEXT("mutecheck"))
	{
		if (!IsModeratorMember(MemberRoles))
		{
			CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
				TEXT("❌ Moderator role required."), true);
			return;
		}
		const FString Player = GetField(TEXT("panel_player"));
		if (Player.IsEmpty())
		{
			ResultMsg = TEXT("❌ Player name or PUID is required.");
		}
		else
		{
			ResultMsg     = ExecutePanelMuteCheck(Player);
			bPostToModLog = false; // read-only
		}
	}
	// Freeze — toggle movement freeze (admin).
	else if (Action == TEXT("freeze"))
	{
		if (!IsAdminMember(MemberRoles))
		{
			CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
				TEXT("❌ Admin role required."), true);
			return;
		}
		const FString Player = GetField(TEXT("panel_player"));
		if (Player.IsEmpty())
		{
			ResultMsg = TEXT("❌ Player name or PUID is required.");
		}
		else
		{
			ResultMsg     = ExecutePanelFreeze(Player, SenderName);
			bPostToModLog = !ResultMsg.StartsWith(TEXT("❌")) && !ResultMsg.StartsWith(TEXT("⚠️"));
		}
	}
	// Clear Chat — flush in-game chat (admin).
	else if (Action == TEXT("clearchat"))
	{
		if (!IsAdminMember(MemberRoles))
		{
			CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
				TEXT("❌ Admin role required."), true);
			return;
		}
		ResultMsg     = ExecutePanelClearChat(GetField(TEXT("panel_reason")), SenderName);
		bPostToModLog = !ResultMsg.StartsWith(TEXT("❌"));
	}
	else
	{
		ResultMsg = FString::Printf(TEXT("❌ Unknown panel modal action `%s`."), *Action);
	}

	// Respond to the modal-submit interaction with the result (ephemeral).
	if (!ResultMsg.IsEmpty())
	{
		CachedProvider->RespondToInteraction(InteractionId, InteractionToken, 4,
			ResultMsg, true);
	}

	if (bPostToModLog)
		PostModerationLog(ResultMsg);
}

// ─────────────────────────────────────────────────────────────────────────────
// Admin panel — action executors
// ─────────────────────────────────────────────────────────────────────────────

FString UBanDiscordSubsystem::ExecutePanelKick(const FString& PlayerArg,
                                                const FString& Reason,
                                                const FString& SenderName,
                                                const FString& StaffPrefix)
{
	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(PlayerArg, Uid, DisplayName, ErrorMsg))
		return ErrorMsg;

	UGameInstance* GI = GetGameInstance();
	UWorld* World = GI ? GI->GetWorld() : nullptr;
	if (!World)
		return TEXT("❌ No active game world found. Is the server running?");

	const FString KickReason = Reason.IsEmpty() ? TEXT("Kicked by Discord admin") : Reason;
	const bool bKicked = UBanEnforcer::KickConnectedPlayer(World, Uid, KickReason);

	if (bKicked)
	{
		FBanDiscordNotifier::NotifyPlayerKicked(DisplayName, KickReason, SenderName);
		FString Msg = FString::Printf(
			TEXT("✅ Kicked **%s** (`%s`).\nReason: %s\nKicked by: %s"),
			*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
			*BanDiscordHelpers::EscapeMarkdown(KickReason),
			*BanDiscordHelpers::EscapeMarkdown(SenderName));
		Msg += BanDiscordHelpers::FormatPlayerLookup(this, Uid);
		UE_LOG(LogBanDiscord, Log,
		       TEXT("BanDiscordSubsystem: [Panel] %s kicked %s (%s). Reason: %s"),
		       *SenderName, *DisplayName, *Uid, *KickReason);

		// Write to audit log so panel-issued kicks appear alongside slash-command kicks.
		if (UGameInstance* GI = GetGameInstance())
		{
			if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
				AuditLog->LogAction(TEXT("kick"), Uid, DisplayName, GetCurrentAuditAdminUid(SenderName), SenderName, KickReason);
		}

		SendInGameModerationNoticeToUid(Uid, FString::Printf(
			TEXT("%s Kicked @%s. Reason: %s. By: %s."),
			*StaffPrefix, *DisplayName, *KickReason, *SenderName));
		PostToPlayerModerationThread(DisplayName, Uid, Msg);
		return Msg;
	}
	return FString::Printf(
		TEXT("⚠️ Player **%s** (`%s`) is not currently connected."),
		*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid);
}

FString UBanDiscordSubsystem::ExecutePanelBan(const FString& PlayerArg,
                                               const FString& Reason,
                                               const FString& SenderName,
                                               const FString& StaffPrefix)
{
	UBanDatabase* DB = BanDiscordHelpers::GetDB(this);
	if (!DB)
		return TEXT("❌ BanSystem is not available on this server.");

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(PlayerArg, Uid, DisplayName, ErrorMsg))
		return ErrorMsg;

	FBanEntry Entry;
	Entry.Uid          = Uid;
	UBanDatabase::ParseUid(Uid, Entry.Platform, Entry.PlayerUID);
	Entry.PlayerName   = DisplayName;
	Entry.Reason       = Reason.IsEmpty() ? TEXT("No reason given") : Reason;
	Entry.BannedBy     = SenderName;
	Entry.BanDate      = FDateTime::UtcNow();
	Entry.bIsPermanent = true;
	Entry.ExpireDate   = FDateTime(0);

	bool bPanelPermSkipped = false;
	if (!DB->AddBanSkipIfPermanentExists(Entry, bPanelPermSkipped))
	{
		if (bPanelPermSkipped)
			return TEXT("⚠️ Player already has a permanent ban — no duplicate record created.");
		return TEXT("❌ Failed to write the ban to the database. Check server logs.");
	}

	if (UWorld* World = GetGameInstance() ? GetGameInstance()->GetWorld() : nullptr)
		UBanEnforcer::KickConnectedPlayer(World, Uid, Entry.GetKickMessage());

	BanDiscordHelpers::AddCounterpartBans(this, DB, Uid, DisplayName,
		Entry.Reason, SenderName, /*bPermanent=*/true, FDateTime(0));

	FBanDiscordNotifier::NotifyBanCreated(Entry);

	FString Msg = FString::Printf(
		TEXT("✅ **%s** (`%s`) has been **permanently** banned.\nReason: %s\nBanned by: %s"),
		*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
		*BanDiscordHelpers::EscapeMarkdown(Entry.Reason),
		*BanDiscordHelpers::EscapeMarkdown(SenderName));
	Msg += BanDiscordHelpers::FormatPlayerLookup(this, Uid);

	UE_LOG(LogBanDiscord, Log,
	       TEXT("BanDiscordSubsystem: [Panel] %s permanently banned %s (%s). Reason: %s"),
	       *SenderName, *DisplayName, *Uid, *Entry.Reason);

	// Write to audit log so panel-issued bans appear alongside slash-command and REST bans.
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
			AuditLog->LogAction(TEXT("ban"), Uid, DisplayName, GetCurrentAuditAdminUid(SenderName), SenderName, Entry.Reason);
	}

	SendInGameModerationNoticeToUid(Uid, FString::Printf(
		TEXT("%s Permanently banned @%s. Reason: %s. By: %s."),
		*StaffPrefix, *DisplayName, *Entry.Reason, *SenderName));
	PostToPlayerModerationThread(DisplayName, Uid, Msg);
	return Msg;
}

FString UBanDiscordSubsystem::ExecutePanelTempBan(const FString& PlayerArg,
                                                   const FString& DurationArg,
                                                   const FString& Reason,
                                                   const FString& SenderName,
                                                   const FString& StaffPrefix)
{
	UBanDatabase* DB = BanDiscordHelpers::GetDB(this);
	if (!DB)
		return TEXT("❌ BanSystem is not available on this server.");

	const int32 DurationMinutes = ParseDurationMinutes(DurationArg);
	if (DurationMinutes <= 0)
	{
		return FString::Printf(
			TEXT("❌ Invalid duration `%s`. Use formats like: 30m, 2h, 1d, 1w."),
			*DurationArg);
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(PlayerArg, Uid, DisplayName, ErrorMsg))
		return ErrorMsg;

	FBanEntry Entry;
	Entry.Uid          = Uid;
	UBanDatabase::ParseUid(Uid, Entry.Platform, Entry.PlayerUID);
	Entry.PlayerName   = DisplayName;
	Entry.Reason       = Reason.IsEmpty() ? TEXT("No reason given") : Reason;
	Entry.BannedBy     = SenderName;
	const FDateTime TempBanNow2 = FDateTime::UtcNow();
	Entry.BanDate      = TempBanNow2;
	Entry.bIsPermanent = false;
	Entry.ExpireDate   = TempBanNow2 + FTimespan::FromMinutes(DurationMinutes);

	// ExecutePanelTempBan always issues a temporary ban; use AddBanSkipIfPermanentExists
	// to prevent silently downgrading an existing permanent ban.
	bool bPanelTempSkipped = false;
	if (!DB->AddBanSkipIfPermanentExists(Entry, bPanelTempSkipped))
	{
		if (bPanelTempSkipped)
			return FString::Printf(
				TEXT("⚠️ **%s** already has a permanent ban — the temporary ban was not applied."),
				*BanDiscordHelpers::EscapeMarkdown(DisplayName));
		return TEXT("❌ Failed to write the ban to the database. Check server logs.");
	}

	if (UWorld* World = GetGameInstance() ? GetGameInstance()->GetWorld() : nullptr)
		UBanEnforcer::KickConnectedPlayer(World, Uid, Entry.GetKickMessage());

	BanDiscordHelpers::AddCounterpartBans(this, DB, Uid, DisplayName,
		Entry.Reason, SenderName, /*bPermanent=*/false, Entry.ExpireDate);

	FBanDiscordNotifier::NotifyBanCreated(Entry);

	FString Msg = FString::Printf(
		TEXT("✅ **%s** (`%s`) has been temporarily banned for **%s**.\n"
		     "Expires: %s\nReason: %s\nBanned by: %s"),
		*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
		*BanDiscordHelpers::FormatDuration(DurationMinutes),
		*BanDiscordHelpers::FormatExpiry(Entry),
		*BanDiscordHelpers::EscapeMarkdown(Entry.Reason),
		*BanDiscordHelpers::EscapeMarkdown(SenderName));
	Msg += BanDiscordHelpers::FormatPlayerLookup(this, Uid);

	UE_LOG(LogBanDiscord, Log,
	       TEXT("BanDiscordSubsystem: [Panel] %s temp-banned %s (%s) for %s. Reason: %s"),
	       *SenderName, *DisplayName, *Uid, *BanDiscordHelpers::FormatDuration(DurationMinutes), *Entry.Reason);

	// Write to audit log so panel-issued temp-bans appear alongside slash-command and REST bans.
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
			AuditLog->LogAction(TEXT("tempban"), Uid, DisplayName, GetCurrentAuditAdminUid(SenderName), SenderName, Entry.Reason);
	}

	SendInGameModerationNoticeToUid(Uid, FString::Printf(
		TEXT("%s Temporarily banned @%s for %s. Reason: %s. By: %s."),
		*StaffPrefix, *DisplayName, *BanDiscordHelpers::FormatDuration(DurationMinutes), *Entry.Reason, *SenderName));
	PostToPlayerModerationThread(DisplayName, Uid, Msg);
	return Msg;
}

FString UBanDiscordSubsystem::ExecutePanelWarn(const FString& PlayerArg,
                                                const FString& Reason,
                                                const FString& SenderName,
                                                const FString& StaffPrefix)
{
	UGameInstance* GI = GetGameInstance();
	UPlayerWarningRegistry* WarnReg =
		GI ? GI->GetSubsystem<UPlayerWarningRegistry>() : nullptr;
	if (!WarnReg)
		return TEXT("❌ The warn command requires the BanSystem mod to be installed.");

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(PlayerArg, Uid, DisplayName, ErrorMsg))
		return ErrorMsg;

	WarnReg->AddWarning(Uid, DisplayName, Reason, SenderName);
	const int32 WarnCount  = WarnReg->GetWarningCount(Uid);
	const int32 WarnPoints = WarnReg->GetWarningPoints(Uid);

	FBanDiscordNotifier::NotifyWarningIssued(Uid, DisplayName, Reason, SenderName, WarnCount);

	UE_LOG(LogBanDiscord, Log,
	       TEXT("BanDiscordSubsystem: [Panel] %s warned %s (%s). Reason: %s"),
	       *SenderName, *DisplayName, *Uid, *Reason);

	// Write to audit log so panel-issued warns appear alongside slash-command and REST warns.
	if (UBanAuditLog* AuditLog = GI ? GI->GetSubsystem<UBanAuditLog>() : nullptr)
		AuditLog->LogAction(TEXT("warn"), Uid, DisplayName, GetCurrentAuditAdminUid(SenderName), SenderName, Reason);

	// Auto-ban escalation — mirrors BanRestApi, BanChatCommands, and HandleWarnCommand warn paths.
	{
		const UBanSystemConfig* SysCfg = UBanSystemConfig::Get();
		if (SysCfg && GI)
		{
			int32 BanDurationMinutes = -1;
			if (SysCfg->WarnEscalationTiers.Num() > 0)
			{
				// Apply the most severe tier that has been reached.
				// Compare by DurationMinutes: 0 means permanent (most severe);
				// among temporary bans, the longest duration wins.
				// This avoids the old BestThreshold comparison which mixed
				// point-threshold and warn-count values numerically (incomparable units).
				for (const FWarnEscalationTier& Tier : SysCfg->WarnEscalationTiers)
				{
					const bool bHit = (Tier.PointThreshold > 0)
						? (WarnPoints >= Tier.PointThreshold)
						: (WarnCount  >= Tier.WarnCount);
					if (!bHit) continue;

					const bool bMoreSevere = (BanDurationMinutes < 0)
						|| (BanDurationMinutes != 0 && (Tier.DurationMinutes == 0
							|| Tier.DurationMinutes > BanDurationMinutes));
					if (bMoreSevere)
						BanDurationMinutes = Tier.DurationMinutes;
				}
			}
			else if (SysCfg->AutoBanWarnCount > 0 && WarnCount >= SysCfg->AutoBanWarnCount)
			{
				BanDurationMinutes = SysCfg->AutoBanWarnMinutes;
			}

			if (BanDurationMinutes >= 0)
			{
				if (UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>())
				{
					// Use AddBanSkipIfPermanentExists so the check-and-add is
					// atomic under the database lock, eliminating the TOCTOU
					// window that existed when IsCurrentlyBannedByAnyId and
					// AddBan were called as two separate steps.
					FBanEntry AutoBan;
					AutoBan.Uid        = Uid;
					UBanDatabase::ParseUid(Uid, AutoBan.Platform, AutoBan.PlayerUID);
					AutoBan.PlayerName   = DisplayName;
					AutoBan.Reason       = TEXT("Auto-banned: reached warning threshold");
					AutoBan.BannedBy     = SenderName;
					const FDateTime AutoNow2 = FDateTime::UtcNow();
					AutoBan.BanDate      = AutoNow2;
					AutoBan.bIsPermanent = (BanDurationMinutes <= 0);
					AutoBan.ExpireDate   = AutoBan.bIsPermanent
						? FDateTime(0)
						: AutoNow2 + FTimespan::FromMinutes(BanDurationMinutes);
					bool bSkipped2 = false;
					if (DB->AddBanSkipIfPermanentExists(AutoBan, bSkipped2))
					{
						if (UWorld* World = GI->GetWorld())
							UBanEnforcer::KickConnectedPlayer(World, Uid, AutoBan.GetKickMessage());
						BanDiscordHelpers::AddCounterpartBans(this, DB, Uid, DisplayName,
							AutoBan.Reason, SenderName, AutoBan.bIsPermanent, AutoBan.ExpireDate);
						FBanDiscordNotifier::NotifyBanCreated(AutoBan);
						FBanDiscordNotifier::NotifyAutoEscalationBan(AutoBan, WarnCount);
						if (UBanAuditLog* AL = GI->GetSubsystem<UBanAuditLog>())
							AL->LogAction(TEXT("ban"), Uid, DisplayName,
								GetCurrentAuditAdminUid(SenderName), SenderName, AutoBan.Reason);
					}
				}
			}
		}
	}

	SendInGameModerationNoticeToUid(Uid, FString::Printf(
		TEXT("%s Warned @%s. Reason: %s. Total warnings: %d. By: %s."),
		*StaffPrefix, *DisplayName, *Reason, WarnCount, *SenderName));

	const FString WarnMsg = FString::Printf(
		TEXT("⚠️ Warned **%s** (`%s`).\nReason: %s\nTotal warnings: **%d**\nWarned by: %s"),
		*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
		*BanDiscordHelpers::EscapeMarkdown(Reason), WarnCount,
		*BanDiscordHelpers::EscapeMarkdown(SenderName));
	PostToPlayerModerationThread(DisplayName, Uid, WarnMsg);
	return WarnMsg;
}

FString UBanDiscordSubsystem::ExecutePanelMute(const FString& PlayerArg,
                                                const FString& DurationArg,
                                                const FString& Reason,
                                                const FString& SenderName,
                                                const FString& StaffPrefix)
{
	UGameInstance* GI = GetGameInstance();
	UMuteRegistry* MuteReg = GI ? GI->GetSubsystem<UMuteRegistry>() : nullptr;
	if (!MuteReg)
		return TEXT("❌ Mute requires the BanChatCommands mod to be installed.");

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(PlayerArg, Uid, DisplayName, ErrorMsg))
		return ErrorMsg;

	// Use ParseDurationMinutes() so "30m", "2h", "7d" formats are accepted.
	// A non-empty but unparseable duration (returns <= 0) is an error rather
	// than a silent fallback to indefinite — report it to the caller.
	int32 Minutes = 0;
	if (!DurationArg.IsEmpty())
	{
		Minutes = ParseDurationMinutes(DurationArg);
		if (Minutes <= 0)
		{
			return FString::Printf(
				TEXT("❌ Invalid duration `%s`. Use formats like: 30m, 2h, 1d, 1w."),
				*DurationArg);
		}
	}

	const FString MuteReason = Reason.IsEmpty() ? TEXT("Muted by Discord admin") : Reason;
	MuteReg->MutePlayer(Uid, DisplayName, MuteReason, SenderName, Minutes);

	const FString DurStr = (Minutes > 0)
		? BanDiscordHelpers::FormatDuration(Minutes)
		: TEXT("indefinitely");

	UE_LOG(LogBanDiscord, Log,
	       TEXT("BanDiscordSubsystem: [Panel] %s muted %s (%s) for %s. Reason: %s"),
	       *SenderName, *DisplayName, *Uid, *DurStr, *MuteReason);

	// Write to audit log so panel-issued mutes appear alongside slash-command mutes.
	if (UBanAuditLog* AuditLog = GI ? GI->GetSubsystem<UBanAuditLog>() : nullptr)
		AuditLog->LogAction(TEXT("mute"), Uid, DisplayName, GetCurrentAuditAdminUid(SenderName), SenderName, MuteReason);

	SendInGameModerationNoticeToUid(Uid, FString::Printf(
		TEXT("%s Muted @%s for %s. Reason: %s. By: %s."),
		*StaffPrefix, *DisplayName, *DurStr, *MuteReason, *SenderName));

	const FString MuteMsg = FString::Printf(
		TEXT("🔇 Muted **%s** (`%s`) for %s.\nReason: %s\nMuted by: %s"),
		*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid, *DurStr,
		*BanDiscordHelpers::EscapeMarkdown(MuteReason),
		*BanDiscordHelpers::EscapeMarkdown(SenderName));
	PostToPlayerModerationThread(DisplayName, Uid, MuteMsg);
	return MuteMsg;
}

FString UBanDiscordSubsystem::ExecutePanelAnnounce(const FString& Message,
                                                    const FString& SenderName)
{
	UGameInstance* GI = GetGameInstance();
	UWorld* World = GI ? GI->GetWorld() : nullptr;
	if (!World)
		return TEXT("❌ No active game world found. Is the server running?");

	int32 Delivered = 0;
	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC)
		{
			PC->ClientMessage(FString::Printf(TEXT("[Announcement] %s"), *Message));
			++Delivered;
		}
	}

	UE_LOG(LogBanDiscord, Log,
	       TEXT("BanDiscordSubsystem: [Panel] %s announced to %d player(s): %s"),
	       *SenderName, Delivered, *Message);

	return FString::Printf(
		TEXT("📢 Announcement sent to **%d** player(s):\n> %s\nSent by: %s"),
		Delivered,
		*BanDiscordHelpers::EscapeMarkdown(Message),
		*BanDiscordHelpers::EscapeMarkdown(SenderName));
}

FString UBanDiscordSubsystem::ExecutePanelBanList() const
{
	UBanDatabase* DB = BanDiscordHelpers::GetDB(this);
	if (!DB)
		return TEXT("❌ BanSystem is not available on this server.");

	DB->ReloadIfChanged();
	TArray<FBanEntry> ActiveBans = DB->GetActiveBans();

	if (ActiveBans.IsEmpty())
		return TEXT("✅ No active bans.");

	const int32 Total      = ActiveBans.Num();
	const int32 TotalPages = FMath::DivideAndRoundUp(Total, BanDiscordHelpers::BanListPageSize);

	FString Body;
	Body.Reserve(1600);
	Body += TEXT("```\n");
	Body += FString::Printf(TEXT("%-4s  %-22s  %-16s  %-20s  %s\n"),
	                        TEXT("ID"), TEXT("UID (truncated)"),
	                        TEXT("Name"), TEXT("Expires"), TEXT("Reason"));
	Body += BanDiscordHelpers::SepLine(80) + TEXT("\n");

	const int32 EndIdx = FMath::Min(BanDiscordHelpers::BanListPageSize, Total);
	for (int32 i = 0; i < EndIdx; ++i)
	{
		const FBanEntry& E = ActiveBans[i];
		const FString UidShort    = BanDiscordHelpers::Truncate(E.Uid, 22);
		const FString NameShort   = BanDiscordHelpers::SanitizeForCodeBlock(BanDiscordHelpers::Truncate(E.PlayerName, 16));
		const FString ExpiryShort = E.bIsPermanent
			? TEXT("permanent")
			: E.ExpireDate.ToString(TEXT("%m-%d %H:%M UTC"));
		const FString ReasonShort = BanDiscordHelpers::SanitizeForCodeBlock(BanDiscordHelpers::Truncate(E.Reason, 28));
		Body += FString::Printf(TEXT("%-4lld  %-22s  %-16s  %-20s  %s\n"),
		                        E.Id, *UidShort, *NameShort, *ExpiryShort, *ReasonShort);
	}
	Body += TEXT("```");

	const FString Header = FString::Printf(
		TEXT("**Active Bans — Page 1/%d (%d total)**\n"), TotalPages, Total);

	FString Msg = Header + Body;
	if (Msg.Len() > 1990)
		Msg = Msg.Left(1940) + TEXT("\n...(truncated)```");
	return Msg;
}

FString UBanDiscordSubsystem::ExecutePanelPlayers() const
{
	UGameInstance* GI = GetGameInstance();
	UWorld* World = GI ? GI->GetWorld() : nullptr;
	if (!World)
		return TEXT("❌ No active game world found. Is the server running?");

	TArray<FString> Names;
	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (!PC) continue;
		APlayerState* PS = PC->GetPlayerState<APlayerState>();
		if (!PS) continue;
		Names.Add(BanDiscordHelpers::EscapeMarkdown(PS->GetPlayerName()));
	}

	if (Names.IsEmpty())
		return TEXT("👥 No players are currently connected.");

	FString Msg = FString::Printf(TEXT("👥 **Online Players (%d):**\n"), Names.Num());
	for (int32 i = 0; i < Names.Num(); ++i)
		Msg += FString::Printf(TEXT("%d. %s\n"), i + 1, *Names[i]);

	if (Msg.Len() > 1990)
		Msg = Msg.Left(1960) + TEXT("...");
	return Msg.TrimEnd();
}

FString UBanDiscordSubsystem::ExecutePanelStaffList() const
{
	const UBanChatCommandsConfig* BccCfg = UBanChatCommandsConfig::Get();
	if (!BccCfg)
		return TEXT("❌ Staff list requires the BanChatCommands mod to be installed.");

	UGameInstance* GI = GetGameInstance();
	UWorld* World = GI ? GI->GetWorld() : nullptr;
	if (!World)
		return TEXT("❌ No active game world found.");

	TArray<FString> Admins;
	TArray<FString> Mods;

	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (!PC) continue;
		APlayerState* PS = PC->GetPlayerState<APlayerState>();
		if (!PS) continue;

		FString PUIDStr;
		if (const FUniqueNetIdRepl& Id = PS->GetUniqueId(); Id.IsValid())
		{
			PUIDStr = Id.ToString();
			FString Platform, RawId;
			UBanDatabase::ParseUid(PUIDStr, Platform, RawId);
			if (Platform == TEXT("EOS")) PUIDStr = RawId;
		}
		const FString CompoundUid = TEXT("EOS:") + PUIDStr.ToLower();
		const FString PlayerName  = BanDiscordHelpers::EscapeMarkdown(PS->GetPlayerName());

		if (BccCfg->IsAdminUid(CompoundUid))
			Admins.Add(PlayerName);
		else if (BccCfg->IsModeratorUid(CompoundUid))
			Mods.Add(PlayerName);
	}

	if (Admins.IsEmpty() && Mods.IsEmpty())
		return TEXT("📋 No staff are currently online.");

	FString Msg = TEXT("📋 **Online Staff:**\n");
	if (!Admins.IsEmpty())
		Msg += FString::Printf(TEXT("🛡️ **Admins:** %s\n"), *FString::Join(Admins, TEXT(", ")));
	if (!Mods.IsEmpty())
		Msg += FString::Printf(TEXT("🔧 **Moderators:** %s\n"), *FString::Join(Mods, TEXT(", ")));
	return Msg.TrimEnd();
}

FString UBanDiscordSubsystem::ExecutePanelReloadConfig(const FString& SenderName)
{
	Config = FBanBridgeConfig::Load();

	// Refresh the cached FDiscordBridgeConfig fields used by BuildPanelData()
	// and PostModerationLog() so changes to ServerName / BanEventsChannelId
	// take effect immediately without a server restart.
	{
		const FDiscordBridgeConfig DiscordCfg = FDiscordBridgeConfig::LoadOrCreate();
		CachedDiscordServerName  = DiscordCfg.ServerName;
		CachedBanEventsChannelId = DiscordCfg.BanEventsChannelId;
	}

	UE_LOG(LogBanDiscord, Log,
	       TEXT("BanDiscordSubsystem: [Panel] Config reloaded by %s."), *SenderName);
	return FString::Printf(TEXT("✅ BanBridge configuration reloaded by **%s**."), *BanDiscordHelpers::EscapeMarkdown(SenderName));
}

// ─────────────────────────────────────────────────────────────────────────────
// Admin panel — Feature 4: Unban / Unmute executors
// ─────────────────────────────────────────────────────────────────────────────

FString UBanDiscordSubsystem::ExecutePanelUnban(const FString& PlayerArg,
                                                 const FString& SenderName,
                                                 const FString& StaffPrefix)
{
	UBanDatabase* DB = BanDiscordHelpers::GetDB(this);
	if (!DB)
		return TEXT("❌ BanSystem is not available on this server.");

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(PlayerArg, Uid, DisplayName, ErrorMsg))
		return ErrorMsg;

	// Use the atomic RemoveBanByUid overload to capture the removed ban entry
	// and delete it in a single mutex scope, eliminating the TOCTOU window that
	// exists when GetBanByUid() and RemoveBanByUid() are called as two separate
	// operations (the ban record, including LinkedUids, could be modified between
	// the two calls).
	FBanEntry BanRecord;
	if (!DB->RemoveBanByUid(Uid, BanRecord))
	{
		const FString Msg = FString::Printf(
			TEXT("ℹ️ No active ban record found for **%s** (`%s`) — player is already unbanned.\nUnbanned by: %s"),
			*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
			*BanDiscordHelpers::EscapeMarkdown(SenderName));
		UE_LOG(LogBanDiscord, Log,
		       TEXT("BanDiscordSubsystem: [Panel] %s unbanned %s (%s) — no record in DB."),
		       *SenderName, *DisplayName, *Uid);
		return Msg;
	}

	// RemoveBanByUid returned true, so BanRecord is fully populated from the
	// removed entry — use its LinkedUids to clean up any counterpart bans.
	int32 ExtraRemoved = 0;
	if (!BanRecord.LinkedUids.IsEmpty())
		ExtraRemoved = BanDiscordHelpers::RemoveCounterpartBans(this, DB, Uid, BanRecord.LinkedUids);

	FBanDiscordNotifier::NotifyBanRemoved(Uid, DisplayName, SenderName);

	FString Msg = FString::Printf(
		TEXT("✅ Ban removed for **%s** (`%s`).\nUnbanned by: %s"),
		*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
		*BanDiscordHelpers::EscapeMarkdown(SenderName));
	if (ExtraRemoved > 0)
		Msg += FString::Printf(TEXT("\nAlso removed %d linked ban(s)."), ExtraRemoved);

	UE_LOG(LogBanDiscord, Log,
	       TEXT("BanDiscordSubsystem: [Panel] %s unbanned %s (%s)."),
	       *SenderName, *DisplayName, *Uid);

	// Write to audit log so panel-issued unbans appear alongside slash-command and REST unbans.
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
			AuditLog->LogAction(TEXT("unban"), Uid, DisplayName, GetCurrentAuditAdminUid(SenderName), SenderName, TEXT(""));
	}

	SendInGameModerationNoticeToUid(Uid, FString::Printf(
		TEXT("%s Unbanned @%s. By: %s."),
		*StaffPrefix, *DisplayName, *SenderName));
	PostToPlayerModerationThread(DisplayName, Uid, Msg);
	return Msg;
}

FString UBanDiscordSubsystem::ExecutePanelUnmute(const FString& PlayerArg,
                                                  const FString& SenderName,
                                                  const FString& StaffPrefix)
{
	UGameInstance* GI = GetGameInstance();
	UMuteRegistry* MuteReg = GI ? GI->GetSubsystem<UMuteRegistry>() : nullptr;
	if (!MuteReg)
		return TEXT("❌ Unmute requires the BanChatCommands mod to be installed.");

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(PlayerArg, Uid, DisplayName, ErrorMsg))
		return ErrorMsg;

	if (!MuteReg->UnmutePlayer(Uid))
	{
		return FString::Printf(
			TEXT("⚠️ **%s** (`%s`) is not currently muted."),
			*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid);
	}

	UE_LOG(LogBanDiscord, Log,
	       TEXT("BanDiscordSubsystem: [Panel] %s unmuted %s (%s)."),
	       *SenderName, *DisplayName, *Uid);

	// Write to audit log so panel-issued unmutes appear alongside slash-command unmutes.
	if (UBanAuditLog* AuditLog = GI ? GI->GetSubsystem<UBanAuditLog>() : nullptr)
		AuditLog->LogAction(TEXT("unmute"), Uid, DisplayName, GetCurrentAuditAdminUid(SenderName), SenderName, TEXT(""));

	SendInGameModerationNoticeToUid(Uid, FString::Printf(
		TEXT("%s Unmuted @%s. By: %s."),
		*StaffPrefix, *DisplayName, *SenderName));

	const FString UnmuteMsg = FString::Printf(
		TEXT("✅ Unmuted **%s** (`%s`).\nUnmuted by: %s"),
		*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
		*BanDiscordHelpers::EscapeMarkdown(SenderName));
	PostToPlayerModerationThread(DisplayName, Uid, UnmuteMsg);
	return UnmuteMsg;
}

// ─────────────────────────────────────────────────────────────────────────────
// Admin panel — Feature 6: Ban check executor
// ─────────────────────────────────────────────────────────────────────────────

FString UBanDiscordSubsystem::ExecutePanelBanCheck(const FString& PlayerArg) const
{
	UBanDatabase* DB = BanDiscordHelpers::GetDB(this);
	if (!DB)
		return TEXT("❌ BanSystem is not available on this server.");

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(PlayerArg, Uid, DisplayName, ErrorMsg))
		return ErrorMsg;

	DB->ReloadIfChanged();

	FBanEntry Entry;
	const bool bBanned = DB->IsCurrentlyBannedByAnyId(Uid, Entry);

	FString Msg;
	if (bBanned)
	{
		Msg = FString::Printf(
			TEXT("🔨 **%s** (`%s`) is **currently banned**.\n"
			     "Reason: %s\n"
			     "Banned by: %s\n"
			     "Ban date: %s UTC\n"
			     "Expires: %s"),
			*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
			*BanDiscordHelpers::EscapeMarkdown(Entry.Reason),
			*BanDiscordHelpers::EscapeMarkdown(Entry.BannedBy),
			*Entry.BanDate.ToString(TEXT("%Y-%m-%d %H:%M:%S")),
			*BanDiscordHelpers::FormatExpiry(Entry));

		if (Entry.LinkedUids.Num() > 0)
			Msg += FString::Printf(TEXT("\nLinked UIDs: `%s`"),
			                       *FString::Join(Entry.LinkedUids, TEXT("`, `")));
	}
	else
	{
		FBanEntry AnyEntry;
		if (DB->GetBanByUid(Uid, AnyEntry))
		{
			Msg = FString::Printf(
				TEXT("✅ **%s** (`%s`) is **not currently banned**.\n"
				     "(Expired ban record: reason: %s, expired: %s)"),
				*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
				*BanDiscordHelpers::EscapeMarkdown(AnyEntry.Reason),
				*BanDiscordHelpers::FormatExpiry(AnyEntry));
		}
		else
		{
			Msg = FString::Printf(
				TEXT("✅ **%s** (`%s`) is **not banned**."),
				*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid);
		}
	}

	Msg += BanDiscordHelpers::FormatPlayerLookup(this, Uid);
	if (Msg.Len() > 1990)
		Msg = Msg.Left(1987) + TEXT("...");
	return Msg;
}

// ─────────────────────────────────────────────────────────────────────────────
// Admin panel — Warn list / Mute check / Mute list / Player history executors
// ─────────────────────────────────────────────────────────────────────────────

FString UBanDiscordSubsystem::ExecutePanelWarnList(const FString& PlayerArg) const
{
	UGameInstance* GI = GetGameInstance();
	UPlayerWarningRegistry* WarnReg =
		GI ? GI->GetSubsystem<UPlayerWarningRegistry>() : nullptr;
	if (!WarnReg)
		return TEXT("❌ The warnings system requires the BanSystem mod to be installed.");

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(PlayerArg, Uid, DisplayName, ErrorMsg))
		return ErrorMsg;

	TArray<FWarningEntry> Warnings = WarnReg->GetWarningsForUid(Uid);
	if (Warnings.IsEmpty())
	{
		return FString::Printf(
			TEXT("✅ No warnings on record for **%s** (`%s`)."),
			*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid);
	}

	FString Body;
	Body.Reserve(1400);
	Body += TEXT("```\n");
	Body += FString::Printf(TEXT("%-4s  %-20s  %-12s  %s\n"),
		TEXT("ID"), TEXT("Date (UTC)"), TEXT("By"), TEXT("Reason"));
	Body += BanDiscordHelpers::SepLine(72) + TEXT("\n");

	const int32 ShowMax = FMath::Min(Warnings.Num(), 15);
	for (int32 i = 0; i < ShowMax; ++i)
	{
		const FWarningEntry& W = Warnings[i];
		const FString DateStr  = W.WarnDate.ToString(TEXT("%m-%d %H:%M"));
		const FString ByShort  = BanDiscordHelpers::SanitizeForCodeBlock(BanDiscordHelpers::Truncate(W.WarnedBy, 12));
		const FString ReasonSh = BanDiscordHelpers::SanitizeForCodeBlock(BanDiscordHelpers::Truncate(W.Reason, 40));
		Body += FString::Printf(TEXT("%-4lld  %-20s  %-12s  %s\n"),
			W.Id, *DateStr, *ByShort, *ReasonSh);
	}
	Body += TEXT("```");

	FString Header = FString::Printf(
		TEXT("**Warnings for %s** (`%s`) — %d total\n"),
		*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid, Warnings.Num());
	if (Warnings.Num() > ShowMax)
		Header += FString::Printf(TEXT("_(Showing first %d)_\n"), ShowMax);

	FString Msg = Header + Body;
	if (Msg.Len() > 1990)
		Msg = Msg.Left(1940) + TEXT("\n...(truncated)```");
	return Msg;
}

FString UBanDiscordSubsystem::ExecutePanelMuteCheck(const FString& PlayerArg) const
{
	UGameInstance* GI = GetGameInstance();
	UMuteRegistry* MuteReg = GI ? GI->GetSubsystem<UMuteRegistry>() : nullptr;
	if (!MuteReg)
		return TEXT("❌ Mute check requires the BanChatCommands mod to be installed.");

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(PlayerArg, Uid, DisplayName, ErrorMsg))
		return ErrorMsg;

	FMuteEntry Entry;
	if (!MuteReg->GetMuteEntry(Uid, Entry))
	{
		return FString::Printf(
			TEXT("🔊 **%s** (`%s`) is **not currently muted**."),
			*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid);
	}

	FString ExpiryStr;
	if (Entry.bIsIndefinite)
	{
		ExpiryStr = TEXT("**indefinitely**");
	}
	else
	{
		const FTimespan Remaining = Entry.ExpireDate - FDateTime::UtcNow();
		const double RawMinsMC = Remaining.GetTotalMinutes();
		const int32 TotalMins = (FMath::IsFinite(RawMinsMC) && RawMinsMC > 0.0)
			? static_cast<int32>(FMath::Min(static_cast<int64>(RawMinsMC), static_cast<int64>(INT32_MAX)))
			: 0;
		ExpiryStr = FString::Printf(TEXT("for **%s** more (expires %s UTC)"),
			*BanDiscordHelpers::FormatDuration(TotalMins),
			*Entry.ExpireDate.ToString(TEXT("%Y-%m-%d %H:%M:%S")));
	}

	return FString::Printf(
		TEXT("🔇 **%s** (`%s`) is muted %s.\nReason: %s\nMuted by: %s"),
		*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
		*ExpiryStr,
		*BanDiscordHelpers::EscapeMarkdown(Entry.Reason),
		*BanDiscordHelpers::EscapeMarkdown(Entry.MutedBy));
}

FString UBanDiscordSubsystem::ExecutePanelMuteList() const
{
	UGameInstance* GI = GetGameInstance();
	UMuteRegistry* MuteReg = GI ? GI->GetSubsystem<UMuteRegistry>() : nullptr;
	if (!MuteReg)
		return TEXT("❌ Mute list requires the BanChatCommands mod to be installed.");

	TArray<FMuteEntry> Mutes = MuteReg->GetAllMutes();
	if (Mutes.IsEmpty())
		return TEXT("🔊 No players are currently muted.");

	FString Body;
	Body.Reserve(1400);
	Body += TEXT("```\n");
	Body += FString::Printf(TEXT("%-18s  %-30s  %-18s  %s\n"),
		TEXT("Name"), TEXT("UID (truncated)"), TEXT("Expires"), TEXT("Reason"));
	Body += BanDiscordHelpers::SepLine(80) + TEXT("\n");

	const int32 ShowMax = FMath::Min(Mutes.Num(), 15);
	for (int32 i = 0; i < ShowMax; ++i)
	{
		const FMuteEntry& M = Mutes[i];
		const FString NameSh   = BanDiscordHelpers::Truncate(M.PlayerName, 18);
		const FString UidSh    = BanDiscordHelpers::Truncate(M.Uid, 30);
		const FString ExpirySh = M.bIsIndefinite
			? TEXT("permanent")
			: M.ExpireDate.ToString(TEXT("%m-%d %H:%M UTC"));
		const FString ReasonSh = BanDiscordHelpers::Truncate(M.Reason, 24);
		Body += FString::Printf(TEXT("%-18s  %-30s  %-18s  %s\n"),
			*NameSh, *UidSh, *ExpirySh, *ReasonSh);
	}
	Body += TEXT("```");

	FString Header = FString::Printf(TEXT("**Muted Players — %d total**\n"), Mutes.Num());
	if (Mutes.Num() > ShowMax)
		Header += FString::Printf(TEXT("_(Showing first %d)_\n"), ShowMax);

	FString Msg = Header + Body;
	if (Msg.Len() > 1990)
		Msg = Msg.Left(1940) + TEXT("\n...(truncated)```");
	return Msg;
}

FString UBanDiscordSubsystem::ExecutePanelAppeals() const
{
	UGameInstance* GI = GetGameInstance();
	UBanAppealRegistry* AppealReg = GI ? GI->GetSubsystem<UBanAppealRegistry>() : nullptr;
	if (!AppealReg)
		return TEXT("❌ BanAppealRegistry is not available (BanSystem may not be installed).");

	TArray<FBanAppealEntry> AllAppeals = AppealReg->GetAllAppeals();

	// Filter to pending only.
	TArray<FBanAppealEntry> Pending;
	for (const FBanAppealEntry& E : AllAppeals)
	{
		if (E.Status == EAppealStatus::Pending)
			Pending.Add(E);
	}

	if (Pending.IsEmpty())
		return TEXT("✅ No pending ban appeals.");

	FString Body;
	Body.Reserve(1400);
	Body += TEXT("```\n");
	Body += FString::Printf(TEXT("%-6s  %-36s  %-22s\n"),
		TEXT("ID"), TEXT("UID"), TEXT("Submitted"));
	Body += BanDiscordHelpers::SepLine(68) + TEXT("\n");

	const int32 ShowMax = FMath::Min(Pending.Num(), 15);
	for (int32 i = 0; i < ShowMax; ++i)
	{
		const FBanAppealEntry& E = Pending[i];
		const FString UidSh      = BanDiscordHelpers::Truncate(E.Uid, 36);
		const FString SubmittedSh = E.SubmittedAt.ToString(TEXT("%m-%d %H:%M UTC"));
		Body += FString::Printf(TEXT("%-6lld  %-36s  %-22s\n"),
			E.Id, *UidSh, *SubmittedSh);
	}
	Body += TEXT("```");

	FString Header = FString::Printf(TEXT("**Pending Ban Appeals — %d total**\n"), Pending.Num());
	if (Pending.Num() > ShowMax)
		Header += FString::Printf(TEXT("_(Showing first %d. Use `/appeal list` for full list.)_\n"), ShowMax);

	FString Msg = Header + Body;
	if (Msg.Len() > 1990)
		Msg = Msg.Left(1940) + TEXT("\n...(truncated)```");
	return Msg;
}

FString UBanDiscordSubsystem::ExecutePanelHistory(const FString& PlayerArg) const
{
	UPlayerSessionRegistry* Registry = BanDiscordHelpers::GetRegistry(this);
	if (!Registry)
		return TEXT("❌ PlayerSessionRegistry is not available on this server.");

	TArray<FPlayerSessionRecord> Results;

	FString Platform, RawId;
	UBanDatabase::ParseUid(PlayerArg, Platform, RawId);
	if (Platform == TEXT("EOS") && IsValidEOSPUID(RawId))
	{
		FPlayerSessionRecord Record;
		if (Registry->FindByUid(UBanDatabase::MakeUid(TEXT("EOS"), RawId.ToLower()), Record))
			Results.Add(Record);
	}
	else if (IsValidEOSPUID(PlayerArg))
	{
		FPlayerSessionRecord Record;
		if (Registry->FindByUid(UBanDatabase::MakeUid(TEXT("EOS"), PlayerArg.ToLower()), Record))
			Results.Add(Record);
	}
	else if (IsValidIPQuery(PlayerArg))
	{
		const FString IpQuery = (Platform == TEXT("IP")) ? RawId : PlayerArg;
		Results = Registry->FindByIp(IpQuery);
	}
	else
	{
		Results = Registry->FindByName(PlayerArg);
	}

	if (Results.IsEmpty())
	{
		return FString::Printf(
			TEXT("⚠️ No session records found for `%s`."),
			*BanDiscordHelpers::EscapeMarkdown(PlayerArg));
	}

	constexpr int32 MaxResults = 10;
	const int32 ShowCount = FMath::Min(Results.Num(), MaxResults);

	FString Body;
	Body.Reserve(1500);
	Body += TEXT("```\n");
	Body += FString::Printf(TEXT("%-16s  %-40s  %-15s  %-20s\n"),
		TEXT("Name"), TEXT("UID"), TEXT("IP"), TEXT("Last Seen (UTC)"));
	Body += BanDiscordHelpers::SepLine(97) + TEXT("\n");

	for (int32 i = 0; i < ShowCount; ++i)
	{
		const FPlayerSessionRecord& R = Results[i];
		const FString NameShort = BanDiscordHelpers::SanitizeForCodeBlock(BanDiscordHelpers::Truncate(R.DisplayName, 16));
		const FString UidShort  = BanDiscordHelpers::Truncate(R.Uid, 40);
		const FString IpShort   = R.IpAddress.IsEmpty()
			? TEXT("—")
			: BanDiscordHelpers::Truncate(R.IpAddress, 15);
		const FString LastSeen  = BanDiscordHelpers::Truncate(R.LastSeen, 20);
		Body += FString::Printf(TEXT("%-16s  %-40s  %-15s  %s\n"),
			*NameShort, *UidShort, *IpShort, *LastSeen);
	}
	Body += TEXT("```");

	FString Header = FString::Printf(
		TEXT("**Player History for `%s`** (%d record(s))\n"),
		*BanDiscordHelpers::EscapeMarkdown(PlayerArg), Results.Num());
	if (Results.Num() > MaxResults)
		Header += FString::Printf(TEXT("_(Showing first %d of %d results)_\n"),
			MaxResults, Results.Num());

	FString Msg = Header + Body;
	if (Msg.Len() > 1990)
		Msg = Msg.Left(1940) + TEXT("\n...(truncated)```");
	return Msg;
}

// ─────────────────────────────────────────────────────────────────────────────
// /mod freeze  — toggle player movement freeze
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleFreezeCommand(const TArray<FString>& Args,
                                                const FString& ChannelId,
                                                const FString& SenderName)
{
	if (!CachedProvider) return;
	if (Args.IsEmpty() || Args[0].IsEmpty())
	{
		Respond(ChannelId, TEXT("❌ Usage: `/mod freeze <player|PUID>`"));
		return;
	}

	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(Args[0], Uid, DisplayName, ErrorMsg))
	{
		Respond(ChannelId, ErrorMsg);
		return;
	}

	UGameInstance* GI = GetGameInstance();
	UWorld* World = GI ? GI->GetWorld() : nullptr;
	if (!World)
	{
		Respond(ChannelId, TEXT("❌ No active game world. Is the server running?"));
		return;
	}

	const bool bWasFrozen = AFreezeChatCommand::FrozenPlayerUids.Contains(Uid);

	if (bWasFrozen)
	{
		for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
		{
			APlayerController* PC = It->Get();
			if (!PC || !PC->PlayerState) continue;
			const FUniqueNetIdRepl& NetId = PC->PlayerState->GetUniqueId();
			if (!NetId.IsValid() || NetId.GetType() == FName(TEXT("NONE"))) continue;
			if (UBanDatabase::MakeUid(TEXT("EOS"), NetId.ToString().ToLower()) == Uid)
			{
				PC->SetIgnoreMoveInput(false);
				break;
			}
		}
		// Always remove from frozen set — if the player is offline the UID removal
		// prevents them from being re-frozen on reconnect after an admin un-froze them.
		AFreezeChatCommand::FrozenPlayerUids.Remove(Uid);
		const FString ResultMsg = FString::Printf(
			TEXT("🔓 **%s** (`%s`) has been **unfrozen** by **%s**."),
			*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
			*BanDiscordHelpers::EscapeMarkdown(SenderName));
		Respond(ChannelId, ResultMsg);
		PostModerationLog(ResultMsg);
		if (UGameInstance* GI2 = GetGameInstance())
			if (UBanAuditLog* AL = GI2->GetSubsystem<UBanAuditLog>())
				AL->LogAction(TEXT("unfreeze"), Uid, DisplayName, GetCurrentAuditAdminUid(SenderName), SenderName, TEXT(""));
		UE_LOG(LogBanDiscord, Log,
		       TEXT("BanDiscordSubsystem: %s unfroze %s (%s)."),
		       *SenderName, *DisplayName, *Uid);
	}
	else
	{
		for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
		{
			APlayerController* PC = It->Get();
			if (!PC || !PC->PlayerState) continue;
			const FUniqueNetIdRepl& NetId = PC->PlayerState->GetUniqueId();
			if (!NetId.IsValid() || NetId.GetType() == FName(TEXT("NONE"))) continue;
			if (UBanDatabase::MakeUid(TEXT("EOS"), NetId.ToString().ToLower()) == Uid)
			{
				PC->SetIgnoreMoveInput(true);
				break;
			}
		}
		// Always add to frozen set — ensures offline players are frozen when they reconnect.
		AFreezeChatCommand::FrozenPlayerUids.Add(Uid);
		const FString ResultMsg = FString::Printf(
			TEXT("❄️ **%s** (`%s`) has been **frozen** by **%s**. Use `/mod freeze` again to unfreeze."),
			*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
			*BanDiscordHelpers::EscapeMarkdown(SenderName));
		Respond(ChannelId, ResultMsg);
		PostModerationLog(ResultMsg);
		if (UGameInstance* GI2 = GetGameInstance())
			if (UBanAuditLog* AL = GI2->GetSubsystem<UBanAuditLog>())
				AL->LogAction(TEXT("freeze"), Uid, DisplayName, GetCurrentAuditAdminUid(SenderName), SenderName, TEXT(""));
		UE_LOG(LogBanDiscord, Log,
		       TEXT("BanDiscordSubsystem: %s froze %s (%s)."),
		       *SenderName, *DisplayName, *Uid);
	}
}

// ─────────────────────────────────────────────────────────────────────────────
// /admin clearchat  — flush in-game chat and notify staff
// ─────────────────────────────────────────────────────────────────────────────

void UBanDiscordSubsystem::HandleClearChatCommand(const TArray<FString>& Args,
                                                   const FString& ChannelId,
                                                   const FString& SenderName)
{
	if (!CachedProvider) return;

	const FString Reason = Args.IsEmpty() || Args[0].IsEmpty()
		? TEXT("Chat cleared by administrator")
		: BanDiscordHelpers::JoinArgs(Args, 0);

	UGameInstance* GI = GetGameInstance();
	UWorld* World = GI ? GI->GetWorld() : nullptr;
	if (!World)
	{
		Respond(ChannelId, TEXT("❌ No active game world. Is the server running?"));
		return;
	}

	// Broadcast blank lines to visually scroll chat off screen.
	// D-1: build one 30-line blank string and send once per player, not 30 RPCs each.
	FString Blanks;
	for (int32 i = 0; i < 30; ++i) Blanks += TEXT("\n");
	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
		if (APlayerController* PC = It->Get())
			PC->ClientMessage(Blanks);

	// Notify all connected players.
	const FString Notice = FString::Printf(
		TEXT("Chat has been cleared by %s. Reason: %s"), *SenderName, *Reason);
	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
		if (APlayerController* PC = It->Get())
			PC->ClientMessage(Notice);

	const FString ResultMsg = FString::Printf(
		TEXT("🧹 **Chat cleared** by **%s**.\nReason: %s"),
			*BanDiscordHelpers::EscapeMarkdown(SenderName),
			*BanDiscordHelpers::EscapeMarkdown(Reason));
	Respond(ChannelId, ResultMsg);
	PostModerationLog(ResultMsg);
	if (UGameInstance* GI2 = GetGameInstance())
		if (UBanAuditLog* AL = GI2->GetSubsystem<UBanAuditLog>())
			AL->LogAction(TEXT("clearchat"), TEXT(""), TEXT(""), GetCurrentAuditAdminUid(SenderName), SenderName, Reason);
	UE_LOG(LogBanDiscord, Log,
	       TEXT("BanDiscordSubsystem: %s cleared in-game chat. Reason: %s"),
	       *SenderName, *Reason);
}

// ─────────────────────────────────────────────────────────────────────────────
// Admin panel — Freeze / ClearChat executors
// ─────────────────────────────────────────────────────────────────────────────

FString UBanDiscordSubsystem::ExecutePanelFreeze(const FString& PlayerArg,
                                                  const FString& SenderName)
{
	FString Uid, DisplayName, ErrorMsg;
	if (!ResolveTarget(PlayerArg, Uid, DisplayName, ErrorMsg))
		return ErrorMsg;

	UGameInstance* GI = GetGameInstance();
	UWorld* World = GI ? GI->GetWorld() : nullptr;
	if (!World)
		return TEXT("❌ No active game world. Is the server running?");

	const bool bWasFrozen = AFreezeChatCommand::FrozenPlayerUids.Contains(Uid);

	if (bWasFrozen)
	{
		// Always update FrozenPlayerUids regardless of online status; SetIgnoreMoveInput
		// only has an effect if the player is currently in the world.
		for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
		{
			APlayerController* PC = It->Get();
			if (!PC || !PC->PlayerState) continue;
			const FUniqueNetIdRepl& NetId = PC->PlayerState->GetUniqueId();
			if (!NetId.IsValid() || NetId.GetType() == FName(TEXT("NONE"))) continue;
			if (UBanDatabase::MakeUid(TEXT("EOS"), NetId.ToString().ToLower()) == Uid)
			{
				PC->SetIgnoreMoveInput(false);
				break;
			}
		}
		// Always remove from frozen set so offline players are not re-frozen on reconnect.
		AFreezeChatCommand::FrozenPlayerUids.Remove(Uid);
		UE_LOG(LogBanDiscord, Log,
		       TEXT("BanDiscordSubsystem: [Panel] %s unfroze %s (%s)."),
		       *SenderName, *DisplayName, *Uid);
		if (GI)
			if (UBanAuditLog* AL = GI->GetSubsystem<UBanAuditLog>())
				AL->LogAction(TEXT("unfreeze"), Uid, DisplayName, GetCurrentAuditAdminUid(SenderName), SenderName, TEXT(""));
		return FString::Printf(
			TEXT("🔓 **%s** (`%s`) has been **unfrozen** by **%s**."),
			*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
			*BanDiscordHelpers::EscapeMarkdown(SenderName));
	}
	else
	{
		// Always update FrozenPlayerUids regardless of online status; SetIgnoreMoveInput
		// only has an effect if the player is currently in the world.
		for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
		{
			APlayerController* PC = It->Get();
			if (!PC || !PC->PlayerState) continue;
			const FUniqueNetIdRepl& NetId = PC->PlayerState->GetUniqueId();
			if (!NetId.IsValid() || NetId.GetType() == FName(TEXT("NONE"))) continue;
			if (UBanDatabase::MakeUid(TEXT("EOS"), NetId.ToString().ToLower()) == Uid)
			{
				PC->SetIgnoreMoveInput(true);
				break;
			}
		}
		// Always add to frozen set so offline players are frozen when they reconnect.
		AFreezeChatCommand::FrozenPlayerUids.Add(Uid);
		UE_LOG(LogBanDiscord, Log,
		       TEXT("BanDiscordSubsystem: [Panel] %s froze %s (%s)."),
		       *SenderName, *DisplayName, *Uid);
		if (GI)
			if (UBanAuditLog* AL = GI->GetSubsystem<UBanAuditLog>())
				AL->LogAction(TEXT("freeze"), Uid, DisplayName, GetCurrentAuditAdminUid(SenderName), SenderName, TEXT(""));
		return FString::Printf(
			TEXT("❄️ **%s** (`%s`) has been **frozen** by **%s**."
			     " Use the Freeze button again to unfreeze."),
			*BanDiscordHelpers::EscapeMarkdown(DisplayName), *Uid,
			*BanDiscordHelpers::EscapeMarkdown(SenderName));
	}
}

FString UBanDiscordSubsystem::ExecutePanelClearChat(const FString& Reason,
                                                     const FString& SenderName)
{
	UGameInstance* GI = GetGameInstance();
	UWorld* World = GI ? GI->GetWorld() : nullptr;
	if (!World)
		return TEXT("❌ No active game world. Is the server running?");

	const FString EffectiveReason = Reason.IsEmpty()
		? TEXT("Chat cleared by administrator")
		: Reason;

	// Broadcast blank lines to visually scroll chat off screen.
	// D-1: build one 30-line blank string and send once per player, not 30 RPCs each.
	FString Blanks;
	for (int32 i = 0; i < 30; ++i) Blanks += TEXT("\n");
	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
		if (APlayerController* PC = It->Get())
			PC->ClientMessage(Blanks);

	// Notify all connected players.
	const FString Notice = FString::Printf(
		TEXT("Chat has been cleared by %s. Reason: %s"), *SenderName, *EffectiveReason);
	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
		if (APlayerController* PC = It->Get())
			PC->ClientMessage(Notice);

	UE_LOG(LogBanDiscord, Log,
	       TEXT("BanDiscordSubsystem: [Panel] %s cleared in-game chat. Reason: %s"),
	       *SenderName, *EffectiveReason);
	if (GI)
		if (UBanAuditLog* AL = GI->GetSubsystem<UBanAuditLog>())
			AL->LogAction(TEXT("clearchat"), TEXT(""), TEXT(""), GetCurrentAuditAdminUid(SenderName), SenderName, EffectiveReason);
	return FString::Printf(
		TEXT("🧹 **Chat cleared** by **%s**.\nReason: %s"),
		*BanDiscordHelpers::EscapeMarkdown(SenderName),
		*BanDiscordHelpers::EscapeMarkdown(EffectiveReason));
}

// Copyright Yamahasxviper. All Rights Reserved.

#include "BanDiscordNotifier.h"
#include "BanSystemConfig.h"
#include "BanWebSocketPusher.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

DEFINE_LOG_CATEGORY(LogBanDiscordNotifier);

// Static delegate definition.
FBanDiscordNotifier::FOnPlayerKickedLogged FBanDiscordNotifier::OnPlayerKickedLogged;

// ─────────────────────────────────────────────────────────────────────────────
//  Helpers
// ─────────────────────────────────────────────────────────────────────────────

namespace
{
    /** Escapes a string for inclusion as a JSON string value. */
    FString JsonEscape(const FString& In)
    {
        FString Out;
        Out.Reserve(In.Len() + 8);
        for (TCHAR C : In)
        {
            switch (C)
            {
            case TEXT('"'):  Out += TEXT("\\\""); break;
            case TEXT('\\'): Out += TEXT("\\\\"); break;
            case TEXT('\n'): Out += TEXT("\\n");  break;
            case TEXT('\r'): Out += TEXT("\\r");  break;
            case TEXT('\t'): Out += TEXT("\\t");  break;
            default:
                // RFC 8259 §7: all control characters U+0000–U+001F must be escaped.
                if (C < 0x20)
                    Out += FString::Printf(TEXT("\\u%04x"), static_cast<uint32>(C));
                // RFC 8259 §8.2: lone surrogate code-points U+D800–U+DFFF produce
                // invalid JSON.  Replace with U+FFFD (replacement character) so the
                // output is always valid JSON regardless of the player name content.
                else if (C >= 0xD800 && C <= 0xDFFF)
                    Out += TEXT("\uFFFD");
                else
                    Out += C;
                break;
            }
        }
        return Out;
    }

    /**
     * Escape Discord markdown special characters in a player-supplied string so
     * that it is rendered literally in Discord embed field values and cannot
     * inject bold/italic/code formatting or clickable links.
     */
    FString EscapeMarkdown(const FString& Text)
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

    /** Builds a Discord embed JSON string. */
    FString BuildEmbed(int32 Color, const FString& Title, const FString& FieldsJson)
    {
        return FString::Printf(
            TEXT("{\"embeds\":[{\"title\":\"%s\",\"color\":%d,\"fields\":[%s],\"timestamp\":\"%s\"}]}"),
            *JsonEscape(Title),
            Color,
            *FieldsJson,
            *FDateTime::UtcNow().ToIso8601());
    }

    /** Builds a single inline Discord embed field JSON fragment. */
    FString Field(const FString& Name, const FString& Value, bool bInline = true)
    {
        return FString::Printf(
            TEXT("{\"name\":\"%s\",\"value\":\"%s\",\"inline\":%s}"),
            *JsonEscape(Name),
            *JsonEscape(Value),
            bInline ? TEXT("true") : TEXT("false"));
    }
} // anonymous namespace

// ─────────────────────────────────────────────────────────────────────────────
//  PostWebhook
// ─────────────────────────────────────────────────────────────────────────────

void FBanDiscordNotifier::PostWebhook(const FString& JsonPayload)
{
    const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
    if (!Cfg || Cfg->DiscordWebhookUrl.IsEmpty())
        return;

    if (!FModuleManager::Get().IsModuleLoaded(TEXT("HTTP")))
        return;

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
        FHttpModule::Get().CreateRequest();

    Request->SetURL(Cfg->DiscordWebhookUrl);
    Request->SetVerb(TEXT("POST"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    Request->SetContentAsString(JsonPayload);
    Request->OnProcessRequestComplete().BindLambda(
        [](FHttpRequestPtr /*Req*/, FHttpResponsePtr Response, bool bConnectedSuccessfully)
        {
            if (!bConnectedSuccessfully || !Response || Response->GetResponseCode() / 100 != 2)
            {
                UE_LOG(LogBanDiscordNotifier, Warning,
                    TEXT("BanDiscordNotifier: Discord webhook delivery failed (HTTP %d)"),
                    Response ? Response->GetResponseCode() : 0);
            }
        });
    Request->ProcessRequest();
}

// ─────────────────────────────────────────────────────────────────────────────
//  Public notification methods
// ─────────────────────────────────────────────────────────────────────────────

void FBanDiscordNotifier::NotifyBanCreated(const FBanEntry& Entry)
{
    const FString PlayerValue = EscapeMarkdown(Entry.PlayerName) + TEXT(" (") + Entry.Uid + TEXT(")");
    const double RawMin0 = (Entry.ExpireDate - Entry.BanDate).GetTotalMinutes();
    const FString DurationValue = Entry.bIsPermanent
        ? TEXT("Permanent")
        : FString::Printf(TEXT("%lld minutes"),
            FMath::Max((int64)0,
                FMath::IsFinite(RawMin0) ? static_cast<int64>(RawMin0) : (int64)0));

    const FString Fields =
        Field(TEXT("Player"),    PlayerValue)                     + TEXT(",") +
        Field(TEXT("Reason"),    EscapeMarkdown(Entry.Reason))    + TEXT(",") +
        Field(TEXT("Duration"),  DurationValue)                   + TEXT(",") +
        Field(TEXT("Banned By"), EscapeMarkdown(Entry.BannedBy));

    // Red: 15158332
    PostWebhook(BuildEmbed(15158332, TEXT("🔨 Player Banned"), Fields));

    // WebSocket push
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("uid"),        Entry.Uid);
        Obj->SetStringField(TEXT("playerName"), Entry.PlayerName);
        Obj->SetStringField(TEXT("reason"),     Entry.Reason);
        Obj->SetStringField(TEXT("bannedBy"),   Entry.BannedBy);
        Obj->SetBoolField  (TEXT("permanent"),  Entry.bIsPermanent);
        if (!Entry.bIsPermanent)
            Obj->SetStringField(TEXT("expireDate"), Entry.ExpireDate.ToIso8601());
        UBanWebSocketPusher::PushEvent(TEXT("ban"), Obj);
    }
}

void FBanDiscordNotifier::NotifyBanRemoved(const FString& Uid, const FString& PlayerName,
                                           const FString& RemovedBy)
{
    const FString PlayerValue = PlayerName.IsEmpty()
        ? Uid
        : EscapeMarkdown(PlayerName) + TEXT(" (") + Uid + TEXT(")");

    const FString Fields =
        Field(TEXT("Player"),     PlayerValue)                     + TEXT(",") +
        Field(TEXT("Removed By"), EscapeMarkdown(RemovedBy));

    // Green: 3066993
    PostWebhook(BuildEmbed(3066993, TEXT("✅ Ban Removed"), Fields));

    // WebSocket push
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("uid"),        Uid);
        Obj->SetStringField(TEXT("playerName"), PlayerName);
        Obj->SetStringField(TEXT("removedBy"),  RemovedBy);
        UBanWebSocketPusher::PushEvent(TEXT("unban"), Obj);
    }
}

void FBanDiscordNotifier::NotifyWarningIssued(const FString& Uid, const FString& PlayerName,
                                              const FString& Reason, const FString& WarnedBy,
                                              int32 TotalWarnings)
{
    const FString PlayerValue = PlayerName.IsEmpty()
        ? Uid
        : EscapeMarkdown(PlayerName) + TEXT(" (") + Uid + TEXT(")");

    const FString Fields =
        Field(TEXT("Player"),         PlayerValue)                               + TEXT(",") +
        Field(TEXT("Reason"),         EscapeMarkdown(Reason))                    + TEXT(",") +
        Field(TEXT("Warned By"),      EscapeMarkdown(WarnedBy))                  + TEXT(",") +
        Field(TEXT("Total Warnings"), FString::FromInt(TotalWarnings));

    // Yellow: 16776960
    PostWebhook(BuildEmbed(16776960, TEXT("⚠️ Player Warned"), Fields));

    // WebSocket push
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("uid"),           Uid);
        Obj->SetStringField(TEXT("playerName"),    PlayerName);
        Obj->SetStringField(TEXT("reason"),        Reason);
        Obj->SetStringField(TEXT("warnedBy"),      WarnedBy);
        // int32 value — exactly representable in double; string encoding not needed.
        Obj->SetNumberField(TEXT("totalWarnings"), static_cast<double>(TotalWarnings));
        UBanWebSocketPusher::PushEvent(TEXT("warn"), Obj);
    }
}

void FBanDiscordNotifier::NotifyPlayerKicked(const FString& PlayerName, const FString& Reason,
                                             const FString& KickedBy, const FString& Uid)
{
    const FString Fields =
        Field(TEXT("Player"),    EscapeMarkdown(PlayerName)) + TEXT(",") +
        Field(TEXT("Reason"),    EscapeMarkdown(Reason))     + TEXT(",") +
        Field(TEXT("Kicked By"), EscapeMarkdown(KickedBy));

    // Red: 15158332
    PostWebhook(BuildEmbed(15158332, TEXT("👢 Player Kicked"), Fields));

    // WebSocket push
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("playerName"), PlayerName);
        Obj->SetStringField(TEXT("reason"),     Reason);
        Obj->SetStringField(TEXT("kickedBy"),   KickedBy);
        if (!Uid.IsEmpty())
            Obj->SetStringField(TEXT("uid"), Uid);
        UBanWebSocketPusher::PushEvent(TEXT("kick"), Obj);
    }

    // Allow BanDiscordSubsystem to route in-game kicks into per-player threads.
    // Only fired when the caller supplies a UID (in-game /kick); Discord slash-kick
    // handlers intentionally omit it, so those events are handled directly by
    // HandleKickCommand → PostToPlayerModerationThread.
    if (!Uid.IsEmpty())
        OnPlayerKickedLogged.Broadcast(Uid, PlayerName, Reason, KickedBy);
}

void FBanDiscordNotifier::NotifyAppealSubmitted(const FBanAppealEntry& Appeal)
{
    const FString PlayerValue = Appeal.Uid.IsEmpty() ? TEXT("(unknown)") : Appeal.Uid;
    const FString SubmittedStr = Appeal.SubmittedAt.ToString(TEXT("%Y-%m-%d %H:%M:%S")) + TEXT(" UTC");

    const FString Fields =
        Field(TEXT("UID"),         PlayerValue)        + TEXT(",") +
        Field(TEXT("Contact"),     EscapeMarkdown(Appeal.ContactInfo.IsEmpty() ? TEXT("(not provided)") : Appeal.ContactInfo)) + TEXT(",") +
        Field(TEXT("Submitted"),   SubmittedStr,   false) + TEXT(",") +
        Field(TEXT("Reason"),      EscapeMarkdown(Appeal.Reason),  false);

    // Blue-purple: 5793266
    PostWebhook(BuildEmbed(5793266,
        FString::Printf(TEXT("📩 Ban Appeal #%lld Submitted"), Appeal.Id),
        Fields));

    // WebSocket push
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("appealId"),    FString::Printf(TEXT("%lld"), Appeal.Id));
        Obj->SetStringField(TEXT("uid"),         Appeal.Uid);
        Obj->SetStringField(TEXT("contactInfo"), Appeal.ContactInfo);
        Obj->SetStringField(TEXT("reason"),      Appeal.Reason);
        Obj->SetStringField(TEXT("submittedAt"), Appeal.SubmittedAt.ToIso8601());
        UBanWebSocketPusher::PushEvent(TEXT("appeal_submitted"), Obj);
    }
}

void FBanDiscordNotifier::NotifyAutoEscalationBan(const FBanEntry& Ban, int32 WarnCount)
{
    const FString PlayerValue = Ban.PlayerName.IsEmpty()
        ? Ban.Uid
        : EscapeMarkdown(Ban.PlayerName) + TEXT(" (") + Ban.Uid + TEXT(")");

    const double RawMin1 = (Ban.ExpireDate - Ban.BanDate).GetTotalMinutes();
    const FString DurationValue = Ban.bIsPermanent
        ? TEXT("Permanent")
        : FString::Printf(TEXT("%lld minutes"),
            FMath::Max((int64)0,
                FMath::IsFinite(RawMin1) ? static_cast<int64>(RawMin1) : (int64)0));

    const FString Fields =
        Field(TEXT("Player"),       PlayerValue)                    + TEXT(",") +
        Field(TEXT("Warnings"),     FString::FromInt(WarnCount))    + TEXT(",") +
        Field(TEXT("Duration"),     DurationValue)                  + TEXT(",") +
        Field(TEXT("Reason"),       EscapeMarkdown(Ban.Reason), false);

    // Dark orange: 16742912
    PostWebhook(BuildEmbed(16742912,
        TEXT("⚡ Auto-Escalation Ban Issued (Review Required)"),
        Fields));

    // WebSocket push
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("uid"),        Ban.Uid);
        Obj->SetStringField(TEXT("playerName"), Ban.PlayerName);
        // int32 value — exactly representable in double; string encoding not needed.
        Obj->SetNumberField(TEXT("warnCount"),  static_cast<double>(WarnCount));
        Obj->SetBoolField  (TEXT("permanent"),  Ban.bIsPermanent);
        Obj->SetStringField(TEXT("reason"),     Ban.Reason);
        UBanWebSocketPusher::PushEvent(TEXT("auto_escalation_ban"), Obj);
    }
}

void FBanDiscordNotifier::NotifyBanExpired(const FBanEntry& Entry)
{
    const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
    if (!Cfg || !Cfg->bNotifyBanExpired) return;

    const FString PlayerValue = Entry.PlayerName.IsEmpty()
        ? Entry.Uid
        : EscapeMarkdown(Entry.PlayerName) + TEXT(" (") + Entry.Uid + TEXT(")");

    const FString ExpireStr = Entry.ExpireDate.ToString(TEXT("%Y-%m-%d %H:%M:%S")) + TEXT(" UTC");

    const FString Fields =
        Field(TEXT("Player"),     PlayerValue)                  + TEXT(",") +
        Field(TEXT("Reason"),     EscapeMarkdown(Entry.Reason)) + TEXT(",") +
        Field(TEXT("Expired At"), ExpireStr);

    // Grey-blue: 8421504
    PostWebhook(BuildEmbed(8421504, TEXT("⏱️ Temp-Ban Expired"), Fields));

    // WebSocket push
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("uid"),        Entry.Uid);
        Obj->SetStringField(TEXT("playerName"), Entry.PlayerName);
        Obj->SetStringField(TEXT("reason"),     Entry.Reason);
        Obj->SetStringField(TEXT("expireDate"), Entry.ExpireDate.ToIso8601());
        UBanWebSocketPusher::PushEvent(TEXT("ban_expired"), Obj);
    }
}

void FBanDiscordNotifier::NotifyAppealReviewed(const FBanAppealEntry& Appeal)
{
    const bool bApproved = (Appeal.Status == EAppealStatus::Approved);
    const FString StatusLabel = bApproved ? TEXT("✅ Approved") : TEXT("❌ Denied");
    const int32 Color         = bApproved ? 3066993 : 15158332; // green or red

    const FString Fields =
        Field(TEXT("Appeal #"),    FString::Printf(TEXT("%lld"), Appeal.Id)) + TEXT(",") +
        Field(TEXT("Player UID"),  Appeal.Uid)                               + TEXT(",") +
        Field(TEXT("Contact"),     EscapeMarkdown(Appeal.ContactInfo))       + TEXT(",") +
        Field(TEXT("Reviewed By"), EscapeMarkdown(Appeal.ReviewedBy.IsEmpty() ? TEXT("-") : Appeal.ReviewedBy)) + TEXT(",") +
        Field(TEXT("Note"),        EscapeMarkdown(Appeal.ReviewNote.IsEmpty() ? TEXT("-") : Appeal.ReviewNote), false);

    PostWebhook(BuildEmbed(Color,
        FString::Printf(TEXT("⚖️ Ban Appeal %s"), *StatusLabel),
        Fields));

    // WebSocket push
    {
        FString StatusStr;
        switch (Appeal.Status)
        {
        case EAppealStatus::Approved: StatusStr = TEXT("approved"); break;
        case EAppealStatus::Denied:   StatusStr = TEXT("denied");   break;
        default:                      StatusStr = TEXT("pending");  break;
        }

        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("appealId"),   FString::Printf(TEXT("%lld"), Appeal.Id));
        Obj->SetStringField(TEXT("uid"),        Appeal.Uid);
        Obj->SetStringField(TEXT("status"),     StatusStr);
        Obj->SetStringField(TEXT("reviewedBy"), Appeal.ReviewedBy);
        Obj->SetStringField(TEXT("reviewNote"), Appeal.ReviewNote);
        UBanWebSocketPusher::PushEvent(TEXT("appeal_reviewed"), Obj);
    }
}

void FBanDiscordNotifier::NotifyGeoIpBlocked(const FString& PlayerName, const FString& Uid,
                                              const FString& IpAddress, const FString& CountryCode)
{
    const FString PlayerValue = PlayerName.IsEmpty()
        ? Uid
        : EscapeMarkdown(PlayerName) + TEXT(" (") + Uid + TEXT(")");

    const FString Fields =
        Field(TEXT("Player"),      PlayerValue)   + TEXT(",") +
        Field(TEXT("IP"),          IpAddress)     + TEXT(",") +
        Field(TEXT("Country"),     CountryCode)   + TEXT(",") +
        Field(TEXT("Reason"),      TEXT("Geo-IP region blocked"), false);

    // Amber: 16744272
    PostWebhook(BuildEmbed(16744272, TEXT("🌍 Geo-IP Block"), Fields));

    // WebSocket push
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("uid"),         Uid);
        Obj->SetStringField(TEXT("playerName"),  PlayerName);
        Obj->SetStringField(TEXT("ipAddress"),   IpAddress);
        Obj->SetStringField(TEXT("countryCode"), CountryCode);
        UBanWebSocketPusher::PushEvent(TEXT("geoip_block"), Obj);
    }
}

void FBanDiscordNotifier::NotifyPlayerMuted(const FString& Uid, const FString& PlayerName,
                                             const FString& MutedBy, const FString& Reason,
                                             bool bIsTimed, const FDateTime& ExpireDate,
                                             const FDateTime& MuteDate)
{
    // Use MuteDate if provided (non-zero) so the shown duration equals the
    // configured value regardless of HTTP delivery delay.  Fall back to
    // UtcNow() for callers that do not supply a start time.
    const FDateTime EffectiveMuteDate = (MuteDate.GetTicks() > 0) ? MuteDate : FDateTime::UtcNow();
    const double RawMin2 = (ExpireDate - EffectiveMuteDate).GetTotalMinutes();
    const FString DurationStr = bIsTimed
        ? FString::Printf(TEXT("%lld min"), FMath::Max((int64)0,
              FMath::IsFinite(RawMin2) ? static_cast<int64>(RawMin2) : (int64)0))
        : TEXT("Indefinite");

    const FString Fields =
        Field(TEXT("Player"),   EscapeMarkdown(PlayerName))  + TEXT(",") +
        Field(TEXT("UID"),      Uid)                         + TEXT(",") +
        Field(TEXT("Muted By"), EscapeMarkdown(MutedBy))     + TEXT(",") +
        Field(TEXT("Duration"), DurationStr)                 + TEXT(",") +
        Field(TEXT("Reason"),   EscapeMarkdown(Reason), false);

    // Deep orange: 15105570
    PostWebhook(BuildEmbed(15105570, TEXT("🔇 Player Muted"), Fields));

    // WebSocket push
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("uid"),        Uid);
        Obj->SetStringField(TEXT("playerName"), PlayerName);
        Obj->SetStringField(TEXT("mutedBy"),    MutedBy);
        Obj->SetStringField(TEXT("reason"),     Reason);
        Obj->SetBoolField  (TEXT("isTimed"),    bIsTimed);
        if (bIsTimed)
            Obj->SetStringField(TEXT("expireDate"), ExpireDate.ToIso8601());
        UBanWebSocketPusher::PushEvent(TEXT("mute"), Obj);
    }
}

void FBanDiscordNotifier::NotifyPlayerUnmuted(const FString& Uid, const FString& PlayerName,
                                               const FString& UnmutedBy)
{
    const FString Fields =
        Field(TEXT("Player"),     EscapeMarkdown(PlayerName.IsEmpty() ? Uid : PlayerName)) + TEXT(",") +
        Field(TEXT("UID"),        Uid)                          + TEXT(",") +
        Field(TEXT("Unmuted By"), EscapeMarkdown(UnmutedBy), false);

    // Green: 3066993
    PostWebhook(BuildEmbed(3066993, TEXT("🔊 Player Unmuted"), Fields));

    // WebSocket push
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("uid"),        Uid);
        Obj->SetStringField(TEXT("playerName"), PlayerName);
        Obj->SetStringField(TEXT("unmutedBy"),  UnmutedBy);
        UBanWebSocketPusher::PushEvent(TEXT("unmute"), Obj);
    }
}

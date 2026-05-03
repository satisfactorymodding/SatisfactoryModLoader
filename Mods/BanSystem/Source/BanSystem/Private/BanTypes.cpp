// Copyright Yamahasxviper. All Rights Reserved.

#include "BanTypes.h"
#include "BanSystemConfig.h"

DEFINE_LOG_CATEGORY(LogBanTypes);

// ─────────────────────────────────────────────────────────────────────────────
//  FBanTemplate helpers
// ─────────────────────────────────────────────────────────────────────────────

bool FBanTemplate::FromConfigString(const FString& ConfigStr, FBanTemplate& OutTemplate)
{
    TArray<FString> Parts;
    ConfigStr.ParseIntoArray(Parts, TEXT("|"));
    if (Parts.Num() < 3) return false;

    OutTemplate.Slug = Parts[0];

    // H2: Reject templates whose duration field is non-numeric to avoid silent
    // 0-minute (permanent) bans from misconfigured or typo'd ini entries.
    for (TCHAR Ch : Parts[1])
    {
        if (!FChar::IsDigit(Ch) && Ch != TEXT('-'))
        {
            UE_LOG(LogBanTypes, Warning,
                TEXT("BanTypes: template slug='%s' has non-numeric durationMinutes '%s' — skipping"),
                *Parts[0], *Parts[1]);
            return false;
        }
    }
    // Use Atoi64 + clamp to safely handle very large digit strings that would
    // overflow FCString::Atoi (int32).  Values outside [INT32_MIN, INT32_MAX] are
    // clamped; negative values are treated as permanent (DurationMinutes <= 0).
    const int64 DurI64 = FCString::Atoi64(*Parts[1]);
    OutTemplate.DurationMinutes = static_cast<int32>(
        FMath::Clamp<int64>(DurI64, static_cast<int64>(INT32_MIN), static_cast<int64>(INT32_MAX)));
    OutTemplate.Reason          = Parts[2];
    OutTemplate.Category        = Parts.Num() > 3 ? Parts[3] : FString();
    return true;
}

TArray<FBanTemplate> FBanTemplate::ParseTemplates(const TArray<FString>& ConfigStrings)
{
    TArray<FBanTemplate> Result;
    Result.Reserve(ConfigStrings.Num());
    for (const FString& Str : ConfigStrings)
    {
        FBanTemplate T;
        if (FromConfigString(Str, T))
        {
            Result.Add(MoveTemp(T));
        }
    }
    return Result;
}

// ─────────────────────────────────────────────────────────────────────────────
//  FBanEntry::GetKickMessage
// ─────────────────────────────────────────────────────────────────────────────

FString FBanEntry::GetKickMessage() const
{
    const UBanSystemConfig* Cfg = UBanSystemConfig::Get();

    // Determine which template to use (permanent vs. temporary).
    FString Tmpl;
    if (Cfg)
    {
        Tmpl = bIsPermanent
            ? Cfg->BanKickMessageTemplate
            : Cfg->TempBanKickMessageTemplate;
    }

    // Apply the configured template, substituting supported variables.
    if (!Tmpl.IsEmpty())
    {
        const FString ExpiryStr = bIsPermanent
            ? TEXT("never")
            : ExpireDate.ToString(TEXT("%Y-%m-%d %H:%M:%S")) + TEXT(" UTC");

        const FString AppealUrlStr = (Cfg && !Cfg->AppealUrl.IsEmpty())
            ? Cfg->AppealUrl
            : TEXT("(contact server admin)");

        // Apply substitutions: {expiry} and {appeal_url} first, {reason} last.
        // This prevents a reason containing "{expiry}" or "{appeal_url}" from being
        // expanded in a subsequent pass (double-substitution bug).
        Tmpl = Tmpl.Replace(TEXT("{expiry}"),     *ExpiryStr,     ESearchCase::IgnoreCase);
        Tmpl = Tmpl.Replace(TEXT("{appeal_url}"), *AppealUrlStr,  ESearchCase::IgnoreCase);
        Tmpl = Tmpl.Replace(TEXT("{reason}"),     *Reason,        ESearchCase::IgnoreCase);
        return Tmpl;
    }

    // Built-in fallback messages.
    const FString BaseAppeal = (Cfg && !Cfg->AppealUrl.IsEmpty())
        ? FString::Printf(TEXT(" Appeal at: %s"), *Cfg->AppealUrl)
        : TEXT("");

    if (bIsPermanent)
    {
        return FString::Printf(
            TEXT("You have been permanently banned. Reason: %s%s"),
            *Reason, *BaseAppeal);
    }
    return FString::Printf(
        TEXT("You are banned until %s UTC. Reason: %s%s"),
        *ExpireDate.ToString(TEXT("%Y-%m-%d %H:%M:%S")),
        *Reason, *BaseAppeal);
}

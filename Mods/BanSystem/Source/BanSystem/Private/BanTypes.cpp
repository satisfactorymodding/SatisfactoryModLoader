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

    // H2: Reject malformed signed integers before numeric conversion.
    // Accept only an optional single leading '-' followed by one or more digits.
    const FString& DurationStr = Parts[1];
    const bool bNegative = DurationStr.StartsWith(TEXT("-"));
    const int32 DigitsStart = bNegative ? 1 : 0;
    if (DurationStr.IsEmpty() || (bNegative && DurationStr.Len() == 1))
    {
        UE_LOG(LogBanTypes, Warning,
            TEXT("BanTypes: template slug='%s' has non-numeric durationMinutes '%s' — skipping"),
            *Parts[0], *DurationStr);
        return false;
    }
    for (int32 i = DigitsStart; i < DurationStr.Len(); ++i)
    {
        if (!FChar::IsDigit(DurationStr[i]))
        {
            UE_LOG(LogBanTypes, Warning,
                TEXT("BanTypes: template slug='%s' has non-numeric durationMinutes '%s' — skipping"),
                *Parts[0], *DurationStr);
            return false;
        }
    }

    // Use Atoi64 + clamp to safely handle large digit strings without int32 overflow.
    // Guard against Atoi64 overflow: max is 19 digits for positive values, or
    // "-9223372036854775808" (20 chars including the sign) for negative values.
    const int32 MaxLen = bNegative ? 20 : 19;
    if (DurationStr.Len() > MaxLen)
    {
        UE_LOG(LogBanTypes, Warning,
            TEXT("BanTypes: template slug='%s' has out-of-range durationMinutes '%s' — clamping to int32 range"),
            *Parts[0], *DurationStr);
        OutTemplate.DurationMinutes = bNegative ? INT32_MIN : INT32_MAX;
        OutTemplate.Reason          = Parts[2];
        OutTemplate.Category        = Parts.Num() > 3 ? Parts[3] : FString();
        return true;
    }
    // Length alone is insufficient for int64 safety: 19-digit positives above
    // INT64_MAX (or 20-char negatives below INT64_MIN) must be clamped before parse.
    if (!bNegative && DurationStr.Len() == 19 && DurationStr > TEXT("9223372036854775807"))
    {
        UE_LOG(LogBanTypes, Warning,
            TEXT("BanTypes: template slug='%s' has out-of-range durationMinutes '%s' — clamping to int32 range"),
            *Parts[0], *DurationStr);
        OutTemplate.DurationMinutes = INT32_MAX;
        OutTemplate.Reason          = Parts[2];
        OutTemplate.Category        = Parts.Num() > 3 ? Parts[3] : FString();
        return true;
    }
    if (bNegative && DurationStr.Len() == 20 && DurationStr.Mid(1) > TEXT("9223372036854775808"))
    {
        UE_LOG(LogBanTypes, Warning,
            TEXT("BanTypes: template slug='%s' has out-of-range durationMinutes '%s' — clamping to int32 range"),
            *Parts[0], *DurationStr);
        OutTemplate.DurationMinutes = INT32_MIN;
        OutTemplate.Reason          = Parts[2];
        OutTemplate.Category        = Parts.Num() > 3 ? Parts[3] : FString();
        return true;
    }

    const int64 DurI64 = FCString::Atoi64(*DurationStr);
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

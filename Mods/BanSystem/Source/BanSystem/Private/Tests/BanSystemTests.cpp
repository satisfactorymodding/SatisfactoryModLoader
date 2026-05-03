// Copyright Yamahasxviper. All Rights Reserved.
//
// Unit tests for BanSystem pure utility functions.
//
// Run with: UE4Editor BanSystem -ExecCmds "Automation RunTests BanSystem"
// Or via the Automation tab in the UE Editor's Session Frontend.
//
// These tests exercise only functions that have no runtime dependencies
// (no UGameInstance, no file I/O, no subsystems required) so they compile
// and pass under #if WITH_DEV_AUTOMATION_TESTS in any build configuration.

#include "CoreTypes.h"
#include "BanTypes.h"
#include "BanDatabase.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS

// ─────────────────────────────────────────────────────────────────────────────
//  FBanTemplate::FromConfigString
// ─────────────────────────────────────────────────────────────────────────────

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBanTemplateParseValidTest,
    "BanSystem.BanTemplate.ParseValid",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FBanTemplateParseValidTest::RunTest(const FString& /*Parameters*/)
{
    // 3-field: slug|duration|reason
    {
        FBanTemplate T;
        const bool bOk = FBanTemplate::FromConfigString(TEXT("griefing|60|Griefing"), T);
        TestTrue(TEXT("3-field parse succeeds"), bOk);
        TestEqual(TEXT("slug"),             T.Slug,            TEXT("griefing"));
        TestEqual(TEXT("duration"),         T.DurationMinutes, 60);
        TestEqual(TEXT("reason"),           T.Reason,          TEXT("Griefing"));
        TestTrue(TEXT("category empty"),    T.Category.IsEmpty());
    }

    // 4-field: slug|duration|reason|category
    {
        FBanTemplate T;
        const bool bOk = FBanTemplate::FromConfigString(TEXT("cheating|0|Cheating|exploit"), T);
        TestTrue(TEXT("4-field parse succeeds"), bOk);
        TestEqual(TEXT("slug"),     T.Slug,            TEXT("cheating"));
        TestEqual(TEXT("duration"), T.DurationMinutes, 0);
        TestEqual(TEXT("reason"),   T.Reason,          TEXT("Cheating"));
        TestEqual(TEXT("category"), T.Category,        TEXT("exploit"));
    }

    // Permanent ban (duration 0)
    {
        FBanTemplate T;
        TestTrue(TEXT("zero-duration parse"), FBanTemplate::FromConfigString(TEXT("perm|0|Permanent ban"), T));
        TestEqual(TEXT("perm duration"), T.DurationMinutes, 0);
    }

    // Large duration clamped to INT32_MAX
    {
        FBanTemplate T;
        const FString Big = FString::Printf(TEXT("long|%lld|Long ban"), static_cast<int64>(INT32_MAX) + 1LL);
        TestTrue(TEXT("large duration parse"), FBanTemplate::FromConfigString(*Big, T));
        TestEqual(TEXT("clamped to INT32_MAX"), T.DurationMinutes, INT32_MAX);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBanTemplateParseInvalidTest,
    "BanSystem.BanTemplate.ParseInvalid",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FBanTemplateParseInvalidTest::RunTest(const FString& /*Parameters*/)
{
    // Fewer than 3 fields → false
    {
        FBanTemplate T;
        TestFalse(TEXT("empty string"),  FBanTemplate::FromConfigString(TEXT(""), T));
        TestFalse(TEXT("one field"),     FBanTemplate::FromConfigString(TEXT("slug"), T));
        TestFalse(TEXT("two fields"),    FBanTemplate::FromConfigString(TEXT("slug|60"), T));
    }

    // Non-numeric duration → false
    {
        FBanTemplate T;
        TestFalse(TEXT("alpha duration"),
            FBanTemplate::FromConfigString(TEXT("slug|forever|Reason"), T));
    }

    // Float duration → false (non-digit character '.')
    {
        FBanTemplate T;
        TestFalse(TEXT("float duration"),
            FBanTemplate::FromConfigString(TEXT("slug|1.5|Reason"), T));
    }

    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
//  UBanDatabase::MakeUid / ParseUid round-trip
// ─────────────────────────────────────────────────────────────────────────────

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBanDatabaseUidRoundTripTest,
    "BanSystem.BanDatabase.UidRoundTrip",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FBanDatabaseUidRoundTripTest::RunTest(const FString& /*Parameters*/)
{
    // EOS platform — MakeUid uppercases the platform and joins with ':'
    {
        const FString Uid = UBanDatabase::MakeUid(TEXT("EOS"), TEXT("abcdef1234567890abcdef1234567890"));
        TestEqual(TEXT("EOS uid format"), Uid, TEXT("EOS:abcdef1234567890abcdef1234567890"));

        FString Platform, PlayerUID;
        UBanDatabase::ParseUid(Uid, Platform, PlayerUID);
        TestEqual(TEXT("ParseUid platform"),   Platform,  TEXT("EOS"));
        TestEqual(TEXT("ParseUid player uid"), PlayerUID, TEXT("abcdef1234567890abcdef1234567890"));
    }

    // IP platform
    {
        const FString Uid = UBanDatabase::MakeUid(TEXT("IP"), TEXT("192.168.1.1"));
        TestEqual(TEXT("IP uid format"), Uid, TEXT("IP:192.168.1.1"));

        FString Platform, PlayerUID;
        UBanDatabase::ParseUid(Uid, Platform, PlayerUID);
        TestEqual(TEXT("IP platform"),  Platform,  TEXT("IP"));
        TestEqual(TEXT("IP address"),   PlayerUID, TEXT("192.168.1.1"));
    }

    // Platform string is uppercased by MakeUid
    {
        const FString Uid = UBanDatabase::MakeUid(TEXT("eos"), TEXT("abc123"));
        TestEqual(TEXT("lowercase platform uppercased"), Uid, TEXT("EOS:abc123"));
    }

    // ParseUid on a malformed UID (no colon) → UNKNOWN platform
    {
        FString Platform, PlayerUID;
        UBanDatabase::ParseUid(TEXT("nocolon"), Platform, PlayerUID);
        TestEqual(TEXT("malformed platform"), Platform,  TEXT("UNKNOWN"));
        TestEqual(TEXT("malformed uid"),      PlayerUID, TEXT("nocolon"));
    }

    // ParseUid on a UID with leading colon → UNKNOWN platform (ColonIdx == 0)
    {
        FString Platform, PlayerUID;
        UBanDatabase::ParseUid(TEXT(":leadingcolon"), Platform, PlayerUID);
        TestEqual(TEXT("leading colon platform"), Platform, TEXT("UNKNOWN"));
    }

    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
//  FBanEntry::MatchesUid
// ─────────────────────────────────────────────────────────────────────────────

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBanEntryMatchesUidTest,
    "BanSystem.FBanEntry.MatchesUid",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FBanEntryMatchesUidTest::RunTest(const FString& /*Parameters*/)
{
    FBanEntry E;
    E.Uid = TEXT("EOS:abc123");
    E.LinkedUids.Add(TEXT("IP:10.0.0.1"));
    E.LinkedUids.Add(TEXT("IP:10.0.0.2"));

    // Primary UID — exact match (case-insensitive)
    TestTrue(TEXT("primary uid exact"),       E.MatchesUid(TEXT("EOS:abc123")));
    TestTrue(TEXT("primary uid upper case"),  E.MatchesUid(TEXT("EOS:ABC123")));

    // Linked UID match
    TestTrue(TEXT("linked uid first"),        E.MatchesUid(TEXT("IP:10.0.0.1")));
    TestTrue(TEXT("linked uid second"),       E.MatchesUid(TEXT("IP:10.0.0.2")));

    // Non-matching UID
    TestFalse(TEXT("no match"),               E.MatchesUid(TEXT("EOS:xxxxxx")));
    TestFalse(TEXT("empty string"),           E.MatchesUid(TEXT("")));

    // Entry with no linked UIDs — only primary matches
    FBanEntry E2;
    E2.Uid = TEXT("EOS:xyz");
    TestTrue(TEXT("primary only match"),      E2.MatchesUid(TEXT("EOS:xyz")));
    TestFalse(TEXT("primary only no match"),  E2.MatchesUid(TEXT("EOS:abc")));

    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
//  FBanTemplate::ParseTemplates batch helper
// ─────────────────────────────────────────────────────────────────────────────

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBanTemplateParseTemplatesTest,
    "BanSystem.BanTemplate.ParseTemplates",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FBanTemplateParseTemplatesTest::RunTest(const FString& /*Parameters*/)
{
    TArray<FString> ConfigStrings = {
        TEXT("hack|0|Cheating/hacking|exploit"),
        TEXT("grief|1440|Griefing"),
        TEXT("bad|oops|Invalid"),  // non-numeric — must be skipped
        TEXT("short|30|Short ban"),
    };

    const TArray<FBanTemplate> Templates = FBanTemplate::ParseTemplates(ConfigStrings);

    // "bad|oops|Invalid" must be filtered out → 3 templates
    TestEqual(TEXT("invalid filtered"), Templates.Num(), 3);

    TestEqual(TEXT("first slug"),     Templates[0].Slug,            TEXT("hack"));
    TestEqual(TEXT("first duration"), Templates[0].DurationMinutes, 0);
    TestEqual(TEXT("first category"), Templates[0].Category,        TEXT("exploit"));

    TestEqual(TEXT("second slug"),    Templates[1].Slug,            TEXT("grief"));
    TestEqual(TEXT("second duration"),Templates[1].DurationMinutes, 1440);

    TestEqual(TEXT("third slug"),     Templates[2].Slug,            TEXT("short"));
    TestEqual(TEXT("third duration"), Templates[2].DurationMinutes, 30);

    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
//  int64 ID serialization round-trip (Printf/Atoi64)
// ─────────────────────────────────────────────────────────────────────────────

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBanIdSerializationTest,
    "BanSystem.IdSerialization.Int64RoundTrip",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FBanIdSerializationTest::RunTest(const FString& /*Parameters*/)
{
    // Verify that int64 IDs above 2^53 survive a Printf/Atoi64 round-trip
    // (they would lose precision if stored as JSON number / double).
    const TArray<int64> TestIds = {
        0LL,
        1LL,
        INT32_MAX,
        static_cast<int64>(INT32_MAX) + 1LL,
        // 2^53 — first int64 not exactly representable as double
        9007199254740993LL,
        INT64_MAX,
    };

    for (int64 Id : TestIds)
    {
        const FString Serialized = FString::Printf(TEXT("%lld"), Id);
        const int64   Recovered  = FCString::Atoi64(*Serialized);
        TestEqual(FString::Printf(TEXT("Id=%lld round-trips"), Id), Recovered, Id);
    }

    // Verify that storing a large ID as double loses precision (motivates string encoding)
    const int64 LargeId = 9007199254740993LL; // 2^53 + 1
    const double AsDouble = static_cast<double>(LargeId);
    const int64 Roundtripped = static_cast<int64>(AsDouble);
    TestNotEqual(TEXT("large id loses precision via double"), Roundtripped, LargeId);

    return true;
}

#endif // WITH_DEV_AUTOMATION_TESTS

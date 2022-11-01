// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoreTypes.h"
#include "SatisfactoryModLoader.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS

TArray<FString> VersionRange = {"1.0.0-alpha", "1.0.0-alpha.1", "1.0.0-alpha.beta", "1.0.0-beta", "1.0.0-beta.2", "1.0.0-beta.11", "1.0.0-rc.1", "1.0.0"};

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FVersionTest, "SMLEditor.Version", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

FString TestVersion(FString AStr, FString BStr, int Expected)
{
	FString ErrA;
	FVersion A;
	bool ok = A.ParseVersion(AStr, ErrA);
	if (!ok)
	{
		return ErrA;
	}
	FString ErrB;
	FVersion B;
	ok = B.ParseVersion(BStr, ErrB);
	if (!ok)
	{
		return ErrB;
	}
	int Comparison = A.Compare(B);
	if (Comparison != Expected)
	{
		return FString::Printf(TEXT("Compared %s to %s | Expected %d Got %d"), *A.ToString(), *B.ToString(), Expected, Comparison);
	}
	return "";
}

bool FVersionTest::RunTest(const FString& Parameters)
{
	FString Err;
	for (int i = 1; i < VersionRange.Num(); ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			Err = TestVersion(VersionRange[i], VersionRange[j], 1);
			if (Err != "")
			{
				AddError(Err);
			}
		}
		Err = TestVersion(VersionRange[i], VersionRange[i], 0);
		if (Err != "")
		{
			AddError(Err);
		}
		for (int j = i+1; j < VersionRange.Num(); ++j)
		{
			Err = TestVersion(VersionRange[i], VersionRange[j], -1);
			if (Err != "")
			{
				AddError(Err);
			}
		}
	}
	
	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS

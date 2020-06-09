#pragma once
#include "Array.h"
#include "UnrealString.h"

#include "CoreMinimal.h"
#include "ObjectMacros.h"
#include "PlayerPresenceState.generated.h"

//[Gafgar:Thu/28-05-2020] a struct used to populate presence strings and parameters to various platforms. Currently only for epic and Steam. 
//Considering moving it to an engine level plugin. So that's why it's not using the FG prefix.
//As we currently need to do the steam specific stuff in local player, instead of the steam OSS. As the OSS has no knowledge about this struct.
USTRUCT()
struct FACTORYGAME_API FPlayerPresenceState
{
	GENERATED_BODY()

	struct SubParameter
	{
		FString key;
		FString value;
		SubParameter(const char* _key, FString v): key(_key), value(v)
		{}
	};

	FString mPresenceString;
	FString mSteamTagString;
	TArray<SubParameter> mParameters;

public:
	FORCEINLINE ~FPlayerPresenceState() = default;
};


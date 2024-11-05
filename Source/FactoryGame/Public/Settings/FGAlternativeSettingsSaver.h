// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "GameFramework/SaveGame.h"

#include "FGAlternativeSettingsSaver.generated.h"


UCLASS()
class FACTORYGAME_API UFGAlternativeSettingSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY( )
	TMap< FString, int32 > mIntValues;

	UPROPERTY( )
	TMap< FString, float > mFloatValues;
};


class UFGAlternativeSettingsSaver
{
	static bool SaveCurrentSettingsToDisc( UFGAlternativeSettingSaveGame* SaveGameObject );

public:
	static bool SaveCurrentSettings( const TMap< FString, int32 > & inIntValues, const TMap< FString, float >& inFloatValues );

	static bool LoadCurrentSettings( TMap< FString, int32 >& outIntValues, TMap< FString, float >& outFloatValues );
};

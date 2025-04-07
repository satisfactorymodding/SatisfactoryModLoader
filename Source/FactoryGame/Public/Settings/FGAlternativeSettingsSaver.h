// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "GameFramework/SaveGame.h"
#include "FGFactoryBlueprintTypes.h"
#include "Subsystems/EngineSubsystem.h"
#include "Settings/FGUserSetting.h"
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

	UPROPERTY( )
	FString mLanguage;

	void FilterBySettingsAvailability();

private:
	template< typename ValueType >
	void FilterValueMap( const TArray< UFGUserSettingApplyType* >& AllUserSettings, const ESettingVisiblityDisqualifier& VisiblityDisqualifier, TMap< FString, ValueType >& Values );
};


USTRUCT()
struct FFGBlueprintSaveData
{
	GENERATED_BODY()

	UPROPERTY( SaveGame )
	FString sessionName;

	UPROPERTY( SaveGame )
	FBlueprintRecord record;

	UPROPERTY( SaveGame )
	TArray< uint8 > data;
};


UCLASS()
class FACTORYGAME_API UFGBlueprintSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY( )
	TArray< FFGBlueprintSaveData > mBlueprints;
};

UCLASS()
class FACTORYGAME_API UFGPlayerReportSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY( )
	TMap<FString, FDateTime> mReports; // [key]: UniqueNetID of reported player - [value]: date of report sent

	UFUNCTION (BlueprintCallable)
	void AddOrUpdateReport( const FString& ReportedID, FDateTime dateOfReport );

	UFUNCTION(BlueprintCallable)
	bool IsPlayerReportedAlready(const FString& PlayerID) const;
};

UCLASS()
class FACTORYGAME_API UFGAlternativeSaveSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
public:
	bool SaveCurrentSettings( const TMap< FString, int32 > & inIntValues, const TMap< FString, float >& inFloatValues, FString inLanguage );
	bool LoadCurrentSettings( TMap< FString, int32 >& outIntValues, TMap< FString, float >& outFloatValues, FString& outLanguage );

// <Blueprints>
	bool LoadBlueprintRecords( const FString& sessionName, TArray< FBlueprintRecord >& out_Records );
	bool LoadBlueprintHeaders( const FString& sessionName, TArray< FBlueprintHeader >& out_Headers );
	bool DeleteBlueprint( const FString& sessionName, const FString& name );
	bool SaveBlueprint( const FString& sessionName, const FBlueprintRecord& record, TArray< uint8 > data );
	bool LoadBlueprint( const FString& sessionName, const FString& name, TArray< uint8 >& out_Data );
	bool GenerateBlueprintManifest( const FString& sessionName, struct FBlueprintManifest& out_Manifest );

#if !UE_BUILD_SHIPPING
	bool SetNumDummyBlueprints( int count );
#endif
//  </Blueprints>

// <Reported players>
	UFUNCTION(BlueprintCallable)
	UFGPlayerReportSaveGame* LoadPlayerReports();
	
	UFUNCTION(BlueprintCallable)
	bool SavePlayerReports();

	UFUNCTION(BlueprintCallable)
	bool SavePlayerReportsAsync();

	UFUNCTION (BlueprintCallable)
	const FString& GetPlayerReportSaveSlotName() const;
// </Reported players>

private:

	bool LoadSettingsFromDisc();
	bool SaveCurrentSettingsToDisc();

// <Blueprints>
	bool LoadBlueprintsFromDisc();
	bool SaveBlueprintsToDisc( uint32 SaveIndex );
//  </Blueprint>

	UPROPERTY()
	UFGAlternativeSettingSaveGame* mSaveGame;

	UPROPERTY()
	TArray<UFGBlueprintSaveGame*> mBlueprintSaveGames;

	UPROPERTY()
	UFGPlayerReportSaveGame* mPlayerReportSaveGame;
};

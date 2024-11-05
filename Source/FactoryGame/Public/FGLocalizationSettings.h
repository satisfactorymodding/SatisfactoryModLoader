// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Engine/DataTable.h"
#include "FGLocalizationSettings.generated.h"

UENUM( BlueprintType )
enum class ELocalizationType : uint8
{
	LT_Official			UMETA( DisplayName = "Official" ),
    LT_Community		UMETA( DisplayName = "Community" ),
    LT_Debug			UMETA( DisplayName = "Debug" )
};

/** Table entry for localization data. Row name is the culture code */
USTRUCT( BlueprintType )
struct FLocalizationEntry : public FTableRowBase
{
	GENERATED_BODY()
	
	FLocalizationEntry() :
		EnglishName(""),
		NativeName(""),
		LocalizationType(ELocalizationType::LT_Official),
		CompletionPercentage(0)
	{}

	UPROPERTY( BlueprintReadOnly, EditAnywhere )
	FString EnglishName;

	UPROPERTY( BlueprintReadOnly, EditAnywhere )
	FString NativeName;

	UPROPERTY( BlueprintReadOnly, EditAnywhere )
	ELocalizationType LocalizationType;
	
	UPROPERTY( BlueprintReadOnly, EditAnywhere )
	int32 CompletionPercentage;

};

/**
 * 
 */
UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Satisfactory Localization Settings" ))
class FACTORYGAME_API UFGLocalizationSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	static const UFGLocalizationSettings* Get() { return GetDefault<UFGLocalizationSettings>(); };

	UFUNCTION( BlueprintCallable )
    static TSoftObjectPtr< class UDataTable > GetOptionsMenuLanugagesDataTable() { return Get()->mOptionsMenuLanugagesDataTable; }
	
	UPROPERTY( EditAnywhere, config, Category = "Options", meta = ( ToolTip = "The data table for languages that populates the options menu dropdown for selecting language" ) )
	TSoftObjectPtr< class UDataTable > mOptionsMenuLanugagesDataTable;

	UPROPERTY( EditAnywhere, config, Category = "Patch Table"
		, meta = ( RelativeToGameContentDir, ToolTip = "The expected destination folder housing string tables." ) )
	FDirectoryPath StringTablesFolder;

	UPROPERTY( EditAnywhere, config, Category = "Patch Table"
		, meta = ( FilePathFilter = "csv", RelativeToGameDir = True, ToolTip = "The path to the Patch Table used to specify text that needs to be moved to String Tables." ) );
	FFilePath PatchTable;

	UPROPERTY( EditAnywhere, config, Category = "Patch Table"
		, meta = ( ToolTip = "The names of the metadata columns that should be picked up from the patch table as a comma separated list e.g.: Context,VariableDescription" ) );
	FString MetaDataColumns;

	UPROPERTY( EditAnywhere, config, Category = "Patch Table"
		, meta = ( ToolTip = "Should processing stop on first error?" ) );
	bool bStopOnError = false;
};
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
};

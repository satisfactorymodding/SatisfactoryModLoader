#pragma once
#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGPlayerCustomizationDesc.h"
#include "PlayerCustomizationData.generated.h"

/** Customization data for the player */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FPlayerCustomizationData
{
	GENERATED_BODY()

	/** First color that the player can choose */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Player Customization" )
	FLinearColor PrimaryColor = FLinearColor::Black;

	/** Secondary color that the player can choose */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Player Customization" )
	FLinearColor SecondaryColor = FLinearColor::Black;

	/** Detail color that the player can choose */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Player Customization" )
	FLinearColor DetailColor = FLinearColor::Black;

	/** Helmet that the player has selected */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Player Customization" )
	TSubclassOf<UFGPlayerHelmetCustomizationDesc> HelmetCustomizationDesc;
	
	/** Index of the helmet that the player has selected */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Player Customization" )
	TSubclassOf<UFGPlayerTrinketCustomizationDesc> TrinketCustomizationDesc;

	/** Map of equipment desc to equipment skin desc. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Player Customization" )
	TArray<TSubclassOf<UFGPlayerEquipmentSkinCustomizationDesc>> EquipmentCustomizationDesc;
};
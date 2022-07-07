// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "FGScannableSettings.generated.h"

/**
 * 
 */
UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Scannable Settings" ) )
class FACTORYGAME_API UFGScannableSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	static const UFGScannableSettings* Get() { return GetDefault<UFGScannableSettings>(); };
	
	/** We might want to solve this in a different way maybe with an interface but this works for now */
	UPROPERTY( EditAnywhere, config, Category = "Hostile Creatures", meta = ( ToolTip = "This is the additional hostile creature classes that doesn't inherit from FGCreature. Thi s is so we should be able to can for them" ) )
	TArray< TSubclassOf< AActor > > mAdditionalHostileCreatureClasses;
};

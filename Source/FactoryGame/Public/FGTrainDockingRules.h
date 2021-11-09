// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGTrainDockingRules.generated.h"

UENUM( BlueprintType )
enum class ETrainDockingDefinition : uint8
{
	TDD_LoadUnloadOnce,
	TDD_FullyLoadUnload
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FTrainDockingRuleSet
{
	GENERATED_BODY()
public:
	FTrainDockingRuleSet() : DockingDefinition( ETrainDockingDefinition::TDD_LoadUnloadOnce ), DockForDuration( 15.f ), IsDurationAndRule( false ) {}

	UPROPERTY( BlueprintReadWrite, SaveGame )
	ETrainDockingDefinition DockingDefinition;

	UPROPERTY( BlueprintReadWrite, SaveGame )
	float DockForDuration;

	UPROPERTY( BlueprintReadWrite, SaveGame )
	bool IsDurationAndRule;
	
	UPROPERTY( BlueprintReadWrite, SaveGame )
	TArray< TSubclassOf< class UFGItemDescriptor > > LoadFilterDescriptors;

	UPROPERTY( BlueprintReadWrite, SaveGame )
	TArray < TSubclassOf< class UFGItemDescriptor > > UnloadFilterDescriptors;
};


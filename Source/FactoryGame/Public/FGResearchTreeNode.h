// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FGSchematic.h"
#include "FGResearchTreeNode.generated.h"

/**
 * 
 */
UCLASS( Blueprintable, DefaultToInstanced, abstract, editinlinenew )
class FACTORYGAME_API UFGResearchTreeNode : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintImplementableEvent, Category="Research" )
	TSubclassOf< class UFGSchematic > GetNodeSchematic() const;
	
};

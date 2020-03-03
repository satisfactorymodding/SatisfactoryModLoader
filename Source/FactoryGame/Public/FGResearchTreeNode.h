// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGResearchTreeNode.generated.h"

/**
 * 
 */
UCLASS( Blueprintable, DefaultToInstanced, abstract, editinlinenew )
class FACTORYGAME_API UFGResearchTreeNode : public UObject
{
	GENERATED_BODY()
	

public:
	FORCEINLINE ~UFGResearchTreeNode() = default;
};

// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "FGEnvQueryTest_ItemDescription.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGEnvQueryTest_ItemDescription : public UEnvQueryTest
{
	// MODDING EDIT
	GENERATED_BODY()
	UFGEnvQueryTest_ItemDescription(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	
protected:
	/** This is where we actually check for the ItemDescriptor class */
	virtual void RunTest( FEnvQueryInstance& QueryInstance ) const override;
	
	/** Class of what descriptor we are looking for */
	UPROPERTY( EditAnywhere, Category = "Item Descriptor" )
	TSubclassOf< class UFGItemDescriptor > mItemDescriptorClass;

public:
	FORCEINLINE ~UFGEnvQueryTest_ItemDescription() = default;
};

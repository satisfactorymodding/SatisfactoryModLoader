// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "FGEnvQueryTest_ItemDescription.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGEnvQueryTest_ItemDescription : public UEnvQueryTest
{
	GENERATED_UCLASS_BODY()
	
protected:
	/** This is where we actually check for the ItemDescriptor class */
	virtual void RunTest( FEnvQueryInstance& QueryInstance ) const override;
	
	/** Class of what descriptor we are looking for */
	UPROPERTY( EditAnywhere, Category = "Item Descriptor" )
	TSubclassOf< class UFGItemDescriptor > mItemDescriptorClass;
};

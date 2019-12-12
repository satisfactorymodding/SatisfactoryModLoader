#pragma once
#include "UObject/Interface.h"
#include "UObject/Class.h"

#include "FGRecipeProducerInterface.generated.h"

/**
* For blueprint support of the interface, we will never add anything to it, just use it to
* have a UCLASS to be able to access
*/
UINTERFACE( Blueprintable )
class UFGRecipeProducerInterface : public UInterface
{
	
 GENERATED_BODY()
	UFGRecipeProducerInterface(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {} 
};

/**
*
*/ 
class IFGRecipeProducerInterface
{
	GENERATED_IINTERFACE_BODY()
};
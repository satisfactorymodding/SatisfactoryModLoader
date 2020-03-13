#pragma once
#include "UObject/Interface.h"
#include "UObject/Class.h"

#include "FGRecipeProducerInterface.generated.h"

/**
* For blueprint support of the interface, we will never add anything to it, just use it to
* have a UCLASS to be able to access
*/
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGRecipeProducerInterface : public UInterface
{
	
 GENERATED_BODY()
	UFGRecipeProducerInterface(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {} 

public:
	FORCEINLINE ~UFGRecipeProducerInterface() = default;
};

/**
*
*/ 
class FACTORYGAME_API IFGRecipeProducerInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	FORCEINLINE IFGRecipeProducerInterface() = default;
};
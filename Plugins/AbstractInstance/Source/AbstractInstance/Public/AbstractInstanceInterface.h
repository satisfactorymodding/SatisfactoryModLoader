// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InstanceData.h"
#include "UObject/Interface.h"
#include "AbstractInstanceInterface.generated.h"

USTRUCT()
struct ABSTRACTINSTANCE_API FInstanceHandleArray
{
	GENERATED_BODY()
	TArray<struct FInstanceHandle*> HandleArray;
};

/**
 * 
 */
UINTERFACE( Blueprintable )
class ABSTRACTINSTANCE_API UAbstractInstanceInterface : public UInterface
{
	GENERATED_BODY()
};


class ABSTRACTINSTANCE_API IAbstractInstanceInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION( BlueprintNativeEvent, Category = "LightweightInstances" )
	TArray<struct FInstanceData> GetActorLightweightInstanceData();

	UFUNCTION( BlueprintNativeEvent, Category = "LightweightInstances" )
	bool DoesContainLightweightInstances();

	/*Lightweight actors could have NO transform, but have them set on spawn,
	 *to get the true transform this function call needs to be made and implemented*/
	UFUNCTION( BlueprintNativeEvent, Category = "LightweightInstances" )
	FTransform GetLightweightInstanceActorTransform() const;

	UFUNCTION( BlueprintNativeEvent, Category = "LightweightInstances" )
	void PostLazySpawnInstances();

	virtual FInstanceHandleArray GetLightweightInstanceHandles() const	{ return FInstanceHandleArray(); }
}; 
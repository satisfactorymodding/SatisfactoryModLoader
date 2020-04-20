#pragma once

#include "GameFramework/Actor.h"
#include "SMLInitMenu.generated.h"

UCLASS(Abstract, Blueprintable, HideCategories = ("Actor Tick", Rendering, Replication, Input, Actor, Collision, LOD, Cooking))
class SML_API ASMLInitMenu : public AActor {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	void Init();
};
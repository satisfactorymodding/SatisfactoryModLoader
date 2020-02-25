#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "GameFramework/Actor.h"
#include "SMLInitMenu.generated.h"

UCLASS(Blueprintable, HideCategories = ("Actor Tick", Rendering, Replication, Input, Actor, Collision, LOD, Cooking))
class SML_API ASMLInitMenu : public AActor {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
	void Init();
};
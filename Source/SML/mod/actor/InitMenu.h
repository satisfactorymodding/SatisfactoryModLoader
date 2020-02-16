#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "GameFramework/Actor.h"
#include "InitMenu.generated.h"

UCLASS(Blueprintable, HideCategories = ("Actor Tick", Rendering, Replication, Input, Actor, Collision, LOD, Cooking))
class SML_API AInitMenu : public AActor {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
	void Init();
};
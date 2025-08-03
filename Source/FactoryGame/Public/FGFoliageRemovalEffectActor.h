// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGFoliageRemovalEffectActor.generated.h"

UCLASS()
class FACTORYGAME_API AFGFoliageRemovalEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGFoliageRemovalEffectActor();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(Replicated)
	TArray<FTransform> Transforms;
	
	UPROPERTY(Replicated)
	TArray<UStaticMesh*> Meshes;
};

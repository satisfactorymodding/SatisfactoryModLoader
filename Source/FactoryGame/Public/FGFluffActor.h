// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGFluffActor.generated.h"

UCLASS()
class FACTORYGAME_API AFGFluffActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGFluffActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called when the game starts or when spawned
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE ~AFGFluffActor() = default;
};

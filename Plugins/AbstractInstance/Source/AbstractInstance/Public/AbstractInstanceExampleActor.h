// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InstanceData.h"
#include "GameFramework/Actor.h"
#include "AbstractInstanceExampleActor.generated.h"

struct FInstanceHandle;

UCLASS( Abstract, Blueprintable )
class ABSTRACTINSTANCE_API AAbstractInstanceExampleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbstractInstanceExampleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
protected:
	UPROPERTY( EditDefaultsOnly, Instanced )
	UAbstractInstanceDataObject* InstanceData;

	TArray<FInstanceHandle*> InstanceHandles;
};

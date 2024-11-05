// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGSignificanceInterface.h"
#include "GameFramework/Actor.h"
#include "FGSignificanceActor.generated.h"

UCLASS()
class FACTORYGAME_API AFGSignificanceActor : public AActor, public IFGSignificanceInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGSignificanceActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Begin IFGSignificanceInterface
	virtual float GetSignificanceRange() override { return mSignificanceRange; }
	// End IFGSignificanceInterface
protected:
	UPROPERTY(EditDefaultsOnly,Category = "Significance")
	float mSignificanceRange = 8000;
	
	UPROPERTY(EditDefaultsOnly,Category = "Significance")
	bool bIsStatic = true;
};

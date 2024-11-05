// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "FGGasPillarDesctructionActor.generated.h"

UCLASS()
class FACTORYGAME_API AFGGasPillarDesctructionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AFGGasPillarDesctructionActor();
	
	virtual void BeginPlay() override;

	void SetDestructionInfo( float dmgScale, const FVector& dmgLocation );

	UFUNCTION( BlueprintImplementableEvent )
	void OnDestructionInfoSet();
	
public:	

	UPROPERTY( VisibleAnywhere )
	UGeometryCollectionComponent* mGeometryCollectionComponent;

	UPROPERTY( EditDefaultsOnly )
	float mDestructionImpulseScale = 2.f;

	UPROPERTY( BlueprintReadOnly, Category="GasPillarDestructionActor" )
	float mAppliedDamageScale;

	UPROPERTY( BlueprintReadOnly, Category="GasPillarDestructionActor" )
	FVector mForceLocation;
	
};

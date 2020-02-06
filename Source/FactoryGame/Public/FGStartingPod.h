// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGDismantleInterface.h"
#include "FGStartingPod.generated.h"

UCLASS()
class FACTORYGAME_API AFGStartingPod : public AActor, public IFGDismantleInterface
{
	GENERATED_BODY()
	
public:	
	AFGStartingPod();

	/** Decide on what properties to replicate */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	//~ Begin IFGDismantleInterface
	virtual FVector GetRefundSpawnLocationAndArea_Implementation( const FVector& aimHitLocation, float& out_radius ) const override;
	virtual bool CanDismantle_Implementation() const override;
	virtual void GetDismantleRefund_Implementation( TArray< FInventoryStack >& out_refund ) const override;
	virtual void PreUpgrade_Implementation() override;
	virtual void Upgrade_Implementation( AActor* newActor ) override;
	virtual void Dismantle_Implementation() override;
	virtual void StartIsLookedAtForDismantle_Implementation(class AFGCharacterPlayer* byCharacter ) override;
	virtual void StopIsLookedAtForDismantle_Implementation( class AFGCharacterPlayer* byCharacter ) override;
	//~ End IFGDismantleInferface

	/** Getter for player */
	UFUNCTION( BlueprintPure, Category = "Starting Pod" )
	FORCEINLINE AFGCharacterPlayer* GetCachedPlayer() { return mCachedPlayer; }

	/** Start the pod animation */
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "Starting Pod" )
	void StartSequence();

	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "Starting Pod" )
	void OnPlayerSkipIntroSequence();

protected:
	virtual void BeginPlay() override;
public:
	/** Player associated with this pod */
	UPROPERTY( Replicated )
	class AFGCharacterPlayer* mCachedPlayer;
protected:
	/** Array containing how much to get back when dismantling this bad boy */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Dismantle")
	TArray< FInventoryStack > mDismantleStacks;

	/** Main mesh */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Starting Pod" )
	class USkeletalMeshComponent* mDropPodMesh;

	/** Flag for whether the actor is being dismantled */
	int32 mIsDismantled : 1;

};

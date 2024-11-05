// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGSaveInterface.h"
#include "FGSignificanceInterface.h"
#include "Replication/FGStaticReplicatedActor.h"
#include "FGSporeFlower.generated.h"

/** todo: (a bigish one) this is just a start of what should be a much more complete nativization of the spore flower */
UCLASS()
class FACTORYGAME_API AFGSporeFlower : public AFGStaticReplicatedActor, public IFGSaveInterface, public IFGSignificanceInterface
{
	GENERATED_BODY()

public:	
	AFGSporeFlower();

	//~ Begin UObject interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~ End UObject interface

	virtual float TakeDamage( float damage, struct FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser ) override;

	//IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual void LostSignificance_Implementation() override;
	virtual float GetSignificanceRange() override { return mSignificanceRange; }
	//End

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/* Called on getting damage. */
	UFUNCTION(BlueprintImplementableEvent)
	void OnDied();

protected:
	/** Test if an actor should trigger spore flower to rise */
	UFUNCTION( BlueprintPure, Category = "SporeFlower" )
	bool ActorShouldTriggerFlower( AActor* actor );

protected:
	/** These actor types will trigger the spore flower to emit */
	UPROPERTY( EditDefaultsOnly, Category = "SporeFlower" )
	TArray<TSubclassOf<AActor>> mTriggerActorClasses;

	/** Holds a list of all actors inside trigger spehere */
	UPROPERTY( )
	TArray<AActor*> mTriggerActors;

	UPROPERTY(EditDefaultsOnly)
	float mDeathTime = 10;

	UPROPERTY(EditDefaultsOnly)
	float mSignificanceRange = 8000.f;
};

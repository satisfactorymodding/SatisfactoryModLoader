#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "Components/SceneComponent.h"
#include "FGDotComponent.generated.h"

/**
 * Attach this to a PrimtiveComponent (like Box, Mesh or Brush) and the whenever someone is inside this
 * shape, then we apply the specified dot to the actors specified in the UFGDamageOverTime class
 */
UCLASS( hidecategories = ( Cooking, Collision, Rendering, Sockets ), ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent, DisplayName = "DotComponent" ) )
class FACTORYGAME_API UFGDotComponent : public USceneComponent
{
	GENERATED_BODY()
public:
	/** ctor */
	UFGDotComponent();

	//~ Begin UObject interface
	virtual void PostLoad() override;
	//~ End UObject interface

	//~ Begin ActorComponent interface
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	virtual void Activate( bool reset = false ) override;
	virtual void Deactivate() override;
	//~ End ActorComponent interface

#if WITH_EDITOR
	virtual void CheckForErrors();
#endif
protected:
	/** Start the timer that will damage actors */
	void StartDamageTimer();

	/** Called whenever a primitive component enters the volume, this triggers check if we should start damage them */
	UFUNCTION()
	virtual void OnPrimitiveComponentEntered( UPrimitiveComponent* overlappedComp, AActor* other, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool fromSweep, const FHitResult& sweepResult );

	/** Called whenever a primitive component enters the volume, stop damage them */
	UFUNCTION()
	virtual void OnPrimitiveComponentExited( UPrimitiveComponent* overlappedComp, AActor* other, UPrimitiveComponent* otherComp, int32 otherBodyIndex );

	/** Called by timer to tell us to damage the containing actors */
	UFUNCTION()
	void DamageContainingActors();
protected:
	/** The dot we should apply to things in the primitive component we are attached to */
	UPROPERTY( EditAnywhere, Category="Dot")
	TSubclassOf< class UFGDamageOverTime > mDotClass;

	/** The actors we want to damage */
	UPROPERTY()
	TArray< class AActor* > mActorsToDamage;

	/** handle to keep track of when we want to damage actors */
	FTimerHandle mDamageTimerHandle;

public:
	FORCEINLINE ~UFGDotComponent() = default;
};
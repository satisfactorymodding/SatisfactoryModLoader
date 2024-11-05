// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

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
	UFGDotComponent();

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
	UFUNCTION()
	virtual void OnActorBeginOverlap( AActor* overlappedActor, AActor* otherActor );
	
	UFUNCTION()
	virtual void OnActorEndOverlap( AActor* overlappedActor, AActor* otherActor );

	void RegisterDOTForActor( AActor* actor, bool shouldRegister ) const;

	UFUNCTION()
	void OnDOTReceiverCreated( class UFGDotReceiverComponent* dotReceiver );
	
protected:	
	/** The dot we should apply to things in the primitive component we are attached to */
	UPROPERTY( EditAnywhere, Category = "Dot" )
	TSubclassOf< class UFGDamageOverTime > mDotClass;

	/** Actors which our primitive component is overlapping. */
	UPROPERTY()
	TArray< AActor* > mOverlappingActor;
};
// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGEquipment.h"
#include "FGEquipmentZipline.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGEquipmentZipline : public AFGEquipment
{
	GENERATED_BODY()
public:
	AFGEquipmentZipline();
	
	// Begin AFGEquipment interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void Tick( float delta ) override;
    virtual void AddEquipmentActionBindings() override;
	virtual void UnEquip() override;
	// End AFGEquipment interface
	
	/** Drop down from zipline */
	void DoDrop();
	/** Jump exit the zipline */
    void JumpExit();

	UFUNCTION( BlueprintPure, Category = "Zipline" )
	FORCEINLINE bool GetWantToGrab() const { return mWantToGrab; }

	UFUNCTION( BlueprintImplementableEvent, Category = "Zipline" )
	void OnZiplineSprintStatusChanged( bool sprint );

	/** Called during tick, tries to grab onto a wire if mWantToGrab is set  */
	void TryToGrab();
	bool CanGrab( AActor* attachActor, const FVector& point1, const FVector& point2 ) const;
protected:
	virtual void HandleDefaultEquipmentActionEvent( EDefaultEquipmentAction action, EDefaultEquipmentActionEvent actionEvent ) override;
	
	/** Input actions */
	void Input_Crouch( const FInputActionValue& actionValue );
	void Input_Jump( const FInputActionValue& actionValue );
	
	/** Called to start the ziplining effects */
	UFUNCTION( BlueprintImplementableEvent, Category = "Zipline" )
	void StartZiplineEffects();

	/** Called to stop the ziplining effects */
	UFUNCTION( BlueprintImplementableEvent, Category = "Zipline" )
	void StopZiplineEffects();

	/** Called from the movement component every frame we update the movement to update the Zipline VFX */
	UFUNCTION( BlueprintNativeEvent, Category = "Zipline" )
	void PlayZiplineEffects( const FVector &inLocation );
	
	/** Called whenever our "Want to grab" value changes. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Zipline" )
	void OnWantToGrabChanged( bool newWantToGrab );

	/** Called to re-apply the current state of the "wants to grab" when we end the zipline movement. Used to restart the animation if we are still wanting to grab the wire */
	UFUNCTION( BlueprintImplementableEvent, Category = "Zipline" )
	void ReapplyWantsToGrabAfterZiplineEnd( bool bWantsToGrab );

	void ZiplineStart( AActor* ziplineActor, const FVector& point1, const FVector& point2, const FVector& actorForward );
	void Local_ZiplineStart( AActor* ziplineActor, const FVector& point1, const FVector& point2, const FVector& actorForward );

	void ZiplineEnd( const FVector& exitForce );
	void Local_ZiplineEnd( const FVector& exitForce );
private:
	friend class UFGCharacterMovementComponent;
	
	void StartActiveNoise();
	void StopActiveNoise();
	
	/** Used to make noise for when the zipline is active. */
	UFUNCTION()
	void MakeActiveNoise();

	UFUNCTION( NetMulticast, Reliable, Category = "Zipline" )
	void Multicast_ZiplineStart( AActor* ziplineActor, const FVector& point1, const FVector& point2, const FVector& actorForward );
	
	UFUNCTION( NetMulticast, Reliable, Category = "Zipline" )
	void Multicast_ZiplineEnd( FVector exitForce );

	/** Same as DoDrop but on server */
	UFUNCTION( Server, Reliable )
	void Server_DoDrop();

	/** Same as JumpExit but on server */
	UFUNCTION( Server, Reliable )
	void Server_JumpExit();

	void SetWantsToGrab( bool wantsToGrab, bool jumpExit = true );

	UFUNCTION()
	void OnRep_WantToGrab();
private:
	/** Set if we should try to grab a zipline */
	UPROPERTY( ReplicatedUsing = OnRep_WantToGrab )
	bool mWantToGrab;

	/* Particle associated with zipline */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame" )
	class UParticleSystem* mZiplineParticle;

	/** How much upwards velocity is applied when jumping on the zipline. */
	UPROPERTY( EditDefaultsOnly, Category = "Zipline" )
	float mZiplineJumpLaunchVelocity;

	/** Max allowed angle on wire for zip-lining. Sine value of the angle needs to be lower than this in order to be valid for zipline. 0-1 value. */
	UPROPERTY( EditDefaultsOnly, Category = "Zipline", meta=( ClampMin=0, UIMin=0, ClampMax=1, UIMax=1 ) )
	float mMaxZiplineAngle;

	/** How long in front of the player should we trace for wires */
	UPROPERTY( EditDefaultsOnly, Category = "Zipline" )
	float mTraceDistance;

	/** How long in front of the player the trace should start */
	UPROPERTY( EditDefaultsOnly, Category = "Zipline" )
	float mTraceStartOffset;

	/** Sphere radius used when tracing */
	UPROPERTY( EditDefaultsOnly, Category = "Zipline" )
	float mTraceRadius;

	/** Debug trace distance */
	UPROPERTY( EditDefaultsOnly, Category = "Zipline" )
	bool mVisualizeTraceDistance;

	/** The noise to make when the zipline is active. */
    UPROPERTY( EditDefaultsOnly, Category = "Zipline" )
    TSubclassOf< class UFGNoise > mActiveNoise;

    /** How often to make the noise (in seconds) while the zipline is active. */
    UPROPERTY( EditDefaultsOnly, Category = "Zipline" )
    float mActiveNoiseFrequency;

    FTimerHandle mActiveNoiseTimerHandle;
	
	/** Duration we need to wait before allowing the player to reattach zipline */
	UPROPERTY( EditDefaultsOnly, Category = "Zipline" )
	float mZiplineReattachCooldown;

	float mZiplineReattachTimer;
};



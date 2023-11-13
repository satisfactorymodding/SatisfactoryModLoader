// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGEquipment.h"
#include "FGEquipmentZipline.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGEquipmentZipline final: public AFGEquipment
{
	GENERATED_BODY()
public:
	AFGEquipmentZipline();
	
	// Begin AFGEquipment interface
    virtual void AddEquipmentActionBindings() override;
	virtual void UnEquip() override;
	// End AFGEquipment interface
	
	virtual void Tick( float delta ) override;

	UFUNCTION( BlueprintPure, Category = "Zipline" )
	FORCEINLINE bool GetWantToGrab() const { return mWantToGrab; }

	void ZiplineEnd();
	
	/** Same as DoDrop but on server */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_DoDrop();

	/** Drop down from zipline */
	UFUNCTION()
	void DoDrop();

	/** Same as JumpExit but on server */
	UFUNCTION( Server, Reliable, WithValidation )
    void Server_JumpExit();
	
	/** Jump exit the zipline */
	UFUNCTION()
    void JumpExit();

	/** Input actions */
	void Input_Crouch( const FInputActionValue& actionValue );
	void Input_Jump( const FInputActionValue& actionValue );

	UFUNCTION( BlueprintImplementableEvent, Category = "Zipline" )
	void OnZiplineSprintStatusChanged( bool sprint );

	/** Called during tick, tries to grab onto a wire if mWantToGrab is set  */
	void TryToGrab();

	bool CanGrab( AActor* attachActor, const FVector& point1, const FVector& point2 ) const;

protected:
	virtual void HandleDefaultEquipmentActionEvent( EDefaultEquipmentAction action, EDefaultEquipmentActionEvent actionEvent ) override;

	/** Called whenever our "Want to grab" value changes. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Zipline" )
	void OnWantToGrabChanged( bool newWantToGrab );
	
	void SetWantsToGrab( bool wantToGrab );

private:
	/** Used to make noise for when the zipline is active. */
	UFUNCTION()
	void MakeActiveNoise();
	
private:
	/** Set if we should try to grab a zipline */
	bool mWantToGrab;

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



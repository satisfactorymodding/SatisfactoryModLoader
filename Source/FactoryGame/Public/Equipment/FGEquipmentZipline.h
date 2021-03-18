// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/FGEquipment.h"
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
    virtual void AddEquipmentActionBindings() override;
    virtual void DoDefaultPrimaryFire_Native() override;
	virtual void UnEquip() override;
	// End AFGEquipment interface
	
	/** Called on the owner, client or server but not both. */
	void OnDefaultPrimaryFireReleased();
	
	/** Only server implementation of primary fire */
	UFUNCTION( Server, Reliable, WithValidation )
    void Server_DefaultPrimaryFireReleased();

	/** Cancel the zipline movement */
    void DoDefaultPrimaryFireReleased_Native();
	
	virtual void Tick( float delta ) override;

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
	
	void OnCrouchPressed();
	void OnCrouchReleased();

	void OnJumpPressed();

	/** Called during tick, tries to grab onto a wire if mWantToGrab is set  */
	void TryToGrab();
	
private:
	/** Set if we dropped from a zipline so that we don't call UnCrouch when button is released */
	bool mDidDrop;

	/** Set if we should try to grab a zipline */
	bool mWantToGrab;

	/** How much upwards velocity is applied when jumping on the zipline. */
	UPROPERTY( EditDefaultsOnly, Category = "Zipline" )
	float mZiplineJumpLaunchVelocity;

	/** Max allowed angle on wire for ziplining. Sine value of the angle needs to be lower than this in order to be valid for zipline. 0-1 value. */
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

	/** Duration we need to wait before allowing the player to reattach zipline */
	UPROPERTY( EditDefaultsOnly, Category = "Zipline" )
	float mZiplineReattachCooldown;

	float mZiplineReattachTimer;
};



// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "GameFramework/Actor.h"
#include "FGEquipment.h"
#include "FGEquipmentAttachment.generated.h"

UCLASS()
class FACTORYGAME_API AFGEquipmentAttachment : public AActor
{
	GENERATED_BODY()
public:
	/** Replication. */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	AFGEquipmentAttachment();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	/** Attaches this attachment to a character */
	void Attach( class AFGCharacterPlayer* character );

	/** Event called when this equipment has been attached */
	UFUNCTION( BlueprintNativeEvent, Category = "Equipment|Attachment" )
	void OnAttach();

	/** Detach from current parent */
	void Detach();

	/** Event called before this equipment is detached */
	UFUNCTION( BlueprintNativeEvent, Category = "Equipment|Attachment" )
	void OnDetach();

	/** @return true if this is attached; false if not. */
	UFUNCTION( BlueprintPure, Category = "Equipment|Attachment" )
	FORCEINLINE bool IsAttached() const { return mIsAttached; }

	/** Sets what slot we are equipped on */
	void SetEquippedSlot( EEquipmentSlot inSlot ) { mEquipmentSlot = inSlot; }

	/** @return The equipment slot that this attachment is associated with  */
	UFUNCTION( BlueprintPure, Category = "Equipment|Attachment" )
	FORCEINLINE EEquipmentSlot GetEquippedSlot() const { return mEquipmentSlot;  }

	/** Calls UpdateUseState on all instances on all connections so that they can handle any visual effects they need to. */
	void SetAttachmentUseState( int newUseState );

	/** Event called when use state is updated */
	UFUNCTION( BlueprintImplementableEvent, Category = "Equipment|Attachment" )
	void OnAttachmentUseStateUpdated( int newUseState );

	/** Event called when we should play attach effects */
	UFUNCTION( BlueprintImplementableEvent, Category = "Equipment|Attachment" )
	void PlayAttachEffects3P();

	/** Event called when we should play detach */
	UFUNCTION( BlueprintImplementableEvent, Category = "Equipment|Attachment" )
	void PlayDetachEffects3P();

	/** Set the use location on server so that it can be relicated to clients */
	void SetUseLocation( const FVector& newUseLocation );

	/** Handles playing of effects on remote clients */
	UFUNCTION( BlueprintNativeEvent, Category = "Attachment" )
	void PlayUseEffect( FVector useLocation );

	/** Get the arms animation to play on the player */
	FORCEINLINE EArmEquipment GetArmsAnimation() const{ return mArmAnimation; }

	/** Get the back animation to play on the player */
	FORCEINLINE EBackEquipment GetBackAnimation() const{ return mBackAnimation; }

protected:
	/** @return character this is attached to; nullptr if not attached. */
	UFUNCTION( BlueprintPure, Category = "Equipment|Attachment" )
	FORCEINLINE class AFGCharacterPlayer* GetAttachedTo() const{ return mAttachedTo; }

	/** @return socket this should attach to, can be none. */
	UFUNCTION( BlueprintPure, Category = "Equipment|Attachment" )
	FORCEINLINE FName GetAttachSocket() const{ return mAttachSocket; }

	/** Called when we get a new use location, on client through replication and on server from SetFlashLocation */
	UFUNCTION()
	void OnRep_UseLocationUpdated();

	/** Called when the animation state has been updated */
	UFUNCTION()
	void OnRep_OnAnimationStateUpdated();

public:

	/** The class of the equipment that spawned this attachment */
	UPROPERTY( Replicated )
	TSubclassOf< class AFGEquipment > mEquipmentClass;

protected:
	/** This value get replicated to clients so they can play effect*/
	UPROPERTY( ReplicatedUsing = OnRep_UseLocationUpdated )
	FVector mUseLocation;

	/** If this equipment should attach to a socket, this is the socket. */
	UPROPERTY( EditDefaultsOnly, Category = "Attachment" )
	FName mAttachSocket;

	/** Arms animation this should play on the when the equipment is equipped (only used if mEquipmentSlot == ES_ARMS) */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment|Animation" )
	EArmEquipment mArmAnimation;

	/** Arms animation this should play on the when the equipment is equipped (only used if mEquipmentSlot == ES_BACK) */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment|Animation" )
	EBackEquipment mBackAnimation;

	/** If this attachment is attached */
	bool mIsAttached;

	/** The character this is attached to.*/
	UPROPERTY()
	class AFGCharacterPlayer* mAttachedTo;

	/** To what slot is this attachment attached */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment|Attachment" )
	EEquipmentSlot mEquipmentSlot;

	/** integer used for animation states */
	UPROPERTY( ReplicatedUsing = OnRep_OnAnimationStateUpdated )
	int32 mAnimationState;
};

// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Equipment/FGEquipmentAttachment.h"
#include "FGWeaponAttachment.generated.h"

UCLASS()
class FACTORYGAME_API AFGWeaponAttachment : public AFGEquipmentAttachment
{
	GENERATED_BODY()

public:
	/** Replication. */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	/** Handles playing of effects on remote clients */
	UFUNCTION( BlueprintNativeEvent, Category = "Attachment" )
	void PlayFireEffect( FVector flashLocation );

	/** Called on all relevant attachments */
	UFUNCTION( NetMulticast, Unreliable, Category = "Attachment" )
	void Multicast_SetFlashLocation( const FVector& newFlashLocation );

	UFUNCTION( BlueprintImplementableEvent, Category = "Attachment" )
	void OnBeginFireEffect( FVector location );

	UFUNCTION( NetMulticast, Unreliable, Category = "Attachment" )
	void Multicast_PlayBeginFireEffect( const FVector& location );

	/** Called on all relevant attachments */
	UFUNCTION( NetMulticast, Unreliable, Category = "Attachment" )
	void Multicast_PlayReloadEffectMulticast();

	/** For client only */
	UFUNCTION( BlueprintImplementableEvent, Category = "Attachment" )
	void ClientPlayReloadEffect();

	UFUNCTION( BlueprintImplementableEvent, Category = "Attachment" )
	void OnIsLoadedSet();

	UFUNCTION( NetMulticast, Reliable, Category = "Attachment" )
	void Multicast_SetIsLoaded( bool isLoaded );

protected:
	/** Called on remote clients when the player fires the weapon. Needed a function so I could overload in FGWeaponAttachmentProjectile */
	virtual void PlayerFired( FVector flashLocation );
protected:
	/** Location that was hit ( or sometimes shoot direction ) */
	FVector mFlashLocation;

	UPROPERTY( BlueprintReadWrite, Category = "Attachment" )
	bool mIsLoaded;
};

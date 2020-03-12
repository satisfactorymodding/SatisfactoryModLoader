#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "FGEquipmentAttachment.h"
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

	/** Called on all relevant attachments */
	UFUNCTION( NetMulticast, Unreliable, Category = "Attachment" )
	void Multicast_PlayReloadEffectMulticast();

	/** For client only */
	UFUNCTION( BlueprintImplementableEvent, Category = "Attachment" )
	void ClientPlayReloadEffect();

protected:
	/** Called on remote clients when the player fires the weapon. Needed a function so I could overload in FGWeaponAttachmentProjectile */
	virtual void PlayerFired( FVector flashLocation );
protected:
	/** Location that was hit ( or sometimes shoot direction ) */
	FVector mFlashLocation;


public:
	FORCEINLINE ~AFGWeaponAttachment() = default;
};

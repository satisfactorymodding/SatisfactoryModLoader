// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Equipment/FGEquipmentAttachment.h"
#include "FGWeaponAttachment.generated.h"

class UFGAmmoType;

UCLASS()
class FACTORYGAME_API AFGWeaponAttachment : public AFGEquipmentAttachment
{
	GENERATED_BODY()

public:
	/** Replication. */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	UFUNCTION( NetMulticast, Reliable, Category = "Attachment" )
	void Multicast_PlayFireEffect( UFGAmmoType* ammoType );
	
	/** Handles playing of effects on remote clients */
	UFUNCTION( BlueprintNativeEvent, Category = "Attachment" )
	void PlayFireEffect( UFGAmmoType* ammoType );

	UFUNCTION( BlueprintImplementableEvent, Category = "Attachment" )
	void OnBeginFireEffect( FVector location );

	UFUNCTION( NetMulticast, Reliable, Category = "Attachment" )
	void Multicast_PlayBeginFireEffect( const FVector& location );

	/** Called on all relevant attachments */
	UFUNCTION( NetMulticast, Reliable, Category = "Attachment" )
	void Multicast_PlayReloadEffectMulticast();

	/** For client only */
	UFUNCTION( BlueprintImplementableEvent, Category = "Attachment" )
	void ClientPlayReloadEffect();

	UFUNCTION( BlueprintImplementableEvent, Category = "Attachment" )
	void OnIsLoadedSet();

	UFUNCTION( NetMulticast, Reliable, Category = "Attachment" )
	void Multicast_SetIsLoaded( bool isLoaded );
protected:
	UPROPERTY( BlueprintReadWrite, Category = "Attachment" )
	bool mIsLoaded;
};

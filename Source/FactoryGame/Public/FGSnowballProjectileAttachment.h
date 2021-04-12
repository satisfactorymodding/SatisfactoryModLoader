// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/FGWeaponAttachment.h"
#include "FGSnowballProjectileAttachment.generated.h"

/**
 * Specialty Attachment class for handling the unique two-part behaviour of FGSnowballDetonator Equipment.
 * This is the 3rd person attachment representing the FGWeaponChild of FGSnowballDetonator Explosive
 */
UCLASS()
class FACTORYGAME_API AFGSnowballProjectileAttachment : public AFGWeaponAttachment
{
	GENERATED_BODY()
	
public:

	/** Replication. */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;


	UFUNCTION( BlueprintImplementableEvent, Category = "Snowball" )
	void OnBeginFireEffect( FVector location );

	UFUNCTION( NetMulticast, Unreliable, Category = "Snowball" )
	void Multicast_PlayBeginFireEffect( const FVector& location );

	UFUNCTION( BlueprintImplementableEvent, Category = "Snowball" )
	void OnIsLoadedSet();
	
	UFUNCTION( NetMulticast, Unreliable, Category = "Snowball" )
	void Multicast_SetIsLoaded( bool isLoaded );

protected:

	UPROPERTY( BlueprintReadWrite, Category = "Snowball" )
	bool mIsLoaded;


};

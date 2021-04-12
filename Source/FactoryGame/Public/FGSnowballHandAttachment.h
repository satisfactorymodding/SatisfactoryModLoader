// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/FGWeaponAttachment.h"
#include "FGSnowballHandAttachment.generated.h"

/**
* Specialty Attachment class for handling the unique two-part behaviour of FGSnowballWeapon Equipment.
* This is the 3rd person attachment representing the FGWeapon : FGSnowballWeapon
*/
UCLASS()
class FACTORYGAME_API AFGSnowballHandAttachment : public AFGWeaponAttachment
{
	GENERATED_BODY()
	
public:
	/** Replication. */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	UFUNCTION( BlueprintImplementableEvent, Category = "Nobelisk" )
	void OnIsLoadedSet();

	UFUNCTION( NetMulticast, Unreliable, Category = "Nobelisk" )
	void Multicast_SetIsLoaded( bool isLoaded );
		
protected:

	UPROPERTY( BlueprintReadWrite, Category = "Nobelisk" )
	bool mIsLoaded;

};

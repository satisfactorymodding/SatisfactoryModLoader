// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Equipment/FGWeaponAttachment.h"
#include "FGNobeliskDetonatorAttachment.generated.h"

/**
* Specialty Attachment class for handling the unique two-part behaviour of FGNobeliskDetonator Equipment.
* This is the 3rd person attachment representing the FGWeapon : FGNobeliskDetonator
*/
UCLASS()
class FACTORYGAME_API AFGNobeliskDetonatorAttachment : public AFGWeaponAttachment
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


public:
	FORCEINLINE ~AFGNobeliskDetonatorAttachment() = default;
};

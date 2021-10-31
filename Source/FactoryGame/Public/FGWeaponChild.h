// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGEquipmentChild.h"
#include "FGWeaponChild.generated.h"


UCLASS()
class FACTORYGAME_API AFGWeaponChild : public AFGEquipmentChild
{
	GENERATED_BODY()

public:
	void SetIsLoaded( bool isLoaded );

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category= "Weapon")
	void Multicast_NotifySetIsLoaded(bool isLoaded);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category= "Weapon")
	void Multicast_NotifyBeginPrimaryFire();

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category= "Weapon")
	void Multicast_NotifyEndPrimaryFire();

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category= "Weapon")
	void Multicast_NotifyFailedToFire();

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category= "Weapon")
	void Multicast_NotifyPrimaryFireExecuted();

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category= "Weapon")
	void Multicast_NotifyBeginSecondaryFire();

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category= "Weapon")
	void Multicast_NotifyEndSecondaryFire();

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category= "Weapon")
	void Multicast_NotifyReloading();

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category= "Weapon")
	void Multicast_NotifyReloadComplete();

	// Start AFGWeapon Event notify calls
	UFUNCTION( BlueprintNativeEvent, Category = "Weapon" )
	void NotifySetIsLoaded(bool isLoaded);

	UFUNCTION( BlueprintNativeEvent, Category = "Weapon" )
	void NotifyBeginPrimaryFire();
	
	UFUNCTION( BlueprintNativeEvent, Category = "Weapon" )
	void NotifyEndPrimaryFire();
	
	UFUNCTION( BlueprintNativeEvent, Category = "Weapon")
	void NotifyFailedToFire();

	/** For instances when the actual fire happens after a delay on ending primary fire
	*	This could be an anim notify or set by a timer etc.
	*	This is special behavior and must be hooked up on a per weapon basis */
	UFUNCTION( BlueprintNativeEvent, Category = "Weapon" )
	void NotifyPrimaryFireExecuted();

	UFUNCTION( BlueprintNativeEvent, Category = "Weapon" )
	void NotifyBeginSecondaryFire();

	UFUNCTION( BlueprintNativeEvent, Category = "Weapon" )
	void NotifyEndSecondaryFire();

	UFUNCTION( BlueprintNativeEvent, Category = "Weapon")
	void NotifyReloading();

	UFUNCTION( BlueprintNativeEvent, Category = "Weapon" )
	void NotifyReloadComplete();
	// End AFGWeapon Event Notify Calls

protected:
	/** Keeps track of whether our parent equipable is loaded */
	UPROPERTY( BlueprintReadOnly, Category = "Weapon" )
	bool mIsLoaded;
};

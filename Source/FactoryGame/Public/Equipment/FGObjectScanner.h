// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Equipment/FGEquipment.h"
#include "FGSchematic.h"
#include "Equipment/FGEquipmentAttachment.h"
#include "FGScannableDetails.h"
#include "FGObjectScanner.generated.h"

UENUM()
enum class ECycleDirection : uint8
{
	CD_Forward,
	CD_Backward
};

/**
*
*/
UCLASS()
class FACTORYGAME_API AFGObjectScanner : public AFGEquipment
{
	GENERATED_BODY()
public:
	/** Ctor */
	AFGObjectScanner();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Tick( float deltaTime ) override;
	// End AActor interface

	/** guess what this does. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Scanner" )
	void PlayBeep( bool isObjectInRange );

	/**
	* Equips the equipment.
	*/
	virtual void Equip( class AFGCharacterPlayer* character ) override;

	/**
	* Put the equipment away.
	*/
	virtual void UnEquip() override;

	UFUNCTION( BlueprintPure, Category = "Scanner" )
	FORCEINLINE bool IsBeeping() { return mIsBeeping; }

	/** 
	 * Cycles scannable type forward and updates the light on the attachment 
	 * @return true if there was a setting change, false means there was nothing to cycle to
	 */
	UFUNCTION( BlueprintCallable, Category = "Scanner" )
	bool CycleForward();

	/** 
	 * Cycles scannable type backward and updates the light on the attachment 
	 * @return true if there was a setting change, false means there was nothing to cycle to
	 */
	UFUNCTION( BlueprintCallable, Category = "Scanner" )
	bool CycleBackward();

	/** 
	 * Set light color etc. 
	 * @param wasChange is true if there was a scanner setting change, false if not. eg. false when initialising scanner, true when you change what you are scanning for.
	 */
	UFUNCTION( BlueprintImplementableEvent, Category = "Scanner" )
	void UpdateScannerVisuals( bool wasChange );

	/** Returns whether or not object scanner has a valid currently selected object */
	UFUNCTION( BlueprintCallable, Category = "Scanner" )
 	FORCEINLINE bool HasValidCurrentDetails() const { return mCurrentScannableDescriptor != nullptr && mCurrentScannableDetails != nullptr; }

	/** Returns the aticve scannable desriptor. Can be nullptr */
	UFUNCTION( BlueprintPure, Category = "Scanner" )
	FORCEINLINE TSubclassOf<UFGItemDescriptor> GetCurrentScannableDescriptor() const { return mCurrentScannableDescriptor; }

	/** Returns array with all descriptors that we can search for */
	UFUNCTION( BlueprintCallable, Category = "Scanner" ) 
	void GetAvailableScannableDescriptors( TArray < TSubclassOf<UFGItemDescriptor> >& out_availableDescriptors );

	/** Sets which descriptor that we want to search for */
	UFUNCTION( BlueprintCallable, Category = "Scanner" ) 
	void SetScannableDescriptor( TSubclassOf<UFGItemDescriptor> newScannableDescriptor );

private:

	bool Internal_CycleObjects( ECycleDirection direction );

	/**
	* Removes all nullptr entries from cache. Possible because other players may pick up Objects, thus nulling them,
	* and this cache does use any replication etc.
	*/
	void RemoveInvalidObjectsFromCache( TSubclassOf< AActor > scannableClass );

	/** Loops through the cached list of Objects and finds the closest one. This may call RemoveInvalidObjectsFromCache if a null is found */
	void UpdateClosestObject();

	/** Calls PlayBeep() and sets up timer for the next beep */
	void Internal_PlayBeep();

	/** If no object has been selected, this will try and equip the first available object in the object scanner */
	void TryToEquipDefaultObject();

protected:
	/** Maximum delay (in seconds) between each beep */
	UPROPERTY( EditDefaultsOnly, Category = "Scanner" )
	float mBeepDelayMax;

	/** Minimum delay (in seconds) between each beep */
	UPROPERTY( EditDefaultsOnly, Category = "Scanner" )
	float mBeepDelayMin;

	/** Detection range of the scanner */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Scanner" )
	float mDetectionRange;

	/** "the closest" Object doesn't really need to be updated every frame. Maybe every second, or 2, or so. */
	UPROPERTY( EditDefaultsOnly, Category = "Scanner" )
	float mUpdateClosestObjectTime;

	/**
	* Details regarding what we should scan. DEPRECATED @todok2 remove when we now new system works and we don't need it anymore 
	* @note order is important here. the order this is in is the order that the scanner's toggle will be in.
	*/
	UPROPERTY( VisibleDefaultsOnly, Category = "Scanner" )
	TArray < FScannableDetails > mObjectDetails;

	/**
	 * The descriptors we would like to scan for
	 * @note order is important here. the order this is in is the order that the scanner's toggle will be in.
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Scanner" )
	TArray< TSubclassOf< class UFGItemDescriptor > > mScannableDescriptors;

	UPROPERTY( BlueprintReadOnly, Category = "Scanner" )
	/** The current closest Object */
	class AActor* mClosestObject;

	/** If true, the scanner beeps even if there is nothing within range. If false, it starts beeping if something comes within range. */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Scanner" )
	bool mShouldBeepEvenIfNoObject;

private:
	/**
	* Stores a reference to all Objects.
	* Entries -may- be nullptr, so be careful. Consider removing nullptr when you find it.
	*/
	TMap< TSubclassOf< class AActor >, TArray< TWeakObjectPtr< class AActor > > > mCachedObjects;

	/**
	* objects that werent cached
	*/
	TArray< TWeakObjectPtr< class AActor > > mUncachedObjects;

	/** The delay between beeps is variable based on distance from the object. This is the current beep delay. */
	float mCurrentBeepDelay;

	/* Handle that triggers on mUpdateClosestObjectTime */
	FTimerHandle mUpdateClosestObjectTimerHandle;

	/* Handle that triggers on mUpdateClosestObjectTime */
	FTimerHandle mBeepTimerHandle;

	/** if true, the device is beeping. */
	bool mIsBeeping;

	/** The currently descriptor we would like to scan for */
	UPROPERTY( Transient )
	TSubclassOf<class UFGItemDescriptor> mCurrentScannableDescriptor;
	/** Cached details for how we scan for different types of objects */
	UPROPERTY( Transient )
	UFGScannableDetails* mCurrentScannableDetails;

	/** if we had a closest object last frame */
	bool mHadClosestObject;
};


UCLASS()
class FACTORYGAME_API AFGObjectScannerAttachment : public AFGEquipmentAttachment
{
	GENERATED_BODY()

public:

	void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	FORCEINLINE void SetIsBeeping( bool isBeeping ) { mIsBeeping = isBeeping; }

	UFUNCTION( BlueprintPure, Category = "Scanner" )
	FORCEINLINE bool IsBeeping() { return mIsBeeping; }

	FORCEINLINE void SetScannerLightColor( FColor scannerLightColor ) { mScannerLightColor = scannerLightColor; }

	UFUNCTION( BlueprintPure, Category = "Scanner" )
	FORCEINLINE FColor GetScannerLightColor() { return mScannerLightColor; }

protected:

	UFUNCTION( BlueprintImplementableEvent, Category = "Scanner" )
	void UpdateScannerVisuals();

private:
	UFUNCTION()
	void OnRep_IsBeeping();

	UFUNCTION()
	void OnRep_ScannerLightColor();

private:

	/** True if scanner is beeping */
	UPROPERTY( ReplicatedUsing = OnRep_IsBeeping )
	bool mIsBeeping;

	/** Scanner light color */
	UPROPERTY( ReplicatedUsing = OnRep_ScannerLightColor )
	FColor mScannerLightColor;
};

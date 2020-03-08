#pragma once
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "Templates/SubclassOf.h"
#include "UObject/Interface.h"
#include "FGUseableInterface.generated.h"

UCLASS(Blueprintable,abstract)
class FACTORYGAME_API UFGUseState : public UObject
{
	GENERATED_BODY()
public:
	/** Returns if we should allocate a instance of the state */
	bool WantsAdditonalData() const { return mWantAdditonalData; }

	/** True if the state is usable */
	bool IsUsableState() const{ return mIsUsableState; }

	/** Helper function to see if we can use the object in this state */
	static bool CanUseInState( TSubclassOf<UFGUseState> state );
protected:
	/** If true, we will allocate a instance of the state, so we can store information in the state */
	UPROPERTY( EditDefaultsOnly, Category="Use" )
	bool mWantAdditonalData;

	/** If true, we will allocate a instance of the state, so we can store information in the state */
	UPROPERTY( EditDefaultsOnly, Category="Use" )
	bool mIsUsableState;

public:
	FORCEINLINE ~UFGUseState() = default;
};

/**
 * Default valid state for things to use whenever things just works as they should
 */
UCLASS()
class FACTORYGAME_API UFGUseState_Valid : public UFGUseState
{
	GENERATED_BODY()

	UFGUseState_Valid() : Super() { mIsUsableState = true; }

public:
	FORCEINLINE ~UFGUseState_Valid() = default;
};

/**
 * Describes a state of a useable object for the player that tries to use it
 */
USTRUCT(BlueprintType)
struct FACTORYGAME_API FUseState
{
	GENERATED_BODY()

	/** Update the use state to a new use state, and allocates additional data if needed */
	void SetUseState( TSubclassOf<UFGUseState> newState );

	FORCEINLINE TSubclassOf<UFGUseState> GetState() const { return State; } 

	/** Additional data that might be heavy to calculate several times the same frame, the reason it's cached here and not in the object, is that several players might want to cache different things */
	UPROPERTY( BlueprintReadOnly )
	class UFGUseState* AdditionalData;

	/** Location of where the use happens */
	UPROPERTY( BlueprintReadOnly )
	FVector UseLocation;

	/** Component that triggered the use */
	UPROPERTY( BlueprintReadOnly )
	UPrimitiveComponent* UseComponent;
protected:
	/** Contains the usable state of the object, might be a error code */
	UPROPERTY( BlueprintReadOnly )
	TSubclassOf< UFGUseState > State;

public:
	FORCEINLINE ~FUseState() = default;
};

/**
 * For blueprint support of the interface, we will never add anything to it, just use it to
 * have a UCLASS to be able to access
 */
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGUseableInterface : public UInterface
{
	
 GENERATED_BODY()
	UFGUseableInterface(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {} 

public:
	FORCEINLINE ~UFGUseableInterface() = default;
};

/**
 * @brief Interface for all useable classes out there
 */
class FACTORYGAME_API IFGUseableInterface
{
	GENERATED_IINTERFACE_BODY()

	/**
	 * Get the current use state for a object
	 * @param byCharacter	The character that want to use the object
	 * @param atLocation	Location on the object where the use is triggered (simulated location on client).
	 * @param componentHit	The component that the trace hit when looking at the object
	 **/
	UFUNCTION( BlueprintNativeEvent, Category = "Use" )
	void UpdateUseState( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, UPARAM(ref) FUseState& out_useState ) const;

	/**
	 * Called when a character tries to use this actor.
	 * @note Called on both server and client.
	 *
	 * @param byCharacter	Character that uses the object.
	 * @param state			The state that describes how the object reacts to interaction
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Use" )
	void OnUse( class AFGCharacterPlayer* byCharacter, const FUseState& state );

	/**
	* Called when a character releases the use button
	* @note Called on both server and client.
	*
	* @param byCharacter	Character that uses the object.
	* @param state			The state that describes how the object reacts to interaction
	*/
	UFUNCTION( BlueprintNativeEvent, Category = "Use" )
	void OnUseStop( class AFGCharacterPlayer* byCharacter, const FUseState& state );

	/**
	 * Checks if this actor is usable (a good example of a not useable actor is a alive enemy)
	 * This should primarily be used when we don't want the outline to show up
	 * @note Called on both server and client.
	 *
	 * @return	true if this object is in a useable state
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Use" )
	bool IsUseable() const;

	/**
	 * Called on by the interface if we are looking at something that's useable
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Use" )
	void StartIsLookedAt( AFGCharacterPlayer* byCharacter, const FUseState& state );

	/**
	 * Called when we stop looking at the item
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Use" )
	void StopIsLookedAt( AFGCharacterPlayer* byCharacter, const FUseState& state );

	/**
	 * Called every frame when we are looked at, get a localized text on how we can be used
	 *
	 * @param byCharacter	Character that uses the object.
	 * @param state			The state that describes how the object reacts to interaction
	 */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Use" )
	FText GetLookAtDecription( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const;

	/** Called from widgets that are opened by the use functionality */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Use" )
	void RegisterInteractingPlayer( class AFGCharacterPlayer* player );

	/** Called from widgets that are opened by the use functionality */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Use" )
	void UnregisterInteractingPlayer( class AFGCharacterPlayer* player );

public:
	FORCEINLINE IFGUseableInterface() = default;
};

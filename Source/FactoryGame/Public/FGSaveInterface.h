#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "UObject/Interface.h"
#include "FGSaveInterface.generated.h"

/** Customize this for complex types to be able to sanitize structs from a array */
template<typename T>
bool IsValidForLoad( const T& element ){ return element != nullptr; }

/**
 * Helper template to be able to sanitize complex array structures
 */
template<typename T>
int32 Save_SanitizeArray( TArray<T>& savedArray )
{
	int32 originalSize = savedArray.Num();
	savedArray.RemoveAllSwap( []( const T& element ){ return !IsValidForLoad( element ); } );
	return originalSize - savedArray.Num();
}

/**
 * To be able to use this, the type stored in TArray<Type> arrayVar need to have the function bool IsValidForLoad( Type element ); implemented for it
 **/
#define SAVE_SANTIZE_ARRAY( arrayVar ) \
	{ \
		int32 numFoundNullpointers = Save_SanitizeArray( arrayVar ); \
		if( numFoundNullpointers > 0 ) \
		{ \
			UE_LOG( LogSave, Warning, TEXT( "Warning, found %i nullpointers in " #arrayVar " during load" ), numFoundNullpointers ); \
		} \
	}

#define SAVE_EMPTY_IMPLEMENTATION( SAVE_CLASS, NeedTransform ) \
void SAVE_CLASS::PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ){} \
void SAVE_CLASS::PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ){} \
void SAVE_CLASS::PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ){} \
void SAVE_CLASS::PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ){} \
void SAVE_CLASS::GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ){} \
bool SAVE_CLASS::NeedTransform_Implementation(){ return NeedTransform; } \
bool SAVE_CLASS::ShouldSave_Implementation() const { return true; }

/**
* For blueprint support of the interface, we will never add anything to it, just use it to
* have a UCLASS to be able to access
*/
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGSaveInterface : public UInterface
{
	
 GENERATED_BODY()
	UFGSaveInterface(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {} 

public:
	FORCEINLINE ~UFGSaveInterface() = default;
};

/**
* @brief If you want your actor to be saved, implement this!
*/
class FACTORYGAME_API IFGSaveInterface
{
	GENERATED_IINTERFACE_BODY()

	/**
	 * Called on all UObjects that will be saved right before the save is done
	 *
	 * @param saveVersion - the version of the save game, incremented when doing native conversions
	 * @param gameVersion - the version of the game, is the CL of our internal Perforce server, will be a large number > 40k
	 **/
	UFUNCTION( BlueprintNativeEvent )
	void PreSaveGame( int32 saveVersion, int32 gameVersion );

	/**
	 * Called on all UObjects right after they have written their data, so they can cleanup any mess done in PreSave
	 *
	 * @param saveVersion - the version of the save game, incremented when doing native conversions
	 * @param gameVersion - the version of the game, is the CL of our internal Perforce server, will be a large number > 40k
	 **/
	UFUNCTION( BlueprintNativeEvent )
	void PostSaveGame( int32 saveVersion, int32 gameVersion );

	/**
	 * Called on all UObjects right after they will be loaded (or created prior to getting their data) 
	 *
	 * @param saveVersion - the version of the save game, incremented when doing native conversions
	 * @param gameVersion - the version of the game, is the CL of our internal Perforce server, will be a large number > 40k
	 **/
	UFUNCTION( BlueprintNativeEvent )
	void PreLoadGame( int32 saveVersion, int32 gameVersion );

	/**
	 * Called on all UObjects when they have gotten their data from serialization
	 *
	 * @param saveVersion - the version of the save game, incremented when doing native conversions
	 * @param gameVersion - the version of the game, is the CL of our internal Perforce server, will be a large number > 40k
	 **/
	UFUNCTION( BlueprintNativeEvent )
	void PostLoadGame( int32 saveVersion, int32 gameVersion );

	/**
	 * Called before PreSaveGame, used to determine the order the objects is to be saved on disc @warning: make sure to NOT create any cyclic
	 * dependencies
	 *
	 * @param out_dependentObjects -	populate this with the object you are dependent on, no need to care about outer/owner, they are automatically
	 *									handled by calling code
	 */ 
	UFUNCTION( BlueprintNativeEvent )
	void GatherDependencies( TArray< UObject* >& out_dependentObjects );

	/**
	 * Called before PreSaveGame, used to determine if the object want to be saved
	 *
	 * @return true if the object want to be saved
	 */
	UFUNCTION( BlueprintNativeEvent )
	bool ShouldSave() const;

	/**
	 * Only relevant for actors.
	 * If returning true, then when loading, we are returned to the location that was stored when saving
	 */
	UFUNCTION( BlueprintNativeEvent )
	bool NeedTransform();

public:
	FORCEINLINE IFGSaveInterface() = default;
};
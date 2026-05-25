// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Serialization/MemoryReader.h"
#include "UObject/Object.h"

#include "FGModularMovementObject.generated.h"

/**
 * Base struct for modular movement data.
 * Can be serialized in order to be stored as data on client-side Saved Moves, or sent through RPCs between server and client.
 */
struct FACTORYGAME_API FGModularMovementDataContainer
{
	virtual ~FGModularMovementDataContainer() = default;

	/** Serializes this SavedMoveData to/from the specified archive. */
	virtual void SerializeSavedMoveData( FArchive& ar ) = 0;

	/** Whether this saved move data can be combined with the specified saved move data. */
	virtual bool CanCombineMove( const FGModularMovementDataContainer* OtherMove ) const = 0;
};

/**
 * Factory class interface used for creating and managing templated Modular Saved Move Data.
 */
class FGModularMovementDataFactoryBase
{
public:
	virtual ~FGModularMovementDataFactoryBase() = default;

	/** Creates a new modular movement data container object based on the movement mode data container type. */
	virtual TUniquePtr< FGModularMovementDataContainer > CreateMoveData( const FGModularMovementDataContainer* CopyFrom = nullptr ) const = 0;

	/** Copies data from one movement data container to another. */
	virtual void CopyData( const FGModularMovementDataContainer* From, FGModularMovementDataContainer* To ) const = 0;
};

template< typename MoveDataContainerType >
class FGModularMovementDataContainerFactory : public FGModularMovementDataFactoryBase
{
	static_assert( TIsDerivedFrom< MoveDataContainerType, FGModularMovementDataContainer >::Value, "MoveDataContainerType is not derived from FGModularMovementDataContainer." );
public:	
	virtual TUniquePtr< FGModularMovementDataContainer > CreateMoveData( const FGModularMovementDataContainer* CopyFrom = nullptr ) const override final
	{
		TUniquePtr< MoveDataContainerType > newMoveData = MakeUnique< MoveDataContainerType >();
		
		CopyData( CopyFrom, newMoveData.Get() );
		
		return newMoveData;
	}

	virtual void CopyData( const FGModularMovementDataContainer* From, FGModularMovementDataContainer* To ) const override final
	{
		if( From && To )
		{
			// Tobias 2025-11-12: Not sure what the best approach is here. Memcpy could potentially cause issues depending on what we're copying. Maybe we should expose a Copy function / use assignment operator on the object.
			FMemory::Memcpy( To, From, sizeof( MoveDataContainerType ) );
		}
	}
};

/**
 * Base class for modular movement objects.
 * Modular movement objects are essentially character movement modes with code isolation.
 */
UCLASS( Abstract, Within = FGCharacterMovementComponent )
class FACTORYGAME_API UFGModularMovementObject : public UObject
{
	GENERATED_BODY()
	
public:
	explicit UFGModularMovementObject();
	
	/** Serializes data used by the movement mode to / from the specified archive. */
	void SerializeSavedMoveData( FArchive& ar );

	/** Movement function of the movement mode. */
	virtual void PhysMovement( const float DeltaSeconds );

	/** Whether movement component velocity should reset when entering this movement mode. */
	virtual bool ResetVelocityOnEnter() const { return false; }
	
	/** Whether or not the movement mode wants to make the character visually slide. */
	virtual bool WantsToVisuallySlide() const { return false; }

	/** Serializes necessary movement mode variables to/from the specified archive. TODO: Maybe it'd be nice to replace this by having replicated subobjects of the movement modes with their own replicated props created on the movement component by the server? */
	virtual void SerializeMovementMode( FArchive& Ar );

	FORCEINLINE class UFGCharacterMovementComponent* GetMovementComponent() const { return GetOuterUFGCharacterMovementComponent(); }

	FGModularMovementDataContainer* GetMovementData() const { return mMovementData.Get(); }
	
	template< typename MoveDataContainerType >
	MoveDataContainerType* GetMovementData() const { return static_cast< MoveDataContainerType* >( mMovementData.Get() ); }

	FGModularMovementDataFactoryBase* GetMovementDataFactory() const { return mSavedMoveDataFactory.Get(); }

	bool IsActiveMovementMode() const;
	void ActivateMovementMode();

	/** TODO MODULAR MOVEMENT: Add OnMovementModeChanged / Enter / Exit functions? */

protected:
	template< typename MoveDataContainerType >
	void InitSavedMoveData();

protected:
	TUniquePtr< FGModularMovementDataContainer > mMovementData;

private:
	TUniquePtr< FGModularMovementDataFactoryBase > mSavedMoveDataFactory;
};

template< typename MoveDataContainerType >
void UFGModularMovementObject::InitSavedMoveData()
{
	if( !mSavedMoveDataFactory )
	{
		mSavedMoveDataFactory = MakeUnique< FGModularMovementDataContainerFactory< MoveDataContainerType > >();
		mMovementData = mSavedMoveDataFactory->CreateMoveData();
	}
}

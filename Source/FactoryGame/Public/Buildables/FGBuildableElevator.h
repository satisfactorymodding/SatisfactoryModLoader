// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGBuildableElevatorFloorStop.h"
#include "FGBuildableFactory.h"
#include "FGCharacterPlayer.h"
#include "FGElevatorTypes.h"
#include "FGPowerConnectionComponent.h"
#include "Net/Core/PushModel/PushModel.h"
#include "FGBuildableElevator.generated.h"


class UFGPowerConnectionComponent;
class AFGElevatorCabin;


UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableElevator : public AFGBuildableFactory
{
	GENERATED_BODY()
public:
	AFGBuildableElevator();

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion) override;
	// End IFGSaveInterface

	// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// End AActor Interface

	// Begin AFGBuildable Interface
	virtual int32 GetDismantleRefundReturnsMultiplier() const override;
	virtual void OnBuildEffectFinished() override;
	virtual void OnBuildEffectActorFinished() override;
	// End AFGBuildable Interface

	// Begin IFGDistmantleInterface
	virtual void GetDismantleDisqualifiers_Implementation(TArray<TSubclassOf<UFGConstructDisqualifier>>& out_dismantleDisqualifiers, const TArray<AActor*>& allSelectedActors) const override;
	virtual void GetChildDismantleActors_Implementation(TArray<AActor*>& out_ChildDismantleActors) const override;
	virtual bool SupportsDismantleDisqualifiers_Implementation() const override { return true; }
	virtual bool CanDismantle_Implementation() const override;
	// End IFGDismantleinterface

	// Begin Customization Interface
	virtual void ApplyCustomizationData_Native(const FFactoryCustomizationData& customizationData ) override;
	// End Customization Interface

	// Begin _Factory Interface
	virtual void Factory_Tick(float dt) override;
	virtual bool CanProduce_Implementation() const override;
	virtual void Factory_TickProducing(float dt) override;
	virtual void Factory_StartProducing() override;
	virtual void Factory_StopProducing() override;
	// End _Factory Interface

	// Begin IFGClearanceInterface
	virtual void GetChildClearanceOutlineActors_Implementation(TArray<AActor*>& out_actors) const override;
	// End IFGClearanceInterface
	
	virtual bool DoesContainLightweightInstances_Native() const override { return true; }
	virtual TArray<struct FInstanceData> GetActorLightweightInstanceData_Implementation() const override;

	UFUNCTION( BlueprintCallable, Category="FactoryGame|Factory|Elevator")
	const TArray< AFGCharacterPlayer* >& GetOccupyingCharacters();

	UFUNCTION( BlueprintCallable, Category="FactoryGame|Factory|Elevator")
	const TArray< APawn* >& GetOccupyingPawns();
	
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Factory|Elevator" )
	bool IsElevatorOccupiedByCharacter( AFGCharacterPlayer* character ) { return mOccupyingCharacters.Contains( character ); }
	
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Factory|Elevator" )
	void AddOccupyingPawn( APawn* pawn );
	
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Factory|Elevator" )
	void RemoveOccupyingPawn( APawn* pawn );
	
	UFUNCTION( BlueprintPure, Category="FactoryGame|Factory|Elevator" )
	bool IsElevatorOccupied() const { return mOccupyingCharacters.Num() > 0; }

	UFUNCTION( BlueprintCallable, Category="FactoryGame|Factory|Elevator" )
	int32 GetIndexOfFloorStop( AFGBuildableElevatorFloorStop* floorStop ) const;

	UFUNCTION( BlueprintPure, Category="FactoryGame|Factory|Elevator" )
	int32 GetNumFloorStops() const { return mFloorStopInfos.Num(); }
	
	UFUNCTION( BlueprintPure, Category="FactoryGame|Factory|Elevator" )
	bool HasFloorAtHeight( float height ) const;
	static bool HasFloorAtHeightFromFloorInfos( const TArray< FElevatorFloorStopInfo >& floorInfos, float height );

	UFUNCTION( BlueprintPure, Category="FactoryGame|Factory|Elevator" )
	bool HasFloorInRange( float minHeight, float maxHeight ) const;
	static bool HasFloorInRangeFromFloorInfos( const TArray< FElevatorFloorStopInfo >& floorInfos, float minHeight, float maxHeight );

	UFUNCTION( BlueprintCallable, Category="FactoryGame|Factory|Elevator")
	void GetFloorStopInfos( TArray<FElevatorFloorStopInfo>& out_floorInfos );

	// Called when "modifying" an elevator with another elevator hologram. Stops can change their respective heights
	void ShiftFloorStopHeights( float shiftBy )
	{
		for( FElevatorFloorStopInfo& info : mFloorStopInfos )
		{
			info.Height += shiftBy;
		}
	}

	UFUNCTION( BlueprintPure, Category="FactoryGame|Factory|Elevator" )
	float GetDurationOfCurrentElevatorState();
	
	/**
	 * Gets the floor info closest to this height along the elevator.
	 * @param height - The height we are searching at (local Z position)
	 * @param mustNotMatch - If true this will ignore any stop that is too close to the given height (useful for finding the next stop in a direction)
	 * @param dir - Search UP, DOWN, or any Direction
	 * @return 
	 */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Factory|Elevator" )
	const FElevatorFloorStopInfo& GetFloorStopInfoNearestHeight( float height, bool mustNotMatch = false, EElevatorDirection dir = EElevatorDirection::EED_Any );

	UFUNCTION( BlueprintPure, Category="FactoryGame|Factory|Elevator" )
	const FElevatorFloorStopInfo& GetFloorStopInfoByIndex( int32 index );

	/** Helper function for finding StopInfo from an Floor Stop Buildable */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Factory|Elevator" )
	const FElevatorFloorStopInfo& GetFloorStopInfoFromFloorStop( AFGBuildableElevatorFloorStop* floorStop ) const
	{
		const FElevatorFloorStopInfo* stopPtr = mFloorStopInfos.FindByPredicate( [&]( const FElevatorFloorStopInfo& floorInfo ) { return floorInfo.FloorStop == floorStop; } );
		if( stopPtr )
		{
			return *stopPtr;
		}

		return FElevatorFloorStopInfo::EmptyFloor;
	}

	/**
	 * Sets the name of the stop in the info array
	 * @param floorStop Buildable Floor Stop to set the name of
	 * @param floorStopName Name to assign the floor stop
	 */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Factory|Elevator" )
	void SetNameOfFloorStop( AFGBuildableElevatorFloorStop* floorStop, const FString& floorStopName  );

	/**
	 * Sets the name of the stop in the info array
	 * @param floorStop Buildable Floor Stop to set the icon of
	 * @param iconId Id of the icon in the IconLibrary - INDEX_NONE = NoIcon
	 */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Factory|Elevator" )
	void SetIconForFloorStop( AFGBuildableElevatorFloorStop* floorStop, int32 iconId );

	/**
	 * Sets the icon color for floor stop
	 * @param floorStop Buildable Floor Stop to set the icon color of
	 * @param color LinearColor to set as the icon color
	 */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Factory|Elevator" )
	void SetIconColorForFloorStop( AFGBuildableElevatorFloorStop* floorStop, FLinearColor color );
	
	/** Helper Function for getting the index of a FloorStopInfo struct in a given array of infos */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Factory|Elevator" )
	int32 IndexOfFloorStopInArray( const TArray< FElevatorFloorStopInfo >& infoArray, const FElevatorFloorStopInfo& info );

	/** Gets the total height of the elevator */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Factory|Elevator" )
	FORCEINLINE float GetElevatorHeight() const { return mHeight; }

	/**
	 * Gets the height of the cabin actor relative to the elevator.
	 * @note: This only updates when reaching a floor stop so it cannot be used to reliably get the position of a moving cabin
	 **/
	UFUNCTION( BlueprintPure, Category="FactoryGame|Factory|Elevator" )
	FORCEINLINE float GetCurrentHeightOfCabin() const { return mHeightOfCabin; }

	/**
	 * Gets the current FloorStop buildable that the cabin actor resides.
	 * @note: This only updates when reaching a floor stop so accessing it while the cabin is moving will return the previous stop
	 **/
	UFUNCTION( BlueprintPure, Category="FactoryGame|Factory|Elevator" )
	FORCEINLINE AFGBuildableElevatorFloorStop* GetCurrentFloorStop() const { return mCurrentFloorStop; }

	/**
	 * Gets the current FloorStopInfo that the cabin actor resides.
	 * @note: This only updates when reaching a floor stop so accessing it while the cabin is moving will return the previous stop info
	 **/
	UFUNCTION( BlueprintPure, Category="FactoryGame|Factory|Elevator" )
	FORCEINLINE FElevatorFloorStopInfo GetCurrentFloorStopInfo() const { return GetFloorStopInfoFromFloorStop( mCurrentFloorStop ); }

	// Gets the speed constant of the elevator
	UFUNCTION( BlueprintPure, Category="FactoryGame|Factory|Elevator" )
	FORCEINLINE float GetElevatorElevatorSpeed() const { return mSpeed; }

	// Gets the Elevator Cabin for this elevator.
	// @note: Can be temporarily null for clients
	UFUNCTION( BlueprintPure, Category="FactoryGame|Factory|Elevator" )
	AFGElevatorCabin* GetElevatorCabin() const { return mElevatorCabin; }

	UFUNCTION()
	void OnRep_FloorStops();

	UFUNCTION()
	void RequestGotoFloorStop( AFGBuildableElevatorFloorStop* floorStop );

	// Called by the Cabin Actor when its movement stops. This triggers the BlueprintEvent to allow for any blueprint logic.
	UFUNCTION()
	void CabinReachedDestination( AFGBuildableElevatorFloorStop* floorStop );
	UFUNCTION( BlueprintImplementableEvent )
	void OnCabinReachedDestination( AFGBuildableElevatorFloorStop* floorStop );
	
	UFUNCTION()
	void UpdateStopSequence();

	/**
	 * Event for when the elevator state changes (Moving/Doors Opening/ Doors Closing etc.)
	 * @param elevatorState The current state of the elevator
	 */
	UFUNCTION( BlueprintImplementableEvent, Category="FactoryGame|Factory|Elevator" )
	void OnStopSequenceUpdated( EElevatorState elevatorState );

	void SortFloorStopsByHeightAndDirection( TArray< FElevatorFloorStopInfo >& infoArray, EElevatorDirection dir, float testHeight );
	
	/**
	 * When placing a floor stop onto an existing elevator this will adjust a location into the best snapped location (adjusting around existing floors)
	 * @param location Location to modify into snap location
	 * @return True if a valid position could be found. False otherwise.
	 */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Factory|Elevator" )
	bool SnapLocationToBestNewStopLocation( FVector& location, float stepHeight );

	UFUNCTION( BlueprintCallable, Category="FactoryGame|Factory|Elevator" )
	TArray< class AFGBuildableElevatorFloorStop* > GetElevatorFloorStops() const;

	UFUNCTION()
	void OnRep_ElevatorState();

	// Sets the queued stop indices and updates floor stop queued visuals
	void SetQueuedStopIndices( const TArray< int32 >& queuedStops );
	
	UFUNCTION()
	void OnRep_QueuedStopIndexes();

	void RegisterFloorStopWithElevator( AFGBuildableElevatorFloorStop* floorStop );
	void UnregisterFloorStopWithElevator( AFGBuildableElevatorFloorStop* floorStop );
	void ConnectFloorStopPower( AFGBuildableElevatorFloorStop* floorStop );

	/** When updating a elevator (extending its height) a new elevator is created so we copy the floor stop info from the old onto the new */
	void CopyFloorStopInfoFrom( AFGBuildableElevator* from );

	FORCEINLINE bool CanAcceptFloorStopRequests() const
	{
		return HasPower() && mElevatorState != EElevatorState::EES_SafetyStopping && mElevatorState != EElevatorState::EES_PausePowerOut;
	}

	FORCEINLINE void SetLockedMovementDirection( EElevatorDirection newDir )
	{
		EElevatorDirection lastDir = mLockedMovementDirection;
		mLockedMovementDirection = newDir;
		if( lastDir != newDir )
		{
			MARK_PROPERTY_DIRTY_FROM_NAME( ThisClass, mLockedMovementDirection, this );
		}
	}

	FORCEINLINE void AddFloorStop( const FElevatorFloorStopInfo& newStop ) 
	{
		mFloorStopInfos.Add( newStop );
		MARK_PROPERTY_DIRTY_FROM_NAME( ThisClass, mFloorStopInfos, this );
	}

	FORCEINLINE void RemoveFloorStop( AFGBuildableElevatorFloorStop* floorStop )
	{
		if( floorStop )
		{
			TInlineComponentArray< UFGPowerConnectionComponent* > powerConnections{ floorStop };
			for( auto connection : powerConnections )
			{
				mPowerConnectionComponent->RemoveHiddenConnection( connection );
			}
		}
		mFloorStopInfos.RemoveAll( [&]( const FElevatorFloorStopInfo& floorInfo ) { return floorInfo.FloorStop == floorStop; } );
		MARK_PROPERTY_DIRTY_FROM_NAME( ThisClass, mFloorStopInfos, this );
	}

	// Gets the sparse data class for this elevator
	UFGBuildableElevatorSparseData* GetElevatorSparseData() const { return mElevatorSparseDataCDO; }

	void ClientRegisterCabin( AFGElevatorCabin* cabin ) { mElevatorCabin = cabin; }

	// Called from the Elevator Cabin to set the SongID
	void SetSongID( uint8 songId );
	// Called from Elevator Cabin to Get the songID
	uint8 GetSongID() const { return mSongID; }

	// For clients to update the song in the cabin
	UFUNCTION()
	void OnRep_SongID();

	// Helper to determine if a point falls inside the elevator cabin
	UFUNCTION( BlueprintPure, Category="Personel Elevator" )
	bool IsPointInElevatorCabin( const FVector& location ) const;
	
private:
	// Begin execution of moving to a floor stop. SHould only be called internally.
	void BeginMoveToFloorStop( const FElevatorFloorStopInfo& floorInfo );

	void DebugLogQueuedArray();

	// Setter for the Elevator State that marks the property dirty for replication
	void SetElevatorState( EElevatorState newState );

	// Called when adding an occupying pawn. Should not be called manually as this array is not saved
	void AddOccupyingCharacter( AFGCharacterPlayer* character ) { mOccupyingCharacters.AddUnique( character ); }
	void RemoveOccupyingCharacter( AFGCharacterPlayer* character ) { mOccupyingCharacters.Remove( character ); }
	
protected:
	
#if WITH_EDITOR
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif
	
public:
	// Elevator Constants
	static constexpr int32 STEP_HEIGHT = 100;
	static constexpr int32 MIN_HEIGHT_BETWEEN_FLOORS = 100;
	static constexpr int32 FLOOR_HEIGHT = 400;
	static constexpr int32 TOTAL_FLOOR_HEIGHT = MIN_HEIGHT_BETWEEN_FLOORS + FLOOR_HEIGHT;
	static constexpr int32 MAX_NUM_FLOORS = 25;
	static constexpr int32 MIN_ELEVATOR_HEIGHT = ( FLOOR_HEIGHT * 2 ) + MIN_HEIGHT_BETWEEN_FLOORS;
	// Used as default. This can be changed by setting the property in the Elevator Sparse Data
	static constexpr int32 MAX_ELEVATOR_HEIGHT = ((TOTAL_FLOOR_HEIGHT * MAX_NUM_FLOORS * 4) - MIN_HEIGHT_BETWEEN_FLOORS);
	static constexpr int32 SHAFT_WIDTH = 800;
	static constexpr int32 SHAFT_HALF_WIDTH = SHAFT_WIDTH / 2;
	
#if WITH_EDITORONLY_DATA
	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Buildable")
	UFGBuildableElevatorSparseData* mElevatorSparseData;
#endif

	UPROPERTY( )
	UFGBuildableElevatorSparseData* mElevatorSparseDataCDO;



private:
	friend class AFGElevatorHologram;
	friend class AFGElevatorCabin;
	
	UPROPERTY( Replicated, SaveGame )
	TObjectPtr< AFGElevatorCabin > mElevatorCabin;

	UPROPERTY()
	FTimerHandle mStopAtFloorTimerHandle;
	
	UPROPERTY()
	FTimerHandle mPowerOutPauseTimerHandle;
	
	// Time to interpolate between stops. This is divided by the stop height + min distance (500.f) to get the time to interpolate. Tex. 500 speed = 1s to travel if 2 stops are right on top of each other.
	UPROPERTY( EditDefaultsOnly )
	float mSpeed = 100.f;
	
	UPROPERTY( Replicated, SaveGame )
	float mHeight;

	// To behave like a real world elevator. Stops can be queued up but the elevator won't travel to stops that don't fall in its currently assigned direction path.
	// ie. If we are traveling to stop 17 from stop 10 our direction is UP. If a new stop is selected that falls between 10 and 17 (and we haven't yet reached it) we will stop there.
	// However if say stop 5 was selected we will first travel to 17 before traveling down to 5
	UPROPERTY(Replicated)
	EElevatorDirection mLockedMovementDirection;
	
	UPROPERTY( ReplicatedUsing=OnRep_FloorStops, SaveGame )
	TArray< FElevatorFloorStopInfo > mFloorStopInfos;

	UPROPERTY()
	TArray< FElevatorFloorStopInfo > mQueuedStops;

	UPROPERTY( ReplicatedUsing=OnRep_QueuedStopIndexes )
	TArray< int32 > mQueuedStopIndexes;

	// DEPRECATED - Left for converting to mAllPawnsInElevator 
	UPROPERTY( SaveGame )
	TArray< class AFGCharacterPlayer* > mCharactersInElevator;

	UPROPERTY()
	TArray< AFGCharacterPlayer* > mOccupyingCharacters;
	
	UPROPERTY( SaveGame )
	TArray< class APawn* > mAllPawnsInElevator;

	// The position of the cabin in the elevator. This is only updated when a stop is reached. Saved so the Cabin can be spawned at the correct location
	UPROPERTY( SaveGame, Replicated )
	float mHeightOfCabin;

	// The ID (specified in blueprint assets) of the track that is set to be playing on this elevator
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_SongID )
	uint8 mSongID; 

	UPROPERTY()
	AFGBuildableElevatorFloorStop* mCurrentFloorStop;

	UPROPERTY( EditDefaultsOnly, Category="Elevator")
	float mDurationToOpenDoors = 1.f;

	UPROPERTY( EditDefaultsOnly, Category="Elevator")
	float mDurationToWaitAtStop = 3.f;
	
	UPROPERTY( EditDefaultsOnly, Category="Elevator")
	float mDurationToCloseDoors = 1.f;

	UPROPERTY( EditDefaultsOnly, Category="Elevator")
	float mDurationPauseBeforeMove = 0.5f;

	UPROPERTY( EditDefaultsOnly, Category="Elevator")
	float mDurationPausePowerOutage = 2.f;

	UPROPERTY( EditDefaultsOnly, Category="Elevator")
	float mDurationPauseBeforeDoorOpen = 0.5f;

	UPROPERTY( VisibleAnywhere, Category="Power" )
	TObjectPtr< UFGPowerConnectionComponent > mPowerConnectionComponent;

	UPROPERTY( ReplicatedUsing=OnRep_ElevatorState )
	EElevatorState mElevatorState;

	static TArray< FInstanceData > BuildElevatorInstanceData( const TArray< FElevatorFloorStopInfo >& floorInfos, float height, UFGBuildableElevatorSparseData* sparseData, float zOffset = 0.f )
	{
		TArray< FInstanceData > InstanceData;
		
		float currentPosition = -AFGBuildableElevator::MIN_HEIGHT_BETWEEN_FLOORS; // Start at -100 so that the later loop can run normally
		FInstanceData data1m;
		data1m.StaticMesh = sparseData->mHeightSegment1m;
		data1m.NumCustomDataFloats = 20;
		data1m.Mobility = EComponentMobility::Static;
		data1m.bUseAkGeometry = true;
		data1m.MeshType = sparseData->AkMeshType;
		FInstanceData data4m;
		data4m.StaticMesh = sparseData->mHeightSegment4m;
		data4m.NumCustomDataFloats = 20;
		data4m.Mobility = EComponentMobility::Static;
		data4m.bUseAkGeometry = true;
		data4m.MeshType = sparseData->AkMeshType;
		int32 numLarge = 0;

		bool useLargeMesh = false;

		FInstanceData bottomMesh;
		bottomMesh.StaticMesh = sparseData->mBottomMesh;
		bottomMesh.NumCustomDataFloats = 20;
		bottomMesh.Mobility = EComponentMobility::Static;
		bottomMesh.RelativeTransform = FTransform( FVector( 0.f, 0.f, 0.f ) );
		bottomMesh.bUseAkGeometry = true;
		bottomMesh.MeshType = sparseData->AkMeshType;
		if( bottomMesh.StaticMesh )
		{
			InstanceData.Add( bottomMesh );
		}

		FInstanceData topMesh;
		topMesh.StaticMesh = sparseData->mTopMesh;
		topMesh.NumCustomDataFloats = 20;
		topMesh.Mobility = EComponentMobility::Static;
		topMesh.RelativeTransform = FTransform( FVector( 0.f, 0.f, height ) );
		topMesh.bUseAkGeometry = true;
		topMesh.MeshType = sparseData->AkMeshType;
		if( topMesh.StaticMesh )
		{
			InstanceData.Add( topMesh );
		}

		while( currentPosition < height )
		{
			do
			{
				currentPosition += HasFloorAtHeightFromFloorInfos( floorInfos, currentPosition + STEP_HEIGHT ) ? FLOOR_HEIGHT : STEP_HEIGHT;
			} while( HasFloorAtHeightFromFloorInfos( floorInfos, currentPosition ) && currentPosition < height );

			// Check if we have 4m meters of space to instead use a 4m mesh
			if( currentPosition + AFGBuildableElevator::FLOOR_HEIGHT <= height )
			{
				if( !HasFloorInRangeFromFloorInfos(floorInfos, currentPosition + AFGBuildableElevator::MIN_HEIGHT_BETWEEN_FLOORS, currentPosition + AFGBuildableElevator::FLOOR_HEIGHT ) )
				{
					useLargeMesh = true;
				}
			}

			if( currentPosition < height )
			{
				if( useLargeMesh )
				{
					++numLarge;
					data4m.RelativeTransform = FTransform( FVector( 0.f, 0.f, currentPosition + zOffset ) );
					//data4m.RelativeTransform.SetRotation( FQuat::MakeFromRotator( data4m.RelativeTransform.GetRotation().Rotator() + FRotator(0.f, numLarge % 2 == 0 ? 90.f : 0.f, 0.f ) ) );
					InstanceData.Add( data4m );
					currentPosition += AFGBuildableElevator::FLOOR_HEIGHT - AFGBuildableElevator::MIN_HEIGHT_BETWEEN_FLOORS;
					useLargeMesh = false;
				}
				else
				{
					data1m.RelativeTransform = FTransform( FVector( 0.f, 0.f, currentPosition + zOffset ) );
					InstanceData.Add( data1m );
				}
			}
		}
		
		return InstanceData;
	}
};
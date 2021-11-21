// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGSaveInterface.h"
#include "Slate/WidgetTransform.h"
#include "Containers/Map.h"
#include "Math/TransformCalculus2D.h"
#include "FGTargetPointLinkedList.generated.h"

USTRUCT( BlueprintType )
struct FDrivingTargetListMapStationData
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadOnly )
	class UFGActorRepresentation* Station = nullptr;

	UPROPERTY( BlueprintReadOnly )
	FVector2D DisplayPosition;
};

USTRUCT( BlueprintType )
struct FDrivingTargetListMapData
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadOnly )
	TArray< FVector2D > PathPoints;

	UPROPERTY( BlueprintReadOnly )
	FWidgetTransform MapTransform;

	UPROPERTY( BlueprintReadOnly )
	TArray< FDrivingTargetListMapStationData > Stations;

	UPROPERTY( BlueprintReadOnly )
	TArray< FWidgetTransform > ArrowTransforms;
};


/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGDrivingTargetList : public AInfo, public IFGSaveInterface
{
public:
	GENERATED_BODY()

	/** Ctor */
	AFGDrivingTargetList();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override {}
	virtual bool NeedTransform_Implementation() override { return false; }
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	// End AActor Interface

	void CreatePath();
	void DestroyPath_Server();
	void DestroyLocalActors();

	/** Add a new item in the end of the linked list */
	void AppendItem( class AFGTargetPoint* newTarget );
	
	/** Add a new item in the end of the linked list */
	void InsertItem( class AFGTargetPoint* newTarget, class AFGTargetPoint* afterTarget );

	/** Removes the desired element from the linked list */
	void RemoveItem( class AFGTargetPoint* targetToRemove );

	/** Get the first target in linked list */
	FORCEINLINE class AFGTargetPoint* GetFirstTarget() const { return mFirst; }

	/** Get the first target in linked list */
	FORCEINLINE class AFGTargetPoint* GetLastTarget() const { return mLast; }

	/** Sets visibility ( and collision ) status of all the targets in the linked list */
	void SetPathVisible( bool isVisible );

	bool IsPathVisible() const { return mIsPathVisible; }

	int GetTargetCount() const { return mTargetCount; }

	UFUNCTION( BlueprintPure, Category = "TargetList" )
	float GetPathLength() const { return mPathLength; }

	UFUNCTION( BlueprintPure, Category = "TargetList" )
	float GetPathTime() const { return mPathTime; }

	int FindTargetIndex( class AFGTargetPoint* target ) const;
	class AFGTargetPoint* FindTargetByIndex( int index ) const;
	class AFGTargetPoint* FindPreviousTarget( class AFGTargetPoint* currentTarget ) const;
	class AFGTargetPoint* GetNextTarget( class AFGTargetPoint* currentTarget ) const;

	/**
	 * Finds the target point closes to the vehicle owning this list 
	 * @param withinLookAngle -1 means ignore look angle
	 * */
	class AFGTargetPoint* FindBestTarget( AActor* vehicleActor, float withinLookAngle = -1.0f, float maxDistance = -1.0f ) const;

	/** Clears the linked list and destroys the targets */
	//UFUNCTION( BlueprintCallable, Category = "Path" )
	//void ClearRecording();

	/**
	 * @param displaySize the pixel length of the side of the display (for now, only square displays are supported)
	 * @param positions the output positions to be displayed, in display space
	 * @param displayTransform the output transform to be applied on the display
	 */
	UFUNCTION( BlueprintCallable, Category = "TargetList" )
	void GetMapData( float displaySize, int numberOfPoints, FDrivingTargetListMapData& data );

	bool IsComplete() const;

	/** @returns true if targets were modified during cleanup */
	bool CleanUpDockingTargets( class AFGBuildableDockingStation* onlyAtStation = nullptr );

	bool IsNearingStation( class AFGTargetPoint* queryTarget, class AFGBuildableDockingStation* station, int searchRange ) const;

	void SetIsTemporary( bool isTemporary );

	bool IsTemporary() const { return mIsTemporary; }

	bool HasData() const;

	int CountTargets() const;

	void CalculateTargetCount();

	float GetPathFuelConsumption() const { return mPathFuelConsumption; }
	void SetPathFuelConsumption( float pathFuelConsumption );

	float GetFuelConsumptionRate() const { return mFuelConsumptionRate; }

	void AddToTouchedStations( class AFGWheeledVehicle* vehicle );
	void RemoveFromTouchedStations( class AFGWheeledVehicle* vehicle );

	float CalculatePathFuelConsumption( TSubclassOf< class UFGItemDescriptor > fuelType ) const;
	float CalculateFuelConsumptionRate( TSubclassOf< class UFGItemDescriptor > fuelType ) const;

	class USplineComponent* GetPath() const { return mPath; }

private:
	UFUNCTION()
	void OnRep_IsPathVisible();

	UFUNCTION()
	void OnRep_IsTemporary();

	UFUNCTION()
	void OnRep_TargetCount();

public:
	/** First node in linked list */
	UPROPERTY( SaveGame, Replicated )
	class AFGTargetPoint* mFirst; 

	/** Last node in linked list */
	UPROPERTY( SaveGame, Replicated )
	class AFGTargetPoint* mLast;

	/** Deprecated and kept for save compatibility. Use AFGWheeledVehicle::mCurrentTarget instead. */
	UPROPERTY( SaveGame )
	class AFGTargetPoint* mCurrentTarget;

	/** Max length that the linked list can be */
	UPROPERTY( EditDefaultsOnly, Category = "TargetList" )
	int32 mMaxLength;

	UPROPERTY()
	class AFGMinimapCaptureActor* mCachedMinimapCaptureActor;

	bool mIsBeingRecorded = false;

	UPROPERTY( SaveGame, Replicated, BlueprintReadOnly )
	TSubclassOf< class AFGWheeledVehicle > mVehicleType;

	// maximum "supported" distance between targets / 2
	static constexpr float MaxSegmentExtent = 3000.0f;

	float mCollisionAvoidanceDistance = 0.0f;

private:
	friend class UFGSplinePathMovementComponent;
	friend class AFGTargetPoint;

	/** Should targets nodes be visible */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_IsPathVisible )
	bool mIsPathVisible = true;

	UPROPERTY( ReplicatedUsing = OnRep_IsTemporary )
	bool mIsTemporary = false;

	UPROPERTY( Transient )
	class AActor* mPathActor;

	UPROPERTY( Transient )
	class USplineComponent* mPath;

	UPROPERTY( ReplicatedUsing = OnRep_TargetCount )
	int mTargetCount;

	bool mIsLooping = true;

	float mPathTime = 0.0f;
	float mPathLength = 0.0f;

	/**
	 * The amount of fuel a vehicle on this path will consume during one lap while in automated mode, equally divided over time
	 */
	UPROPERTY( SaveGame, Replicated )
	float mPathFuelConsumption = 0.0f;

	float mFuelConsumptionRate = 0.0f;
};

/**
 * Deprecated. Kept for compatibility with legacy saves
 */
UCLASS()
class FACTORYGAME_API UFGTargetPointLinkedList : public UObject, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override {}
	virtual bool NeedTransform_Implementation() override { return false; }
	virtual bool ShouldSave_Implementation() const override { return false; }
	// End IFSaveInterface

	/** First node in linked list */
	UPROPERTY( SaveGame )
	class AFGTargetPoint* mFirst;

	/** Last node in linked list */
	UPROPERTY( SaveGame )
	class AFGTargetPoint* mLast;

	/** Current node */
	UPROPERTY( SaveGame )
	class AFGTargetPoint* mCurrentTarget;
};

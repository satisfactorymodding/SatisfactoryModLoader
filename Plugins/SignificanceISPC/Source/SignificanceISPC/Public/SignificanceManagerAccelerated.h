// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SignificanceManagerAccelerated.generated.h"

enum class SignificanceState : int8
{
	Unknown = -1,
	Insignificant = 0,
	Significant = 1
};

struct FStaticObjectSignificanceUpdateInfo
{
	FVector ObjectLocation{ForceInit};
	float ObjectRadius{0.0f};
};

struct FStaticSignificanceRegistrationInfo : FStaticObjectSignificanceUpdateInfo
{
	float SignificanceRange{0.0f};
	bool bIsTickManaged{false};
	int32 NumTickLevels{INDEX_NONE};
};

struct FStaticAcceleratedManagedSignificanceInfo
{
	FVector3f CachedLocation;
	float CachedObjectRadius;
	float CachedSignificanceRange;
	float SignificanceDistanceSquare;
	int8 NumTickStages;

	int8 CurrentTickStage;	
	float CurrentSignificance;
	float ClosestDistSquared;

	/* -1 for unknown, 0 false, 1 true. */
	SignificanceState bIsSignificant;
	SignificanceState bWasSignificant;
	SignificanceState bDidChangeTickState;

	bool bSupportsTickRateDilation;
	bool bIsObjectAllocated;

	FStaticAcceleratedManagedSignificanceInfo() = default;

	explicit FStaticAcceleratedManagedSignificanceInfo(const FStaticSignificanceRegistrationInfo& RegistrationInfo) :
		CachedLocation(RegistrationInfo.ObjectLocation),
		CachedObjectRadius(RegistrationInfo.ObjectRadius),
		CachedSignificanceRange(RegistrationInfo.SignificanceRange),
		SignificanceDistanceSquare(FMath::Square(CachedObjectRadius + CachedSignificanceRange)),
		NumTickStages(RegistrationInfo.NumTickLevels),
		CurrentTickStage(NumTickStages),
		CurrentSignificance(-1.0f),
		ClosestDistSquared(3.4e+38f),
		bIsSignificant(SignificanceState::Unknown),
		bWasSignificant(SignificanceState::Unknown),
		bDidChangeTickState(SignificanceState::Unknown),
		bSupportsTickRateDilation(RegistrationInfo.bIsTickManaged),
		bIsObjectAllocated(true)
	{
	}
};

struct FStaticAcceleratedManagedObjectInfo
{
	TWeakObjectPtr<UObject> ManagedObject;
	FName DebugObjectTag;
	bool bIsDynamicObject;

	FStaticAcceleratedManagedObjectInfo() = default;

	FStaticAcceleratedManagedObjectInfo(UObject* InObject, const bool bInIsDynamicObject)
	{
		ManagedObject = InObject;
		DebugObjectTag = InObject->GetFName();
		bIsDynamicObject = bInIsDynamicObject;
	}
};

/**
 * Accelerated significance manager handles object significance using ISPC
 * Objects that are close to the active view points will be considered significant.
 * Significance is not networked and is only for local players.
 */
UCLASS(Abstract)
class SIGNIFICANCEISPC_API USignificanceManagerAccelerated : public UTickableWorldSubsystem
{
	GENERATED_BODY()
public:
	// Begin UWorldSubsystem interface
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	// End UWorldSubsystem interface
	
	/** Adds a new object to the significance manager */
	void RegisterObject(UObject* Object, bool bIsDynamicObject);
	/** Removes an object from the significance manager */
	void RemoveObject(UObject* Object);
	/** Recalculates the significance range and location for the given object after it has already been added to the significance manager */
	void UpdateStaticObjectSignificanceRange(UObject* Object);

	/** Dumps information about the significance manager state to the log */
	void DumpSignificanceDebugData();
protected:
	void CalculatePlayerViewpoints(TArray<FVector3f>& OutPlayerViewpoints) const;
	int32 AllocateEntryIndex();
	void ReleaseEntryIndex(int32 EntryIndex);

	bool CalculateImmediateSignificanceState(const FStaticAcceleratedManagedSignificanceInfo& SignificanceInfo);

	/** Can be overriden by the subclass to receive the initial estimated significance state of the registered static object */
	virtual void SetInitialSignificanceState(UObject* Object, bool bState) {}

	/** Given an object, populate a registration info with the information about the significance state of this object */
	virtual FStaticSignificanceRegistrationInfo GetStaticObjectInfo(const UObject* Object) const PURE_VIRTUAL(USignificanceManagerAccelerated::GetStaticObjectInfo, return FStaticSignificanceRegistrationInfo{};);
	/** Will be called to update a location of dynamic objects every frame */
	virtual FStaticObjectSignificanceUpdateInfo GetDynamicObjectInfo(const UObject* Object) const PURE_VIRTUAL(USignificanceManagerAccelerated::GetDynamicObjectLocation, return FStaticObjectSignificanceUpdateInfo{};);

	/** Client side on significance loss, expecting a project based interface call to be implemented in subclass */
	virtual void OnSignificanceLoss(UObject* Object) {}
	/** Client side on significance gain, expecting a project based interface call to be implemented in subclass */
	virtual void OnSignificanceGain(UObject* Object) {}
	/** Tick rate reduction based on significance */
	virtual void OnSignificanceTickRateUpdate(UObject* Object, int32 TickLevel, int32 NumTickLevels) {}

	/** Number of frames that it will take to process all significant objects in order */
	UPROPERTY(EditDefaultsOnly, Category = "Significance Manager")
	int32 NumFramesForFullCycle{10};

	/**
	 * Arrays with aligned ID's, one contains the data for the ISPC function to compute the relevancy, the other
	 * contains the same implementation as native Unreal Engine's significance system.
	 */
	TArray<FStaticAcceleratedManagedSignificanceInfo> StaticEntries;
	TArray<FStaticAcceleratedManagedObjectInfo> StaticEntriesObjects;
	TBitArray<> DynamicObjectEntryIndices;
	TArray<int32> FreeEntryIndices;
	TMap<TWeakObjectPtr<UObject>, int32> ObjectEntryIndexLookup;
	TArray<FVector3f> LastFramePlayerViewPoints;
	bool bHasCachedPlayerViewPoints{false};
	int32 LastHandledItem{0};
};

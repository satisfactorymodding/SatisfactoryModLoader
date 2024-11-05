// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Math/GenericOctree.h"
#include "SignificanceManager.h"
#include "SignificanceManagerAccelerated.h"
#include "HAL/IConsoleManager.h"
#include "FGSignificanceManager.generated.h"

static TAutoConsoleVariable<float> CVarSignificanceManagerTickRateServerSide(
	TEXT("SigMan.server.tickrate"),
	0.5,
	TEXT("Tick frequency(sec)\n @NOTE Needs session restart to apply."));

enum class EFGSignificanceType : uint8
{
	Creature,
	AudioVolume,
	GenericTickHelper,
	ConveyorBelt,
	Factory,
	LowDistanceGainSignificance,
	MidDistanceGainSignificance,
	HighDistanceGainSignificance,
	AmbientSoundSpline,
	CustomDistanceGainSignificance,
	ParticleSignificance,
	TrainSignificance,
	PipelineSignificance,
	MAX
};

USTRUCT()
struct FServerSideSignificanceData
{
	GENERATED_BODY()
	
	UPROPERTY()
	UObject* Object;
	
	mutable SignificanceState bWasSignificant = SignificanceState::Unknown;
	mutable int32 RelevanceCounter = 0;

	FServerSideSignificanceData(UObject* InObject) : Object( InObject ) { }
	FServerSideSignificanceData() : Object( nullptr ) { }

	bool operator==(const FServerSideSignificanceData& A) const
	{
		return this->Object == A.Object;
	}
};

FORCEINLINE uint32 GetTypeHash(const FServerSideSignificanceData* Thing)
{
	return FCrc::MemCrc32(&Thing, sizeof(FServerSideSignificanceData));
}

struct FSignificanceOctreeSemantics
{
	// When a leaf gets more than this number of elements, it will split itself into a node with multiple child leaves
	enum { MaxElementsPerLeaf = 10 };
	enum { MinInclusiveElementsPerNode = 5 };
	enum { MaxNodeDepth = 64 };

	using FOctree = TOctree2<UObject*, FSignificanceOctreeSemantics>;
	typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator;

	static FBoxCenterAndExtent GetBoundingBox(const UObject* Element);
	static bool AreElementsEqual(const UObject* A, const UObject* B) { return A == B; }
	static void SetElementId(FOctree& Octree, UObject* Element, FOctreeElementId2 OctreeElementID);
};

struct FSignificanceOctree : public TOctree2<UObject*, FSignificanceOctreeSemantics>
{
	FSignificanceOctree() = default;
	FSignificanceOctree(const FVector& InOrigin,FVector::FReal InExtent) : TOctree2(InOrigin, InExtent) {};

	TMap<UObject*, TPair<FServerSideSignificanceData,FOctreeElementId2>> mElementIdMap;
};


USTRUCT() 
struct FACTORYGAME_API FGainSignificanceData
{
	GENERATED_BODY()
	EFGSignificanceType SignificanceType; 
	int32				GainSignificanceDistance;
};

USTRUCT()
struct FFGPawnLocationData
{
	GENERATED_BODY()
	FVector CurrentLocation = FVector::ZeroVector;
	FVector LastUpdatedLocation = FVector::ZeroVector;
	bool bIsValid = false;
};

/**
 * 
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGSignificanceManager : public USignificanceManagerAccelerated
{
	GENERATED_BODY()
public:
	UFGSignificanceManager(); 


	//This is the function that users call as a replacement for the virtual RegisterObject which exposes only the significance type so it can be looked up
	void RegisterSignificanceObject( UObject* Object, EFGSignificanceType SignificanceType );

	virtual void RegisterObject(UObject* Object, FName Tag, FManagedObjectSignificanceFunction SignificanceFunction, EPostSignificanceType InPostSignificanceType = EPostSignificanceType::None, FManagedObjectPostSignificanceFunction InPostSignificanceFunction = nullptr) override;
	virtual void UnregisterObject(UObject* Object) override;

	virtual void Update( TArrayView<const FTransform> Viewpoints ) override;

	// Begin USignificanceManagerAccelerated interface
	virtual void OnSignificanceLoss(UObject* Object, EPostSignificanceType InPostSignificanceType) override;
	virtual void OnSignificanceGain(UObject* Object, EPostSignificanceType InPostSignificanceType) override;
	virtual void OnSignificanceTickRateUpdate(UObject* Object, int32 TickLevel, int32 NumTickLevels) override;
	
	virtual void OnServerSignificanceGain(UObject* Object, EPostSignificanceType InPostSignificanceType) override;
	virtual void OnServerSignificanceLoss(UObject* Object, EPostSignificanceType InPostSignificanceType) override;
	virtual float GetServerSignificanceNetworkRange(UObject* Object) const override;

	virtual float GetSignificanceRange(UObject* Object) const override;
	virtual FVector GetObjectLocation(UObject* Object) const override;
	virtual bool GetIsTickManaged(UObject* Object) const override;
	virtual int32 GetNumTickLevels(UObject* Object) const override;
	virtual float GetTickExponent(UObject* Object) const override;
	virtual void SetIsSignificance(UObject* Object, bool bState) override;
	// End USignificanceManagerAccelerated interface.

	FGainSignificanceData GetClosestGainSignificanceData( UObject* inObject, float desiredDistance );

	void DumpSignificanceManagedObjects();

	/** Is the manager enabled */
	UPROPERTY( EditAnywhere, Category = "SignificanceManager" )
	bool mIsEnabled;

	/** caching delta time before doing Update() */
	float mCachedDT;
	
	// Add actor to shared networked significance cell.
	void AddObjectToSignificanceOctTree( UObject* Object );
	void RemoveObjectFromSignificanceOctTree( UObject* Object );

	void RegisterNetObject();
	void RemoveNetObject();
	
protected:
	/** Keeps the list of conveyor belts sorted and sets the closest ones to significant */
	void UpdateConveyorBelts();

	/** Keeps the list of factories sorted and sets the closest ones to significant */
	void UpdateFactories();

	/** Keeps the list of pipelines sorted and sets the closest ones to significant */
	void UpdatePipelines();

	/** Sets significance status */
	static void UpdateSignificanceStatus( float oldSignificance, float newSignificance, UObject* inObject );
private:
	static FName GetTagFromTagEnum( EFGSignificanceType InType );

	static void OnComponentActivationChange( UParticleSystemComponent* PSC, bool bActivated );

	//Generic Significance functions
	static float GenericTickSignificance( FManagedObjectInfo* Object, const FTransform& Viewpoint );
	static void GenericTickPostSignificance( FManagedObjectInfo* ObjectInfo, float OldSignificance, float NewSignificance, bool bFinal );

	//Generic Significance functions
	static float ParticleTickSignificance( FManagedObjectInfo* Object, const FTransform& Viewpoint );
	static void ParticleTickPostSignificance( FManagedObjectInfo* ObjectInfo, float OldSignificance, float NewSignificance, bool bFinal );

	//Factory Significance functions
	static float FactorySignificance( FManagedObjectInfo* Object, const FTransform& Viewpoint );
	static void FactoryPostSignificance( FManagedObjectInfo* ObjectInfo, float OldSignificance, float NewSignificance, bool bFinal );

	//ConveyorBelt Significance functions
	static float ConveyorBeltSignificance( FManagedObjectInfo* Object, const FTransform& Viewpoint );
	static void ConveyorBeltPostSignificance( FManagedObjectInfo* ObjectInfo, float OldSignificance, float NewSignificance, bool bFinal );

	//Pipeline Significance functions
	static float PipelineSignificance( FManagedObjectInfo* Object, const FTransform& Viewpoint );
	static void PipelinePostSignificance( FManagedObjectInfo* ObjectInfo, float OldSignificance, float NewSignificance, bool bFinal );

	//Gain Significance on low distance functions
	static float LowDistanceSignificance( FManagedObjectInfo* Object, const FTransform& Viewpoint );

	//Gain Significance on mid distance functions
	static float MidDistanceSignificance( FManagedObjectInfo* Object, const FTransform& Viewpoint );

	//Gain Significance on high distance functions
	static float HighDistanceSignificance( FManagedObjectInfo* Object, const FTransform& Viewpoint );

	//Gain Significance on custom distance functions
	static float CustomDistanceSignificance( FManagedObjectInfo* Object, const FTransform& Viewpoint );

	/** Either call gain or lose significance based on value */
	static void GainSignificanceOnDistancePostSignificance( FManagedObjectInfo* ObjectInfo, float OldSignificance, float NewSignificance, bool bFinal );

	//Ambient volume functions
	static float AudioVolumeSignificance( FManagedObjectInfo* Object, const FTransform& Viewpoint );
	static void AudioVolumePostSignificance( FManagedObjectInfo* ObjectInfo, float OldSignificance, float NewSignificance, bool bFinal );

	//Ambient sound spline functions
	static float AmbientSoundSplineSignificance( FManagedObjectInfo* Object, const FTransform& Viewpoint );
	static void AmbientSoundSplinePostSignificance( FManagedObjectInfo* ObjectInfo, float OldSignificance, float NewSignificance, bool bFinal );

	//Ambient sound spline functions
	static float TrainSignificance( FManagedObjectInfo* Object, const FTransform& Viewpoint );
	static void TrainPostSignificance( FManagedObjectInfo* ObjectInfo, float OldSignificance, float NewSignificance, bool bFinal );

	/** Helper functions for getting location and setting tick rates */
	FORCEINLINE static FVector GetObjectLocation( FManagedObjectInfo* objInfo ){ return GetObjectLocation_Old( objInfo->GetObject() ); }
	static FVector GetObjectLocation_Old( UObject* obj ); // TODO Deprecate.
	FORCEINLINE static void SetObjectTickRate( FManagedObjectInfo* objInfo, float newTickRate ){ SetObjectTickRate( objInfo->GetObject(), newTickRate ); }
	static void SetObjectTickRate( UObject* obj, float newTickRate );
	FORCEINLINE static void SetObjectTicks( FManagedObjectInfo* objInfo, bool newTicks ){ SetObjectTicks( objInfo->GetObject(), newTicks ); }
	static void SetObjectTicks( UObject* obj, bool newTicks );
	static void SetObjectLOD(FManagedObjectInfo* objInfo, int32 newLod);
	/* Data about the different distance levels */
	TArray< FGainSignificanceData > mGainSignificanceData;

	/** List of factories that were significant last time we checked */
	UPROPERTY()
	TArray< class AFGBuildableFactory* > mPreviousSignificantFactories;

	/** List of conveyor bases (belts and lifts) that were significant last time we checked */
	UPROPERTY()
	TArray< class AFGBuildableConveyorBase* > mPreviousSignificantConveyorBases;

	/** List of pipelines that were significant last time we checked */
	UPROPERTY()
	TArray< class AFGBuildablePipeBase* > mPreviousSignificantPipelines;

	/** How often we should sort the factories/conveyors */
	float mSortTimerTime;

	/** Current value of sorting timer */
	float mSortTimer;

	// Begin serverside significance.
	/* Octree containing all entries that could go significant.
	 * Used for server side significance.*/
	FSignificanceOctree mServerSideSignificanceOctree;

	/* Set of current significant entries.
	 * Used for server side significance. */
	UPROPERTY()
	TSet<UObject*> mSignificantSet;

	/* Map from pawn to location used to determine the distance. */
	UPROPERTY()
	TMap<APawn*, FFGPawnLocationData> mPawnToLocationMap;
	// End serverside significance
};


/*	Tickable world subsystem which ticks the significance manager on servers as they have no viewport which
 *	ticks the current implementation of the significance manager.
 *	@TODO post1.0 ensure we dont spawn or register the tick function for listen servers & clients, they have their own viewport. */
UCLASS()
class UFGSignificanceServerManager : public UTickableWorldSubsystem
{
	GENERATED_BODY()

	virtual void Tick(float DeltaTime) override;
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual TStatId GetStatId() const override {RETURN_QUICK_DECLARE_CYCLE_STAT(UFGSignificanceServerManager, STATGROUP_Tickables);} 
	virtual ETickableTickType GetTickableTickType() const override
	{
		return ETickableTickType::Always;
	}
	
	/* Accumulated delta time since last tick*/
	float mAccumulatedDT = 0;

	/* Current update rate for the server side significance, this is set through `SigMan.server.tickrate` */
	float mUpdateRate = 0.5;
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Math/GenericOctree.h"
#include "SignificanceManagerAccelerated.h"
#include "FGSignificanceManager.generated.h"

// No initializers to keep it a plain old data type
struct FSignificanceOctreeElement
{
	FBoxCenterAndExtent BoundingBox;
	UObject* Object;
};

struct FSignificanceOctreeSemantics
{
	// When a leaf gets more than this number of elements, it will split itself into a node with multiple child leaves
	enum { MaxElementsPerLeaf = 16 };
	enum { MinInclusiveElementsPerNode = 7 };
	enum { MaxNodeDepth = 20 };

	using FOctree = TOctree2<FSignificanceOctreeElement, FSignificanceOctreeSemantics>;
	typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator;

	static const FBoxCenterAndExtent& GetBoundingBox(const FSignificanceOctreeElement& Element) { return Element.BoundingBox; }
	static bool AreElementsEqual(const FSignificanceOctreeElement& A, const FSignificanceOctreeElement& B) { return A.Object == B.Object; }
	static void SetElementId(FOctree& Octree, const FSignificanceOctreeElement& Element, FOctreeElementId2 OctreeElementID);
};

struct FSignificanceOctree : public TOctree2<FSignificanceOctreeElement, FSignificanceOctreeSemantics>
{
	FSignificanceOctree() = default;
	FSignificanceOctree(const FVector& InOrigin, const FVector::FReal InExtent) : TOctree2(InOrigin, InExtent) {};

	TMap<UObject*, FOctreeElementId2> mElementIdMap;
};

USTRUCT()
struct FFGPawnLocationData
{
	GENERATED_BODY()

	FVector CurrentLocation{ForceInit};
	FVector LastUpdatedLocation{ForceInit};
	bool bIsValid{false};
};

/**
 * Significance manager manages which objects are significant to the player viewport and which are not
 */
UCLASS()
class FACTORYGAME_API UFGSignificanceManager : public USignificanceManagerAccelerated
{
	GENERATED_BODY()
public:
	// Begin USignificanceManagerAccelerated interface
	virtual FStaticSignificanceRegistrationInfo GetStaticObjectInfo(const UObject* Object) const override;
	virtual FStaticObjectSignificanceUpdateInfo GetDynamicObjectInfo(const UObject* Object) const override;
	virtual void OnSignificanceLoss(UObject* Object) override;
	virtual void OnSignificanceGain(UObject* Object) override;
	virtual void OnSignificanceTickRateUpdate(UObject* Object, int32 TickLevel, int32 NumTickLevels) override;
	virtual void SetInitialSignificanceState(UObject* Object, bool bState) override;
	// End USignificanceManagerAccelerated interface

	/** Calculates object bounding box for significance calculation */
	static FBox CalculateObjectBoundingBox( const UObject* Element );
};

UCLASS()
class FACTORYGAME_API UFGServerSideSignificanceSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
public:
	UFGServerSideSignificanceSubsystem();
	
	// Begin UTickableWorldSubsystem interface
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	// End UTickableWorldSubsystem interface

	void AddObjectToSignificanceOctTree( UObject* Object );
	void RemoveObjectFromSignificanceOctTree( UObject* Object );
	/** Manually marks the object as significant until the next significance update. Object will immediately receive GainedNetSignificance unless it is already net significant */
	void ManuallyMarkObjectSignificant( UObject* Object );
protected:
	/* Octree containing all entries that could go significant. Used for server side significance */
	FSignificanceOctree mServerSideSignificanceOctree;

	/* Set of current significant entries. Used for server side significance */
	UPROPERTY()
	TSet<TObjectPtr<UObject>> mSignificantSet;

	/* Map from pawn to location used to determine the distance */
	UPROPERTY()
	TMap<TObjectPtr<APawn>, FFGPawnLocationData> mPawnToLocationMap;

	/** True if server side significance needs to be fully recalculated because new objects have been added */
	bool mServerSideSignificanceDirty{false};

	/** Accumulated delta time since last tick */
	float mAccumulatedDeltaTime{0.0f};
};


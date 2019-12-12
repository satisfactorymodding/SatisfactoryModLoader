// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGBuildGuide.generated.h"

struct FGuideLineBuildingSweepData
{
	FGuideLineBuildingSweepData( class AActor* building, float angle )
	{
		mBuilding = building;
		mAngle = angle;
	}

	class AActor* mBuilding;
	float mAngle;
};

UENUM()
enum class EGuideLineType : uint8
{
	GLT_Default			UMETA( DisplayName = "Default" ),
	GLT_ConveyorBelt	UMETA( DisplayName = "Conveyor Belt" ),
};

struct FBuildingGuideLineData
{
public:
	FBuildingGuideLineData( class UObject* referenceObject, FVector startPoint, FVector endPoint, EGuideLineType lineType = EGuideLineType::GLT_Default ) :
		mReferenceObject( referenceObject ),
		mStartPoint( startPoint ),
		mEndPoint( endPoint ),
		mGuideLineType( lineType )
	{
	}

	class UObject* mReferenceObject;
	FVector mStartPoint;
	FVector mEndPoint;
	EGuideLineType mGuideLineType;
};

UCLASS()
class FACTORYGAME_API AFGBuildGuide : public AActor
{
	GENERATED_BODY()

public:
	/** Find how many degrees pointB is from pointA's right-angles (0, 90, 180, 270). Will convert vectors to 2D space. */
	static float FindAngleBetweenBuildingCenterpoints( FVector pointA, FVector pointB, FVector rotation );

	/** Finds the angle between two points based on the rotation of vector a. */
	static float FindRotationAngleBetweenVectors( FVector a, FVector b, FVector rotation );

	/** Finds the point on originPoint's right-angled axis that the relativePoint is closest to snap to. */
	static FVector FindRelativeSnapPoint( FTransform originTransform, FVector relativePoint );

	/** Finds a snap point that aligns with guide lines. Updates the BuildingGuideLineData to new snap point. Will base all calculations in 2D space. */
	static bool FindAlignedSnapPoint( UWorld* world, class AFGHologram* hologram, FVector currentUnSnappedLocation, FVector currentRotation, TArray<FGuideLineBuildingSweepData>& sweepData, FVector& out_resultSnapPoint );

	static void UpdateGuideLines( TArray<FGuideLineBuildingSweepData> contenderBuildings, FVector hologramOrigin, FVector endPoint, class AActor* endPointActor, TMap<class UObject*, class AFGBuildGuide*>* guideLinePool );

	/** Given a guide lines pool, it will update the state of the lines based on the updateData given. If lines in the pool are absent in the update data they will be removed from the pool. */
	static void UpdateGuideLinesPool( class AActor* poolOwner, TArray<FBuildingGuideLineData> updateData, TMap<class UObject*, class AFGBuildGuide*>* guideLinePool );

	/** Checks whether there's anything obstructing the guide lines. */
	static bool IsClearPathToHologram( class UWorld* world, FVector start, FVector end, TSet<class AActor*> excludedActors, ECollisionChannel collisionChannel );

	static TArray<FGuideLineBuildingSweepData> SweepForAlignedBuildings( class AActor* actor, FVector guidelinesBase );

	static bool IsWithinRange( float value, float min, float max, bool inclusive = true );

	//static float FindAngleBetweenVectors( FVector a, FVector b );

	AFGBuildGuide();

	/** Sets the start and end points of the build guide, similar to DrawDebugLines() */
	UFUNCTION(BlueprintCallable, Category = "BuildGuides")
	void SetBuildGuideStartEnd( FVector startPoint, FVector endPoint, float meshSize = 30.f );

	/** Defines what type of build guide line this is. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BuildGuides")
	EGuideLineType mGuideLineType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UStaticMeshComponent* mMeshComponent;
	class UStaticMesh* mBuildGuideMesh;

private:

};

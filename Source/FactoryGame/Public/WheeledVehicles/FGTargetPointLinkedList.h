// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Containers/Map.h"
#include "CoreMinimal.h"
#include "FGSaveInterface.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Info.h"
#include "Math/TransformCalculus2D.h"
#include "Slate/WidgetTransform.h"
#include "UObject/NoExportTypes.h"
#include "FGTargetPointLinkedList.generated.h"

class USplineComponent;
class AFGTargetPoint;
class AFGWheeledVehicle;

/**
 * Deprecated. Kept for compatibility with legacy saves
 */
UCLASS()
class FACTORYGAME_API AFGDrivingTargetList : public AInfo, public IFGSaveInterface
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

	/** Converts this target list to a vehicle path, and destroys the actor and all the nodes */
	void ConvertLegacyTargetListToPath();

	/** Destroys this path and target points connected to it */
	void DestroyPathAndConnectedPathNodes();
public:
	/** First node in linked list */
	UPROPERTY( SaveGame )
	TObjectPtr<AFGTargetPoint> mFirst; 

	/** Last node in linked list */
	UPROPERTY( SaveGame )
	TObjectPtr<AFGTargetPoint> mLast;

	/** Vehicle type for which this path was created */
	UPROPERTY( SaveGame )
	TSubclassOf<AFGWheeledVehicle> mVehicleType;
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
	TObjectPtr<class AFGTargetPoint> mFirst;

	/** Last node in linked list */
	UPROPERTY( SaveGame )
	TObjectPtr<class AFGTargetPoint> mLast;

	/** Current node */
	UPROPERTY( SaveGame )
	TObjectPtr<class AFGTargetPoint> mCurrentTarget;
};

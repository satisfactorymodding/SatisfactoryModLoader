// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGSaveInterface.h"
#include "FGTargetPoint.generated.h"

UCLASS()
class FACTORYGAME_API AFGTargetPoint : public AActor, public IFGSaveInterface
{
	GENERATED_BODY()
public:	
	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {};
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override {}
	virtual bool NeedTransform_Implementation() override { return false; }
	virtual bool ShouldSave_Implementation() const override { return false; }
	// End IFSaveInterface

	/** Reference to the next target point ( used in linked list ) */
	UPROPERTY( SaveGame )
	TObjectPtr<AFGTargetPoint> mNext;

	/** Accumulated wait time for this node */ 
	UPROPERTY( SaveGame )
	float mWaitTime;

	/** Target speed at this node */ 
	UPROPERTY( SaveGame )
	int32 mTargetSpeed = -1;
};	

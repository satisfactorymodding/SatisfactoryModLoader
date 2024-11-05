// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGSaveInterface.h"
#include "GameFramework/Actor.h"
#include "FGSignificanceInterface.h"
#include "FGCrashSiteDebrisActor.generated.h"

class AFGCrashSiteDebris;

UCLASS()
class FACTORYGAME_API AFGCrashSiteDebrisActor : public AActor, public IFGSignificanceInterface, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGCrashSiteDebrisActor();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	// End AActor interface

	// Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	virtual float GetSignificanceRange() override { return 10000.f; }
	// End IFGSignificanceInterface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	UFUNCTION( BlueprintPure, Category = "Crash Site Debris Actor" )
	class UStaticMeshComponent* GetMeshComponent() const { return mMesh; }

public:
	// The crash site debris actor that owns this visual actor
	UPROPERTY( EditAnywhere, Category = "Crash Site Debris Actor" )
	TSoftObjectPtr<AFGCrashSiteDebris> mOwnerCrashSiteDebris;
protected:
	UPROPERTY( EditAnywhere, Category = "Crash Site Debris Actor" )
	class UStaticMeshComponent* mMesh;
};

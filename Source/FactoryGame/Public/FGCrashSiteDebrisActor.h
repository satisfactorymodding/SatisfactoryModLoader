// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGCrashSiteBaseActor.h"
#include "FGSignificanceInterface.h"
#include "FGCrashSiteDebrisActor.generated.h"

class AFGCrashSiteDebris;

UCLASS( Blueprintable )
class FACTORYGAME_API AFGCrashSiteDebrisActor : public AFGCrashSiteBaseActor, public IFGSignificanceInterface
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

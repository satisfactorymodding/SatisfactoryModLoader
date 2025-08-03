// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGDismantleInterface.h"
#include "FGCrashSiteBaseActor.generated.h"

/**
 * Base actor for all crash site actors
 */
UCLASS( NotBlueprintable )
class FACTORYGAME_API AFGCrashSiteBaseActor : public AActor, public IFGDismantleInterface, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGCrashSiteBaseActor();

	// Begin Actor interface
	virtual void BeginPlay() override;
	// End Actor interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	// Begin IFGDismantleInterface
	virtual bool CanDismantle_Implementation() const override;
	virtual void GetDismantleRefund_Implementation(TArray<FInventoryStack>& out_refund, bool noBuildCostEnabled) const override;
	virtual FVector GetRefundSpawnLocationAndArea_Implementation(const FVector& aimHitLocation, float& out_radius) const override;
	virtual void Dismantle_Implementation() override;
	virtual void StartIsLookedAtForDismantle_Implementation(AFGCharacterPlayer* byCharacter) override;
	virtual void StopIsLookedAtForDismantle_Implementation(AFGCharacterPlayer* byCharacter) override;
	virtual FText GetDismantleDisplayName_Implementation(AFGCharacterPlayer* byCharacter) const override;
	// End IFGDismantleInterface
protected:
	/** Multicast to play the dismantle effect and remove the actor */
	UFUNCTION( Reliable, NetMulticast )
	virtual void Multicast_Dismantle();

	/** Called when the dismantle effect has ended. Called locally for all players */
	virtual void OnDismantleEffectFinished();
	
protected:
	/** Name of the drop pod as visible when dismantling it */
	UPROPERTY( EditDefaultsOnly, Category = "Drop Pod" )
	FText mDisplayName;
	
	/** Index of the dismantle refunds that we rolled on BeginPlay */
	UPROPERTY( SaveGame )
	int32 mDismantleRefundsIndex{INDEX_NONE};

	/** Build effect to play on the actor when dismantling it */
	UPROPERTY( EditDefaultsOnly, Category = "Drop Pod" )
	TSoftClassPtr<class UFGMaterialEffect_Build> mDismantleBuildEffect;

	/** The speed with which the dismantle effect is played */
	UPROPERTY( EditDefaultsOnly, Category = "Drop Pod" )
	float mDismantleEffectSpeed{0.0f};
	
	/** True if we have been dismantled and should be removed after finishing the dismantle effect */
	UPROPERTY( SaveGame )
	bool mIsDismantled;

	/** Active dismantle build effect currently playing */
	UPROPERTY()
	UFGMaterialEffect_Build* mActiveDismantleEffect;
};

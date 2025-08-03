// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FGFoliageDestructionData.generated.h"

class AFGFallingTree;
class UNiagaraSystem;
class UAkAudioEvent;

/**
 * 
 */
UCLASS(BlueprintType)
class FACTORYGAME_API UFGFoliageDestructionData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY( BlueprintReadOnly ,EditDefaultsOnly, Category="Crumble")
	TObjectPtr<UNiagaraSystem> mFoliageCrumbleEffect;

	UPROPERTY( BlueprintReadOnly ,EditDefaultsOnly, Category="Crumble")
	TObjectPtr<UAkAudioEvent> mFoliageCrumbleSoundEffect;
	
	UPROPERTY( BlueprintReadOnly ,EditDefaultsOnly, Category="Crumble")
	FName mFoliageCrumbleEffectSocketName;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Crumble", AdvancedDisplay = true )
	FName mFoliageCrumbleParticleIDName = FName("Index");

	UPROPERTY( BlueprintReadOnly ,EditDefaultsOnly, Category="Crumble")
	bool bFoliageCrumbleParticleIgnoreScale = false;
	
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Leaves")
	TObjectPtr<UNiagaraSystem> mFoliageLeafSplatterEffect;
	
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Leaves", AdvancedDisplay = true )
	FName mFoliageLeafParticleIDName = FName("Index");

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Leaves")
	TObjectPtr<UAkAudioEvent> mFoliageLeafSplatterSoundEffect;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Leaves")
	FName mFoliageLeafSplatterEffectSocketName = NAME_None;

	UPROPERTY( BlueprintReadOnly ,EditDefaultsOnly, Category="Leaves")
	bool bFoliageLeafSplatterEffectIgnoreScale = false;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Falling")
	TSubclassOf<AFGFallingTree> mFallingTreeClass;
	
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Falling")
	bool bScreenShake = false;
	
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Falling")
	bool bCanConvertToFallingPhysicsActor = true;
	
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Falling")
	TObjectPtr<UNiagaraSystem> mFoliageTrunkCollisionEffect;
	
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Falling", AdvancedDisplay = true )
	FName mFoliageTrunkCollisionEffectIDName = FName("Index");
	
	/* AK event fired when the tree hits a surface.*/
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Falling", DisplayName = "Tree Hit")
	UAkAudioEvent* mTreeFallHitAKEvent = nullptr;
	
	/* AK event fired when the trees starts to fall.*/
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category="Falling",DisplayName = "Tree Fall")
	UAkAudioEvent* mTreeFallCrumbleAKEvent = nullptr;

	// Helper functions
	UFUNCTION(BlueprintCallable)
	static void SpawnFoliageDestructionEffects(UObject* WorldContext, UStaticMesh* Mesh, FTransform Transform, bool& bFailed);
	
	static void HandleTrunkCrumbleEffect(UObject* WorldContext, UStaticMesh* Mesh, const UFGFoliageDestructionData* DestructionData,const FVector& CrumbleEffectLocation, const FTransform& InstanceTransform );
	static void HandleLeafSplatterEffect(UObject* WorldContext, UStaticMesh* Mesh, const UFGFoliageDestructionData* DestructionData,const FVector& LeafEffectLocation, const FTransform& InstanceTransform );
};

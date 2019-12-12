// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "Engine/AssetUserData.h"
#include "ItemDrop.h"
#include "FGFoliageResourceUserData.generated.h"

/**
 * 
 */
UCLASS( EditInlineNew, DefaultToInstanced )
class FACTORYGAME_API UFGFoliageResourceUserData : public UAssetUserData
{
	GENERATED_BODY()
public:
	//~ Begin UObject interface
	virtual void PostLoad() override;
	//~ End UObject interface

	/** Text describing what you will get when you pickup the foliage */
	FText GetLookAtText() const;

	/**
	 * Return true if mFoliageIdentifiers contains any item that is a subclass of identifier
	 * @return true if identifier is nullptr
	 */
	bool IdentifiesWith( TSubclassOf< class UFGFoliageIdentifier > identifier ) const;

	/**
	 * Check if a mesh has the supplied identifier
	 *
	 * @param mesh - the mesh we want to check
	 * @param identifier - the identifier we want to check if the mesh has, nullptr means it has a UFGFoliageResourceUserData
	 * @return false if mesh is nullptr, true identifier is null, also if the mesh doesn't have any UFGFoliageResourceUserData
	 */
	static bool MeshHasIdentifier( UStaticMesh* mesh, TSubclassOf< class UFGFoliageIdentifier > identifier );

	// Accessors
	FORCEINLINE const TArray< FItemDropWithChance >& GetPickupItems() const{ return mPickupItems; }
	FORCEINLINE class UAkAudioEvent* GetPickupEvent() const{ return mPickupEvent; }
	FORCEINLINE class UParticleSystem* GetPickupEffect() const { return mPickupEffect; }
	FORCEINLINE class UAkAudioEvent* GetVehicleDestroyedEvent() const { return mVehicleDestroyedEvent; }
	FORCEINLINE class UParticleSystem* GetVehicleDestroyedEffect() const { return mVehicleDestroyedEffect; }
	FORCEINLINE int32 GetFXPriority() const { return mFXPriority;  }

	// Returns the first defined effect starting from most desirable, mExplosionDestroyedEffect working down to mPickupEffect
	class UParticleSystem* GetExplosionDestroyedEffect() const;

protected:
	/** Items we should gain when picking up the item, @todo: Remove BlueprintReadOnly */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TArray< FItemDropWithChance > mPickupItems;

	/** Audio event to be posted when picked up, @todo: Remove BlueprintReadOnly */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	class UAkAudioEvent* mPickupEvent;

	/** The effect to play where the pickup was, @todo: Remove BlueprintReadOnly */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	class UParticleSystem* mPickupEffect;

	/** Audio event to be posted when run over by a vehicle, @todo: Remove BlueprintReadOnly */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	class UAkAudioEvent* mVehicleDestroyedEvent;

	/** The effect to play when run over by a vehicle, @todo: Remove BlueprintReadOnly */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	class UParticleSystem* mVehicleDestroyedEffect;

	/** The effect to play when destroyed by an explosive. If one is not specified it may fall back to either the vehicle effect or pickup effect */
	UPROPERTY( EditDefaultsOnly )
	class UParticleSystem* mExplosionDestroyedEffect;

	/** Specifies priority for spawning against other effects. Must be implemented by the spawning class. ex: FGDestructiveProjectile */
	UPROPERTY( EditDefaultsOnly )
	int32 mFXPriority;

	/** What does this foliage identify itself as */
	UPROPERTY( EditDefaultsOnly )
	TArray< TSubclassOf< class UFGFoliageIdentifier > > mFoliageIdentifiers;
};

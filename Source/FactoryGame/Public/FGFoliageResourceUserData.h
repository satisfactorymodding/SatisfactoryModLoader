// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Engine/AssetUserData.h"
#include "ItemDrop.h"
#include "Materials/MaterialInstance.h"
#include "FGFoliageResourceUserData.generated.h"

class UFGFoliageDestructionData;

/**
 * 
 */
UENUM(BlueprintType)
enum EProximityEffectTypes
{
	PET_None 		UMETA(DisplayName = "None"),
	PET_Bush 		UMETA(DisplayName = "Bush(s)"),
    PET_Tree 		UMETA(DisplayName = "Tree(s)"),
    PET_Rock 		UMETA(DisplayName = "Rock(s)"),
    PET_Flower		UMETA(DisplayName = "Flower(s)"),
	PET_Mushroom	UMETA(DisplayName = "Mushroom(s)")
};

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

	UFUNCTION(BlueprintPure, Category = "Foliage")
	static EProximityEffectTypes GetProximityEffectTypeByMesh(UStaticMesh* mesh);
	
	UFUNCTION(BlueprintPure, Category = "Foliage")
	static TArray<int32> GetProximityEffectIdsByMesh(UStaticMesh* mesh);

	UFUNCTION(BlueprintPure, Category = "Foliage")
	static bool GetIsCaveTypeByMesh(UStaticMesh* mesh);

	UFUNCTION(BlueprintPure, Category = "Foliage")
	static UAkAudioEvent* GetPickupEventByMesh( UStaticMesh* mesh);
	
	UFUNCTION(BlueprintPure, Category = "Foliage")
	static UParticleSystem* GetPickupEffectByMesh( UStaticMesh* mesh);
	
	// Accessors
	FORCEINLINE const TArray< FItemDropWithChance >& GetPickupItems() const			{ return mPickupItems; }
	FORCEINLINE class UAkAudioEvent* GetPickupEvent() const							{ return mPickupEvent; }
	FORCEINLINE class UParticleSystem* GetPickupEffect() const						{ return mPickupEffect; }
	FORCEINLINE class UAkAudioEvent* GetVehicleDestroyedEvent() const				{ return mVehicleDestroyedEvent; }
	FORCEINLINE class UParticleSystem* GetVehicleDestroyedEffect() const			{ return mVehicleDestroyedEffect; }
	FORCEINLINE int32 GetFXPriority() const											{ return mFXPriority;  }
	// @NOTE DEPRECATED
	FORCEINLINE class UStaticMesh* GetPhysicsMesh() const							{ return mPhysicsMesh; }
	FORCEINLINE EProximityEffectTypes GetEffectCategory() const						{ return EffectCategory; }
	FORCEINLINE TArray<int32> GetFoliageTypeIDs() const								{ return FoliageTypeIDs; }
	FORCEINLINE bool GetIsCaveType() const											{ return bIsCaveMesh; }
	FORCEINLINE UFGFoliageDestructionData* GetFoliageDestructionData() const		{ return FoliageDestructionData; }
	FORCEINLINE int32 GetFoliageLeafDestructionIndex() const						{ return FoliageLeafParticleID; }
	FORCEINLINE int32 GetFoliageTrunkCrumbleDestructionIndex() const				{ return TrunkCrumbleParticleID; }
	FORCEINLINE FVector GetTrunkCustomPivotLocation() const							{ return TrunkPivotLocation; }
	FORCEINLINE float GetTrunkCustomRadius() const									{ return TrunkRadius; }
	FORCEINLINE FBoxSphereBounds GetSimpleCollision() const							{ return SimpleCollision; }
	FORCEINLINE float GetMaxWedgeAngle() const										{ return MaxWedgeAngle; }
	                                                                    			
	// Returns the first defined effect starting from most desirable, mExplosionDestroyedEffect working down to mPickupEffect
	class UParticleSystem* GetExplosionDestroyedEffect() const;

	// TODO @ben add comments.
	static UFGFoliageDestructionData* GetFoliageDestructionData( UStaticMesh* mesh );
	static int32 GetLeafDestructionIndex( UStaticMesh* mesh );
	static int32 GetTrunkCrumbleDestructionIndex( UStaticMesh* mesh );
	static FVector GetTrunkPivot( UStaticMesh* mesh );
	static float GetTrunkRadius( UStaticMesh* mesh );
	static UMaterialInterface* GetCapMaterialOverride(UStaticMesh* Mesh);
	
	static void GetTrunkPreciseCollision(UStaticMesh* Mesh, FBoxSphereBounds& UserDefinedBounds);
	static bool HandleUserDefinedCollision(const FBoxSphereBounds& SimpleBounds, const FTransform& InstanceTransform, const FVector& HitLocation, float HitRadius);
	
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

	/** Mesh to use when we want this object to simulate physics */
	UPROPERTY( EditDefaultsOnly )
	class UStaticMesh* mPhysicsMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Proximity")
	TEnumAsByte<EProximityEffectTypes> EffectCategory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Proximity")
	TArray<int32> FoliageTypeIDs;

	/* Is the foliage type normally used in caves? if so we know what vfx to spawn from it.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsCaveMesh = false;

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Begin tree variables
	
	/* Foliage destruction data, which sound effect to play etc. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Destruction" )
	TObjectPtr<UFGFoliageDestructionData> FoliageDestructionData = nullptr;

	/* ID used for selecting mesh on the niagara system for falling leaves,
	 * Particle is set in the Destruction data and the Parameter name too. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Destruction")
	int32 FoliageLeafParticleID = INDEX_NONE;

	/* ID used for selecting mesh on the niagara system for falling leaves,
	 * Particle is set in the Destruction data and the Parameter name too. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Destruction")
	int32 TrunkCrumbleParticleID = INDEX_NONE;

	/* Simple collision used for accurate destruction of the foliage. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Destruction")
	FBoxSphereBounds SimpleCollision;
	
	/* Trunk radius used for falling animation. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Destruction")
	float TrunkRadius = -1.f;

	/* Slice location for the cutting.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Destruction")
	FVector TrunkPivotLocation;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Destruction")
	float MaxWedgeAngle = 15.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Destruction")
	UMaterialInstance* mCapMaterialOverride = nullptr;
	
	friend class AFGFallingTree;
	// End tree variables
	////////////////////////////////////////////////////////////////////////////////////////////////
};

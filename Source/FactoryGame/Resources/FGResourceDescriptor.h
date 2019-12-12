// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGItemDescriptor.h"
#include "FGResourceDescriptor.generated.h"

/**
*
*/
UCLASS( Abstract )
class FACTORYGAME_API UFGResourceDescriptor : public UFGItemDescriptor
{
	GENERATED_BODY()
public:
	UFGResourceDescriptor();

	/** The static mesh we want the ResourceNode to use when it has this class selected */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Resource" )
	static bool CanBeHandMined( TSubclassOf< UFGResourceDescriptor > inClass );

	/** The static mesh we want the ResourceNode to use when it has this class selected */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Resource" )
	static class UStaticMesh* GetGroundMesh( TSubclassOf< UFGResourceDescriptor > inClass );

	/** The static mesh we want the Resource Deposit to use when it has this class selected */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Resource" )
	static class UStaticMesh* GetDepositMesh( TSubclassOf< UFGResourceDescriptor > inClass );

	/** If this is non-null, then we will use this material instead of the material specified in the mGroundMesh */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Resource" )
	static class UMaterialInstance* GetMeshOverrideMaterial( TSubclassOf< UFGResourceDescriptor > inClass );

	/** Returns the decal this resource use (if any) */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Resource" )
	static UMaterial* GetDecalMaterial( TSubclassOf< UFGResourceDescriptor > inClass );

	/** Returns the material this resource deposit use (if any) */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Resource" )
	static UMaterialInstance* GetDepositMaterial( TSubclassOf< UFGResourceDescriptor > inClass );

	/** If we are using a decal, then this returns how big that decal should be */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Resource" )
	static float GetDecalSize( TSubclassOf< UFGResourceDescriptor > inClass );

	//@todo This may not be the best place but break it out if there is a need for it.
	/** The color the ping should have for this material */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Resource" )
	static FLinearColor GetPingColor( TSubclassOf< UFGResourceDescriptor > inClass );

	/** A multiplier for this resource to set if it is fast or slow to pick up. 1.0 = normal */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Resource" )
	static float GetCollectSpeedMultiplier( TSubclassOf< UFGResourceDescriptor > inClass );

	/** Texture to show in the compass when this resource has been scanned and found. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Resource" )
	static class UTexture2D* GetCompasTexture( TSubclassOf< UFGResourceDescriptor > inClass );

	/** Gets particle for manual mining*/
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Resource" )
	static class UParticleSystem* GetManualMiningParticle( TSubclassOf< UFGResourceDescriptor > inClass );

	/** Gets particle for when node gets destroyed */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Resource" )
	static class UParticleSystem* GetDestroyedParticle( TSubclassOf< UFGResourceDescriptor > inClass );

	/** Gets name used in audio event for mining manually*/
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Resource" )
	static FName GetManualMiningAudioName( TSubclassOf< UFGResourceDescriptor > inClass );

	/** Gets particle for factory mining */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Resource" )
	static class UParticleSystem* GetFactoryMiningParticle( TSubclassOf< UFGResourceDescriptor > inClass );

#if WITH_EDITOR
	/** When this is changed in the editor, propagate the changes to the preview window */
	virtual void PostEditChangeProperty( struct FPropertyChangedEvent& propertyChangedEvent ) override;
#endif
	
protected:
	/** The static mesh we want the ResourceNode to use when it has this class selected */
	UPROPERTY( EditDefaultsOnly, Category = "Item|World", meta = ( EditCondition="!mUseMaterialDecal" ) )
	class UStaticMesh* mGroundMesh;

	/** The static mesh we want the Resource Deposit to use when it has this class selected */
	UPROPERTY( EditDefaultsOnly, Category = "Item|World", meta = (EditCondition = "!mUseMaterialDecal") )
	class UStaticMesh* mDepositMesh;

	/** The material this resource deposit use (if any) */
	UPROPERTY( EditDefaultsOnly, Category = "Item|World" )
	class UMaterialInstance* mDepositMaterial;

	/** If this is non-null, then we will use this material instead of the material specified in the mGroundMesh */
	UPROPERTY( EditDefaultsOnly, Category = "Item|World" )
	class UMaterialInstance* mGroundMeshMaterialOverride;

	/** The decal this resource use (if any) */
	UPROPERTY( EditDefaultsOnly, Category = "Item|World" )
	class UMaterial* mDecalMaterial;

	/** How big will the decal on the ground be (and the collision for it) if we have mUseMaterialDecal enabled */
	UPROPERTY( EditDefaultsOnly, Category="Item|World", meta = ( EditCondition = "mUseMaterialDecal" ) )
	float mDecalSize;
	
	//@todo This may not be the best place but break it out if there is a need for it.
	/** The color the ping should have for this material */
	UPROPERTY( EditDefaultsOnly, Category = "Item|Resource" )
	FLinearColor mPingColor;

	/** A multiplier for this resource to set if it is fast or slow to pick up. 1.0 = normal  */
	UPROPERTY( EditDefaultsOnly, Category = "Item|Resource" )
	float mCollectSpeedMultiplier;

	/** Texture to show in the compass when this resource has been scanned and found. */
	UPROPERTY( EditDefaultsOnly, Category = "Item|Resource" )
	UTexture2D* mCompassTexture;

	/** Particle to show when mining by hand */
	UPROPERTY( EditDefaultsOnly, Category = "Item|FX" )
	class UParticleSystem* mManualMiningParticle;

	/** Particle to show when mining with machine */
	UPROPERTY( EditDefaultsOnly, Category = "Item|FX" )
	class UParticleSystem* mFactoryMiningParticle;

	/** Particle to show when mining with machine */
	UPROPERTY( EditDefaultsOnly, Category = "Item|FX" )
	class UParticleSystem* mDestroyedParticle;

	/** name of sound to play when mining by hand */
	UPROPERTY( EditDefaultsOnly, Category = "Item|FX" )
	FName mManualMiningAudioName;
private:
};

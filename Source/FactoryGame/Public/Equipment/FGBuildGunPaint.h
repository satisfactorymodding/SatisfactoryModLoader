// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Equipment/FGBuildGun.h"
#include "ItemAmount.h"
#include "FGFactoryColoringTypes.h"
#include "FGBuildableSubsystem.h"
#include "FGConstructionMessageInterface.h"
#include "FGBuildGunPaint.generated.h"


UENUM( BlueprintType )
enum class EPaintMode : uint8
{
	EPM_Single	=	0,
	EPM_Area	=	1,
	EPM_Type	=	2
};


/**
 * Build guns customization / painting state
 */
UCLASS()
class FACTORYGAME_API UFGBuildGunStatePaint : public UFGBuildGunState
{
	GENERATED_BODY()

public:
	/** Ctor */
	UFGBuildGunStatePaint();

	/** Replication. */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	// Begin UFGBuildGunState
	virtual void BeginState_Implementation() override;
	virtual void EndState_Implementation() override;
	virtual void TickState_Implementation( float deltaTime ) override;
	virtual void PrimaryFire_Implementation() override;
	virtual void PrimaryFireRelease_Implementation() override;
	virtual void SecondaryFire_Implementation() override;
	virtual void ScrollDown_Implementation() override;
	virtual void ScrollUp_Implementation() override;
	// End UFGBuildGunState

	UFUNCTION( BlueprintCallable, Category = "BuildGunState|Dismantle" )
	void SetSingleApplicationState( bool isActive )
	{
		mIsSingleApplicationActive = isActive;
		mSingleApplicationActor = nullptr;
	}

	// Stencil Previews
	void CreateStencilProxy( AActor* selected );
	void DestroyStencilProxies( bool destroyComponents );

	UFUNCTION( Server, Unreliable )
	void Server_ExecutePrimaryFire();

	UFUNCTION( Server, Reliable )
	void Server_ExecutePaint( uint8 mode, FFactoryCustomizationData customizationData, AActor* hitActor );

	/** Start - Remove all these */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|BuildGunPaint" )
	void SetActiveCustomization( TSubclassOf< UFGFactoryCustomizationDescriptor > customizationDesc );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|BuildGunPaint" )
	void SetActiveSwatchDesc( TSubclassOf< UFGFactoryCustomizationDescriptor_Swatch > swatchDesc );
	
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|BuildGunPaint" )
	void SetActivePatternDesc( TSubclassOf< UFGFactoryCustomizationDescriptor_Pattern > patternDesc );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|BuildGunPaint" )
	void SetActiveMaterialDesc( TSubclassOf< UFGFactoryCustomizationDescriptor_Material > materialDesc);

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|BuildGunPaint" )
	void SetActiveSkinDesc( TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > skinDesc );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|BuildGunPaint" )
	void RemoveCustomization( TSubclassOf< UFGFactoryCustomizationDescriptor > customization );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|BuildGunPaint" )
	void ClearAllCustomizations();
	/** End - Remove all these*/

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|BuildGunPaint" )
	void SetActiveRecipe( TSubclassOf< UFGCustomizationRecipe > customizationRecipe );


	/** Return the currently active Color Descriptor */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|BuildGunPaint" )
	TSubclassOf< UFGFactoryCustomizationDescriptor_Swatch > GetActiveSwatchDesc() { return mActiveColorSwatch; }

	/** Return the currently active Pattern Descriptor */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|BuildGunPaint" )
	TSubclassOf< UFGFactoryCustomizationDescriptor_Pattern > GetActivePatternDesc() { return mActivePatternDesc; }

	/** Return the currently active Material Descriptor */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|BuildGunPaint" )
	TSubclassOf< UFGFactoryCustomizationDescriptor_Material > GetActiveMaterialDesc() { return mActiveMaterialDesc; }

	/** Return the currently active Skin Descriptor */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|BuildGunPaint" )
	TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > GetActiveSkinDesc() { return mActiveSkinDesc; }

	/** Is a give customization currently active? */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|BuildGunPaint" )
	bool IsCustomizationActive( TSubclassOf< UFGFactoryCustomizationDescriptor > customization );

	UFUNCTION( BlueprintPure, Category = "FactoryhGame|BuildGunPaint" )
	bool IsRecipeActive( TSubclassOf< class UFGCustomizationRecipe > inClass );

	/** Gets the current hit status for swatches */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|BuildGunPaint" )
	FORCEINLINE bool IsSwatchHitValid() const { return mHitCanApplySwatch; }

	/** Gets the current hit status for patterns */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|BuildGunPaint" )
	FORCEINLINE bool IsPatternHitValid() const { return mHitCanApplyPattern; }

	/** Gets the current hit status for materials */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|BuildGunPaint" )
	FORCEINLINE bool IsMaterialHitValid() const { return mHitCanApplyMaterial; }

	/** Returns the cost for applying a customization */
	UFUNCTION( BlueprintPure, Category = "BuildGunState|BuildGunPaint" )
	TArray< FItemAmount > GetCustomizationCost() const;

	UFUNCTION( BlueprintPure, Category = "BuildGunState|BuildGunPaint" )
	TArray< TSubclassOf< class UFGConstructDisqualifier > > GetConstructDisqualifiers() { return mConstructDisqualifiers; }

	UFUNCTION( BlueprintPure, Category = "BuildGunState|BuildGunPaint" )
	TSubclassOf< class UFGCustomizationRecipe > GetActiveRecipe() { return mActiveRecipe; }

	/** Spawns a preview actor for displaying the mesh swap that might occur when applying a material Desc. Will modify target objects material desc for preview */
	void SpawnPreviewActor( AFGBuildable* aimedAtBuildable, TSubclassOf< UFGRecipe > recipe, TSubclassOf< UFGFactoryCustomizationDescriptor_Material >& targetMaterialDesc );

	/** Spawn a preview actor for a Skin Desc*/
	void SpawnPreviewForMaterial(AFGBuildable* aimedAtBuildable, TSubclassOf< UFGFactoryCustomizationDescriptor_Material >& targetMaterialDesc );
	
	/** Sets up components for the preview actor*/
	USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName );

	//////////////////////////////////////////////////////////////////////////
	/// Blueprint Events

	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|BuildGunPaint" )
	void OnHitStatusChanged( TSubclassOf < class UFGBuildingDescriptor > hitBuildingDesc, bool validSwatch, bool validPattern, bool validMaterial );

	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|BuildGunPaint" )
	void OnSwatchDescriptorChanged( TSubclassOf< UFGFactoryCustomizationDescriptor_Swatch > newColorDesc );

	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|BuildGunPaint" )
	void OnPatternDescriptorChanged( TSubclassOf< UFGFactoryCustomizationDescriptor_Pattern > newPatternDesc );

	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|BuildGunPaint" )
	void OnMaterialDescriptorChanged( TSubclassOf< UFGFactoryCustomizationDescriptor_Material > newMaterialDesc );

	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|BuildGunPaint" )
	void OnSkinDescriptorChanged( TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > newSkinDesc );

	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|BuildGunPaint" )
	void OnPatternRotationChanged( uint8 patternOrientation );

	/** Give blueprint a chance to do effect when applying a customization */
	UFUNCTION( BlueprintImplementableEvent, Category = "BuildGunState" )
	void OnApplyCustomization( TSubclassOf< UFGFactoryCustomizationDescriptor > customizationDesc );

	/** Give blueprint a chance to do effect when a customization failed to apply (the player clicked but requirements we not met) */
	UFUNCTION( BlueprintImplementableEvent, Category = "BuildGunState" )
	void OnApplyCustomizationFailed( );

private:
	/** Duplicate component for preview actor */
	template< typename T >
	T* DuplicateComponent( USceneComponent* attachParent, T* templateComponent, const FName& componentName );

	/** Called to determine if a player has appropriate funds to place hologram */
	void ValidateCost();

	/** Call to add a construct disqualifier */
	void AddConstructDisqualifier( TSubclassOf< class UFGConstructDisqualifier > disqualifier );

	/** Aligns the pattern rotation with the forward vector of the actor. Useful to make sure patterns on foundations don't rotate depending on foundation rotation. */
	uint8 AlignPatternRotationWithActor( const AActor* actor, uint8 currentPatternRotation ) const;

protected:
	/** Material used on stencil proxies */
	UPROPERTY( EditDefaultsOnly )
	UMaterialInterface* mHoverProxyMaterial;

	/** Invisible Material Descriptor (for hiding meshes when they're hovered to for material replacement )*/
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf< UFGFactoryCustomizationDescriptor_Material > mInvisibleMaterialDescriptor;

private:
	UPROPERTY()
	TArray< TSubclassOf< class UFGConstructDisqualifier > > mConstructDisqualifiers;

	// The active color slot index. This indicates which slot we are applying. There are two special case indices used. 
	// INDEX_NONE - denotes there is no color set on the gun
	// UINT8_MAX  - denotes we are applying a custom color that doesn't belong to a slot index
	UPROPERTY()
	uint8 mActiveColorSlot;

	UPROPERTY()
	TSubclassOf< class UFGCustomizationRecipe > mActiveRecipe;

	UPROPERTY()
	TSubclassOf< UFGFactoryCustomizationDescriptor_Swatch > mActiveColorSwatch;

	UPROPERTY()
	TSubclassOf< UFGFactoryCustomizationDescriptor_Pattern > mActivePatternDesc;

	UPROPERTY()
	TSubclassOf< UFGFactoryCustomizationDescriptor_Material > mActiveMaterialDesc;

	UPROPERTY()
	TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > mActiveSkinDesc;

	UPROPERTY()
	uint8 mPatternRotation;

	// Max number of orientations, this is a little rough as we might want it per pattern. But generally we will never want more that 4
	const uint8 mNumPatternOrientations = 4;

	bool mHitCanApplySwatch;
	bool mHitCanApplyPattern;
	bool mHitCanApplyMaterial;
	bool mHitCanApplySkin;
	bool mDescHasChanged;
	bool mPatternRotationChanged;

	// Is this swatch application to be deferred
	bool mIsDeferredSwatchApply;
	FVector mDeferredHitLocation;

	// Tracking for for refire
	bool mFireIsHeld;
	float mRefireTime;
	
	// Tracking for specified selection state
	bool mIsSingleApplicationActive;

	UPROPERTY()
	TSubclassOf< AActor > mSingleApplicationActor;

	UPROPERTY()
	AActor* mCurrentCustomizationTarget;

	// Utilized by the Custom Color application so that we don't spam apply on the same building while holding down the fire key
	UPROPERTY()
	AActor* mLastAppliedActor;

	UPROPERTY()
	AActor* mPreviewActor;

	UPROPERTY( Transient )
	TMap< UStaticMesh*, UInstancedStaticMeshComponent* > mPendingPreviewMeshes;

};



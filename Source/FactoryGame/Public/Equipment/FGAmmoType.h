// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AkAudioEvent.h"
#include "FGSaveInterface.h"
#include "Engine/SkinnedAssetCommon.h"
#include "Curves/CurveFloat.h"
#include "Resources/FGItemDescriptor.h"
#include "Engine/EngineTypes.h"
#include "FGWeaponState.h"
#include "FGAmmoType.generated.h"

class AFGWeapon;
class UFGDamageType;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnAmmoFired, AActor*, SpawnedActor );

USTRUCT()
struct FACTORYGAME_API FAmmoTickFunction : public FTickFunction
{
	GENERATED_BODY()

	/** Buildable that is the target of this tick. */
	class UFGAmmoType* Target;

	/**
	 * Abstract function actually execute the tick.
	 * @param DeltaTime - frame time to advance, in seconds
	 * @param TickType - kind of tick for this frame
	 * @param CurrentThread - thread we are executing on, useful to pass along as new tasks are created
	 * @param MyCompletionGraphEvent - completion event for this task. Useful for holding the completetion of this task until certain child tasks are complete.
	 */
	virtual void ExecuteTick( float DeltaTime, ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent ) override;
	/** Abstract function to describe this tick. Used to print messages about illegal cycles in the dependency graph **/
	virtual FString DiagnosticMessage() override;
};

template<>
struct TStructOpsTypeTraits<FAmmoTickFunction> : public TStructOpsTypeTraitsBase2<FAmmoTickFunction>
{
	enum
	{
		WithCopy = false
	};
};

/**
 *  Descriptor for all types of ammunition magazines and their effects.
 */
UCLASS()
class FACTORYGAME_API UFGAmmoType : public UFGItemDescriptor, public IFGSaveInterface
{
	GENERATED_BODY()

public:
	UFGAmmoType();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	// Begin IFGSaveInterface
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface
	
	/** Mark this class as supported for networking */
	virtual bool IsSupportedForNetworking() const override;
	virtual bool CallRemoteFunction (UFunction* Function, void* Parms, struct FOutParmRec* OutParms, FFrame* Stack) override;
	virtual int32 GetFunctionCallspace (UFunction* Function, FFrame* Stack) override;

	// GetWorld function so we can access world context functions in blueprint like SpawnEmitterAtLocation
	// Begin UObject interface
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	virtual UWorld* GetWorld() const override;
	// End UObject interface

	UFUNCTION( BlueprintPure, Category = "Ammo Descriptor" )
	bool HasAuthority() const;
	
	/** Initialize the internals of the ammo type, to call first upon creation */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category= "Ammo Descriptor" )
	void InitializeAmmoType(AFGWeapon* Weapon, bool Force = false);

	/** Called on both server and client when we change to a new ammo type on the weapon. */
	UFUNCTION( BlueprintNativeEvent, Category= "Ammo Descriptor" )
	void OnAmmoTypeEjected();

	/** Called on both server and client when the weapon changes state. */
	UFUNCTION()
	void OnWeaponStateChanged( EWeaponState oldState, EWeaponState newState );

	/** Called on both server and client when the weapon starts firing the ammunition. */
	UFUNCTION( BlueprintNativeEvent, Category= "Ammo Descriptor" )
	void OnBeginFire();

	/** Called on both server and client when the weapon stops firing the ammunition. */
	UFUNCTION( BlueprintNativeEvent, Category= "Ammo Descriptor" )
	void OnEndFire();

	UFUNCTION( BlueprintCallable, Category="Ammunition" )
	void SetAmmoColor(FLinearColor color){ mAmmoColor = color; }

	UFUNCTION( BlueprintCallable, Category="Ammunition" )
	FLinearColor GetAmmoColor() const { return mAmmoColor; }

	UFUNCTION( BlueprintCallable, Category="Ammunition" )
	void SetAmmoScale(float uniformScale){mAmmoScale = uniformScale;}

	UFUNCTION( BlueprintCallable, Category="Ammunition" )
	float GetAmmoScale() const {return mAmmoScale;}
	
	/** Ticking function for the magazine object. */
	UFUNCTION( BlueprintNativeEvent, Category= "Ammo Descriptor" )
	void AmmoTick( float DeltaSeconds );
	
	UFUNCTION( BlueprintCallable, Category= "Ammo Descriptor" )
	void SetAmmoInstigator(APawn* pawn);

	UFUNCTION( BlueprintCallable, Category="Ammunition" )
	void SetFiringTransform( const FTransform& firingTransform );

	UFUNCTION( BlueprintCallable, Category="Ammunition" )
	void SetFiringDirection( const FVector& firingDirection );

	UFUNCTION( BlueprintPure, Category="Ammunition" )
	FORCEINLINE FTransform GetFiringTransform() const { return mFiringTransform; }

	UFUNCTION( BlueprintCallable, Category="Ammunition" )
	virtual void SetAmmoTarget( AActor* target ) { mAmmoTarget = target; };

	UFUNCTION( BlueprintPure, Category="Ammunition" )
	FORCEINLINE AActor* GetAmmoTarget() const { return mAmmoTarget; };

	/** Called by firing actor to trigger main behavior of the ammo type. Overriden to implement specialized behaviors */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category= "Ammo Descriptor" )
	void FireAmmunition();

	/** Called by firing actor to trigger secondary behaviors of the ammo type. Overriden to implement specialized behaviors */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category= "Ammo Descriptor" )
	void FireSecondary();

	/** Has ammo type been initialized properly and successfully? If not, I'd avoid doing anything with it */
	UFUNCTION( BlueprintPure, Category="Ammunition" )
	FORCEINLINE bool HasBeenInitialized() const { return mHasBeenInitialized; }

	UFUNCTION( BlueprintPure, Category="Ammunition")
	FORCEINLINE AFGWeapon* GetWeapon() const { return mWeapon; }

	UFUNCTION( BlueprintPure, Category="Ammunition" )
	FORCEINLINE float GetWeaponDamageMultiplier() const { return mWeaponDamageMultiplier; }

	/** Returns damage types of this ammo type*/
	UFUNCTION( BlueprintPure, Category="Ammunition" )
	FORCEINLINE TArray< UFGDamageType* > GetDamageTypesOnImpact() const { return mDamageTypesOnImpact; }

	/** Returns magazine size */
	UFUNCTION( BlueprintPure, Category="Ammunition" )
	FORCEINLINE int GetMagazineSize() const { return mMagazineSize; }

	/** Returns the Skeletal mesh used to visualize the ammunition */
	UFUNCTION( BlueprintPure, Category="Ammunition")
	FORCEINLINE USkeletalMesh* GetMagazineMesh() const { return mMagazineMesh; }

	UFUNCTION( BlueprintPure, Category="Ammunition" )
	FORCEINLINE TSubclassOf<UAnimInstance> GetMagazineAnimClass() const { return mMagazineMeshAnimClass; }

	UFUNCTION( BlueprintPure, Category="Ammunition")
	USkeletalMesh* GetMagazineMeshWithCustomMaterials();

	UFUNCTION( BlueprintPure, Category="Ammunition")
	FORCEINLINE TArray<FSkeletalMaterial> GetMagazineMaterials() const { return mMagazineMeshMaterials; }

	UFUNCTION( BlueprintPure, Category="Ammunition")
	TArray< UMaterialInstance* > GetMagazineMaterials1p() const { return mMagazineMeshMaterials1p; }

	UFUNCTION( BlueprintPure, Category="Ammunition" )
	FORCEINLINE float GetMaxAmmoEffectiveRange() const { return mMaxAmmoEffectiveRange; }

	UFUNCTION( BlueprintPure, Category="Ammunition" )
	FORCEINLINE FRuntimeFloatCurve GetAmmoDamageFalloffCurve() const { return mAmmoDamageFalloff; }

	UFUNCTION( BlueprintPure, Category = "Ammunition|FX" )
	FORCEINLINE UParticleSystem* GetMuzzleFlashVFX() const { return mMuzzleFlashVFX; }

	UFUNCTION( BlueprintPure, Category = "Ammunition|FX" )
	FORCEINLINE FVector GetMuzzleFlashScale() const { return mMuzzleFlashScale; }

	UFUNCTION( BlueprintPure, Category = "Ammunition|FX" )
	FORCEINLINE TArray<UAkAudioEvent*> GetFiringSounds() const { return mFiringSounds; }

	UFUNCTION( BlueprintPure, Category = "Ammunition|FX" )
	FORCEINLINE TArray<UAkAudioEvent*> GetFiringSounds1P() const { return mFiringSounds1P; }

	/** Returns reload time multiplier in percent (1 = 100%, 0.5 = 50% time) */
	UFUNCTION( BlueprintPure, Category="Ammunition|Modifiers" )
	FORCEINLINE float GetReloadTimeMultiplier() const { return mReloadTimeMultiplier; }

	/** Returns fire rate modifier in percent (Increasing value = faster firerate, Decreasing value = slower firerate) */
	UFUNCTION( BlueprintPure, Category="Ammunition|Modifiers" )
	FORCEINLINE float GetFireRate() const { return mFireRate; }

	UFUNCTION( BlueprintPure, Category="Ammunition|Modifiers" )
	FORCEINLINE bool GetFiringTransformIgnoresDispersion() const { return mFiringTransformIgnoresDispersion; }
	
	UFUNCTION( BlueprintPure, Category="Ammunition|Modifiers" )
	FORCEINLINE float GetDispersionFireRateMultiplier() const { return mDispersionFireRateMultiplier; }

	UFUNCTION( BlueprintPure, Category="Ammunition|Modifiers" )
	FORCEINLINE float GetDispersionPerShot() const { return mDispersionPerShot; }

	UFUNCTION( BlueprintPure, Category="Ammunition|Modifiers" )
	FORCEINLINE float GetRestingDispersion() const { return mRestingDispersion; }

	UFUNCTION( BlueprintPure, Category="Ammunition|Modifiers" )
	FORCEINLINE float GetFiringDispersion() const { return mFiringDispersion; }

	UFUNCTION( BlueprintPure, Category="Ammunition|Modifiers" )
	FORCEINLINE float GetDispersionRecoveryTime() const { return mDispersionRecoveryTime; }

	/** Called when an ammunition has been fired. Actor can be null. */
	UPROPERTY( BlueprintAssignable )
	FOnAmmoFired AmmoFiredDelegate;

private:
	void RegisterTickFunction( bool shouldRegister );

protected:
	/** Weapon owning this ammo type descriptor and most likely the firing actor */
	UPROPERTY( Replicated )
	AFGWeapon* mWeapon = nullptr;

	/** The actor responsible for dealing the damage of the weapon */
	UPROPERTY( Replicated )
	APawn* mInstigator = nullptr;

	/** The transform used for spawning the projectile. Affected by dispersion. */
	UPROPERTY( Replicated )
	FTransform mFiringTransform;

	/** The general direction towards where we're firing. Unaffected by dispersion. */
	UPROPERTY( Replicated )
	FVector mFiringDirection;

	/** Maximum amount of ammunition held by this magazine type */
    UPROPERTY( EditDefaultsOnly, Category = "Ammunition|Stats" )
    int mMagazineSize = 0;

    /** Maximum distance in cm beyond which the effective range of the weapon will be considered minimal */
    UPROPERTY( SaveGame, EditDefaultsOnly, Category="Ammunition|Stats" )
    float mMaxAmmoEffectiveRange = 5000.0f;
	
	/** Multiplicative modifier to the reload time, between 0 and the moon (1 = 100%, 0.5 = 50% time) */
	UPROPERTY( EditDefaultsOnly, Category="Ammunition|Stats", meta = (ClampMin = "0.0", UIMin = "0.0") )
	float mReloadTimeMultiplier = 1.0f;

	/** The firerate of the ammo. */
	UPROPERTY( EditDefaultsOnly, Category="Ammunition|Stats", meta = (ClampMin = "0.0", UIMin = "0") )
	float mFireRate = 1.0f;

	/** Whether or not the firing transform gets modified by dispersion. If this is set to true then the weapon will always keep the firing transform straight. */
	UPROPERTY( EditDefaultsOnly, Category="Ammunition|Stats", meta = (ClampMin = "0.0", UIMin = "0") )
	bool mFiringTransformIgnoresDispersion = false;

	/** The firerate will be scaled by this value based on the current dispersion level. (1 = 100%) */
	UPROPERTY( EditDefaultsOnly, Category="Ammunition|Stats", meta = (ClampMin = "0.0", UIMin = "0") )
	float mDispersionFireRateMultiplier = 1.0f;

	/** Weapon dispersion added on each shot (degrees) */
	UPROPERTY( EditDefaultsOnly, Category="Ammunition|Stats", meta = (ClampMin = "0.0", UIMin = "0") )
	float mDispersionPerShot = 0.0f;

	/** Resting dispersion of the weapon (degrees). This is what the dispersion starts at. */
	UPROPERTY( EditDefaultsOnly, Category="Ammunition|Stats", meta = (ClampMin = "0.0", UIMin = "0") )
	float mRestingDispersion = 0.0f;

	/** Maximum (firing) dispersion of the weapon (degrees). */
	UPROPERTY( EditDefaultsOnly, Category="Ammunition|Stats", meta = (ClampMin = "0.0", UIMin = "0") )
	float mFiringDispersion = 0.0f;

	/** The time it takes for the weapon to recover from the max dispersion. */
	UPROPERTY( EditDefaultsOnly, Category="Ammunition|Stats", meta = (ClampMin = "0.0", UIMin = "0") )
	float mDispersionRecoveryTime = 1.0f;

private:
	/** Initialization flag */
	UPROPERTY( Replicated )
	bool mHasBeenInitialized = false;

	UPROPERTY( Replicated )
	AActor* mAmmoTarget = nullptr;

	UPROPERTY( Replicated )
	float mWeaponDamageMultiplier = 1.0f;

	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	USkeletalMesh* mMagazineMesh = nullptr;
 
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	TSubclassOf<UAnimInstance> mMagazineMeshAnimClass = nullptr;

	UPROPERTY( EditDefaultsOnly, EditFixedSize, Category = "Item" )
	TArray<FSkeletalMaterial> mMagazineMeshMaterials;

	UPROPERTY( EditDefaultsOnly, Category="Item" )
	TArray<UMaterialInstance* > mMagazineMeshMaterials1p;

	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Ammunition|Damage" )
	TArray<  UFGDamageType*  > mDamageTypesOnImpact;

	/** The noise to make when we fire the weapon. */
	UPROPERTY( EditDefaultsOnly, Category = "Ammunition|Noise" )
	TSubclassOf< class UFGNoise > mFiringNoise;

	/** Horizontal axis drives the damage falloff between 0-1 (1 = max effective range).
	 * Up axis controls how much damage attenuation/amplification we get at said distance.*/
	UPROPERTY( EditDefaultsOnly, Category="Ammunition|Damage" )
	FRuntimeFloatCurve mAmmoDamageFalloff;

	UPROPERTY( EditDefaultsOnly, Category = "Ammunition|FX" )
	UParticleSystem* mMuzzleFlashVFX = nullptr;
	
	UPROPERTY( EditDefaultsOnly, meta=(AllowPreserveRatio), Category = "Ammunition|FX" )
	FVector mMuzzleFlashScale = FVector::OneVector;

	UPROPERTY( EditDefaultsOnly, Category = "Ammunition|FX" )
	TArray<UAkAudioEvent*> mFiringSounds;

	UPROPERTY( EditDefaultsOnly, Category = "Ammunition|FX" )
	TArray<UAkAudioEvent*> mFiringSounds1P;

	/** To set the color of a spawned ammo type. */
	UPROPERTY( EditDefaultsOnly, Category = "Ammunition|FX" )
	FLinearColor mAmmoColor = FLinearColor::White;

	/** To scale an ammo, mostly intended for projectile-based ammo types, but can be used by hit-scan for VFX. */
	UPROPERTY( EditDefaultsOnly, Category = "Ammunition" )
	float mAmmoScale = 1.0f;

	UPROPERTY( EditDefaultsOnly, Category = "Tick" )
	FAmmoTickFunction mAmmoTickFunction;
};

// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Resources/FGItemDescriptor.h"
#include "FGMaterialEffectComponent.generated.h"


USTRUCT( BlueprintType )
struct FACTORYGAME_API FCostIngredientEffectActorInfo
{
	GENERATED_BODY()

	/** What class is this cost of */
	UPROPERTY( BlueprintReadWrite )
	TSubclassOf< class UFGItemDescriptor > ItemClass;

	/** Delay between this and the previous cost actor spawned */
	UPROPERTY( BlueprintReadWrite )
	float SpawnDelay;

	/** Where this cost actor should travel to */
	UPROPERTY( BlueprintReadWrite )
	FVector TargetLocation;

public:
	FORCEINLINE ~FCostIngredientEffectActorInfo() = default;
};

USTRUCT()
struct FACTORYGAME_API FCachedMaterialArray
{
	GENERATED_BODY()

	UPROPERTY()
	TArray< UMaterialInterface* > MaterialInterfaces;

	// Component FName for each material interface
	UPROPERTY()
	FName MeshFName;

	UPROPERTY()
	TWeakObjectPtr<UMeshComponent> MeshComponent;

public:
	FORCEINLINE ~FCachedMaterialArray() = default;
};

/**
 * Base class for material based effects on actors.
 */
UCLASS( Abstract, Blueprintable, ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ), hidecategories = ( "Component Tick", Collision ) )
class FACTORYGAME_API UFGMaterialEffectComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UFGMaterialEffectComponent();

	// Begin AActorComponent interface
	virtual void OnUnregister() override;
	virtual void Activate( bool reset ) override;
	virtual void Deactivate() override;
	virtual void TickComponent( float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction) override;
	// End ActorComponent interface

	void Start();
	void Stop();

	/** Set the meshes to override material on, cannot be called after PreStarted. */
	UFUNCTION( BlueprintCallable )
	void SetMeshes( TArray< UMeshComponent* > meshes );

	/** Get the meshes which have the overridden material. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false )
	TArray< UMeshComponent* > GetMeshes() const { return mMeshes; };

	/** Get the bounds of the meshes. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false )
	void GetMeshesBounds( bool onlyVisible, bool onlyColliding, FVector& out_origin, FVector& out_boxExtent ) const;

	/** Set the duration for this effect [seconds]. This is not replicated. */
	UFUNCTION( BlueprintCallable )
	void SetDuration( float duration ) { mDuration = duration; }

	/** Get the duration for this effect. [seconds] */
	UFUNCTION( BlueprintPure )
	FORCEINLINE float GetDuration() const { return mDuration; }

	FORCEINLINE void SetAutoDestroy( bool autoDestroy ) { mAutoDestroy = autoDestroy; }

	/** Get the array of cached materials set when the build effect starts */
	const TArray< FCachedMaterialArray >& GetCachedMaterialArray() { return mOverrideMaterials; }

	/** Attempt to retrieve a cached material for a given component. Will return null if not set OR if the name of the actual mesh asset doesn't match that cached name*/
	UMaterialInterface* GetCachedMaterialForComponent( UMeshComponent* inComponent, int32 materialIndex );

protected:
	/** Called prior to the build effect starting and before the materials have been overridden. */
	UFUNCTION( BlueprintNativeEvent, Category = "Material Effect" )
	void PreStarted();

	/** Called when the effect has been started and the materials have been overridden. */
	UFUNCTION( BlueprintNativeEvent, Category = "Material Effect" )
	void OnStarted();

	/** Called when the effect has ended and the material overrides have been cleared. */
	UFUNCTION( BlueprintNativeEvent, Category = "Material Effect" )
	void OnEnded();

	/** Called when the effect is updated. */
	UFUNCTION( BlueprintNativeEvent, Category = "Material Effect" )
	void OnUpdate( float deltaTime );

	/** Set a scalar parameter on the effect. */
	UFUNCTION( BlueprintCallable, Category = "Material Effect Parameter" )
	void SetMaterialScalarParameterValue( FName name, float value );

private:
	void InitializeMaterials();
	void FinalizeMaterials();
	
	/** Helper to try and deduce the name of the mesh element on a given mesh component (Used to track changes to applied meshes between start and end of Material Effect) */
	void TryGetFNameFromMeshComponent( UMeshComponent* meshComp, FName& out_meshName );

public:
	/** Delegates */
	DECLARE_DELEGATE( FMaterialEffectStarted );
	DECLARE_DELEGATE( FMaterialEffectEnded );

	/** Called when material effect has finished. */
	FMaterialEffectStarted mOnStarted;

	/** Called when material effect has finished. */
	FMaterialEffectEnded mOnEnded;

protected:
	/** Meshes affected by the material effect. */
	UPROPERTY()
	TArray< UMeshComponent* > mMeshes;

	/** Material to display. */
	UPROPERTY( EditDefaultsOnly, Category = "Material Effect" )
	class UMaterialInterface* mMaterial;

	/** How long is this effect. */
	float mDuration;

	/** Automatically start playing this effect. */
	bool mAutoStart;

	/** Is this effect running */
	bool mIsStarted;

	/** Should this effect be auto destroyed on finish. */
	UPROPERTY( EditDefaultsOnly, Category = "Material Effect" )
	bool mAutoDestroy;

	/** The cached mids we apply effects to. */
	UPROPERTY( BlueprintReadOnly )
	TArray< class UMaterialInstanceDynamic* > mMids;

	/** The cached override materials present before initializing (Takes into account custom override materials on meshes)*/
	UPROPERTY()
	TArray< FCachedMaterialArray > mOverrideMaterials;

public:
	FORCEINLINE ~UFGMaterialEffectComponent() = default;
};

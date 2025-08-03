// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FGBlueprintFunctionLibrary.h"
#include "FGOutlineComponent.generated.h"

/**
 * Can be added to Static Mesh assets as User Data to allow overriding some materials on them when they are rendered in the Outline
 * Note that this does not include hologram meshes, which render in both the main pass and the custom depth pass
 */
UCLASS( EditInlineNew, DefaultToInstanced )
class FACTORYGAME_API UFGOutlineMaterialOverrideIdentifier : public UAssetUserData
{
	GENERATED_BODY()
public:
	/** The material that the filter material will be replaced with when the mesh is rendered in custom depth pass */
	UPROPERTY( EditAnywhere, Category = "Material Overrides" )
	class UMaterialInterface* DepthOverrideMaterial{nullptr};

	/** Applies material overrides to the mesh component that will be rendered in the custom depth pass for the outline component */
	UFUNCTION( BlueprintCallable, Category = "Custom Depth Material Overrides" )
	static void ApplyOutlineMaterialOverrides(class UStaticMeshComponent* meshComponent);
};

USTRUCT()
struct FActorOutlineState
{
	GENERATED_BODY()

	UPROPERTY()
	AActor* Actor = nullptr;
	
	UPROPERTY()
	TMap< FName, class UStaticMeshComponent* > OutlineProxies;
	
	UPROPERTY()
	TMap< FName, class UInstancedStaticMeshComponent* > InstancedOutlineProxies;

	UPROPERTY()
	EOutlineColor OutlineColor = EOutlineColor::OC_NONE;

	UPROPERTY()
	bool OnlyHighlightProxies = false;
};

/**
 * Component attached to the player that helps with outlining things the player is interacting with.
 */
UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGOutlineComponent final : public USceneComponent
{
	GENERATED_BODY()
public:
	UFGOutlineComponent();
	
	static UFGOutlineComponent* Get( const UWorld* world );

	/** Shows outline using actor's mesh components. Default way to show outline. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline", Meta = ( DefaultToSelf = "actorToOutline" ) )
	void ShowOutline( AActor* actorToOutline, const EOutlineColor color, bool createDefaultProxies = true, bool onlyHighlightProxies = false );

	/** Shows an outline for only a specific mesh on an actor */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline", Meta = ( DefaultToSelf = "actorToOutline" ) )
	void ShowOutlineForStaticMeshComponent( AActor* actorToOutline, UStaticMeshComponent* meshComp, const EOutlineColor color );
	
	const FActorOutlineState* GetImmutableOutlineStateForActor( const AActor* actor ) const;

	EOutlineColor GetOutlineStateColorForActor(const AActor* actor);

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline", Meta = ( DefaultToSelf = "actor" ) )
	UStaticMeshComponent* FindOrAddOutlineProxy( const AActor* actor, const FName& identifier );
	
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline", Meta = ( DefaultToSelf = "actor" ) )
	UInstancedStaticMeshComponent* FindOrAddInstancedOutlineProxy( const AActor* actor, const FName& identifier, UMeshComponent* meshComp = nullptr );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline", Meta = ( DefaultToSelf = "actor" ) )
	void RemoveOutlineProxy( const AActor* actor, const FName& identifier );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline", Meta = ( DefaultToSelf = "actor" ) )
	void RemoveInstancedOutlineProxy( const AActor* actor, const FName& identifier );

	/** Disables highlight if it is visible. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline", Meta = ( DefaultToSelf = "actor" ) )
	void HideOutline( AActor* actor );

	/** Disables highlight for a specific mesh comp if its visible. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline", Meta = ( DefaultToSelf = "actor" ) )
	void HideOutlineForStaticMeshComponent( AActor* actor, UStaticMeshComponent* meshComp );
	
protected:
	void UpdateOutlineState( const FActorOutlineState& outlineState );

	UFUNCTION()
	void BuildEffectFinished();

private:
	FActorOutlineState* GetOutlineStateForActor( const AActor* actor, UMeshComponent* meshComp = nullptr );

	UStaticMeshComponent* CreateOutlineProxy( FActorOutlineState& outlineState, const FName& identifier );
	UInstancedStaticMeshComponent* CreateInstancedOutlineProxy( FActorOutlineState& outlineState, const FName& identifier );

	static void SetupOutlineProxyComponent( const FActorOutlineState& outlineState, UStaticMeshComponent* comp );
	
	bool IsOwnedByLocalPlayer() const;

protected:	
	UPROPERTY()
	TArray< FActorOutlineState > mActorOutlineStates;

	UPROPERTY()
	TArray< FActorOutlineState > mComponentSpecifiedActorOutlineStates;
};
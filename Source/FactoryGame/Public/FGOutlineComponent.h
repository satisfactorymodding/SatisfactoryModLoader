// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FGBlueprintFunctionLibrary.h"
#include "FGOutlineComponent.generated.h"

/* Swap data for the build effect to function. */
UCLASS( EditInlineNew, DefaultToInstanced )
class FACTORYGAME_API UFGGlassIdentifier : public UAssetUserData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* DepthOverrideMaterial = nullptr;
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
	bool OnlyHighlightProxies;
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

	const FActorOutlineState* GetOutlineStateForActor( const AActor* actor ) const;

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline", Meta = ( DefaultToSelf = "actor" ) )
	UStaticMeshComponent* FindOrAddOutlineProxy( const AActor* actor, const FName& identifier );
	
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline", Meta = ( DefaultToSelf = "actor" ) )
	UInstancedStaticMeshComponent* FindOrAddInstancedOutlineProxy( const AActor* actor, const FName& identifier );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline", Meta = ( DefaultToSelf = "actor" ) )
	void RemoveOutlineProxy( const AActor* actor, const FName& identifier );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline", Meta = ( DefaultToSelf = "actor" ) )
	void RemoveInstancedOutlineProxy( const AActor* actor, const FName& identifier );

	/** Disables highlight if it is visible. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline", Meta = ( DefaultToSelf = "actor" ) )
	void HideOutline( AActor* actor );
	
protected:
	void UpdateOutlineState( const FActorOutlineState& outlineState );

	UFUNCTION()
	void BuildEffectFinished();

private:
	FActorOutlineState* GetOutlineStateForActor( const AActor* actor );

	UStaticMeshComponent* CreateOutlineProxy( FActorOutlineState& outlineState, const FName& identifier );
	UInstancedStaticMeshComponent* CreateInstancedOutlineProxy( FActorOutlineState& outlineState, const FName& identifier );

	static void SetupOutlineProxyComponent( const FActorOutlineState& outlineState, UStaticMeshComponent* comp );
	
	bool IsOwnedByLocalPlayer() const;

protected:	
	UPROPERTY()
	TArray< FActorOutlineState > mActorOutlineStates;
};

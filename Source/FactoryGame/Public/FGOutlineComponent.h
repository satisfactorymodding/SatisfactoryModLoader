// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FGBlueprintFunctionLibrary.h"
#include "FGOutlineComponent.generated.h"


/**
 * Component attached to the player that helps with outlining things the player is interacting with.
 *
 * @todo-outline [G2 2022-10-24] I did some minor cleaning up now, but this is a bit messy and could use a proper rework.
 */
UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGOutlineComponent : public USceneComponent
{
	GENERATED_BODY()
public:
	UFGOutlineComponent();

	static UFGOutlineComponent* Get( UWorld* world );

	/** Shows outline using actor's mesh components. Default way to show outline. */
	UFUNCTION(BlueprintCallable, Category = "FactoryGame|Outline")
	void ShowOutline( AActor* actorToOutline, EOutlineColor color );

	/** Shows outline using a proxy components. Should only be used if used on instanced actors where default usage fails. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline" )
	void ShowProxyOutline( class UStaticMesh* outlineMesh, const FTransform transform, EOutlineColor color );

	/** Shows outline for multiple actors at the same time. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline" )
	void ShowMultiActorOutline( TArray< AActor* > actorsToOutline, EOutlineColor color );

	/** Will change the static mesh used for proxy outlines. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline" )
	void UpdateProxyOutlineMesh( class UStaticMesh* newOutlineMesh );

	/** Updates the current proxy outline mesh's world location and rotation */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline" )
	void UpdateProxyOutlineLocationAndRotation( FVector newLocation, FRotator newRotation );

	/** Disables highlight if it is visible. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline" )
	void HideOutline();

	/** Checks if any outline is visible. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Outline" )
	FORCEINLINE bool IsOutlineVisible() const { return mActiveOutlineActor || mOutlineProxy->IsVisible() || mActiveMultiOutlineActors.Num() > 0; }

	/** Gets the current outline color. If the outline isn't visible the color will be OC_NONE. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Outline" )
	FORCEINLINE EOutlineColor GetOutlineColor() const { return mLastOutlineColor; }

protected:
	void ShowActorOutline( class AActor* actorToOutline, EOutlineColor color );
	void HideActorOutline( class AActor* actorToDisableOutlineOn );

	/** Special treatment for some unknown reason. */
	void ShowDismantlePendingMaterial( TArray< AActor* > actorPendingDismantle );
	void ShowDismantlePendingMaterial( AActor* actorPendingDismantle );
	void ShowDismantlePendingMaterialOnActor( AActor* actorPendingForDismantle );

private:
	bool IsOwnedByLocalPlayer();

protected:
	UPROPERTY()
	class UStaticMeshComponent* mOutlineProxy;
	
	UPROPERTY()
	AActor* mActiveOutlineActor;
	
	UPROPERTY()
	TArray< AActor* > mActiveMultiOutlineActors;
	
private:
	EOutlineColor mLastOutlineColor;
};
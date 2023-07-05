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
class FACTORYGAME_API UFGOutlineComponent final : public USceneComponent
{
	GENERATED_BODY()
public:
	UFGOutlineComponent();

	virtual void BeginPlay() override;
	
	static UFGOutlineComponent* Get( const UWorld* world );

	/** Shows outline using actor's mesh components. Default way to show outline. */
	UFUNCTION(BlueprintCallable, Category = "FactoryGame|Outline")
	void ShowOutline( AActor* actorToOutline, const EOutlineColor color );

	/** Shows outline using a proxy components. Should only be used if used on instanced actors where default usage fails. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline" )
	void ShowProxyOutline( class UStaticMesh* outlineMesh, const FTransform &transform, const EOutlineColor color );

	/** Shows outline for multiple actors at the same time. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline" )
	void ShowMultiActorOutline( TArray< AActor* > actorsToOutline, const EOutlineColor color );

	/** Will change the static mesh used for proxy outlines. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline" )
	void UpdateProxyOutlineMesh( class UStaticMesh* newOutlineMesh ) const;

	/** Updates the current proxy outline mesh's world location and rotation */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline" )
	void UpdateProxyOutlineLocationAndRotation( const FVector& newLocation, const FRotator& newRotation ) const;

	/** Disables highlight if it is visible. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Outline" )
	void HideOutline();

	/** Checks if any outline is visible. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Outline" )
	FORCEINLINE bool IsOutlineVisible() const { return mActiveOutlineActor || mOutlineProxy->IsVisible() || mActiveMultiOutlineActors.Num() > 0; }

	/** Gets the current outline color. If the outline isn't visible the color will be OC_NONE. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Outline" )
	FORCEINLINE EOutlineColor GetOutlineColor() const { return mLastOutlineColor; }

	void SetUpOutlineProxy();
	
protected:
	void ShowActorOutline( class AActor* actorToOutline, const EOutlineColor color ) const;
	static void HideActorOutline( const AActor* actorToDisableOutlineOn );

	/** Special treatment for some unknown reason. */
	void ShowDismantlePendingMaterial( TArray< AActor* > actorsPendingDismantle );
	void ShowDismantlePendingMaterial( AActor* actorPendingDismantle );
	void ShowDismantlePendingMaterialOnActor( AActor* actorPendingForDismantle );

private:
	bool IsOwnedByLocalPlayer() const;

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
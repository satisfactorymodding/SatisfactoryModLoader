// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "Components/SplineMeshComponent.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FGBlueprintFunctionLibrary.h"

#include "FGOutlineComponent.generated.h"

USTRUCT()
struct FCachedMaterialInterfaceArray
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<class UMaterialInterface*> MaterialInterfaces;
};

USTRUCT()
struct FCachedMeshToMaterialObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TMap<class UMeshComponent*, FCachedMaterialInterfaceArray > CachedMaterialInterfaces;
};

USTRUCT()
struct FCachedSplineMeshToMaterialObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TMap<class USplineMeshComponent*, FCachedMaterialInterfaceArray> CachedMaterialInterfaces;

	UPROPERTY()
	TArray<UMaterialInterface*> InstancedMaterialInterfaces;
};


UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGOutlineComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UFGOutlineComponent();

	static UFGOutlineComponent* Get(UWorld* world);

	/** Shows outline using actor's mesh components. Default way to show outline. */
	UFUNCTION(BlueprintCallable, Category = "Outline")
	void ShowOutline( AActor* actorToOutline, EOutlineColor color );

	/** Shows outline using a proxy components. Should only be used if used on instanced actors where default usage fails. */
	UFUNCTION( BlueprintCallable, Category = "Outline" )
	void ShowProxyOutline( class UStaticMesh* outlineMesh, const FTransform transform, EOutlineColor color );

	/** Shows outline for multiple actors at the same time. */
	UFUNCTION( BlueprintCallable, Category = "Outline" )
	void ShowMultiActorOutline( TArray<AActor*> actorsToOutline, EOutlineColor color );

	/** Will change the static mesh used for proxy outlines. */
	UFUNCTION( BlueprintCallable, Category = "Outline" )
	void UpdateProxyOutlineMesh( class UStaticMesh* newOutlineMesh );

	/** Updates the current proxy outline mesh's world location and rotation */
	UFUNCTION( BlueprintCallable, Category = "Outline" )
	void UpdateProxyOutlineLocationAndRotation( FVector newLocation, FRotator newRotation );

	/** Disables highlight if it is visible. */
	UFUNCTION( BlueprintCallable, Category = "Outline" )
	void HideOutline();

	/** Checks if any outline is visible. */
	UFUNCTION( BlueprintPure, Category = "Outline" )
	FORCEINLINE bool IsOutlineVisible() const { return mActiveOutlineActor || mOutlineProxy->IsVisible() || mActiveMultiOutlineActors.Num() > 0; }

	/** Gets the current outline color. If the outline isn't visible the color will be OC_NONE. */
	UFUNCTION( BlueprintPure, Category = "Outline" )
	FORCEINLINE EOutlineColor GetOutlineColor() const { return mLastOutlineColor; }

	/** Switches out all materials on all MeshComponents on an Actor, replaces them with the dismantle effect in FGFactorySettings, and caches them for when the actor is no longer in focus. */
	void ShowDismantlePendingMaterial( TArray<class AActor*> actorPendingDismantle );
	void ShowDismantlePendingMaterial( class AActor* actorPendingDismantle );
	void ShowDismantlePendingMaterial( class UFGSplineComponent* splineComponent );
	void ShowDismantlePendingMaterial( class UProxyInstancedStaticMeshComponent* proxyMesh );

	/** Reapplies any cached materials on actors that have been switched from ShowDismantlePendingMaterial. */
	void HideDismantlePendingMaterial();

protected:
	void ShowActorOutline( class AActor* actorToOutline, EOutlineColor color );
	void HideActorOutline( class AActor* actorToDisableOutlineOn );

	void ShowDismantlePendingMaterialOnActor( class AActor* actorPendingForDismantle );
	void HideDismantlePendingMaterialOnActor( class AActor* actorPendingForDismantle );
	
	void ShowDismantlePendingMaterialOnProxyMesh( class UProxyInstancedStaticMeshComponent* proxyMesh );
	void HideDismantlePendingMaterialOnProxyMesh( class UProxyInstancedStaticMeshComponent* proxyMesh );

	void HideDismantlePendingMaterialOnSplineComponent( class UFGSplineComponent* splineComponent );

	UPROPERTY()
	class UStaticMeshComponent* mOutlineProxy;

	UPROPERTY()
	class AActor* mActiveOutlineActor;

	UPROPERTY()
	TArray<class AActor*> mActiveMultiOutlineActors;

	UPROPERTY()
	TMap<class AActor*, FCachedMeshToMaterialObject> mCachedActorMaterials;

	UPROPERTY()
	TMap<class UFGSplineComponent*, FCachedSplineMeshToMaterialObject> mCachedSplineComponentMaterials;

	// MODDING EDIT
	//UPROPERTY()
	//TMap<class UProxyInstancedStaticMeshComponent*, FCachedMaterialInterfaceArray> mCachedProxyMeshMaterials;

private:
	bool IsOwnedByLocalPlayer();

	EOutlineColor mLastOutlineColor;
};
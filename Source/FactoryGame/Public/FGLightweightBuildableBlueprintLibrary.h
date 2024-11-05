// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGLightweightBuildableSubsystem.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FGLightweightBuildableBlueprintLibrary.generated.h"

class UFGRecipe;
class AFGBuildable;
struct FFactoryCustomizationData;

/** A blueprint function library for dealing with lightweight actors */
UCLASS()
class FACTORYGAME_API UFGLightweightBuildableBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/** Returns true if lightweight buildable reference provided is still valid */
	UFUNCTION(BlueprintPure, Category = "Lightweight Buildable")
	static bool IsLightweightValid(const FLightweightBuildableInstanceRef& instance);

	/** Returns the lightweight buildable class from the instance */
	UFUNCTION(BlueprintPure, Category = "Lightweight Buildable")
	static TSubclassOf<AFGBuildable> GetLightweightClass(const FLightweightBuildableInstanceRef& instance);

	/** Returns the lightweight buildable location */
	UFUNCTION(BlueprintPure, Category = "Lightweight Buildable")
	static FTransform GetLightweightTransform(const FLightweightBuildableInstanceRef& instance);
	
	/** Returns the recipe that the given lightweight buildable was built with */
	UFUNCTION(BlueprintPure, Category = "Lightweight Buildable")
	static TSubclassOf<UFGRecipe> GetLightweightBuiltWithRecipe(const FLightweightBuildableInstanceRef& instance);
	
	/** Resolves the lightweight buildable customization data from the instance. Returns false if the buildable no longer exists */
	UFUNCTION(BlueprintCallable, Category = "Lightweight Buildable")
	static bool ResolveLightweightCustomizationData(const FLightweightBuildableInstanceRef& instance, FFactoryCustomizationData& out_customizationData);

	/** Updates the currently applied customization data on the provided lightweight buildable, if it still exists */
	UFUNCTION(BlueprintCallable, Category = "Lightweight Buildable")
	static void UpdateLightweightCustomizationData(const FLightweightBuildableInstanceRef& instance, const FFactoryCustomizationData& customizationData);

	/** Removes the lightweight buildable */
	UFUNCTION(BlueprintCallable, Category = "Lightweight Buildable")
	static void RemoveLightweight(UPARAM(Ref) FLightweightBuildableInstanceRef& instance);

	/**
	 * Spawns a temporary buildable actor that mirrors the properties of this lightweight instance
	 * The buildable will be spawned locally and not replicated to clients, so it should not be used for networking
	 * This function is not safe to call outside of the game thread.
	 * Resulted buildable will not be saved either, and only serves as a proxy to the lightweight instance.
	 */
	UFUNCTION(BlueprintCallable, Category = "Lightweight Buildable")
	static AFGBuildable* SpawnTemporaryFromLightweight(const FLightweightBuildableInstanceRef& instance);
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Templates/SubclassOf.h"
#include "FGTestBlueprintFunctionLibrary.generated.h"

class UFGFactoryConnectionComponent;
class AFGBuildableConveyorBelt;
class AFGBuildable;
class UFGBuildableSpawnStrategy;
class UFGBlueprintDescriptor;
class UFGBuildableSpawnStrategy_Spline;

// Library containing various utilities useful for testing game content
UCLASS()
class FACTORYGAME_API UFGTestBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	// Spawns the buildable from the given class using the provided spawn strategy
	UFUNCTION( BlueprintCallable, Category = "FactoryGame | Testing", meta = ( DeterminesOutputType = "buildableClass", WorldContext = "worldContext" ) )
	static AFGBuildable* SpawnBuildableFromClass( TSubclassOf<AFGBuildable> buildableClass, const FTransform& transform, UObject* worldContext, UFGBuildableSpawnStrategy* spawnStrategy = nullptr );

	// Spawns the buildables from the given blueprint descriptor. Applies first strategy compatible with the buildable for each buildable in the blueprint.
	UFUNCTION( BlueprintCallable, Category = "FactoryGame | Testing", meta = ( WorldContext = "worldContext" ) )
	static bool SpawnBlueprintFromDescriptor( UFGBlueprintDescriptor* blueprintDescriptor, const FTransform& transform, UObject* worldContext, TArray<UFGBuildableSpawnStrategy*> spawnStrategies, TArray<AFGBuildable*>& out_buildables );

	// Spawns a uniform grid of buildables of the same type using the same spawn strategy
	UFUNCTION( BlueprintCallable, Category = "FactoryGame | Testing", meta = ( WorldContext = "worldContext" ) )
	static bool SpawnUniformGridOfBuildables( TSubclassOf<AFGBuildable> buildableClass, const FTransform& transform, int32 gridSizeX, int32 gridSizeY, UObject* worldContext, TArray<AFGBuildable*>& out_buildables, UFGBuildableSpawnStrategy* spawnStrategy = nullptr, float spacingX = -1.0f, float spacingY = -1.0f );

	// Spawns a uniform grid of the same blueprint
	UFUNCTION( BlueprintCallable, Category = "FactoryGame | Testing", meta = ( WorldContext = "worldContext" ) )
	static bool SpawnUniformGridOfBlueprints( UFGBlueprintDescriptor* blueprintDescriptor, const FTransform& transform, int32 gridSizeX, int32 gridSizeY, UObject* worldContext, TArray<AFGBuildable*>& out_buildables, TArray<UFGBuildableSpawnStrategy*> spawnStrategies, float spacingX = -1.0f, float spacingY = -1.0f );

	// Spawns a spline buildable pathing from Connection 1 to Connection 2 of a given class. This means conveyor belts, train tracks, and pipes
	UFUNCTION( BlueprintCallable, Category = "FactoryGame | Testing", meta = ( DeterminesOutputType = "buildableClass", WorldContext = "worldContext" ) )
	static AFGBuildable* SpawnSplineBuildable( TSubclassOf<AFGBuildable> buildableClass, UFGConnectionComponent* fromConnection, UFGConnectionComponent* toConnection, UFGBuildableSpawnStrategy_Spline* customSplineStrategy = nullptr );

	/**
	 * Attempts to make a connection between the provided components. The supported components are:
	 * FGPipeConnectionComponentBase, FGFactoryConnectionComponent, FGTrainPlatformConnection and FGCircuitConnectionComponent
	 * the rest of the underused or complex components (like train stations) are not handled by this function
	 *
	 * Circuit connections will not be visible and will be handled as hidden connections instead. If you want the connection to follow normal rules, spawn a FGBuildableWire and connect it manually
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame | Testing" )
	static void MakeConnectionBetweenComponents( UFGConnectionComponent* connection0, UFGConnectionComponent* connection1 );

	// Allows you to estimate the boundaries of the buildable without actually constructing it. Might be not reliable with dynamically spawned collision components (like conveyor belts and lifts)
	UFUNCTION( BlueprintPure, Category = "FactoryGame | Testing")
	static FVector EstimateBuildableBounds( const FTransform& originTransform, TSubclassOf<AFGBuildable> buildableClass );

	// Allows you to estimate the boundaries of the blueprint. Note that this will in fact load it into the blueprint world.
	UFUNCTION( BlueprintCallable, Category = "FactoryGame | Testing", meta = ( WorldContext = "worldContext" ) )
	static FVector DetermineBlueprintBounds( const FTransform& originTransform, UFGBlueprintDescriptor* blueprintDescriptor, UObject* worldContext );
};
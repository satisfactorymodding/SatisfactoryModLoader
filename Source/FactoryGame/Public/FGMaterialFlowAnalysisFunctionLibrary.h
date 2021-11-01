// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Templates/SharedPointer.h"
#include "FGMaterialFlowAnalysisFunctionLibrary.generated.h"

class UFGRecipe;

/**
 * The resulting DAG from a flow analysis.
 */
USTRUCT( BlueprintType, Category = "FactoryGame|MaterialFlow" )
struct FACTORYGAME_API FMaterialFlowGraph
{
	GENERATED_BODY()
public:
	/** @return Depth of the resulting graph. */
	int32 GetDepth() const;

	/** Get all nodes, optionally at a certain depth. */
	TArray< struct FMaterialFlowNode* > GetNodes( int32 depth = INDEX_NONE ) const;

private:
	friend class UFGMaterialFlowAnalysisFunctionLibrary;

	struct FMaterialFlowNode* CreateNodeFromRecipe( TSubclassOf< UFGRecipe > recipe, int32 depth );
	struct FMaterialFlowNode* CreateNodeFromOutput( TSubclassOf< class UFGItemDescriptor > descriptor, int32 depth );

	/** Sort nodes by depth. */
	void SortNodes();
	/** Nodes must be sorted for this to give proper results. */
	void UpdateTotals();

private:
	TArray< TSharedRef< struct FMaterialFlowNode > > Nodes;
};

/**
 * Input/output in the flow analysis.
 */
USTRUCT( BlueprintType, Category = "FactoryGame|MaterialFlow" )
struct FACTORYGAME_API FMaterialFlowConnection
{
	GENERATED_BODY();
public:
	FMaterialFlowConnection();

	/** Details about the material flow in this step. */
	UPROPERTY( BlueprintReadOnly )
	TSubclassOf< UFGItemDescriptor > Descriptor;

	/** Base count. [items/cycle] */
	UPROPERTY( BlueprintReadOnly )
	int32 Count;
	/** Base flow. [items/second] */
	UPROPERTY( BlueprintReadOnly )
	float Flow;

	/** Total count. [items/cycle] */
	UPROPERTY( BlueprintReadOnly )
	int32 TotalCount;
	/** Total flow. [items/second] */
	UPROPERTY( BlueprintReadOnly )
	float TotalFlow;
};

/**
 * Material flow node.
 */
USTRUCT( BlueprintType, Category = "FactoryGame|MaterialFlow" )
struct FACTORYGAME_API FMaterialFlowNode
{
	GENERATED_BODY();
public:
	FMaterialFlowNode();

	/** Recipe analyzed, nullptr for leaf nodes. */
	UPROPERTY( BlueprintReadOnly )
	TSubclassOf< UFGRecipe > Recipe;

	/** At which depth in the dependency tree is this item, root is 0. */
	UPROPERTY( BlueprintReadOnly )
	int32 Depth;

	/** How many producers are needed for this recipe. */
	UPROPERTY( BlueprintReadOnly )
	int32 ProducerCount;

	/** Parent flow nodes, 0 for root nodes. */
	UPROPERTY( BlueprintReadOnly )
	TArray< FMaterialFlowConnection > Outputs;

	/** Child flow nodes, 0 for leaf nodes. */
	UPROPERTY( BlueprintReadOnly )
	TArray< FMaterialFlowConnection > Inputs;
};

/**
 * Function library for material flow analysis in the factory.
 */
UCLASS()
class FACTORYGAME_API UFGMaterialFlowAnalysisFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	/** Perform a material flow analysis on the given recipe. */
	static FMaterialFlowGraph PerformMaterialFlowAnalysis( TArray< TSubclassOf< UFGRecipe > > recipes, const TArray< TSubclassOf< UFGRecipe > >& availableRecipes );

	/** Perform a material flow analysis on the given recipe. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|MaterialFlow" )
	static FMaterialFlowGraph PerformMaterialFlowAnalysis( TArray< TSubclassOf< UFGRecipe > > recipes, class AFGRecipeManager* recipeManager );

	/** Get the depth of the material flow graph. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|MaterialFlow" )
	static int32 GetGraphDepth( const FMaterialFlowGraph& graph ) { return graph.GetDepth(); }

	/** Get nodes in the material flow graph at a certain depth, -1 to get all nodes. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|MaterialFlow" )
	static TArray< FMaterialFlowNode > GetGraphNodes( const FMaterialFlowGraph& graph, int32 depth = -1 );

public:
	/** Helpers to implement the exec functions. */
	static void MaterialFlowAnalysisToLog( const TArray< FString >& recipeNames, class AFGRecipeManager* recipeManager );
	static void MaterialLookupToLog( const FString& itemName, class AFGRecipeManager* recipeManager );
};

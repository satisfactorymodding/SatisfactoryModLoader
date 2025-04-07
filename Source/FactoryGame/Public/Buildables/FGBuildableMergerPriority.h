// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Buildables/FGBuildableConveyorAttachment.h"
#include "FGBuildableMergerPriority.generated.h"

/**
 * Base class for mergers, it can have multiple inputs, but only one output.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableMergerPriority : public AFGBuildableConveyorAttachment
{
	GENERATED_BODY()
public:
	AFGBuildableMergerPriority();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor interface
	
	// Begin AFGBuildable interface
	virtual void Factory_Tick( float deltaTime ) override;
	// End AFGBuildable interface

	/** Returns the priority of the input connection at the specified index */
	UFUNCTION( BlueprintPure, Category = "Priority Merger" )
	int32 GetPriorityByInputIndex( int32 inputIndex ) const;

	/** Returns the priority set for the specified input connection. Returns INDEX_NONE if this is not a valid input on this merger */
	UFUNCTION( BlueprintPure, Category = "Priority Merger" )
	int32 GetPriorityByInputConnection( const UFGFactoryConnectionComponent* inputConnection ) const;

	/** Returns the input priorities for each input index in the merger */
	UFUNCTION( BlueprintPure, Category = "Priority Merger" )
	FORCEINLINE TArray<int32> GetInputPriorities() const { return mInputPriorities; }

	/** Returns all input connections for the priority merger */
	UFUNCTION( BlueprintPure, Category = "Priority Merger" )
	FORCEINLINE TArray<UFGFactoryConnectionComponent*> GetInputConnections() const { return mInputs; }

	/** Updates the priority for the input connection at the given index to the specified value */
	UFUNCTION( BlueprintAuthorityOnly, BlueprintCallable, Category = "Priority Merger" )
	void SetPriorityByInputIndex( int32 inputIndex, int32 newPriority );

	/** Updates the priorities for all inputs in this merger. The passed array size must match the number of inputs in this merger */
	UFUNCTION( BlueprintAuthorityOnly, BlueprintCallable, Category = "Priority Merger" )
	void SetInputPriorities( TArray<int32> newInputPriorities );

	/** Updates the priority for the given input connection to the specified value */
	UFUNCTION( BlueprintCallable, Category = "Priority Merger" )
	void SetPriorityByInputConnection( const UFGFactoryConnectionComponent* inputConnection, int32 newPriority );
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnInputPrioritiesChanged );
	
	/** Called when the priority of one or more inputs have changed */
	UPROPERTY( BlueprintAssignable, Category = "Sort" )
	FOnInputPrioritiesChanged OnInputPrioritiesChanged;
protected:
	/** Can be overriden to apply input priorities to the mesh of the buildable. By default, it will apply it through customization data's extra data */
	UFUNCTION( BlueprintNativeEvent, Category = "Priority Merger", meta = (ForceAsFunction) )
	void ApplyInputPrioritiesToMesh();
private:
	UFUNCTION()
	void OnRep_InputPriorities();

	/** Rebuilds input indices for priority groups based on the sort rules */
	void RebuildPriorityGroupInputIndices();

	/** Priority number for each input connection of the priority merger */
	UPROPERTY( ReplicatedUsing = OnRep_InputPriorities, SaveGame )
	TArray<int32> mInputPriorities;

	/** Input connection indices for each priority group */
	TArray<TArray<int32>> mInputIndicesPerPriority;

	/** Current input index for each priority group */
	UPROPERTY( SaveGame )
	TArray<int32> mCurrentInputIndices;

	/** Current input priority group index that we checked last tick. Used to make sure that we do not switch the priority if for one frame our current priority fails to deliver an item */
	UPROPERTY( SaveGame )
	int32 mCurrentInputPriorityGroupIndex;
};
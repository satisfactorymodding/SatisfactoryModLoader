// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Input/FGBoundMappingContextHandle.h"
#include "Templates/SubclassOf.h"
#include "UObject/Object.h"
#include "FGVisualizationMode.generated.h"

class UFGVisualizationModeDescriptor;
class UFGEnhancedInputComponent;
class UInputMappingContext;
class UUserWidget;
class AFGPlayerController;

/** Base class for visualization modes. Visualization modes allow visualizing various aspects of the gameplay and are local to each player */
UCLASS( Blueprintable, Abstract, Within = FGPlayerController )
class FACTORYGAME_API UFGVisualizationMode : public UObject
{
	GENERATED_BODY()
public:
	UFGVisualizationMode();

	// Begin UObject interface
	virtual UWorld* GetWorld() const override;
	// End UObject interface

	/** Returns the visualization mode descriptor that created this instance of the visualization mode */
	UFUNCTION( BlueprintPure, Category = "Visualization Mode" )
	FORCEINLINE TSubclassOf<UFGVisualizationModeDescriptor> GetVisualizationModeDescriptor() const { return mVisualizationModeDescriptor; }

	/** Called when this visualization mode is enabled */
	UFUNCTION( BlueprintNativeEvent, Category = "Visualization Mode" )
	void BeginMode();

	/** Called when this visualization mode is disabled */
	UFUNCTION( BlueprintNativeEvent, Category = "Visualization Mode" )
	void EndMode();

	/** Called each frame the visualization mode is enabled to update it */
	UFUNCTION( BlueprintNativeEvent, Category = "Visualization Mode" )
	void TickMode( float deltaTime );

	/** Allows binding input actions to the player when this visualization mode is active */
	virtual void BindInputActions( UFGEnhancedInputComponent* inputComponent );

	/** Clears the previously bound input actions */
	void ClearInputActions( UFGEnhancedInputComponent* inputComponent );

	void SetVisualizationModeDescriptor( const TSubclassOf<UFGVisualizationModeDescriptor>& visualizationModeDescriptor );
protected:
	/** Mapping context bound when this visualization mode is active */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Input" )
	TObjectPtr<UInputMappingContext> mMappingContext;

	FBoundMappingContextHandle mMappingContextHandle;

	UPROPERTY()
	TSubclassOf<UFGVisualizationModeDescriptor> mVisualizationModeDescriptor;
};

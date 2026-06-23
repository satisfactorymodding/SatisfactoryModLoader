#include "FGVisualizationMode.h"

UFGVisualizationMode::UFGVisualizationMode() : Super() {
	this->mMappingContext = nullptr;
	this->mVisualizationModeDescriptor = nullptr;
}
UWorld* UFGVisualizationMode::GetWorld() const{ return UObject::GetWorld(); }
void UFGVisualizationMode::BeginMode_Implementation(){ }
void UFGVisualizationMode::EndMode_Implementation(){ }
void UFGVisualizationMode::TickMode_Implementation(float deltaTime){ }
void UFGVisualizationMode::BindInputActions(UFGEnhancedInputComponent* inputComponent){ }
void UFGVisualizationMode::ClearInputActions(UFGEnhancedInputComponent* inputComponent){ }
void UFGVisualizationMode::SetVisualizationModeDescriptor(const TSubclassOf<UFGVisualizationModeDescriptor>& visualizationModeDescriptor){ }

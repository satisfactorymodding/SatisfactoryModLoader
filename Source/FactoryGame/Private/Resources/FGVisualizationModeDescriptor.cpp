#include "Resources/FGVisualizationModeDescriptor.h"

UFGVisualizationModeDescriptor::UFGVisualizationModeDescriptor() : Super() {
	this->mVisualizationModeClass = nullptr;
	this->mForm = EResourceForm::RF_INVALID;
}
TSubclassOf<UFGVisualizationMode> UFGVisualizationModeDescriptor::GetVisualizationModeClass(const TSubclassOf<UFGVisualizationModeDescriptor>& descriptor){ return TSubclassOf<UFGVisualizationMode>(); }

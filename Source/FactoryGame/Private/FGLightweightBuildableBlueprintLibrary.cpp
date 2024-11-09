#include "FGLightweightBuildableBlueprintLibrary.h"

bool UFGLightweightBuildableBlueprintLibrary::IsLightweightValid(const FLightweightBuildableInstanceRef& instance){ return bool(); }
TSubclassOf<AFGBuildable> UFGLightweightBuildableBlueprintLibrary::GetLightweightClass(const FLightweightBuildableInstanceRef& instance){ return TSubclassOf<AFGBuildable>(); }
FTransform UFGLightweightBuildableBlueprintLibrary::GetLightweightTransform(const FLightweightBuildableInstanceRef& instance){ return FTransform(); }
TSubclassOf<UFGRecipe> UFGLightweightBuildableBlueprintLibrary::GetLightweightBuiltWithRecipe(const FLightweightBuildableInstanceRef& instance){ return TSubclassOf<UFGRecipe>(); }
bool UFGLightweightBuildableBlueprintLibrary::ResolveLightweightCustomizationData(const FLightweightBuildableInstanceRef& instance, FFactoryCustomizationData& out_customizationData){ return bool(); }
void UFGLightweightBuildableBlueprintLibrary::UpdateLightweightCustomizationData(const FLightweightBuildableInstanceRef& instance, const FFactoryCustomizationData& customizationData){ }
void UFGLightweightBuildableBlueprintLibrary::RemoveLightweight(FLightweightBuildableInstanceRef& instance){ }
AFGBuildable* UFGLightweightBuildableBlueprintLibrary::SpawnTemporaryFromLightweight(const FLightweightBuildableInstanceRef& instance){ return nullptr; }

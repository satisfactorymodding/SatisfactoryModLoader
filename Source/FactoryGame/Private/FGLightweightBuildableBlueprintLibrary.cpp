// This file has been manually implemented by Th3Fanbus

#include "FGLightweightBuildableBlueprintLibrary.h"

bool UFGLightweightBuildableBlueprintLibrary::IsLightweightValid(const FLightweightBuildableInstanceRef& instance)
{
    return instance.IsValid();
}

TSubclassOf<AFGBuildable> UFGLightweightBuildableBlueprintLibrary::GetLightweightClass(const FLightweightBuildableInstanceRef& instance)
{
    return instance.GetBuildableClass();
}

FTransform UFGLightweightBuildableBlueprintLibrary::GetLightweightTransform(const FLightweightBuildableInstanceRef& instance)
{
    return instance.GetBuildableTransform();
}

TSubclassOf<UFGRecipe> UFGLightweightBuildableBlueprintLibrary::GetLightweightBuiltWithRecipe(const FLightweightBuildableInstanceRef& instance)
{
    return instance.GetBuiltWithRecipe();
}

bool UFGLightweightBuildableBlueprintLibrary::ResolveLightweightCustomizationData(const FLightweightBuildableInstanceRef& instance, FFactoryCustomizationData& out_customizationData)
{
    if (const FRuntimeBuildableInstanceData* InstanceData = instance.ResolveBuildableInstanceData()) {
        out_customizationData = InstanceData->CustomizationData;
        return true;
    }
    return false;
}

void UFGLightweightBuildableBlueprintLibrary::UpdateLightweightCustomizationData(const FLightweightBuildableInstanceRef& instance, const FFactoryCustomizationData& customizationData)
{
    instance.SetCustomizationData(customizationData);
}

void UFGLightweightBuildableBlueprintLibrary::RemoveLightweight(UPARAM(Ref)FLightweightBuildableInstanceRef& instance)
{
    instance.Remove();
}

AFGBuildable* UFGLightweightBuildableBlueprintLibrary::SpawnTemporaryFromLightweight(const FLightweightBuildableInstanceRef& instance)
{
    return instance.SpawnTemporaryBuildable();
}

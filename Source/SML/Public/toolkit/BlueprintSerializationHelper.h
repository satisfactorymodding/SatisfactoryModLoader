#pragma once
#include "Json.h"
#include "UObjectHierarchySerializer.h"
#include "Engine/BlueprintGeneratedClass.h"

class FBlueprintSerializationHelper {
public:
    TSharedRef<FJsonObject> WriteSimpleConstructionScript(USimpleConstructionScript* ConstructionScript, UObjectHierarchySerializer* HierarchySerializer);
};

#pragma once
#include "Object.h"
#include "JsonObject.h"
#include "EdGraph/EdGraphPin.h"

class SML_API FPropertyTypeHelper {
public:
    static FEdGraphPinType DeserializeGraphPinType(const TSharedRef<FJsonObject>& PinJson, UClass* SelfScope);
    static TSharedRef<FJsonObject> SerializeGraphPinType(const FEdGraphPinType& GraphPinType, UClass* SelfScope);
    static bool ConvertPropertyToPinType(const UProperty* Property, FEdGraphPinType& OutType);
};

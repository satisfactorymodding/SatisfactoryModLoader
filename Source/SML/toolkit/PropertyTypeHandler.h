#pragma once
#include "Object.h"
#include "JsonObject.h"
#include "EdGraph/EdGraphPin.h"

class FPropertyTypeHelper {
public:
    static FEdGraphPinType DeserializeGraphPinType(const TSharedRef<FJsonObject>& PinJson);
    static TSharedRef<FJsonObject> SerializeGraphPinType(const FEdGraphPinType& GraphPinType);
    static bool ConvertPropertyToPinType(const UProperty* Property, FEdGraphPinType& OutType);
};

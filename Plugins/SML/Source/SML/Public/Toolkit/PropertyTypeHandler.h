#pragma once
#include "UObject/Object.h"
#include "Dom/JsonObject.h"
#include "EdGraph/EdGraphPin.h"

class SML_API FPropertyTypeHelper {
public:
    static FEdGraphPinType DeserializeGraphPinType(const TSharedRef<FJsonObject>& PinJson, UClass* SelfScope);
    static TSharedRef<FJsonObject> SerializeGraphPinType(const FEdGraphPinType& GraphPinType, UClass* SelfScope);
    static bool ConvertPropertyToPinType(const FProperty* Property, FEdGraphPinType& OutType);
};

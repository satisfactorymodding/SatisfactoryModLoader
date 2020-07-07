#include "UPropertySerializer.h"
#include "TextProperty.h"

DECLARE_LOG_CATEGORY_CLASS(LogPropertySerializer, Error, Log);

void UPropertySerializer::DeserializePropertyValue(UProperty* Property, const TSharedRef<FJsonValue>& JsonValue, void* Value) {
	const UMapProperty* MapProperty = Cast<const UMapProperty>(Property);
	const USetProperty* SetProperty = Cast<const USetProperty>(Property);
	const UArrayProperty* ArrayProperty = Cast<const UArrayProperty>(Property);

	if (MapProperty) {
		UProperty* KeyProperty = MapProperty->KeyProp;
		UProperty* ValueProperty = MapProperty->ValueProp;
		FScriptMapHelper MapHelper(MapProperty, Value);
		const TArray<TSharedPtr<FJsonValue>>& PairArray = JsonValue->AsArray();

		for (int32 i = 0; i < PairArray.Num(); i++) {
			const TSharedPtr<FJsonObject>& Pair = PairArray[i]->AsObject();
			const TSharedPtr<FJsonValue>& EntryKey = Pair->Values.FindChecked(TEXT("Key"));
			const TSharedPtr<FJsonValue>& EntryValue = Pair->Values.FindChecked(TEXT("Value"));
			const int32 Index = MapHelper.AddDefaultValue_Invalid_NeedsRehash();
			uint8* PairPtr = MapHelper.GetPairPtr(Index);
			// Copy over imported key and value from temporary storage
			DeserializePropertyValue(KeyProperty, EntryKey.ToSharedRef(), PairPtr);
			DeserializePropertyValue(ValueProperty, EntryValue.ToSharedRef(), PairPtr + MapHelper.MapLayout.ValueOffset);
		}
		MapHelper.Rehash();

	} else if (SetProperty) {
		UProperty* ElementProperty = SetProperty->ElementProp;
		FScriptSetHelper SetHelper(SetProperty, Value);
		const TArray<TSharedPtr<FJsonValue>>& SetArray = JsonValue->AsArray();
		SetHelper.EmptyElements();
		uint8* TempElementStorage = static_cast<uint8*>(FMemory::Malloc(ElementProperty->ElementSize));
		ElementProperty->InitializeValue(TempElementStorage);
		
		for (int32 i = 0; i < SetArray.Num(); i++) {
			const TSharedPtr<FJsonValue>& Element = SetArray[i];
			DeserializePropertyValue(ElementProperty, Element.ToSharedRef(), TempElementStorage);
			
			const int32 NewElementIndex = SetHelper.AddDefaultValue_Invalid_NeedsRehash();
			uint8* NewElementPtr = SetHelper.GetElementPtr(NewElementIndex);

			// Copy over imported key from temporary storage
			ElementProperty->CopyCompleteValue_InContainer(NewElementPtr, TempElementStorage);
		}
		SetHelper.Rehash();

		ElementProperty->DestroyValue(TempElementStorage);
		FMemory::Free(TempElementStorage);
		
	} else if (ArrayProperty) {
		UProperty* ElementProperty = ArrayProperty->Inner;
		FScriptArrayHelper ArrayHelper(ArrayProperty, Value);
		const TArray<TSharedPtr<FJsonValue>>& SetArray = JsonValue->AsArray();
		ArrayHelper.EmptyValues();

		for (int32 i = 0; i < SetArray.Num(); i++) {
			const TSharedPtr<FJsonValue>& Element = SetArray[i];
			const uint32 AddedIndex = ArrayHelper.AddValue();
			uint8* ValuePtr = ArrayHelper.GetRawPtr(AddedIndex);
			DeserializePropertyValue(ElementProperty, Element.ToSharedRef(), ValuePtr);
		}
		
	} else if (Property->IsA<UMulticastDelegateProperty>()) {
		//Delegates should not be serialized directly
		
	} else if (Property->IsA<UDelegateProperty>()) {
		//Delegates should not be serialized directly
		
	} else if (const UInterfaceProperty* InterfaceProperty = Cast<const UInterfaceProperty>(Property)) {
		//UObject is enough to re-create value, since we known property on deserialization
		FScriptInterface* Interface = static_cast<FScriptInterface*>(Value);
		UObject* Object = ObjectHierarchySerializer->DeserializeObject((int32) JsonValue->AsNumber());
		if (Object != nullptr) {
			void* InterfacePtr = Object->GetInterfaceAddress(InterfaceProperty->InterfaceClass);
			check(InterfacePtr != nullptr);
			Interface->SetObject(Object);
			Interface->SetInterface(InterfacePtr);
		}

	} else if (const UClassProperty* ClassProperty = Cast<const UClassProperty>(Property)) {
		//For class it's enough just to have it's path name for deserialization
		const FString PathName = JsonValue->AsString();
		if (PathName != TEXT("None")) {
			UClass* ClassObject = LoadObject<UClass>(nullptr, *PathName);
			check(ClassObject != nullptr && ClassObject->IsChildOf(ClassProperty->MetaClass));
			ClassProperty->SetObjectPropertyValue(Value, ClassObject);
		}
		
	} else if (Property->IsA<USoftObjectProperty>()) {
		//For soft object reference, path is enough too for deserialization.
		const FString PathString = JsonValue->AsString();
		FSoftObjectPtr* ObjectPtr = static_cast<FSoftObjectPtr*>(Value);
		*ObjectPtr = FSoftObjectPath(PathString);

	} else if (const UObjectPropertyBase* ObjectProperty = Cast<const UObjectPropertyBase>(Property)) {
		//Need to serialize full UObject for object property
		UObject* Object = ObjectHierarchySerializer->DeserializeObject((int32) JsonValue->AsNumber());
		ObjectProperty->SetObjectPropertyValue(Value, Object);

	} else if (const UStructProperty* StructProperty = Cast<const UStructProperty>(Property)) {
		//To serialize struct, we need it's type and value pointer, because struct value doesn't contain type information
		DeserializeStruct(StructProperty->Struct, JsonValue->AsObject().ToSharedRef(), Value);

		//Primitives below, they are serialized as plain json values
	} else if (const UNumericProperty* NumberProperty = Cast<const UNumericProperty>(Property)) {
		const double NumberValue = JsonValue->AsNumber();
		if (NumberProperty->IsFloatingPoint())
			NumberProperty->SetFloatingPointPropertyValue(Value, NumberValue);
		else NumberProperty->SetIntPropertyValue(Value, static_cast<int64>(NumberValue));
		
	} else if (const UBoolProperty* BoolProperty = Cast<const UBoolProperty>(Property)) {
		const bool bBooleanValue = JsonValue->AsBool();
		BoolProperty->SetPropertyValue(Value, bBooleanValue);

	} else if (Property->IsA<UStrProperty>()) {
		const FString StringValue = JsonValue->AsString();
		*static_cast<FString*>(Value) = StringValue;

	} else if (const UEnumProperty* EnumProperty = Cast<const UEnumProperty>(Property)) {
		// K2 only supports byte enums right now - any violations should have been caught by UHT or the editor
		if (!EnumProperty->GetUnderlyingProperty()->IsA<UByteProperty>()) {
			UE_LOG(LogPropertySerializer, Fatal, TEXT("Unsupported Underlying Enum Property Found: %s"), *EnumProperty->GetUnderlyingProperty()->GetClass()->GetName());
		}
		//Prefer readable enum names in result json to raw numbers
		const FString EnumName = JsonValue->AsString();
		const int64 UnderlyingValue = EnumProperty->GetEnum()->GetValueByNameString(EnumName);
		check(UnderlyingValue != INDEX_NONE);
		*static_cast<uint8*>(Value) = static_cast<uint8>(UnderlyingValue);

	} else if (Property->IsA<UNameProperty>()) {
		//Name is perfectly representable as string
		const FString NameString = JsonValue->AsString();
		*static_cast<FName*>(Value) = *NameString;
		
	} else if (const UTextProperty* TextProperty = Cast<const UTextProperty>(Property)) {
		//For FText, standard ExportTextItem is okay to use, because it's serialization is quite complex
		const FString SerializedValue = JsonValue->AsString();
		if (!SerializedValue.IsEmpty()) {
			FTextStringHelper::ReadFromBuffer(*SerializedValue, *static_cast<FText*>(Value));
		}
	} else {
		UE_LOG(LogPropertySerializer, Fatal, TEXT("Found unsupported property type when deserializing value: %s"), *Property->GetClass()->GetName());
	}
}

TSharedRef<FJsonValue> UPropertySerializer::SerializePropertyValue(UProperty* Property, const void* Value) {
	const UMapProperty* MapProperty = Cast<const UMapProperty>(Property);
	const USetProperty* SetProperty = Cast<const USetProperty>(Property);
	const UArrayProperty* ArrayProperty = Cast<const UArrayProperty>(Property);
	
	if (MapProperty) {
		UProperty* KeyProperty = MapProperty->KeyProp;
		UProperty* ValueProperty = MapProperty->ValueProp;
		FScriptMapHelper MapHelper(MapProperty, Value);
		TArray<TSharedPtr<FJsonValue>> ResultArray;
		for (int32 i = 0; i < MapHelper.Num(); i++) {
			TSharedPtr<FJsonValue> EntryKey = SerializePropertyValue(KeyProperty, MapHelper.GetKeyPtr(i));
			TSharedPtr<FJsonValue> EntryValue = SerializePropertyValue(ValueProperty, MapHelper.GetValuePtr(i));
			TSharedRef<FJsonObject> Pair = MakeShareable(new FJsonObject());
			Pair->SetField(TEXT("Key"), EntryKey);
			Pair->SetField(TEXT("Value"), EntryValue);
			ResultArray.Add(MakeShareable(new FJsonValueObject(Pair)));
		}
		return MakeShareable(new FJsonValueArray(ResultArray));
	}
	
	if (SetProperty) {
		UProperty* ElementProperty = SetProperty->ElementProp;
		FScriptSetHelper SetHelper(SetProperty, Value);
		TArray<TSharedPtr<FJsonValue>> ResultArray;
		for (int32 i = 0; i < SetHelper.Num(); i++) {
			TSharedPtr<FJsonValue> Element = SerializePropertyValue(ElementProperty, SetHelper.GetElementPtr(i));
			ResultArray.Add(Element);
		}
		return MakeShareable(new FJsonValueArray(ResultArray));
	}
	
	if (ArrayProperty) {
		UProperty* ElementProperty = ArrayProperty->Inner;
		FScriptArrayHelper ArrayHelper(ArrayProperty, Value);
		TArray<TSharedPtr<FJsonValue>> ResultArray;
		for (int32 i = 0; i < ArrayHelper.Num(); i++) {
			TSharedPtr<FJsonValue> Element = SerializePropertyValue(ElementProperty, ArrayHelper.GetRawPtr(i));
			ResultArray.Add(Element);
		}
		return MakeShareable(new FJsonValueArray(ResultArray));
	}

	if (Property->IsA<UMulticastDelegateProperty>()) {
		//Delegates should not be serialized directly
		return MakeShareable(new FJsonValueString(TEXT("#Delegate#")));
	}
	
	if (Property->IsA<UDelegateProperty>()) {
		//Delegates should not be serialized directly
		return MakeShareable(new FJsonValueString(TEXT("#Delegate#")));
	}
	
	if (Property->IsA<UInterfaceProperty>()) {
		//UObject is enough to re-create value, since we known property on deserialization
		const FScriptInterface* Interface = reinterpret_cast<const FScriptInterface*>(Value);
		return MakeShareable(new FJsonValueNumber(ObjectHierarchySerializer->SerializeObject(Interface->GetObject())));
	}
	
	if (const UClassProperty* ClassProperty = Cast<const UClassProperty>(Property)) {
		UClass* ClassObject = Cast<UClass>(ClassProperty->GetObjectPropertyValue(Value));
		//For class it's enough just to have it's path name for deserialization
		return MakeShareable(new FJsonValueString(ClassObject->GetPathName()));
	}
	
	if (Property->IsA<USoftObjectProperty>()) {
		//For soft object reference, path is enough too for deserialization.
		const FSoftObjectPtr* ObjectPtr = reinterpret_cast<const FSoftObjectPtr*>(Value);
		return MakeShareable(new FJsonValueString(ObjectPtr->ToSoftObjectPath().ToString()));
	}

	if (const UObjectPropertyBase* ObjectProperty = Cast<const UObjectPropertyBase>(Property)) {
		//Need to serialize full UObject for object property
		UObject* ObjectPointer = ObjectProperty->GetObjectPropertyValue(Value);
		return MakeShareable(new FJsonValueNumber(ObjectHierarchySerializer->SerializeObject(ObjectPointer)));
	}

	if (const UStructProperty* StructProperty = Cast<const UStructProperty>(Property)) {
		//To serialize struct, we need it's type and value pointer, because struct value doesn't contain type information
		return MakeShareable(new FJsonValueObject(SerializeStruct(StructProperty->Struct, Value)));
	}
	
	if (const UNumericProperty* NumberProperty = Cast<const UNumericProperty>(Property)) {
		double ResultValue;
		if (NumberProperty->IsFloatingPoint())
			ResultValue = NumberProperty->GetFloatingPointPropertyValue(Value);
		else ResultValue = NumberProperty->GetSignedIntPropertyValue(Value);
		return MakeShareable(new FJsonValueNumber(ResultValue));
	}
	
	if (const UBoolProperty* BoolProperty = Cast<const UBoolProperty>(Property)) {
		const bool bBooleanValue = BoolProperty->GetPropertyValue(Value);
		return MakeShareable(new FJsonValueBoolean(bBooleanValue));
	}
	
	if (Property->IsA<UStrProperty>()) {
		const FString& StringValue = *reinterpret_cast<const FString*>(Value);
		return MakeShareable(new FJsonValueString(StringValue));
	}
	
	if (const UEnumProperty* EnumProperty = Cast<const UEnumProperty>(Property)) {
		// K2 only supports byte enums right now - any violations should have been caught by UHT or the editor
		if (!EnumProperty->GetUnderlyingProperty()->IsA<UByteProperty>()) {
			UE_LOG(LogPropertySerializer, Fatal, TEXT("Unsupported Underlying Enum Property Found: %s"), *EnumProperty->GetUnderlyingProperty()->GetClass()->GetName());
		}
		//Prefer readable enum names in result json to raw numbers
		const uint8 UnderlyingValue = *reinterpret_cast<const uint8*>(Value);
		const FString EnumName = EnumProperty->GetEnum()->GetNameByValue(UnderlyingValue).ToString();
		return MakeShareable(new FJsonValueString(EnumName));
	}
	
	if (Property->IsA<UNameProperty>()) {
		//Name is perfectly representable as string
		FName* Temp = ((FName*) Value);
		return MakeShareable(new FJsonValueString(Temp->ToString()));
	}

	if (const UTextProperty* TextProperty = Cast<const UTextProperty>(Property)) {
		FString ResultValue;
		const FText& TextValue = TextProperty->GetPropertyValue(Value);
		FTextStringHelper::WriteToBuffer(ResultValue, TextValue);
		return MakeShareable(new FJsonValueString(ResultValue));
	}
	
	UE_LOG(LogPropertySerializer, Fatal, TEXT("Found unsupported property type when serializing value: %s"), *Property->GetClass()->GetName());
	return MakeShareable(new FJsonValueString(TEXT("#ERROR#")));
}

TSharedRef<FJsonObject> UPropertySerializer::SerializeStruct(UScriptStruct* Struct, const void* Value) {
	TSharedRef<FJsonObject> Properties = MakeShareable(new FJsonObject());
	for (UProperty* Property = Struct->PropertyLink; Property; Property = Property->PropertyLinkNext) {
		if (ObjectHierarchySerializer->ShouldSerializeProperty(Property)) {
			const void* PropertyValue = Property->ContainerPtrToValuePtr<void>(Value);
			TSharedRef<FJsonValue> PropertyValueJson = SerializePropertyValue(Property, PropertyValue);
			Properties->SetField(Property->GetName(), PropertyValueJson);
		}
	}
	return Properties;
}

void UPropertySerializer::DeserializeStruct(UScriptStruct* Struct, const TSharedRef<FJsonObject>& Properties, void* OutValue) {
	for (UProperty* Property = Struct->PropertyLink; Property; Property = Property->PropertyLinkNext) {
		const FString PropertyName = Property->GetName();
		if (ObjectHierarchySerializer->ShouldSerializeProperty(Property) && Properties->HasField(PropertyName)) {
			void* PropertyValue = Property->ContainerPtrToValuePtr<void>(OutValue);
			const TSharedPtr<FJsonValue>& ValueObject = Properties->Values.FindChecked(PropertyName);
			if (ValueObject.IsValid()) {
				DeserializePropertyValue(Property, ValueObject.ToSharedRef(), PropertyValue);
			}
		}
	}
}

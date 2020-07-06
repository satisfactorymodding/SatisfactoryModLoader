#include "BlueprintLibrary.h"

#include "SML/util/Logging.h"
#include "IImageWrapperModule.h"
#include "IImageWrapper.h"

FString makeBetterPropName(FString name) {
	int32 index;
	FString temp = name;
	name.FindLastChar('_', index);
	name = name.Left(index);
	name.FindLastChar('_', index);
	name = name.Left(index);
	if (name == "")
		return temp;
	return name;
}

TSharedPtr<FJsonObject> USMLBlueprintLibrary::ConvertUStructToJsonObject(UStruct* Struct, void* ptrToStruct, bool UsePrettyName) {
	auto obj = TSharedPtr<FJsonObject>(new FJsonObject());
	for (auto prop = TFieldIterator<UProperty>(Struct); prop; ++prop) {
		if(UsePrettyName == true)
			obj->SetField(makeBetterPropName(prop->GetName()), ConvertUPropToJsonValue(*prop, prop->ContainerPtrToValuePtr<void>(ptrToStruct)));
		else
			obj->SetField(prop->GetName(), ConvertUPropToJsonValue(*prop, prop->ContainerPtrToValuePtr<void>(ptrToStruct)));
	}
	return obj;
}

void USMLBlueprintLibrary::ConvertJsonObjectToUStruct(TSharedPtr<FJsonObject> json, UStruct* Struct, void* ptrToStruct, bool UsePrettyName) {
	auto obj = TSharedPtr<FJsonObject>(new FJsonObject());
	for (auto prop = TFieldIterator<UProperty>(Struct); prop; ++prop) {
		FString FieldName;
		if (UsePrettyName == true)
			FieldName = makeBetterPropName(prop->GetName());
		else
			FieldName = prop->GetName();
		auto field = json->TryGetField(FieldName);
		if (!field.IsValid()) continue;
		ConvertJsonValueToUProperty(field, *prop, prop->ContainerPtrToValuePtr<void>(ptrToStruct));
	}
}

void USMLBlueprintLibrary::ConvertJsonValueToUProperty(TSharedPtr<FJsonValue> json, UProperty* prop, void* ptrToProp) {
	if (auto strProp = Cast<UStrProperty>(prop)) {
		strProp->SetPropertyValue(ptrToProp, json->AsString());
	} else if (auto fProp = Cast<UFloatProperty>(prop)) {
		fProp->SetPropertyValue(ptrToProp, json->AsNumber());
	} else if (auto iProp = Cast<UIntProperty>(prop)) {
		iProp->SetPropertyValue(ptrToProp, json->AsNumber());
	} else if (auto bProp = Cast<UBoolProperty>(prop)) {
		bProp->SetPropertyValue(ptrToProp, json->AsBool());
	} else if (auto eProp = Cast<UEnumProperty>(prop)) {
		UByteProperty* ByteProp = Cast<UByteProperty>(eProp->GetUnderlyingProperty());
		int64 ENumb = json->AsNumber();
		void* EnumPtr = eProp->ContainerPtrToValuePtr<void>(ptrToProp);
		ByteProp->SetIntPropertyValue(EnumPtr, ENumb);
	} else if (auto aProp = Cast<UArrayProperty>(prop)) {
		FScriptArrayHelper helper(aProp, ptrToProp);
		helper.EmptyValues();
		TArray<TSharedPtr<FJsonValue>> jsonArr = json->AsArray();
		for (int i = 0; i < jsonArr.Num(); i++) {
			int64 valueIndex = helper.AddValue();
			ConvertJsonValueToUProperty(jsonArr[i], aProp->Inner, helper.GetRawPtr(valueIndex));
		}
	} else if (auto sProp = Cast<UStructProperty>(prop)) {
		ConvertJsonObjectToUStruct(json->AsObject(), sProp->Struct, ptrToProp);
	}
}

FVersion USMLBlueprintLibrary::ParseVersionString(const FString& String) {
	return FVersion{String};
}

FString USMLBlueprintLibrary::Conv_VersionToString(const FVersion& Version) {
	return Version.String();
}

bool USMLBlueprintLibrary::IsModLoaded(const FString& ModId) {
	return SML::GetModHandler().IsModLoaded(ModId);
}

const TArray<FString>& USMLBlueprintLibrary::GetLoadedMods() {
	return SML::GetModHandler().GetLoadedMods();
}

FModInfo USMLBlueprintLibrary::GetLoadedModInfo(const FString& ModId) {
	FModHandler& ModHandler = SML::GetModHandler();
	if (!ModHandler.IsModLoaded(ModId))
		return FModInfo{};
	const FModContainer& ModContainer = ModHandler.GetLoadedMod(ModId);
	return ModContainer.ModInfo;
}

UTexture2D* LoadModIconInternal(const FString& ModId) {
	FModHandler& ModHandler = SML::GetModHandler();
	if (!ModHandler.IsModLoaded(ModId)) {
		return NULL;
	}
	const FModContainer& ModContainer = ModHandler.GetLoadedMod(ModId);
	const FString& IconPath = ModContainer.ModInfo.ModResources.ModIconPath;
	if (IconPath.IsEmpty()) {
		//Icon path not set, mod doesn't have any icon
		return NULL;
	}
	const FString* IconFileLocation = ModContainer.CustomFilePaths.Find(IconPath);
	if (!IconFileLocation) {
		//Mod has icon set, but extraction failed
		return NULL;
	}
	TArray<uint8> RawFileContents;
	SML::Logging::info(TEXT("Loading mod icon from "), **IconFileLocation);
	if (!FFileHelper::LoadFileToArray(RawFileContents, **IconFileLocation)) {
		//Failed to load image from the file
		SML::Logging::error(TEXT("Failed to load icon for mod "), *ModId, TEXT(": File read failed"));
		return NULL;
	}
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	const EImageFormat ImageFormat = ImageWrapperModule.DetectImageFormat(RawFileContents.GetData(), RawFileContents.Num());
	if (ImageFormat == EImageFormat::Invalid) {
		//Malformed image file - unknown image format
		SML::Logging::error(TEXT("Failed to load icon for mod "), *ModId, TEXT(": Unknown image format"));
		return NULL;
	}
	const TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(ImageFormat);
	if (!ImageWrapper.IsValid() || !ImageWrapper->SetCompressed(RawFileContents.GetData(), RawFileContents.Num())) {
		//Malformed image file - unexpected data format
		SML::Logging::error(TEXT("Failed to load icon for mod "), *ModId, TEXT(": Malformed image data"));
		return NULL;
	}
	const TArray<uint8>* UncompressedBGRA = NULL;
	//Data equal to EPixelFormat::PF_B8G8R8A8 used below - BGRA, 8 bits depth
	if (!ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA)) {
		//Malformed image file - decompression failed
		SML::Logging::error(TEXT("Failed to load icon for mod "), *ModId, TEXT(": Malformed image data"));
		return NULL;
	}
	//Create transient texture with size known from image wrapper
	UTexture2D* TextureObject = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), EPixelFormat::PF_B8G8R8A8);
	if (!TextureObject) {
		SML::Logging::error(TEXT("Failed to load icon for mod "), *ModId, TEXT(": Failed to allocate texture object"));
		return NULL;
	}
	//Add texture to root set so it is not garbage collected
	TextureObject->AddToRoot();
	//Lock initial mip map, copy texture data, and then unlock it
	FTexture2DMipMap& PrimaryMipMap = TextureObject->PlatformData->Mips[0];
	void* TextureDataPtr = PrimaryMipMap.BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(TextureDataPtr, UncompressedBGRA->GetData(), UncompressedBGRA->Num());
	PrimaryMipMap.BulkData.Unlock();
	//Update resources to see our changes
	TextureObject->UpdateResource(); 
	return TextureObject;
}

UTexture2D* USMLBlueprintLibrary::LoadModIconTexture(const FString& ModId, UTexture2D* FallbackIcon) {
	static TMap<FString, UTexture2D*> AlreadyLoadedIcons{};
	if (AlreadyLoadedIcons.Contains(ModId)) {
		//Icon already loaded - return cached one
		return AlreadyLoadedIcons.FindChecked(ModId);
	}
	//Icon not loaded - load one and cache it for further calls
	UTexture2D* LoadedTexture = LoadModIconInternal(ModId);
	if (LoadedTexture == NULL)
		LoadedTexture = FallbackIcon;
	AlreadyLoadedIcons.Add(ModId, LoadedTexture);
	return LoadedTexture;
}


TSharedPtr<FJsonValue> USMLBlueprintLibrary::ConvertUPropToJsonValue(UProperty* prop, void* ptrToProp) {
	if (auto strProp = Cast<UStrProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueString(strProp->GetPropertyValue(ptrToProp)));
	} else if (auto fProp = Cast<UFloatProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueNumber(fProp->GetPropertyValue(ptrToProp)));
	} else if (auto iProp = Cast<UIntProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueNumber(iProp->GetPropertyValue(ptrToProp)));
	} else if (auto bProp = Cast<UBoolProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueBoolean(bProp->GetPropertyValue(ptrToProp)));
	} else if (auto eProp = Cast<UEnumProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueNumber(eProp->GetUnderlyingProperty()->GetSignedIntPropertyValue(ptrToProp)));
	} else if (auto nProp = Cast<UNumericProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueNumber(nProp->GetUnsignedIntPropertyValue(ptrToProp)));
	} else if (auto aProp = Cast<UArrayProperty>(prop)) {
		auto& arr = aProp->GetPropertyValue(ptrToProp);
		TArray<TSharedPtr<FJsonValue>> jsonArr;
		for (int i = 0; i < arr.Num(); i++) {
			jsonArr.Add(ConvertUPropToJsonValue(aProp->Inner, (void*)((size_t)arr.GetData() + i * aProp->Inner->ElementSize)));
		}
		return TSharedPtr<FJsonValue>(new FJsonValueArray(jsonArr));
	} else if (auto sProp = Cast<UStructProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueObject(ConvertUStructToJsonObject(sProp->Struct, ptrToProp)));
	} else return TSharedPtr<FJsonValue>(new FJsonValueNull());
}

void USMLBlueprintLibrary::LogDebug(const FString& str, bool ignoreDebugMode) {
	if (ignoreDebugMode) SML::Logging::log(SML::Logging::LogType::Debug, *str);
	else SML::Logging::debug(*str);
}

void USMLBlueprintLibrary::LogInfo(const FString& str) {
	SML::Logging::info(*str);
}

void USMLBlueprintLibrary::LogWarning(const FString& str) {
	SML::Logging::warning(*str);
}

void USMLBlueprintLibrary::LogError(const FString& str) {
	SML::Logging::error(*str);
}

void USMLBlueprintLibrary::LogFatal(const FString& str) {
	SML::Logging::fatal(*str);
}

FVersion USMLBlueprintLibrary::GetSMLVersion() {
	return SML::GetModLoaderVersion();
}

FVersion USMLBlueprintLibrary::GetBootstrapperVersion() {
	return SML::GetBootstrapperVersion();
}

bool USMLBlueprintLibrary::GetDevelopmentModeEnabled() {
	return SML::GetSmlConfig().bDevelopmentMode;
}

void USMLBlueprintLibrary::InternalGetStructAsJson(UStructProperty *Structure, void* StructurePtr, FString &String, bool UsePretty) {
	TSharedPtr<FJsonObject> JsonObject = ConvertUStructToJsonObject(Structure->Struct,StructurePtr, UsePretty);
	FString write;
	TSharedRef<TJsonWriter<wchar_t, TPrettyJsonPrintPolicy<wchar_t>>> JsonWriter = TJsonWriterFactory<wchar_t, TPrettyJsonPrintPolicy<wchar_t>>::Create(&write); //Our Writer Factory
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
	String = write;
}

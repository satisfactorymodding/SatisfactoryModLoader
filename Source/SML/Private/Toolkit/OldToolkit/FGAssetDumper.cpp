#include "Toolkit/OldToolkit/FGAssetDumper.h"
#include "Toolkit/AssetTypes/AssetTypeSerializer.h"
#include "Json.h"
#include "IPlatformFilePak.h"
#include "HAL/ConsoleManager.h"
#include "toolkit/PropertyTypeHandler.h"
#include "Misc/PackageName.h"
#include "UObject/UObjectHash.h"
#include "Toolkit/PropertySerializer.h"
#include "Toolkit/AssetTypes/AssetCategory.h"
#include "UObject/Package.h"

DEFINE_LOG_CATEGORY(LogAssetDumper)

//Implementation of asset serialization context saving files in-place
//This reduces overhead of copying serialized file contents over and over
//but brings dependency on exact save procedure and workflow
class SML_API FAssetSerializationContextImpl : public FAssetSerializationContext {
	FString SerializedPrimaryAssetFilename;
	public:
        FAssetSerializationContextImpl(const FString& InFilename) : SerializedPrimaryAssetFilename(InFilename) {};

	virtual FString GetAdditionalFilePath(const FString& FilenamePostfix, const FString& FileExtension) override {
		const FString FilenameNoExtension = FPaths::ChangeExtension(SerializedPrimaryAssetFilename, TEXT(""));
		return FString::Printf(TEXT("%s%s.%s"), *FilenameNoExtension, *FilenamePostfix, *FileExtension);
	}
};

UStruct* FindNativeSuperStruct(UStruct* Struct) {
	while (!Struct->IsNative()) {
		Struct = Struct->GetSuperStruct();
	}
	check(Struct);
	return Struct;
}

void SerializeAssetObject(UPackage* AssetPackage, EAssetCategory AssetCategory) {
	//Create filename for asset saving
	FString OutPackageFilename;
	FPackageName::TryConvertLongPackageNameToFilename(AssetPackage->GetName(), OutPackageFilename, TEXT(".json"));
	FPaths::MakeStandardFilename(OutPackageFilename);

	//Remove ..\..\.. from the start to get path relative to project root
	FString ResultPath = FPaths::Combine(FPaths::RootDir(), TEXT("AssetDump"), OutPackageFilename);
	ResultPath.ReplaceInline(TEXT("/../../../"), TEXT("/"));

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	//Skip seriailizing assets if destination file already exists
	if (PlatformFile.FileExists(*ResultPath)) {
		return;
	}

	const FString AssetCategoryString = FAssetCategoryHelper::AssetCategoryToString(AssetCategory);
	UE_LOG(LogAssetDumper, Display, TEXT("Asset Category: %s (%d)"), *AssetCategoryString, AssetCategory);
	
	UAssetTypeSerializer* AssetTypeSerializer = UAssetTypeSerializer::FindSerializerForAssetCategory(AssetCategory);
	if (AssetTypeSerializer == NULL) {
		UE_LOG(LogAssetDumper, Display, TEXT("No serializer is found for this asset category"));
		return;
	}

	//Make sure we have correct directory tree
	PlatformFile.CreateDirectoryTree(*FPaths::GetPath(ResultPath));
	UE_LOG(LogAssetDumper, Display, TEXT("Saving package file to %s"), *ResultPath);

	//Create serialization context
	FAssetSerializationContextImpl AssetSerializationContext{ResultPath};

	//Create object hierarchy serializer and property serializer
	UObjectHierarchySerializer* ObjectHierarchySerializer = NewObject<UObjectHierarchySerializer>(GetTransientPackage());
	UPropertySerializer* PropertySerializer = NewObject<UPropertySerializer>(GetTransientPackage());
	ObjectHierarchySerializer->Initialize(AssetPackage, PropertySerializer);

	//Write basic information about asset in JSON object
	const TSharedPtr<FJsonObject> ResultJsonObject = MakeShareable(new FJsonObject());
	ResultJsonObject->SetStringField(TEXT("AssetCategory"), AssetCategoryString);
	ResultJsonObject->SetStringField(TEXT("PackageName"), AssetPackage->GetPathName());
	
	//Let asset type serializer write additional information and possibly create extra files
	AssetTypeSerializer->SerializeAsset(AssetPackage, ResultJsonObject, ObjectHierarchySerializer, AssetSerializationContext);

	//Append serialized object hierarchy in the end of object
	const TArray<TSharedPtr<FJsonValue>> ObjectHierarchy = ObjectHierarchySerializer->FinalizeSerialization();
	ResultJsonObject->SetArrayField(TEXT("SerializedObjectHierarchy"), ObjectHierarchy);

	//Serialize contents to string
	FString OutFileContentsString;
	const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutFileContentsString);
	FJsonSerializer::Serialize(ResultJsonObject.ToSharedRef(), Writer);

	//Save primary asset file text as json
	FFileHelper::SaveStringToFile(OutFileContentsString, *ResultPath);

	UE_LOG(LogAssetDumper, Display, TEXT("Asset dumped successfully to %s"), *ResultPath);
}

void DumpSatisfactoryAssets(EAssetCategory SelectedAssetCategory, bool bActuallyDump) {
	UE_LOG(LogAssetDumper, Display, TEXT("Dumping game assets (actually dump = %d)"), bActuallyDump);

	TSet<FString> ResultAssetList;
	FPakPlatformFile* PakPlatformFile = static_cast<FPakPlatformFile*>(FPlatformFileManager::Get().GetPlatformFile(TEXT("PakFile")));
	PakPlatformFile->IterateDirectoryRecursively(TEXT("../../../FactoryGame/Content/"), [&ResultAssetList](const TCHAR* FileName, bool IsDirectory) {
		if (!IsDirectory) {
			const FString FileNameString = FileName;
			if (FileNameString.EndsWith(TEXT(".uasset")) || FileNameString.EndsWith(TEXT(".umap"))) {
				const FString PackageName = FPackageName::FilenameToLongPackageName(FileNameString);
				ResultAssetList.Add(PackageName);
			}
		}
		return true;
	});

	TMap<EAssetCategory, int32> AssetsFoundByCategory;
	TArray<FString> AssetsFoundBySelectedCategory;
	
	for (const FString& PackageName : ResultAssetList) {
		UPackage* PackageLoaded = LoadPackage(NULL, *PackageName, LOAD_Quiet | LOAD_NoWarn);
		if (PackageLoaded == NULL) {
			//continue - must be some kind of wwise asset
			//that references raw file, or maybe configuration file
			continue;
		}
		PackageLoaded->AddToRoot();

		//Try to guess asset type in package
		EAssetCategory AssetType = FAssetCategoryHelper::DeterminePackageCategory(PackageLoaded);

		if (AssetType == EAssetCategory::EAC_Unknown) {
			UE_LOG(LogAssetDumper, Error, TEXT("Failed to determine asset type for object package %s"), *PackageLoaded->GetPathName());
			UE_LOG(LogAssetDumper, Error, TEXT("Objects inside: "));
			ForEachObjectWithOuter(PackageLoaded, [&](UObject* Object) {
				UStruct* ObjectType = Object->GetClass();
				if (ObjectType != NULL) {
					UStruct* NativeStructType = FindNativeSuperStruct(ObjectType);
					UE_LOG(LogAssetDumper, Error, TEXT("- %s (non-native type %s) (actual asset path: %s)"),
						*NativeStructType->GetPathName(), *ObjectType->GetPathName(), *Object->GetPathName());
				}
			}, false);
		}
		
		if (AssetType == SelectedAssetCategory) {
			if (SelectedAssetCategory != EAssetCategory::EAC_Unknown) {
				AssetsFoundBySelectedCategory.Add(PackageName);
			}
		}

		//Actually dump game asset if we have been requested to
		if (AssetType != EAssetCategory::EAC_Unknown && bActuallyDump &&
				(SelectedAssetCategory == EAssetCategory::EAC_Unknown || AssetType == SelectedAssetCategory)) {
			SerializeAssetObject(PackageLoaded, AssetType);
		}
		
		AssetsFoundByCategory.FindOrAdd(AssetType)++;
		PackageLoaded->RemoveFromRoot();
	}

	UEnum* AssetCategoryEnum = StaticEnum<EAssetCategory>();
	check(AssetCategoryEnum);
	UE_LOG(LogAssetDumper, Display, TEXT("Assets discovered by category: "));
	
	for (const TPair<EAssetCategory, int32>& Pair : AssetsFoundByCategory) {
		const FString FriendlyName = AssetCategoryEnum->GetNameStringByValue((int64) Pair.Key);
		check(!FriendlyName.IsEmpty());
		UE_LOG(LogAssetDumper, Display, TEXT("  %s: %d"), *FriendlyName, Pair.Value);
	}

	if (AssetsFoundBySelectedCategory.Num()) {
		const FString AssetCategoryName = AssetCategoryEnum->GetNameStringByValue((int64) SelectedAssetCategory);
		UE_LOG(LogAssetDumper, Display, TEXT("Assets found by filter category %s: "), *AssetCategoryName);
		for (const FString& PackageName : AssetsFoundBySelectedCategory) {
			UE_LOG(LogAssetDumper, Display, TEXT("    %s"), *PackageName);
		}
	}
	
	UE_LOG(LogAssetDumper, Display, TEXT("Dumping finished!"));

	UE_LOG(LogAssetDumper, Display, TEXT("Unhandled native classes: "));
	for (const FName& ClassName : UObjectHierarchySerializer::GetUnhandledNativeClasses()) {
		UE_LOG(LogAssetDumper, Display, TEXT("%s"), *ClassName.ToString());
	}
}

void DumpGameAssetConsoleCommand(const TArray<FString>& Arguments) {
	if (Arguments.Num() != 1) {
		UE_LOG(LogAssetDumper, Display, TEXT("Usage: DumpGameAsset <AssetPath>"));
		return;
	}
	const FString AssetPath = Arguments[0];
	UPackage* AssetPackage = LoadPackage(NULL, *AssetPath, LOAD_None);
	if (AssetPackage == nullptr) {
		UE_LOG(LogAssetDumper, Display, TEXT("Object with provided path is not found"));
		return;
	}
	
	//Determine asset category and search for type serializer
	const EAssetCategory AssetCategory = FAssetCategoryHelper::DeterminePackageCategory(AssetPackage);
	SerializeAssetObject(AssetPackage, AssetCategory);
}

void ExecuteDumpAllGameAssets(const TArray<FString>& Arguments) {
	UE_LOG(LogAssetDumper, Display, TEXT("Dumping all game assets..."));
	UE_LOG(LogAssetDumper, Display, TEXT("Warning! It may take noticable amount of time!"));

	EAssetCategory AssetCategory = EAssetCategory::EAC_Unknown;
	if (Arguments.Num() >= 1) {
		UEnum* AssetCategoryEnum = StaticEnum<EAssetCategory>();
		const FString EnumerationName = Arguments[0];
		const int64 AssetCategoryRaw = AssetCategoryEnum->GetValueByNameString(EnumerationName);
		if (AssetCategoryRaw == INDEX_NONE) {
			UE_LOG(LogAssetDumper, Display, TEXT("Unknown asset category: %s"), *EnumerationName);
			return;
		}
		UE_LOG(LogAssetDumper, Display, TEXT("Dumping list of assets of type %s"), *EnumerationName);
		AssetCategory = (EAssetCategory) AssetCategoryRaw;
	}
	bool bActuallyDump = false;
	if (Arguments.Num() >= 2) {
		bActuallyDump = Arguments[1].ToBool();
	}
	
	DumpSatisfactoryAssets(AssetCategory, bActuallyDump);
	UE_LOG(LogAssetDumper, Display, TEXT("Dumping game assets finished!"));
}

void FGameAssetDumper::RegisterConsoleCommands() {
	IConsoleManager& ConsoleManager = FConsoleManager::Get();
	
	FConsoleCommandWithArgsDelegate CommandDelegate;
	CommandDelegate.BindStatic(DumpGameAssetConsoleCommand);
	ConsoleManager.RegisterConsoleCommand(TEXT("DumpGameAsset"), TEXT("DumpGameAsset <AssetPath>"), CommandDelegate);

	FConsoleCommandWithArgsDelegate CommandDelegateDumpAll;
	CommandDelegateDumpAll.BindStatic(ExecuteDumpAllGameAssets);
	ConsoleManager.RegisterConsoleCommand(TEXT("DumpAllGameAssets"), TEXT("DumpAllGameAssets [AssetCategory]"), CommandDelegateDumpAll);
}

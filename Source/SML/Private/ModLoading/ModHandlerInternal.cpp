#include "ModLoading/ModHandlerInternal.h"
#include "FGInventoryComponent.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Configuration/Legacy/LegacyConfigurationHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"
#include "SatisfactoryModLoader.h"
#include "UObject/UObjectGlobals.h"
#include "Util/ZipFile/ZipFile.h"

FFileHash HashArchiveFileAttributes(FZipFile& ZipHandle, const FString& FilePath) {
	const FZipFileStat FileStat = ZipHandle.StatFile(FilePath);
	return FFileHash{FileStat.UncompressedFileSize, FileStat.ModificationTime};
}

int64 ToUnixTimestamp(const FDateTime& DateTime) {
	return (DateTime.GetTicks() - FDateTime(1970, 1, 1).GetTicks()) / ETimespan::TicksPerSecond;
}

FDateTime FromUnixTimestamp(const int64 Timestamp) {
	return FDateTime(1970, 1, 1) + FTimespan(Timestamp * ETimespan::TicksPerSecond);
}

FFileHash HashFileAttributes(const FString& Path) {
	const FFileStatData Data = FPlatformFileManager::Get().GetPlatformFile().GetStatData(*Path);
	if (!Data.bIsValid) {
		return FFileHash{0, 0};
	}
	return FFileHash{static_cast<uint64>(Data.FileSize), ToUnixTimestamp(Data.ModificationTime)};
}

FString GetExtractDirectoryForModId(const FString& ModId) {
	return FPaths::Combine(*FModHandlerHelper::GetCacheDirectory(), ModId);
}

FString FModHandlerHelper::GetModsDirectory() {
	return FPaths::RootDir() + TEXT("mods/");
}

FString FModHandlerHelper::GetCacheDirectory() {
	return FPaths::RootDir() + TEXT("cache/");
}

bool FModHandlerHelper::IsVirtualDependency(const FString& DependencyModId) {
	return DependencyModId.StartsWith(TEXT("@"));
}

void FModHandlerHelper::PopulateModSortingSet(FModSortingSet& SortingSet, const TMap<FString, FModLoadingEntry>& LoadingEntries) {
	uint64 CurrentModIndex = 0;
	
	for (const TPair<FString, FModLoadingEntry>& Pair : LoadingEntries) {
		uint64 ThisModIndex = CurrentModIndex++;
		const FString& ModReference = Pair.Key;
		//Populate sorting state with data of this mod
		SortingSet.ModIndices.Add(ModReference, ThisModIndex);
		SortingSet.ModByIndex.Add(ThisModIndex, ModReference);
		SortingSet.SortGraph.AddNode(ThisModIndex);
	}

	for (const TPair<FString, FModLoadingEntry>& Pair : LoadingEntries) {
		const FModInfo& ThisModInfo = Pair.Value.ModInfo;
		
		for (const TPair<FString, FVersionRange>& DependencyPair : ThisModInfo.Dependencies) {
			const FString& DependencyModReference = DependencyPair.Key;
			const FVersionRange& DependencyVersion = DependencyPair.Value;
			const FModLoadingEntry* LoadingEntry = LoadingEntries.Find(DependencyModReference);
			
			if (!IsVirtualDependency(DependencyModReference)) {
				if (LoadingEntry == NULL) {
					const FString Message = FString::Printf(TEXT("%s requires %s installed"), *ThisModInfo.ModReference, *DependencyModReference);
					SortingSet.MissingDependencies.Add(Message);
					
				} else if (!DependencyVersion.Matches(LoadingEntry->ModInfo.Version)) {
					const FVersion ActualVersion = LoadingEntry->ModInfo.Version;
					const FString Message = FString::Printf(TEXT("%s requires %s (%s), but installed version is %s"),
						*ThisModInfo.ModReference, *DependencyModReference, *DependencyVersion.ToString(), *ActualVersion.ToString());
					SortingSet.MissingDependencies.Add(Message);
				} else {
					const int64 DependencyIndex = SortingSet.ModIndices.FindChecked(DependencyModReference);
					const int64 ThisModIndex = SortingSet.ModIndices.FindChecked(ThisModInfo.ModReference);
					
					SortingSet.SortGraph.AddEdge(DependencyIndex, ThisModIndex);
				}
			}
		}

		for (const TPair<FString, FVersionRange>& DependencyPair : ThisModInfo.OptionalDependencies) {
			const FString& DependencyModReference = DependencyPair.Key;
			const FVersionRange& DependencyVersion = DependencyPair.Value;
			const FModLoadingEntry* LoadingEntry = LoadingEntries.Find(DependencyModReference);

			if (!IsVirtualDependency(DependencyModReference)) {
				if (LoadingEntry != NULL && DependencyVersion.Matches(LoadingEntry->ModInfo.Version)) {
					const int64 DependencyIndex = SortingSet.ModIndices.FindChecked(DependencyModReference);
					const int64 ThisModIndex = SortingSet.ModIndices.FindChecked(ThisModInfo.ModReference);
					
					SortingSet.SortGraph.AddEdge(DependencyIndex, ThisModIndex);
				}
			}
		}
	}
}

void FModHandlerHelper::FinalizeSortingResults(FModSortingSet& SortingSet, const TMap<FString, FModLoadingEntry>& LoadingEntries) {
	TArray<uint64_t> ModsToMoveInTheEnd;
	TArray<uint64_t> ModsToMoveInTheStart;
	
	for (uint64_t i = 0; i < SortingSet.SortedIndices.Num(); i++) {
		const uint64_t ModIndex = SortingSet.SortedIndices[i];
		const FString& ModReference = SortingSet.ModByIndex.FindChecked(ModIndex);
		const FModLoadingEntry& LoadingEntry = LoadingEntries.FindChecked(ModReference);
		const TMap<FString, FVersionRange>& Dependencies = LoadingEntry.ModInfo.Dependencies;
		if (Dependencies.Contains(TEXT("@ORDER:LAST"))) {
			ModsToMoveInTheEnd.Add(ModIndex);
		}
		if (Dependencies.Contains(TEXT("@ORDER:FIRST"))) {
			ModsToMoveInTheStart.Add(ModIndex);
		}
	}

	for (uint64_t ModIndex : ModsToMoveInTheStart) {
		SortingSet.SortedIndices.Remove(ModIndex);
		SortingSet.SortedIndices.Insert(ModIndex, 0);
	}
	for (uint64_t ModIndex : ModsToMoveInTheEnd) {
		SortingSet.SortedIndices.Remove(ModIndex);
		SortingSet.SortedIndices.Add(ModIndex);
	}
}

FModLoadingEntry FModHandlerHelper::CreateSMLLoadingEntry() {
	FModInfo SMLModInfo = FModInfo::CreateDummyInfo(TEXT("SML"));
	
	SMLModInfo.Name = TEXT("Satisfactory Mod Loader");
	SMLModInfo.Version = FSatisfactoryModLoader::GetModLoaderVersion();
	SMLModInfo.Description = TEXT("Mod Loading and Compatibility Layer for Satisfactory");

	const FVersionRange MinimumRemoteVersion = FVersionRange::CreateRangeWithMinVersion(SMLModInfo.Version);
	SMLModInfo.RemoteVersion = FModRemoteVersion{MinimumRemoteVersion, false};
	
	SMLModInfo.Authors = {
		TEXT("Archengius"),
		TEXT("Brabb3l"),
		TEXT("Mircea"),
		TEXT("Nog"),
		TEXT("Panakotta00"),
		TEXT("SuperCoder79"),
		TEXT("Vilsol")
	};

	const FString SMLPakFilePath = FPaths::RootDir() + TEXT("loaders/SML.pak");
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.FileExists(*SMLPakFilePath)) {
		UE_LOG(LogModLoading, Fatal, TEXT("SML.pak not found at %s. This installation is corrupted, please re-install."), *SMLPakFilePath);
	}
	
	FModLoadingEntry ModLoadingEntry{};
	ModLoadingEntry.ModInfo = SMLModInfo;
	ModLoadingEntry.PakFiles.Add(FModPakFileEntry{SMLPakFilePath, 100});
	return ModLoadingEntry;
}

FModLoadingEntry FModHandlerHelper::CreateFactoryGameLoadingEntry() {
	const FEngineVersion& CurrentEngineVersion = FEngineVersion::Current();
	
	FModInfo FactoryGameModInfo = FModInfo::CreateDummyInfo(TEXT("FactoryGame"));
	FactoryGameModInfo.Name = TEXT("Satisfactory");
	FactoryGameModInfo.Version = FVersion(CurrentEngineVersion.GetChangelist(), 0, 0);
	FactoryGameModInfo.RemoteVersion.bAcceptAnyRemoteVersion = true;
	FactoryGameModInfo.Authors = {TEXT("Coffee Stain Studios")};
	return FModLoadingEntry{FactoryGameModInfo};
}

template<typename T>
UClass* LoadInitializerClass(const FString& ModReference, const FString& InitializerType) {
	//Do not emit any warnings about missing assets, because not all mods have all initializers
	const uint32 LoadFlags = LOAD_NoWarn | LOAD_Quiet;

	const FString InitBPClassPath = FString::Printf(TEXT("/Game/%s/%s.%s_C"), *ModReference, *InitializerType, *InitializerType);
	const FString InitNativeClassPath = FString::Printf(TEXT("/Script/%s.%s%s"), *ModReference, *InitializerType, *ModReference);

	//First, try class inside of the blueprint mod package
	UClass* LoadedClass = LoadClass<T>(NULL, *InitBPClassPath, NULL, LoadFlags);
	if (LoadedClass == NULL) {
		//Otherwise fallback to native package
		LoadedClass = LoadClass<T>(NULL, *InitNativeClassPath, NULL, LoadFlags);
	}
	return LoadedClass;
}

FModPakLoadEntry FModHandlerHelper::DiscoverModInitializers(const FString& ModReference) {
	UClass* InitGameInstanceClass = LoadInitializerClass<UGameInstanceModule>(ModReference, TEXT("InitGameInstance"));
	UClass* InitGameWorldClass = LoadInitializerClass<UWorldModule>(ModReference, TEXT("InitGameWorld"));
	UClass* InitMenuWorldClass = LoadInitializerClass<UWorldModule>(ModReference, TEXT("InitMenuWorld"));

	FModPakLoadEntry LoadEntry{ModReference};

	if (InitGameInstanceClass != NULL) {
		InitGameInstanceClass->AddToRoot();
		LoadEntry.InitGameInstanceClass = InitGameInstanceClass;
	}
	
	if (InitGameWorldClass != NULL) {
		InitGameWorldClass->AddToRoot();
		LoadEntry.InitGameWorldClass = InitGameWorldClass;
	}
	
	if (InitMenuWorldClass != NULL) {
		InitMenuWorldClass->AddToRoot();
		LoadEntry.InitMenuWorldClass = InitMenuWorldClass;
	}
	
	return LoadEntry;
}

FString FModHandlerHelper::GetModReferenceFromFile(const FString& FilePath) {
	FString ModReference = FPaths::GetBaseFilename(FilePath);
	//remove extension from file name
	if (FPaths::GetExtension(FilePath) == TEXT("dll")) {
		//UE4-SML-Win64-Shipping, Mod ID is the second piece - name of the module
		if (ModReference.StartsWith(TEXT("UE4-")) && ModReference.EndsWith(TEXT("-Win64-Shipping"))) {
			return ModReference.RightChop(4).LeftChop(15);
		}
		//otherwise load it straight with the same name as file name
		return ModReference;
	}
	if (FPaths::GetExtension(FilePath) == TEXT("pak")) {
		//FactoryGame_p.pak, clean priority suffix if it is there
		
		if (ModReference.EndsWith(TEXT("_p")) || ModReference.EndsWith(TEXT("_P"))) { return ModReference.LeftChop(2); }
		//return normal mod id if it doesn't contain suffix
		return ModReference;
	}
	return ModReference;
}

bool FModHandlerHelper::ReadArchiveDataJson(const TSharedPtr<FZipFile>& ZipFile, TArray<TSharedPtr<FJsonValue>>& OutJsonObjects, FModInfo& OutModInfo, FString& OutErrorMessage) {
	FString FileContents;
	if (!ZipFile->ReadFileToString(TEXT("data.json"), FileContents)) {
		OutErrorMessage = TEXT("Failed to load data.json");
		return false;
	}
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(FileContents);
	TSharedPtr<FJsonObject> ResultObject;
	if (!FJsonSerializer::Deserialize(JsonReader, ResultObject)) {
		OutErrorMessage = TEXT("Failed to parse data.json");
		return false;
	}
	FString ErrorMessage;
	const bool bModInfoSucceed = FModInfo::CreateFromJson(ResultObject, OutModInfo, ErrorMessage);
	if (!bModInfoSucceed) {
		OutErrorMessage = FString::Printf(TEXT("Invalid data.json: %s"), *ErrorMessage);
		return false;
	}
	if (!ResultObject->HasTypedField<EJson::Array>(TEXT("objects"))) {
		OutErrorMessage = TEXT("Objects section is missing from data.json file");
		return false;
	}
	OutJsonObjects = ResultObject->GetArrayField(TEXT("objects"));
	return true;
}

bool FModHandlerHelper::ExtractArchiveObjects(const TSharedPtr<class FZipFile>& ZipFile, const TArray<TSharedPtr<FJsonValue>>& JsonObjects, FModLoadingEntry& LoadingEntry, FString& OutErrorMessage) {
	const FString& ModReference = LoadingEntry.ModInfo.ModReference;
	
	if (JsonObjects.Num() == 0) {
		UE_LOG(LogModLoading, Warning, TEXT("Empty objects array in data.json for mod %s. It may be intentional, but in most cases indicates a broken mod"), *ModReference);
	}
	for (const TSharedPtr<FJsonValue>& Value : JsonObjects) {
		const TSharedPtr<FJsonObject>& JSONObject = Value.Get()->AsObject();
		if (!JSONObject.IsValid() || !JSONObject->HasTypedField<EJson::String>(TEXT("path"))) {
			OutErrorMessage = TEXT("Invalid object entry in mod object definitions");
			UE_LOG(LogModLoading, Error, TEXT("Invalid object entry found in mod %s object definitions"), *ModReference);
			return false;
		}
		const FString OBJType = JSONObject->GetStringField(TEXT("type"));
		const FString Path = JSONObject->GetStringField(TEXT("path"));
		TSharedRef<FJsonObject> Metadata = MakeShareable(new FJsonObject());
		if (JSONObject->HasField(TEXT("metadata"))) {
			Metadata = JSONObject->GetObjectField(TEXT("metadata")).ToSharedRef();
		}
		const FArchiveObjectInfo ObjectInfo{Path, OBJType, Metadata};
		FString OutObjectExtractErrorMessage;
		if (!ExtractArchiveObject(*ZipFile, ObjectInfo, LoadingEntry, OutObjectExtractErrorMessage)) {
			OutErrorMessage = FString::Printf(TEXT("Failed to extract object %s: %s"), *Path, *OutObjectExtractErrorMessage);
			UE_LOG(LogModLoading, Error, TEXT("Failed to extract object %s for mod %s: %s"), *Path, *ModReference, *OutObjectExtractErrorMessage);
			return false;
		}
	}
	const FModResources& ModResources = LoadingEntry.ModInfo.ModResources;
	if (!ModResources.ModIconPath.IsEmpty()) {
		//Mod icon is considered a custom object with fixed path,
		//Resolvable via ordinary CustomFilePaths lookup with key available from ModIconPath
		const FArchiveObjectInfo IconObjectInfo{ModResources.ModIconPath, TEXT("custom"), MakeShareable(new FJsonObject())};
		FString ModIconExtractionErrorMessage;
		if (!ExtractArchiveObject(*ZipFile, IconObjectInfo, LoadingEntry, ModIconExtractionErrorMessage)) {
			UE_LOG(LogModLoading, Warning, TEXT("Failed to extract mod icon at %s for mod %s: %s"), *ModResources.ModIconPath, *ModReference, *ModIconExtractionErrorMessage);
		}
	}
	return true;
}

bool FModHandlerHelper::ExtractArchiveObject(FZipFile& ZipHandle, const FArchiveObjectInfo& ObjectInfo, FModLoadingEntry& LoadingEntry, FString& OutErrorMessage) {
	const FString CacheDirectory = GetExtractDirectoryForModId(LoadingEntry.ModInfo.ModReference);
	const FString FileLocation = FPaths::Combine(CacheDirectory, ObjectInfo.ObjectPath);
	const FString& ModReference = LoadingEntry.ModInfo.ModReference;
	//Extract file to temporary storage
	FString FileExtractErrorMessage;
	if (!ExtractArchiveFile(ZipHandle, FileLocation, ObjectInfo.ObjectPath, ModReference, FileExtractErrorMessage)) {
		OutErrorMessage = FString::Printf(TEXT("Couldn't extract file: %s"), *FileExtractErrorMessage);
		return false;
	}
	//then do object type-specific things
	//Copy default config to configs directory from temporary
	if (ObjectInfo.ObjectType == TEXT("config")) {
		const FString ConfigFilePath = FLegacyConfigurationHelper::GetModConfigFilePath(LoadingEntry.ModInfo.ModReference);
		if (!FPaths::FileExists(ConfigFilePath)) {
			FPlatformFileManager::Get().GetPlatformFile().CopyFile(*ConfigFilePath, *FileLocation);
		}
		return true;
	}
	//try to also extract PDB files for archive dll files
	if (FPaths::GetExtension(FileLocation) == TEXT("dll")) {
		const FString PdbFileLocation = FPaths::ChangeExtension(FileLocation, TEXT("pdb"));
		const FString ArchivePdbFilePath = FPaths::ChangeExtension(ObjectInfo.ObjectPath, TEXT("pdb"));
		if (ZipHandle.FileExists(ArchivePdbFilePath)) {
			//Extract PDB file and place it near DLL
			FString OutPDBExtractionErrorMessage;
			const bool bExtractedPDB = ExtractArchiveFile(ZipHandle, PdbFileLocation, ArchivePdbFilePath, ModReference, OutPDBExtractionErrorMessage);
			if (!bExtractedPDB) {
				UE_LOG(LogModLoading, Warning, TEXT("Couldn't extract PDB file from %s to %s, for mod %s: %s"), *ArchivePdbFilePath, *PdbFileLocation, *LoadingEntry.ModInfo.ModReference, *OutPDBExtractionErrorMessage);
			}
		}
	}
	
	if (ObjectInfo.ObjectType == TEXT("pak")) {
		const FString BaseFilename = FPaths::GetBaseFilename(FileLocation);
		int32 LoadingPriority = 0;
		//Replicate UE4 behavior _p patch paks have default priority set to 100
		if (BaseFilename.EndsWith(TEXT("_p"))) {
			LoadingPriority = 100;
		}
		if (ObjectInfo.Metadata->HasField(TEXT("loading_priority"))) {
			LoadingPriority = ObjectInfo.Metadata->GetIntegerField(TEXT("loading_priority"));
		}
		LoadingEntry.PakFiles.Add(FModPakFileEntry{FileLocation, LoadingPriority});
		return true;
		
	}
	if (ObjectInfo.ObjectType == TEXT("sml_mod")) {
		if (!LoadingEntry.DLLFilePath.IsEmpty()) {
			OutErrorMessage = TEXT("Mods can only have one DLL module at a time");
			return false;
		}
		LoadingEntry.DLLFilePath = FileLocation;
		return true;	
	}
	if (ObjectInfo.ObjectType == TEXT("coremod")) {
		OutErrorMessage = TEXT("Coremods are not supported by this version of SML. Use normal APIs and hooking instead.");
		return false;
	}
	if (ObjectInfo.ObjectType == TEXT("custom")) {
		LoadingEntry.CustomFilePaths.Add(ObjectInfo.ObjectPath, FileLocation);
		return true;
	}
	OutErrorMessage = FString::Printf(TEXT("Unsupported archive object type: %s"), *ObjectInfo.ObjectType);
	return false;
}


bool FModHandlerHelper::ExtractArchiveFile(FZipFile& ZipHandle, const FString& OutFilePath, const FString& ArchiveFilePath, const FString& ModReference, FString& OutErrorMessage) {
	const FFileHash ArchiveFileHash = HashArchiveFileAttributes(ZipHandle, ArchiveFilePath);
	if (ArchiveFileHash.FileSize == 0) {
		OutErrorMessage = FString::Printf(TEXT("File specified not found in the archive: %s"), *ArchiveFilePath);
		return false;
	}
	//First, check if file already exists and it's hash matches
	FFileHash DiskFileHash = HashFileAttributes(OutFilePath);
	if (DiskFileHash == ArchiveFileHash) {
		//Hashes match, no extraction needed
		return true;
	}
	UE_LOG(LogModLoading, Display, TEXT("Extracting archive file: %s -> %s [%s]"), *ArchiveFilePath, *OutFilePath, *ModReference);
	//Ensure parent directories exist
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	const FString ParentFile = FPaths::GetPath(OutFilePath);
	if (!PlatformFile.CreateDirectoryTree(*ParentFile)) {
		OutErrorMessage = FString::Printf(TEXT("Cannot create parent directories for %s"), *OutFilePath);
		return false;
	}
	IFileHandle* NewFileHandle = PlatformFile.OpenWrite(*OutFilePath);
	if (NewFileHandle == nullptr) {
		OutErrorMessage = FString::Printf(TEXT("Cannot open output file %s for writing"), *OutFilePath);
		return false;
	}
	//Perform extraction now, delete file handle afterwards to avoid memory leaks
	const bool Result = ZipHandle.ExtractFile(ArchiveFilePath, NewFileHandle);
	delete NewFileHandle;
	//Set modification time to reflect one from the archive
	PlatformFile.SetTimeStamp(*OutFilePath, FromUnixTimestamp(ArchiveFileHash.ModificationTime));

	DiskFileHash = HashFileAttributes(*OutFilePath);
	if (DiskFileHash != ArchiveFileHash) {
		UE_LOG(LogModLoading, Error, TEXT("File hashes don't match after extraction for file %s"), *OutFilePath);
		UE_LOG(LogModLoading, Error, TEXT("That probably means zip is corrupted because actual length doesn't match expected one"));
		UE_LOG(LogModLoading, Error, TEXT("Actual Size: %llu, Actual Timestamp: %llu"), DiskFileHash.FileSize, DiskFileHash.ModificationTime);
		UE_LOG(LogModLoading, Error, TEXT("Expected Size: %llu, Expected Timestamp: %llu"), ArchiveFileHash.FileSize, ArchiveFileHash.ModificationTime);
	}
	
	if (!Result) {
		OutErrorMessage = FString::Printf(TEXT("Cannot extract file from zip at %s"), *ArchiveFilePath);
		return false;
	}
	return true;
}

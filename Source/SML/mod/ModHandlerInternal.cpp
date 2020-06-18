#include "ModHandlerInternal.h"
#include "SMLModule.h"
#include "UObjectGlobals.h"
#include "util/Utility.h"
#include "util/Logging.h"
#include "actor/SMLInitMod.h"
#include "actor/SMLInitMenu.h"
#include "zip/miniz.h"

void IterateDependencies(TMap<FString, FModLoadingEntry>& loadingEntries,
	TMap<FString, uint64_t>& modIndices,
	const FModInfo& selfInfo,
	TArray<FString>& missingDependencies,
	SML::TopologicalSort::DirectedGraph<uint64_t>& sortGraph,
	const TMap<FString, FVersionRange>& dependencies,
	bool optional);

void FinalizeSortingResults(TMap<uint64_t, FString>& modByIndex,
	TMap<FString, FModLoadingEntry>& loadingEntries,
	TArray<uint64_t>& sortedIndices) {
	TArray<uint64_t> modsToMoveInTheEnd;
	for (uint64_t i = 0; i < sortedIndices.Num(); i++) {
		const uint64_t modIndex = sortedIndices[i];
		const FModLoadingEntry& loadingEntry = loadingEntries[modByIndex[modIndex]];
		auto dependencies = loadingEntry.ModInfo.Dependencies;
		if (dependencies.Find(TEXT("@ORDER:LAST")) != nullptr)
			modsToMoveInTheEnd.Add(sortedIndices[i]);
	}
	for (auto& modIndex : modsToMoveInTheEnd) {
		sortedIndices.Remove(modIndex);
		sortedIndices.Add(modIndex);
	}
}

void PopulateSortedModList(TMap<uint64_t, FString>& modByIndex,
	TMap<FString, FModLoadingEntry>& loadingEntries,
	TArray<uint64_t>& sortedIndices,
	TArray<FModLoadingEntry>& sortedModLoadingList) {
	for (auto& modIndex : sortedIndices) {
		FModLoadingEntry& entry = loadingEntries[modByIndex[modIndex]];
		sortedModLoadingList.Add(entry);
	}
}

FModLoadingEntry CreateSmlLoadingEntry() {
	FModLoadingEntry entry;
	entry.bIsValid = true;
	entry.ModInfo = FModInfo::CreateDummyInfo(TEXT("SML"));
	entry.ModInfo.Name = TEXT("Satisfactory Mod Loader");
	entry.ModInfo.Version = GetModLoaderVersion();
	entry.ModInfo.Description = TEXT("Mod Loading & Compatibility layer for Satisfactory");
	entry.ModInfo.Authors = {TEXT("Archengius"), TEXT("Brabb3l"), TEXT("Mircea"), TEXT("Panakotta00"), TEXT("SuperCoder79"), TEXT("Vilsol")};
	entry.ModInfo.RemoteVersion.bAcceptAnyRemoteVersion = false;
	entry.ModInfo.RemoteVersion.RemoteVersion = FVersionRange(entry.ModInfo.Version, EVersionComparisonOp::GREATER_EQUALS);
	const FString SMLPakFilePath = FPaths::Combine(FPaths::GetPath(SML::GetModDirectory()), TEXT("loaders"), TEXT("SML.pak"));
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (PlatformFile.FileExists(*SMLPakFilePath)) {
		entry.PakFiles.Add({SMLPakFilePath, 100});
	} else {
		SML::Logging::error(TEXT("SML Pak file missing from the expected location: "), *SMLPakFilePath);
		SML::Logging::error(TEXT("It probably means your installation is corrupt, please re-install SML"));
		SML::Logging::error(TEXT("Game will launch, but some features won't be available."));
	}
	return entry;
}

FModPakLoadEntry CreatePakLoadEntry(const FString& Modid) {
	const FString modInitPath = FString::Printf(TEXT("/Game/%s/InitMod.InitMod_C"), *Modid);
	const FString menuInitPath = FString::Printf(TEXT("/Game/%s/InitMenu.InitMenu_C"), *Modid);
	TSubclassOf<ASMLInitMod> modInitializerClass = LoadClass<ASMLInitMod>(nullptr, *modInitPath);
	TSubclassOf<ASMLInitMenu> menuInitializerClass = LoadClass<ASMLInitMenu>(nullptr, *menuInitPath);

	FModPakLoadEntry pakEntry{Modid};
	if (modInitializerClass != nullptr) {
		//Prevent UClass Garbage Collection
		modInitializerClass->AddToRoot();
		pakEntry.ModInitClass = modInitializerClass;
	}
	if (menuInitializerClass != nullptr) {
		//Prevent UClass Garbage Collection
		menuInitializerClass->AddToRoot();
		pakEntry.MenuInitClass = menuInitializerClass;
	}
	return pakEntry;
}

FString GetModIdFromFile(const FString& FilePath) {
	FString ModId = FPaths::GetBaseFilename(FilePath);
	//remove extension from file name
	if (FPaths::GetExtension(FilePath) == TEXT("dll")) {
		//UE4-SML-Win64-Shipping, Mod ID is the second piece - name of the module
		if (ModId.StartsWith(TEXT("UE4-")) && ModId.EndsWith(TEXT("-Win64-Shipping"))) {
			return ModId.RightChop(4).LeftChop(15);
		}
		//otherwise load it straight with the same name as file name
		return ModId;
	}
	if (FPaths::GetExtension(FilePath) == TEXT("pak")) {
		//FactoryGame_p.pak, clean priority suffix if it is there
		
		if (ModId.EndsWith(TEXT("_p")) || ModId.EndsWith(TEXT("_P"))) { return ModId.LeftChop(2); }
		//return normal mod id if it doesn't contain suffix
		return ModId;
	}
	return ModId;
}

FFileHash HashArchiveFileAttributes(FZipFile& ZipHandle, const FString& FilePath) {
	const mz_zip_archive_file_stat FileStat = ZipHandle.StatFile(FilePath);
	return FFileHash{FileStat.m_uncomp_size, FileStat.m_time};
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

bool ExtractArchiveFile(FZipFile& ZipHandle, const FString& OutFilePath, const FString& ArchiveFilePath) {
	const FFileHash ArchiveFileHash = HashArchiveFileAttributes(ZipHandle, ArchiveFilePath);
	if (ArchiveFileHash.FileSize == 0) {
		SML::Logging::error(TEXT("ExtractArchiveFile failed for "), *OutFilePath, TEXT(": File specified is not found in mod archive: "), *ArchiveFilePath);
		return false;
	}
	//First, check if file already exists and it's hash matches
	FFileHash DiskFileHash = HashFileAttributes(OutFilePath);
	if (DiskFileHash == ArchiveFileHash) {
		//Hashes match, no extraction needed
		return true;
	}
	SML::Logging::info(TEXT("Extracting object "), *ArchiveFilePath, TEXT(" to "), *OutFilePath);
	//Ensure parent directories exist
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	const FString ParentFile = FPaths::GetPath(OutFilePath);
	if (!PlatformFile.CreateDirectoryTree(*ParentFile)) {
		SML::Logging::error(TEXT("ExtractArchiveFile failed for "), *OutFilePath, TEXT(": Cannot create parent directories"));
		return false;
	}
	IFileHandle* NewFileHandle = PlatformFile.OpenWrite(*OutFilePath);
	if (NewFileHandle == nullptr) {
		SML::Logging::error(TEXT("ExtractArchiveFile failed for "), *OutFilePath, TEXT(": Cannot create output file"));
		return false;
	}
	//Perform extraction now, delete file handle afterwards to avoid memory leaks
	const bool Result = ZipHandle.ExtractFile(ArchiveFilePath, NewFileHandle);
	delete NewFileHandle;
	//Set modification time to reflect one from the archive
	PlatformFile.SetTimeStamp(*OutFilePath, FromUnixTimestamp(ArchiveFileHash.ModificationTime));

	DiskFileHash = HashFileAttributes(*OutFilePath);
	if (DiskFileHash != ArchiveFileHash) {
		SML::Logging::error(TEXT("File hashes don't match after extraction for file "), *OutFilePath);
		SML::Logging::error(TEXT("That probably means zip is corrupted because actual length doesn't match expected one"));
		SML::Logging::error(TEXT("Actual Size: "), DiskFileHash.FileSize, TEXT(", Actual Timestamp: "), DiskFileHash.ModificationTime);
		SML::Logging::error(TEXT("Expected Size: "), ArchiveFileHash.FileSize, TEXT(", Expected Timestamp: "), ArchiveFileHash.ModificationTime);
	}
	
	if (!Result) {
		SML::Logging::error(TEXT("ExtractArchiveFile failed for "), *OutFilePath, TEXT(": Cannot extract file"));
		return false;
	}
	return true;
}

FString GetExtractDirectoryForModId(const FString& ModId) {
	return FPaths::Combine(SML::GetCacheDirectory(), ModId);
}

TSharedPtr<FJsonObject> ReadArchiveDataJson(FZipFile& ZipFile) {
	FString FileContents;
	if (!ZipFile.ReadFileToString(TEXT("data.json"), FileContents)) {
		SML::Logging::error(TEXT("Failed to load data.json"));
		return nullptr;
	}
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(FileContents);
	FJsonSerializer Serializer;
	TSharedPtr<FJsonObject> ResultObject;
	if (!Serializer.Deserialize(JsonReader, ResultObject)) {
		SML::Logging::error(TEXT("Failed to parse data.json"));
		return nullptr;
	}
	return ResultObject;
}

bool ExtractArchiveObject(FZipFile& ZipHandle, const FArchiveObjectInfo& ObjectInfo, FModLoadingEntry& LoadingEntry) {
	const FString CacheDirectory = GetExtractDirectoryForModId(LoadingEntry.ModInfo.Modid);
	const FString FileLocation = FPaths::Combine(CacheDirectory, ObjectInfo.ObjectPath);
	//Extract file to temporary storage
	if (!ExtractArchiveFile(ZipHandle, FileLocation, ObjectInfo.ObjectPath)) {
		SML::Logging::error(TEXT("Extraction of Object "), *ObjectInfo.ObjectPath, TEXT(" failed for Mod "), *LoadingEntry.ModInfo.Modid);
		return false;
	}
	//then do object type-specific things
	//Copy default config to configs directory from temporary
	if (ObjectInfo.ObjectType == TEXT("config")) {
		const FString ConfigFilePath = GetModConfigFilePath(LoadingEntry.ModInfo.Modid);
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
			ExtractArchiveFile(ZipHandle, PdbFileLocation, ArchivePdbFilePath);
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
		
	} else if (ObjectInfo.ObjectType == TEXT("sml_mod")) {
		if (!LoadingEntry.DLLFilePath.IsEmpty()) {
			SML::Logging::error(TEXT("Mod can only have one DLL module at a time: "), *LoadingEntry.ModInfo.Modid);
			return false;
		}
		LoadingEntry.DLLFilePath = FileLocation;
		return true;
		
	} else if (ObjectInfo.ObjectType == TEXT("coremod")) {
		SML::Logging::error(TEXT("Core mods are not supported by this version of SML"));
		return false;
	} else if (ObjectInfo.ObjectType == TEXT("custom")) {
		LoadingEntry.CustomFilePaths.Add(ObjectInfo.ObjectPath, FileLocation);
		return true;
	} else {
		SML::Logging::error(TEXT("Unsupported archive object type: "), *ObjectInfo.ObjectType);
		return false;
	}
}

bool ExtractArchiveObjects(FZipFile& ZipHandle, const FJsonObject& DataJson, FModLoadingEntry& LoadingEntry) {
	const TArray<TSharedPtr<FJsonValue>>& Objects = DataJson.GetArrayField(TEXT("objects"));
	
	if (Objects.Num() == 0) {
		SML::Logging::error(TEXT("missing `objects` array in data.json, or it is empty for mod: "), *LoadingEntry.ModInfo.Modid);
		return false;
	}
	for (auto& Value : Objects) {
		const TSharedPtr<FJsonObject>& JSONObject = Value.Get()->AsObject();
		if (!JSONObject.IsValid() || !JSONObject->HasTypedField<EJson::String>(TEXT("path"))) {
			SML::Logging::warning(TEXT("Invalid object entry found in mod's object definitions: "), *LoadingEntry.ModInfo.Modid);
			continue;
		}
		const FString OBJType = JSONObject->GetStringField(TEXT("type"));
		const FString Path = JSONObject->GetStringField(TEXT("path"));
		TSharedRef<FJsonObject> Metadata = MakeShareable(new FJsonObject());
		if (JSONObject->HasField(TEXT("metadata"))) {
			Metadata = JSONObject->GetObjectField(TEXT("metadata")).ToSharedRef();
		}
		const FArchiveObjectInfo ObjectInfo{Path, OBJType, Metadata};
		if (!ExtractArchiveObject(ZipHandle, ObjectInfo, LoadingEntry)) {
			SML::Logging::error(TEXT("Failed to extract object "), *Path, TEXT(" for mod "), *LoadingEntry.ModInfo.Modid);
			return false;
		}
	}
	const FModResources& ModResources = LoadingEntry.ModInfo.ModResources;
	if (!ModResources.ModIconPath.IsEmpty()) {
		//Mod icon is considered a custom object with fixed path,
		//Resolvable via ordinary CustomFilePaths lookup with key available from ModIconPath
		const FArchiveObjectInfo IconObjectInfo{ModResources.ModIconPath, TEXT("custom"), MakeShareable(new FJsonObject())};
		if (!ExtractArchiveObject(ZipHandle, IconObjectInfo, LoadingEntry)) {
			SML::Logging::error(TEXT("Failed to extract mod icon at "), *ModResources.ModIconPath, TEXT(" for mod "), *LoadingEntry.ModInfo.Modid);
		}
	}
	return true;
}

void IterateDependencies(TMap<FString, FModLoadingEntry>& loadingEntries,
	TMap<FString, uint64_t>& modIndices,
	const FModInfo& selfInfo,
	TArray<FString>& missingDependencies,
	TopologicalSort::DirectedGraph<uint64_t>& sortGraph,
	const TMap<FString, FVersionRange>& dependencies,
	bool optional) {

	for (auto& pair : dependencies) {
		FModLoadingEntry& dependencyEntry = loadingEntries[pair.Key];
		FModInfo& depInfo = dependencyEntry.ModInfo;
		if (pair.Key != "@ORDER:LAST") {
			if (!dependencyEntry.bIsValid || !pair.Value.Matches(depInfo.Version)) {
				const FString reason = dependencyEntry.bIsValid ? FString::Printf(TEXT("unsupported version: %s"), *depInfo.Version.String()) : TEXT("not installed");
				const FString message = FString::Printf(TEXT("%s requires %s(%s): %s"), *selfInfo.Modid, *pair.Key, *pair.Value.String(), *reason);
				if (!optional) missingDependencies.Add(message);
				continue;
			}
			sortGraph.addEdge(modIndices[depInfo.Modid], modIndices[selfInfo.Modid]);
		}
	}
}

IModuleInterface* InitializeSMLModule() {
	return new FSMLModule();
}
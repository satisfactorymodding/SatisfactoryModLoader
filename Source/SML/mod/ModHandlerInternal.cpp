#include "ModHandlerInternal.h"
#include "SMLModule.h"
#include "UObjectGlobals.h"
#include "util/Utility.h"
#include "util/Logging.h"
#include "util/picosha2.h"
#include "GameFramework/Actor.h"
#include "actor/SMLInitMod.h"
#include "actor/SMLInitMenu.h"

void iterateDependencies(TMap<FString, FModLoadingEntry>& loadingEntries,
	TMap<FString, uint64_t>& modIndices,
	const FModInfo& selfInfo,
	TArray<FString>& missingDependencies,
	SML::TopologicalSort::DirectedGraph<uint64_t>& sortGraph,
	const TMap<FString, FVersionRange>& dependencies,
	bool optional);

void finalizeSortingResults(TMap<uint64_t, FString>& modByIndex,
	TMap<FString, FModLoadingEntry>& loadingEntries,
	TArray<uint64_t>& sortedIndices) {
	TArray<uint64_t> modsToMoveInTheEnd;
	for (uint64_t i = 0; i < sortedIndices.Num(); i++) {
		uint64_t modIndex = sortedIndices[i];
		const FModLoadingEntry& loadingEntry = loadingEntries[modByIndex[modIndex]];
		auto dependencies = loadingEntry.modInfo.dependencies;
		if (dependencies.Find(TEXT("@ORDER:LAST")) != nullptr)
			modsToMoveInTheEnd.Add(sortedIndices[i]);
	}
	for (auto& modIndex : modsToMoveInTheEnd) {
		sortedIndices.Remove(modIndex);
		sortedIndices.Add(modIndex);
	}
}

void populateSortedModList(TMap<uint64_t, FString>& modByIndex,
	TMap<FString, FModLoadingEntry>& loadingEntries,
	TArray<uint64_t>& sortedIndices,
	TArray<FModLoadingEntry>& sortedModLoadingList) {
	for (auto& modIndex : sortedIndices) {
		FModLoadingEntry& entry = loadingEntries[modByIndex[modIndex]];
		sortedModLoadingList.Add(entry);
	}
}

FModLoadingEntry createSMLLoadingEntry() {
	FModLoadingEntry entry;
	entry.isValid = true;
	entry.modInfo = FModInfo::createDummyInfo(TEXT("SML"));
	entry.modInfo.name = TEXT("Satisfactory Mod Loader");
	entry.modInfo.version = getModLoaderVersion();
	entry.modInfo.description = TEXT("Mod Loading & Compatibility layer for Satisfactory");
	entry.modInfo.authors = {TEXT("Archengius"), TEXT("Brabb3l"), TEXT("Mircea"), TEXT("Panakotta00"), TEXT("SuperCoder79"), TEXT("Vilsol")};
	return entry;
}

FModPakLoadEntry CreatePakLoadEntry(const FString& modid) {
	const FString modInitPath = FString::Printf(TEXT("/Game/%s/InitMod.InitMod_C"), *modid);
	const FString menuInitPath = FString::Printf(TEXT("/Game/%s/InitMenu.InitMenu_C"), *modid);
	TSubclassOf<ASMLInitMod> modInitializerClass = LoadClass<ASMLInitMod>(nullptr, *modInitPath);
	TSubclassOf<ASMLInitMenu> menuInitializerClass = LoadClass<ASMLInitMenu>(nullptr, *menuInitPath);

	FModPakLoadEntry pakEntry{modid};
	if (modInitializerClass != nullptr) {
		//Prevent UClass Garbage Collection
		modInitializerClass->AddToRoot();
		pakEntry.modInitClass = modInitializerClass;
	}
	if (menuInitializerClass != nullptr) {
		//Prevent UClass Garbage Collection
		menuInitializerClass->AddToRoot();
		pakEntry.menuInitClass = menuInitializerClass;
	}
	return pakEntry;
}

FString getModIdFromFile(const FString& filePath) {
	FString modId = FPaths::GetBaseFilename(filePath);
	//remove extension from file name
	if (FPaths::GetExtension(filePath) == TEXT("dll")) {
		//UE4-SML-Win64-Shipping, Mod ID is the second piece - name of the module
		if (modId.StartsWith(TEXT("UE4-")) && modId.EndsWith(TEXT("-Win64-Shipping"))) {
			return modId.RightChop(4).LeftChop(15);
		}
		//otherwise load it straight with the same name as file name
		return modId;
	}
	if (FPaths::GetExtension(filePath) == TEXT("pak")) {
		//FactoryGame_p.pak, clean priority suffix if it is there
		
		if (modId.EndsWith(TEXT("_p")) || modId.EndsWith(TEXT("_P"))) { return modId.LeftChop(2); }
		//return normal mod id if it doesn't contain suffix
		return modId;
	}
	return modId;
}

FileHash hashFileContents(const FString& path) {
	std::ifstream f(*path, std::ios::binary);
	std::vector<unsigned char> hash(picosha2::k_digest_size);
	picosha2::hash256(f, hash.begin(), hash.end());
	return picosha2::bytes_to_hex_string(hash);
}

FString generateTempFilePath(const FileHash& fileHash, const char* fileName) {
	FString dir = SML::getCacheDirectory() / FString(fileHash.c_str());
	FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*dir);
	return dir / fileName;
}

bool extractArchiveFile(const FString& outFilePath, ttvfs::File* obj) {
	std::ofstream outFile(*outFilePath, std::ofstream::binary);
	auto buffer_size = 4096;
	if (!obj->open("rb")) {
		SML::Logging::error(TEXT("Failed opening archive object "), obj->name());
		return false;
	}
	char* buf = new char[buffer_size];
	do {
		size_t bytes = obj->read(buf, buffer_size);
		outFile.write(buf, bytes);
	} while (obj->getpos() < obj->size());
	outFile.close();
	obj->close();
	return true;
}

TSharedPtr<FJsonObject> readArchiveJson(ttvfs::File* obj) {
	if (!obj->open("rb")) {
		SML::Logging::error(TEXT("Failed opening archive object"));
		return TSharedPtr<FJsonObject>();
	}
	std::vector<char> buffer(obj->size());
	obj->read(buffer.data(), obj->size());
	obj->close();
	const FString string(std::string(buffer.begin(), buffer.end()).c_str());
	try {
		return parseJsonLenient(string);
	} catch (const std::exception& ex) {
		SML::Logging::error(*FString::Printf(TEXT("Failed to parse data.json from archive object %s: %s"), obj->name(), ex.what()));
		return TSharedPtr<FJsonObject>();
	}
}

bool hashArchiveFileContents(ttvfs::File* obj, FileHash& outHash) {
	if (!obj->open("rb")) {
		SML::Logging::error(TEXT("Failed opening archive object"));
		return false;
	}
	std::vector<char> buffer(obj->size());
	obj->read(buffer.data(), obj->size());
	obj->close();

	std::vector<unsigned char> hash(picosha2::k_digest_size);
	picosha2::hash256(buffer.begin(), buffer.end(), hash.begin(), hash.end());
	outHash = picosha2::bytes_to_hex_string(hash);
	return true;
}

bool extractFixedNameFileInternal(ttvfs::File* objectFile, const FString& filePath) {
	FileHash fileHash;
	if (!hashArchiveFileContents(objectFile, fileHash)) {
		return false;
	}
	//if cached file doesn't exist, or file hashes don't match, unpack file and copy it
	if (!FPaths::FileExists(filePath) || fileHash != hashFileContents(filePath)) {
		//in case of broken cache file, remove old file
		FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*filePath);
		//unpack file in the temporary directory
		return extractArchiveFile(filePath, objectFile);
	}
	return true;
}

bool extractTempFileInternal(ttvfs::File* objectFile, const std::string& objectType, FString& filePath) {
	FileHash fileHash;
	if (!hashArchiveFileContents(objectFile, fileHash)) {
		return false;
	}
	filePath = generateTempFilePath(fileHash, objectFile->name());
	//if cached file doesn't exist, or file hashes don't match, unpack file and copy it
	if (!FPaths::FileExists(filePath) || fileHash != hashFileContents(filePath)) {
		//in case of broken cache file, remove old file
		FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*filePath);
		//unpack file in the temporary directory
		return extractArchiveFile(filePath, objectFile);
	}
	return true;
}

bool extractArchiveObject(ttvfs::Dir& root, const std::string& objectType, const std::string& archivePath, SML::Mod::FModLoadingEntry& loadingEntry, const FJsonObject* metadata) {
	ttvfs::File* objectFile = root.getFile(archivePath.c_str());
	if (objectFile == nullptr) {
		SML::Logging::error("object specified in data.json is missing in zip file");
		return false;
	}

	//extract configuration
	if (objectType == "config") {
		//extract mod configuration into the predefined folder
		FString configFilePath = getModConfigFilePath(loadingEntry.modInfo.modid);
		if (!FPaths::FileExists(configFilePath)) {
			//only extract it if it doesn't exist already
			return extractArchiveFile(configFilePath, objectFile);
		}
		return true;
	}
	//extract archive file now into the temporary directory
	FString filePath;
	if (!extractTempFileInternal(objectFile, objectType, filePath)) {
		return false;
	}

	//try to also extract PDB files for archive dll files
	if (FPaths::GetExtension(filePath) == TEXT("dll")) {
		//replace last 4 characters (.dll) with new extension (.pdb)
		std::string archivePdbFilePath = archivePath;
		archivePdbFilePath.replace(archivePdbFilePath.length() - 4, 4, ".pdb");
		FString pdbFilePath = FString(filePath);
		pdbFilePath = FPaths::ChangeExtension(pdbFilePath, TEXT("pdb"));
		ttvfs::File* pdbObjectFile = root.getFile(archivePdbFilePath.c_str());
		if (pdbObjectFile != nullptr) {
			//extract pdb file with the same name now
			if (!extractFixedNameFileInternal(pdbObjectFile, pdbFilePath)) {
				SML::Logging::warning(TEXT("Failed to extract mod PDB file"));
			}
		}
	}
	
	if (objectType == "pak") {
		int32 loadingPriority = 0;
		if (metadata != nullptr && metadata->HasTypedField<EJson::Number>(TEXT("loading_priority"))) {
			loadingPriority = metadata->GetIntegerField(TEXT("loading_priority"));
		}
		const FString pakFilePath = filePath;
		loadingEntry.pakFiles.Add(FModPakFileEntry{ pakFilePath, loadingPriority });
	} else if (objectType == "sml_mod") {
		if (!loadingEntry.dllFilePath.IsEmpty()) {
			SML::Logging::error("mod can only have one DLL module at a time");
			return false;
		}
		loadingEntry.dllFilePath = filePath;
	} else if (objectType == "core_mod") {
		SML::Logging::error("core mods are not supported by this version of SML");
		return false;
	} else {
		SML::Logging::error("Unknown archive object type encountered: ", objectType.c_str());
		return false;
	}
	return true;
}

bool extractArchiveObjects(ttvfs::Dir& root, const FJsonObject& dataJson, SML::Mod::FModLoadingEntry& loadingEntry) {
	const TArray<TSharedPtr<FJsonValue>>& objects = dataJson.GetArrayField(TEXT("objects"));
	
	if (objects.Num() == 0) {
		SML::Logging::error("missing `objects` array in data.json, or it is empty.");
		return false;
	}
	for (auto& value : objects) {
		const TSharedPtr<FJsonObject>& jsonObject = value.Get()->AsObject();
		if (!jsonObject.IsValid() ||
			!jsonObject->HasTypedField<EJson::String>(TEXT("Path")) ||
			!jsonObject->HasTypedField<EJson::String>(TEXT("path"))) {
			SML::Logging::warning(TEXT("Invalid object entry found in mod's object definitions"));
			continue;
		}
		std::string objType = TCHAR_TO_ANSI(*jsonObject->GetStringField(TEXT("type")));
		std::string path = TCHAR_TO_ANSI(*jsonObject->GetStringField(TEXT("path")));
		FJsonObject* metadata = jsonObject->HasField(TEXT("metadata")) ? jsonObject->GetObjectField(TEXT("metadata")).Get() : nullptr;
		if (!extractArchiveObject(root, objType, path, loadingEntry, metadata))
			return false;
	}
	return true;
}

void iterateDependencies(TMap<FString, FModLoadingEntry>& loadingEntries,
	TMap<FString, uint64_t>& modIndices,
	const FModInfo& selfInfo,
	TArray<FString>& missingDependencies,
	TopologicalSort::DirectedGraph<uint64_t>& sortGraph,
	const TMap<FString, FVersionRange>& dependencies,
	bool optional) {

	for (auto& pair : dependencies) {
		FModLoadingEntry& dependencyEntry = loadingEntries[pair.Key];
		FModInfo& depInfo = dependencyEntry.modInfo;
		if (pair.Key != "@ORDER:LAST") {
			if (!dependencyEntry.isValid || !pair.Value.matches(depInfo.version)) {
				const FString reason = dependencyEntry.isValid ? FString::Printf(TEXT("unsupported version: %s"), *depInfo.version.string()) : TEXT("not installed");
				const FString message = FString::Printf(TEXT("%s requires %s(%s): %s"), *selfInfo.modid, *pair.Key, *pair.Value.string(), *reason);
				if (!optional) missingDependencies.Add(message);
				continue;
			}
			sortGraph.addEdge(modIndices[depInfo.modid], modIndices[selfInfo.modid]);
		}
	}
}

IModuleInterface* InitializeSMLModule() {
	return new FSMLModule();
}
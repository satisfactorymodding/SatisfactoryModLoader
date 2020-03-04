#include "ModHandlerInternal.h"
#include "SMLModule.h"
#include "UObjectGlobals.h"
#include "util/Utility.h"
#include "util/Logging.h"
#include "util/picosha2.h"
#include "GameFramework/Actor.h"
#include "actor/SMLInitMod.h"
#include "actor/SMLInitMenu.h"

void iterateDependencies(std::unordered_map<std::wstring, FModLoadingEntry>& loadingEntries,
	std::unordered_map<std::wstring, uint64_t>& modIndices,
	const FModInfo& selfInfo,
	std::vector<std::wstring>& missingDependencies,
	SML::TopologicalSort::DirectedGraph<uint64_t>& sortGraph,
	const std::unordered_map<std::wstring, FVersionRange>& dependencies,
	bool optional);

void finalizeSortingResults(std::unordered_map<uint64_t, std::wstring>& modByIndex,
	std::unordered_map<std::wstring, FModLoadingEntry>& loadingEntries,
	std::vector<uint64_t>& sortedIndices) {
	std::vector<uint64_t> modsToMoveInTheEnd;
	for (uint64_t i = 0; i < sortedIndices.size(); i++) {
		uint64_t modIndex = sortedIndices[i];
		const FModLoadingEntry& loadingEntry = loadingEntries[modByIndex[modIndex]];
		auto dependencies = loadingEntry.modInfo.dependencies;
		if (dependencies.find(TEXT("@ORDER:LAST")) != dependencies.end())
			modsToMoveInTheEnd.push_back(i);
	}
	for (auto& modIndex : modsToMoveInTheEnd) {
		sortedIndices.erase(std::remove(sortedIndices.begin(), sortedIndices.end(), modIndex), sortedIndices.end());
		sortedIndices.push_back(modIndex);
	}
}

void populateSortedModList(std::unordered_map<uint64_t, std::wstring>& modByIndex,
	std::unordered_map<std::wstring, FModLoadingEntry>& loadingEntries,
	std::vector<uint64_t>& sortedIndices,
	std::vector<FModLoadingEntry>& sortedModLoadingList) {
	for (auto& modIndex : sortedIndices) {
		FModLoadingEntry& entry = loadingEntries[modByIndex[modIndex]];
		sortedModLoadingList.push_back(entry);
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

FModPakLoadEntry CreatePakLoadEntry(const std::wstring& modid) {
	const std::wstring baseInitPath = formatStr(TEXT("/Game/"), modid);
	const std::wstring modInitPath = formatStr(baseInitPath, TEXT("/InitMod.InitMod_C"));
	const std::wstring menuInitPath = formatStr(baseInitPath, TEXT("/InitMenu.InitMenu_C"));
	TSubclassOf<ASMLInitMod> modInitializerClass = LoadClass<ASMLInitMod>(nullptr, modInitPath.c_str());
	TSubclassOf<ASMLInitMenu> menuInitializerClass = LoadClass<ASMLInitMenu>(nullptr, menuInitPath.c_str());

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

std::wstring getModIdFromFile(const path& filePath) {
	std::wstring modId = filePath.filename().generic_wstring();
	//remove extension from file name
	modId.erase(modId.find_last_of(TEXT('.')));
	if (filePath.extension() == TEXT(".dll")) {
		//UE4-SML-Win64-Shipping, Mod ID is the second piece - name of the module
		if (modId.find(TEXT("UE4-")) == 0 && modId.find(TEXT("-Win64-Shipping")) == modId.size() - 15) {
			return modId.substr(4, modId.size() - 15 - 4);
		}
		//otherwise load it straight with the same name as file name
		return modId;
	}
	if (filePath.extension() == TEXT(".pak")) {
		//FactoryGame_p.pak, clean priority suffix if it is there
		if (modId.find_last_of(TEXT("_P")) == modId.size() - 2 ||
			modId.find_last_of(TEXT("_p")) == modId.size() - 2) {return modId.substr(0, modId.size() - 2);
		}
		//return normal mod id if it doesn't contain suffix
		return modId;
	}
	return modId;
}

FileHash hashFileContents(const path& path) {
	std::ifstream f(path.generic_string(), std::ios::binary);
	std::vector<unsigned char> hash(picosha2::k_digest_size);
	picosha2::hash256(f, hash.begin(), hash.end());
	return picosha2::bytes_to_hex_string(hash);
}

path generateTempFilePath(const FileHash& fileHash, const char* extension) {
	path result = SML::getCacheDirectory();
	return path(result / fileHash).replace_extension(extension);
}

bool extractArchiveFile(const path& outFilePath, ttvfs::File* obj) {
	std::ofstream outFile(outFilePath, std::ofstream::binary);
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
	const std::wstring string(buffer.begin(), buffer.end());
	try {
		return parseJsonLenient(string);
	} catch (const std::exception& ex) {
		SML::Logging::error(TEXT("Failed to parse data.json from archive object "), obj->name(), TEXT(": "), ex.what());
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

bool stringEndsWith(const std::string& fullString, const std::string& ending) {
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	} else {
		return false;
	}
}

bool extractFixedNameFileInternal(ttvfs::File* objectFile, const path& filePath) {
	FileHash fileHash;
	if (!hashArchiveFileContents(objectFile, fileHash)) {
		return false;
	}
	//if cached file doesn't exist, or file hashes don't match, unpack file and copy it
	if (!exists(filePath) || fileHash != hashFileContents(filePath)) {
		//in case of broken cache file, remove old file
		remove(filePath);
		//unpack file in the temporary directory
		return extractArchiveFile(filePath, objectFile);
	}
	return true;
}

bool extractTempFileInternal(ttvfs::File* objectFile, const std::string& objectType, path& filePath) {
	FileHash fileHash;
	if (!hashArchiveFileContents(objectFile, fileHash)) {
		return false;
	}
	filePath = generateTempFilePath(fileHash, objectType.c_str());
	//if cached file doesn't exist, or file hashes don't match, unpack file and copy it
	if (!exists(filePath) || fileHash != hashFileContents(filePath)) {
		//in case of broken cache file, remove old file
		remove(filePath);
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
		const path& configFilePath = getModConfigFilePath(loadingEntry.modInfo.modid);
		if (!exists(configFilePath)) {
			//only extract it if it doesn't exist already
			return extractArchiveFile(configFilePath, objectFile);
		}
		return true;
	}
	//extract archive file now into the temporary directory
	path filePath;
	if (!extractTempFileInternal(objectFile, objectType, filePath)) {
		return false;
	}

	//try to also extract PDB files for archive dll files
	if (stringEndsWith(archivePath, ".dll")) {
		//replace last 4 characters (.dll) with new extension (.pdb)
		std::string archivePdbFilePath = archivePath;
		archivePdbFilePath.replace(archivePdbFilePath.length() - 4, 4, ".pdb");
		path pdbFilePath = path(filePath);
		pdbFilePath.replace_extension("pdb");
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
		const std::wstring pakFilePath = filePath.generic_wstring();
		loadingEntry.pakFiles.push_back(FModPakFileEntry{ pakFilePath, loadingPriority });
	} else if (objectType == "sml_mod") {
		if (!loadingEntry.dllFilePath.empty()) {
			SML::Logging::error("mod can only have one DLL module at a time");
			return false;
		}
		loadingEntry.dllFilePath = filePath.generic_wstring();
	} else if (objectType == "core_mod") {
		SML::Logging::error("core mods are not supported by this version of SML");
		return false;
	} else {
		SML::Logging::error("Unknown archive object type encountered: ", objectType);
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

void iterateDependencies(std::unordered_map<std::wstring, FModLoadingEntry>& loadingEntries,
	std::unordered_map<std::wstring, uint64_t>& modIndices,
	const FModInfo& selfInfo,
	std::vector<std::wstring>& missingDependencies,
	TopologicalSort::DirectedGraph<uint64_t>& sortGraph,
	const std::unordered_map<std::wstring, FVersionRange>& dependencies,
	bool optional) {

	for (auto& pair : dependencies) {
		FModLoadingEntry& dependencyEntry = loadingEntries[pair.first];
		FModInfo& depInfo = dependencyEntry.modInfo;
		if (pair.first != "@ORDER:LAST") {
			if (!dependencyEntry.isValid || !pair.second.matches(depInfo.version)) {
				const std::wstring reason = dependencyEntry.isValid ? formatStr(TEXT("unsupported version: "), depInfo.version.string()) : TEXT("not installed");
				const std::wstring message = formatStr(selfInfo.modid, " requires ", pair.first, "(", pair.second.string(), "): ", reason);
				if (!optional) missingDependencies.push_back(message);
				continue;
			}
			sortGraph.addEdge(modIndices[selfInfo.modid], modIndices[depInfo.modid]);
		}
	}
}

IModuleInterface* InitializeSMLModule() {
	return new FSMLModule();
}
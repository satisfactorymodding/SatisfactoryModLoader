#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_AssetRegistry_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class AssetRegistry.AssetRegistryImpl
// 0x06E8 (0x0710 - 0x0028)
class UAssetRegistryImpl : public UObject
{
public:
	unsigned char                                      UnknownData00[0x6E8];                                     // 0x0028(0x06E8) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class AssetRegistry.AssetRegistryImpl");
		return ptr;
	}

};


// Class AssetRegistry.AssetRegistryHelpers
// 0x0000 (0x0028 - 0x0028)
class UAssetRegistryHelpers : public UObject
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class AssetRegistry.AssetRegistryHelpers");
		return ptr;
	}


	struct FSoftObjectPath ToSoftObjectPath(const struct FAssetData& InAssetData);
	struct FARFilter SetFilterTagsAndValues(const struct FARFilter& InFilter, TArray<struct FTagAndValue> InTagsAndValues);
	bool IsValid(const struct FAssetData& InAssetData);
	bool IsUAsset(const struct FAssetData& InAssetData);
	bool IsRedirector(const struct FAssetData& InAssetData);
	bool IsAssetLoaded(const struct FAssetData& InAssetData);
	bool GetTagValue(const struct FAssetData& InAssetData, const struct FName& InTagName, class FString* OutTagValue);
	class FString GetFullName(const struct FAssetData& InAssetData);
	class FString GetExportTextName(const struct FAssetData& InAssetData);
	class UClass* GetClass(const struct FAssetData& InAssetData);
	TScriptInterface<class UAssetRegistry> GetAssetRegistry();
	class UObject* GetAsset(const struct FAssetData& InAssetData);
	struct FAssetData CreateAssetData(class UObject* InAsset, bool bAllowBlueprintClass);
};


// Class AssetRegistry.AssetRegistry
// 0x0000 (0x0028 - 0x0028)
class UAssetRegistry : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class AssetRegistry.AssetRegistry");
		return ptr;
	}


	void SearchAllAssets(bool bSynchronousSearch);
	void ScanPathsSynchronous(TArray<class FString> InPaths, bool bForceRescan);
	void ScanModifiedAssetFiles(TArray<class FString> InFilePaths);
	void ScanFilesSynchronous(TArray<class FString> InFilePaths, bool bForceRescan);
	void RunAssetsThroughFilter(const struct FARFilter& Filter, TArray<struct FAssetData>* AssetDataList);
	void PrioritizeSearchPath(const class FString& PathToPrioritize);
	bool IsLoadingAssets();
	bool HasAssets(const struct FName& PackagePath, bool bRecursive);
	void GetSubPaths(const class FString& InBasePath, bool bInRecurse, TArray<class FString>* OutPathList);
	bool GetAssetsByPath(const struct FName& PackagePath, bool bRecursive, bool bIncludeOnlyOnDiskAssets, TArray<struct FAssetData>* OutAssetData);
	bool GetAssetsByPackageName(const struct FName& PackageName, bool bIncludeOnlyOnDiskAssets, TArray<struct FAssetData>* OutAssetData);
	bool GetAssetsByClass(const struct FName& ClassName, bool bSearchSubClasses, TArray<struct FAssetData>* OutAssetData);
	bool GetAssets(const struct FARFilter& Filter, TArray<struct FAssetData>* OutAssetData);
	struct FAssetData GetAssetByObjectPath(const struct FName& ObjectPath, bool bIncludeOnlyOnDiskAssets);
	void GetAllCachedPaths(TArray<class FString>* OutPathList);
	bool GetAllAssets(bool bIncludeOnlyOnDiskAssets, TArray<struct FAssetData>* OutAssetData);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

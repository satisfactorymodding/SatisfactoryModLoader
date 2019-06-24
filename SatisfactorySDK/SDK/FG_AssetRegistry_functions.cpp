// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_AssetRegistry_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function AssetRegistry.AssetRegistryHelpers.ToSoftObjectPath
// ()
// Parameters:
// struct FAssetData              InAssetData                    (ConstParm, Parm, OutParm, ReferenceParm)
// struct FSoftObjectPath         ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm)

struct FSoftObjectPath UAssetRegistryHelpers::ToSoftObjectPath(const struct FAssetData& InAssetData)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistryHelpers.ToSoftObjectPath");

	UAssetRegistryHelpers_ToSoftObjectPath_Params params;
	params.InAssetData = InAssetData;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function AssetRegistry.AssetRegistryHelpers.SetFilterTagsAndValues
// ()
// Parameters:
// struct FARFilter               InFilter                       (ConstParm, Parm, OutParm, ReferenceParm)
// TArray<struct FTagAndValue>    InTagsAndValues                (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
// struct FARFilter               ReturnValue                    (Parm, OutParm, ReturnParm)

struct FARFilter UAssetRegistryHelpers::SetFilterTagsAndValues(const struct FARFilter& InFilter, TArray<struct FTagAndValue> InTagsAndValues)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistryHelpers.SetFilterTagsAndValues");

	UAssetRegistryHelpers_SetFilterTagsAndValues_Params params;
	params.InFilter = InFilter;
	params.InTagsAndValues = InTagsAndValues;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function AssetRegistry.AssetRegistryHelpers.IsValid
// ()
// Parameters:
// struct FAssetData              InAssetData                    (ConstParm, Parm, OutParm, ReferenceParm)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UAssetRegistryHelpers::IsValid(const struct FAssetData& InAssetData)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistryHelpers.IsValid");

	UAssetRegistryHelpers_IsValid_Params params;
	params.InAssetData = InAssetData;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function AssetRegistry.AssetRegistryHelpers.IsUAsset
// ()
// Parameters:
// struct FAssetData              InAssetData                    (ConstParm, Parm, OutParm, ReferenceParm)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UAssetRegistryHelpers::IsUAsset(const struct FAssetData& InAssetData)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistryHelpers.IsUAsset");

	UAssetRegistryHelpers_IsUAsset_Params params;
	params.InAssetData = InAssetData;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function AssetRegistry.AssetRegistryHelpers.IsRedirector
// ()
// Parameters:
// struct FAssetData              InAssetData                    (ConstParm, Parm, OutParm, ReferenceParm)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UAssetRegistryHelpers::IsRedirector(const struct FAssetData& InAssetData)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistryHelpers.IsRedirector");

	UAssetRegistryHelpers_IsRedirector_Params params;
	params.InAssetData = InAssetData;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function AssetRegistry.AssetRegistryHelpers.IsAssetLoaded
// ()
// Parameters:
// struct FAssetData              InAssetData                    (ConstParm, Parm, OutParm, ReferenceParm)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UAssetRegistryHelpers::IsAssetLoaded(const struct FAssetData& InAssetData)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistryHelpers.IsAssetLoaded");

	UAssetRegistryHelpers_IsAssetLoaded_Params params;
	params.InAssetData = InAssetData;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function AssetRegistry.AssetRegistryHelpers.GetTagValue
// ()
// Parameters:
// struct FAssetData              InAssetData                    (ConstParm, Parm, OutParm, ReferenceParm)
// struct FName                   InTagName                      (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// class FString                  OutTagValue                    (Parm, OutParm, ZeroConstructor)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UAssetRegistryHelpers::GetTagValue(const struct FAssetData& InAssetData, const struct FName& InTagName, class FString* OutTagValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistryHelpers.GetTagValue");

	UAssetRegistryHelpers_GetTagValue_Params params;
	params.InAssetData = InAssetData;
	params.InTagName = InTagName;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (OutTagValue != nullptr)
		*OutTagValue = params.OutTagValue;

	return params.ReturnValue;
}


// Function AssetRegistry.AssetRegistryHelpers.GetFullName
// ()
// Parameters:
// struct FAssetData              InAssetData                    (ConstParm, Parm, OutParm, ReferenceParm)
// class FString                  ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm)

class FString UAssetRegistryHelpers::GetFullName(const struct FAssetData& InAssetData)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistryHelpers.GetFullName");

	UAssetRegistryHelpers_GetFullName_Params params;
	params.InAssetData = InAssetData;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function AssetRegistry.AssetRegistryHelpers.GetExportTextName
// ()
// Parameters:
// struct FAssetData              InAssetData                    (ConstParm, Parm, OutParm, ReferenceParm)
// class FString                  ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm)

class FString UAssetRegistryHelpers::GetExportTextName(const struct FAssetData& InAssetData)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistryHelpers.GetExportTextName");

	UAssetRegistryHelpers_GetExportTextName_Params params;
	params.InAssetData = InAssetData;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function AssetRegistry.AssetRegistryHelpers.GetClass
// ()
// Parameters:
// struct FAssetData              InAssetData                    (ConstParm, Parm, OutParm, ReferenceParm)
// class UClass*                  ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UClass* UAssetRegistryHelpers::GetClass(const struct FAssetData& InAssetData)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistryHelpers.GetClass");

	UAssetRegistryHelpers_GetClass_Params params;
	params.InAssetData = InAssetData;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function AssetRegistry.AssetRegistryHelpers.GetAssetRegistry
// ()
// Parameters:
// TScriptInterface<class UAssetRegistry> ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

TScriptInterface<class UAssetRegistry> UAssetRegistryHelpers::GetAssetRegistry()
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistryHelpers.GetAssetRegistry");

	UAssetRegistryHelpers_GetAssetRegistry_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function AssetRegistry.AssetRegistryHelpers.GetAsset
// ()
// Parameters:
// struct FAssetData              InAssetData                    (ConstParm, Parm, OutParm, ReferenceParm)
// class UObject*                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UObject* UAssetRegistryHelpers::GetAsset(const struct FAssetData& InAssetData)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistryHelpers.GetAsset");

	UAssetRegistryHelpers_GetAsset_Params params;
	params.InAssetData = InAssetData;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function AssetRegistry.AssetRegistryHelpers.CreateAssetData
// ()
// Parameters:
// class UObject*                 InAsset                        (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
// bool                           bAllowBlueprintClass           (Parm, ZeroConstructor, IsPlainOldData)
// struct FAssetData              ReturnValue                    (Parm, OutParm, ReturnParm)

struct FAssetData UAssetRegistryHelpers::CreateAssetData(class UObject* InAsset, bool bAllowBlueprintClass)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistryHelpers.CreateAssetData");

	UAssetRegistryHelpers_CreateAssetData_Params params;
	params.InAsset = InAsset;
	params.bAllowBlueprintClass = bAllowBlueprintClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function AssetRegistry.AssetRegistry.SearchAllAssets
// ()
// Parameters:
// bool                           bSynchronousSearch             (Parm, ZeroConstructor, IsPlainOldData)

void UAssetRegistry::SearchAllAssets(bool bSynchronousSearch)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistry.SearchAllAssets");

	UAssetRegistry_SearchAllAssets_Params params;
	params.bSynchronousSearch = bSynchronousSearch;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function AssetRegistry.AssetRegistry.ScanPathsSynchronous
// ()
// Parameters:
// TArray<class FString>          InPaths                        (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
// bool                           bForceRescan                   (Parm, ZeroConstructor, IsPlainOldData)

void UAssetRegistry::ScanPathsSynchronous(TArray<class FString> InPaths, bool bForceRescan)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistry.ScanPathsSynchronous");

	UAssetRegistry_ScanPathsSynchronous_Params params;
	params.InPaths = InPaths;
	params.bForceRescan = bForceRescan;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function AssetRegistry.AssetRegistry.ScanModifiedAssetFiles
// ()
// Parameters:
// TArray<class FString>          InFilePaths                    (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)

void UAssetRegistry::ScanModifiedAssetFiles(TArray<class FString> InFilePaths)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistry.ScanModifiedAssetFiles");

	UAssetRegistry_ScanModifiedAssetFiles_Params params;
	params.InFilePaths = InFilePaths;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function AssetRegistry.AssetRegistry.ScanFilesSynchronous
// ()
// Parameters:
// TArray<class FString>          InFilePaths                    (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
// bool                           bForceRescan                   (Parm, ZeroConstructor, IsPlainOldData)

void UAssetRegistry::ScanFilesSynchronous(TArray<class FString> InFilePaths, bool bForceRescan)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistry.ScanFilesSynchronous");

	UAssetRegistry_ScanFilesSynchronous_Params params;
	params.InFilePaths = InFilePaths;
	params.bForceRescan = bForceRescan;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function AssetRegistry.AssetRegistry.RunAssetsThroughFilter
// ()
// Parameters:
// TArray<struct FAssetData>      AssetDataList                  (Parm, OutParm, ZeroConstructor)
// struct FARFilter               Filter                         (ConstParm, Parm, OutParm, ReferenceParm)

void UAssetRegistry::RunAssetsThroughFilter(const struct FARFilter& Filter, TArray<struct FAssetData>* AssetDataList)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistry.RunAssetsThroughFilter");

	UAssetRegistry_RunAssetsThroughFilter_Params params;
	params.Filter = Filter;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (AssetDataList != nullptr)
		*AssetDataList = params.AssetDataList;
}


// Function AssetRegistry.AssetRegistry.PrioritizeSearchPath
// ()
// Parameters:
// class FString                  PathToPrioritize               (Parm, ZeroConstructor)

void UAssetRegistry::PrioritizeSearchPath(const class FString& PathToPrioritize)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistry.PrioritizeSearchPath");

	UAssetRegistry_PrioritizeSearchPath_Params params;
	params.PathToPrioritize = PathToPrioritize;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function AssetRegistry.AssetRegistry.IsLoadingAssets
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UAssetRegistry::IsLoadingAssets()
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistry.IsLoadingAssets");

	UAssetRegistry_IsLoadingAssets_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function AssetRegistry.AssetRegistry.HasAssets
// ()
// Parameters:
// struct FName                   PackagePath                    (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
// bool                           bRecursive                     (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UAssetRegistry::HasAssets(const struct FName& PackagePath, bool bRecursive)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistry.HasAssets");

	UAssetRegistry_HasAssets_Params params;
	params.PackagePath = PackagePath;
	params.bRecursive = bRecursive;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function AssetRegistry.AssetRegistry.GetSubPaths
// ()
// Parameters:
// class FString                  InBasePath                     (Parm, ZeroConstructor)
// TArray<class FString>          OutPathList                    (Parm, OutParm, ZeroConstructor)
// bool                           bInRecurse                     (Parm, ZeroConstructor, IsPlainOldData)

void UAssetRegistry::GetSubPaths(const class FString& InBasePath, bool bInRecurse, TArray<class FString>* OutPathList)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistry.GetSubPaths");

	UAssetRegistry_GetSubPaths_Params params;
	params.InBasePath = InBasePath;
	params.bInRecurse = bInRecurse;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (OutPathList != nullptr)
		*OutPathList = params.OutPathList;
}


// Function AssetRegistry.AssetRegistry.GetAssetsByPath
// ()
// Parameters:
// struct FName                   PackagePath                    (Parm, ZeroConstructor, IsPlainOldData)
// TArray<struct FAssetData>      OutAssetData                   (Parm, OutParm, ZeroConstructor)
// bool                           bRecursive                     (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bIncludeOnlyOnDiskAssets       (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UAssetRegistry::GetAssetsByPath(const struct FName& PackagePath, bool bRecursive, bool bIncludeOnlyOnDiskAssets, TArray<struct FAssetData>* OutAssetData)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistry.GetAssetsByPath");

	UAssetRegistry_GetAssetsByPath_Params params;
	params.PackagePath = PackagePath;
	params.bRecursive = bRecursive;
	params.bIncludeOnlyOnDiskAssets = bIncludeOnlyOnDiskAssets;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (OutAssetData != nullptr)
		*OutAssetData = params.OutAssetData;

	return params.ReturnValue;
}


// Function AssetRegistry.AssetRegistry.GetAssetsByPackageName
// ()
// Parameters:
// struct FName                   PackageName                    (Parm, ZeroConstructor, IsPlainOldData)
// TArray<struct FAssetData>      OutAssetData                   (Parm, OutParm, ZeroConstructor)
// bool                           bIncludeOnlyOnDiskAssets       (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UAssetRegistry::GetAssetsByPackageName(const struct FName& PackageName, bool bIncludeOnlyOnDiskAssets, TArray<struct FAssetData>* OutAssetData)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistry.GetAssetsByPackageName");

	UAssetRegistry_GetAssetsByPackageName_Params params;
	params.PackageName = PackageName;
	params.bIncludeOnlyOnDiskAssets = bIncludeOnlyOnDiskAssets;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (OutAssetData != nullptr)
		*OutAssetData = params.OutAssetData;

	return params.ReturnValue;
}


// Function AssetRegistry.AssetRegistry.GetAssetsByClass
// ()
// Parameters:
// struct FName                   ClassName                      (Parm, ZeroConstructor, IsPlainOldData)
// TArray<struct FAssetData>      OutAssetData                   (Parm, OutParm, ZeroConstructor)
// bool                           bSearchSubClasses              (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UAssetRegistry::GetAssetsByClass(const struct FName& ClassName, bool bSearchSubClasses, TArray<struct FAssetData>* OutAssetData)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistry.GetAssetsByClass");

	UAssetRegistry_GetAssetsByClass_Params params;
	params.ClassName = ClassName;
	params.bSearchSubClasses = bSearchSubClasses;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (OutAssetData != nullptr)
		*OutAssetData = params.OutAssetData;

	return params.ReturnValue;
}


// Function AssetRegistry.AssetRegistry.GetAssets
// ()
// Parameters:
// struct FARFilter               Filter                         (ConstParm, Parm, OutParm, ReferenceParm)
// TArray<struct FAssetData>      OutAssetData                   (Parm, OutParm, ZeroConstructor)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UAssetRegistry::GetAssets(const struct FARFilter& Filter, TArray<struct FAssetData>* OutAssetData)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistry.GetAssets");

	UAssetRegistry_GetAssets_Params params;
	params.Filter = Filter;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (OutAssetData != nullptr)
		*OutAssetData = params.OutAssetData;

	return params.ReturnValue;
}


// Function AssetRegistry.AssetRegistry.GetAssetByObjectPath
// ()
// Parameters:
// struct FName                   ObjectPath                     (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
// bool                           bIncludeOnlyOnDiskAssets       (Parm, ZeroConstructor, IsPlainOldData)
// struct FAssetData              ReturnValue                    (Parm, OutParm, ReturnParm)

struct FAssetData UAssetRegistry::GetAssetByObjectPath(const struct FName& ObjectPath, bool bIncludeOnlyOnDiskAssets)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistry.GetAssetByObjectPath");

	UAssetRegistry_GetAssetByObjectPath_Params params;
	params.ObjectPath = ObjectPath;
	params.bIncludeOnlyOnDiskAssets = bIncludeOnlyOnDiskAssets;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function AssetRegistry.AssetRegistry.GetAllCachedPaths
// ()
// Parameters:
// TArray<class FString>          OutPathList                    (Parm, OutParm, ZeroConstructor)

void UAssetRegistry::GetAllCachedPaths(TArray<class FString>* OutPathList)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistry.GetAllCachedPaths");

	UAssetRegistry_GetAllCachedPaths_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (OutPathList != nullptr)
		*OutPathList = params.OutPathList;
}


// Function AssetRegistry.AssetRegistry.GetAllAssets
// ()
// Parameters:
// TArray<struct FAssetData>      OutAssetData                   (Parm, OutParm, ZeroConstructor)
// bool                           bIncludeOnlyOnDiskAssets       (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UAssetRegistry::GetAllAssets(bool bIncludeOnlyOnDiskAssets, TArray<struct FAssetData>* OutAssetData)
{
	static auto fn = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistry.GetAllAssets");

	UAssetRegistry_GetAllAssets_Params params;
	params.bIncludeOnlyOnDiskAssets = bIncludeOnlyOnDiskAssets;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (OutAssetData != nullptr)
		*OutAssetData = params.OutAssetData;

	return params.ReturnValue;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

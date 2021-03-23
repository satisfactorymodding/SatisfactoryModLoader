// Editor Function Lib providing Utility Function for dynamic Content Creation.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "EngineUtils.h"
#include "runtime\Json\Public\Policies\PrettyJsonPrintPolicy.h"
#include "runtime\Json\Public\Policies\CondensedJsonPrintPolicy.h"
#include "UObject/UnrealType.h"
#include "Kismet2/KismetEditorUtilities.h" 
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet2/BlueprintEditorUtils.h" 
#include <string>
#include "GenericPlatform/GenericPlatformFile.h"
#include "Json.h"
// unlocks 
#include "Unlocks/FGUnlockRecipe.h"
#include "Unlocks/FGUnlockScannableResource.h"
#include "Unlocks/FGUnlockInventorySlot.h"
#include "Unlocks/FGUnlockArmEquipmentSlot.h"
// unlocks end
// schematics
#include "AvailabilityDependencies/FGItemPickedUpDependency.h"
#include "AvailabilityDependencies/FGSchematicPurchasedDependency.h"
#include "AvailabilityDependencies/FGRecipeUnlockedDependency.h"
#include "AvailabilityDependencies/FGGamePhaseReachedDependency.h"
#include "Unlocks/FGUnlockArmEquipmentSlot.h"
#include "Unlocks/FGUnlockBuildEfficiency.h"
#include "Unlocks/FGUnlockBuildOverclock.h"
#include "Unlocks/FGUnlockGiveItem.h"
#include "Unlocks/FGUnlockInventorySlot.h"
#include "Unlocks/FGUnlockMap.h"
#include "Unlocks/FGUnlockRecipe.h"
#include "Unlocks/FGUnlockScannableResource.h"
#include "Unlocks/FGUnlockSchematic.h"
#include "FGSchematicCategory.h"
// schematics end
// ResearchTree
#include "FGResearchTree.h"
// ResearhTree End
// Recipe 
#include "FGRecipe.h"
// recipe End
// Descriptor 
#include "Resources/FGItemDescriptor.h"
#include "FGItemCategory.h"
// Descriptor End
#include "EditorBlueprintFunctionLibrary.generated.h"


/**
 * 
 */
UCLASS()
class SMLEDITOR_API UEditorBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	template <class FunctorType>
	class PlatformFileFunctor : public IPlatformFile::FDirectoryVisitor	//GenericPlatformFile.h
	{
	public:

		virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override
		{
			return Functor(FilenameOrDirectory, bIsDirectory);
		}

		PlatformFileFunctor(FunctorType&& FunctorInstance)
			: Functor(MoveTemp(FunctorInstance))
		{
		}

	private:
		FunctorType Functor;
	};

	template <class Functor>
	static PlatformFileFunctor<Functor> MakeDirectoryVisitor(Functor&& FunctorInstance)
	{
		return PlatformFileFunctor<Functor>(MoveTemp(FunctorInstance));
	}


	static TSharedPtr<FJsonValue> convertUPropToJsonValue(UProperty* prop, void* ptrToProp);
	static FString SanitizeJsonString(FString write, bool some, bool RemoveOthers = false);
	static TSharedPtr<FJsonObject> convertUStructToJsonObject(UStruct* Struct, void* ptrToStruct);
	static TSharedPtr<FJsonObject> convertUStructToJsonObjectWithName(UStruct * Struct, void * ptrToStruct, FString Name);
	static void convertJsonObjectToUStruct(TSharedPtr<FJsonObject> json, UStruct* Struct, void* ptrToStruct);
	static void convertJsonValueToUProperty(TSharedPtr<FJsonValue> json, UProperty* prop, void* ptrToProp);
	static void InternalInsertIntoDataTable(UDataTable* DataTable, UStructProperty* Structure, void* StructurePtr, FString RowName);
	static void InternalGetStructAsJson(UStructProperty *Structure, void * StructurePtr, FString &String, FString Name);

	
	// Inserts a Struct into a Table ! Carefull very slow ! the Datatable needs to Reinsert every row ! 
	// Use Fill data Table from Json instead for Filling Tables with alot of Rows 
	UFUNCTION(BlueprintCallable, Category = "Editor| Json", CustomThunk, meta = (DataTable = "DataTable", CustomStructureParam = "Structure"))
		static void InsertIntoDataTable(FString RowName, UDataTable* DataTable, UProperty* Structure);
	
	// Formats a String in a way that lets you Add it to UDataTables ( they need RowNames ) 
	// UDataTableFunctionLibrary::FillDataTableFromJSONString will accept it under the following contions: 
	// The String Array still needs to be joined into a String with ',' as seperator and "[" pre-pended and "]" appended
	// Use GetStringFromArrayForTable(Array) to format or do it yourself.
	UFUNCTION(BlueprintCallable, Category = "EDitor | Json")
		static FString GetStringFromArrayForTable(const TArray<FString>& Array) { return FString("[").Append(FString::Join(Array,TEXT(","))).Append("]");}
	// Formats a Json String resulting from a Struct , in a Format Data Tables can accept ( Needs Row Name) 
	UFUNCTION(BlueprintCallable, Category = "Editor| Json", CustomThunk, meta = (CustomStructureParam = "Structure"))
		static void GetStructAsJsonForTable(FString RowName, UPARAM(ref)FString &String, UProperty *Structure);
	// Json String from Struct
	UFUNCTION(BlueprintCallable, Category = "Editor| Json", CustomThunk, meta = (CustomStructureParam = "Structure"))
		static void GetJsonAsStruct(const FString& String, UPARAM(ref) UProperty*& Structure);
	// Get Struct from Json
	UFUNCTION(BlueprintCallable, Category = "Editor| Json", CustomThunk, meta = (CustomStructureParam = "Structure"))
		static void GetStructAsJson(UPARAM(ref)FString &String, UProperty *Structure);

	DECLARE_FUNCTION(execInsertIntoDataTable)
	{
		//Grab the UDataTable Object from the Stack
		FString RowName;
		Stack.StepCompiledIn<UStrProperty>(&RowName);
		P_GET_OBJECT(UDataTable, DataTable);

		// Step into the stack
		Stack.Step(Stack.Object, NULL);

		// Grab the last property found when we walked the stack
		// This does not contains the property value, only its type information

		UStructProperty* StructureProperty = Cast<UStructProperty>(Stack.MostRecentProperty);


		// Grab the base address where the struct actually stores its data
		// This is where the property value is truly stored
		void* StructurePtr = Stack.MostRecentPropertyAddress;

		// We need this to wrap up the stack
		P_FINISH;

		//Now we have our data from the stack, lets internally update the data table
		InternalInsertIntoDataTable(DataTable, StructureProperty, StructurePtr, RowName);
	}
	DECLARE_FUNCTION(execGetStructAsJsonForTable)
	{
		FString RowName;
		Stack.StepCompiledIn<UStrProperty>(&RowName);
		PARAM_PASSED_BY_REF(String, UStrProperty, FString);
		Stack.Step(Stack.Object, NULL);

		UStructProperty* StructureProperty = Cast<UStructProperty>(Stack.MostRecentProperty);

		void* StructurePtr = Stack.MostRecentPropertyAddress;

		P_FINISH;
		InternalGetStructAsJson(StructureProperty, StructurePtr, String, RowName);
	}
	DECLARE_FUNCTION(execGetJsonAsStruct) {
		FString String;
		Stack.StepCompiledIn<UStrProperty>(&String);
		Stack.Step(Stack.Object, NULL);

		UStructProperty* Struct =  Cast<UStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;

		P_FINISH;

		TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(*String);
		FJsonSerializer Serializer;
		TSharedPtr<FJsonObject> result;
		Serializer.Deserialize(reader, result);
		convertJsonObjectToUStruct(result, Struct->Struct, StructPtr);
	}
	DECLARE_FUNCTION(execGetStructAsJson)
	{
		PARAM_PASSED_BY_REF(String, UStrProperty, FString);
		Stack.Step(Stack.Object, NULL);

		UStructProperty* StructureProperty =  Cast<UStructProperty>(Stack.MostRecentProperty);

		void* StructurePtr = Stack.MostRecentPropertyAddress;

		P_FINISH;
		InternalGetStructAsJson(StructureProperty, StructurePtr, String, "");
	}


	// can be used to create a Blueprint from provided Class
	// relative path is required for example :  "Game/ExampleMod"
	UFUNCTION(BlueprintCallable, Category = "Editor| File IO")
		static UObject * CreateBlueprintOfClass(UClass * Class, FString Name, FString Path);

	/** Obtain all files in a provided directory, with optional extension filter. All files are returned if Ext is left blank. Returns false if operation could not occur. */
	UFUNCTION(BlueprintPure, Category = "Editor| File IO")
		static bool FileIO_GetFiles(TArray<FString>& Files, FString RootFolderFullPath, FString Ext);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Victory Get All Files
	//  Optional File Extension Filter!!!  by Rama
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	UFUNCTION(BlueprintPure, Category = "Editor| File IO")
		static FORCEINLINE bool GetFiles(const FString& FullPathOfBaseDir, TArray<FString>& FilenamesOut, bool Recursive = false, const FString& FilterByExtension = "")
	{
		//Format File Extension, remove the "." if present
		const FString FileExt = FilterByExtension.Replace(TEXT("."), TEXT("")).ToLower();

		FString Str;
		auto FilenamesVisitor = MakeDirectoryVisitor(
			[&](const TCHAR* FilenameOrDirectory, bool bIsDirectory)
		{
			//Files
			if (!bIsDirectory)
			{
				//Filter by Extension
				if (FileExt != "")
				{
					Str = FPaths::GetCleanFilename(FilenameOrDirectory);

					//Filter by Extension
					if (FPaths::GetExtension(Str).ToLower() == FileExt)
					{
						if (Recursive)
						{
							FilenamesOut.Push(FilenameOrDirectory); //need whole path for recursive
						}
						else
						{
							FilenamesOut.Push(Str);
						}
					}
				}

				//Include All Filenames!
				else
				{
					//Just the Directory
					Str = FPaths::GetCleanFilename(FilenameOrDirectory);

					if (Recursive)
					{
						FilenamesOut.Push(FilenameOrDirectory); //need whole path for recursive
					}
					else
					{
						FilenamesOut.Push(Str);
					}
				}
			}
			return true;
		}
		);
		if (Recursive)
		{
			return FPlatformFileManager::Get().GetPlatformFile().IterateDirectoryRecursively(*FullPathOfBaseDir, FilenamesVisitor);
		}
		else
		{
			return FPlatformFileManager::Get().GetPlatformFile().IterateDirectory(*FullPathOfBaseDir, FilenamesVisitor);
		}
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Victory Get Directories
	//  Optional Search SubString!!!  by Rama
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Get Directories
	UFUNCTION(BlueprintPure, Category = "Editor| File IO")
		static FORCEINLINE bool GetDirectories(const FString& FullPathOfBaseDir, TArray<FString>& DirsOut, const FString&  NotContainsStr = "", bool Recursive = false, const FString& ContainsStr = "")
	{
		FString Str;
		FString Str2;

		auto FilenamesVisitor = MakeDirectoryVisitor(
			[&](const TCHAR* FilenameOrDirectory, bool bIsDirectory)
		{
			if (bIsDirectory)
			{
				//Using a Contains Filter?
				if (ContainsStr != "")
				{
					Str = FPaths::GetCleanFilename(FilenameOrDirectory);
					//Only if Directory Contains Str		
					if (Str.Contains(ContainsStr))
					{
						if (Recursive) DirsOut.Push(FilenameOrDirectory); //need whole path for recursive
						else DirsOut.Push(Str);
					}

				}
				else if (NotContainsStr != "") {
					if (!Str.Contains(NotContainsStr))
					{
						if (Recursive) DirsOut.Push(FilenameOrDirectory); //need whole path for recursive
						else DirsOut.Push(Str);
					}
				}
				//Get ALL Directories!
				else
				{
					//Just the Directory
					Str = FPaths::GetCleanFilename(FilenameOrDirectory);

					if (Recursive) DirsOut.Push(FilenameOrDirectory); //need whole path for recursive
					else DirsOut.Push(Str);
				}
			}
			return true;
		}
		);
		if (Recursive)
		{
			return FPlatformFileManager::Get().GetPlatformFile().IterateDirectoryRecursively(*FullPathOfBaseDir, FilenamesVisitor);
		}
		else
		{
			return FPlatformFileManager::Get().GetPlatformFile().IterateDirectory(*FullPathOfBaseDir, FilenamesVisitor);
		}
	}

	/*
		!!! CAREFULL ! REALLY SLOW !!!
		Path Like "/Game/FactoryGame/Resource" is expected
		leave UClass empty to get every BP
	*/
	UFUNCTION(BlueprintCallable, Category = "Editor| Class")
		static TArray<UObject*> GetBlueprintsFromPath(FString Path, UClass * Filter);

	// Helper Function for Editor Tools using Blueprints as UObjects. Without this BP Doesnt provide a way to resolve to class aside from via Name search.
	UFUNCTION(BlueprintCallable, Category = "Editor| Class")
		static UClass * GetClassGeneratedByBlueprint(UObject * Blueprint);


	// Road Position is the Center Location of a Line
	// CanvasStart is the Pivot Point
	// Size is the FVector2D(x = the distance to the Next Point, y = thickness)
	// Render Angle is the FromTo Direction Yaw
	UFUNCTION(BlueprintPure, Category = "Editor| ResearchTree")
		static void CalculateRoadPosition(FVector2D Start, FVector2D End, float Thickness, FVector2D &CanvasStart, FVector2D& Size, float& RenderAngle, float& InvertedRenderAngle);

	// SoftClasses from UObject Array
	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
		static TArray<TSoftClassPtr<UObject>> GetSoftClassFromObjects(TArray<UObject*> In);

	// SoftClasses from UClass Array
	UFUNCTION(BlueprintPure, Category = "Editor| Recipe")
		static TArray<TSoftClassPtr<UObject>> GetSoftClass(TArray<UClass*> In);

	// SoftClasses from Soft-Uobject Array
	UFUNCTION(BlueprintPure, Category = "Editor| Recipe")
		static TArray<UClass*> GetClassFromSoftPtr(TArray<TSoftClassPtr<UObject>> In);

};

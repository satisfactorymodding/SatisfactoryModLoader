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


// Structs for DataTables
USTRUCT(Blueprintable)
struct SMLEDITOR_API FItemDescriptorStruct
{
	GENERATED_BODY()

	FItemDescriptorStruct();
	FItemDescriptorStruct(TSubclassOf<class UFGItemDescriptor> inClass);

	bool operator==(TSubclassOf<class UFGItemDescriptor> inClass) {

		if (inClass.GetDefaultObject()->mDisplayName.ToString() != Name)
		{
			return false;
		}
		if (inClass.GetDefaultObject()->mForm != Form)
		{
			return false;
		}
		if (inClass.GetDefaultObject()->mStackSize != StackSize)
		{
			return false;
		}
		if (inClass.GetDefaultObject()->mRememberPickUp != RememberPickUp)
		{
			return false;
		}
		if (inClass.GetDefaultObject()->mCanBeDiscarded != CanBeDiscarded)
		{
			return false;
		}
		if (inClass.GetDefaultObject()->mEnergyValue != EnergyValue)
		{
			return false;
		}
		if (inClass.GetDefaultObject()->mRadioactiveDecay != RadioactiveDecay)
		{
			return false;
		}
		if (inClass.GetDefaultObject()->mFluidColor != FluidColor)
		{
			return false;
		}
		if (inClass.GetDefaultObject()->mItemCategory != Category)
		{
			return false;
		}

		if (inClass.GetDefaultObject()->mSmallIcon != IconSmall)
		{
			return false;
		}
		if (inClass.GetDefaultObject()->mPersistentBigIcon != IconBig)
		{
			return false;
		}

		return true;
	}
	bool operator==(FItemDescriptorStruct inClass) {

		if (inClass.Name != Name)
		{
			return false;
		}
		if (inClass.Form != Form)
		{
			return false;
		}
		if (inClass.StackSize != StackSize)
		{
			return false;
		}
		if (inClass.RememberPickUp != RememberPickUp)
		{
			return false;
		}
		if (inClass.CanBeDiscarded != CanBeDiscarded)
		{
			return false;
		}
		if (inClass.EnergyValue != EnergyValue)
		{
			return false;
		}
		if (inClass.RadioactiveDecay != RadioactiveDecay)
		{
			return false;
		}
		if (inClass.FluidColor != FluidColor)
		{
			return false;
		}
		if (inClass.Category != Category)
		{
			return false;
		}

		if (inClass.IconSmall != IconSmall)
		{
			return false;
		}
		if (inClass.IconBig != IconBig)
		{
			return false;
		}

		return true;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		EResourceForm Form;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		EStackSize StackSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool RememberPickUp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool CanBeDiscarded;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float EnergyValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float RadioactiveDecay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FColor FluidColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<class UFGItemDescriptor> Class;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<class UFGItemCategory> Category;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMesh * GroundMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UTexture2D * IconSmall;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UTexture2D * IconBig;

};

USTRUCT(Blueprintable)
struct SMLEDITOR_API FSchematicStruct
{
	GENERATED_BODY()

	FSchematicStruct();
	FSchematicStruct(TSubclassOf<class UFGSchematic> inClass);

	bool operator==(FSchematicStruct inClass) {
		if (inClass.Class != Class)
		{
			return false;
		}
		if (inClass.mDisplayName != mDisplayName)
		{
			return false;
		}
		if (inClass.mType != mType)
		{
			return false;
		}
		if (inClass.mTechTier != mTechTier)
		{
			return false;
		}
		if (inClass.mSchematicCategory != mSchematicCategory)
		{
			return false;
		}
		if (inClass.mSubCategories != mSubCategories)
		{
			return false;
		}
		if (inClass.mTimeToComplete != mTimeToComplete)
		{
			return false;
		}
		if (inClass.mSchematicIcon != mSchematicIcon)
		{
			return false;
		}
		if (CompareCost(inClass.mCost))
		{
			return false;
		}
		if (inClass.mUnlocks != mUnlocks)
		{
			for (int32 i = 0; i < inClass.mUnlocks.Num(); i++)
			{
				if (!inClass.mUnlocks.IsValidIndex(i) || !mUnlocks.IsValidIndex(i))
					return false;

				//UFGUnlockArmEquipmentSlot
				{
					UFGUnlockArmEquipmentSlot * A = Cast< UFGUnlockArmEquipmentSlot>(mUnlocks[i]);
					UFGUnlockArmEquipmentSlot * B = Cast< UFGUnlockArmEquipmentSlot>(inClass.mUnlocks[i]);
					if (A && !B || !A && B)
						return false;
					else if (A && B)
					{
						int32 A_ = A->GetNumArmEquipmentSlotsToUnlock();
						int32 B_ = B->GetNumArmEquipmentSlotsToUnlock();
						if (A_ != B_)
							return false;
					}

				}
				//UFGUnlockInventorySlot
				{
					UFGUnlockInventorySlot * A = Cast< UFGUnlockInventorySlot>(mUnlocks[i]);
					UFGUnlockInventorySlot * B = Cast< UFGUnlockInventorySlot>(inClass.mUnlocks[i]);
					if (A && !B || !A && B)
						return false;
					else if (A && B)
					{
						int32 A_ = A->GetNumInventorySlotsToUnlock();
						int32 B_ = B->GetNumInventorySlotsToUnlock();
						if (A_ != B_)
							return false;
					}

				}
				//UFGUnlockBuildEfficiency
				{
					UFGUnlockBuildEfficiency * A = Cast< UFGUnlockBuildEfficiency>(mUnlocks[i]);
					UFGUnlockBuildEfficiency * B = Cast< UFGUnlockBuildEfficiency>(inClass.mUnlocks[i]);
					if (A && !B || !A && B)
						return false;
				}
				//UFGUnlockBuildOverclock
				{
					UFGUnlockBuildOverclock * A = Cast< UFGUnlockBuildOverclock>(mUnlocks[i]);
					UFGUnlockBuildOverclock * B = Cast< UFGUnlockBuildOverclock>(inClass.mUnlocks[i]);
					if (A && !B || !A && B)
						return false;
				}
				//UFGUnlockMap
				{
					UFGUnlockMap * A = Cast< UFGUnlockMap>(mUnlocks[i]);
					UFGUnlockMap * B = Cast< UFGUnlockMap>(inClass.mUnlocks[i]);
					if (A && !B || !A && B)
						return false;
				}

				//UFGUnlockGiveItem
				{
					UFGUnlockGiveItem * A = Cast< UFGUnlockGiveItem>(mUnlocks[i]);
					UFGUnlockGiveItem * B = Cast< UFGUnlockGiveItem>(inClass.mUnlocks[i]);
					if (A && !B || !A && B)
						return false;

					if (A && B)
					{
						TArray< FItemAmount > A_ = A->GetItemsToGive();
						TArray< FItemAmount > B_ = B->GetItemsToGive();
						if (A_.Num() != B_.Num())
							return false;
						for (int32 j = 0; j < A_.Num(); j++)
						{
							if (!B_.IsValidIndex(j))
								return false;

							if (B_[j].Amount != mCost[j].Amount || B_[j].ItemClass != mCost[j].ItemClass)
								return false;
						}
					}
				}
				//UFGUnlockRecipe
				{
					UFGUnlockRecipe * A = Cast< UFGUnlockRecipe>(mUnlocks[i]);
					UFGUnlockRecipe * B = Cast< UFGUnlockRecipe>(inClass.mUnlocks[i]);
					if (A && !B || !A && B)
						return false;
					else if (A && B)
					{
						TArray< TSubclassOf< class UFGRecipe > > A_ = A->GetRecipesToUnlock();
						TArray< TSubclassOf< class UFGRecipe > > B_ = B->GetRecipesToUnlock();
						if (A_ != B_)
							return false;
					}
				}
				//UFGUnlockScannableResource
				{
					UFGUnlockScannableResource * A = Cast< UFGUnlockScannableResource>(mUnlocks[i]);
					UFGUnlockScannableResource * B = Cast< UFGUnlockScannableResource>(inClass.mUnlocks[i]);
					if (A && !B || !A && B)
						return false;
					else if (A && B)
					{
						TArray< FScannableResourcePair > A_ = A->GetResourcesToAddToScanner();
						TArray< FScannableResourcePair > B_ = B->GetResourcesToAddToScanner();
						if (A != B)
							return false;
					}

				}
				//UFGUnlockSchematic
				{
					UFGUnlockSchematic * A = Cast< UFGUnlockSchematic>(mUnlocks[i]);
					UFGUnlockSchematic * B = Cast< UFGUnlockSchematic>(inClass.mUnlocks[i]);
					if (A && !B || !A && B)
						return false;
					else if (A && B)
					{
						TArray < TSubclassOf< class UFGSchematic > > A_ = A->GetSchematicsToUnlock();
						TArray < TSubclassOf< class UFGSchematic > > B_ = B->GetSchematicsToUnlock();
						if (A != B)
							return false;
					}

				}

			}
		}
		if (inClass.mSchematicDependencies != mSchematicDependencies)
		{
			for (int32 i = 0; i < inClass.mSchematicDependencies.Num(); i++)
			{
				//UFGItemPickedUpDependency
				{
					UFGItemPickedUpDependency * A = Cast< UFGItemPickedUpDependency>(inClass.mSchematicDependencies[i]);
					UFGItemPickedUpDependency * B = Cast< UFGItemPickedUpDependency>(inClass.mSchematicDependencies[i]);
					if (A && !B || !A && B)
						return false;
					else if (A && B)
					{
						TArray< TSubclassOf< class UFGItemDescriptor > > A_; A->GetItems(A_);
						TArray< TSubclassOf< class UFGItemDescriptor > > B_; B->GetItems(B_);
						if (A_ != B_)
							return false;
					}
				}
				//UFGSchematicPurchasedDependency
				{
					UFGSchematicPurchasedDependency * A = Cast< UFGSchematicPurchasedDependency>(inClass.mSchematicDependencies[i]);
					UFGSchematicPurchasedDependency * B = Cast< UFGSchematicPurchasedDependency>(inClass.mSchematicDependencies[i]);

					if (A && !B || !A && B)
						return false;

					if (A && B)
					{
						TArray< TSubclassOf< class UFGSchematic > > A_; A->GetSchematics(A_);
						TArray< TSubclassOf< class UFGSchematic > > B_; B->GetSchematics(B_);
						if (A_ != B_)
							return false;
					}

				}
				//UFGRecipeUnlockedDependency
				{
					UFGRecipeUnlockedDependency * A = Cast< UFGRecipeUnlockedDependency>(inClass.mSchematicDependencies[i]);
					UFGRecipeUnlockedDependency * B = Cast< UFGRecipeUnlockedDependency>(inClass.mSchematicDependencies[i]);
					if (A && !B || !A && B)
						return false;
					if (A && B)
					{
						TArray< TSubclassOf< class UFGRecipe > > A_; A->GetRecipes(A_);
						TArray< TSubclassOf< class UFGRecipe > > B_; B->GetRecipes(B_);
						if (A_ != B_)
							return false;
					}


				}
				//UFGGamePhaseReachedDependency
				{
					UFGGamePhaseReachedDependency * A = Cast< UFGGamePhaseReachedDependency>(inClass.mSchematicDependencies[i]);
					UFGGamePhaseReachedDependency * B = Cast< UFGGamePhaseReachedDependency>(inClass.mSchematicDependencies[i]);
					if (A && !B || !A && B)
						return false;
					if (A && B)
					{
						EGamePhase A_ = A->GetGamePhase();
						EGamePhase B_ = B->GetGamePhase();
						if (A_ != B_)
							return false;
					}

				}

			}
			return false;
		}

		return true;
	}

	bool operator==(TSubclassOf<class UFGSchematic> inClass) {
		return *this == FSchematicStruct(inClass);
	}

	bool CompareCost(TArray< FItemAmount > ProductsIn)
	{
		if (mCost.Num() != ProductsIn.Num())
			return false;
		for (int32 i = 0; i < mCost.Num(); i++)
		{
			if (!ProductsIn.IsValidIndex(i))
				return false;

			if (ProductsIn[i].Amount != mCost[i].Amount || ProductsIn[i].ItemClass != mCost[i].ItemClass)
				return false;
		}
		return true;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<class UFGSchematic> Class;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FString mDisplayName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		ESchematicType mType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 mTechTier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<class UFGSchematicCategory>  mSchematicCategory;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray < TSubclassOf<class UFGSchematicCategory>> mSubCategories;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray< FItemAmount > mCost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float mTimeToComplete;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray< class UFGUnlock* > mUnlocks;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FSlateBrush mSchematicIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray< class UFGAvailabilityDependency* > mSchematicDependencies;

};

USTRUCT(Blueprintable)
struct SMLEDITOR_API FRecipeStruct
{
	GENERATED_BODY()

		FRecipeStruct();
	FRecipeStruct(TSubclassOf<class UFGRecipe> inClass);

	bool operator==(FRecipeStruct inClass) {

		if (inClass.Name != Name)
		{
			return false;
		}
		if (inClass.Class != Class)
		{
			return false;
		}
		if (inClass.ManufactoringDuration != ManufactoringDuration)
		{
			return false;
		}
		if (inClass.ManualManufacturingMultiplier != ManualManufacturingMultiplier)
		{
			return false;
		}
		if (inClass.mProducedIn != mProducedIn)
		{
			return false;
		}
		if (CompareProducts(inClass.Ingredients))
		{
			return false;
		}
		if (CompareProducts(inClass.Products))
		{
			return false;
		}

		return true;
	}

	bool operator==(TSubclassOf<class UFGRecipe> inClass) {
		return *this == FRecipeStruct(inClass);
	}

	bool CompareProducts(TArray< FItemAmount > ProductsIn)
	{
		for (int32 i = 0; i < Products.Num(); i++)
		{
			if (!ProductsIn.IsValidIndex(i))
				return false;

			if (ProductsIn[i].Amount != Products[i].Amount || ProductsIn[i].ItemClass != Products[i].ItemClass)
				return false;
		}
		return true;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<class UFGRecipe> Class;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray< FItemAmount > Ingredients;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray< FItemAmount > Products;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float ManufactoringDuration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float ManualManufacturingMultiplier;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray< TSoftClassPtr< UObject > > mProducedIn;

};

// Structs End

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



	// Unlock Class
	UFUNCTION(BlueprintCallable, Category = "Editor|Unlock")
		static void InitRecipeUnlocks(UFGUnlockRecipe * Obj, TArray< TSubclassOf< class UFGRecipe > > recipes) { Obj->Init(recipes); };
	UFUNCTION(BlueprintCallable, Category = "Editor|Unlock")
		static void InitScannableUnlocks(UFGUnlockScannableResource * Obj, TArray< TSubclassOf< class UFGResourceDescriptor > > descriptor) { Obj->mResourcesToAddToScanner = descriptor; };
	UFUNCTION(BlueprintCallable, Category = "Editor|Unlock")
		static void InitUnlockInventorySlot(UFGUnlockInventorySlot * Obj, int32 count) { Obj->Init(count); };
	UFUNCTION(BlueprintCallable, Category = "Editor|Unlock")
		static void InitUnlockArmEquipmentSlot(UFGUnlockArmEquipmentSlot * Obj, int32 count) { Obj->Init(count); };


	// Research Tree
	UFUNCTION(BlueprintCallable, Category = "Editor| ResearchTree")
		static void SetRecipeDisplayName(TSubclassOf < UFGResearchTree>  Obj, FText mDisplayName) { Obj.GetDefaultObject()->mDisplayName = mDisplayName; Obj->MarkPackageDirty(); };
	UFUNCTION(BlueprintCallable, Category = "Editor| ResearchTree")
		static void SetPreUnlockDisplayName(TSubclassOf < UFGResearchTree>  Obj, FText mPreUnlockDisplayName) { Obj.GetDefaultObject()->mPreUnlockDisplayName = mPreUnlockDisplayName; Obj->MarkPackageDirty(); };
	UFUNCTION(BlueprintCallable, Category = "Editor| ResearchTree")
		static void SetPreUnlockDescription(TSubclassOf < UFGResearchTree>  Obj, FText mPreUnlockDescription) { Obj.GetDefaultObject()->mPreUnlockDescription = mPreUnlockDescription; Obj->MarkPackageDirty(); };
	UFUNCTION(BlueprintCallable, Category = "Editor| ResearchTree")
		static void SetPostUnlockDescription(TSubclassOf < UFGResearchTree> Obj, FText mPostUnlockDescription) { Obj.GetDefaultObject()->mPostUnlockDescription = mPostUnlockDescription; Obj->MarkPackageDirty(); };
	UFUNCTION(BlueprintCallable, Category = "Editor| ResearchTree")
		static void SetResearchTreeIcon(TSubclassOf < UFGResearchTree>  Obj, FSlateBrush mResearchTreeIcon) { Obj.GetDefaultObject()->mResearchTreeIcon = mResearchTreeIcon; Obj->MarkPackageDirty(); };


	// Research Tree Nodes use Coordinates but Offset Y Coods depending on if Column Number is %2 = 1 or not 
	// depending on GridSize(alternatively the Node Widget Size)  Coordinates on Canvas are returned
	// (Works but could use improvement // for now better than nothing) 
	UFUNCTION(BlueprintPure, Category = "Editor| ResearchTree")
		static FVector2D ResearchTreeCoordinateToCanvasPosition(int32 X, int32 Y, int32 GridSize)
	{
		return FVector2D(X * GridSize, (Y * GridSize) + (X % 2 > 0 ? GridSize / 2 : GridSize)) - (GridSize / 8);
	}
	// Roads follow the same Column Offset paradigm
	UFUNCTION(BlueprintPure, Category = "Editor| ResearchTree")
		static FVector2D ResearchTreeRoadCoordinateToCanvasPosition(int32 X, int32 Y, int32 OtherX, int32 GridSize, bool IsStart)
	{
		float newXOffset = (GridSize / 4); bool mod = X % 2 > 0;
		return FVector2D((X * GridSize) + newXOffset, (Y * GridSize) + (mod ? (newXOffset * 2) : (newXOffset * 4)) + (mod ? (IsStart ? 3.f : 2.f) * newXOffset : ((IsStart ? 3.f : (X == OtherX ? 2.f : 3.f)) * newXOffset)));
	}

	// Find a node using a specific Schematic, First usage Instance returned
	UFUNCTION(BlueprintPure, Category = "Editor| ResearchTree")
		static UFGResearchTreeNode * GetNodeForSchematic(TSubclassOf<class UFGResearchTree> Tree, TSubclassOf<class UFGSchematic> Schematic)
	{
		for (auto Node : Tree.GetDefaultObject()->mNodes)
		{
			UProperty *  uprop = Node->GetClass()->FindPropertyByName(TEXT("mNodeDataStruct"));
			UStructProperty *  structProp = Cast<UStructProperty>(uprop);
			if (structProp)
			{
				for (auto prop = TFieldIterator<UProperty>(structProp->Struct); prop; ++prop) {
					UClassProperty * SchematicProp = Cast<UClassProperty>(*prop);
					if (SchematicProp)
					{
						void* LoadedObject = prop->ContainerPtrToValuePtr<void>(structProp);
						UClass * CastResult = Cast<UClass>(SchematicProp->GetPropertyValue(LoadedObject));
						if (CastResult)
						{
							if (CastResult == Schematic)
							{
								return Node;
							}
							else
							{
								break;

							}
						}
					}
				}
			}
		}
		return nullptr;
	}

	// Road Position is the Center Location of a Line
	// CanvasStart is the Pivot Point
	// Size is the FVector2D(x = the distance to the Next Point, y = thickness)
	// Render Angle is the FromTo Direction Yaw
	UFUNCTION(BlueprintPure, Category = "Editor| ResearchTree")
		static void CalculateRoadPosition(FVector2D Start, FVector2D End, float Thickness, FVector2D &CanvasStart, FVector2D& Size, float& RenderAngle, float& InvertedRenderAngle);

	// Research Tree End


	// Schematic 

	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
		static void SetDisplayName(TSubclassOf< UFGSchematic > inClass, FText Name) { inClass.GetDefaultObject()->mDisplayName = Name; inClass->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
		static void SetType(TSubclassOf< UFGSchematic > inClass, ESchematicType Type) { inClass.GetDefaultObject()->mType = Type; inClass->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
		static void SetTechTier(TSubclassOf< UFGSchematic > inClass, int32 Tier) { inClass.GetDefaultObject()->mTechTier = Tier; inClass->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
		static void SetSchemCategory(TSubclassOf< UFGSchematic > inClass, TSubclassOf<class UFGSchematicCategory> Cat) { inClass.GetDefaultObject()->mSchematicCategory = Cat; inClass->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
		static void SetSubCategories(TSubclassOf< UFGSchematic > inClass, TArray < TSubclassOf<class UFGSchematicCategory>> Cat) { inClass.GetDefaultObject()->mSubCategories = Cat; inClass->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
		static void SetCost(TSubclassOf< UFGSchematic > inClass, TArray<FItemAmount> Cost) { inClass.GetDefaultObject()->mCost = Cost; inClass->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
		static void SetTimeToComplete(TSubclassOf< UFGSchematic > inClass, float sec) { inClass.GetDefaultObject()->mTimeToComplete = sec; inClass->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
		static void SetUnlocks(TSubclassOf< UFGSchematic > inClass, TArray< class UFGUnlock* > Unlocks) { inClass.GetDefaultObject()->mUnlocks = Unlocks; inClass->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
		static void SetSchematicIcon(TSubclassOf< UFGSchematic > inClass, FSlateBrush Icon) { inClass.GetDefaultObject()->mSchematicIcon = Icon; inClass->MarkPackageDirty(); }

	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
		static void SetDependsOnSchematic(TSubclassOf< UFGSchematic > inClass, TArray< class UFGAvailabilityDependency* > Deps) { inClass.GetDefaultObject()->mSchematicDependencies = Deps; inClass->MarkPackageDirty(); }


	UFUNCTION(BlueprintCallable, Category = "Editor| Schematics")
		static void InitSchematicPurchaseDep(UFGSchematicPurchasedDependency * selfref, TArray< TSubclassOf< class UFGSchematic > > schematics, bool requireAllSchematicsToBePurchased);

	UFUNCTION(BlueprintCallable, Category = "Editor| Schematics")
		static void GetSchematicDependencies(TSubclassOf< UFGSchematic > inClass, UPARAM(ref) TArray<  UFGAvailabilityDependency* >& out_schematicDependencies);

	// Fills and returns all Struct generated from a Input Schematic
	UFUNCTION(BlueprintPure, Category = "Editor| Schematics")
		static FSchematicStruct GetStructFromSchematic(TSubclassOf<UFGSchematic> inClass) { return FSchematicStruct(inClass); }
	
	// CAREFULL ! this will modify the BP the Class belongs to and applies all Settings from the provided Struct
	// Blueprint is Marked Dirty and will need saving afterwards!
	// to abandon ( revert ) changes Restart the editor !without! saving changes.
	// after saving the BP - there is no option to automatically reverse changes !
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematics")
		static void SetSchematicFromStruct(FSchematicStruct Struct);

	/** Returns true if FSchematicStruct A is equal to FSchematicStruct B (A == B)*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (SchematicStruct)", CompactNodeTitle = "==", ScriptMethod = "Equals", ScriptOperator = "==", Keywords = "== equal"), Category = "Editor| Schematics")
		static bool EqualEqual_FSchematicStructFSchematicStruct(FSchematicStruct A, FSchematicStruct B);
	/** Returns true if FSchematicStruct A is equal to the generated FSchematicStruct from a UFGSchematic B (A == B)*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (UFGSchematic)", CompactNodeTitle = "==", ScriptMethod = "Equals", ScriptOperator = "==", Keywords = "== equal"), Category = "Editor| Schematics")
		static bool EqualEqual_FSchematicStructUFGSchematic(FSchematicStruct A, TSubclassOf<class UFGSchematic> B);

	// Schematic End

	// Recipes

	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
		static void SetRecipeName(TSubclassOf<UFGRecipe> recipe, FText Name) { recipe.GetDefaultObject()->mDisplayName = Name; recipe->MarkPackageDirty(); };
	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
		static void SetIngredient(TSubclassOf<UFGRecipe> recipe, TArray<FItemAmount> ingredient) { recipe.GetDefaultObject()->mIngredients = ingredient; recipe->MarkPackageDirty(); };
	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
		static void SetProduct(TSubclassOf< UFGRecipe > recipe, TArray< FItemAmount > product) { recipe.GetDefaultObject()->mProduct = product; recipe->MarkPackageDirty(); };
	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
		static void SetManufactoringDuration(TSubclassOf<UFGRecipe> recipe, float sec) { recipe.GetDefaultObject()->mManufactoringDuration = sec; recipe->MarkPackageDirty(); };
	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
		static void SetManualManufacturingMultiplier(TSubclassOf<UFGRecipe> recipe, float val) { recipe.GetDefaultObject()->mManualManufacturingMultiplier = val; recipe->MarkPackageDirty(); };
	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
		static void SetProducedIn(TSubclassOf<UFGRecipe> recipe, TArray< TSoftClassPtr< UObject > > mProducedIn) { recipe.GetDefaultObject()->mProducedIn = mProducedIn; recipe->MarkPackageDirty(); };


	// didnt fully test those function but otherwise not possible to do in BP

	// SoftClasses from UObject Array
	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
		static TArray<TSoftClassPtr<UObject>> GetSoftClassFromObjects(TArray<UObject*> In);

	// SoftClasses from UClass Array
	UFUNCTION(BlueprintPure, Category = "Editor| Recipe")
		static TArray<TSoftClassPtr<UObject>> GetSoftClass(TArray<UClass*> In);

	// SoftClasses from Soft-Uobject Array
	UFUNCTION(BlueprintPure, Category = "Editor| Recipe")
		static TArray<UClass*> GetClassFromSoftPtr(TArray<TSoftClassPtr<UObject>> In);

	// Fills and returns all Struct generated from a Input Recipe
	UFUNCTION(BlueprintPure, Category = "Editor| Recipe")
		static FRecipeStruct GetStructFromRecipe(TSubclassOf<UFGRecipe> inClass) { return FRecipeStruct(inClass); }

	// CAREFULL ! this will modify the BP the Class belongs to and applies all Settings from the provided Struct
	// Blueprint is Marked Dirty and will need saving afterwards!
	// to abandon ( revert ) changes Restart the editor !without! saving changes.
	// after saving the BP - there is no option to automatically reverse changes !
	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
		static void SetRecipeFromStruct(TSubclassOf<UFGRecipe> inClass, FRecipeStruct Struct);

	/** Returns true if FRecipeStruct A is equal to FRecipeStruct B (A == B)*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (RecipeStruct)", CompactNodeTitle = "==", ScriptMethod = "Equals", ScriptOperator = "==", Keywords = "== equal"), Category = "Editor| Schematics")
		static bool EqualEqual_FRecipeStructFRecipeStruct(FRecipeStruct A, FRecipeStruct B);
	/** Returns true if FRecipeStruct A is equal to the generated FRecipeStruct from a UFGSchematic B (A == B)*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (UFGSchematic)", CompactNodeTitle = "==", ScriptMethod = "Equals", ScriptOperator = "==", Keywords = "== equal"), Category = "Editor| Schematics")
		static bool EqualEqual_FRecipeStructUFGRecipe(FRecipeStruct A, TSubclassOf<class UFGRecipe> B);


// Recipes End

	// Descriptor


	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetUseName(TSubclassOf< UFGItemDescriptor > item, bool UseName) { item.GetDefaultObject()->mUseDisplayNameAndDescription = UseName; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetName(TSubclassOf< UFGItemDescriptor > item, FText Name) { item.GetDefaultObject()->mDisplayName = Name; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetDescription(TSubclassOf< UFGItemDescriptor > item, FText Name) { item.GetDefaultObject()->mDescription = Name; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetMesh(TSubclassOf< UFGItemDescriptor > item, UStaticMesh * Mesh) { item.GetDefaultObject()->mConveyorMesh = Mesh; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetMaterial(TSubclassOf< UFGItemDescriptor > item, UMaterialInterface * Mat) { item.GetDefaultObject()->mConveyorMesh->SetMaterial(0, Mat); item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetBigIcon(TSubclassOf<UFGItemDescriptor> item, UTexture2D *Icon) { item.GetDefaultObject()->mPersistentBigIcon = Icon; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetSmallIcon(TSubclassOf<UFGItemDescriptor> item, UTexture2D *Icon) { item.GetDefaultObject()->mSmallIcon = Icon; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetFluidColor(TSubclassOf<UFGItemDescriptor> item, FColor  Value) { item.GetDefaultObject()->mFluidColor = Value; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetForm(TSubclassOf<UFGItemDescriptor> item, EResourceForm  Value) { item.GetDefaultObject()->mForm = Value; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetCategory(TSubclassOf<UFGItemDescriptor> item, TSubclassOf<UFGItemCategory>  Value) { item.GetDefaultObject()->mItemCategory = Value; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetCanbeDisgarded(TSubclassOf<UFGItemDescriptor> item, bool  Value) { item.GetDefaultObject()->mCanBeDiscarded = Value; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetRememberPickUp(TSubclassOf<UFGItemDescriptor> item, bool  Value) { item.GetDefaultObject()->mRememberPickUp = Value; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetEnergyValue(TSubclassOf<UFGItemDescriptor> item, float  Value) { item.GetDefaultObject()->mEnergyValue = Value; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetRadioactiveDecay(TSubclassOf<UFGItemDescriptor> item, float  Value) { item.GetDefaultObject()->mRadioactiveDecay = Value; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetStackSize(TSubclassOf<UFGItemDescriptor> item, EStackSize  Value) { item.GetDefaultObject()->mStackSize = Value; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintPure, Category = "Editor| Item")
		static EStackSize GetStackSize(TSubclassOf<UFGItemDescriptor> item) { return item.GetDefaultObject()->mStackSize; }


	// Fills and returns all Struct generated from a Input ItemDescriptor
	UFUNCTION(BlueprintPure, Category = "Editor| Item")
		static FItemDescriptorStruct GetStructFromDescriptor(TSubclassOf<UFGItemDescriptor> inClass) { return FItemDescriptorStruct(inClass); }
	
	// CAREFULL ! this will modify the BP the Class belongs to and applies all Settings from the provided Struct
	// Blueprint is Marked Dirty and will need saving afterwards!
	// to abandon ( revert ) changes Restart the editor !without! saving changes.
	// after saving the BP - there is no option to automatically reverse changes !
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetDescriptorFromStruct(TSubclassOf<UFGItemDescriptor> inClass, FItemDescriptorStruct Struct);

	/** Returns true if FItemDescriptorStruct A is equal to FItemDescriptorStruct B (A == B)*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (DescriptorStruct)", CompactNodeTitle = "==", ScriptMethod = "Equals", ScriptOperator = "==", Keywords = "== equal"), Category = "Editor| Item")
		static bool EqualEqual_FDescriptorStructFDescriptorStruct(FItemDescriptorStruct A, FItemDescriptorStruct B);
	/** Returns true if FItemDescriptorStruct A is equal to the generated FItemDescriptorStruct from a UFGItemDescriptor B (A == B)*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (UFGItemDescriptor)", CompactNodeTitle = "==", ScriptMethod = "Equals", ScriptOperator = "==", Keywords = "== equal"), Category = "Editor| Item")
		static bool EqualEqual_FDescriptorStructUFGItemDescriptor(FItemDescriptorStruct A, TSubclassOf<class UFGItemDescriptor> B);

	// Descriptor End
};

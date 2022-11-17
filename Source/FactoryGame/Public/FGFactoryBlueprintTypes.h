// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Resources/FGBuildDescriptor.h"
#include "FGCategory.h"
#include "FGInventoryComponent.h"
#include "Resources/FGItemDescriptor.h"
#include "ItemAmount.h"
#include "FGFactoryBlueprintTypes.generated.h"

struct FACTORYGAME_API FBlueprintConfigVersion
{
	enum Type
	{
		InitialVersion,
		AddedMD5Hash,
		RemovedMD5Hash,
		VersionPlusOne,
		LatestVersion = VersionPlusOne - 1
	};

	inline static const FGuid GUID = FGuid( 0x23A43E21, 0x13361FD2, 0x123B9F51, 0x7936B131 );
};


USTRUCT( BlueprintType )
struct FBlueprintSubCategoryRecord
{
	GENERATED_BODY()
public:
	UPROPERTY( SaveGame )
	FString SubCategoryName;

	UPROPERTY( SaveGame )
	float MenuPriority;

	UPROPERTY( SaveGame )
	uint8 IsUndefined;

	UPROPERTY( SaveGame )
	TArray< FString > BlueprintNames;
};

USTRUCT( BlueprintType )
struct FBlueprintCategoryRecord
{
	GENERATED_BODY()
public:
	UPROPERTY( SaveGame )
	FString CategoryName;

	UPROPERTY( SaveGame )
	int32 IconID;

	UPROPERTY( SaveGame )
	float MenuPriority;
	
	UPROPERTY( SaveGame )
	uint8 IsUndefined :1;

	UPROPERTY( SaveGame )
	TArray< FBlueprintSubCategoryRecord > SubCategoryRecords;
};

USTRUCT( BlueprintType )
struct FBlueprintRecord
{
	GENERATED_BODY()
public:
	FBlueprintRecord() :
		BlueprintName( "" ),
		BlueprintDescription( "" ),
		IconID( -1 ),
		Color( FLinearColor::Black ),
		Category( nullptr ),
		SubCategory( nullptr ),
		Priority( 0 ),
		ConfigVersion( FBlueprintConfigVersion::InitialVersion )
	{}

	bool IsValid() const { return !BlueprintName.IsEmpty(); }
	
	UPROPERTY( BlueprintReadWrite, Category="Blueprint Record")
	FString BlueprintName;

	UPROPERTY( BlueprintReadWrite, Category="Blueprint Record")
	FString BlueprintDescription;

	UPROPERTY( BlueprintReadWrite, Category="Blueprint Record")
	int32 IconID;

	UPROPERTY( BlueprintReadWrite, Category="Blueprint Record")
	FLinearColor Color;
	
	UPROPERTY(BlueprintReadWrite, Category="Blueprint Record" )
	class UFGBlueprintCategory* Category;

	UPROPERTY(BlueprintReadWrite, Category="Blueprint Record" )
	class UFGBlueprintSubCategory* SubCategory;

	UPROPERTY(BlueprintReadWrite, Category="Blueprint Record" )
	int32 Priority;
	
	int32 ConfigVersion;
	
	friend FArchive& operator<< ( FArchive& ar, FBlueprintRecord& record );
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FBlueprintItemAmount
{
	GENERATED_BODY()


	FBlueprintItemAmount() :
		ItemClass( nullptr ),
		Amount( 0 )
	{
	}

	explicit  FBlueprintItemAmount( TSubclassOf< class UFGItemDescriptor > inClass ) :
		ItemClass( inClass )
	{}
	
	FBlueprintItemAmount( TSubclassOf< class UFGItemDescriptor > inClass, int32 inAmount ) :
		ItemClass( inClass ),
		Amount( inAmount )
	{
	}

	FBlueprintItemAmount( FItemAmount& itemAmount ) :
		ItemClass( itemAmount.ItemClass ),
		Amount( itemAmount.Amount )
	{}

	bool Serialize( FArchive& ar );
	friend FArchive& operator<< ( FArchive& ar, FBlueprintItemAmount& itemAmount );
	
	/** The item. */
	UPROPERTY(SaveGame)
	TSubclassOf< class UFGItemDescriptor > ItemClass;

	/** The amount of this item. */
	UPROPERTY(SaveGame)
	int32 Amount;

};

/** Enable custom serialization of FInventoryItem */
template<>
struct TStructOpsTypeTraits< FBlueprintItemAmount > : public TStructOpsTypeTraitsBase2< FBlueprintItemAmount >
{
	enum
	{
		WithSerializer = true,
		WithCopy = true
	};
};


USTRUCT(  BlueprintType )
struct FBlueprintHeader
{
	GENERATED_BODY()

public:
	// if you modify this struct, increment this number
	enum Type
	{
		// First version
		InitialVersion = 0,

		// Added item costs to the header
		AddedItemCosts,

		// Added recipe array for recipes used in the blueprint
		AddedUsedRecipes,
		
		// -----<new versions can be added above this line>-----
		VersionPlusOne,
		LatestVersion = VersionPlusOne - 1 // Last version to use
	};
	
	FBlueprintHeader() {}

	// @todoBlueprint - Probably want more sophisticated checking of validity
	bool IsValid() const { return !BlueprintName.IsEmpty(); }

	/** Version of the save game used to create the blueprint */
	int32 SaveVersion;

	/** CL the game was on when this blueprint was created */
	int32 BuildVersion;

	// This is Not stored to disc, rather its is filled in as the file name on disc
	UPROPERTY(BlueprintReadWrite, Category="Blueprint Header")
	FString BlueprintName;

	UPROPERTY()
	FIntVector Dimensions;

	UPROPERTY()
	TArray< FBlueprintItemAmount > Cost;

	UPROPERTY()
	TArray< TSubclassOf< class UFGRecipe > > Recipes;
	
	TArray< FObjectReferenceDisc > RecipeRefs;

	friend FArchive& operator<< ( FArchive& ar, FBlueprintHeader& header );

	inline static const FGuid GUID = FGuid( 0xC8C3A46C, 0x9E2BBC1B, 0x13F86A01, 0xD34A7A2D );
};

USTRUCT()
struct FBlueprintSaveData
{
	GENERATED_BODY()

public:
	FBlueprintSaveData() {}

	FBlueprintHeader BlueprintHeader;
	TArray< uint8 > TOCData;
	TArray< uint8 > BlobData;

	bool IsValid() const { return BlueprintHeader.IsValid() && TOCData.Num() > 0 && BlobData.Num() > 0; }
	
};

FArchive& operator<<( FArchive& ar, FBlueprintSaveData& blueprintSaveData );


/**
 * Descriptor for defining a file on disk that can be loaded or placed via hologram
 */
UCLASS()
class FACTORYGAME_API UFGBlueprintDescriptor : public UFGBuildDescriptor
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Category|Blueprint" )
	void UpdateData( const FBlueprintRecord& blueprintRecord );
	
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Category|Blueprint" )
	void InitializeData(const FBlueprintRecord& blueprintRecord);

	UFUNCTION()
	void InitializeHeaderInfo( const FBlueprintHeader& header );

	UFUNCTION( BlueprintCallable, Category="FactoryGame|Category|Blueprint" )
	void SetPriorityOnInstance( float priority ) { mMenuPriority = priority; }
	
	//void SetCategoryOnInstance( class UFGBlueprintCategory* category ) { mInstancedCategory = category; }
	FString GetBlueprintNameAsString() const { return GetItemNameFromInstance().ToString(); }
	
	int32 GetBlueprintID( UFGBlueprintDescriptor* blueprint ) { return mID; }

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Blueprint" )
	FLinearColor GetColorOnInstance() { return mColor; }

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Blueprint" )
	FIntVector GetDimensionsOnInstance() { return mDimensions; }

	UFUNCTION( BlueprintPure, Category="FactoryGame|Descriptor|Blueprint" )
	FBlueprintRecord GetDescriptorAsRecord();
	
	UFUNCTION( BlueprintPure, Category="FactoryGame|Category|Blueprint")
	int32 GetIconID() const { return mIconID; }

	UFUNCTION( BlueprintCallable, Category="FactoryGame|Category|Blueprint")
	void GetBlueprintCost( TArray< FItemAmount >& out_cost )
	{
		out_cost.Reset();
		out_cost.Append( mCost );
	}
	
	void SetRecipeRequirementsAreMet( bool areMet ) { mRecipeRequirementsAreMet = areMet; }
	
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Category|Blueprint")
	bool GetRecipeRequirementsAreMet() { return mRecipeRequirementsAreMet; }
	
public:
	
	UPROPERTY()
	uint32 mID;

	UPROPERTY()
	TArray< FItemAmount > mCost;

	UPROPERTY()
	FLinearColor mColor;
	
	UPROPERTY()
	int32 mIconID;

	UPROPERTY()
	FIntVector mDimensions;

	UPROPERTY()
	bool mRecipeRequirementsAreMet;
	
};

UCLASS()
class UFGBlueprintSubCategory : public UFGCategory
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Category|Blueprint" )
	void InitializeData( FText categoryName, float menuPriority, uint8 isUndefined );

	UFUNCTION( BlueprintCallable, Category="FactoryGame|Category|Blueprint" )
	void SetDisplayNameOnInstance( FText displayName ) { mDisplayName = displayName; }

	UFUNCTION( BlueprintCallable, Category="FactoryGame|Category|Blueprint" )
	void SetPriorityOnInstance( float priority ) { mMenuPriority = priority; }

	UFUNCTION( BlueprintCallable, Category="FactoryGame|Category|Blueprint" )
	void SetParentCategory( UFGBlueprintCategory* parentCategory ) { mParentCategory = parentCategory; }

	UFUNCTION( BlueprintCallable, Category="FactoryGame|Category|Blueprint" )
	void SetBlueprintDescriptors( TArray< UFGBlueprintDescriptor* > descriptors );
	
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Category|Blueprint" )
	void AddBlueprintDescriptor( UFGBlueprintDescriptor* desc )
	{
#if !UE_BUILD_SHIPPING
		ensureAlways( !mBlueprintDescriptors.Contains( desc ) );
#endif
		
		mBlueprintDescriptors.Add( desc );
	}

	void RemoveBlueprintDesc( UFGBlueprintDescriptor* desc )
	{
#if !UE_BUILD_SHIPPING
		ensureAlways( mBlueprintDescriptors.Contains( desc ) );
#endif
		
		mBlueprintDescriptors.Remove( desc );
	}
	
	UFUNCTION( BlueprintPure, Category="FactoryGame|Category|Blueprint")
	TArray< UFGBlueprintDescriptor* > GetBlueprintDescriptors() const { return mBlueprintDescriptors; }
	
	UFUNCTION( BlueprintPure, Category="FactoryGame|Category|Blueprint")
	class UFGBlueprintCategory* GetParentCategory() { return mParentCategory; }

	UFUNCTION( BlueprintPure, Category="FactoryGame|Category|Blueprint" )
	FORCEINLINE bool IsUndefined() const { return (bool)mIsUndefined; }
	
public:
	UPROPERTY()
	class UFGBlueprintCategory* mParentCategory;
	
	UPROPERTY()
	TArray< UFGBlueprintDescriptor* > mBlueprintDescriptors;

	UPROPERTY()
	uint8 mIsUndefined;
};


UCLASS()
class UFGBlueprintCategory : public UFGCategory
{
	GENERATED_BODY()
public:
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Category|Blueprint" )
	void InitializeData( FText categoryName, float menuPriority, int32 iconID, uint8 isUndefined );

	UFUNCTION( BlueprintCallable, Category="FactoryGame|Category|Blueprint" )
	void SetDisplayNameOnInstance( FText displayName ) { mDisplayName = displayName; }

	UFUNCTION( BlueprintCallable, Category="FactoryGame|Category|Blueprint" )
	void SetIconIdOnInstance( int32 iconId ) { mIconID = iconId; }

	UFUNCTION( BlueprintCallable, Category="FactoryGame|Category|Blueprint" )
	void SetPriorityOnInstance( float priority ) { mMenuPriority = priority; }

	/** Empties subcategories and appends incoming array */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Category|Blueprint" )
	void SetSubCategories( TArray< UFGBlueprintSubCategory* > subCategories );
	
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Category|Blueprint" )
	void AddSubCategory( UFGBlueprintSubCategory* subCategory );
	
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Category|Blueprint" )
	void GetSubCategories( TArray< UFGBlueprintSubCategory* >& out_SubCategories )
	{
		out_SubCategories.Reset();
		out_SubCategories.Append( mSubCategories );
	}

	UFUNCTION( BlueprintPure, Category="FactoryGame|Category|Blueprint" )
	FORCEINLINE bool IsUndefined() const { return (bool)mIsUndefined; }
	
	UFUNCTION( BlueprintPure, Category="FactoryGame|Category|Blueprint" )
	FORCEINLINE int32 GetIconIdFromInstance() const { return mIconID; }

	template< typename typeOne, typename typeTwo >
	static bool AreNamesConsideredEqual( const typeOne& A, const typeTwo& B )
	{
		return A.ToLower().EqualTo( B.ToLower() );
	}
	
	FORCEINLINE UFGBlueprintSubCategory* GetSubCategoryByName( FText name )
	{
		for( UFGBlueprintSubCategory* subCategory : mSubCategories )
		{
			if( AreNamesConsideredEqual(name, subCategory->GetCategoryNameFromInstance() ) )
			{
				return subCategory;
			}
		}
		return nullptr;
	}
	
public:
	UPROPERTY()
	uint32 mID;

	UPROPERTY()
	int32 mIconID;

	UPROPERTY()
	uint8 mIsUndefined;

	UPROPERTY()
	TArray< UFGBlueprintSubCategory* > mSubCategories;
	
};


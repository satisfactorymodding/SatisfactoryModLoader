// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "ItemAmount.h"
#include "Resources/FGItemDescriptor.h"
#include "FGFactoryColoringTypes.generated.h"

static const uint8 BUILDABLE_COLORS_MAX_SLOTS_LEGACY = 18;
static const int32 BUILDABLE_CUSTOM_DATA_NUM = 20;
static const uint8 INDEX_CUSTOM_COLOR_SLOT = 255; // The index used to specify a "slot" is a custom user color and thus not really a slot at all
static const uint8 INDEX_PATTERN_REMOVAL = 0; // The index for the custom removal pattern that should refund the cost of a pattern on application (if one exists)
static const int32 INDEX_SKIN_REMOVAL = -1;

// Save/Loadable Color Structure so players can reuse colors across a variety of places (Lights, Factory Colors, Signs_
USTRUCT( BlueprintType )
struct FACTORYGAME_API FGlobalColorPreset 
{
	GENERATED_BODY()

public:
	UPROPERTY( SaveGame, EditDefaultsOnly, BlueprintReadWrite )
	FText PresetName;

	UPROPERTY( SaveGame, EditDefaultsOnly, BlueprintReadWrite )
	FLinearColor Color;
};



namespace BuildableColorConstants
{

	enum class EColorDataIndices : uint8
	{
		CDI_Primary_R = 0,
		CDI_Primary_G = 1,
		CDI_Primary_B = 2,
		CDI_Secondary_R = 3,
		CDI_Secondary_G = 4,
		CDI_Secondary_B = 5,
		CDI_HasPower = 6, // Dynamic set - Shouldn't be set by the user or saved
		CDI_PatternID = 7,
		CDI_MaterialID = 8,
		CDI_Metallic = 9,
		CDI_Roughness = 10,
		CDI_LastPlusOne = 11, // Used to initialize the size of FFactoryCustomizationData data array. Increment as values are added
		//... Add new data here
		CDI_Max = 19
	};

	// The length of the data for saving (we won't save all properties)
	const uint8 SAVE_DATA_LENGTH = (uint8)EColorDataIndices::CDI_Roughness - (uint8)EColorDataIndices::CDI_Primary_R + 1;

}

// Base Customization Descriptor. Holds most, if not all, data we need to define a customization.
// Child classes can include extra data if needed but mostly they are used to identify types
UCLASS( Abstract, Blueprintable, BlueprintType )
class FACTORYGAME_API UFGFactoryCustomizationDescriptor : public UFGItemDescriptor
{
	GENERATED_BODY()

public:
	UFGFactoryCustomizationDescriptor();

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Customization" )
	UTexture2D* GetIcon() const
	{
		if( mIcon.IsPending() )
		{
			mIcon.LoadSynchronous();
		}

		return mIcon.Get();
	}

public:
	/**
	 * If specified, this customization can only be placed on these (or children of) these buildables
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Customization", meta = ( AllowAbstract = true ) )
	TArray< TSubclassOf< class AFGBuildable > > mValidBuildables;

	UPROPERTY( EditDefaultsOnly, Category = "Customization" )
	int32 ID;

	UPROPERTY( EditDefaultsOnly )
	TSoftObjectPtr< UTexture2D > mIcon;

};

// Swatch Class
UCLASS( Blueprintable, BlueprintType )
class FACTORYGAME_API UFGFactoryCustomizationDescriptor_Swatch : public UFGFactoryCustomizationDescriptor
{
	GENERATED_BODY()
};

// Pattern Class
UCLASS( Blueprintable, BlueprintType )
class FACTORYGAME_API UFGFactoryCustomizationDescriptor_Pattern : public UFGFactoryCustomizationDescriptor
{
	GENERATED_BODY()

public:
	FItemAmount GetRefundCostOnApplication() const { return mRefundCostOnApplication; }

protected:
	/** 
	* This is a very specific property for only the Pattern Removal so that we can refund a cost when used. This was preferable to having to store the 
	* recipes used for every pattern since that's a lot of extra data and all patterns should TM cost the same to apply.
	*/
	UPROPERTY( EditDefaultsOnly, Category="Pattern Removal" )
	FItemAmount mRefundCostOnApplication;
};

// Material Class
UCLASS( Blueprintable, BlueprintType )
class FACTORYGAME_API UFGFactoryCustomizationDescriptor_Material : public UFGFactoryCustomizationDescriptor
{
	GENERATED_BODY()

public:
	FORCEINLINE TMap< TSubclassOf< class AFGBuildable >, TSubclassOf< class UFGRecipe > >& GetBuildableMap() { return mBuildableMap; }
	FORCEINLINE bool GetIsCategoryDefault() const { return IsCategoryDefault; }

	bool BuildableRecipeIsMappedTo( TSubclassOf< class UFGRecipe > recipe );

protected:
	
	// Maps a target buildable onto the recipe it should use when switching to this material desc
	UPROPERTY( EditDefaultsOnly )
	TMap< TSubclassOf< class AFGBuildable >, TSubclassOf< class UFGRecipe > > mBuildableMap; 

	// Is this Material Desc the "default" for its category. This means it will be prioritized as the Build Menu Default selection if the player hasn't specified yet
	UPROPERTY( EditDefaultsOnly )
	bool IsCategoryDefault;
};


//////////////////////////////////////////////////////////////////////////
/// Begin Skin Types

/**
 * This is the Skin Descriptor Asset. This is the global skin that is mostly just a name/identifier/icon
 * Because different buildings/vehicles will have different material/component layouts
 * none of the actual skin data is stored here
 */
UCLASS( Blueprintable, Abstract )
class FACTORYGAME_API UFGFactoryCustomizationDescriptor_Skin : public UFGFactoryCustomizationDescriptor
{
	GENERATED_BODY()

	UFGFactoryCustomizationDescriptor_Skin() {}
};


USTRUCT( BlueprintType )
struct FACTORYGAME_API FIndexToMaterialData
{
	GENERATED_BODY()
	
	FIndexToMaterialData() : Index( 0 ), Material( nullptr ) {}
	FIndexToMaterialData( int32 index, UMaterialInterface* material ) : Index( index ), Material( material ) {}
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	int32 Index;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	UMaterialInterface* Material;	
};

/**
 * An individual components information for a skin descriptor
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFactorySkinComponentData
{
	GENERATED_BODY()

	FFactorySkinComponentData() {}

public:
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	FName ComponentName;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TArray< FIndexToMaterialData > IndexToMaterialData;
};

/**
 * This acts as a struct contain so that we can have "nested" containers
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFactorySkinComponentGroup
{
	GENERATED_BODY()

	FFactorySkinComponentGroup() {}

public:
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TArray< FFactorySkinComponentData > mComponentData;
};

/**
 * Each Buildable / Vehicle will have a data asset of this type to define which Skin Descriptors are valid on this buildable
 * If a key is present for a particular skin, it is valid and we use the component group to determine which materials to update
 * and on which components.
 */
UCLASS( Blueprintable, Abstract )
class FACTORYGAME_API UFGFactorySkinActorData : public UObject
{
	GENERATED_BODY()

public:
	UFGFactorySkinActorData() {}

	UFUNCTION( BlueprintCallable, Category = "FactorySkin" )
	static void GetSkinComponentDataForSkinActorData( TSubclassOf< UFGFactorySkinActorData > skinClass, TMap< TSubclassOf< UFGFactoryCustomizationDescriptor_Skin >, FFactorySkinComponentGroup >& out_componentGroupData );

public:
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	TMap< TSubclassOf< UFGFactoryCustomizationDescriptor_Skin >, FFactorySkinComponentGroup > mSkinToComponentGroupData;
};


/// End Skin Types
//////////////////////////////////////////////////////////////////////////





UCLASS( Blueprintable, BlueprintType )
class FACTORYGAME_API UFGFactoryCustomizationCollection : public UObject
{
	GENERATED_BODY()

public:
	UFGFactoryCustomizationCollection();

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid( TArray< FText >& ValidationErrors ) override;
#endif
	
	// Returns the class type all elements must be of to exist in this collection
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Customization" )
	TSubclassOf< UFGFactoryCustomizationDescriptor > GetCustomizationClass() const { return mCustomizationClass; }

	// Returns the customization array
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Customization" )
	const TArray< TSubclassOf< UFGFactoryCustomizationDescriptor > >& GetCustomizations() const { return mCustomizations; }

	// Returns the first Customization in the list OR nullptr if no customizations have been added
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Customization" )
	TSubclassOf< UFGFactoryCustomizationDescriptor > GetDefaultCustomization() const { return mCustomizations.Num() > 0 ? mCustomizations[0] : nullptr; }

protected:
	// Specify the type of this collection. This is used to validate the data ensuring we don't mix customization types in a single collection
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf< UFGFactoryCustomizationDescriptor > mCustomizationClass;

	UPROPERTY( EditDefaultsOnly )
	TArray< TSubclassOf < UFGFactoryCustomizationDescriptor > > mCustomizations;
};

using namespace BuildableColorConstants;

USTRUCT( BlueprintType, meta = ( HasNativeBreak = "FactoryGame.FGBlueprintFunctionLibrary.BreakCustomizationColorSlot", HasNativeMake = "FactoryGame.FGBlueprintFunctionLibrary.MakeCustomizationColorSlot" ) )
struct FACTORYGAME_API FFactoryCustomizationColorSlot
{
	GENERATED_BODY()

public:

	FFactoryCustomizationColorSlot() : 
		PrimaryColor( FLinearColor( 0.f, 0.f, 0.f, 1.f ) ), 
		SecondaryColor( FLinearColor( 0.f, 0.f, 0.f, 1.f ) )
	{}

	FFactoryCustomizationColorSlot( FLinearColor primary, FLinearColor secondary ) : 
		PrimaryColor( primary ), 
		SecondaryColor( secondary ) 
	{}

	FORCEINLINE bool operator==( const FFactoryCustomizationColorSlot& other ) const 
	{
		return this->PrimaryColor == other.PrimaryColor && this->SecondaryColor == other.SecondaryColor && this->Metallic == other.Metallic && this->Roughness == other.Roughness;
	}

	FORCEINLINE bool operator!=( const FFactoryCustomizationColorSlot& other ) const 
	{ 
		return !(*this == other);
	}

	bool NetSerialize( FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess )
	{
		bOutSuccess = true;
		if( Ar.IsSaving() )
		{
			// Write color data minus the alpha as that is guarenteed to be 1.f
			Ar << PrimaryColor.R;
			Ar << PrimaryColor.G;
			Ar << PrimaryColor.B;

			Ar << SecondaryColor.R;
			Ar << SecondaryColor.G;
			Ar << SecondaryColor.B;

			// @todoCustomization - Compress these if we're going to use them (preferably before BU5)
			Ar << Metallic;
			Ar << Roughness;
		}
		else
		{
			Ar << PrimaryColor.R;
			Ar << PrimaryColor.G;
			Ar << PrimaryColor.B;
			PrimaryColor.A = 1.f;

			Ar << SecondaryColor.R;
			Ar << SecondaryColor.G;
			Ar << SecondaryColor.B;
			SecondaryColor.A = 1.f;

			// @todoCustomization - Uncompress these if we're going to use them (preferably before BU5)
			Ar << Metallic;
			Ar << Roughness;
		}

		return bOutSuccess;
	}

	UPROPERTY( SaveGame, EditAnywhere, NotReplicated )
	FLinearColor PrimaryColor;

	UPROPERTY( SaveGame, EditAnywhere, NotReplicated )
	FLinearColor SecondaryColor;

	UPROPERTY( SaveGame, EditAnywhere, NotReplicated )
	float Metallic;

	UPROPERTY( SaveGame, EditAnywhere, NotReplicated )
	float Roughness;
};

template<>
struct TStructOpsTypeTraits< FFactoryCustomizationColorSlot > : public TStructOpsTypeTraitsBase2< FFactoryCustomizationColorSlot >
{
	enum
	{
		WithNetSerializer = true,
	};
};


// All properties pertaining to setting of custom data per instance
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFactoryCustomizationData
{
	GENERATED_BODY()

	FFactoryCustomizationData() :
		SwatchDesc( nullptr ),
		PatternDesc( nullptr ),
		MaterialDesc( nullptr )
	{}

	/**
	 * Call from buildable after fully "setup". This shouldn't be done on creation, but only once we know the data is complete. Ie. from the buildable not say, the BuildGun
	 */
	void Initialize( class AFGGameState* gameState );
	
	/**
	 * Combine the data from this CustomizationData with another. This will correctly apply data so that nullptrs don't override existing data
	 * The "other" data will take precedent overriding existing values.
	 */
	void InlineCombine( const FFactoryCustomizationData& other );

	/**
	 * Has the data array been initialized from the Descriptors 
	 */
	bool IsInitialized() const { return Data.Num() > 0; }

	/**
	 * Update the data array with current HasPower
	 */
	void UpdateHasPowerData();

	/**
	 * Fills an array with all valid customizations ( useful when sampling buildings tex. )
	 */
	void GetCustomizationArray( TArray< TSubclassOf < class UFGFactoryCustomizationDescriptor > >& out_customizations );

	FORCEINLINE bool operator==( const FFactoryCustomizationData& other ) const
	{
		return this->SwatchDesc == other.SwatchDesc && this->PatternDesc == other.PatternDesc && this->MaterialDesc == other.MaterialDesc;
	}

	FORCEINLINE bool operator!=( const FFactoryCustomizationData& other ) const
	{
		return !( *this == other );
	}

	UPROPERTY( SaveGame, EditAnywhere, Category = "Customization" )
	TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > SwatchDesc;
	
	UPROPERTY( SaveGame, EditAnywhere, Category = "Customization" )
	TSubclassOf< class UFGFactoryCustomizationDescriptor_Pattern > PatternDesc;

	UPROPERTY( SaveGame, EditAnywhere, Category = "Customization" )
	TSubclassOf< class UFGFactoryCustomizationDescriptor_Material > MaterialDesc;

	UPROPERTY( SaveGame, EditAnywhere, Category = "Customization" )
	TSubclassOf< class UFGFactoryCustomizationDescriptor_Skin > SkinDesc;
	
	UPROPERTY( SaveGame )
	FFactoryCustomizationColorSlot OverrideColorData;

	UPROPERTY( SaveGame )
	uint8 PatternRotation;

	/**
	 * When Initialized, the data array will be filled in with indices corresponding to EColorDataIndices so that lookups / access can be much faster
	 */
	UPROPERTY( BlueprintReadWrite, NotReplicated )
	TArray< float > Data;

	/**
	 * This is a custom array of floats to allow for buildables to have their own PIC data starting after the last index of the global PIC data struct
	 */
	UPROPERTY( BlueprintReadWrite, NotReplicated )
	TArray< float > ExtraData;

	/**
	 * When Initialized, the slot will be set from the Swatch Desc. This is a cached value to reduce subsequent lookup times
	 */
	UPROPERTY( NotReplicated )
	uint8 ColorSlot;

	/*
	 * Tracking variable used to know if skin data needs to be updated
	 */
	UPROPERTY( BlueprintReadWrite, NotReplicated )
	bool NeedsSkinUpdate;

	/**
	 * Must be manually assigned by buildable/vehicle if desired, otherwise 0 will be used. This is included for ease of access from instanced meshes so we don't have to pass extra data
	 */
	UPROPERTY( NotReplicated )
	uint8 HasPower;
};


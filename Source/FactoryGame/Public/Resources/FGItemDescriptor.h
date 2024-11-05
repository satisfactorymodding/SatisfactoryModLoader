// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGScannableDetails.h"
#include "HAL/IConsoleManager.h"
#include "UObject/Object.h"
#include "FGItemDescriptor.generated.h"

extern TAutoConsoleVariable<int32> CVarStressTestRadioActivity; 

/**
 * The form this item is in, i.e. does it require pipes or conveyors, can the player pick it up etc.
 */
UENUM( BlueprintType )
enum class EResourceForm : uint8
{
	RF_INVALID		UMETA( DisplayName = "Invalid" ),
	RF_SOLID		UMETA( DisplayName = "Solid" ),
	RF_LIQUID		UMETA( DisplayName = "Liquid" ),
	RF_GAS			UMETA( DisplayName = "Gas" ),
	RF_HEAT			UMETA( DisplayName = "Heat" ),
	RF_LAST_ENUM	UMETA( Hidden )
};

/**
 * In case this item is a gas resource, this is the type of gas.
 */
UENUM( BlueprintType )
enum class EGasType : uint8
{
	GT_NORMAL		UMETA( DisplayName = "Normal" ),
	GT_ENERGY		UMETA( DisplayName = "Energy" ),
	GT_LAST_ENUM	UMETA( Hidden )
};

/**
 * Stack Size for items
 */
UENUM( BlueprintType )
enum class EStackSize : uint8
{
	SS_ONE			UMETA( DisplayName = "One" ),
	SS_SMALL		UMETA( DisplayName = "Small" ),
	SS_MEDIUM		UMETA( DisplayName = "Medium" ),
	SS_BIG			UMETA( DisplayName = "Big" ),
	SS_HUGE			UMETA( DisplayName = "Huge" ),
	SS_FLUID		UMETA( DisplayName = "Fluid" ),
	SS_LAST_ENUM	UMETA( Hidden )
};

USTRUCT(BlueprintType)
struct FItemView
{
	GENERATED_BODY()

	FItemView() :
		Distance( 200 ),
		FocalOffset( 0, 0, 0 ),
		CameraPitch( -35 )
	{
	}

	/** The distance to the object when creating it's view */
	UPROPERTY( EditDefaultsOnly, Category = "View" )
	float Distance;

	/** Where should the camera focus offsetted on the mesh */
	UPROPERTY( EditDefaultsOnly, Category = "View", meta=(ShowOnlyInnerProperties) )
	FVector FocalOffset;

	/** How much "down or up" the camera should be angeled (in degrees) when crating the view */
	UPROPERTY( EditDefaultsOnly, Category = "View" )
	float CameraPitch;
};

UENUM( BlueprintType )
enum class ECompatibleItemType : uint8
{
	CIT_OTHER		UMETA( DisplayName = "Other" ),
	CIT_AMMO		UMETA( DisplayName = "Ammo" ),
	CIT_FUEL		UMETA( DisplayName = "Fuel" ),
	CIT_WEAPON		UMETA( DisplayName = "Weapon" ),
	CIT_FILTER		UMETA( DisplayName = "Filter" )
};

USTRUCT( BlueprintType )
struct FCompatibleItemDescriptors
{
	GENERATED_BODY()

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	ECompatibleItemType CompatibleItemType;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	TArray< TSubclassOf< class UFGItemDescriptor > > CompatibleItemDescriptors;
	
};

UENUM( BlueprintType )
enum class EDescriptorStatBarType : uint8
{
	DSBT_Damage				UMETA( DisplayName = "Damage" ),
	DSBT_EnergyEfficiency	UMETA( DisplayName = "Energy Efficiency" ),
};

USTRUCT( BlueprintType )
struct FDescriptorStatBar
{
	GENERATED_BODY()

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	EDescriptorStatBarType DescriptorStatBarType;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	int32 Value;
};

/** Simple struct when you need an array of item descriptors in a struct. For example when you want to have TMap< xyz, TArray< TSubclassOf< class UFGItemDescriptor> > > */
USTRUCT()
struct FItemDescriptors
{
	GENERATED_BODY()

	FItemDescriptors(){}
	FItemDescriptors( TArray< TSoftClassPtr< class UFGItemDescriptor> > itemDescriptors ) :
		ItemDescriptors( itemDescriptors )
	{}
	
	UPROPERTY( EditDefaultsOnly )
	TArray< TSoftClassPtr< class UFGItemDescriptor> > ItemDescriptors;
};

/**
 * Base for all descriptors in the game like resource, equipment etc.
 */
UCLASS(Blueprintable, Abstract,HideCategories=(Icon, Preview),meta=(AutoJSON=true))
class FACTORYGAME_API UFGItemDescriptor : public UObject
{
	GENERATED_BODY()
public:
	UFGItemDescriptor();

#if WITH_EDITOR
	virtual void PostEditChangeProperty( struct FPropertyChangedEvent& propertyChangedEvent ) override;
#endif

	// Begin UObject interface
	virtual void Serialize( FArchive& ar ) override;
	virtual void PostLoad() override;
	virtual void BeginDestroy() override;
	// End UObject interface

	/** The state of this resource. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static EResourceForm GetForm( TSubclassOf< UFGItemDescriptor > inClass );

	/** In case the item is a gas form, this is the type of gas. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static EGasType GetGasType( TSubclassOf< UFGItemDescriptor > inClass );

	/** Energy value for this resource if used as fuel. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static float GetEnergyValue( TSubclassOf< UFGItemDescriptor > inClass );

	/** How much radiation this item gives out, 0 means it's not radioactive. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static float GetRadioactiveDecay( TSubclassOf< UFGItemDescriptor > inClass );
	FORCEINLINE static float GetRadioactiveDecay_inline( TSubclassOf< UFGItemDescriptor > inClass )
	{
#if !UE_BUILD_SHIPPING
		if( CVarStressTestRadioActivity.GetValueOnAnyThread() > 0 )
		{
			return 50.f;
		}
#endif
		if( inClass )
		{
			return inClass->GetDefaultObject< UFGItemDescriptor >()->mRadioactiveDecay;
		}
		return 0.0f;		
	}

	/** Used to get the resource name in blueprints */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static FText GetItemName( TSubclassOf< UFGItemDescriptor > inClass );

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	FText GetItemNameFromInstance() const { return GetItemNameInternal(); }

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	FString GetItemNameFromInstanceAsString() const { return GetItemNameInternalAsString(); }

	/** Used to get the resource description in blueprints */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static FText GetItemDescription( TSubclassOf< UFGItemDescriptor > inClass );

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	FText GetItemDescriptionFromInstance() const { return GetItemDescriptionInternal(); };
	
	/** Used to get the abbreviated name of the item in blueprints */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static FText GetAbbreviatedDisplayName( TSubclassOf< UFGItemDescriptor > inClass );

	/** The small icon of the item */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static UTexture2D* GetSmallIcon( TSubclassOf< UFGItemDescriptor > inClass );

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	UTexture2D* GetSmallIconFromInstance() const { return Internal_GetSmallIcon(); }

	/** The big icon of the item */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static UTexture2D* GetBigIcon( TSubclassOf< UFGItemDescriptor > inClass );

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	UTexture2D* GetBigIconFromInstance() const { return Internal_GetBigIcon(); }

	/** Returns the crosshair material used with this item */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static UMaterialInterface* GetCrosshairMaterial( TSubclassOf< UFGItemDescriptor > inClass );

	/** Returns the stat bars for this item descriptor */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static void GetDescriptorStatBars( TSubclassOf< UFGItemDescriptor > inClass, TArray<FDescriptorStatBar>& out_DescriptorStatBars );

	/** Should we consider this item as an "alien item"? It is used purely for cosmetic purposes (visual effects) in the UI. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static bool IsAlienItem( TSubclassOf< UFGItemDescriptor > inClass );

	/** Return the inventory settings widget for this item descriptor*/
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static void GetInventorySettingsWidget( TSubclassOf< UFGItemDescriptor > inClass, TSubclassOf<class UFGInventorySettingsWidget>& out_InventorySettingsWidget );

	/** The static mesh we want for representing the resource when they are in the production line.
	 * @return The items mesh; a default mesh if the item has no mesh specified, nullptr if inClass is nullptr. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static class UStaticMesh* GetItemMesh( TSubclassOf< UFGItemDescriptor > inClass );

	// TODO we might want to inline this.
	/** Returns the number of items of a certain type we can stack in one inventory slot */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static int32 GetStackSize( TSubclassOf< UFGItemDescriptor > inClass );

	/** 
	* Returns the number of items of a certain type we can stack in one inventory slot converted by its resource form to match a unit specification
	* eg. Liquid Descriptors will divided by 1000 to switch from liters to m^3
	*/
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static float GetStackSizeConverted( TSubclassOf< UFGItemDescriptor > inClass );

	/** Returns if this item can be discarded */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static bool CanBeDiscarded( TSubclassOf< UFGItemDescriptor > inClass );

	/** Returns if we should store if this item ever has been picked up  */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static bool RememberPickUp( TSubclassOf< UFGItemDescriptor > inClass );

	/** Get the category for this descriptor. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Organization" )
	static TSubclassOf< class UFGCategory > GetCategory( TSubclassOf< UFGItemDescriptor > inClass );

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Organization" )
	TSubclassOf< class UFGCategory > GetCategoryFromInstance() const { return mCategory; }
	
	/** Get the category for this descriptor. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Descriptor|Organization" )
	static void GetSubCategories( TSubclassOf< UFGItemDescriptor > inClass, TArray< TSubclassOf< class UFGCategory > >& out_subCategories );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Descriptor|Organization" )
	void GetSubCategoriesFromInstance( TArray< TSubclassOf< class UFGCategory > >& out_subCategories ) const { out_subCategories.Append( mSubCategories ); }
	
	/** Get the category for this descriptor of the given output class. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Descriptor|Organization", meta = (DeterminesOutputType = "outputCategoryClass") )
	static TArray< TSubclassOf< class UFGCategory > > GetSubCategoriesOfClass( TSubclassOf< UFGItemDescriptor > inClass, TSubclassOf< class UFGCategory > outputCategoryClass );

	/** Get the quick switch group for this building descriptor. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Organization" )
	static TSubclassOf< class UFGQuickSwitchGroup > GetQuickSwitchGroup( TSubclassOf< UFGItemDescriptor > inClass );

	/** The order we want stuff in the build menu, lower is earlier */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Organization" )
	static float GetMenuPriority( TSubclassOf< UFGItemDescriptor > inClass );

	/** Returns the color of this is a fluid. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Fluid" )
	static FColor GetFluidColor( TSubclassOf< UFGItemDescriptor > inClass );

	/** Returns the color of this fluid ( if it is one ) as type FLinearColor */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Fluid" )
	static FLinearColor GetFluidColorLinear( TSubclassOf< UFGItemDescriptor > inClass );

	/** Returns the color of this is a gas. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Gas" )
    static FColor GetGasColor( TSubclassOf< UFGItemDescriptor > inClass );

	/** Returns the color of this gas ( if it is one ) as type FLinearColor */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Gas" )
    static FLinearColor GetGasColorLinear( TSubclassOf< UFGItemDescriptor > inClass );

	/** Returns the compatible item descriptors for this item */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|CompatibleType" )
	static TArray< FCompatibleItemDescriptors > GetCompatibleItemDescriptors( TSubclassOf< UFGItemDescriptor > inClass );

	/** Returns the class we want to scan for when looking for this descriptor */
	static TSubclassOf< AActor > GetClassToScanFor( TSubclassOf< UFGItemDescriptor > inClass );
	/** Returns a custom class we want to use when we scan for mClassToScanFor */
	static TSubclassOf< class UFGScannableDetails > GetCustomScannableDetails( TSubclassOf< UFGItemDescriptor > inClass );
	/** Returns the scannable type which decides how we present this descriptor after it been scanned */
	static EScannableActorType GetScannableActorType( TSubclassOf< UFGItemDescriptor > inClass );
	/** Required schematic to search for this descriptor. None means no requirement. */
	static TSubclassOf<UFGSchematic> GetRequiredSchematicToScan( TSubclassOf< UFGItemDescriptor > inClass );
	/** Return the display text for this descriptor when displayed in object scanner */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|CompatibleType" )
	static FText GetScannerDisplayText( TSubclassOf< UFGItemDescriptor > inClass );
	/** Return the scanner light color for this descriptor when displayed in object scanner */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|CompatibleType" )
	static FColor GetScannerLightColor( TSubclassOf< UFGItemDescriptor > inClass );

	/** Returns true if this item needs a pick-up marker spawned when it is dropped on the ground */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor" )
	static bool NeedsPickupMapMarker( TSubclassOf<UFGItemDescriptor> inClass );

	/**
	 * Set array index used by the conveyor item renderer subsystem.
	 * Should only be called in runtime and by the conveyor renderer, will write to the mutable default object.
	 */
	FORCEINLINE static void SetItemEncountered( TSubclassOf<UFGItemDescriptor> Class, int32 Index );
	FORCEINLINE static int32 IsItemEncountered( TSubclassOf<UFGItemDescriptor> Class );

	/** Returns true if this item descriptor can be picked up and stored in player inventory. i.e if its a solid and not a building or other non pickupable item
	 *  If it's a non pickupable class we will return false in the overridden Internal_CanItemBePickedup */
	static bool CanItemBePickedup( TSubclassOf< UFGItemDescriptor > inClass );
	static bool CanItemBePickedup( UFGItemDescriptor* inClass );

protected:
	/** Internal function to get the display name. */
	virtual FText GetItemNameInternal() const;

	/** Internal function to get the display name as a string */
	virtual FString GetItemNameInternalAsString() const;

	/** Internal function to get the display description. */
	virtual FText GetItemDescriptionInternal() const;
	
	virtual UTexture2D* Internal_GetSmallIcon() const;
	virtual UTexture2D* Internal_GetBigIcon() const;
	
	FORCEINLINE virtual bool Internal_CanItemBePickedup() const { return mForm == EResourceForm::RF_SOLID; }

public:
	/**
	 * If mDisplayName and mDisplayName is overridden and specified elsewhere.
	 * This is specified in the native constructor and is meant to be per class.
	 * E.g. vehicle descriptors get name and description from the vehicle class so the defaults are useless.
	 */
	UPROPERTY( Transient )
	bool mUseDisplayNameAndDescription;

	/** Readable name of the item */
	UPROPERTY( EditDefaultsOnly, Category = "Item", meta = ( EditCondition = mUseDisplayNameAndDescription, HideEditConditionToggle ) )
	FText mDisplayName;

	/** Readable description of the item */
	UPROPERTY( EditDefaultsOnly, Category = "Item", meta = ( EditCondition = mUseDisplayNameAndDescription, HideEditConditionToggle, MultiLine = true ) )
	FText mDescription;

protected:
	/** Abbreviated name of the item */
	UPROPERTY( EditDefaultsOnly, Category = "Item", meta = ( EditCondition = mUseDisplayNameAndDescription, HideEditConditionToggle ) )
	FText mAbbreviatedDisplayName;

	/** How many of this item can be in the same slot in an inventory */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	EStackSize mStackSize;

	/** Indicates if this item can be thrown in the trash or not */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	bool mCanBeDiscarded;

	/** Do we want to know if this item ever has been picked up  */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	bool mRememberPickUp;

	/** Energy value for this resource if used as fuel. In megawatt seconds (MWs), a.k.a. mega joule (MJ) */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	float mEnergyValue;

	/**
	 * How much radiation this item gives out in the number of nucleus that decays per second.
	 * 0 means no radiation and 1 is 10^15 (1 quadrillion) decays/s.
	 * Good values are in the range 0 to 1.
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Item", meta = ( ClampMin=0, UIMin=0, UIMax=1 ) )
	float mRadioactiveDecay;

	/** The state of this resource (cannot change during it's lifetime). */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	EResourceForm mForm;

	/** In case this item is a gas type, this represents the type of gas. */
	UPROPERTY( EditDefaultsOnly, Category = "Item", meta = ( EditCondition="mForm == EResourceForm::RF_GAS", EditConditionHides ) )
	EGasType mGasType;

	/** Small icon of the item, always in memory */
	UPROPERTY( EditDefaultsOnly, Category="UI", meta = ( AddAutoJSON = true ) )
	UTexture2D* mSmallIcon;

	/** Big icon of the item, SHOULD only be loaded by demand, but right now persistent in memory */
	UPROPERTY( EditDefaultsOnly, Category = "UI", DisplayName="Big Icon", meta = ( AddAutoJSON = true ) )
	UTexture2D* mPersistentBigIcon;

	/** The crosshair material used with this item */
	UPROPERTY( EditDefaultsOnly, Category = "UI" )
	TSoftObjectPtr<UMaterialInterface> mCrosshairMaterial;

	/** This is just enums mapped to arbitrary values meant to represent this item descriptors capabilities when we show it in the UI. This has no effect on game logic */
	UPROPERTY( EditDefaultsOnly, Category="UI" )
	TArray< FDescriptorStatBar > mDescriptorStatBars;

	/** Should we consider this item as an "alien item"? It is used purely for cosmetic purposes (visual effects) in the UI. */
	UPROPERTY( EditDefaultsOnly, Category="UI" )
	bool mIsAlienItem;

	/** The inventory settings widget we want to show to modifying settings for an item in an equipment slot  */
	UPROPERTY( EditDefaultsOnly, Category="UI" )
	TSubclassOf<class UFGInventorySettingsWidget> mInventorySettingsWidget;

	/** The static mesh we want for representing the resource when they are in the production line. */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	class UStaticMesh* mConveyorMesh;

	UPROPERTY( EditDefaultsOnly, Category = "Organization" )
	TSubclassOf< class UFGCategory > mCategory;

	/** The sub categories in the build menu for this building */
	UPROPERTY( EditDefaultsOnly, Category = "Organization" )
	TArray< TSubclassOf< class UFGCategory > > mSubCategories;

	/** The quick switch group this building is sorted into in the build menu, used for fast switching between similiar buildings */
	UPROPERTY( EditDefaultsOnly, Category = "Organization" )
	TSubclassOf< class UFGQuickSwitchGroup > mQuickSwitchGroup;

	/** The order where this is displayed is decided by this value. Lower values means earlier in menu. Negative values are allowed. [-N..0..N] */
	UPROPERTY( EditDefaultsOnly, Category = "Organization" )
	float mMenuPriority;

	// NOTE: Ideally we want a fluid descriptor but some fluids are already a raw resource so we cannot do multiple inheritance, so either we need refactor how descriptors work or we put them here for now.
	/**
	 * Color for this fluid, RGB is the color and A is the transparency of the fluid.
	 * Form must be liquid or gas for this to be useful.
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Item", Meta = (DisplayName="Color 1 (Fluid Color)") )
	FColor mFluidColor;

	/**
	 * Color for this gas, RGB is the color and A is the transparency of the gas.
	 * Form must be liquid or gas for this to be useful.
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Item", Meta = (DisplayName="Color 2 (Gas Color)") )
	FColor mGasColor;

	/** The compatible item descriptors for this item. For example which ammo descriptors a weapon can use */
	UPROPERTY( EditDefaultsOnly, Category="Item" )
	TArray< FCompatibleItemDescriptors > mCompatibleItemDescriptors;

	/** The class we want to scan for when looking for this descriptor */
	UPROPERTY( EditDefaultsOnly, Category = "Scanning" )
	TSoftClassPtr< class AActor > mClassToScanFor;
	/** The custom class we want to use when we scan for mClassToScanFor. If null we use the base scanning which just searched for actors of the class */
	UPROPERTY( EditDefaultsOnly, Category = "Scanning" )
	TSubclassOf< class UFGScannableDetails > mCustomScannableDetails;
	/** The scannable type which decides how we present this descriptor after it been scanned */
	UPROPERTY( EditDefaultsOnly, Category = "Scanning" )
	EScannableActorType mScannableType;
	/** Required schematic to search for this descriptor. None means no requirement. */
	UPROPERTY( EditDefaultsOnly, Category = "Scanning" )
	TSubclassOf<class UFGSchematic> mRequiredSchematicToScan;
	/** If this is true we use the mScannerDisplayText as display text instead of the item descriptor name */ 
	UPROPERTY( EditDefaultsOnly, Category = "Scanning", meta = (InlineEditConditionToggle) )
	bool mShouldOverrideScannerDisplayText;
	/** Name of object to scan for if we want to override display text */
	UPROPERTY( EditDefaultsOnly, Category = "Scanning", meta = (EditCondition="mShouldOverrideScannerDisplayText") )
	FText mScannerDisplayText;
	/** Scanner light color that shows up in the hand scanner. This is an FColor since it was and FColor in the old struct used for scanning. */
	UPROPERTY( EditDefaultsOnly, Category = "Scanning" )
	FColor mScannerLightColor;
	/** True if this item needs a marker on the map when it is dropped */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	bool mNeedsPickUpMarker;
	
	/**
	 * This is just a hook for the resource sink points so we can add them to the 
	 * JSON wiki file even though they are in a separate datatable.  
	 */
	UPROPERTY()
	int32 mResourceSinkPoints;

	/** Stack size will be cached on post load, this way we dont need to cast every time to get the value.*/
	UPROPERTY( Transient )
	int32 mCachedStackSize;
public:
	/*for by passing get CDO calls */
	FColor FluidColor() const	{ return mFluidColor; }
	FColor GasColor() const		{ return mGasColor; }
	EResourceForm Form() const	{ return mForm; }
	EGasType GasType() const	{ return mGasType; }

	FORCEINLINE int32 GetConveyorRendererItemIndex() const { return mItemIndex;}

	/**
     * Index used by the conveyor item subsystem.
     * Written onto the mutable default object.
     */
    UPROPERTY( Transient )
    int32 mItemIndex = INDEX_NONE;
private:


	friend class FItemDescriptorDetails;
	friend class FFGItemDescriptorPropertyHandle;
};

// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Array.h"
#include "UnrealString.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "Object.h"
#include "Styling/SlateBrush.h"
#include "Templates/SubclassOf.h"
#include "FGItemDescriptor.generated.h"

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
struct FACTORYGAME_API FItemView
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

public:
	FORCEINLINE ~FItemView() = default;
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
	// End UObject interface

	/** The state of this resource. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static EResourceForm GetForm( TSubclassOf< UFGItemDescriptor > inClass );

	/** Energy value for this resource if used as fuel. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static float GetEnergyValue( TSubclassOf< UFGItemDescriptor > inClass );

	/** How much radiation this item gives out, 0 means it's not radioactive. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static float GetRadioactiveDecay( TSubclassOf< UFGItemDescriptor > inClass );

	/** Used to get the resource name in blueprints */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static FText GetItemName( TSubclassOf< UFGItemDescriptor > inClass );

	/** Used to get the resource description in blueprints */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static FText GetItemDescription( TSubclassOf< UFGItemDescriptor > inClass );

	/** Used to get the abbreviated name of the item in blueprints */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static FText GetAbbreviatedDisplayName( TSubclassOf< UFGItemDescriptor > inClass );

	/** Get the view to use when previewing this item */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static void GetPreviewView( TSubclassOf< UFGItemDescriptor > inClass, FItemView& out_previewView );

	/** Get the view to use when previewing this item */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item", meta = ( DevelopmentOnly ) )
	static void GetIconView( TSubclassOf< UFGItemDescriptor > inClass, FItemView& out_itemView );

	//@todo This has been deprecated for a while, cleanup crew? G2 2019-06-12
	/** The icon to be used in UI. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item", meta=( DeprecatedFunction, DeprecationMessage = "Don't use the brush anymore, please use GetSmallIcon or GetBigIcon" ) )
	static FSlateBrush GetItemIcon( TSubclassOf< UFGItemDescriptor > inClass );

	/** The small icon of the item */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static UTexture2D* GetSmallIcon( TSubclassOf< UFGItemDescriptor > inClass );

	/** The big icon of the item */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static UTexture2D* GetBigIcon( TSubclassOf< UFGItemDescriptor > inClass );

	/** The static mesh we want for representing the resource when they are in the production line.
	 * @return The items mesh; a default mesh if the item has no mesh specified, nullptr if inClass is nullptr. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static class UStaticMesh* GetItemMesh( TSubclassOf< UFGItemDescriptor > inClass );

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

	/** Returns the item category */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Item" )
	static TSubclassOf< UFGItemCategory > GetItemCategory( TSubclassOf< UFGItemDescriptor > inClass );

	/** Returns the density if this is a fluid. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Fluid" )
	static float GetFluidDensity( TSubclassOf< UFGItemDescriptor > inClass );

	/** Returns the viscosity if this is a fluid. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Fluid" )
	static float GetFluidViscosity( TSubclassOf< UFGItemDescriptor > inClass );

	/** Returns the friction of this fluid. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Fluid" )
	static float GetFluidFriction( TSubclassOf< UFGItemDescriptor > inClass );

	/** Returns the color of this is a fluid. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Fluid" )
	static FColor GetFluidColor( TSubclassOf< UFGItemDescriptor > inClass );

	/** Returns the color of this fluid ( if it is one ) as type FLinearColor */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Fluid" )
	static FLinearColor GetFluidColorLinear( TSubclassOf< UFGItemDescriptor > inClass );

	/** Getters and setters for icon capture properties, for editor tools use only but not wrapped with WiTH_EDITOR since it's needed in a tool with a scene which is technically a game.
	*	The content of the functions are instead wrapped
	*/
	UFUNCTION( BlueprintPure, Category = "FactoryEditor|Descriptor|Icon", meta = ( DevelopmentOnly ) )
	static FTransform GetIconCameraTransform( TSubclassOf< UFGItemDescriptor > inClass );
	UFUNCTION( BlueprintCallable, Category = "FactoryEditor|Descriptor|Icon", meta = ( DevelopmentOnly ) )
	static void SetIconCameraTransform( TSubclassOf< UFGItemDescriptor > inClass, FTransform cameraTransform );
	UFUNCTION( BlueprintPure, Category = "FactoryEditor|Descriptor|Icon", meta = ( DevelopmentOnly ) )
	static float GetIconFOV( TSubclassOf< UFGItemDescriptor > inClass );
	UFUNCTION( BlueprintCallable, Category = "FactoryEditor|Descriptor|Icon", meta = ( DevelopmentOnly ) )
	static void SetIconFOV( TSubclassOf< UFGItemDescriptor > inClass, float iconFOV );
	UFUNCTION( BlueprintPure, Category = "FactoryEditor|Descriptor|Icon", meta = ( DevelopmentOnly ) )
	static FRotator GetIconObjectOrientation( TSubclassOf< UFGItemDescriptor > inClass );
	UFUNCTION( BlueprintCallable, Category = "FactoryEditor|Descriptor|Icon", meta = ( DevelopmentOnly ) )
	static void SetIconObjectOrientation( TSubclassOf< UFGItemDescriptor > inClass, FRotator objectOrientation );
	UFUNCTION( BlueprintPure, Category = "FactoryEditor|Descriptor|Icon", meta = ( DevelopmentOnly ) )
	static float GetIconCameraDistance( TSubclassOf< UFGItemDescriptor > inClass );
	UFUNCTION( BlueprintCallable, Category = "FactoryEditor|Descriptor|Icon", meta = ( DevelopmentOnly ) )
	static void SetIconCameraDistance( TSubclassOf< UFGItemDescriptor > inClass, float cameraDistance );
	UFUNCTION( BlueprintPure, Category = "FactoryEditor|Descriptor|Icon", meta = ( DevelopmentOnly ) )
	static FRotator GetIconSkyOrientation( TSubclassOf< UFGItemDescriptor > inClass );
	UFUNCTION( BlueprintCallable, Category = "FactoryEditor|Descriptor|Icon", meta = ( DevelopmentOnly ) )
	static void SetIconSkyOrientation( TSubclassOf< UFGItemDescriptor > inClass, FRotator skyOrientation );

#if WITH_EDITOR
	/** Delete all icons in the game that's referenced by a FGItemDescriptor */
	static void DeleteAllIcons();

	/** Go through all FGItemDescriptor and generate a Icon for them */
	static void GenerateAllIcons();

	/** Calculate the bounds of this item */
	virtual FVector GetCenterOfCollision();

#endif

protected:
	/** Internal function to get the display name. */
	virtual FText GetItemNameInternal() const;

	/** Internal function to get the display description. */
	virtual FText GetItemDescriptionInternal() const;

#if WITH_EDITOR
	/** Setup for generating icons */
	static void BeginGenerateIcons();

	/** Cleanup after generating icon */
	static void EndGenerateIcons();

	/** Clear the stage */
	void ClearStage();

	/** Let all the classes setup the stage the way it prefer, subclasses probably don't want to call Super */
	virtual void SetupStage();

	/** Generate a icon for this item */
	virtual void GenerateIcon( bool reopenAssetEditor, TArray<UPackage*>& out_modifiedAddedPackages );

	/** Get the item name from this class (Desc_IronScrew_C, becomes IronScrew) */
	void GetItemName( FString& out_itemName ) const;

	/** Get the folder path to the current class (/Game/FactoryGame/Resources/Parts/IronScrew) */
	void GetCurrentFolderPath( FString& out_folderPath ) const;

	/** Let this class generate a package and asset name for the icon */
	void GenerateIconName( FString& out_package, FString& out_assetName ) const;

	/** Let this class generate a package and asset name for the material instance */
	void GenerateMaterialInstanceName( FString& out_package, FString& out_assetName ) const;

	// Decide what components we want in our icon preview
	class USceneComponent* CreatePreviewComponent( class USceneComponent* attachParent, class UActorComponent* componentTemplate, const FName& componentName );

	// Abuse of the duplicate component system to calculate the bounds of a item... Ssssshhhh... Just walk away
	class USceneComponent* CalculateComponentBounds( class USceneComponent* attachParent, class UActorComponent* componentTemplate, const FName& componentName );
#endif

public:
	/**
	 * If mDisplayName and mDisplayName is overridden and specified elsewhere.
	 * This is specified in the native constructor and is meant to be per class.
	 * E.g. vehicle descriptors get name and description from the vehicle class so the defaults are useless.
	 */
	UPROPERTY( EditDefaultsOnly, Transient ) // MODDING EDIT
	bool mUseDisplayNameAndDescription;

	/** Readable name of the item */
	UPROPERTY( EditDefaultsOnly, Category = "Item", meta = ( EditCondition = mUseDisplayNameAndDescription, HideEditConditionToggle ) )
	FText mDisplayName;

	/** Readable description of the item */
	UPROPERTY( EditDefaultsOnly, Category = "Item", meta = ( EditCondition = mUseDisplayNameAndDescription, HideEditConditionToggle, MultiLine = true ) )
	FText mDescription;

public: // MODDING EDIT: protected -> public
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

	//@todo @save Maybe clean this up at a later point? /G2 2018-10-25
	/** Old brush used for UI, can't be DEPRECATED_ as it won't work in shipping builds during conversion then */
	UPROPERTY( Meta = (NoAutoJSON = true) )
	FSlateBrush mInventoryIcon;

	/** Small icon of the item, always in memory */
	UPROPERTY( EditDefaultsOnly, Category="UI", meta = ( AddAutoJSON = true ) )
	UTexture2D* mSmallIcon;

	/** Big icon of the item, SHOULD only be loaded by demand, but right now persistent in memory */
	UPROPERTY( EditDefaultsOnly, Category = "UI", DisplayName="Big Icon", meta = ( AddAutoJSON = true ) )
	UTexture2D* mPersistentBigIcon;

	/** The static mesh we want for representing the resource when they are in the production line. */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	class UStaticMesh* mConveyorMesh;

	/** The view in the build menu for this item */
	UPROPERTY( EditDefaultsOnly, Category = "Preview", meta = ( ShowOnlyInnerProperties, NoAutoJSON = true) )
	FItemView mPreviewView;

	/** The category for this item */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	TSubclassOf< class UFGItemCategory > mItemCategory;

#if WITH_EDITORONLY_DATA
	/** Internal variable used when calculating the bounds of a descriptor */
	FBox mComponentBounds;

	// Used persist a world/stage between several GenerateIconCalls
	struct FGenerateIconContext
	{
		/** Setup a zeroed context */
		FGenerateIconContext();

		/** Verify that the icon context is in a valid state*/
		bool IsValid() const;

		TWeakObjectPtr<class UWorld> World;
		TWeakObjectPtr<class AFGRenderTargetStage> Stage;
		TWeakObjectPtr<class UMaterialInstanceConstantFactoryNew> Factory;
		TArray<FString> Prefixes;
	};

	/** Context used when generating icon data */
	static FGenerateIconContext GenerateIconContext;

	/** The jaw of the object when rendering the icon */
	UPROPERTY( EditDefaultsOnly, Category = "Icon", Meta=(NoAutoJSON =true) )
	float mIconYaw;

	/** The distance to the object when rendering the icon */
	UPROPERTY( EditDefaultsOnly, Category = "Icon", meta=( ShowOnlyInnerProperties, NoAutoJSON = true) )
	FItemView mIconView;

	/** The transform used for icon capture */
	UPROPERTY( EditDefaultsOnly, Category = "Icon - EDITOR ONLY", Meta = ( NoAutoJSON = true ) )
	FTransform mIconCameraTransform;

	/** The FOV used for icon capture */
	UPROPERTY( EditDefaultsOnly, Category = "Icon - EDITOR ONLY", Meta = ( NoAutoJSON = true ) )
	float mIconFOV;

	/** The object orientation used for icon capture */
	UPROPERTY( EditDefaultsOnly, Category = "Icon - EDITOR ONLY", Meta = ( NoAutoJSON = true ) )
	FRotator mIconObjectOrientation;

	/** The spring arm distance used for icon capture */
	UPROPERTY( EditDefaultsOnly, Category = "Icon - EDITOR ONLY", Meta = ( NoAutoJSON = true ) )
	float mIconCameraDistance;

	/** The sky orientation used for icon capture */
	UPROPERTY( EditDefaultsOnly, Category = "Icon - EDITOR ONLY", Meta = ( NoAutoJSON = true ) )
	FRotator mIconSkyOrientation;

#endif

	// NOTE: Ideally we want a fluid descriptor but some fluids are already a raw resource so we cannot do multiple inheritance, so either we need refactor how descriptors work or we put them here for now.
	/**
	 * @todoPipes Removing this for now, it was always 1 anyway.
	 * Density for this fluid.
	 * Form must be liquid or gas for this to be useful.
	 */
	UPROPERTY()
	float mFluidDensity;
	/**
	 * @todoPipes Removing this for now, caused more issues than it fixed, the back flow in junctions issue.
	 * Friction for this fluid, this is the friction inside the fluid itself.
	 * Form must be liquid or gas for this to be useful.
	 */
	UPROPERTY()
	float mFluidViscosity;
	/**
	 * Friction for this fluid, this is the friction between the fluid and the pipe.
	 * Form must be liquid or gas for this to be useful.
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Item|Fluid" )
	float mFluidFriction;
	/**
	 * Color for this fluid, RGB is the color and A is the transparency of the fluid.
	 * Form must be liquid or gas for this to be useful.
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Item|Fluid" )
	FColor mFluidColor;

	/** This is just a hook for the resource sink points so we can add them to the 
	* JSON wiki file even though they are in a separate datatable.  
	*/
	UPROPERTY()
	int32 mResourceSinkPoints;

private:
	friend class FItemDescriptorDetails;
	friend class FFGItemDescriptorPropertyHandle;

public:
	FORCEINLINE ~UFGItemDescriptor() = default;
};

FORCEINLINE FString VarToFString(const TSubclassOf<UFGItemDescriptor>& var) { return FString::Printf( TEXT("") ); }
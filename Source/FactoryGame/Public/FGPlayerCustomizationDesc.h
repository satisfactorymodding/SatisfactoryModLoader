// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Resources/FGItemDescriptor.h"
#include "AddOnEntitlement.h"
#include "FGPlayerCustomizationDesc.generated.h"

/**
 * 
 */

class AFGEquipment;
class UStaticMesh;
class USkeletalMesh;
class UMaterialInterface;

/*Base class */
UCLASS(Blueprintable)
class FACTORYGAME_API UFGPlayerCustomizationDesc : public UFGItemDescriptor
{
	GENERATED_BODY()

public:
	UFGPlayerCustomizationDesc();
	
	/**
	 * If a DLC is required for accessing a customization, this will return the source DLC.
	 */
	UFUNCTION( BlueprintCallable )
	static UAddOnEntitlement* GetSourceDLCForCustomization( TSubclassOf< UFGPlayerCustomizationDesc > customizationDesc );

	/** Returns a mesh used to represent this player customization. */
	virtual UStaticMesh* GetRepresentationMesh() const { return nullptr; }

	/** Whether or not the specified Player Customization is unlocked by default. */
	UFUNCTION( BlueprintPure, Category = "Player Customization" )
	static bool IsUnlockedByDefault( TSubclassOf< UFGPlayerCustomizationDesc > Desc );

	/** Whether or not the customization is visible without having entitlement to the content */
	UFUNCTION( BlueprintPure, Category = "Player Customization" )
	static bool IsVisibleByDefault( TSubclassOf<UFGPlayerCustomizationDesc> Desc);
	
protected:
	/**
	 * If provided, this customization will only be available if the player has this entitlement.
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Availability" )
	TSoftObjectPtr< UAddOnEntitlement > mAddOnEntitlement;

	/**
	 * Whether or not this customization is unlocked by default. If not then it needs to be unlocked through a schematic. It can still require DLC even if it's unlocked by default.
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Availability" )
	bool mIsUnlockedByDefault;

	/**
	 * Whether or not the customization is visible without having entitlement to the content.
	 */
	UPROPERTY(EditDefaultsOnly)
	bool mIsVisibleOnDefault;
};

UCLASS(Blueprintable)
class FACTORYGAME_API UFGPlayerHelmetCustomizationDesc : public UFGPlayerCustomizationDesc
{
	GENERATED_BODY()

public:
	// Begin UFGPlayerCustomizationDesc interface
	virtual UStaticMesh* GetRepresentationMesh() const override { return mMesh; }
	// End UFGPlayerCustomizationDesc interface

private:
	/* Static mesh used.*/
	UPROPERTY(EditDefaultsOnly,Category="Visuals")
	UStaticMesh* mMesh;

	/* Offset Applied to the helmet.*/
	UPROPERTY(EditDefaultsOnly,Category="Visuals")
	FTransform mOffset = FTransform::Identity;
	
	/* Used to override current materials, make sure it has the same length as the default number of materials the array ID should be the same as the material slot id.*/
	UPROPERTY(EditDefaultsOnly,Category="Visuals")
	TArray<UMaterialInterface*> mMaterialOverrides;

	/* Used to override current attached socket.*/
	UPROPERTY(EditDefaultsOnly,Category="Visuals")
	FName SocketName = NAME_None;

public:
	UFUNCTION( BlueprintPure, Category="Player Customization|Helmets")
	static UStaticMesh* GetHelmetMesh(TSubclassOf<UFGPlayerHelmetCustomizationDesc> Desc);
	
	UFUNCTION( BlueprintPure, Category="Player Customization|Helmets")
	static FTransform GetHelmetOffset(TSubclassOf<UFGPlayerHelmetCustomizationDesc> Desc);

	UFUNCTION( BlueprintPure, Category="Player Customization|Helmets")
	static TArray<UMaterialInterface*> GetHelmetMaterialOverrides(TSubclassOf<UFGPlayerHelmetCustomizationDesc> Desc);

	UFUNCTION( BlueprintPure, Category="Player Customization|Helmets")
	static FName GetHelmetSocketName(TSubclassOf<UFGPlayerHelmetCustomizationDesc> Desc);
};

UCLASS(Blueprintable)
class FACTORYGAME_API UFGPlayerTrinketCustomizationDesc : public UFGPlayerCustomizationDesc
{
	GENERATED_BODY()
	
public:
	// Begin UFGPlayerCustomizationDesc interface
	virtual UStaticMesh* GetRepresentationMesh() const override { return mTrinketMesh; }
	// End UFGPlayerCustomizationDesc interface

	UPROPERTY(EditDefaultsOnly,Category="Visuals")
	USkeletalMesh* mTrinketChainMesh = nullptr;

	UPROPERTY(EditDefaultsOnly,Category="Visuals")
	FName mTrinketChainSocketName = NAME_None;
	
	UPROPERTY(EditDefaultsOnly,Category="Visuals")
	UStaticMesh* mTrinketMesh = nullptr;
	
	UPROPERTY(EditDefaultsOnly,Category="Visuals")
	FName mTrinketSocketName = NAME_None;

public:
	UFUNCTION( BlueprintPure, Category="Player Customization|Trinkets")
	static USkeletalMesh* GetTrinketChainMesh(TSubclassOf<UFGPlayerTrinketCustomizationDesc> Desc);

	UFUNCTION( BlueprintPure, Category="Player Customization|Trinkets")
	static FName GetTrinketChainSocketName(TSubclassOf<UFGPlayerTrinketCustomizationDesc> Desc);

	UFUNCTION( BlueprintPure, Category="Player Customization|Trinkets")
	static UStaticMesh* GetTrinketMesh(TSubclassOf<UFGPlayerTrinketCustomizationDesc> Desc);
	
	UFUNCTION( BlueprintPure, Category="Player Customization|Trinkets")
	static FName GetTrinketSocketName(TSubclassOf<UFGPlayerTrinketCustomizationDesc> Desc);
};

USTRUCT(BlueprintType)
struct FSkinEntry
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TArray<UMaterialInterface*> mMaterialData;
};

UCLASS(Blueprintable)
class FACTORYGAME_API UFGPlayerEquipmentSkinCustomizationDesc : public UFGPlayerCustomizationDesc
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,Category="Visuals")
	TSubclassOf<AFGEquipment> EquipmentClass;
	
	UPROPERTY(EditDefaultsOnly,Category="Visuals")
	TArray<UMaterialInterface*> mFirstPersonMaterialData;
	
	UPROPERTY(EditDefaultsOnly,Category="Visuals")
	TArray<UMaterialInterface*> mMaterialData;

	UPROPERTY(EditDefaultsOnly)
	TArray<FName> MeshNames = {FName("EquipmentDefaultMesh")};
	
public:
	UFUNCTION( BlueprintPure, Category="Player Customization|Trinkets")
	static TArray<UMaterialInterface*> GetSkinMaterial(TSubclassOf<UFGPlayerEquipmentSkinCustomizationDesc> Desc, bool bFirstPerson, TArray<FName>& ExpectedComponentNames);

	UFUNCTION( BlueprintPure, Category="Player Customization|Trinkets")
	static bool IsSkinSupportedForEquipment(TSubclassOf<UFGPlayerEquipmentSkinCustomizationDesc> Desc,TSubclassOf<AFGEquipment> TargetEquipment);
};
// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGSignInterface.h"
#include "FGSettings.h"
#include "Materials/Material.h"
#include "FGSignSettings.generated.h"


USTRUCT( Blueprintable )
struct FACTORYGAME_API FSignColorData
{
	GENERATED_BODY()

	/** The static mesh that will be rendered on the actual sign in the world */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Sign Data Settings" )
	FLinearColor SignColor;
	
	/** A text name to display with the icon inside of menus */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Sign Data Settings" )
	FText ColorName;

	/** The TEXT material instance is created at runtime and stored here when it is needed */
	UPROPERTY()
	UMaterialInstanceDynamic* TextMaterialInstance;

	/** The ICON material instance is created at runtime and stored here when it is needed */
	UPROPERTY()
	UMaterialInstanceDynamic* IconMaterialInstance;

	/** The BACKGROUND material instance is created at runtime and stored here when it is needed */
	UPROPERTY()
	UMaterialInstanceDynamic* BackgroundMaterialInstance;

public:
	FORCEINLINE ~FSignColorData() = default;
};




/**
 * Master settings for Standalone Sign parameters and attributes
 */
UCLASS( abstract )
class FACTORYGAME_API UFGSignSettings : public UFGSettings
{
	GENERATED_BODY()
	
public:

	/** Helper to get signs settings without going through UFGGlobalSettings */
	static UFGSignSettings* Get();

	UFUNCTION( BlueprintPure, Category = "Sign Data Settings" )
	static const TArray<FSignColorData>& GetSignColorData();

	/** Returns the corresponding text material instance from the sign color data array. If one does not exist yet it is created */
	UFUNCTION( BlueprintPure, Category = "Sign Data Settings" )
	static UMaterialInterface* GetTextMaterialInstanceFromIndex( int32 index );

	/** Returns the corresponding icon material instance from the sign color data array. If one does not exist yet it is created */
	UFUNCTION( BlueprintPure, Category = "Sign Data Settings" )
	static UMaterialInterface* GetIconMaterialInstanceFromIndex( int32 index );

	/** Returns the corresponding background material instance from the sign color data array. If one does not exist yet it is created */
	UFUNCTION( BlueprintPure, Category = "Sign Data Settings" )
	static UMaterialInterface* GetBackgroundMaterialInstanceFromIndex( int32 index );

	/** Returns the index of the background meshes material index for the background material */
	static int32 GetBackgroundMeshMaterialIndex();

public:
	/** Base material to be used for text component material instances */
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings" )
	UMaterial* mTextMaterial;

	/** Base material to be used for icon material instances */
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings" )
	UMaterial* mIconMaterial;

	/** Base material to be used for sign background material instances */
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings" )
	UMaterial* mBackgroundMaterial;

	/** The index in the sign mesh material array pointing to the screen / background material */
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings" )
	int32 mBackgroundMeshMaterialIndex;

	/** Parameter name of color adjustment FVector inside the text material */
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings" )
	FName mTextMaterialColorParam;

	/** Parameter name of color adjustment FVector inside the icon material */
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings" )
	FName mIconMaterialColorParam;

	/** Parameter name of color adjustment FVector inside the background material */
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings" )
	FName mBackgroundMaterialColorParam;

	/** Array of sign color data */
	UPROPERTY( EditDefaultsOnly, Category = "Sign Data Settings" )
	TArray<FSignColorData> mSignColorData;


public:
	FORCEINLINE ~UFGSignSettings() = default;
};

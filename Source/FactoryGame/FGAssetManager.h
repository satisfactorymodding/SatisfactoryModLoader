#pragma once
#include "Array.h"
#include "UnrealString.h"
#include "UObject/Class.h"

#include "Engine/AssetManager.h"
#include "IncludeInBuild.h"
#include "FGAssetManager.generated.h"

/** Help us discard packages that shouldn't be cooked and add assets that's should always be cooked */
UCLASS()
class UFGAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	UFGAssetManager();

#if WITH_EDITOR
	/** Change behavior dependent on the cook parameters */
	virtual void SetCookParameters( const FString& commandlineValues ) /*override MODDING EDIT*/;

	/** Convenient hook for when we want to be able to add more things to the cook */
	virtual void ModifyCook( TArray<FName>& out_packagesToCook, TArray<FName>& out_packagesToNeverCook ) override;
	
	/** Let us exclude certain packages that we don't want to include */
	virtual EPrimaryAssetCookRule GetPackageCookRule( FName PackageName ) const override;
#endif
protected:
#if WITH_EDITORONLY_DATA
	/** Cached version of the max current tier */
	int32 mCachedMaxTechTier;

	/** During cooking step, what's the minimum value of EIncludeInBuild on asset for it to be included in cooks */
	EIncludeInBuilds mMinimumIncludeInBuildFlag;
#endif
};

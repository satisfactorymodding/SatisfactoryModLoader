// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGSettings.h"
#include "FGEnvironmentSettings.generated.h"

class UMaterialParameterCollection;

/**
 * Settings for the environment
 */
UCLASS( abstract )
class FACTORYGAME_API UFGEnvironmentSettings : public UFGSettings
{
	GENERATED_BODY()
public:
#if WITH_EDITOR
	virtual void PostEditChangeProperty( struct FPropertyChangedEvent& propertyChangedEvent ) override;
#endif
	/** The material parameter collection that contains world bounds */
	static UMaterialParameterCollection* GetWorldBoundsParameters();

	/** The collection containing weather parameters like wind direction */
	static UMaterialParameterCollection* GetWeatherParameters();
public:
	/** The collection containing the world bounds*/
	UPROPERTY( EditDefaultsOnly )
	class UMaterialParameterCollection* mWorldBoundsParameters;

	/** The collection containing weather parameters like wind direction */
	UPROPERTY( EditDefaultsOnly )
	class UMaterialParameterCollection* mWeatherParameters;

	/** The parameter name of Min of mWorldBoundsParameters */
	static FName WorldBoundsMinName;
	/** The parameter name of Extent of mWorldBoundsParameters */
	static FName WorldBoundsExtentName;
};

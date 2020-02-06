// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"
#include "Materials/MaterialParameterCollection.h"
#include "FGSettings.h"
#include "FGEnvironmentSettings.generated.h"

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
public:
	/** The collection containing the world bounds*/
	UPROPERTY( EditDefaultsOnly )
	class UMaterialParameterCollection* mWorldBoundsParameters;

	/** The parameter name of Min of mWorldBoundsParameters */
	static FName WorldBoundsMinName;
	/** The parameter name of Extent of mWorldBoundsParameters */
	static FName WorldBoundsExtentName;
};

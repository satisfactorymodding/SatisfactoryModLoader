// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "EnvironmentQuery/Generators/EnvQueryGenerator_ProjectedPoints.h"
#include "UObject/UObjectGlobals.h"
#include "Templates/SubclassOf.h"
#include "DataProviders/AIDataProvider.h"
#include "FGEnvQueryGenerator_ForAngle.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGEnvQueryGenerator_ForAngle : public UEnvQueryGenerator_ProjectedPoints
{
	GENERATED_BODY()
public:
	UFGEnvQueryGenerator_ForAngle( const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get() );

	/** Binds data to data providers
	*  @param QueryInstance - the instance of the query
	*/
	void BindDataToDataProviders( FEnvQueryInstance& QueryInstance ) const;

	/** Generate points from the querier and outwards in an angle */
	virtual void GenerateItems( FEnvQueryInstance& QueryInstance ) const override;
public:
	/** Total distance for point generation */
	UPROPERTY( EditDefaultsOnly, Category = Generator )
	FAIDataProviderFloatValue mDistance;

	/** Angle to generate points for  */
	UPROPERTY( EditDefaultsOnly, Category = Generator )
	FAIDataProviderFloatValue mAngle;

	/** The step of the angle increase. Angle step must be >=1
	*  Smaller values generate less items
	*/
	UPROPERTY( EditDefaultsOnly, Category = Generator )
	FAIDataProviderFloatValue mStepSize;

	/** Should we also generate points for the negative angle value? */
	UPROPERTY( EditDefaultsOnly, Category = Generator )
	FAIDataProviderBoolValue mGenerateMirroredPoints;

	/** The actor (or actors) that will generate a cone in their facing direction */
	UPROPERTY( EditAnywhere, Category = Generator )
	TSubclassOf< UEnvQueryContext > mCenterActor;
	

public:
	FORCEINLINE ~UFGEnvQueryGenerator_ForAngle() = default;
};

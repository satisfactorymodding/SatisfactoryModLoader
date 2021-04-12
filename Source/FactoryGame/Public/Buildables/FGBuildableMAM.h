// Copyright 2021 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "FGSignificanceInterface.h"
#include "FGResearchManager.h"
#include "FGBuildableMAM.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableMAM : public AFGBuildable, public IFGSignificanceInterface
{
	GENERATED_BODY()

public:
	// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason );
	// End AActor Interface

	//Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	virtual float GetSignificanceRange() override { return mSignificanceRange; }
	virtual void GainedSignificance_Native() override;
	virtual void LostSignificance_Native() override;
	//End IFGSignificanceInterface

	UFUNCTION( BlueprintImplementableEvent, Category = "MAM" )
	void ResearchStateChanged( EResearchState researchState );

	UFUNCTION( BlueprintCallable, Category = "MAM" )
	bool IsSignificant() const { return mIsSignificant; }

private:
	UFUNCTION()
	void OnResearchStateChanged( EResearchState researchState );

private:
	/** Indicates if the factory is within significance distance */
	bool mIsSignificant = false;

	/** The range to keep the factory in significance */
	UPROPERTY( EditDefaultsOnly, Category = "Significance" )
	float mSignificanceRange = 18000.0f;
};

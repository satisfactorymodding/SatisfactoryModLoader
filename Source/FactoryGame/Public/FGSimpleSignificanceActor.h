// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSignificanceInterface.h"
#include "GameFramework/Actor.h"
#include "FGSimpleSignificanceActor.generated.h"

/** Simple actor that has its tick rate controlled by the significance manager */
UCLASS()
class FACTORYGAME_API AFGSimpleSignificanceActor : public AActor, public IFGSignificanceInterface
{
	GENERATED_BODY()
public:
	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	// End AActor interface

	/** Returns true if this actor is currently significant to the local player */
	UFUNCTION( BlueprintPure, Category = "Significance" )
	FORCEINLINE bool GetIsSignificant() const { return mIsSignificant; }

	// Begin IFGSignificanceInterface
	virtual float GetSignificanceRange_Implementation() const override;
	virtual void GainedSignificance_Implementation() override;
	virtual void LostSignificance_Implementation() override;
	virtual FFGSignificanceTickRateSettings GetSignificanceTickRateSettings_Implementation() const override;
	virtual void UpdateSignificanceTickRate_Implementation(float NewTickRate, bool bTickEnabled) override;
	// End IFGSignificanceInterface
protected:
	/** Range of significance for the actor */
	UPROPERTY( EditDefaultsOnly, Category = "Significance" )
	float mSignificanceRange{15000.0f};

	/** Number of tick levels for tick management */
	UPROPERTY( EditDefaultsOnly, Category = "Significance" )
	int32 mNumTickLevels{5};

	/** True if this actor is significant to the local player */
	bool mIsSignificant{false};
};

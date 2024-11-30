// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSignificanceInterface.h"
#include "Buildables/FGBuildable.h"
#include "FGBuildableSnowCannon.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableSnowCannon : public AFGBuildable, public IFGSignificanceInterface
{
	GENERATED_BODY()

public:
	AFGBuildableSnowCannon();
	
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

	//Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	virtual float GetSignificanceRange() override { return mSignificanceRange; }
	virtual void SetInitialState(bool bState) override { mIsSignificant = bState; }
	//End IFGSignificanceInterface

	UFUNCTION( BlueprintPure, Category = "Significance" )
	FORCEINLINE bool GetIsSignificant() const { return mIsSignificant; }

	const FInt32Interval& GetAngleLimit() const { return mAngleLimit; }
	int32 GetAngleOffset() const { return mAngleOffset; }

	class UFGColoredInstanceMeshProxy* GetBaseMeshComponent() const { return mBaseMeshComponent; }
	class UFGColoredInstanceMeshProxy* GetHeadMeshComponent() const { return mHeadMeshComponent; }

	void SetCannonAngle( int32 angle );

private:
	void UpdateCannonMesh();
	
protected:
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Snow Cannon" )
	class UFGColoredInstanceMeshProxy* mBaseMeshComponent;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Snow Cannon" )
	class UFGColoredInstanceMeshProxy* mHeadMeshComponent;
	
private:
	/** The range to keep the snow cannon in significance */
	UPROPERTY( EditDefaultsOnly, Category = "Significance" )
	float mSignificanceRange;
	
	UPROPERTY( EditDefaultsOnly, Category = "Snow Cannon" )
	FInt32Interval mAngleLimit;
	
	UPROPERTY( EditDefaultsOnly, Category = "Snow Cannon" )
	int32 mAngleOffset;

	UPROPERTY( SaveGame )
	int32 mCannonAngle;
	
	bool mIsSignificant;
};

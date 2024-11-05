// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"
#include "UObject/NoExportTypes.h"
#include "FGWeatherReaction.generated.h"

/**
 * 
 */

class AFGSkySphere;

UCLASS(Blueprintable)
class FACTORYGAME_API AFGWeatherReaction : public AActor
{
	GENERATED_BODY()

	AFGWeatherReaction();
	
public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	UFUNCTION( BlueprintNativeEvent )
	void StartWeatherState( AFGSkySphere* SkySphere );

	/* Will auto destroy once done. */
	UFUNCTION( BlueprintNativeEvent )
	void EndWeatherState( AFGSkySphere* SkySphere );

	UFUNCTION(BlueprintPure, Category = "Weather")
	AFGSkySphere* GetSkySphere() const { return mSkySphere; }

protected:
	UFUNCTION( BlueprintImplementableEvent )
	void TransitionBeginWeatherState( float Dt, float Percentage );

	/* Blueprint event for updating the weather state. */
	UFUNCTION( BlueprintImplementableEvent )
	void TransitionEndWeatherState( float Dt, float Percentage );

	UFUNCTION( BlueprintImplementableEvent )
	void OnTransitionFinished( bool bEventFinished );
	
private:
	/* seconds the transition takes.*/
	UPROPERTY( EditDefaultsOnly )
	float TransitionTime;

	float mSpawnTime;
	
	UPROPERTY()
	AFGSkySphere* mSkySphere;

	/* is it stopping? or starting*/
	bool bIsWindingDown;
};

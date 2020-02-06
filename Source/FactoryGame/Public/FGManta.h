// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGSignificanceInterface.h"
#include "FGManta.generated.h"

UCLASS()
class FACTORYGAME_API AFGManta : public AActor, public IFGSignificanceInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGManta();

	//IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	virtual float GetSignificanceRange() override; 
	//End

	/** Gets time variable */
	UFUNCTION( BlueprintPure, Category = "Manta" )
	FORCEINLINE float GetCurrentTime() { return mCurrentTime; }

	/** Gets spline*/
	UFUNCTION( BlueprintPure, Category = "Manta" )
	FORCEINLINE class USplineComponent* GetSpline() { return mCachedSpline; }
protected:
	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;

	/** Updates the mantas location based on values being ticked */
	void UpdateManta();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private: 
	/** Reference to the spline that was added in BP */
	UPROPERTY()
	class USplineComponent* mCachedSpline;

	/** Path spline that this actor should set to follow */
	UPROPERTY( EditAnywhere, Category = "Manta" )
	class AFGSplinePath* mSplinePath;

	/** Reference to the skel mesh that was added in BP */
	UPROPERTY()
	class USkeletalMeshComponent* mCachedMesh;
	
	/** Value between 0.0 - 1.0 */
	float mPosition; 
	/** Current time ( value between 0.0 and mSecondsPerLoop */
	UPROPERTY( Replicated )
	float mCurrentTime;

	/** Magnitude of the offset to add  */
	UPROPERTY( EditDefaultsOnly, Category = "Manta" )
	float mOffsetMagnitude;

	/** How many seconds a complete loop should take ( defaults to 900 ie 15 minutes ) */
	UPROPERTY( EditInstanceOnly, Category = "Manta" )
	float mSecondsPerLoop;

	/** Is this volume in significance range */
	bool mIsSignificant;

	/** Range that this volume should be significant within */
	UPROPERTY( EditDefaultsOnly, Category = "Significance" )
	float mSignificanceRange;

	/** Should we tick this mesh */
	UPROPERTY( EditDefaultsOnly, Category = "Manta" )
	bool mTickTransform;

	/** Is the spline loop closed */
	UPROPERTY( EditDefaultsOnly, Category = "Manta" )
	bool mIsClosedSplineLoop;
};

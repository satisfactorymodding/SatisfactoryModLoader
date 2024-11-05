// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimInstanceProxy.h"
#include "FGAnimInstanceTruckStation.generated.h"

USTRUCT( BlueprintType )
struct FACTORYGAME_API FAnimInstanceProxyTruckStation : public FAnimInstanceProxy
{
	GENERATED_BODY()

		FAnimInstanceProxyTruckStation() : FAnimInstanceProxy(),
		StateMachineName( TEXT( "None" ) ),
		AnimPlayRate( 1.0f ),
		RampUpTime( 0.0f ),
		RampDownTime( 0.0f ),
		HasPower( false ),
		IsLoading( false ),
		IsUnloading( false ),
		IsProducing( false ),
		OfflineToLoadTransition( false ),
		OfflineToUnloadTransition( false ),
		LoadToOfflineTransition( false ),
		UnloadToOfflineTransition( false )
	{}

	FAnimInstanceProxyTruckStation( UAnimInstance* Instance ) : FAnimInstanceProxy( Instance )
	{
	}

	// Begin FAnimInstanceProxy
	virtual void Initialize( UAnimInstance* InAnimInstance ) override;
	virtual void PreUpdate( UAnimInstance* InAnimInstance, float DeltaSeconds ) override;
	virtual void Update( float DeltaSeconds ) override;
	// End FAnimInstanceProxy
public:
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	FName StateMachineName;

	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float AnimPlayRate;

	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float RampUpTime;

	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float RampDownTime;
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 HasPower : 1;

	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 IsLoading : 1;

	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 IsUnloading : 1;

	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 IsProducing : 1;

	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 OfflineToLoadTransition : 1;

	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 OfflineToUnloadTransition : 1;

	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 LoadToOfflineTransition : 1;

	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 UnloadToOfflineTransition : 1;
};

UCLASS()
class FACTORYGAME_API UFGAnimInstanceTruckStation : public UAnimInstance
{
	GENERATED_BODY()
protected:
	// Begin UAnimInstance
	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override { return &mProxy; }
	virtual void DestroyAnimInstanceProxy( FAnimInstanceProxy* InProxy ) override {}
	// End UAnimInstance
public:
	/** Time factory should spend ramping up */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	float mRampUpTime;

	/** Time factory should spend ramping up */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	float mRampDownTime;

	/**Name of the state machine that does stuff*/
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	FName mStateMachineName;
protected:
	UPROPERTY( Transient, BlueprintReadOnly, Category = "Factory Anim", meta = (AllowPrivateAccess = "true") )
	FAnimInstanceProxyTruckStation mProxy;
};

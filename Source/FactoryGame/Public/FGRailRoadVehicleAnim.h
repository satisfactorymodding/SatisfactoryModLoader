// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "../../Plugins/Wwise/Source/AkAudio/Classes/AkAudioEvent.h"
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimInstanceProxy.h"
#include "FGRailRoadVehicleAnim.generated.h"

USTRUCT( BlueprintType )
struct FACTORYGAME_API FAnimInstanceProxyRailRoadVehicle : public FAnimInstanceProxy
{
	GENERATED_BODY()

	FAnimInstanceProxyRailRoadVehicle() : FAnimInstanceProxy(),
		mDeltaTime(0),
		mFrontBogieRotation(EForceInit::ForceInitToZero),
		mBackBogieRotation(EForceInit::ForceInitToZero),
		mWheelRotation(EForceInit::ForceInitToZero),
		mFrontConnectorRotation(EForceInit::ForceInitToZero),
		mFrontConnectorTranslation(EForceInit::ForceInitToZero),
		mBackConnectorRotation(EForceInit::ForceInitToZero),
		mBackConnectorTranslation(EForceInit::ForceInitToZero),
		mTrackCurvature(EForceInit::ForceInitToZero),
		mForwardSpeed(0),
		mTractiveForce(0),
		mHandBrakeForce(0),
		mThrottle(0),
		mBrakeForce(0),
		mHandBrakeForceSpeed(0),
		mHandBrakeGlow(0),
		mHandBrakeVfxSpawn(0),
		mAGBrakePlayRate(0),
		mIsMoving(false),
		mIsUsingHandBrake(false),
		mIsLocomotive(false),
		mHasPower(false),
		mAGThrottleZero(false),
		mAGThrottlePositive(false),
		mAGStartToRunningTransition(false),
		mAGHandBrakeTransition01(false),
		mAGHandBrakeTransition02(false),
		mAGBrakeForcePositive(false),
		mAGBrakeToRunningTransition(false),
		mAGHandBrakeReset01(false),
		mAGHandBrakeReset02(false),
		mAGHandBrakeStop(false)
	{
	}

	FAnimInstanceProxyRailRoadVehicle( UAnimInstance* Instance ) : FAnimInstanceProxy( Instance )
	{
	}
	virtual void PreUpdate( UAnimInstance* InAnimInstance, float DeltaSeconds ) override;

	virtual void Update( float DeltaSeconds ) override;

	/** Called when our anim instance is being initialized */
	virtual void Initialize( UAnimInstance* InAnimInstance ) override;
public:
	/** saved DT */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float mDeltaTime;

	/** Front Bogie Rotation */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	FRotator mFrontBogieRotation;

	/** Front Bogie Rotation */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	FRotator mBackBogieRotation;

	/** Wheel Rotation */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	FRotator mWheelRotation;

	/** Front Connector Rotation */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	FRotator mFrontConnectorRotation;

	/** Front Connector Translation */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	FVector mFrontConnectorTranslation;

	/** Back Connector Rotation */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	FRotator mBackConnectorRotation;

	/** Back Connector Translation */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	FVector mBackConnectorTranslation;

	/** Track curvature */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	FRotator mTrackCurvature;

	/** Forward speed */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float mForwardSpeed;

	/** Tractive force */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float mTractiveForce;

	/** Hand break */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float mHandBrakeForce;

	/** Throttle */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float mThrottle;

	/** brake force */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float mBrakeForce;

	/** hand brake force multiplied with forward speed and clamped within nice values */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float mHandBrakeForceSpeed;

	/** Glow value for when using handbrake on moving vehicle */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float mHandBrakeGlow;

	/** Spawn rate of brake particles */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float mHandBrakeVfxSpawn;

	/** Bigge values, I dunno */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float mAGBrakePlayRate;

	/** Is Moving */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 mIsMoving : 1;

	/** is break boosting */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 mIsUsingHandBrake : 1;

	/** Is Locomotive*/
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 mIsLocomotive : 1;

	/** Has Power*/
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 mHasPower : 1;

	/** Is throttle value zero */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 mAGThrottleZero : 1;

	/** Is throttle value positive */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 mAGThrottlePositive : 1;

	/** Phase when train starts moving */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 mAGStartToRunningTransition : 1;

	/** Bigge values, I dunno */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 mAGHandBrakeTransition01 : 1;

	/** Bigge values, I dunno */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 mAGHandBrakeTransition02 : 1;

	/** Bigge values, I dunno */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 mAGBrakeForcePositive : 1;

	/** Bigge values, I dunno */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 mAGBrakeToRunningTransition : 1;

	/** Bigge values, I dunno */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 mAGHandBrakeReset01 : 1;

	/** Bigge values, I dunno */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 mAGHandBrakeReset02 : 1;

	/** Bigge values, I dunno */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 mAGHandBrakeStop : 1;

public:
	FORCEINLINE ~FAnimInstanceProxyRailRoadVehicle() = default;
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGRailRoadVehicleAnim : public UAnimInstance
{
	GENERATED_BODY()
public:
	/** Constructor */
	UFGRailRoadVehicleAnim();

	virtual void NativeUpdateAnimation( float DeltaSeconds ) override;

	virtual void NativeInitializeAnimation() override;

	UFUNCTION( BlueprintCallable, Category = "Rail Road Vehicle Anim" )
	void SetUsingHandBrake( bool inValue );

	FORCEINLINE bool IsUsingHandBrake() { return mIsUsingHandBrake; }

	UFUNCTION( BlueprintCallable, Category = "Rail Road Vehicle Anim" )
	void SetupHandBrakeEffects();

	UFUNCTION( BlueprintCallable, Category = "Rail Road Vehicle Anim" )
	void RemoveBrakeEffects();

	UFUNCTION( BlueprintCallable, Category = "Rail Road Vehicle Anim" )
	void RemoveHandBrakeEffects();

	UFUNCTION( BlueprintCallable, Category = "Rail Road Vehicle Anim" )
	void TriggerHandBrakeVfx();
protected:
	UPROPERTY( Transient, BlueprintReadOnly, Category = "Rail Road Vehicle Anim", meta = ( AllowPrivateAccess = "true" ) )
	FAnimInstanceProxyRailRoadVehicle mProxy;

	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override
	{
		return &mProxy;
	}

	virtual void DestroyAnimInstanceProxy( FAnimInstanceProxy* InProxy ) override
	{

	}

	friend struct FAnimInstanceProxyRailRoadVehicle;
public:
	/** The UCurveFloat specifying brake force */
	UPROPERTY( EditDefaultsOnly, Category = "Rail Road Vehicle Anim" )
	UCurveFloat* mBrakeCurve;
private:
	bool mIsUsingHandBrake;

	/** Trains material */
	UPROPERTY()
	UMaterialInstanceDynamic* mTrainMaterial;

	/** Collection of brake socket names */
	UPROPERTY( EditDefaultsOnly, Category = "Rail Road Vehicle Anim" )
	TArray< FName > mBrakeSocketNames;

	/** Collection of brake effect particle components */
	UPROPERTY()
	TArray< UParticleSystemComponent* > mBrakeEffects;

	/** Collection of steam socket names */
	UPROPERTY( EditDefaultsOnly, Category = "Rail Road Vehicle Anim" )
	TArray< FName > mSteamSocketNames;

	/** Collection of brake effect particle components */
	UPROPERTY()
	TArray< UParticleSystemComponent* > mSteamEffects;


	/** Template for brake sparks particle */
	UPROPERTY( EditDefaultsOnly, Category = "Rail Road Vehicle Anim" )
	UParticleSystem* mBrakeSparkTemplate;

	/** Template for steam particle */
	UPROPERTY( EditDefaultsOnly, Category = "Rail Road Vehicle Anim" )
	UParticleSystem* mSteamTemplate;

	/** Sound for when braking stops and steam occurs */
	UPROPERTY( EditDefaultsOnly, Category = "Rail Road Vehicle Anim" )
	class UAkAudioEvent* mBrakeSound;

	/** Template for brake effect */
	UPROPERTY( EditDefaultsOnly, Category = "Rail Road Vehicle Anim" )
	UParticleSystem* mHandBrakeVfxTemplate;

	/** Template for brake effect */
	UPROPERTY()
	UParticleSystemComponent* mHandBrakeVfxComponent;

public:
	FORCEINLINE ~UFGRailRoadVehicleAnim() = default;
};

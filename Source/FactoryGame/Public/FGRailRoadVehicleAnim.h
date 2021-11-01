// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimInstanceProxy.h"
#include "FGRailroadVehicleAnim.generated.h"

USTRUCT( BlueprintType )
struct FACTORYGAME_API FAnimInstanceProxyRailroadVehicle : public FAnimInstanceProxy
{
	GENERATED_BODY()

	FAnimInstanceProxyRailroadVehicle() : FAnimInstanceProxy(),
		mSpeed(0),
		mMaxSpeed(0),
    	mTractionPct(0),
    	mAirBrakePct(0),
    	mDynamicBrakePct(0),
    	mWheelsetRotation0(EForceInit::ForceInitToZero),
        mWheelsetRotation1(EForceInit::ForceInitToZero),
        mCouplerRotation0(EForceInit::ForceInitToZero),
        mCouplerRotation1(EForceInit::ForceInitToZero),
        mCouplerExtension0(0),
        mCouplerExtension1(0),
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

	FAnimInstanceProxyRailroadVehicle( UAnimInstance* Instance ) : FAnimInstanceProxy( Instance )
	{
	}

	// Begin FAnimInstanceProxy
	virtual void PreUpdate( UAnimInstance* inAnimInstance, float dt ) override;
	virtual void Update( float dt ) override;
	virtual void Initialize( UAnimInstance* inAnimInstance ) override;
	// End FAnimInstanceProxy
	
public:
	// Copied data
	float mSpeed;
	float mMaxSpeed;
	float mTractionPct;
	float mAirBrakePct;
	float mDynamicBrakePct;
	FVector mWheelsetRotation0;
	FVector mWheelsetRotation1;
	FVector mCouplerRotation0;
	FVector mCouplerRotation1;
	float mCouplerExtension0;
	float mCouplerExtension1;
	
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
};

UCLASS()
class FACTORYGAME_API UFGRailroadVehicleAnim : public UAnimInstance
{
	GENERATED_BODY()
public:
	UFGRailroadVehicleAnim();

	// Begin UAnimInstance
	virtual void NativeUpdateAnimation( float dt ) override;
	virtual void NativeInitializeAnimation() override;
	// End UAnimInstance

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
	// Begin UAnimInstance
	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override { return &mProxy; }
	virtual void DestroyAnimInstanceProxy( FAnimInstanceProxy* inProxy ) override {}
	// End UAnimInstance
	
public:
	/** The UCurveFloat specifying brake force */
	UPROPERTY( EditDefaultsOnly, Category = "Rail Road Vehicle Anim" )
	UCurveFloat* mBrakeCurve;
	
	/** Cached in init. */
	UPROPERTY()
	class AFGRailroadVehicle* mVehicle;
	
	/** Cached in init. */
	UPROPERTY()
	class AFGLocomotive* mLocomotive;

protected:
	UPROPERTY( Transient, BlueprintReadOnly, Category = "Rail Road Vehicle Anim", meta = ( AllowPrivateAccess = "true" ) )
	FAnimInstanceProxyRailroadVehicle mProxy;
	
private:
	friend struct FAnimInstanceProxyRailRoadVehicle;
	
	/** Are the handbrake effects playing? */
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
};

// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimInstanceProxy.h"
#include "FGFAnimInstanceFactory.generated.h"

USTRUCT( BlueprintType )
struct FAnimInstanceProxyFactory : public FAnimInstanceProxy
{
	GENERATED_BODY()

	FAnimInstanceProxyFactory() : FAnimInstanceProxy()
	{}

	FAnimInstanceProxyFactory( UAnimInstance* Instance ) : FAnimInstanceProxy( Instance ) 
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

	/** saved production progress for the factory */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float mProductionProgress;

	/** saved production cycle time for the factory */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float mProductionCycleTime;

	/** Multiplier for play rate */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float mAnimPlayRate;

	/** Time factory should spend ramping up */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float mRampUpTime;

	/** Time factory should not produce stuff */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float mTimeNotProducing;

	/** Time factory should spend ramping up */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float mRampDownTime;

	/** Last frames production progress */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float mLastProductionProgress;

	/** Play rate for recipe */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float mRecipePlayRate;

	/** Length of production cycle */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float mCycleTime;

	/** Actual animation length */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float mDefaultCycleTime;

	/** Frame to...start?...i dunno */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float mStartFrame;

	/** From 0.0 - 1.0 Only valid for generators! */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	float mLoadPercentage;

	/** valid for generators! */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	bool mHasFuel;

	/** Factory has power */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 mHasPower : 1;

	/** Factory is producing something */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 mIsProducing : 1;

	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 mIsActivated : 1;

	/** A production cycle was completed */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 mCycleComplete : 1;

	/** If we should use the ramp up system */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 mUseRampUp : 1;

	/** Is the owning actor a generator */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 mIsGenerator : 1;

	/** True if generator has power and is producing */
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 mIsFuelGeneratorOnline : 1;
};

/**
 * 
 */
UCLASS( Transient, Blueprintable )
class FACTORYGAME_API UFGFAnimInstanceFactory : public UAnimInstance
{
	GENERATED_BODY()
public:
	/** Constructor */
	UFGFAnimInstanceFactory();

	virtual void NativeUpdateAnimation( float DeltaSeconds ) override;

	virtual void NativeInitializeAnimation() override;

	/** Function for updating a rtpc at intervals */
	virtual void UpdateSoundRTPC( float DeltaSeconds );
protected:
	UPROPERTY( Transient, BlueprintReadOnly, Category = "Factory Anim", meta = ( AllowPrivateAccess = "true" ) )
	FAnimInstanceProxyFactory mProxy;

	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override
	{
		return &mProxy;
	}

	virtual void DestroyAnimInstanceProxy( FAnimInstanceProxy* InProxy ) override
	{

	}

	friend struct FAnimInstanceProxyFactory;
public:
	/** If we should use the ramp up system */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	bool mUseRampUp;

	/** Time factory should spend ramping up */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	float mRampUpTime;

	/** Time factory should spend ramping up */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	float mRampDownTime;

	/** Actual animation length */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	float mDefaultCycleTime;

	/** RTPC for sound speed */
	UPROPERTY( EditDefaultsOnly , Category = "Anim" )
	FName mSoundSpeedRTPC;

	/** How often RTPC for sound speed should update */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	float mSoundSpeedRTPCInterval;

	/** Accumulator for the interval */
	UPROPERTY()
	float mSoundSpeedAccumulator;

	/** Is this factory a generator? */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	bool mIsGenerator;

	/** Min value for RTPC range */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	float mSoundSpeedRTPCMinValue;

	/** Max value for RTPC range */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	float mSoundSpeedRTPCMaxValue;
};

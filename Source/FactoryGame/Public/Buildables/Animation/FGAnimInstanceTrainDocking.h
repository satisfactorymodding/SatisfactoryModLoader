// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimInstanceProxy.h"
#include "../FGBuildableTrainPlatform.h"
#include "FGAnimInstanceTrainDocking.generated.h"

USTRUCT( BlueprintType )
struct FACTORYGAME_API FAnimInstanceProxyTrainDocking: public FAnimInstanceProxy
{
	GENERATED_BODY()

	FAnimInstanceProxyTrainDocking() : FAnimInstanceProxy(),
		TranslationOffset( FVector::ZeroVector ),
		DockingStatus( ETrainPlatformDockingStatus::ETPDS_None ),
		HasPower( false ),
		IsFullLoad( false ),
		IsFullUnload( false ),
		ShouldEnterTransferState( false ),
		ShouldEnterOfflineState( false )
	{}

	FAnimInstanceProxyTrainDocking( UAnimInstance* Instance ) : FAnimInstanceProxy( Instance )
	{
	}
	virtual void PreUpdate( UAnimInstance* InAnimInstance, float DeltaSeconds ) override;

	virtual void Update( float DeltaSeconds ) override;

	/** Called when our anim instance is being initialized */
	virtual void Initialize( UAnimInstance* InAnimInstance ) override;
public:
	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	FVector TranslationOffset;

	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	ETrainPlatformDockingStatus DockingStatus;

	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 HasPower : 1;

	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 IsFullLoad : 1;

	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 IsFullUnload : 1;

	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 ShouldEnterTransferState : 1;

	UPROPERTY( Transient, BlueprintReadWrite, EditAnywhere, Category = "Anim" )
	uint8 ShouldEnterOfflineState : 1;



public:
	FORCEINLINE ~FAnimInstanceProxyTrainDocking() = default;
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGAnimInstanceTrainDocking : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY( Transient, BlueprintReadOnly, Category = "Factory Anim", meta = (AllowPrivateAccess = "true") )
	FAnimInstanceProxyTrainDocking mProxy;;

	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override
	{
		return &mProxy;
	}

	virtual void DestroyAnimInstanceProxy( FAnimInstanceProxy* InProxy ) override
	{

	}

	friend struct FAnimInstanceProxyTrainDocking;
	

public:
	FORCEINLINE ~UFGAnimInstanceTrainDocking() = default;
};

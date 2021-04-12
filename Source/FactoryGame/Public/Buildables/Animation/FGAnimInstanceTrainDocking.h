// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimInstanceProxy.h"
#include "Buildables/FGBuildableTrainPlatform.h"
#include "FGAnimInstanceTrainDocking.generated.h"

USTRUCT( BlueprintType )
struct FACTORYGAME_API FAnimInstanceProxyTrainDocking : public FAnimInstanceProxy
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

	// Begin FAnimInstanceProxy
	virtual void PreUpdate( UAnimInstance* InAnimInstance, float DeltaSeconds ) override;
	virtual void Update( float DeltaSeconds ) override;
	virtual void Initialize( UAnimInstance* InAnimInstance ) override;
	// End FAnimInstanceProxy
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
};

UCLASS()
class FACTORYGAME_API UFGAnimInstanceTrainDocking : public UAnimInstance
{
	GENERATED_BODY()
protected:
	// Begin UAnimInstance
	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override { return &mProxy; }
	virtual void DestroyAnimInstanceProxy( FAnimInstanceProxy* InProxy ) override {}
	// End UAnimInstance

protected:
	UPROPERTY( Transient, BlueprintReadOnly, Category = "Factory Anim", meta = (AllowPrivateAccess = "true") )
	FAnimInstanceProxyTrainDocking mProxy;;
};

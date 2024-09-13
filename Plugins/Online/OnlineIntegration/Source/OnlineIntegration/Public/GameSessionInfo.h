// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonSessionTypes.h"
#include "MVVMViewModelBase.h"
#include "GameSessionInfo.generated.h"

/**
 * 
 */
UCLASS()
class UE_DEPRECATED(5.3, "This type is getting replaced by UOnlineSessionInfo.") ONLINEINTEGRATION_API UGameSessionInfo : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	
protected:
	void Initialize(FCommonSession InPlatformSession, TOptional<FCommonSession> InCrossPlaySession);
	
private:
	FString MakeSessionIdString() const;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	bool bIsCrossPlaySession = false;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	FCommonSession PlatformSession;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	FCommonSession ExternalSession;

	UPROPERTY(BlueprintReadOnly, FieldNotify, meta=(AllowPrivateAccess))
	FString SessionIdString;
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "IEOSSDKManager.h"
#include "OnlineServicesEOS.h"
#include "EOSReportPlayerExtension.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerReportSendComplete, bool, isSuccessful);

UENUM(BlueprintType)
enum class EPlayerReportsCategoryFrontEnd : uint8
{
	Invalid,
	Cheating,
	Exploiting,
	OffensiveProfile,
	VerbalAbuse,
	Scamming,
	Spamming,
	Other
};

typedef UE::Online::FAccountId FAccountId;

UCLASS()
class ONLINEINTEGRATIONEOSEXTENSIONS_API UEOSReportPlayerExtension : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	UFUNCTION(BlueprintCallable)
	void SendReportToEOS(UOnlineUserBackendLink* SenderBackend, UOnlineUserBackendLink* ReportedBackend, EPlayerReportsCategoryFrontEnd ReportsCategory, FString Description);

	static void OnReportSendCompleted(const EOS_Reports_SendPlayerBehaviorReportCompleteCallbackInfo* Data);
	
	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
	FOnPlayerReportSendComplete OnPlayerReportSendComplete;

private:
	EOS_HReports EOSReportsHandle;
};


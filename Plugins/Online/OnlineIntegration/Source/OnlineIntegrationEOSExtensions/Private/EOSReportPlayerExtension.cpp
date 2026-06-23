#include "EOSReportPlayerExtension.h"

#include "GameFramework/OnlineReplStructs.h"

void UEOSReportPlayerExtension::Initialize(FSubsystemCollectionBase& Collection){ }
void UEOSReportPlayerExtension::SendReportToEOS(UOnlineUserBackendLink* SenderBackend, UOnlineUserBackendLink* ReportedBackend, EPlayerReportsCategoryFrontEnd ReportsCategory, FString Description){ }
void UEOSReportPlayerExtension::SendReportToEOSWithPlayerNetID(UOnlineUserBackendLink* SenderBackend,
	FUniqueNetIdRepl ReportedPlayerInfo, EPlayerReportsCategoryFrontEnd ReportsCategory, FString Description){ }
void UEOSReportPlayerExtension::SendReportToEOS(EOS_ProductUserId LocalProductUserId,
	EOS_ProductUserId ReportedProductUserId, EPlayerReportsCategoryFrontEnd ReportsCategory, FString Description){ }
void UEOSReportPlayerExtension::OnReportSendCompleted(const EOS_Reports_SendPlayerBehaviorReportCompleteCallbackInfo* Data){ }

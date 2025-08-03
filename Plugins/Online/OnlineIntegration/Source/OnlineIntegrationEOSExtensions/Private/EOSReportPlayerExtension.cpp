#include "EOSReportPlayerExtension.h"

void UEOSReportPlayerExtension::Initialize(FSubsystemCollectionBase& Collection){ }
void UEOSReportPlayerExtension::SendReportToEOS(UOnlineUserBackendLink* SenderBackend, UOnlineUserBackendLink* ReportedBackend, EPlayerReportsCategoryFrontEnd ReportsCategory, FString Description){ }
void UEOSReportPlayerExtension::OnReportSendCompleted(const EOS_Reports_SendPlayerBehaviorReportCompleteCallbackInfo* Data){ }

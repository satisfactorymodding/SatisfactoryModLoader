#include "BulkDataReplicationModule.h"

void FBulkDataReplicationModule::StartupModule(){ }
void FBulkDataReplicationModule::ShutdownModule(){ }

DEFINE_LOG_CATEGORY(LogReliableMessaging);
IMPLEMENT_GAME_MODULE(FBulkDataReplicationModule, ReliableMessaging);
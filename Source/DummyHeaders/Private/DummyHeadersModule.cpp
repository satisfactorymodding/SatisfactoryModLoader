#include "DummyHeadersModule.h"
#include "AkMetering.h"

void FDummyHeadersModule::StartupModule() {
	UPackage* AkAudioPackage = FindPackage(nullptr, TEXT("/Script/AkAudio"));
	FAkBusMeteringInfo::StaticStruct()->Rename(nullptr, AkAudioPackage, REN_DontCreateRedirectors | REN_NonTransactional);
}

void FDummyHeadersModule::ShutdownModule() {
}

IMPLEMENT_GAME_MODULE(FDummyHeadersModule, DummyHeaders);

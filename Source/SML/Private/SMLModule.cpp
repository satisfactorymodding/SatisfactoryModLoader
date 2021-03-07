#include "SMLModule.h"
#include "SatisfactoryModLoader.h"

void FSMLModule::StartupModule() {
//TODO uncomment when we will get FactoryGame DLL for editor target
#if !WITH_EDITOR
	//Basic subsystems like logging are initialized on OnInit
	FSatisfactoryModLoader::PreInitializeModLoading();
        
	//UObject subsystem and Engine are initialized on PostEngineInit and we need to delay their initialization to that moment
	FCoreDelegates::OnPostEngineInit.AddStatic(FSatisfactoryModLoader::InitializeModLoading);
#endif
}

void FSMLModule::ShutdownModule() {
}

IMPLEMENT_GAME_MODULE(FSMLModule, SML);

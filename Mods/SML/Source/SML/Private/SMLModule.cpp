#include "SMLModule.h"

#include "GameplayTagsManager.h"
#include "SatisfactoryModLoader.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/CoreDelegates.h"

void AddModGameplayTagIniSearchPath(const IPlugin& Plugin) {
	if(Plugin.GetType() == EPluginType::Mod) {
		UGameplayTagsManager::Get().AddTagIniSearchPath(Plugin.GetBaseDir() / TEXT("Config/Tags"));
	}
}

void RegisterPluginGameplayTagInis() {
	// Add all enabled mods to the gameplay tag ini search path
	IPluginManager& PluginManager = IPluginManager::Get();
	auto EnabledPlugins = PluginManager.GetEnabledPlugins();
	for (auto& Plugin : EnabledPlugins) {
		AddModGameplayTagIniSearchPath(Plugin.Get());
	}
	PluginManager.OnNewPluginMounted().AddLambda([](IPlugin& Plugin) {
		AddModGameplayTagIniSearchPath(Plugin);
	});
}

void FSMLModule::StartupModule() {
	//Basic subsystems like logging are initialized on OnInit
	FSatisfactoryModLoader::PreInitializeModLoading();

	//UObject subsystem and Engine are initialized on PostEngineInit and we need to delay their initialization to that moment
	FCoreDelegates::OnPostEngineInit.AddStatic(FSatisfactoryModLoader::InitializeModLoading);

	// ExecCmds are run after Engine is initialized as they use GEngine to run the commands
	FCoreDelegates::OnPostEngineInit.AddStatic(FSatisfactoryModLoader::ParseExecCmds);

	RegisterPluginGameplayTagInis();
}

void FSMLModule::ShutdownModule() {
}

IMPLEMENT_GAME_MODULE(FSMLModule, SML);

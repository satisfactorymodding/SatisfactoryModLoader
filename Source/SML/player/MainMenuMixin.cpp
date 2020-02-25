#include "mod/hooking.h"
#include "FGGameInstance.h"
#include "util/Logging.h"
#include "MainMenuMixin.h"

class UFGGameInstanceProto {
public: void LoadComplete(const float loadTime, const FString& mapName) {}
};

void SML::registerMainMenuHooks() {
	SUBSCRIBE_METHOD("?LoadComplete@UFGGameInstance@@MEAAXMAEBVFString@@@Z", UFGGameInstanceProto::LoadComplete, [](CallResult<void>&, void* thisPtr, const float, const FString& mapName) {
		UFGGameInstance* gameInstance = reinterpret_cast<UFGGameInstance*>(thisPtr);
		SML::Logging::info(TEXT("LoadComplete for map "), *mapName);
		if (mapName == TEXT("/Game/FactoryGame/Map/MenuScenes/MenuScene_01")) {
			SML::Logging::info(TEXT("Menu scene loaded. Widgets injected."));
			//TODO some nice main menu UI stuff, will come a bit later
			//UGameViewportClient* viewport = gameInstance->GetWorld()->GetGameViewport();
			//viewport->AddViewportWidgetContent(SNew(STextBlock).Text(FText::FromString(TEXT("Satisfactory Mod Loader"))));
		}
	});
}
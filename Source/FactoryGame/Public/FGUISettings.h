#pragma once
#include "UObject/Class.h"

#include "Engine/DeveloperSettings.h"
#include "FGUISettings.generated.h"

UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Satisfactory UI Settings" ) )
class FACTORYGAME_API UFGUISettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	static const UFGUISettings* Get() { return GetDefault<UFGUISettings>(); };
public:
	/** Widget used to show that the user is setting up a server */
	UPROPERTY( EditAnywhere, config, Category = UI )
	TAssetSubclassOf<UUserWidget> mSettingUpServerWidget;

	/** Widget used to show the user when joining a session */
	UPROPERTY( EditAnywhere, config, Category = UI )
	TAssetSubclassOf<UUserWidget> mJoinSessionWidget;

public:
	FORCEINLINE ~UFGUISettings() = default;
};
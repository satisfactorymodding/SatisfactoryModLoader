// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Engine/DeveloperSettings.h"
#include "FGUISettings.generated.h"

class UFGPopupWidgetContent;

UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Satisfactory UI Settings" ) )
class FACTORYGAME_API UFGUISettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	static const UFGUISettings* Get() { return GetDefault<UFGUISettings>(); };

	/** Widget used to show that the user is setting up a server */
	UPROPERTY( EditAnywhere, config, Category = Online )
	TSoftClassPtr<UUserWidget> mSettingUpServerWidget;

	/** Widget used to show the user when joining a session */
	UPROPERTY( EditAnywhere, config, Category = Online )
	TSoftClassPtr<UUserWidget> mJoinSessionWidget;

	// <FL> [WuttkeP] Replaced a few TSubclassOf with TSoftClassPtr to fix editor initialization.
	/** Widget used to show the user when linking accounts */
	UPROPERTY( EditAnywhere, config, Category = Online )
	TSoftClassPtr<UUserWidget> mConnectAccountsWidget;

	/** Widget to show the user when unlinking account */
	UPROPERTY( EditAnywhere, config, Category = Online )
	TSoftClassPtr<UUserWidget> mResetAccountLinkingWidget;

	/** Popup that will be displayed when the user attempts to create an online session without being logged in to the relevant online services. */
	UPROPERTY( EditAnywhere, Config, Category = Online )
	TSoftClassPtr<class UFGCreateOfflineSessionPrompt> mCreateOfflineSessionPrompt;

	/** Widget used to show the user when enabling the debug overlay */
	UPROPERTY( EditAnywhere, config, Category = UI )
	TSoftClassPtr< class UFGDebugOverlayWidget > mDebugOverlayWidgetClass;

	/** Emote wheel widget to select a widget */
	UPROPERTY( EditAnywhere, config, Category = UI )
	TSoftClassPtr< class UFGInteractWidget > mEmoteMenuWidget;

	/** Widget used to customize and spawn a map marker in the world */
	UPROPERTY( EditAnywhere, config, Category = UI )
	TSoftClassPtr< class UFGInteractWidget > mAddMapMarkerWidget;
	// </FL>

	/** Widget used to hold audio messages that the player receives. This is populated with data from UFGMessage assets */
	UPROPERTY( EditAnywhere, config, Category = Narrative )
	TSoftClassPtr< class UFGAudioMessage > mDefaultAudioMessageWidget;

	UPROPERTY( EditAnywhere, config, Category = ErrorReporting, meta = ( RequiredAssetDataTags = "RowStructure=/Script/FactoryGame.ErrorDescriptor" ) )
	TSoftObjectPtr< class UDataTable > mErrorDescriptorTable;

	UPROPERTY( EditAnywhere, config, Category = ErrorReporting )
	TSoftClassPtr< UFGPopupWidgetContent > mDefaultErrorPopupClass;

};
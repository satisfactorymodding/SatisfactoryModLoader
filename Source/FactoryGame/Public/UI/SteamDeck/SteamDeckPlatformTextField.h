
#pragma once

#if (PLATFORM_WINDOWS || PLATFORM_LINUX) 
	#if !UE_SERVER && WITH_STEAMWORKS

	DECLARE_LOG_CATEGORY_EXTERN(LogSteamDeck, Log, All)
#include "FactoryGame.h"
	#include "Framework/Application/IPlatformTextField.h"
	#include <steam/steam_api_common.h>
	#include <steam/isteamutils.h>

	class IVirtualKeyboardEntry;

	class FSteamDeckPlatformTextField  : public IPlatformTextField
	{
	public:
		virtual void ShowVirtualKeyboard(bool bShow, int32 UserIndex, TSharedPtr<IVirtualKeyboardEntry> TextEntryWidget) override;
		virtual bool AllowMoveCursor() override { return true; };

		TWeakPtr<IVirtualKeyboardEntry> mTextEntryWidget;
	private:
		STEAM_CALLBACK( FSteamDeckPlatformTextField, OnSteamKeyboardDismissed, GamepadTextInputDismissed_t );
	};

	typedef FSteamDeckPlatformTextField  FPlatformTextField;

	#else
	#include "Framework/Text/GenericPlatformTextField.h"	
	#endif
#else
	#include "Framework/Text/GenericPlatformTextField.h"
#endif
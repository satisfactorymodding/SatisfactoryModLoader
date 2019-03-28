#pragma once
#include <event/Event.h>
#include <util/Utility.h>
#include <event/EventLoader.h>
#include <util/FString.h>
#include <util/FLinearColor.h>
#include "EnterChatMessageEvent.h"

class AHUDDrawText : public Event {
public:
	AHUDDrawText();
	virtual ~AHUDDrawText();

	static constexpr EventType descriptor = EventType::OnAHUDDrawText;

	static constexpr const char* addressName = "AHUD::DrawText";

	virtual EventType type() const {
		return descriptor;
	}

	virtual const char* name() const {
		return addressName;
	}

	static void draw() {

	}

	// ; void __fastcall AHUD::DrawText(AHUD *this, FString *Text, FLinearColor Color, float ScreenX, float ScreenY, UFont *Font, float Scale, bool bScalePosition)
	static void use(void* hud, FString* text, FLinearColor color, float x, float y, void* font, float scale, bool bScalePosition) {
		log("AHUD_DRAWTEXT");

		auto pointer = (AHUDDrawTextFunction)originalFunctions[descriptor].Function;
		pointer(hud, text, color, x, y, font, scale, bScalePosition);
	}

private:
	typedef void(WINAPI* AHUDDrawTextFunction)(VOID*, FString*, FLinearColor, float, float, VOID*, float, bool);
};

AHUDDrawText::AHUDDrawText() {
}


AHUDDrawText::~AHUDDrawText() {
}
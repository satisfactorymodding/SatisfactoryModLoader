#pragma once

#include "AnalogCursor.h"
#include "Engine/LocalPlayer.h"
//#include "FGGamepadCursor.generated.h"

class FACTORYGAME_API FFGGamepadCursor : public FAnalogCursor
{
public:
	/** default ctor */
	FFGGamepadCursor();

	/** Ctor */
	FFGGamepadCursor( class APlayerController* inPC, float inRadius );

	void Tick( const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor ) override;

	static void EnableAnalogCursor( class APlayerController* PC, TSharedPtr<SWidget> WidgetToFocus );
	static void DisableAnalogCursor( class APlayerController* PC );

	/** Getter */
	FORCEINLINE float GetRadius() const
	{
		return Radius;
	}
private:
	/** The radius of the analog cursor */
	float Radius;

	/** The Player's Context */
	FLocalPlayerContext PlayerContext;

	/** The single analog cursor we allow in the game */
	static TSharedPtr< FFGGamepadCursor > AnalogCursor;

public:
	FORCEINLINE ~FFGGamepadCursor() = default;
};
// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGLocalAudioContextSubsystem.h"
#include "FGTrain.h"
#include "SlateIMWidgetBase.h"
#include "Brushes/SlateColorBrush.h"
#include "Containers/RingBuffer.h"

class FACTORYGAME_API FGLocalAudioContextDebugWindow : public FSlateIMWindowBase
{
public:
	FGLocalAudioContextDebugWindow() :
	FSlateIMWindowBase(
		TEXT( "Local Audio Context Debug" ),
		FVector2f( 1000, 1100 ),
		TEXT( "FGAudio.ToggleLocalAudioContextDebug" ),
		TEXT( "Opens a window that can show in-depth information about Local Audio Subsystems" ) )
	{
	}

	virtual void DrawWindow(float DeltaTime) override;
	void SetSubsystem( AFGLocalAudioContextSubsystem* subsystem );
private:
	void DrawDebugInfo();
	void DrawAudioSettingsInfo();

	static bool IsLocalAudioContextEnabled();
	static void SetLocalAudioContextEnabled( bool enabled );
	
	static float GetLocalAudioContextHorizontalLength();
	static void SetLocalAudioContextHorizontalLength( float length );

	static float GetLocalAudioContextVerticalLimit();
	static void SetLocalAudioContextVerticalLimit( float length );

	static float GetLocalAudioContextAngularLength();
	static void SetLocalAudioContextAngularLength( float length );

	static float GetLocalAudioContextVerticalAngle();
	static void SetLocalAudioContextVerticalAngle( float angle );
	
	void DisplayDebugHitsWorld();
	void DisplayDebugWallsWorld();
	
private:
	TObjectPtr< AFGLocalAudioContextSubsystem > mSubsystem;
	FSlateColorBrush GraphBorderBrush { FLinearColor(0.5f,0.5f,0.5f, 0.3f) };
	
	bool mForceRefreshUI { true };
	
	bool mDebugToggleSlapbackWalls { false };
	
	bool mDebugHits { false };

	TArray<FString> mDebugHitsComboBoxItems = { TEXT("Horizontal Hits"), TEXT("Vertical Hits"), TEXT("Angular Hits") };
	int32 mDebugHitsType { 2 };
};
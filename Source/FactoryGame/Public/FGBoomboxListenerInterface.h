// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Resources/FGTapeData.h"
#include "UObject/Interface.h"
#include "FGBoomboxListenerInterface.generated.h"

UENUM( BlueprintType, meta=( Bitflags, UseEnumValuesAsMaskValuesInEditor = "true" ) )
enum class EBoomBoxPlaybackStateBitfield : uint8
{
	NotPlaying								= 0,
	PlaybackEnabled							= 1,		/** Bit should be set if the player actually started playback */
	PlaybackAllowedByEquipmentStatus		= 1 << 1,	/** Bit should be set if playback is allowed by the equipment's equipped status. */
	PlaybackAllowedByPawnPossessedStatus	= 1 << 2,	/** Bit should be set if playback is allowed by the owning pawn's possessed status.*/
	MayActuallyPlay							= PlaybackEnabled | PlaybackAllowedByEquipmentStatus | PlaybackAllowedByPawnPossessedStatus
};

ENUM_CLASS_FLAGS( EBoomBoxPlaybackStateBitfield );

inline int32& operator|=( int32& Lhs, EBoomBoxPlaybackStateBitfield Rhs ) { return Lhs = Lhs | static_cast<std::underlying_type_t<EBoomBoxPlaybackStateBitfield>>( Rhs ); }
inline int32& operator&=( int32& Lhs, EBoomBoxPlaybackStateBitfield Rhs ) { return Lhs = Lhs & static_cast<std::underlying_type_t<EBoomBoxPlaybackStateBitfield>>( Rhs ); }
constexpr int32 operator&( int32 Lhs, EBoomBoxPlaybackStateBitfield Rhs ) { return Lhs & static_cast<std::underlying_type_t<EBoomBoxPlaybackStateBitfield>>( Rhs ); }
constexpr int32 operator|( int32 Lhs, EBoomBoxPlaybackStateBitfield Rhs ) { return Lhs | static_cast<std::underlying_type_t<EBoomBoxPlaybackStateBitfield>>( Rhs ); }
constexpr int32 operator^( int32  Lhs, EBoomBoxPlaybackStateBitfield Rhs ) { return Lhs ^ static_cast<std::underlying_type_t<EBoomBoxPlaybackStateBitfield>>( Rhs ); }
constexpr bool operator==( int32 Lhs, EBoomBoxPlaybackStateBitfield Rhs ) { return Lhs == static_cast<std::underlying_type_t<EBoomBoxPlaybackStateBitfield>>( Rhs ); }
constexpr bool operator!=( int32 Lhs, EBoomBoxPlaybackStateBitfield Rhs ) { return !( Lhs == Rhs ); }


UENUM( BlueprintType )
enum class EBoomBoxRepeatMode: uint8
{
	NoRepeat,
	RepeatTape,
	RepeatSong
};


UENUM( BlueprintType )
enum class EBoomBoxMode: uint8
{
	Undefined,				/** The mode is undefined, the boombox is not initialized. It cannot be shown or play any music in this mode */
	EquippedVisible,		/** The boombox is currently used as an equipment and should be visible (active equipment on possessed pawn). */
	EquippedHidden,			/** The boombox is used as an equipment but should currently be hidden (can still play music). */
	Static					/** The boombox is placed within the world as a static actor. */
};

/**
 * 
 */
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGBoomboxListenerInterface : public UInterface
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGBoomboxListenerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintImplementableEvent )
	void PlaybackStateChanged( UPARAM(meta = (Bitmask, BitmaskEnum = "/Script/FactoryGame.EBoomBoxPlaybackStateBitfield")) int32 newState );

	UFUNCTION( BlueprintImplementableEvent )
	void CurrentSongChanged( const FSongData& currentSong, int32 index );

	UFUNCTION( BlueprintImplementableEvent )
	void PlaybackPositionUpdate( float currentPosition, float totalDuration );

	UFUNCTION( BlueprintImplementableEvent )
	void CurrentTapeChanged( TSubclassOf<UFGTapeData> currentTape );

	UFUNCTION( BlueprintImplementableEvent )
	void AudioVolumeChanged( float volume );

	UFUNCTION( BlueprintImplementableEvent )
	void RepeatModeChanged( EBoomBoxRepeatMode newMode );

	UFUNCTION( BlueprintImplementableEvent )
	void BoomBoxModeChanged( EBoomBoxMode newMode );
};

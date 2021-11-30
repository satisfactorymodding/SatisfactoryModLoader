// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSignTypes.h"
#include "UObject/NoExportTypes.h"
#include "FGEmote.generated.h"

/**
 * A class to represent an emote in game. Most things are handled in blueprint since it's mostly animations and sound.
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGEmote : public UObject
{
	GENERATED_BODY()

public:
	void PlayEmote(class AFGCharacterPlayer* playerCharacter, int32 randomInteger );
	
	UFUNCTION( BlueprintImplementableEvent )
	void OnPlayEmoteLocally();

	UFUNCTION( BlueprintImplementableEvent )
	void OnPlayEmoteRemote();

	/** Get the text that is shown in the emote wheel */
	UFUNCTION( BlueprintPure, Category = "Emote"  )
	static FText GetEmoteName( TSubclassOf< UFGEmote > inClass );
	
	/** Get the icon that is shown in the emote wheel */
	UFUNCTION( BlueprintPure, Category = "Emote" )
	static UTexture2D* GetEmoteIcon( TSubclassOf< UFGEmote > inClass );

	UFUNCTION( BlueprintCallable, Category = "Emote" )
	void PlayEmoteSFX( class UAkAudioEvent* event );
	UFUNCTION( BlueprintCallable, Category = "Emote" )
	float PlayEmoteMontage_1P(class UAnimMontage* MontageToPlay, float InPlayRate = 1.f, EMontagePlayReturnType ReturnValueType = EMontagePlayReturnType::MontageLength, float InTimeToStartMontageAt=0.f, bool bStopAllMontages = true);
	UFUNCTION( BlueprintCallable, Category = "Emote" )
	float PlayEmoteMontage_3P(class UAnimMontage* MontageToPlay, float InPlayRate = 1.f, EMontagePlayReturnType ReturnValueType = EMontagePlayReturnType::MontageLength, float InTimeToStartMontageAt=0.f, bool bStopAllMontages = true);
	UFUNCTION( BlueprintCallable, Category = "Emote" )
	void PlayEmoteCameraAnim(class UCameraAnim* AnimToPlay, float Scale=1.f, float Rate=1.f, float BlendInTime=0.f, float BlendOutTime=0.f, bool bLoop=false, bool bRandomStartTime=false, ECameraShakePlaySpace Space=ECameraShakePlaySpace::CameraLocal, FRotator CustomPlaySpace=FRotator::ZeroRotator);

	UFUNCTION( BlueprintPure, Category = "Emote" )
	class AFGCharacterPlayer* GetPlayerCharacter() const {return mPlayerCharacter;}

	/** Get the generated random integer for this emote between 0-1000. Can be used for easter eggs and such. Will be the synced between client and server.*/
	UFUNCTION( BlueprintPure, Category = "Emote" )
	int32 GetRandomIntegerForEmote() const {return mRandomInteger;}
	
protected:
	/** The text that is shown in the emote wheel */
	UPROPERTY( EditDefaultsOnly, Category = "Emote" )
	FText mEmoteName;
	
	/** The icon that is shown in the emote wheel */
	UPROPERTY( EditDefaultsOnly, Category = "Emote" )
	class UTexture2D* mEmoteIcon;

private:
	UPROPERTY()
	class AFGCharacterPlayer* mPlayerCharacter;

	/** Get the generated random integer for this emote between 0-1000. Can be used for easter eggs and such. Will be the synced between client and server.*/
	int32 mRandomInteger;
	
};

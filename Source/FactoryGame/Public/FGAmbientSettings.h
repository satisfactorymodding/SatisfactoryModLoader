#pragma once
#include "../../Plugins/Wwise/Source/AkAudio/Classes/AkAudioEvent.h"
#include "UObject/Class.h"

#include "Object.h"
#include "FGAmbientSettings.generated.h"

UCLASS( Abstract, BlueprintType, Blueprintable )
class FACTORYGAME_API UFGAmbientSettings : public UObject
{
	GENERATED_BODY()
public:
	/** ctor */
	UFGAmbientSettings();

	/** Get the event that is played whenever you get close to the ambient volume */
	UFUNCTION( BlueprintNativeEvent, Category = "Audio" )
	class UAkAudioEvent* GetEnterOuterVolumeEvent() const;

	/** Get the event that is played whenever you get close to the ambient volume */
	UFUNCTION( BlueprintNativeEvent, Category = "Audio" )
	class UAkAudioEvent* GetEnterInnerVolumeEvent() const;

	/** Called when we are getting close to the attenuation radius of the ambient volume */
	UFUNCTION( BlueprintNativeEvent, Category = "Audio" )
	void OnEnterOuterVolume( class UAkComponent* ambientComponent ) const;

	/** Called when we are far away from the attenuation radius of the ambient volume */
	UFUNCTION( BlueprintNativeEvent, Category = "Audio" )
	void OnExitOuterVolume( class UAkComponent* ambientComponent ) const;

	/** Called when the camera is entering the the ambient volume */
	UFUNCTION( BlueprintNativeEvent, Category = "Audio" )
	void OnEnterInnerVolume( class UAkComponent* ambientComponent ) const;

	/** Called when the camera is leaving the ambient volume */
	UFUNCTION( BlueprintNativeEvent, Category = "Audio" )
	void OnExitInnerVolume( class UAkComponent* ambientComponent ) const;

	/** Check if we should ignore the rotation of the listener when inside the volume */
	UFUNCTION( BlueprintNativeEvent, Category = "Audio" )
	bool ShouldIgnoreListenerRotation() const;

#if WITH_EDITOR
	// Check for errors in the settings
	virtual void CheckForErrors();
#endif
protected:
	/** Event to post when OnGetClose is triggered */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Audio" )
	class UAkAudioEvent* mOnEnterOuterVolumeEvent;

	/** Event to post when OnGetFar is triggered */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Audio" )
	class UAkAudioEvent* mOnExitOuterVolumeEvent;

	/** Event to post when OnEnter is triggered */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Audio" )
	class UAkAudioEvent* mOnEnterInnerVolumeEvent;

	/** Event to post when OnExit is triggered */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Audio" )
	class UAkAudioEvent* mOnExitInnerVolumeEvent;

	/** If checked, then we don't rotate the audio source to match the rotation of the listener when inside the volume */
	UPROPERTY( EditDefaultsOnly, Category = "Audio" )
	uint8 mIgnoreListenerRotation:1;
private:
	// Members to optimize all native events, so we don't have to pay the cost for using BlueprintNativeEvents if they ain't used
	uint8 mHave_GetEnterOuterVolumeEvent:1;
	uint8 mHave_OnEnterOuterVolume:1;
	uint8 mHave_OnExitOuterVolume:1;
	uint8 mHave_OnEnterInnerVolume:1;
	uint8 mHave_OnExitInnerVolume:1;
	uint8 mHave_ShouldIgnoreListenerRotation:1;
	uint8 mHave_GetEnterInnerVolumeEvent : 1;

public:
	FORCEINLINE ~UFGAmbientSettings() = default;
};
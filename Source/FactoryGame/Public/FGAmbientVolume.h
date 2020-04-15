#pragma once
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "UndefinedBool.h"
#include "GameFramework/Volume.h"
#include "FGSignificanceInterface.h"
#include "FGAmbientVolume.generated.h"
 
UCLASS(HideCategories=(Cooking,Mobile))
class FACTORYGAME_API AFGAmbientVolume : public AVolume, public IFGSignificanceInterface
{
	GENERATED_BODY()
public:
	AFGAmbientVolume();

	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;

	//IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	virtual void GainedSignificance_Native() override;
	virtual void LostSignificance_Native() override;
	virtual float GetSignificanceRange() override;
	//End

	/** Get the audio component you want */
	FORCEINLINE class UAkComponent* GetAudioComponent(){ return mAudioComponent; }

	/** Get the ambient settings of this volume */
	const class UFGAmbientSettings* GetAmbientSettings() const;

	/** Set from the FGAmbientVolumeSubsystem */
	void SetCameraIsClose( bool close );
	void SetCameraIsInside( bool inside );
	bool IsCameraClose() const { return mIsCameraClose == EUndefinedBool::UB_True; }
	bool IsCameraInside() const { return mIsCameraInside == EUndefinedBool::UB_True; }

	/** Extra distance to start playing audio outside the attenuation radius */
	FORCEINLINE float GetAdditionalAttunationDistance() const{ return mAdditionalAttenuationDistance; }

	/** Getter for significance */
	FORCEINLINE bool GetIsSignificant() { return mIsSignificant; }

	//~ Begin AActor Interface
	virtual void PostUnregisterAllComponents( void ) override;
#if WITH_EDITOR
	virtual void CheckForErrors() override;
#endif
	/** Returns the cached box extent */
	FORCEINLINE FBoxSphereBounds GetCachedBoxSphereBounds() { return mCachedBoxSphereBounds; }
protected:
	virtual void PostRegisterAllComponents() override;
	//~ End AActor Interface

	/** Adds to volume to the world */
	void AddVolume();

	/** Adds to volume to the world */
	void RemoveVolume();
protected:
	/** The settings for the volume */
	UPROPERTY( EditInstanceOnly, Category="Audio")
	TSubclassOf<class UFGAmbientSettings> mAmbientSettings;

	/** The audio component we want to move around */
	UPROPERTY( VisibleInstanceOnly, Category="Audio" )
	class UAkComponent* mAudioComponent;

	/** How much further away than the attenuation distance do we want to start playing the ambient OnGeCloseSound */
	UPROPERTY( EditInstanceOnly, Category="Audio")
	float mAdditionalAttenuationDistance;

	/** Caching the extent for use later */
	FBoxSphereBounds mCachedBoxSphereBounds;
private:
	// if set, then the camera is within/close to the attenuation range of the sound
	bool mIsCameraClose;
	// if set, the the camera is inside the volume
	bool mIsCameraInside;

	/** Is this volume in significance range */
	bool mIsSignificant;

	/** Range that this volume should be significant within */
	UPROPERTY( EditInstanceOnly, Category = "Significance" )
	float mSignificanceRange;

public:
	FORCEINLINE ~AFGAmbientVolume() = default;
};
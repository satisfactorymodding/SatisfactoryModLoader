#pragma once
#include "../../Plugins/Wwise/Source/AkAudio/Classes/AkAudioEvent.h"
#include "Array.h"
#include "UObject/Class.h"

#include "FGWaterAudio.generated.h"

USTRUCT( BlueprintType )
struct FACTORYGAME_API FPawnImpactAudio
{
	GENERATED_BODY()

	/** If we have at least this velocity (in Z) when entering the volume, we will post the specified event */
	UPROPERTY( EditAnywhere, Category="Audio")
	float MinImpactVelocity;

	/** Event to post if the pawn has the specified velocity */
	UPROPERTY( EditAnywhere, Category = "Audio" )
	class UAkAudioEvent* ImpactEvent;

public:
	FORCEINLINE ~FPawnImpactAudio() = default;
};

UCLASS(Abstract,Blueprintable)
class FACTORYGAME_API UFGWaterAudio : public UObject
{
	GENERATED_BODY()
public:
	/** Called whenever the camera entered water */
	UFUNCTION(BlueprintImplementableEvent, Category = "Water|Audio" )
	void OnCameraEnteredWater( class AFGWaterVolume* waterVolume, FVector enterLocation, class AFGPlayerController* PC ) const;

	/** Called whenever the camera entered water */
	UFUNCTION(BlueprintImplementableEvent, Category = "Water|Audio" )
	void OnCameraExitedWater( class AFGWaterVolume* waterVolume, FVector exitLocation, class AFGPlayerController* PC ) const;

	/** Called whenever a pawn hits the surface of the water volume */
	UFUNCTION( BlueprintImplementableEvent, Category = "Water|Audio" )
	void OnPawnHitSurface( class AFGWaterVolume* waterVolume, class APawn* pawn, FVector surfaceLocation ) const;

	/** Get the impact event that a pawn should post when it hits the water surface */
	UFUNCTION( BlueprintPure, Category="Water|Audio" )
	class UAkAudioEvent* GetImpactEvent( class APawn* pawn ) const;
protected:
	/** Audio effects to play whenever a pawn hits the water surface with a specified velocity */
	UPROPERTY( EditDefaultsOnly, Category = "Water|Audio" )
	TArray<FPawnImpactAudio> mImpactAudioMap;

public:
	FORCEINLINE ~UFGWaterAudio() = default;
};

#pragma once
#include "Engine/World.h"
#include "UObject/Class.h"

#include "FGSubsystem.h"
#include "FGAudioVolumeSubsystem.generated.h"

UCLASS(NotPlaceable)
class AFGAudioVolumeSubsystem : public AFGSubsystem
{
	GENERATED_BODY()
public:
	AFGAudioVolumeSubsystem();

	/** Called every frame, updates the location of all ambient volumes */
	virtual void Tick( float dt ) override;

protected:
	/** returns true if we should update the given world */
	bool ShouldUpdateWorld( UWorld* world ) const;

	/** Update the volumes in the specified world */
	void UpdateWorld( UWorld* world );

	/** Get the distance where we assume that we are "close" to the volume */
	float GetCloseDistance( class AFGAmbientVolume* ambientVolume ) const;
};

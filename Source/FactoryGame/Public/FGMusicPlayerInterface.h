// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FGMusicPlayerInterface.generated.h"


UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGMusicPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGMusicPlayerInterface
{
	GENERATED_BODY()
public:
	/** Called when distance to player has ben changed */
	UFUNCTION( BlueprintNativeEvent, Category = "Music Player" )
    void OnDistanceChanged( float distSquared, bool isClosest );

	/** Is this music player active */
	UFUNCTION( BlueprintNativeEvent, Category = "Music Player" )
    bool IsPlaying();

	/** Get world location of object that implements this interface */
	UFUNCTION()
	virtual FVector GetWorldLocation();
public:
};
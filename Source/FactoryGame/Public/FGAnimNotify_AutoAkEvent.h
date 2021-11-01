// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"

#include "AkGameplayTypes.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "FGAnimNotify_AutoAkEvent.generated.h"

class FACTORYGAME_API UFGAnimNotify_AutoAkEvent;

/**
 * 
 */
UCLASS( const, hidecategories = Object, collapsecategories, meta = ( DisplayName = "Post Ak Event" ) )
class FACTORYGAME_API UFGAnimNotify_AutoAkEvent : public UAnimNotify
{
	GENERATED_BODY()
public:
	UFGAnimNotify_AutoAkEvent();

	//~ Begin UAnimNotify interface
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify( USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation ) final override;
	//~ End UAnimNotify interface

	FORCEINLINE class UAkAudioEvent* GetAudioEvent() { return AudioEvent; }
protected:
	// The socket or bone name we want to attach the event to
	UPROPERTY( EditAnywhere, Category = "Audio" )
	FName SocketName;

	/** Event to post when this event is triggered */
	UPROPERTY( EditAnywhere, Category = "Audio" )
	class UAkAudioEvent* AudioEvent;

	/** If true, then we attach the event to the socket/actor, else it stays in the world where it was posted (true is more expensive) */
	UPROPERTY( EditAnywhere, Category = "Audio" )
	bool bFollow;
private:
	/// Called after an event has been posted. May be used by derived classes to perform additional actions ( eg: set an RTPC value ) 
	virtual void PostNotify( USkeletalMeshComponent* SkeletalMeshComponent, UAkComponent* Component );

	/// Called just before an audio event is posted
	virtual void OnBeforePostEvent( USkeletalMeshComponent* SkeletalMeshComponent, UAkComponent* Component );
};

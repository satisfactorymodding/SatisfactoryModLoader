// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGOnScreenCallWidget.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGOnScreenCallWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    void StartCall( TSubclassOf< class UFGAudioMessage > message );
	
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Call" )
	bool CanAnswerCall( TSubclassOf< class UFGAudioMessage > message ) const;
	
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable,Category = "Call" )
	void OnAnswerCall();
	
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Call" )
	bool CanDeclineCall( TSubclassOf< class UFGAudioMessage > message ) const;

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable,Category = "Call" )
	void OnDeclineCall();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable,Category = "Call" )
	bool CanReceiveCall();
	
protected:
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable,Category = "Call" )
	void OnStartCall();
	
	UFUNCTION( BlueprintCallable, Category = "Call" )
	void AnswerCall();

	UFUNCTION( BlueprintCallable, Category = "Call" )
	void DeclineCall();

	UPROPERTY( BlueprintReadOnly )
	TSubclassOf<class UFGAudioMessage> mMessageClass;

	UPROPERTY( BlueprintReadOnly )
	bool mIsPriorityCall;
	
	UPROPERTY( BlueprintReadOnly )
	float mMaximumDelayForCall;
};

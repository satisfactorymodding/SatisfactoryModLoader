// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Creature/FGCreatureAction.h"
#include "Templates/SubclassOf.h"
#include "FGCreatureActionAnimatedBase.generated.h"

/**
 * 
 */
UCLASS( Abstract )
class FACTORYGAME_API UFGCreatureActionAnimatedBase : public UFGCreatureAction
{
	GENERATED_BODY()
public:
	UFGCreatureActionAnimatedBase( const FObjectInitializer& ObjectInitializer );

	// Begin UFGAction Interface
	virtual void CancelAction_Implementation() override;
	virtual void CleanupAction_Implementation( bool actionSuccess ) override;
	// End UFGAction Interface

	/** Whether or not our action is currently animating. */
	UFUNCTION( BlueprintPure, Category = "Action|Animation")
	FORCEINLINE bool IsCurrentlyAnimating() const { return mActiveMontages.Num() > 0; }
	
protected:
	/** Starts an animation montage for the action. broadcastToClients can be set to false if this logic runs on clients as well. */
	UFUNCTION( BlueprintCallable, Category = "Action|Animation" )
	bool StartActionAnimation( class UAnimMontage* montage, bool stopOtherMontages = false, bool broadcastToClients = true );

	/** Stop an animation montage for the action. broadcastToClients can be set to false if this logic runs on clients as well. */
	UFUNCTION( BlueprintCallable, Category = "Action|Animation" )
	bool StopActionAnimation( class UAnimMontage* montage, bool broadcastToClients = true );

	/** Called when the action animation montage has finished. */
	UFUNCTION( BlueprintNativeEvent, Category = "Action|Animation" )
	void OnAnimationFinished( class UAnimMontage* montage, bool WasInterrupted );

	/** Called when the action animation montage has started to blend out. */
	UFUNCTION( BlueprintNativeEvent, Category = "Action|Animation" )
	void OnAnimationBlendingOut( class UAnimMontage* montage, bool WasInterrupted );

	/** Called when one of the notifies we've subscribed to gets triggered. */
	UFUNCTION( BlueprintNativeEvent, Category = "Action|Animation" )
	void OnAnimNotify( const class UFGAnimNotify* Notify );

private:
	UFUNCTION( NetMulticast, Reliable )
	void NetMulticast_StartActionAnimation( class UAnimMontage* montage, bool stopOtherMontages );

	UFUNCTION( NetMulticast, Reliable )
	void NetMulticast_StopActionAnimation( class UAnimMontage* montage );

	UFUNCTION( NetMulticast, Reliable )
	void NetMulticast_CancelActionAnimation();

	void StartActionAnimation_Internal( class UAnimMontage* montage, bool stopOtherMontages );

	void StopActionAnimation_Internal( class UAnimMontage* montage );
	
	UFUNCTION()
	void OnAnimNotify_Internal( const class UFGAnimNotify* Notify, AActor* Owner );

	// Used to bind / unbind from anim notify delegate
	void BindAnimNotifyDelegate( const UAnimMontage* montage, bool shouldBind );
	
	/** Called when action animation ended */
	UFUNCTION()
	void OnMontageEnded( class UAnimMontage* Montage, bool Interrupted );

	/** Called when action animation is starting to blend out */
	UFUNCTION()
	void OnMontageBlendingOutStarted( class UAnimMontage* Montage, bool Interrupted );
	
protected:	
	/** Called when animation ended */
	FOnMontageEnded mOnMontageEnded;

	/** Called when animation starts to blend out.  */
	FOnMontageBlendingOutStarted mOnMontageBlendingOutStarted;

	/** What anim notify classes we want to listen to. */
	UPROPERTY( EditAnywhere, Category = "Animation" )
	TArray< TSubclassOf< class UFGAnimNotify > > mAnimNotifyTriggers;

private:
	UPROPERTY()
	TMap< class UAnimMontage*, int32 > mActiveMontages;
};

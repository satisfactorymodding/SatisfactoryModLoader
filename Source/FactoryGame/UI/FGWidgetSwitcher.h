#pragma once
#include "UObject/Class.h"

#include "Components/WidgetSwitcher.h"
#include "FGWidgetSwitcher.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnActiveWidgetSet, UWidget*, oldWidget, UWidget*, newWidget );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnMenuAnimDone );

UCLASS()
class UFGWidgetSwitcher : public UWidgetSwitcher
{
	GENERATED_BODY()
public:
	UFGWidgetSwitcher();

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	
	/** Make sure to call menu exit on our widgets */
	virtual void RemoveFromParent() override;

	/** Activates the widget and makes it the active index. */
	virtual void SetActiveWidgetIndex( int32 index ) override;

	/** Adding special case for null widget (ie, hide) */
	virtual void SetActiveWidget( UWidget* widget ) override;

	/** Called after menu enter animations has completed by our menu base child */
	void WidgetMenuEnterDone( class UFGMenuBase* menuBase );

	/** Called after menu exit animations has completed by our menu base child */
	void WidgetMenuExitDone( class UFGMenuBase* menuBase );
protected:
	/** Activates the widget and makes it the active index. */
	virtual void Internal_SetActiveWidgetIndex( int32 index );

	/** Set a active widget and clear all delegates */
	void Internal_SetActiveWidget( class UWidget* widget );

	/** Return true if we are currently animating in/out */
	bool IsDoingWidgetAnimation() const;

	/** Called if a childs Enter animation took too long. So we just skip it */
	UFUNCTION()
	void EnterAnimationTookToLong();

	/** Called if a childs Exit animation took too long. So we just skip it */
	UFUNCTION()
	void ExitAnimationTookToLong();

	UFUNCTION()
	void FadeOut();

	class FTimerManager* GetTimerManager() const;
protected:
	UPROPERTY(EditDefaultsOnly)
	float mFadeOutTime;

	/** Time we started fading out */
	float mFadeOutStartTime;

	/** */
	UPROPERTY(BlueprintAssignable)
	FOnActiveWidgetSet mOnWidgetSet;	

	/** */
	UPROPERTY(BlueprintAssignable)
	FOnMenuAnimDone mOnFadoutDone;


	/** Called whenever  */
	FTimerHandle mEnterAnimationTimeout;
	FTimerHandle mExitAnimationTimeout;
	FTimerHandle mFadeOutTimer;

	/** Pending widget that will be set when the animations is done */
	UPROPERTY()
	UWidget* mPendingNewWidget;

	// Widget currently running it's entering animation
	UPROPERTY()
	UFGMenuBase* mEnteringWidget;

	// Widget currently running it's exiting animation
	UPROPERTY()
	UFGMenuBase* mExitingWidget;
};
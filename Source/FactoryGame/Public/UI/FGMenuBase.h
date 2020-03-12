#pragma once
#include "UObject/Class.h"

#include "Blueprint/UserWidget.h"
#include "FGMenuBase.generated.h"

UCLASS(meta=(DisableNativeTick))
class FACTORYGAME_API UFGMenuBase : public UUserWidget
{
	GENERATED_BODY()
public:
	UFGMenuBase( const FObjectInitializer& objectInitializer );

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	void MenuEnter( class UWidget* prevMenu );
	void MenuExit( class UWidget* nextMenu, bool noAnimation = false );
protected:
	/** Cache our parent switcher */
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnMenuEnter( class UWidget* prevMenu );
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnMenuExit( class UWidget* prevMenu, bool noAnimation );

	UFUNCTION(BlueprintCallable)
	void OnMenuEnterDone();
	
	UFUNCTION(BlueprintCallable)
	void OnMenuExitDone();
protected:
	/** Cached switcher owning this widget */
	UPROPERTY()
	class UFGWidgetSwitcher* mCachedOwner;

public:
	FORCEINLINE ~UFGMenuBase() = default;
};

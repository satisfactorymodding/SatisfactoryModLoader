// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Components/Widget.h"
#include "CoreMinimal.h"
#include "FGLoadingScreenWidgetWrapper.generated.h"

/**
 * UMG Wrapper for SFGLoadingScreen
 */
UCLASS(BlueprintType)
class FACTORYGAME_API UFGLoadingScreen: public UWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void SetStatusText( const FText& inText );
protected:
	//~ Begin UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void SynchronizeProperties() override;
	//~ End UWidget Interface

	//~ Begin UVisual Interface
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	//~ End UVisual Interface

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText mStatusText;
	
private:
	TSharedPtr<class SFGMinimalLoadingScreen> mLoadingScreen;
};

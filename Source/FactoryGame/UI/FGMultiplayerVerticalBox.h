#pragma once
#include "UObject/Class.h"

#include "Components/VerticalBox.h"
#include "FGMultiplayerVerticalBox.generated.h"

UCLASS()
class UFGMultiplayerVerticalBox : public UVerticalBox
{
	GENERATED_BODY()

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	UFUNCTION(BlueprintCallable)
	void Sort();

	virtual TSharedRef<SWidget> RebuildWidget() override;
protected:
	// Specialized replace child at with no property sync, as we will create a new slot anyway
	bool ReplaceChildAt_NoSync( int32 Index, UWidget* Content );
};
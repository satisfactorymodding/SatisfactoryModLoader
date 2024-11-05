// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGGridNavigationHelper.h"
#include "FGTreeNavigationHelper.generated.h"

UCLASS()
class FACTORYGAME_API UFGTreeNavigationHelper : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION( BlueprintCallable )
	void SetupNavigation(const TArray<UWidget*>& widgets);

	UFUNCTION( BlueprintCallable )
	UWidget* DoNavigation(EUINavigation NavigationDirection);

	UPROPERTY( BlueprintAssignable )
	FFGNavigateBorderEvent mOnNavigateBorder;

	TArray<UWidget*> mAllWidgets;
};

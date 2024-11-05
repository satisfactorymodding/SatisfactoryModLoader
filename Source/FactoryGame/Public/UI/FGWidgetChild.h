// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "UObject/WeakObjectPtr.h"

#include "FGWidgetChild.generated.h"

class UWidget;

USTRUCT()
struct FFGWidgetChild
{
	GENERATED_BODY();

public:

	FACTORYGAME_API FFGWidgetChild();
	FACTORYGAME_API FFGWidgetChild(const class UUserWidget* Outer, FName InChildName);

	FName GetFName() const
	{
		return WidgetName;
	};

	UWidget* GetWidget() const
	{ 
		return WidgetPtr.Get(); 
	};

	FACTORYGAME_API UWidget* Resolve(const class UWidgetTree* WidgetTree);

private:

	UPROPERTY(EditAnywhere, Category = "Interaction")
	FName WidgetName;

	UPROPERTY(Transient)
	TWeakObjectPtr<UWidget> WidgetPtr;
};

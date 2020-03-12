// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../FGOptionsSettings.h"
#include "FGDynamicOptionsRow.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGDynamicOptionsRow : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

	void InitOptionRow( FOptionRowData optionRowData, TSubclassOf<class UFGOptionsValueController> widgetOptionClass );
	
	UFUNCTION( Blueprintpure, Category = "Option" )
	FORCEINLINE EOptionCategory GetOptionCategory() const { return EOptionCategory::OC_Gameplay; }

protected:
	UFUNCTION( Blueprintpure, Category = "Option" )
	FORCEINLINE FOptionRowData GetOptionRowData() const { return mOptionRowData; }

	UFUNCTION( Blueprintpure, Category = "Option" )
	FORCEINLINE UFGOptionsValueController* GetValueControllerWidget() const { return mValueControllerWidget; }

	UFUNCTION( BlueprintImplementableEvent, Category = "Option" )
	void OnOptionRowInit();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Option" )
	void OnOptionValueUpdated();

private:

	FOptionRowData mOptionRowData;

	EOptionType mOptionType;
	
	UPROPERTY()
	TSubclassOf<class UFGOptionsValueController> mWidgetOptionClass;

	UPROPERTY()
	UFGOptionsValueController* mValueControllerWidget;

public:
	FORCEINLINE ~UFGDynamicOptionsRow() = default;
};

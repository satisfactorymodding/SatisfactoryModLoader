// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UnrealString.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../FGOptionsSettings.h"
#include "FGOptionsValueController.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGOptionsValueController : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void OnRowHovered();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void OnRowUnhovered();

	void InitValueController( FOptionRowData optionRowData );
	
	UFUNCTION( BlueprintImplementableEvent )
	void OnInitValueController();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void OnOptionValueUpdated();

	UFUNCTION( BlueprintPure )
	FString GetNewSelectionKey( FString currentKey, bool incrementSelection );

protected:

	virtual void NativeConstruct() override;

protected:

	UPROPERTY( BlueprintReadOnly )
	FOptionRowData mOptionRowData;
	
	UPROPERTY( BlueprintReadOnly )
	bool mIsDynamicOption;


public:
	FORCEINLINE ~UFGOptionsValueController() = default;
};

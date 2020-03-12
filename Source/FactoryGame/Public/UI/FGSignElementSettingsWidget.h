// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGSignElementSettingsWidget.generated.h"

/**
 *	Base Widget for modifying a sign canvas element
 */
UCLASS()
class FACTORYGAME_API UFGSignElementSettingsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	/** Called when a element is selected to initialize */
	void NativeInit( class UFGSignElementWidget* elementWidget );
	
	UFUNCTION( BlueprintImplementableEvent, Category = "Sign Widget" )
	void Init();

	UFUNCTION( BlueprintNativeEvent, Category = "Sign Widget" )
	void OnColorIndexSelected( int index );

	UFUNCTION( BlueprintCallable, Category = "Sign Widget" )
	void OnElementDataChanged( );

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Sign Widget" )
	class UFGSignElementWidget* mElementWidget;



public:
	FORCEINLINE ~UFGSignElementSettingsWidget() = default;
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSignTypes.h"
#include "Framework/Text/TextLayout.h"
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
	void NativeInit( class UFGSignInteractWidget* interactWidget, class UFGSignElementWidget* elementWidget );
	
	UFUNCTION( BlueprintImplementableEvent, Category = "Signs|SettingsWidget" )
	void Init();

	UFUNCTION( BlueprintCallable, Category = "Signs|SettingsWidget" )
	void SetPosition( FVector2D newPosition );

	UFUNCTION( BlueprintCallable, Category = "Signs|SettingsWidget" )
	void SetText( FString newText );

	UFUNCTION( BlueprintCallable, Category = "Signs|SettingsWidget" )
	void SetSize( FVector2D newSize );

	UFUNCTION( BlueprintCallable, Category = "Signs|SettingsWidget" )
	void SetIconID( int32 iconID );

	UFUNCTION( BlueprintCallable, Category = "Signs|SettingsWidget" )
	void SetSizeDefinition( ESignSizeDefinition sizeDefinition );

	UFUNCTION( BlueprintCallable, Category = "Signs|SettingsWidget" )
	void SetAlignment( ETextJustify::Type newJustification );

protected:
	UPROPERTY( BlueprintReadOnly, Category = "Sign Widget" )
	class UFGSignInteractWidget* mInteractWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Sign Widget" )
	class UFGSignElementWidget* mElementWidget;


};

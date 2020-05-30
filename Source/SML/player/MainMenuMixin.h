#pragma once
#include "Widget.h"
#include "mod/ModInfo.h"
#include "MainMenuMixin.generated.h"

UCLASS()
class UButtonClickHandlerWidget : public UWidget {
    GENERATED_BODY()
public:
    UButtonClickHandlerWidget();
    
    FModInfo ModInfo;
    UPROPERTY()
    class UVerticalBox* ContentBox;
    UPROPERTY()
    UUserWidget* SelfButton;
public:
    UFUNCTION()
    void OnButtonClicked() const;
};


void GRegisterMainMenuHooks();
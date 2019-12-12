#pragma once
#include "UObject/Class.h"

#include "FGHotbarShortcut.h"
#include "FGDismantleShortcut.generated.h"

UCLASS()
class UFGDismantleShortcut : public UFGHotbarShortcut
{
	GENERATED_BODY()
public:
	//~ Begin UFGHotbarShortcut interface
	void Execute_Implementation( class AFGPlayerController* owner ) override;
	bool IsValidShortcut_Implementation( class AFGPlayerController* owner ) const override;
	UTexture2D* GetDisplayImage_Implementation() const override;
	bool IsActive_Implementation( class AFGPlayerController* owner ) const override;
	//~ End UFGHotbarShortcut interface
};
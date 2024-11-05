// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FGFactoryClipboard.generated.h"

UCLASS( Blueprintable, Abstract )
class FACTORYGAME_API UFGFactoryClipboardSettings : public UObject
{
	GENERATED_BODY()
	
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UFGFactoryClipboardInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FACTORYGAME_API IFGFactoryClipboardInterface
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintNativeEvent, Category = "Factory Clipboard" )
	bool CanUseFactoryClipboard();
	UFUNCTION( BlueprintNativeEvent, Category = "Factory Clipboard" )
	TSubclassOf<UFGFactoryClipboardSettings> GetClipboardSettingsClass();
	UFUNCTION( BlueprintNativeEvent, Category = "Factory Clipboard" )
	TSubclassOf<UObject> GetClipboardMappingClass();
	UFUNCTION( BlueprintNativeEvent, Category = "Factory Clipboard" )
	UFGFactoryClipboardSettings* CopySettings();
	UFUNCTION( BlueprintNativeEvent, Category = "Factory Clipboard" )
	bool PasteSettings( UFGFactoryClipboardSettings* factoryClipboard );
public:
};

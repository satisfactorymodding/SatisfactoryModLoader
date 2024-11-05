// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGInteractWidget.h"
#include "FGSignInterface.h"
#include "FGSignTypes.h"
#include "Framework/Text/TextLayout.h"
#include "FGPrefabSignInteract.generated.h"


/**
 *	General purpose Sign Designer Interact Widget. Intended to be used across all customizable signs
 */
UCLASS()
class FACTORYGAME_API UFGPrefabSignInteract : public UFGInteractWidget
{
	GENERATED_BODY()
public:
	/** Set the prefab that is active on this sign */
	UFUNCTION( BlueprintCallable, Category = "Signs|InteractWidget" )
	void SetPrefabLayout( TSoftClassPtr<UUserWidget> prefabLayout );

	UFUNCTION( BlueprintCallable, Category = "Signs|InteractWidget" )
	void GetAvailablePrefabLayouts( TArray< TSoftClassPtr<UUserWidget> >& out_prefabLayouts );

	/////////////////////////////////////////////////////////////////////
	/// Element Property Setters

	UFUNCTION( BlueprintCallable, Category = "Signs|InteractWidget" )
	void SetElementText( FString& elementName, FString newText );

	UFUNCTION( BlueprintCallable, Category = "Signs|InteractWidget" )
	void SetElementIconID( FString& elementName, int32 iconID );

protected:
	// Pointer to the interact objects sign interface
	IFGSignInterface* mSignInterface;

private:
	friend class UFGSignElementListWidget;
	friend class UFGSignCanvasWidget;
};

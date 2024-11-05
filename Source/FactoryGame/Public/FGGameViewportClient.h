// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "FGGameViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
public:
	// Begin UEngine interface
	virtual void Tick( float deltaSeconds ) override;
	// End UEngine interface

	//~ Begin FViewportClient Interface.
	// <FL> [WuttkeP] Added input handler to move focus when attempting to navigate without having anything focused.
	virtual bool InputKey( const FInputKeyEventArgs& EventArgs ) override;
	// </FL>
	virtual void LostFocus( FViewport* Viewport ) override;
	virtual void ReceivedFocus( FViewport* Viewport ) override;
	//~ End FViewportClient Interface.

	/** When full screen command is triggered we handle it hear */
	bool HandleToggleFullscreenCommand() override;

};

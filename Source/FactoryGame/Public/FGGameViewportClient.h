// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "FGGameViewportClient.generated.h"


//<FL> [KonradA] We want to keep track of this event in some hard to reach objects for e.g. Console Privelege refreshes
DECLARE_MULTICAST_DELEGATE(FOnViewportReceivedFocus)
//</FL>
/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
public:

	FOnViewportReceivedFocus OnViewportReceivedFocus;

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


	virtual void Activated( FViewport* InViewport, const FWindowActivateEvent& InActivateEvent ) override;
	virtual void Deactivated( FViewport* InViewport, const FWindowActivateEvent& InActivateEvent ) override;

	/** When full screen command is triggered we handle it hear */
	bool HandleToggleFullscreenCommand() override;

};

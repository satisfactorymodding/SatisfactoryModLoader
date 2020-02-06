// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

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
	virtual void LostFocus( FViewport* Viewport ) override;
	virtual void ReceivedFocus( FViewport* Viewport ) override;
	//~ End FViewportClient Interface.
};

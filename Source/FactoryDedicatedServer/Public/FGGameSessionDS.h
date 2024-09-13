// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGGameSession.h"
#include "FGGameSessionDS.generated.h"

UCLASS()
class FACTORYDEDICATEDSERVER_API AFGGameSessionDS : public AFGGameSession
{
	GENERATED_BODY()
public:
	AFGGameSessionDS();

	// Begin AGameSession interface
	virtual void PostLogin(APlayerController* NewPlayer) override;
	// End AGameSession interface
};
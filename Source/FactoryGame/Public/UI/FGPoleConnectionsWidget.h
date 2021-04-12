// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGPoleConnectionsWidget.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGPoleConnectionsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/* Gets the current amount of connections according to the widget. */
	UFUNCTION( BlueprintPure, Category = "UI" )
	class UFGCircuitConnectionComponent* GetConnection() const { return mConnection; }

	/* Sets the current amount of connections on the widget. */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	void SetConnection( class UFGCircuitConnectionComponent* connection );
	
protected:
	UPROPERTY()
	class UFGCircuitConnectionComponent* mConnection;
};

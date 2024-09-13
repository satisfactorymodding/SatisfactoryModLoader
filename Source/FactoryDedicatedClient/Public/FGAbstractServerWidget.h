// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "FGServerObject.h"
#include "FGAbstractServerWidget.generated.h"

/**
 * Abstract class for server manager related widgets that would like to receive updates about the state of the server.
 * Is just a convenience wrapper around server state listener. If you cannot use this class, implement the server state listener directly
 */
UCLASS( Abstract )
class FACTORYDEDICATEDCLIENT_API UFGAbstractServerWidget : public UUserWidget, public IFGServerStateListener
{
	GENERATED_BODY()
public:
	/** Updates the server object associated with this widget */
	UFUNCTION( BlueprintCallable, Category = "Server Widget" )
	void SetServer( UFGServerObject* Server );
	
protected:
	/** Called when the new server is associated with this widget */
	UFUNCTION( BlueprintImplementableEvent, Category = "Server Widget", meta = ( DisplayName = "On Server Changed" ) )
	void BP_OnServerChanged( UFGServerObject* Server );

	virtual void NativeOnServerChanged( UFGServerObject* Server ) {}

	/** The server currently associated with this widget */
	UPROPERTY( BlueprintReadOnly, Category = "Server Widget" )
	UFGServerObject* mServer;
};

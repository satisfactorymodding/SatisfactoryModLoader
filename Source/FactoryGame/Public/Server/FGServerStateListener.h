// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "OnlineBeaconClient.h"
#include "Server/FGDedicatedServerTypes.h"
#include "FGServerStateListener.generated.h"

/**
 * 
 */
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGServerStateListener : public UInterface
{
	GENERATED_BODY()
};

/*
 * A Server state listener is a utility interface available both to native code and blueprints that makes it possible to listen for any server
 * state changes. For a listener to receive notifications, it needs to register itself with a @UFGServerObject::RegisterStateListener
 * Similarly, once a listener does not want to receive notification any more it can unregister itself by calling @UFGServerObject::UnRegisterStateListener
 **/ 
class FACTORYGAME_API IFGServerStateListener
{
	GENERATED_BODY()
public:
	virtual void NativeOnServerStateChanged( class UFGServerObject* Server, EServerState State );
	UFUNCTION( BlueprintImplementableEvent, Category = "Server Info Listener", meta = ( DisplayName = "On Server State Changed" ) )
	void BP_OnServerStateChanged( class UFGServerObject* Server, EServerState State );

	virtual void NativeOnServerGameStateChanged( class UFGServerObject* Server, const FServerGameState& GameState );
	UFUNCTION( BlueprintImplementableEvent, Category = "Server Info Listener", meta = ( DisplayName = "On Server Game State Changed" ) )
	void BP_OnServerGameStateChanged( class UFGServerObject* Server, const FServerGameState& GameState );

	virtual void NativeOnServerConnectionStateChanged( class UFGServerObject* Server, EBeaconConnectionState ConnectionState );
	UFUNCTION( BlueprintImplementableEvent, Category = "Server Info Listener", meta = ( DisplayName = "On Server Connection State Changed" ) )
	void BP_OnServerConnectionStateChanged( class UFGServerObject* Server, EBeaconConnectionState ConnectionState );
	
	virtual void NativeOnServerAuthenticationChanged( class UFGServerObject* Server, const FServerAuthenticationToken& AuthToken );
	UFUNCTION( BlueprintImplementableEvent, Category = "Server Info Listener", meta = ( DisplayName = "On Server Authentication State Changed" ) )
	void BP_OnServerAuthenticationChanged( class UFGServerObject* Server, const FServerAuthenticationToken& AuthToken );

	virtual void NativeOnServerRenamed( class UFGServerObject* Server, const FString& Name );
	UFUNCTION( BlueprintImplementableEvent, Category = "Server Info Listener", meta = ( DisplayName = "On Server Renamed" ) )
	void BP_OnServerRenamed( class UFGServerObject* Server, const FString& Name );

	virtual void NativeOnServerComplexStateChanged( class UFGServerObject* Server, EServerComplexState State );
	UFUNCTION( BlueprintImplementableEvent, Category = "Server Info Listener", meta = ( DisplayName = "On Server Complex State Changed" ) )
	void BP_OnServerComplexStateChanged( class UFGServerObject* Server, EServerComplexState State );

	virtual void NativeOnNewServerConsoleOutput( class UFGServerObject* Server, const FString& NewOutput );
	UFUNCTION( BlueprintImplementableEvent, Category = "Server Info Listener", meta = ( DisplayName = "On New Server Console Output" ) )
	void BP_OnNewServerConsoleOutput( class UFGServerObject* Server, const FString& ConsoleOutput );

	virtual void NativeOnServerBasicSettingsUpdate( class UFGServerObject* Server, const FServerBasicSettings& BasicSettings );
	UFUNCTION( BlueprintImplementableEvent, Category = "Server Info Listener", meta = ( DisplayName = "On Server Basic Settings Update" ) )
	void BP_OnServerBasicSettingsUpdate( class UFGServerObject* Server, const FServerBasicSettings& BasicSettings );
};

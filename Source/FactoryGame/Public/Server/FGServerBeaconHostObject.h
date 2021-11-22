// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "OnlineBeaconHostObject.h"
#include "FGServerBeaconHostObject.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGServerBeaconHostObject : public AOnlineBeaconHostObject
{
	GENERATED_BODY()

	AFGServerBeaconHostObject();
public:
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason );
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnClientConnected( AOnlineBeaconClient* NewClientActor, UNetConnection* ClientConnection ) override;
	virtual void NotifyClientDisconnected(AOnlineBeaconClient* LeavingClientActor) override;
	void PushBasicSettings();

private:
	void SavesCollectionChanged();
};

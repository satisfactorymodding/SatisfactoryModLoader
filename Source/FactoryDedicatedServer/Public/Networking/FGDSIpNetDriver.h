// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IpNetDriver.h"
#include "FGDSIpNetDriver.generated.h"

class FMultiBindDatagramSocket;

/**
 * A variant of IpNetDriver that will attempt to bind to all of the bindable addresses across both IPv4 and IPv6,
 * as opposed to only binding to the first socket available.
 * 
 * It will also attempt to maintain the server query responsiveness on level change by reclaiming the socket and ticking it off the game thread with the cached data
 * until the server starts listening using the net driver on main thread again after the level change is completed.
 */
UCLASS()
class FACTORYDEDICATEDSERVER_API UFGDSIpNetDriver : public UIpNetDriver
{
	GENERATED_BODY()
public:
	// Begin UIpNetDriver interface
	virtual bool InitBase(bool bInitAsClient, FNetworkNotify* InNotify, const FURL& URL, bool bReuseAddressAndPort, FString& Error) override;
	virtual FUniqueSocket CreateAndBindSocket(TSharedRef<FInternetAddr> BindAddr, int32 Port, bool bReuseAddressAndPort, int32 DesiredRecvSize, int32 DesiredSendSize, FString& Error) override;
	virtual void SetWorld(UWorld* InWorld) override;
	virtual void LowLevelDestroy() override;
	virtual void TickDispatch(float DeltaTime) override;
	// End UIpNetDriver interface
private:
	/** Cached pointer to the multi-bind socket created during CreateAndBindSocket. */
	FMultiBindDatagramSocket* mMultiBindSocket{nullptr};
	/** True if we are waiting for the server to be done with loading to re-claim the socket */
	bool mWaitingToReClaimTheSocket{false};

	/** Cached pointer to the server subsystem we are associated with */
	TWeakObjectPtr<class UFGServerSubsystem> mServerSubsystem;
};

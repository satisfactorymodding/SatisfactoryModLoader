// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGServerObject.h"
#include "SocketSubsystem.h"
#include "Containers/Queue.h"
#include "HAL/Runnable.h"

class FClientQuerySocket : public FRunnable
{
public:
	FClientQuerySocket( TSharedRef< FInternetAddr > BindAddr );
	
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;

	FORCEINLINE TSharedRef<const FInternetAddr> GetBoundAddress() { return mBindAddress; }

	void ProcessServerQueryPing( FBitWriter& BitWriter );
	void ProcessServerQueryResponse( FBitReader& BitReader, const TSharedRef<FInternetAddr>& ResponseAddress );

	// Queue from quick socket thread to Game thread
	TQueue<FServerStatePollResponse> mServerStatePollResponses;
	// Queue from Game thread to quick socket thread. 
	TQueue<TSharedPtr<FInternetAddr>> mServerStatePollRequestQueue;
private:
	FUniqueSocket mSocket;
	TSharedRef<FInternetAddr> mBindAddress;
	int32 mFailedSends = 0;
	TAtomic<bool> ShouldStopRunning;
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DSQueryHandlerComponent.h"
#include "SocketSubsystem.h"
#include "HAL/Runnable.h"

enum class EServerFlags : uint64;
enum class EServerSubStateId : uint8;

class FFGOffThreadServerQuerySocket : public FRunnable
{
public:
	FFGOffThreadServerQuerySocket( FUniqueSocket&& InSocket, const FFGProcessServerQueryData& InServerQueryData );

	/** Re-claims the socket that the thread is using. Assumes that the thread has been stopped. */
	FUniqueSocket ReclaimSocket_AssumeLocked();

	virtual uint32 Run() override;
	virtual void Stop() override;
private:
	FUniqueSocket mSocket;
	TAtomic<bool> mShouldStopRunning;

	// Data that will be used to respond to the lightweight query. Not updated after the thread is initialized, and as such not locked.
	FFGProcessServerQueryData mServerQueryData;
};

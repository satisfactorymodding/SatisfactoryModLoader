// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

namespace FGServerCommands
{
	FACTORYDEDICATEDSERVER_API void RegisterConsoleCommands();
	FACTORYDEDICATEDSERVER_API void UnregisterConsoleCommands();
}

namespace FGServerCommandInternals
{
	void HandleSaveGame( const TArray<FString>& Args, UWorld* World, FOutputDevice& Ar );
	void HandleGenerateAPIToken( const TArray<FString>& Args, UWorld* World, FOutputDevice& Ar );
	void HandleResetAllAPITokens( const TArray<FString>& Args, UWorld* World, FOutputDevice& Ar );
}
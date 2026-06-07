// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGBoundMappingContextHandle.generated.h"

/**
 * Represents a handle to the mapping context binding on the player controller
 * This allows the same mapping context to be concurrently bound by multiple consumers without having a complex
 * and error-prone handling of multiple simultaneous registrations by each consumer
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FBoundMappingContextHandle
{
	GENERATED_BODY()

	enum EGenerateNewHandle { GenerateNewHandle };

	FBoundMappingContextHandle() = default;
	explicit FBoundMappingContextHandle( EGenerateNewHandle );

	FORCEINLINE void Reset()
	{
		HandleID = 0;
	}

	FORCEINLINE bool IsValid() const
	{
		return !!HandleID;
	}

	friend bool operator==( const FBoundMappingContextHandle& A, const FBoundMappingContextHandle& B )
	{
		return A.HandleID == B.HandleID;
	}

	friend uint32 GetTypeHash( const FBoundMappingContextHandle& Value )
	{
		return GetTypeHash( Value.HandleID );
	}
private:
	uint64 HandleID{0};
};

template<>
struct TStructOpsTypeTraits<FBoundMappingContextHandle> : TStructOpsTypeTraitsBase2<FBoundMappingContextHandle>
{
	enum
	{
		WithCopy = true,
		WithIdenticalViaEquality = true,
	};
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGClientInitialLoadStatusData.generated.h"

/**
 * Fortschritt eines Clients beim ersten Laden der replizierten Akteure.
 * Eigene Rekonstruktion aus dem Binärcode des Spielbuilds 520140 (nicht offiziell).
 */
USTRUCT()
struct FACTORYGAME_API FClientInitialLoadStatusData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	int32 AckedInitialLoadNetActors = 0;

	UPROPERTY()
	int32 TotalInitialLoadNetActors = 0;

	/** Der Client meldet das Laden unabhängig vom Fortschritt als abgeschlossen. */
	UPROPERTY()
	uint8 ClientForceComplete : 1;

	FClientInitialLoadStatusData() : ClientForceComplete( false ) {}

	bool IsValid() const;
	bool NetSerialize( FArchive& ar, UPackageMap* map, bool& out_success );
};

template<>
struct TStructOpsTypeTraits< FClientInitialLoadStatusData > : public TStructOpsTypeTraitsBase2< FClientInitialLoadStatusData >
{
	enum
	{
		WithNetSerializer = true,
	};
};

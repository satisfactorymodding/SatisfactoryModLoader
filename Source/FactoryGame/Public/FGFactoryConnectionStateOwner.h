// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "UObject/Interface.h"
#include "FGFactoryConnectionStateOwner.generated.h"

class UFGFactoryConnectionComponent;

/**
 * Verbindungszustände einer Fabrik als Bitmaske, damit sie atomar repliziert werden können.
 * Eigene Rekonstruktion aus dem Binärcode des Spielbuilds 520140 (nicht offiziell).
 */
USTRUCT()
struct FACTORYGAME_API FFGFactoryConnectionStates
{
	GENERATED_BODY()
public:
	/** Setzt den Zustand einer Verbindung, gibt true zurück, wenn er sich geändert hat. */
	bool SetConnected( const UFGFactoryConnectionComponent* connection, bool connected );

	/** Überträgt die Zustände auf die Verbindungskomponenten des Besitzers. */
	void ApplyToConnections( const AActor* owner ) const;

private:
	UPROPERTY()
	uint64 ConnectedMask = 0;
};

UINTERFACE()
class FACTORYGAME_API UFGFactoryConnectionStateOwner : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class FACTORYGAME_API IFGFactoryConnectionStateOwner
{
	GENERATED_IINTERFACE_BODY()
public:
	virtual void SetFactoryConnectionConnected( const UFGFactoryConnectionComponent* connection, bool connected ) = 0;
};

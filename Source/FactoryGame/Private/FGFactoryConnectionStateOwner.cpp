// Eigene Rekonstruktion für den Spielbuild 520140 (nicht offiziell)

#include "FGFactoryConnectionStateOwner.h"

bool FFGFactoryConnectionStates::SetConnected(const UFGFactoryConnectionComponent* connection, bool connected){ return bool(); }
void FFGFactoryConnectionStates::ApplyToConnections(const AActor* owner) const{ }
UFGFactoryConnectionStateOwner::UFGFactoryConnectionStateOwner(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

}

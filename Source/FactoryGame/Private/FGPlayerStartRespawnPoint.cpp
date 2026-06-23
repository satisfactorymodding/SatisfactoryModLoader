#include "FGPlayerStartRespawnPoint.h"

AFGPlayerStartRespawnPoint::AFGPlayerStartRespawnPoint() : Super(FObjectInitializer::Get()) {
	this->PlayerStartTag = TEXT("RespawnPoint");
}
const FName AFGPlayerStartRespawnPoint::STATIC_PLAYER_START_TAG = FName();
#include "Narrative/FGBarkMessageType.h"

UFGBarkMessageType::UFGBarkMessageType() : Super() {
	this->mMessageCooldown = 0.0;
	this->mIgnoreGlobalMessageCooldown = false;
}

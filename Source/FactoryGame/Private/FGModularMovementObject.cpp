#include "FGModularMovementObject.h"

void UFGModularMovementObject::SerializeSavedMoveData(FArchive& ar){ }
void UFGModularMovementObject::PhysMovement(const float DeltaSeconds){ }
void UFGModularMovementObject::SerializeMovementMode(FArchive& Ar){ }
bool UFGModularMovementObject::IsActiveMovementMode() const{ return false; }
void UFGModularMovementObject::ActivateMovementMode(){ }
UFGModularMovementObject::UFGModularMovementObject() : Super() {

}

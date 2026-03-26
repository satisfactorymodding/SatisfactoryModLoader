#include "FGModularMovementObject.h"
void FGModularMovementDataContainer::SerializeSavedMoveData(FArchive& ar){ }
bool FGModularMovementDataContainer::CanCombineMove(const FGModularMovementDataContainer* OtherMove) const{ return false; }
TUniquePtr<FGModularMovementDataContainer> FGModularMovementDataFactoryBase::CreateMoveData(const FGModularMovementDataContainer* CopyFrom) const{ return nullptr; }
void FGModularMovementDataFactoryBase::CopyData(const FGModularMovementDataContainer* From, FGModularMovementDataContainer* To) const{ }
void UFGModularMovementObject::SerializeSavedMoveData(FArchive& ar){ }
void UFGModularMovementObject::PhysMovement(const float DeltaSeconds){ }
void UFGModularMovementObject::SerializeMovementMode(FArchive& Ar){ }
bool UFGModularMovementObject::IsActiveMovementMode() const{ return false; }
void UFGModularMovementObject::ActivateMovementMode(){ }
UFGModularMovementObject::UFGModularMovementObject() : Super() {

}

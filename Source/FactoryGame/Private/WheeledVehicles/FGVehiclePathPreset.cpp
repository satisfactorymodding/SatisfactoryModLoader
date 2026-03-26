#include "WheeledVehicles/FGVehiclePathPreset.h"

UFGVehiclePathPreset::UFGVehiclePathPreset() : Super() {
	this->mPathValidationConfig.VehicleClass = nullptr;
	this->mPathValidationConfig.VehicleCollisionBox = FBox(FVector::ZeroVector, FVector::ZeroVector);
	this->mPathValidationConfig.VehicleMaxClimbAngle = 40.0;
	this->mPathValidationConfig.VehicleTurnRadius = 500.0;
	this->mPathValidationConfig.SuspensionMaxRaise = 100.0;
	this->mPathValidationConfig.SuspensionMaxDrop = 200.0;
	this->mPathValidationConfig.WheelMaxClimbAngle = 60.0;
	this->mPathValidationConfig.WheelSweepElevation = 40.0;
	this->mPathValidationConfig.VehicleSuspensionRollSmoothingDistance = 200.0;
	this->mPathValidationConfig.MaximumVehicleBankingAngle = 50.0;
	this->mPathValidationConfig.VehicleClimbAngleDistanceScaleCurve = nullptr;
}

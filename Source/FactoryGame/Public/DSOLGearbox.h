#pragma once

#include "CoreMinimal.h"

namespace physx
{
	class PxVehicleWheelsSimData;
	class PxVehicleDriveDynData;
	class PxVehicleDriveSimData;
}

/* DSOL (Don't shift on (wheel) load) dynamic gearbox data */
struct DSOLDynGearboxData
{
	bool mWasShiftingUp;
	bool mWasShiftingDown;
	int32 mTargetGear = 1;
	float mGearSwitchTime;
	float mSlopeShiftRatio; //Multiplier to affect shifting gears up and down on a slope
};

/* DSOL (Don't shift on (wheel) load) dynamic gearbox data */
struct DSOLSetupData
{
	int mNumberOfGears;
	float mDownShiftLatency;
};

struct DSOLGearbox
{
	///////////////////////DSOL Gearbox Stuff////////////////////////////////
	// "Don't Shift On Load" gearbox. Doesn't shift up if there is load on 
	// the tires. Useful for climbing uphill.
	// I'm putting this functionality here because it is a common object 
	// for movement components to access without modifying the engine.
	// The flag to enable/disable this, however, will be in the 
	// movement components. This mean we must manually also 
	// call this from movement components.
	/////////////////////////////////////////////////////////////////////////

	/** Simulates an automatic gearbox that does not shift up when there is load on the tires (useful when driving uphill) */
	static void Simulate(
		float DeltaTime,
		float RawThrottleInput,
		DSOLSetupData& setupData,
		DSOLDynGearboxData& gearboxData, 
		PxVehicleWheelsSimData& wheelsSimData, 
		PxVehicleDriveDynData& driveDynData, 
		PxVehicleDriveSimData& driveSimData );
};

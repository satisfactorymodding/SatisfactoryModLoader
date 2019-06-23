#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_RawInput_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class RawInput.RawInputFunctionLibrary
// 0x0000 (0x0028 - 0x0028)
class URawInputFunctionLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class RawInput.RawInputFunctionLibrary");
		return ptr;
	}


	TArray<struct FRegisteredDeviceInfo> GetRegisteredDevices();
};


// Class RawInput.RawInputSettings
// 0x0010 (0x0048 - 0x0038)
class URawInputSettings : public UDeveloperSettings
{
public:
	TArray<struct FRawInputDeviceConfiguration>        DeviceConfigurations;                                     // 0x0038(0x0010) (Edit, ZeroConstructor, Config)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class RawInput.RawInputSettings");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

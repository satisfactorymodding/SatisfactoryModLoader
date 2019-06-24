#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_MaterialShaderQualitySettings_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class MaterialShaderQualitySettings.MaterialShaderQualitySettings
// 0x0050 (0x0078 - 0x0028)
class UMaterialShaderQualitySettings : public UObject
{
public:
	TMap<struct FName, class UShaderPlatformQualitySettings*> ForwardSettingMap;                                        // 0x0028(0x0050) (ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MaterialShaderQualitySettings.MaterialShaderQualitySettings");
		return ptr;
	}

};


// Class MaterialShaderQualitySettings.ShaderPlatformQualitySettings
// 0x0028 (0x0050 - 0x0028)
class UShaderPlatformQualitySettings : public UObject
{
public:
	struct FMaterialQualityOverrides                   QualityOverrides[0x3];                                    // 0x0028(0x0008) (Edit, Config)
	unsigned char                                      UnknownData00[0x10];                                      // 0x0040(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MaterialShaderQualitySettings.ShaderPlatformQualitySettings");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

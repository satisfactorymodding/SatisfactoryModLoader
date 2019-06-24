#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_IntroTutorial_DismantleDropPod_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass IntroTutorial_DismantleDropPod.IntroTutorial_DismantleDropPod_C
// 0x0000 (0x02F0 - 0x02F0)
class UIntroTutorial_DismantleDropPod_C : public UWidget_AudioMessage_C
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass IntroTutorial_DismantleDropPod.IntroTutorial_DismantleDropPod_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

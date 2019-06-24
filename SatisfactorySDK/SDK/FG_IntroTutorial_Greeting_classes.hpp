#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_IntroTutorial_Greeting_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass IntroTutorial_Greeting.IntroTutorial_Greeting_C
// 0x0008 (0x02F8 - 0x02F0)
class UIntroTutorial_Greeting_C : public UWidget_AudioMessage_C
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x02F0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass IntroTutorial_Greeting.IntroTutorial_Greeting_C");
		return ptr;
	}


	void Destruct();
	void ExecuteUbergraph_IntroTutorial_Greeting(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

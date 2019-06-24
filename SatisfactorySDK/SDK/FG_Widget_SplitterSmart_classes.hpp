#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SplitterSmart_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_SplitterSmart.Widget_SplitterSmart_C
// 0x000F (0x02E8 - 0x02D9)
class UWidget_SplitterSmart_C : public UWidget_SplitterProgrammable_C
{
public:
	unsigned char                                      UnknownData00[0x7];                                       // 0x02D9(0x0007) MISSED OFFSET
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x02E0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_SplitterSmart.Widget_SplitterSmart_C");
		return ptr;
	}


	void Construct();
	void Destruct();
	void PreConstruct(bool* IsDesignTime);
	void ExecuteUbergraph_Widget_SplitterSmart(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

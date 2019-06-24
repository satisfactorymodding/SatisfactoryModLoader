#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_CodexEntryParent_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_CodexEntryParent.Widget_CodexEntryParent_C
// 0x0058 (0x0260 - 0x0208)
class UWidget_CodexEntryParent_C : public UWidget_CodexContent_C
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0208(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FText                                       mName;                                                    // 0x0210(0x0028) (Edit, BlueprintVisible, DisableEditOnInstance)
	class UTexture*                                    mIcon;                                                    // 0x0228(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<class UWidget_CodexContent_C*>              mRelatedEntries;                                          // 0x0230(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	TArray<struct FText>                               mStats;                                                   // 0x0240(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	TArray<struct FText>                               mAdditionalStats;                                         // 0x0250(0x0010) (Edit, BlueprintVisible, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_CodexEntryParent.Widget_CodexEntryParent_C");
		return ptr;
	}


	void GetStats();
	void Construct();
	void ExecuteUbergraph_Widget_CodexEntryParent(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

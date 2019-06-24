#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ResourceNode_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_ResourceNode.BP_ResourceNode_C
// 0x0010 (0x03D0 - 0x03C0)
class ABP_ResourceNode_C : public AFGResourceNode
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x03C0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x03C8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_ResourceNode.BP_ResourceNode_C");
		return ptr;
	}


	void UserConstructionScript();
	void GainedSignificance();
	void LostSignificance();
	void ExecuteUbergraph_BP_ResourceNode(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

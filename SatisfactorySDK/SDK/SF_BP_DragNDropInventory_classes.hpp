#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_BP_DragNDropInventory_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_DragNDropInventory.BP_DragNDropInventory_C
// 0x0008 (0x0090 - 0x0088)
class UBP_DragNDropInventory_C : public UDragDropOperation
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0088(0x0008) (Transient, DuplicateTransient)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_DragNDropInventory.BP_DragNDropInventory_C");
		return ptr;
	}


	void Dragged(struct FPointerEvent* PointerEvent);
	void DragCancelled(struct FPointerEvent* PointerEvent);
	void Drop(struct FPointerEvent* PointerEvent);
	void ExecuteUbergraph_BP_DragNDropInventory(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

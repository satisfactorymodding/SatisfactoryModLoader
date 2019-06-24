// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_InventorySlotInterface_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_InventorySlotInterface.BP_InventorySlotInterface_C.SubscribeToParentWindow
// ()
// Parameters:
// class UWidget_Window_C*        ParentWindow                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UBP_InventorySlotInterface_C::SubscribeToParentWindow(class UWidget_Window_C* ParentWindow)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_InventorySlotInterface.BP_InventorySlotInterface_C.SubscribeToParentWindow");

	UBP_InventorySlotInterface_C_SubscribeToParentWindow_Params params;
	params.ParentWindow = ParentWindow;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_InventoryAddNotificationIcon_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_InventoryAddNotificationIcon.Widget_InventoryAddNotificationIcon_C.Animate Icon
// ()

void UWidget_InventoryAddNotificationIcon_C::Animate_Icon()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventoryAddNotificationIcon.Widget_InventoryAddNotificationIcon_C.Animate Icon");

	UWidget_InventoryAddNotificationIcon_C_Animate_Icon_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventoryAddNotificationIcon.Widget_InventoryAddNotificationIcon_C.ExecuteUbergraph_Widget_InventoryAddNotificationIcon
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_InventoryAddNotificationIcon_C::ExecuteUbergraph_Widget_InventoryAddNotificationIcon(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventoryAddNotificationIcon.Widget_InventoryAddNotificationIcon_C.ExecuteUbergraph_Widget_InventoryAddNotificationIcon");

	UWidget_InventoryAddNotificationIcon_C_ExecuteUbergraph_Widget_InventoryAddNotificationIcon_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

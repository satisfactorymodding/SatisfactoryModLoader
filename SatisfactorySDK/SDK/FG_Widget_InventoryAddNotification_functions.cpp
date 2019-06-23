// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_InventoryAddNotification_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.BindOnInventoryAddAndCacheChar
// ()

void UWidget_InventoryAddNotification_C::BindOnInventoryAddAndCacheChar()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.BindOnInventoryAddAndCacheChar");

	UWidget_InventoryAddNotification_C_BindOnInventoryAddAndCacheChar_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.UnbindOnInventoryAdd
// ()
// Parameters:
// class AFGCharacterPlayer*      FromCharacter                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_InventoryAddNotification_C::UnbindOnInventoryAdd(class AFGCharacterPlayer* FromCharacter)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.UnbindOnInventoryAdd");

	UWidget_InventoryAddNotification_C_UnbindOnInventoryAdd_Params params;
	params.FromCharacter = FromCharacter;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.IsInventoryOpen
// ()
// Parameters:
// bool                           IsOpen                         (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_InventoryAddNotification_C::IsInventoryOpen(bool* IsOpen)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.IsInventoryOpen");

	UWidget_InventoryAddNotification_C_IsInventoryOpen_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (IsOpen != nullptr)
		*IsOpen = params.IsOpen;
}


// Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.OnItemADded
// ()
// Parameters:
// class UClass*                  ItemClass                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            numAdded                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_InventoryAddNotification_C::OnItemADded(class UClass* ItemClass, int numAdded)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.OnItemADded");

	UWidget_InventoryAddNotification_C_OnItemADded_Params params;
	params.ItemClass = ItemClass;
	params.numAdded = numAdded;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.Construct
// ()

void UWidget_InventoryAddNotification_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.Construct");

	UWidget_InventoryAddNotification_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.Destruct
// ()

void UWidget_InventoryAddNotification_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.Destruct");

	UWidget_InventoryAddNotification_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_InventoryAddNotification_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.Tick");

	UWidget_InventoryAddNotification_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.ExecuteUbergraph_Widget_InventoryAddNotification
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_InventoryAddNotification_C::ExecuteUbergraph_Widget_InventoryAddNotification(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.ExecuteUbergraph_Widget_InventoryAddNotification");

	UWidget_InventoryAddNotification_C_ExecuteUbergraph_Widget_InventoryAddNotification_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

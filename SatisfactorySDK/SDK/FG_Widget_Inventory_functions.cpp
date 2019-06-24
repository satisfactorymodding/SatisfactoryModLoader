// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Inventory_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Inventory.Widget_Inventory_C.GetAllInventorySlots
// ()
// Parameters:
// TArray<class UWidget_InventorySlot_C*> InventorySlots                 (Parm, OutParm, ZeroConstructor)

void UWidget_Inventory_C::GetAllInventorySlots(TArray<class UWidget_InventorySlot_C*>* InventorySlots)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Inventory.Widget_Inventory_C.GetAllInventorySlots");

	UWidget_Inventory_C_GetAllInventorySlots_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (InventorySlots != nullptr)
		*InventorySlots = params.InventorySlots;
}


// Function Widget_Inventory.Widget_Inventory_C.GetSqrtOfLinearSize
// ()
// Parameters:
// int                            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

int UWidget_Inventory_C::GetSqrtOfLinearSize()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Inventory.Widget_Inventory_C.GetSqrtOfLinearSize");

	UWidget_Inventory_C_GetSqrtOfLinearSize_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Inventory.Widget_Inventory_C.GetWidth
// ()
// Parameters:
// int                            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

int UWidget_Inventory_C::GetWidth()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Inventory.Widget_Inventory_C.GetWidth");

	UWidget_Inventory_C_GetWidth_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Inventory.Widget_Inventory_C.CreateAllSlots
// ()

void UWidget_Inventory_C::CreateAllSlots()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Inventory.Widget_Inventory_C.CreateAllSlots");

	UWidget_Inventory_C_CreateAllSlots_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Inventory.Widget_Inventory_C.ClearAllSlots
// ()

void UWidget_Inventory_C::ClearAllSlots()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Inventory.Widget_Inventory_C.ClearAllSlots");

	UWidget_Inventory_C_ClearAllSlots_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Inventory.Widget_Inventory_C.CalcIndex
// ()
// Parameters:
// int                            X                              (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            Y                              (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            Width                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            idx                            (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_Inventory_C::CalcIndex(int X, int Y, int Width, int* idx)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Inventory.Widget_Inventory_C.CalcIndex");

	UWidget_Inventory_C_CalcIndex_Params params;
	params.X = X;
	params.Y = Y;
	params.Width = Width;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (idx != nullptr)
		*idx = params.idx;
}


// Function Widget_Inventory.Widget_Inventory_C.CreateSlot
// ()
// Parameters:
// int                            Index                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            Row                            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            Column                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UWidget_InventorySlot_C* Result                         (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Inventory_C::CreateSlot(int Index, int Row, int Column, class UWidget_InventorySlot_C** Result)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Inventory.Widget_Inventory_C.CreateSlot");

	UWidget_Inventory_C_CreateSlot_Params params;
	params.Index = Index;
	params.Row = Row;
	params.Column = Column;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Result != nullptr)
		*Result = params.Result;
}


// Function Widget_Inventory.Widget_Inventory_C.Init
// ()
// Parameters:
// class UFGInventoryComponent*   component                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Inventory_C::Init(class UFGInventoryComponent* component)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Inventory.Widget_Inventory_C.Init");

	UWidget_Inventory_C_Init_Params params;
	params.component = component;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Inventory.Widget_Inventory_C.OnInventoryResized
// ()
// Parameters:
// int                            oldSize                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            newSize                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Inventory_C::OnInventoryResized(int oldSize, int newSize)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Inventory.Widget_Inventory_C.OnInventoryResized");

	UWidget_Inventory_C_OnInventoryResized_Params params;
	params.oldSize = oldSize;
	params.newSize = newSize;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Inventory.Widget_Inventory_C.Destruct
// ()

void UWidget_Inventory_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Inventory.Widget_Inventory_C.Destruct");

	UWidget_Inventory_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Inventory.Widget_Inventory_C.ExecuteUbergraph_Widget_Inventory
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Inventory_C::ExecuteUbergraph_Widget_Inventory(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Inventory.Widget_Inventory_C.ExecuteUbergraph_Widget_Inventory");

	UWidget_Inventory_C_ExecuteUbergraph_Widget_Inventory_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

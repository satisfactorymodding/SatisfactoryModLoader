// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_EmoteMenu_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_EmoteMenu.Widget_EmoteMenu_C.Construct
// ()

void UWidget_EmoteMenu_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_EmoteMenu.Widget_EmoteMenu_C.Construct");

	UWidget_EmoteMenu_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_EmoteMenu.Widget_EmoteMenu_C.Destruct
// ()

void UWidget_EmoteMenu_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_EmoteMenu.Widget_EmoteMenu_C.Destruct");

	UWidget_EmoteMenu_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_EmoteMenu.Widget_EmoteMenu_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_EmoteMenu_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_EmoteMenu.Widget_EmoteMenu_C.Tick");

	UWidget_EmoteMenu_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_EmoteMenu.Widget_EmoteMenu_C.ExecuteUbergraph_Widget_EmoteMenu
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_EmoteMenu_C::ExecuteUbergraph_Widget_EmoteMenu(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_EmoteMenu.Widget_EmoteMenu_C.ExecuteUbergraph_Widget_EmoteMenu");

	UWidget_EmoteMenu_C_ExecuteUbergraph_Widget_EmoteMenu_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_EmoteMenu.Widget_EmoteMenu_C.ShowEmote__DelegateSignature
// ()
// Parameters:
// int                            EmoteIndex                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_EmoteMenu_C::ShowEmote__DelegateSignature(int EmoteIndex)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_EmoteMenu.Widget_EmoteMenu_C.ShowEmote__DelegateSignature");

	UWidget_EmoteMenu_C_ShowEmote__DelegateSignature_Params params;
	params.EmoteIndex = EmoteIndex;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

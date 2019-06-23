// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_AudioMessage_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_AudioMessage.Widget_AudioMessage_C.SetSenderInfo
// ()
// Parameters:
// class UClass*                  inSender                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_AudioMessage_C::SetSenderInfo(class UClass* inSender)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AudioMessage.Widget_AudioMessage_C.SetSenderInfo");

	UWidget_AudioMessage_C_SetSenderInfo_Params params;
	params.inSender = inSender;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AudioMessage.Widget_AudioMessage_C.GetDarkGray
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_AudioMessage_C::GetDarkGray()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AudioMessage.Widget_AudioMessage_C.GetDarkGray");

	UWidget_AudioMessage_C_GetDarkGray_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_AudioMessage.Widget_AudioMessage_C.PlayNextDialogue
// ()

void UWidget_AudioMessage_C::PlayNextDialogue()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AudioMessage.Widget_AudioMessage_C.PlayNextDialogue");

	UWidget_AudioMessage_C_PlayNextDialogue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AudioMessage.Widget_AudioMessage_C.Construct
// ()

void UWidget_AudioMessage_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AudioMessage.Widget_AudioMessage_C.Construct");

	UWidget_AudioMessage_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AudioMessage.Widget_AudioMessage_C.ShowContent
// ()

void UWidget_AudioMessage_C::ShowContent()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AudioMessage.Widget_AudioMessage_C.ShowContent");

	UWidget_AudioMessage_C_ShowContent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AudioMessage.Widget_AudioMessage_C.Destruct
// ()

void UWidget_AudioMessage_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AudioMessage.Widget_AudioMessage_C.Destruct");

	UWidget_AudioMessage_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AudioMessage.Widget_AudioMessage_C.ExecuteUbergraph_Widget_AudioMessage
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_AudioMessage_C::ExecuteUbergraph_Widget_AudioMessage(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AudioMessage.Widget_AudioMessage_C.ExecuteUbergraph_Widget_AudioMessage");

	UWidget_AudioMessage_C_ExecuteUbergraph_Widget_AudioMessage_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

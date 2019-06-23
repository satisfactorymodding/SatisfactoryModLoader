// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_AggroText_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_AggroText.Widget_AggroText_C.Get_Text_Text_1
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_AggroText_C::Get_Text_Text_1()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AggroText.Widget_AggroText_C.Get_Text_Text_1");

	UWidget_AggroText_C_Get_Text_Text_1_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_AggroText.Widget_AggroText_C.SetAggroData
// ()
// Parameters:
// float                          Aggro                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class FString                  ActorName                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
// class FString                  Status                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)

void UWidget_AggroText_C::SetAggroData(float Aggro, const class FString& ActorName, const class FString& Status)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AggroText.Widget_AggroText_C.SetAggroData");

	UWidget_AggroText_C_SetAggroData_Params params;
	params.Aggro = Aggro;
	params.ActorName = ActorName;
	params.Status = Status;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AggroText.Widget_AggroText_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_AggroText_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AggroText.Widget_AggroText_C.Tick");

	UWidget_AggroText_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AggroText.Widget_AggroText_C.ExecuteUbergraph_Widget_AggroText
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_AggroText_C::ExecuteUbergraph_Widget_AggroText(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AggroText.Widget_AggroText_C.ExecuteUbergraph_Widget_AggroText");

	UWidget_AggroText_C_ExecuteUbergraph_Widget_AggroText_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

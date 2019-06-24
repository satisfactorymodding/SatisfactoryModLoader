// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_HUDBox_GasMask_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_HUDBox_GasMask.Widget_HUDBox_GasMask_C.Construct
// ()

void UWidget_HUDBox_GasMask_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_GasMask.Widget_HUDBox_GasMask_C.Construct");

	UWidget_HUDBox_GasMask_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBox_GasMask.Widget_HUDBox_GasMask_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_HUDBox_GasMask_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_GasMask.Widget_HUDBox_GasMask_C.Tick");

	UWidget_HUDBox_GasMask_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBox_GasMask.Widget_HUDBox_GasMask_C.ExecuteUbergraph_Widget_HUDBox_GasMask
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_HUDBox_GasMask_C::ExecuteUbergraph_Widget_HUDBox_GasMask(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_GasMask.Widget_HUDBox_GasMask_C.ExecuteUbergraph_Widget_HUDBox_GasMask");

	UWidget_HUDBox_GasMask_C_ExecuteUbergraph_Widget_HUDBox_GasMask_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

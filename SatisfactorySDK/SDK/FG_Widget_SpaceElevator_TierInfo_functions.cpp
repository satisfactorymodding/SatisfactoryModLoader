// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SpaceElevator_TierInfo_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_SpaceElevator_TierInfo.Widget_SpaceElevator_TierInfo_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SpaceElevator_TierInfo_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator_TierInfo.Widget_SpaceElevator_TierInfo_C.PreConstruct");

	UWidget_SpaceElevator_TierInfo_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator_TierInfo.Widget_SpaceElevator_TierInfo_C.ExecuteUbergraph_Widget_SpaceElevator_TierInfo
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SpaceElevator_TierInfo_C::ExecuteUbergraph_Widget_SpaceElevator_TierInfo(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator_TierInfo.Widget_SpaceElevator_TierInfo_C.ExecuteUbergraph_Widget_SpaceElevator_TierInfo");

	UWidget_SpaceElevator_TierInfo_C_ExecuteUbergraph_Widget_SpaceElevator_TierInfo_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

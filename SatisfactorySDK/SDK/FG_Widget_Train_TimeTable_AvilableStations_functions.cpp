// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Train_TimeTable_AvilableStations_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Train_TimeTable_AvilableStations.Widget_Train_TimeTable_AvilableStations_C.SetIsVisible
// ()
// Parameters:
// bool                           mIsVisible                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Train_TimeTable_AvilableStations_C::SetIsVisible(bool mIsVisible)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_AvilableStations.Widget_Train_TimeTable_AvilableStations_C.SetIsVisible");

	UWidget_Train_TimeTable_AvilableStations_C_SetIsVisible_Params params;
	params.mIsVisible = mIsVisible;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

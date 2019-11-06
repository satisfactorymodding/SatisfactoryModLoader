// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_GenericParticle_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_GenericParticle.Widget_GenericParticle_C.Construct
// ()

void UWidget_GenericParticle_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_GenericParticle.Widget_GenericParticle_C.Construct");

	UWidget_GenericParticle_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_GenericParticle.Widget_GenericParticle_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_GenericParticle_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_GenericParticle.Widget_GenericParticle_C.Tick");

	UWidget_GenericParticle_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_GenericParticle.Widget_GenericParticle_C.ExecuteUbergraph_Widget_GenericParticle
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_GenericParticle_C::ExecuteUbergraph_Widget_GenericParticle(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_GenericParticle.Widget_GenericParticle_C.ExecuteUbergraph_Widget_GenericParticle");

	UWidget_GenericParticle_C_ExecuteUbergraph_Widget_GenericParticle_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

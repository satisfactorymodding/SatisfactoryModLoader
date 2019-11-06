// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_GenericParticleSpawner_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_GenericParticleSpawner.Widget_GenericParticleSpawner_C.CreateParticles
// ()
// Parameters:
// int                            NumberOfParticles              (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_GenericParticleSpawner_C::CreateParticles(int NumberOfParticles)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_GenericParticleSpawner.Widget_GenericParticleSpawner_C.CreateParticles");

	UWidget_GenericParticleSpawner_C_CreateParticles_Params params;
	params.NumberOfParticles = NumberOfParticles;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_GenericParticleSpawner.Widget_GenericParticleSpawner_C.ExecuteUbergraph_Widget_GenericParticleSpawner
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_GenericParticleSpawner_C::ExecuteUbergraph_Widget_GenericParticleSpawner(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_GenericParticleSpawner.Widget_GenericParticleSpawner_C.ExecuteUbergraph_Widget_GenericParticleSpawner");

	UWidget_GenericParticleSpawner_C_ExecuteUbergraph_Widget_GenericParticleSpawner_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

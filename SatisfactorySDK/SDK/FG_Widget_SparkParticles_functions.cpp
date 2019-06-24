// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SparkParticles_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_SparkParticles.Widget_SparkParticles_C.CreateSparks
// ()
// Parameters:
// int                            NumberOfSparks                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SparkParticles_C::CreateSparks(int NumberOfSparks)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SparkParticles.Widget_SparkParticles_C.CreateSparks");

	UWidget_SparkParticles_C_CreateSparks_Params params;
	params.NumberOfSparks = NumberOfSparks;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SparkParticles.Widget_SparkParticles_C.OnSparkBounce
// ()
// Parameters:
// struct FVector2D               Position                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               Scale                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SparkParticles_C::OnSparkBounce(const struct FVector2D& Position, const struct FVector2D& Scale)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SparkParticles.Widget_SparkParticles_C.OnSparkBounce");

	UWidget_SparkParticles_C_OnSparkBounce_Params params;
	params.Position = Position;
	params.Scale = Scale;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SparkParticles.Widget_SparkParticles_C.ExecuteUbergraph_Widget_SparkParticles
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SparkParticles_C::ExecuteUbergraph_Widget_SparkParticles(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SparkParticles.Widget_SparkParticles_C.ExecuteUbergraph_Widget_SparkParticles");

	UWidget_SparkParticles_C_ExecuteUbergraph_Widget_SparkParticles_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_AggroEntry_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_AggroEntry.Widget_AggroEntry_C.GetSortedAggroEntries
// ()
// Parameters:
// TArray<struct FAggroEntry>     allEntries                     (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm)
// TArray<struct FAggroEntry>     sortedEntries                  (Parm, OutParm, ZeroConstructor)

void UWidget_AggroEntry_C::GetSortedAggroEntries(TArray<struct FAggroEntry>* allEntries, TArray<struct FAggroEntry>* sortedEntries)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AggroEntry.Widget_AggroEntry_C.GetSortedAggroEntries");

	UWidget_AggroEntry_C_GetSortedAggroEntries_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (allEntries != nullptr)
		*allEntries = params.allEntries;
	if (sortedEntries != nullptr)
		*sortedEntries = params.sortedEntries;
}


// Function Widget_AggroEntry.Widget_AggroEntry_C.UpdateAggroList
// ()

void UWidget_AggroEntry_C::UpdateAggroList()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AggroEntry.Widget_AggroEntry_C.UpdateAggroList");

	UWidget_AggroEntry_C_UpdateAggroList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AggroEntry.Widget_AggroEntry_C.Construct
// ()

void UWidget_AggroEntry_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AggroEntry.Widget_AggroEntry_C.Construct");

	UWidget_AggroEntry_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AggroEntry.Widget_AggroEntry_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_AggroEntry_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AggroEntry.Widget_AggroEntry_C.Tick");

	UWidget_AggroEntry_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AggroEntry.Widget_AggroEntry_C.ExecuteUbergraph_Widget_AggroEntry
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_AggroEntry_C::ExecuteUbergraph_Widget_AggroEntry(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AggroEntry.Widget_AggroEntry_C.ExecuteUbergraph_Widget_AggroEntry");

	UWidget_AggroEntry_C_ExecuteUbergraph_Widget_AggroEntry_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

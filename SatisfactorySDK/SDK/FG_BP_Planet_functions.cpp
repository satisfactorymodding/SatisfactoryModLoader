// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Planet_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_Planet.BP_Planet_C.ShouldSave
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_Planet_C::ShouldSave()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Planet.BP_Planet_C.ShouldSave");

	ABP_Planet_C_ShouldSave_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Planet.BP_Planet_C.GatherDependencies
// ()
// Parameters:
// TArray<class UObject*>         out_dependentObjects           (Parm, OutParm, ZeroConstructor)

void ABP_Planet_C::GatherDependencies(TArray<class UObject*>* out_dependentObjects)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Planet.BP_Planet_C.GatherDependencies");

	ABP_Planet_C_GatherDependencies_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (out_dependentObjects != nullptr)
		*out_dependentObjects = params.out_dependentObjects;
}


// Function BP_Planet.BP_Planet_C.NeedTransform
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_Planet_C::NeedTransform()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Planet.BP_Planet_C.NeedTransform");

	ABP_Planet_C_NeedTransform_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Planet.BP_Planet_C.UpdateMaterialParameters
// ()

void ABP_Planet_C::UpdateMaterialParameters()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Planet.BP_Planet_C.UpdateMaterialParameters");

	ABP_Planet_C_UpdateMaterialParameters_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Planet.BP_Planet_C.UserConstructionScript
// ()

void ABP_Planet_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Planet.BP_Planet_C.UserConstructionScript");

	ABP_Planet_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Planet.BP_Planet_C.PostSaveGame
// ()
// Parameters:
// int                            SaveVersion                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            GameVersion                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Planet_C::PostSaveGame(int SaveVersion, int GameVersion)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Planet.BP_Planet_C.PostSaveGame");

	ABP_Planet_C_PostSaveGame_Params params;
	params.SaveVersion = SaveVersion;
	params.GameVersion = GameVersion;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Planet.BP_Planet_C.PreLoadGame
// ()
// Parameters:
// int                            SaveVersion                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            GameVersion                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Planet_C::PreLoadGame(int SaveVersion, int GameVersion)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Planet.BP_Planet_C.PreLoadGame");

	ABP_Planet_C_PreLoadGame_Params params;
	params.SaveVersion = SaveVersion;
	params.GameVersion = GameVersion;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Planet.BP_Planet_C.ReceiveBeginPlay
// ()

void ABP_Planet_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Planet.BP_Planet_C.ReceiveBeginPlay");

	ABP_Planet_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Planet.BP_Planet_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Planet_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Planet.BP_Planet_C.ReceiveTick");

	ABP_Planet_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Planet.BP_Planet_C.UpdatePreview
// ()

void ABP_Planet_C::UpdatePreview()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Planet.BP_Planet_C.UpdatePreview");

	ABP_Planet_C_UpdatePreview_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Planet.BP_Planet_C.PreSaveGame
// ()
// Parameters:
// int                            SaveVersion                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            GameVersion                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Planet_C::PreSaveGame(int SaveVersion, int GameVersion)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Planet.BP_Planet_C.PreSaveGame");

	ABP_Planet_C_PreSaveGame_Params params;
	params.SaveVersion = SaveVersion;
	params.GameVersion = GameVersion;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Planet.BP_Planet_C.PostLoadGame
// ()
// Parameters:
// int                            SaveVersion                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            GameVersion                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Planet_C::PostLoadGame(int SaveVersion, int GameVersion)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Planet.BP_Planet_C.PostLoadGame");

	ABP_Planet_C_PostLoadGame_Params params;
	params.SaveVersion = SaveVersion;
	params.GameVersion = GameVersion;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Planet.BP_Planet_C.ExecuteUbergraph_BP_Planet
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Planet_C::ExecuteUbergraph_BP_Planet(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Planet.BP_Planet_C.ExecuteUbergraph_BP_Planet");

	ABP_Planet_C_ExecuteUbergraph_BP_Planet_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

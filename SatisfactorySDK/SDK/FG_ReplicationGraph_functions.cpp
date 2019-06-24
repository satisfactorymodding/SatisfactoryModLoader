// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_ReplicationGraph_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function ReplicationGraph.ReplicationGraphDebugActor.ServerStopDebugging
// ()

void AReplicationGraphDebugActor::ServerStopDebugging()
{
	static auto fn = UObject::FindObject<UFunction>("Function ReplicationGraph.ReplicationGraphDebugActor.ServerStopDebugging");

	AReplicationGraphDebugActor_ServerStopDebugging_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function ReplicationGraph.ReplicationGraphDebugActor.ServerStartDebugging
// ()

void AReplicationGraphDebugActor::ServerStartDebugging()
{
	static auto fn = UObject::FindObject<UFunction>("Function ReplicationGraph.ReplicationGraphDebugActor.ServerStartDebugging");

	AReplicationGraphDebugActor_ServerStartDebugging_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function ReplicationGraph.ReplicationGraphDebugActor.ServerSetPeriodFrameForClass
// ()
// Parameters:
// class UClass*                  Class                          (Parm, ZeroConstructor, IsPlainOldData)
// int                            PeriodFrame                    (Parm, ZeroConstructor, IsPlainOldData)

void AReplicationGraphDebugActor::ServerSetPeriodFrameForClass(class UClass* Class, int PeriodFrame)
{
	static auto fn = UObject::FindObject<UFunction>("Function ReplicationGraph.ReplicationGraphDebugActor.ServerSetPeriodFrameForClass");

	AReplicationGraphDebugActor_ServerSetPeriodFrameForClass_Params params;
	params.Class = Class;
	params.PeriodFrame = PeriodFrame;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function ReplicationGraph.ReplicationGraphDebugActor.ServerSetCullDistanceForClass
// ()
// Parameters:
// class UClass*                  Class                          (Parm, ZeroConstructor, IsPlainOldData)
// float                          CullDistance                   (Parm, ZeroConstructor, IsPlainOldData)

void AReplicationGraphDebugActor::ServerSetCullDistanceForClass(class UClass* Class, float CullDistance)
{
	static auto fn = UObject::FindObject<UFunction>("Function ReplicationGraph.ReplicationGraphDebugActor.ServerSetCullDistanceForClass");

	AReplicationGraphDebugActor_ServerSetCullDistanceForClass_Params params;
	params.Class = Class;
	params.CullDistance = CullDistance;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function ReplicationGraph.ReplicationGraphDebugActor.ServerPrintAllActorInfo
// ()
// Parameters:
// class FString                  str                            (Parm, ZeroConstructor)

void AReplicationGraphDebugActor::ServerPrintAllActorInfo(const class FString& str)
{
	static auto fn = UObject::FindObject<UFunction>("Function ReplicationGraph.ReplicationGraphDebugActor.ServerPrintAllActorInfo");

	AReplicationGraphDebugActor_ServerPrintAllActorInfo_Params params;
	params.str = str;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function ReplicationGraph.ReplicationGraphDebugActor.ServerPrintAllActorDependencies
// ()
// Parameters:
// class FString                  str                            (Parm, ZeroConstructor)

void AReplicationGraphDebugActor::ServerPrintAllActorDependencies(const class FString& str)
{
	static auto fn = UObject::FindObject<UFunction>("Function ReplicationGraph.ReplicationGraphDebugActor.ServerPrintAllActorDependencies");

	AReplicationGraphDebugActor_ServerPrintAllActorDependencies_Params params;
	params.str = str;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function ReplicationGraph.ReplicationGraphDebugActor.ServerCellInfo
// ()

void AReplicationGraphDebugActor::ServerCellInfo()
{
	static auto fn = UObject::FindObject<UFunction>("Function ReplicationGraph.ReplicationGraphDebugActor.ServerCellInfo");

	AReplicationGraphDebugActor_ServerCellInfo_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function ReplicationGraph.ReplicationGraphDebugActor.ClientCellInfo
// ()
// Parameters:
// struct FVector                 CellLocation                   (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 CellExtent                     (Parm, ZeroConstructor, IsPlainOldData)
// TArray<class AActor*>          Actors                         (ConstParm, Parm, ZeroConstructor, ReferenceParm)

void AReplicationGraphDebugActor::ClientCellInfo(const struct FVector& CellLocation, const struct FVector& CellExtent, TArray<class AActor*> Actors)
{
	static auto fn = UObject::FindObject<UFunction>("Function ReplicationGraph.ReplicationGraphDebugActor.ClientCellInfo");

	AReplicationGraphDebugActor_ClientCellInfo_Params params;
	params.CellLocation = CellLocation;
	params.CellExtent = CellExtent;
	params.Actors = Actors;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

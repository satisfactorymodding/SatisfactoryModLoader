#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_ReplicationGraph_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function ReplicationGraph.ReplicationGraphDebugActor.ServerStopDebugging
struct AReplicationGraphDebugActor_ServerStopDebugging_Params
{
};

// Function ReplicationGraph.ReplicationGraphDebugActor.ServerStartDebugging
struct AReplicationGraphDebugActor_ServerStartDebugging_Params
{
};

// Function ReplicationGraph.ReplicationGraphDebugActor.ServerSetCullDistanceForClass
struct AReplicationGraphDebugActor_ServerSetCullDistanceForClass_Params
{
	class UClass*                                      Class;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              CullDistance;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function ReplicationGraph.ReplicationGraphDebugActor.ServerPrintAllActorInfo
struct AReplicationGraphDebugActor_ServerPrintAllActorInfo_Params
{
	class FString                                      str;                                                      // (Parm, ZeroConstructor)
};

// Function ReplicationGraph.ReplicationGraphDebugActor.ServerPrintAllActorDependencies
struct AReplicationGraphDebugActor_ServerPrintAllActorDependencies_Params
{
	class FString                                      str;                                                      // (Parm, ZeroConstructor)
};

// Function ReplicationGraph.ReplicationGraphDebugActor.ServerCellInfo
struct AReplicationGraphDebugActor_ServerCellInfo_Params
{
};

// Function ReplicationGraph.ReplicationGraphDebugActor.ClientCellInfo
struct AReplicationGraphDebugActor_ClientCellInfo_Params
{
	struct FVector                                     CellLocation;                                             // (Parm, IsPlainOldData)
	struct FVector                                     CellExtent;                                               // (Parm, IsPlainOldData)
	TArray<class AActor*>                              Actors;                                                   // (ConstParm, Parm, ZeroConstructor, ReferenceParm)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

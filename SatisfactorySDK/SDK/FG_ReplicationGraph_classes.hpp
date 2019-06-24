#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_ReplicationGraph_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class ReplicationGraph.ReplicationGraph
// 0x02C8 (0x02F0 - 0x0028)
class UReplicationGraph : public UReplicationDriver
{
public:
	class UClass*                                      ReplicationConnectionManagerClass;                        // 0x0028(0x0008) (ZeroConstructor, Config, IsPlainOldData)
	class UNetDriver*                                  NetDriver;                                                // 0x0030(0x0008) (ZeroConstructor, IsPlainOldData)
	TArray<class UNetReplicationGraphConnection*>      Connections;                                              // 0x0038(0x0010) (ZeroConstructor)
	TArray<class UNetReplicationGraphConnection*>      PendingConnections;                                       // 0x0048(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData00[0x40];                                      // 0x0058(0x0040) MISSED OFFSET
	TArray<class UReplicationGraphNode*>               GlobalGraphNodes;                                         // 0x0098(0x0010) (ZeroConstructor)
	TArray<class UReplicationGraphNode*>               PrepareForReplicationNodes;                               // 0x00A8(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData01[0x238];                                     // 0x00B8(0x0238) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class ReplicationGraph.ReplicationGraph");
		return ptr;
	}

};


// Class ReplicationGraph.BasicReplicationGraph
// 0x0030 (0x0320 - 0x02F0)
class UBasicReplicationGraph : public UReplicationGraph
{
public:
	class UReplicationGraphNode_GridSpatialization2D*  GridNode;                                                 // 0x02F0(0x0008) (ZeroConstructor, IsPlainOldData)
	class UReplicationGraphNode_ActorList*             AlwaysRelevantNode;                                       // 0x02F8(0x0008) (ZeroConstructor, IsPlainOldData)
	TArray<struct FConnectionAlwaysRelevantNodePair>   AlwaysRelevantForConnectionList;                          // 0x0300(0x0010) (ZeroConstructor)
	TArray<class AActor*>                              ActorsWithoutNetConnection;                               // 0x0310(0x0010) (ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class ReplicationGraph.BasicReplicationGraph");
		return ptr;
	}

};


// Class ReplicationGraph.ReplicationGraphNode
// 0x0028 (0x0050 - 0x0028)
class UReplicationGraphNode : public UObject
{
public:
	TArray<class UReplicationGraphNode*>               AllChildNodes;                                            // 0x0028(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData00[0x18];                                      // 0x0038(0x0018) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class ReplicationGraph.ReplicationGraphNode");
		return ptr;
	}

};


// Class ReplicationGraph.ReplicationGraphNode_ActorList
// 0x00A8 (0x00F8 - 0x0050)
class UReplicationGraphNode_ActorList : public UReplicationGraphNode
{
public:
	unsigned char                                      UnknownData00[0xA8];                                      // 0x0050(0x00A8) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class ReplicationGraph.ReplicationGraphNode_ActorList");
		return ptr;
	}

};


// Class ReplicationGraph.ReplicationGraphNode_ActorListFrequencyBuckets
// 0x00E8 (0x0138 - 0x0050)
class UReplicationGraphNode_ActorListFrequencyBuckets : public UReplicationGraphNode
{
public:
	unsigned char                                      UnknownData00[0xE8];                                      // 0x0050(0x00E8) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class ReplicationGraph.ReplicationGraphNode_ActorListFrequencyBuckets");
		return ptr;
	}

};


// Class ReplicationGraph.ReplicationGraphNode_ConnectionDormanyNode
// 0x0098 (0x0190 - 0x00F8)
class UReplicationGraphNode_ConnectionDormanyNode : public UReplicationGraphNode_ActorList
{
public:
	unsigned char                                      UnknownData00[0x98];                                      // 0x00F8(0x0098) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class ReplicationGraph.ReplicationGraphNode_ConnectionDormanyNode");
		return ptr;
	}

};


// Class ReplicationGraph.ReplicationGraphNode_DormancyNode
// 0x0050 (0x0148 - 0x00F8)
class UReplicationGraphNode_DormancyNode : public UReplicationGraphNode_ActorList
{
public:
	unsigned char                                      UnknownData00[0x50];                                      // 0x00F8(0x0050) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class ReplicationGraph.ReplicationGraphNode_DormancyNode");
		return ptr;
	}

};


// Class ReplicationGraph.ReplicationGraphNode_GridCell
// 0x0058 (0x0150 - 0x00F8)
class UReplicationGraphNode_GridCell : public UReplicationGraphNode_ActorList
{
public:
	unsigned char                                      UnknownData00[0x48];                                      // 0x00F8(0x0048) MISSED OFFSET
	class UReplicationGraphNode*                       DynamicNode;                                              // 0x0140(0x0008) (ZeroConstructor, IsPlainOldData)
	class UReplicationGraphNode_DormancyNode*          DormancyNode;                                             // 0x0148(0x0008) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class ReplicationGraph.ReplicationGraphNode_GridCell");
		return ptr;
	}

};


// Class ReplicationGraph.ReplicationGraphNode_GridSpatialization2D
// 0x0170 (0x01C0 - 0x0050)
class UReplicationGraphNode_GridSpatialization2D : public UReplicationGraphNode
{
public:
	unsigned char                                      UnknownData00[0x170];                                     // 0x0050(0x0170) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class ReplicationGraph.ReplicationGraphNode_GridSpatialization2D");
		return ptr;
	}

};


// Class ReplicationGraph.ReplicationGraphNode_AlwaysRelevant
// 0x0018 (0x0068 - 0x0050)
class UReplicationGraphNode_AlwaysRelevant : public UReplicationGraphNode
{
public:
	class UReplicationGraphNode*                       ChildNode;                                                // 0x0050(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x10];                                      // 0x0058(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class ReplicationGraph.ReplicationGraphNode_AlwaysRelevant");
		return ptr;
	}

};


// Class ReplicationGraph.ReplicationGraphNode_AlwaysRelevant_ForConnection
// 0x0028 (0x0120 - 0x00F8)
class UReplicationGraphNode_AlwaysRelevant_ForConnection : public UReplicationGraphNode_ActorList
{
public:
	unsigned char                                      UnknownData00[0x18];                                      // 0x00F8(0x0018) MISSED OFFSET
	class AActor*                                      LastViewer;                                               // 0x0110(0x0008) (ZeroConstructor, IsPlainOldData)
	class AActor*                                      LastViewTarget;                                           // 0x0118(0x0008) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class ReplicationGraph.ReplicationGraphNode_AlwaysRelevant_ForConnection");
		return ptr;
	}

};


// Class ReplicationGraph.ReplicationGraphNode_TearOff_ForConnection
// 0x0028 (0x0078 - 0x0050)
class UReplicationGraphNode_TearOff_ForConnection : public UReplicationGraphNode
{
public:
	TArray<struct FTearOffActorInfo>                   TearOffActors;                                            // 0x0050(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData00[0x18];                                      // 0x0060(0x0018) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class ReplicationGraph.ReplicationGraphNode_TearOff_ForConnection");
		return ptr;
	}

};


// Class ReplicationGraph.NetReplicationGraphConnection
// 0x0180 (0x01A8 - 0x0028)
class UNetReplicationGraphConnection : public UReplicationConnectionDriver
{
public:
	class UNetConnection*                              NetConnection;                                            // 0x0028(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x140];                                     // 0x0030(0x0140) MISSED OFFSET
	class AReplicationGraphDebugActor*                 DebugActor;                                               // 0x0170(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0178(0x0008) MISSED OFFSET
	TArray<class UReplicationGraphNode*>               ConnectionGraphNodes;                                     // 0x0180(0x0010) (ZeroConstructor)
	class UReplicationGraphNode_TearOff_ForConnection* TearOffNode;                                              // 0x0190(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x10];                                      // 0x0198(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class ReplicationGraph.NetReplicationGraphConnection");
		return ptr;
	}

};


// Class ReplicationGraph.ReplicationGraphDebugActor
// 0x0010 (0x0338 - 0x0328)
class AReplicationGraphDebugActor : public AActor
{
public:
	class UReplicationGraph*                           ReplicationGraph;                                         // 0x0328(0x0008) (ZeroConstructor, IsPlainOldData)
	class UNetReplicationGraphConnection*              ConnectionManager;                                        // 0x0330(0x0008) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class ReplicationGraph.ReplicationGraphDebugActor");
		return ptr;
	}


	void ServerStopDebugging();
	void ServerStartDebugging();
	void ServerSetPeriodFrameForClass(class UClass* Class, int PeriodFrame);
	void ServerSetCullDistanceForClass(class UClass* Class, float CullDistance);
	void ServerPrintAllActorInfo(const class FString& str);
	void ServerPrintAllActorDependencies(const class FString& str);
	void ServerCellInfo();
	void ClientCellInfo(const struct FVector& CellLocation, const struct FVector& CellExtent, TArray<class AActor*> Actors);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_GeometryCache_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function GeometryCache.GeometryCacheActor.GetGeometryCacheComponent
struct AGeometryCacheActor_GetGeometryCacheComponent_Params
{
	class UGeometryCacheComponent*                     ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function GeometryCache.GeometryCacheComponent.TickAtThisTime
struct UGeometryCacheComponent_TickAtThisTime_Params
{
	float                                              Time;                                                     // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bInIsRunning;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bInBackwards;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bInIsLooping;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function GeometryCache.GeometryCacheComponent.Stop
struct UGeometryCacheComponent_Stop_Params
{
};

// Function GeometryCache.GeometryCacheComponent.SetStartTimeOffset
struct UGeometryCacheComponent_SetStartTimeOffset_Params
{
	float                                              NewStartTimeOffset;                                       // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
};

// Function GeometryCache.GeometryCacheComponent.SetPlaybackSpeed
struct UGeometryCacheComponent_SetPlaybackSpeed_Params
{
	float                                              NewPlaybackSpeed;                                         // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
};

// Function GeometryCache.GeometryCacheComponent.SetLooping
struct UGeometryCacheComponent_SetLooping_Params
{
	bool                                               bNewLooping;                                              // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
};

// Function GeometryCache.GeometryCacheComponent.SetGeometryCache
struct UGeometryCacheComponent_SetGeometryCache_Params
{
	class UGeometryCache*                              NewGeomCache;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GeometryCache.GeometryCacheComponent.PlayReversedFromEnd
struct UGeometryCacheComponent_PlayReversedFromEnd_Params
{
};

// Function GeometryCache.GeometryCacheComponent.PlayReversed
struct UGeometryCacheComponent_PlayReversed_Params
{
};

// Function GeometryCache.GeometryCacheComponent.PlayFromStart
struct UGeometryCacheComponent_PlayFromStart_Params
{
};

// Function GeometryCache.GeometryCacheComponent.Play
struct UGeometryCacheComponent_Play_Params
{
};

// Function GeometryCache.GeometryCacheComponent.Pause
struct UGeometryCacheComponent_Pause_Params
{
};

// Function GeometryCache.GeometryCacheComponent.IsPlayingReversed
struct UGeometryCacheComponent_IsPlayingReversed_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GeometryCache.GeometryCacheComponent.IsPlaying
struct UGeometryCacheComponent_IsPlaying_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GeometryCache.GeometryCacheComponent.IsLooping
struct UGeometryCacheComponent_IsLooping_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GeometryCache.GeometryCacheComponent.GetStartTimeOffset
struct UGeometryCacheComponent_GetStartTimeOffset_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GeometryCache.GeometryCacheComponent.GetPlaybackSpeed
struct UGeometryCacheComponent_GetPlaybackSpeed_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GeometryCache.GeometryCacheComponent.GetPlaybackDirection
struct UGeometryCacheComponent_GetPlaybackDirection_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GeometryCache.GeometryCacheComponent.GetNumberOfFrames
struct UGeometryCacheComponent_GetNumberOfFrames_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GeometryCache.GeometryCacheComponent.GetDuration
struct UGeometryCacheComponent_GetDuration_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GeometryCache.GeometryCacheComponent.GetAnimationTime
struct UGeometryCacheComponent_GetAnimationTime_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function GeometryCache.GeometryCacheTrack_FlipbookAnimation.AddMeshSample
struct UGeometryCacheTrack_FlipbookAnimation_AddMeshSample_Params
{
	struct FGeometryCacheMeshData                      MeshData;                                                 // (ConstParm, Parm, OutParm, ReferenceParm)
	float                                              SampleTime;                                               // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
};

// Function GeometryCache.GeometryCacheTrack_TransformAnimation.SetMesh
struct UGeometryCacheTrack_TransformAnimation_SetMesh_Params
{
	struct FGeometryCacheMeshData                      NewMeshData;                                              // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function GeometryCache.GeometryCacheTrack_TransformGroupAnimation.SetMesh
struct UGeometryCacheTrack_TransformGroupAnimation_SetMesh_Params
{
	struct FGeometryCacheMeshData                      NewMeshData;                                              // (ConstParm, Parm, OutParm, ReferenceParm)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

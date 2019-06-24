// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_GeometryCache_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function GeometryCache.GeometryCacheActor.GetGeometryCacheComponent
// ()
// Parameters:
// class UGeometryCacheComponent* ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UGeometryCacheComponent* AGeometryCacheActor::GetGeometryCacheComponent()
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheActor.GetGeometryCacheComponent");

	AGeometryCacheActor_GetGeometryCacheComponent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function GeometryCache.GeometryCacheComponent.TickAtThisTime
// ()
// Parameters:
// float                          Time                           (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
// bool                           bInIsRunning                   (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bInBackwards                   (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bInIsLooping                   (Parm, ZeroConstructor, IsPlainOldData)

void UGeometryCacheComponent::TickAtThisTime(float Time, bool bInIsRunning, bool bInBackwards, bool bInIsLooping)
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheComponent.TickAtThisTime");

	UGeometryCacheComponent_TickAtThisTime_Params params;
	params.Time = Time;
	params.bInIsRunning = bInIsRunning;
	params.bInBackwards = bInBackwards;
	params.bInIsLooping = bInIsLooping;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function GeometryCache.GeometryCacheComponent.Stop
// ()

void UGeometryCacheComponent::Stop()
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheComponent.Stop");

	UGeometryCacheComponent_Stop_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function GeometryCache.GeometryCacheComponent.SetStartTimeOffset
// ()
// Parameters:
// float                          NewStartTimeOffset             (ConstParm, Parm, ZeroConstructor, IsPlainOldData)

void UGeometryCacheComponent::SetStartTimeOffset(float NewStartTimeOffset)
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheComponent.SetStartTimeOffset");

	UGeometryCacheComponent_SetStartTimeOffset_Params params;
	params.NewStartTimeOffset = NewStartTimeOffset;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function GeometryCache.GeometryCacheComponent.SetPlaybackSpeed
// ()
// Parameters:
// float                          NewPlaybackSpeed               (ConstParm, Parm, ZeroConstructor, IsPlainOldData)

void UGeometryCacheComponent::SetPlaybackSpeed(float NewPlaybackSpeed)
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheComponent.SetPlaybackSpeed");

	UGeometryCacheComponent_SetPlaybackSpeed_Params params;
	params.NewPlaybackSpeed = NewPlaybackSpeed;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function GeometryCache.GeometryCacheComponent.SetLooping
// ()
// Parameters:
// bool                           bNewLooping                    (ConstParm, Parm, ZeroConstructor, IsPlainOldData)

void UGeometryCacheComponent::SetLooping(bool bNewLooping)
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheComponent.SetLooping");

	UGeometryCacheComponent_SetLooping_Params params;
	params.bNewLooping = bNewLooping;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function GeometryCache.GeometryCacheComponent.SetGeometryCache
// ()
// Parameters:
// class UGeometryCache*          NewGeomCache                   (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UGeometryCacheComponent::SetGeometryCache(class UGeometryCache* NewGeomCache)
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheComponent.SetGeometryCache");

	UGeometryCacheComponent_SetGeometryCache_Params params;
	params.NewGeomCache = NewGeomCache;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function GeometryCache.GeometryCacheComponent.PlayReversedFromEnd
// ()

void UGeometryCacheComponent::PlayReversedFromEnd()
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheComponent.PlayReversedFromEnd");

	UGeometryCacheComponent_PlayReversedFromEnd_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function GeometryCache.GeometryCacheComponent.PlayReversed
// ()

void UGeometryCacheComponent::PlayReversed()
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheComponent.PlayReversed");

	UGeometryCacheComponent_PlayReversed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function GeometryCache.GeometryCacheComponent.PlayFromStart
// ()

void UGeometryCacheComponent::PlayFromStart()
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheComponent.PlayFromStart");

	UGeometryCacheComponent_PlayFromStart_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function GeometryCache.GeometryCacheComponent.Play
// ()

void UGeometryCacheComponent::Play()
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheComponent.Play");

	UGeometryCacheComponent_Play_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function GeometryCache.GeometryCacheComponent.Pause
// ()

void UGeometryCacheComponent::Pause()
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheComponent.Pause");

	UGeometryCacheComponent_Pause_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function GeometryCache.GeometryCacheComponent.IsPlayingReversed
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UGeometryCacheComponent::IsPlayingReversed()
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheComponent.IsPlayingReversed");

	UGeometryCacheComponent_IsPlayingReversed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function GeometryCache.GeometryCacheComponent.IsPlaying
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UGeometryCacheComponent::IsPlaying()
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheComponent.IsPlaying");

	UGeometryCacheComponent_IsPlaying_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function GeometryCache.GeometryCacheComponent.IsLooping
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UGeometryCacheComponent::IsLooping()
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheComponent.IsLooping");

	UGeometryCacheComponent_IsLooping_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function GeometryCache.GeometryCacheComponent.GetStartTimeOffset
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UGeometryCacheComponent::GetStartTimeOffset()
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheComponent.GetStartTimeOffset");

	UGeometryCacheComponent_GetStartTimeOffset_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function GeometryCache.GeometryCacheComponent.GetPlaybackSpeed
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UGeometryCacheComponent::GetPlaybackSpeed()
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheComponent.GetPlaybackSpeed");

	UGeometryCacheComponent_GetPlaybackSpeed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function GeometryCache.GeometryCacheComponent.GetPlaybackDirection
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UGeometryCacheComponent::GetPlaybackDirection()
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheComponent.GetPlaybackDirection");

	UGeometryCacheComponent_GetPlaybackDirection_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function GeometryCache.GeometryCacheComponent.GetNumberOfFrames
// ()
// Parameters:
// int                            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

int UGeometryCacheComponent::GetNumberOfFrames()
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheComponent.GetNumberOfFrames");

	UGeometryCacheComponent_GetNumberOfFrames_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function GeometryCache.GeometryCacheComponent.GetDuration
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UGeometryCacheComponent::GetDuration()
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheComponent.GetDuration");

	UGeometryCacheComponent_GetDuration_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function GeometryCache.GeometryCacheComponent.GetAnimationTime
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UGeometryCacheComponent::GetAnimationTime()
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheComponent.GetAnimationTime");

	UGeometryCacheComponent_GetAnimationTime_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function GeometryCache.GeometryCacheTrack_FlipbookAnimation.AddMeshSample
// ()
// Parameters:
// struct FGeometryCacheMeshData  MeshData                       (ConstParm, Parm, OutParm, ReferenceParm)
// float                          SampleTime                     (ConstParm, Parm, ZeroConstructor, IsPlainOldData)

void UGeometryCacheTrack_FlipbookAnimation::AddMeshSample(const struct FGeometryCacheMeshData& MeshData, float SampleTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheTrack_FlipbookAnimation.AddMeshSample");

	UGeometryCacheTrack_FlipbookAnimation_AddMeshSample_Params params;
	params.MeshData = MeshData;
	params.SampleTime = SampleTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function GeometryCache.GeometryCacheTrack_TransformAnimation.SetMesh
// ()
// Parameters:
// struct FGeometryCacheMeshData  NewMeshData                    (ConstParm, Parm, OutParm, ReferenceParm)

void UGeometryCacheTrack_TransformAnimation::SetMesh(const struct FGeometryCacheMeshData& NewMeshData)
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheTrack_TransformAnimation.SetMesh");

	UGeometryCacheTrack_TransformAnimation_SetMesh_Params params;
	params.NewMeshData = NewMeshData;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function GeometryCache.GeometryCacheTrack_TransformGroupAnimation.SetMesh
// ()
// Parameters:
// struct FGeometryCacheMeshData  NewMeshData                    (ConstParm, Parm, OutParm, ReferenceParm)

void UGeometryCacheTrack_TransformGroupAnimation::SetMesh(const struct FGeometryCacheMeshData& NewMeshData)
{
	static auto fn = UObject::FindObject<UFunction>("Function GeometryCache.GeometryCacheTrack_TransformGroupAnimation.SetMesh");

	UGeometryCacheTrack_TransformGroupAnimation_SetMesh_Params params;
	params.NewMeshData = NewMeshData;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

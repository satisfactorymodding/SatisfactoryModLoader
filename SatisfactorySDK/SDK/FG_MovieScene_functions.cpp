// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_MovieScene_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function MovieScene.MovieSceneSequencePlayer.Stop
// ()

void UMovieSceneSequencePlayer::Stop()
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.Stop");

	UMovieSceneSequencePlayer_Stop_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function MovieScene.MovieSceneSequencePlayer.SetTimeRange
// ()
// Parameters:
// float                          StartTime                      (Parm, ZeroConstructor, IsPlainOldData)
// float                          Duration                       (Parm, ZeroConstructor, IsPlainOldData)

void UMovieSceneSequencePlayer::SetTimeRange(float StartTime, float Duration)
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.SetTimeRange");

	UMovieSceneSequencePlayer_SetTimeRange_Params params;
	params.StartTime = StartTime;
	params.Duration = Duration;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function MovieScene.MovieSceneSequencePlayer.SetPlayRate
// ()
// Parameters:
// float                          PlayRate                       (Parm, ZeroConstructor, IsPlainOldData)

void UMovieSceneSequencePlayer::SetPlayRate(float PlayRate)
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.SetPlayRate");

	UMovieSceneSequencePlayer_SetPlayRate_Params params;
	params.PlayRate = PlayRate;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function MovieScene.MovieSceneSequencePlayer.SetPlaybackRange
// ()
// Parameters:
// float                          NewStartTime                   (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
// float                          NewEndTime                     (ConstParm, Parm, ZeroConstructor, IsPlainOldData)

void UMovieSceneSequencePlayer::SetPlaybackRange(float NewStartTime, float NewEndTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.SetPlaybackRange");

	UMovieSceneSequencePlayer_SetPlaybackRange_Params params;
	params.NewStartTime = NewStartTime;
	params.NewEndTime = NewEndTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function MovieScene.MovieSceneSequencePlayer.SetPlaybackPosition
// ()
// Parameters:
// float                          NewPlaybackPosition            (Parm, ZeroConstructor, IsPlainOldData)

void UMovieSceneSequencePlayer::SetPlaybackPosition(float NewPlaybackPosition)
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.SetPlaybackPosition");

	UMovieSceneSequencePlayer_SetPlaybackPosition_Params params;
	params.NewPlaybackPosition = NewPlaybackPosition;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function MovieScene.MovieSceneSequencePlayer.SetFrameRate
// ()
// Parameters:
// struct FFrameRate              FrameRate                      (Parm, ZeroConstructor, IsPlainOldData)

void UMovieSceneSequencePlayer::SetFrameRate(const struct FFrameRate& FrameRate)
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.SetFrameRate");

	UMovieSceneSequencePlayer_SetFrameRate_Params params;
	params.FrameRate = FrameRate;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function MovieScene.MovieSceneSequencePlayer.SetFrameRange
// ()
// Parameters:
// int                            StartFrame                     (Parm, ZeroConstructor, IsPlainOldData)
// int                            Duration                       (Parm, ZeroConstructor, IsPlainOldData)

void UMovieSceneSequencePlayer::SetFrameRange(int StartFrame, int Duration)
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.SetFrameRange");

	UMovieSceneSequencePlayer_SetFrameRange_Params params;
	params.StartFrame = StartFrame;
	params.Duration = Duration;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function MovieScene.MovieSceneSequencePlayer.SetDisableCameraCuts
// ()
// Parameters:
// bool                           bInDisableCameraCuts           (Parm, ZeroConstructor, IsPlainOldData)

void UMovieSceneSequencePlayer::SetDisableCameraCuts(bool bInDisableCameraCuts)
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.SetDisableCameraCuts");

	UMovieSceneSequencePlayer_SetDisableCameraCuts_Params params;
	params.bInDisableCameraCuts = bInDisableCameraCuts;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function MovieScene.MovieSceneSequencePlayer.ScrubToSeconds
// ()
// Parameters:
// float                          TimeInSeconds                  (Parm, ZeroConstructor, IsPlainOldData)

void UMovieSceneSequencePlayer::ScrubToSeconds(float TimeInSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.ScrubToSeconds");

	UMovieSceneSequencePlayer_ScrubToSeconds_Params params;
	params.TimeInSeconds = TimeInSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function MovieScene.MovieSceneSequencePlayer.ScrubToFrame
// ()
// Parameters:
// struct FFrameTime              NewPosition                    (Parm)

void UMovieSceneSequencePlayer::ScrubToFrame(const struct FFrameTime& NewPosition)
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.ScrubToFrame");

	UMovieSceneSequencePlayer_ScrubToFrame_Params params;
	params.NewPosition = NewPosition;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function MovieScene.MovieSceneSequencePlayer.Scrub
// ()

void UMovieSceneSequencePlayer::Scrub()
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.Scrub");

	UMovieSceneSequencePlayer_Scrub_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function MovieScene.MovieSceneSequencePlayer.PlayToSeconds
// ()
// Parameters:
// float                          TimeInSeconds                  (Parm, ZeroConstructor, IsPlainOldData)

void UMovieSceneSequencePlayer::PlayToSeconds(float TimeInSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.PlayToSeconds");

	UMovieSceneSequencePlayer_PlayToSeconds_Params params;
	params.TimeInSeconds = TimeInSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function MovieScene.MovieSceneSequencePlayer.PlayToFrame
// ()
// Parameters:
// struct FFrameTime              NewPosition                    (Parm)

void UMovieSceneSequencePlayer::PlayToFrame(const struct FFrameTime& NewPosition)
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.PlayToFrame");

	UMovieSceneSequencePlayer_PlayToFrame_Params params;
	params.NewPosition = NewPosition;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function MovieScene.MovieSceneSequencePlayer.PlayReverse
// ()

void UMovieSceneSequencePlayer::PlayReverse()
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.PlayReverse");

	UMovieSceneSequencePlayer_PlayReverse_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function MovieScene.MovieSceneSequencePlayer.PlayLooping
// ()
// Parameters:
// int                            NumLoops                       (Parm, ZeroConstructor, IsPlainOldData)

void UMovieSceneSequencePlayer::PlayLooping(int NumLoops)
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.PlayLooping");

	UMovieSceneSequencePlayer_PlayLooping_Params params;
	params.NumLoops = NumLoops;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function MovieScene.MovieSceneSequencePlayer.Play
// ()

void UMovieSceneSequencePlayer::Play()
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.Play");

	UMovieSceneSequencePlayer_Play_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function MovieScene.MovieSceneSequencePlayer.Pause
// ()

void UMovieSceneSequencePlayer::Pause()
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.Pause");

	UMovieSceneSequencePlayer_Pause_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function MovieScene.MovieSceneSequencePlayer.JumpToSeconds
// ()
// Parameters:
// float                          TimeInSeconds                  (Parm, ZeroConstructor, IsPlainOldData)

void UMovieSceneSequencePlayer::JumpToSeconds(float TimeInSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.JumpToSeconds");

	UMovieSceneSequencePlayer_JumpToSeconds_Params params;
	params.TimeInSeconds = TimeInSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function MovieScene.MovieSceneSequencePlayer.JumpToPosition
// ()
// Parameters:
// float                          NewPlaybackPosition            (Parm, ZeroConstructor, IsPlainOldData)

void UMovieSceneSequencePlayer::JumpToPosition(float NewPlaybackPosition)
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.JumpToPosition");

	UMovieSceneSequencePlayer_JumpToPosition_Params params;
	params.NewPlaybackPosition = NewPlaybackPosition;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function MovieScene.MovieSceneSequencePlayer.JumpToFrame
// ()
// Parameters:
// struct FFrameTime              NewPosition                    (Parm)

void UMovieSceneSequencePlayer::JumpToFrame(const struct FFrameTime& NewPosition)
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.JumpToFrame");

	UMovieSceneSequencePlayer_JumpToFrame_Params params;
	params.NewPosition = NewPosition;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function MovieScene.MovieSceneSequencePlayer.IsReversed
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UMovieSceneSequencePlayer::IsReversed()
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.IsReversed");

	UMovieSceneSequencePlayer_IsReversed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function MovieScene.MovieSceneSequencePlayer.IsPlaying
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UMovieSceneSequencePlayer::IsPlaying()
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.IsPlaying");

	UMovieSceneSequencePlayer_IsPlaying_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function MovieScene.MovieSceneSequencePlayer.IsPaused
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UMovieSceneSequencePlayer::IsPaused()
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.IsPaused");

	UMovieSceneSequencePlayer_IsPaused_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function MovieScene.MovieSceneSequencePlayer.GoToEndAndStop
// ()

void UMovieSceneSequencePlayer::GoToEndAndStop()
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.GoToEndAndStop");

	UMovieSceneSequencePlayer_GoToEndAndStop_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function MovieScene.MovieSceneSequencePlayer.GetStartTime
// ()
// Parameters:
// struct FQualifiedFrameTime     ReturnValue                    (Parm, OutParm, ReturnParm)

struct FQualifiedFrameTime UMovieSceneSequencePlayer::GetStartTime()
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.GetStartTime");

	UMovieSceneSequencePlayer_GetStartTime_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function MovieScene.MovieSceneSequencePlayer.GetPlayRate
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UMovieSceneSequencePlayer::GetPlayRate()
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.GetPlayRate");

	UMovieSceneSequencePlayer_GetPlayRate_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function MovieScene.MovieSceneSequencePlayer.GetPlaybackStart
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UMovieSceneSequencePlayer::GetPlaybackStart()
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.GetPlaybackStart");

	UMovieSceneSequencePlayer_GetPlaybackStart_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function MovieScene.MovieSceneSequencePlayer.GetPlaybackPosition
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UMovieSceneSequencePlayer::GetPlaybackPosition()
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.GetPlaybackPosition");

	UMovieSceneSequencePlayer_GetPlaybackPosition_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function MovieScene.MovieSceneSequencePlayer.GetPlaybackEnd
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UMovieSceneSequencePlayer::GetPlaybackEnd()
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.GetPlaybackEnd");

	UMovieSceneSequencePlayer_GetPlaybackEnd_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function MovieScene.MovieSceneSequencePlayer.GetObjectBindings
// ()
// Parameters:
// class UObject*                 InObject                       (Parm, ZeroConstructor, IsPlainOldData)
// TArray<struct FMovieSceneObjectBindingID> ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm)

TArray<struct FMovieSceneObjectBindingID> UMovieSceneSequencePlayer::GetObjectBindings(class UObject* InObject)
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.GetObjectBindings");

	UMovieSceneSequencePlayer_GetObjectBindings_Params params;
	params.InObject = InObject;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function MovieScene.MovieSceneSequencePlayer.GetLength
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UMovieSceneSequencePlayer::GetLength()
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.GetLength");

	UMovieSceneSequencePlayer_GetLength_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function MovieScene.MovieSceneSequencePlayer.GetFrameRate
// ()
// Parameters:
// struct FFrameRate              ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FFrameRate UMovieSceneSequencePlayer::GetFrameRate()
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.GetFrameRate");

	UMovieSceneSequencePlayer_GetFrameRate_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function MovieScene.MovieSceneSequencePlayer.GetFrameDuration
// ()
// Parameters:
// int                            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

int UMovieSceneSequencePlayer::GetFrameDuration()
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.GetFrameDuration");

	UMovieSceneSequencePlayer_GetFrameDuration_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function MovieScene.MovieSceneSequencePlayer.GetEndTime
// ()
// Parameters:
// struct FQualifiedFrameTime     ReturnValue                    (Parm, OutParm, ReturnParm)

struct FQualifiedFrameTime UMovieSceneSequencePlayer::GetEndTime()
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.GetEndTime");

	UMovieSceneSequencePlayer_GetEndTime_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function MovieScene.MovieSceneSequencePlayer.GetDuration
// ()
// Parameters:
// struct FQualifiedFrameTime     ReturnValue                    (Parm, OutParm, ReturnParm)

struct FQualifiedFrameTime UMovieSceneSequencePlayer::GetDuration()
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.GetDuration");

	UMovieSceneSequencePlayer_GetDuration_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function MovieScene.MovieSceneSequencePlayer.GetDisableCameraCuts
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UMovieSceneSequencePlayer::GetDisableCameraCuts()
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.GetDisableCameraCuts");

	UMovieSceneSequencePlayer_GetDisableCameraCuts_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function MovieScene.MovieSceneSequencePlayer.GetCurrentTime
// ()
// Parameters:
// struct FQualifiedFrameTime     ReturnValue                    (Parm, OutParm, ReturnParm)

struct FQualifiedFrameTime UMovieSceneSequencePlayer::GetCurrentTime()
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.GetCurrentTime");

	UMovieSceneSequencePlayer_GetCurrentTime_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function MovieScene.MovieSceneSequencePlayer.GetBoundObjects
// ()
// Parameters:
// struct FMovieSceneObjectBindingID ObjectBinding                  (Parm)
// TArray<class UObject*>         ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm)

TArray<class UObject*> UMovieSceneSequencePlayer::GetBoundObjects(const struct FMovieSceneObjectBindingID& ObjectBinding)
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.GetBoundObjects");

	UMovieSceneSequencePlayer_GetBoundObjects_Params params;
	params.ObjectBinding = ObjectBinding;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function MovieScene.MovieSceneSequencePlayer.ChangePlaybackDirection
// ()

void UMovieSceneSequencePlayer::ChangePlaybackDirection()
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneSequencePlayer.ChangePlaybackDirection");

	UMovieSceneSequencePlayer_ChangePlaybackDirection_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function MovieScene.MovieSceneEasingFunction.OnEvaluate
// ()
// Parameters:
// float                          Interp                         (Parm, ZeroConstructor, IsPlainOldData)
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UMovieSceneEasingFunction::OnEvaluate(float Interp)
{
	static auto fn = UObject::FindObject<UFunction>("Function MovieScene.MovieSceneEasingFunction.OnEvaluate");

	UMovieSceneEasingFunction_OnEvaluate_Params params;
	params.Interp = Interp;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

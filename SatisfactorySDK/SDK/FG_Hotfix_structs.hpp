#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_CoreUObject_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Enums
//---------------------------------------------------------------------------

// Enum Hotfix.EHotfixResult
enum class EHotfixResult : uint8_t
{
	Failed                         = 0,
	Success                        = 1,
	SuccessNoChange                = 2,
	SuccessNeedsReload             = 3,
	SuccessNeedsRelaunch           = 4,
	EHotfixResult_MAX              = 5
};


// Enum Hotfix.EPatchCheckResult
enum class EPatchCheckResult : uint8_t
{
	NoPatchRequired                = 0,
	PatchRequired                  = 1,
	NoLoggedInUser                 = 2,
	PatchCheckFailure              = 3,
	EPatchCheckResult_MAX          = 4
};


// Enum Hotfix.EUpdateCompletionStatus
enum class EUpdateCompletionStatus : uint8_t
{
	UpdateUnknown                  = 0,
	UpdateSuccess                  = 1,
	UpdateSuccess_NoChange         = 2,
	UpdateSuccess_NeedsReload      = 3,
	UpdateSuccess_NeedsRelaunch    = 4,
	UpdateSuccess_NeedsPatch       = 5,
	UpdateFailure_PatchCheck       = 6,
	UpdateFailure_HotfixCheck      = 7,
	UpdateFailure_NotLoggedIn      = 8,
	EUpdateCompletionStatus_MAX    = 9
};


// Enum Hotfix.EUpdateState
enum class EUpdateState : uint8_t
{
	UpdateIdle                     = 0,
	UpdatePending                  = 1,
	CheckingForPatch               = 2,
	DetectingPlatformEnvironment   = 3,
	CheckingForHotfix              = 4,
	WaitingOnInitialLoad           = 5,
	InitialLoadComplete            = 6,
	UpdateComplete                 = 7,
	EUpdateState_MAX               = 8
};



}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

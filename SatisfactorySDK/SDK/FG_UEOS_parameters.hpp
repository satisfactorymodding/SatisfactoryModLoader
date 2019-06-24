#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_UEOS_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function UEOS.EOSAuthentication.Update
struct UEOSAuthentication_Update_Params
{
};

// Function UEOS.EOSAuthentication.Logout
struct UEOSAuthentication_Logout_Params
{
};

// Function UEOS.EOSAuthentication.Login
struct UEOSAuthentication_Login_Params
{
	ELoginMode                                         LoginMode;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	class FString                                      UserId;                                                   // (Parm, ZeroConstructor)
	class FString                                      UserToken;                                                // (Parm, ZeroConstructor)
};

// Function UEOS.EOSAuthentication.GetAuthorised
struct UEOSAuthentication_GetAuthorised_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function UEOS.EOSMetrics.IsValid
struct UEOSMetrics_IsValid_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function UEOS.EOSMetrics.InitMetric
struct UEOSMetrics_InitMetric_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function UEOS.EOSMetrics.EndPlayerSession
struct UEOSMetrics_EndPlayerSession_Params
{
	class FString                                      DisplayName;                                              // (Parm, ZeroConstructor)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function UEOS.EOSMetrics.BeginPlayerSession
struct UEOSMetrics_BeginPlayerSession_Params
{
	class FString                                      DisplayName;                                              // (Parm, ZeroConstructor)
	ESupportedAccountType                              TargetAccountType;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	EInputControllerType                               ControllerType;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function UEOS.EOSManager.UpdateEOS
struct UEOSManager_UpdateEOS_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function UEOS.EOSManager.ShutdownEOS
struct UEOSManager_ShutdownEOS_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function UEOS.EOSManager.IsEOSInitialized
struct UEOSManager_IsEOSInitialized_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function UEOS.EOSManager.InitEOS
struct UEOSManager_InitEOS_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function UEOS.EOSManager.GetMetrics
struct UEOSManager_GetMetrics_Params
{
	class UEOSMetrics*                                 ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function UEOS.EOSManager.GetEOSManager
struct UEOSManager_GetEOSManager_Params
{
	class UEOSManager*                                 ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function UEOS.EOSManager.GetAuthentication
struct UEOSManager_GetAuthentication_Params
{
	class UEOSAuthentication*                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function UEOS.EOSManager.Cleanup
struct UEOSManager_Cleanup_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

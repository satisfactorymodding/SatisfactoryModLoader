// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_GameAnalyticsModule_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function GameAnalyticsModule.AnalyticsService.GetPagePrefix
// ()
// Parameters:
// class FString                  ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm)

class FString UAnalyticsService::GetPagePrefix()
{
	static auto fn = UObject::FindObject<UFunction>("Function GameAnalyticsModule.AnalyticsService.GetPagePrefix");

	UAnalyticsService_GetPagePrefix_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function GameAnalyticsModule.AnalyticsService.GetBuildPrefix
// ()
// Parameters:
// class FString                  ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm)

class FString UAnalyticsService::GetBuildPrefix()
{
	static auto fn = UObject::FindObject<UFunction>("Function GameAnalyticsModule.AnalyticsService.GetBuildPrefix");

	UAnalyticsService_GetBuildPrefix_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function GameAnalyticsModule.StatHatJsonRequest.SendRequest
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UStatHatJsonRequest::SendRequest()
{
	static auto fn = UObject::FindObject<UFunction>("Function GameAnalyticsModule.StatHatJsonRequest.SendRequest");

	UStatHatJsonRequest_SendRequest_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

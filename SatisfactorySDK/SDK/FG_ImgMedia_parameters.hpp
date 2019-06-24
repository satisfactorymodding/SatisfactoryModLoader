#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_ImgMedia_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function ImgMedia.ImgMediaSource.SetSequencePath
struct UImgMediaSource_SetSequencePath_Params
{
	class FString                                      Path;                                                     // (Parm, ZeroConstructor)
};

// Function ImgMedia.ImgMediaSource.GetSequencePath
struct UImgMediaSource_GetSequencePath_Params
{
	class FString                                      ReturnValue;                                              // (ConstParm, Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function ImgMedia.ImgMediaSource.GetProxies
struct UImgMediaSource_GetProxies_Params
{
	TArray<class FString>                              OutProxies;                                               // (Parm, OutParm, ZeroConstructor)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

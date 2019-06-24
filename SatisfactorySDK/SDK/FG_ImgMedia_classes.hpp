#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_ImgMedia_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class ImgMedia.ImgMediaSource
// 0x0028 (0x0060 - 0x0038)
class UImgMediaSource : public UBaseMediaSource
{
public:
	struct FFrameRate                                  FrameRateOverride;                                        // 0x0038(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class FString                                      ProxyOverride;                                            // 0x0040(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	struct FDirectoryPath                              SequencePath;                                             // 0x0050(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class ImgMedia.ImgMediaSource");
		return ptr;
	}


	void SetSequencePath(const class FString& Path);
	class FString GetSequencePath();
	void GetProxies(TArray<class FString>* OutProxies);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

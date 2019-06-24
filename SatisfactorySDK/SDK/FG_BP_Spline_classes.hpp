#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Spline_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_Spline.BP_Spline_C
// 0x000C (0x033C - 0x0330)
class ABP_Spline_C : public AFGSplinePath
{
public:
	int                                                mIndex;                                                   // 0x0330(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               mIsYoyoing;                                               // 0x0334(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0335(0x0003) MISSED OFFSET
	int                                                mIncrementSign;                                           // 0x0338(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_Spline.BP_Spline_C");
		return ptr;
	}


	void GetNextSplineIndex(int currentIndex, int* nextIndex);
	void UserConstructionScript();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

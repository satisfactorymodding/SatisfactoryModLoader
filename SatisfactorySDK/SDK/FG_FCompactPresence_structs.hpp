#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// UserDefinedStruct FCompactPresence.FCompactPresence
// 0x0013
struct FFCompactPresence
{
	class FString                                      PresenceString_8_73B095B54A983F2391EE189D60CC1495;        // 0x0000(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	bool                                               IsOnline_3_0B4A819747012DC786FA4097038402CD;              // 0x0010(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               IsPlayingThisGame_6_D07FB68E4051EB599EEFC5B695C2B0FA;     // 0x0011(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               IsPlayingOtherGame_7_ED9DBFB84A164DABCD8A488B070BE8C3;    // 0x0012(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

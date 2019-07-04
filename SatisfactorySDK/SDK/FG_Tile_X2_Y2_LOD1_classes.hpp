#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Tile_X2_Y2_LOD1_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Tile_X2_Y2_LOD1.Tile_X2_Y2_LOD1_C
// 0x0000 (0x0330 - 0x0330)
class ATile_X2_Y2_LOD1_C : public ALevelScriptActor
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Tile_X2_Y2_LOD1.Tile_X2_Y2_LOD1_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

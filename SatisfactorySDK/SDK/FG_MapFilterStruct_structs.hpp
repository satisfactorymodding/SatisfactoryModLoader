#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_FactoryGame_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// UserDefinedStruct MapFilterStruct.MapFilterStruct
// 0x0028
struct FMapFilterStruct
{
	ERepresentationType                                RepresentationType_3_5D457985464D101149CAEF83656C9370;    // 0x0000(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0001(0x0007) MISSED OFFSET
	TArray<class UFGActorRepresentation*>              ActorRepresentation_6_2C64EC784A601AFE845DA2834D3A2212;   // 0x0008(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	TArray<class UWidget_MapObject_C*>                 MapObject_10_E7619CDE4C223F0B26B78DA3C3602333;            // 0x0018(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

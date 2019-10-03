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

// UserDefinedStruct ItemCategoryRecipeStruct.ItemCategoryRecipeStruct
// 0x0018
struct FItemCategoryRecipeStruct
{
	class UClass*                                      Category_5_48CE2A3C41089DC1E5DE39909CF17792;              // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TArray<class UClass*>                              Recipes_6_5C2C7BF54D78A483A81B2785C2CF7736;               // 0x0008(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

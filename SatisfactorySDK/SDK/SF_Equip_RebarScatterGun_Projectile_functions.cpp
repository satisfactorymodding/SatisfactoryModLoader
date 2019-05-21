// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Equip_RebarScatterGun_Projectile_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Equip_RebarScatterGun_Projectile.Equip_RebarScatterGun_Projectile_C.UserConstructionScript
// ()

void AEquip_RebarScatterGun_Projectile_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_RebarScatterGun_Projectile.Equip_RebarScatterGun_Projectile_C.UserConstructionScript");

	AEquip_RebarScatterGun_Projectile_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

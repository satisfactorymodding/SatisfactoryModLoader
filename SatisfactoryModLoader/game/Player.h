#pragma once

#include <HookLoader.h>
#include <util/FString.h>

#pragma warning (push)
#pragma warning (disable: 4667)
namespace Classes {
	class AFGCharacterBase {
	public:
		void BeginPlay();
		void GetHealthComponent(struct FFrame*, void* const);
	};
}
DEFINE_METHOD(Classes::AFGCharacterBase::BeginPlay);
// manually override name
template <>
struct HookName<&Classes::AFGCharacterBase::GetHealthComponent> {
	static constexpr const char Name[] = "AFGCharacterBase::execGetHealthComponent";
};

EXPORT_METHOD(Classes::AFGCharacterBase::GetHealthComponent);

namespace Classes {
	class AFGCharacterPlayer : public Classes::AFGCharacterBase
	{
	public:
		void BeginPlay();
		void HotKeyDismantle();
		void OnUsePressed();
		void SprintPressed();
	};
}
DEFINE_METHOD(Classes::AFGCharacterPlayer::BeginPlay);
DEFINE_METHOD(Classes::AFGCharacterPlayer::HotKeyDismantle);
DEFINE_METHOD(Classes::AFGCharacterPlayer::OnUsePressed);
DEFINE_METHOD(Classes::AFGCharacterPlayer::SprintPressed);

namespace Classes {
	class HealthComponent {
	public:
		void TakeDamage(class AActor* damagedActor, float damageAmount, class UDamageType *damageType, class AController *instigatedBy, class AActor *damageCauser);
	};
}

DEFINE_METHOD_PRE("UFG", Classes::HealthComponent::TakeDamage);

namespace Classes {
	class UFGBuildGunState {
	public:
		float GetBuildGunDelayPercentage();
	};
}

DEFINE_METHOD(Classes::UFGBuildGunState::GetBuildGunDelayPercentage);

namespace Classes {
	class AFGBuildGun {
	public:
		void  OnNoSnapModePressed();
		void  OnPrimaryFirePressed();
		void  OnScrollDownPressed();
		void  OnScrollModePressed();
		void  OnSnapToGuideLinesPressed();
	};
}

DEFINE_METHOD(Classes::AFGBuildGun::OnNoSnapModePressed);
DEFINE_METHOD(Classes::AFGBuildGun::OnPrimaryFirePressed);
DEFINE_METHOD(Classes::AFGBuildGun::OnScrollDownPressed);
DEFINE_METHOD(Classes::AFGBuildGun::OnScrollModePressed);
DEFINE_METHOD(Classes::AFGBuildGun::OnSnapToGuideLinesPressed);

namespace Classes {
	class AFGC4Dispenser {
	public:
		void  OnDetonatePressed();
		void  OnPrimaryFirePressed();
	};
}

DEFINE_METHOD(Classes::AFGC4Dispenser::OnDetonatePressed);
DEFINE_METHOD(Classes::AFGC4Dispenser::OnPrimaryFirePressed);

namespace Classes {
	class AFGChainsaw {
	public:
		void  OnPrimaryFirePressed();
	};
}

DEFINE_METHOD(Classes::AFGChainsaw::OnPrimaryFirePressed);

namespace Classes {
	class AFGColorGun {
	public:
		void  OnSecondaryFirePressed();
	};
}

DEFINE_METHOD(Classes::AFGColorGun::OnSecondaryFirePressed);

namespace Classes {
	class AFGConsumableEquipment {
	public:
		void  OnPrimaryFirePressed();
	};
}

DEFINE_METHOD(Classes::AFGConsumableEquipment::OnPrimaryFirePressed);

namespace Classes {
	class AFGEquipmentStunSpear {
	public:
		void  OnFirePressed();
	};
}

DEFINE_METHOD(Classes::AFGEquipmentStunSpear::OnFirePressed);

namespace Classes {
	class AFGHookshot {
	public:
		void  OnPrimaryFirePressed();
		void  OnSecondaryFirePressed();
	};
}

DEFINE_METHOD(Classes::AFGHookshot::OnPrimaryFirePressed);
DEFINE_METHOD(Classes::AFGHookshot::OnSecondaryFirePressed);

namespace Classes {
	class AFGPortableMinerDispenser {
	public:
		void  OnPrimaryFirePressed();
	};
}

DEFINE_METHOD(Classes::AFGPortableMinerDispenser::OnPrimaryFirePressed);

namespace Classes {
	class AFGResourceScanner {
	public:
		void  OnScanPressed();
	};
}

DEFINE_METHOD(Classes::AFGResourceScanner::OnScanPressed);

namespace Classes {
	class AFGWeapon {
	public:
		void  OnPrimaryFirePressed();
		void  OnReloadPressed();
	};
}

DEFINE_METHOD(Classes::AFGWeapon::OnPrimaryFirePressed);
DEFINE_METHOD(Classes::AFGWeapon::OnReloadPressed);

namespace Classes {
	class UFGBuildGunStateDismantle {
	public:
		void  BeginBuildGunDelay();
		void  ResetBuildGunDelay();
	};
}

DEFINE_METHOD(Classes::UFGBuildGunStateDismantle::BeginBuildGunDelay);
DEFINE_METHOD(Classes::UFGBuildGunStateDismantle::ResetBuildGunDelay);

#pragma warning (pop)

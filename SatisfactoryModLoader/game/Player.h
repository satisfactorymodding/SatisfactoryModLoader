#pragma once

#include <HookLoader.h>
#include <util/FString.h>

#pragma warning (push)
#pragma warning (disable: 4667)

namespace SML {
	namespace Objects {
		class AFGCharacterBase {
		public:
			void BeginPlay();
			void GetHealthComponent(struct FFrame*, void* const);
			void RagdollCharacter(bool ragdollState);
		};

		DEFINE_METHOD(AFGCharacterBase::RagdollCharacter);
		DEFINE_METHOD(AFGCharacterBase::BeginPlay);
		EXPORT_METHOD(AFGCharacterBase::GetHealthComponent);

		// manually override name
		template <>
		struct HookName<&AFGCharacterBase::GetHealthComponent> {
			static constexpr const char Name[] = "AFGCharacterBase::execGetHealthComponent";
		};

		class AFGCharacterPlayer : public AFGCharacterBase
		{
		public:
			void BeginPlay();
			void HotKeyDismantle();
			void OnUsePressed();
			void SprintPressed();
		};

		DEFINE_METHOD(AFGCharacterPlayer::BeginPlay);
		DEFINE_METHOD(AFGCharacterPlayer::HotKeyDismantle);
		DEFINE_METHOD(AFGCharacterPlayer::OnUsePressed);
		DEFINE_METHOD(AFGCharacterPlayer::SprintPressed);

		class HealthComponent {
		public:
			void TakeDamage(class AActor* damagedActor, float damageAmount, class UDamageType *damageType, class AController *instigatedBy, class AActor *damageCauser);
		};

		DEFINE_METHOD_PRE("UFG", HealthComponent::TakeDamage);

		class UFGBuildGunState {
		public:
			float GetBuildGunDelayPercentage();
		};

		DEFINE_METHOD(UFGBuildGunState::GetBuildGunDelayPercentage);

		class AFGBuildGun {
		public:
			void  OnNoSnapModePressed();
			void  OnPrimaryFirePressed();
			void  OnScrollDownPressed();
			void  OnScrollModePressed();
			void  OnSnapToGuideLinesPressed();
		};

		DEFINE_METHOD(AFGBuildGun::OnNoSnapModePressed);
		DEFINE_METHOD(AFGBuildGun::OnPrimaryFirePressed);
		DEFINE_METHOD(AFGBuildGun::OnScrollDownPressed);
		DEFINE_METHOD(AFGBuildGun::OnScrollModePressed);
		DEFINE_METHOD(AFGBuildGun::OnSnapToGuideLinesPressed);

		class AFGC4Dispenser {
		public:
			void  OnDetonatePressed();
			void  OnPrimaryFirePressed();
		};

		DEFINE_METHOD(AFGC4Dispenser::OnDetonatePressed);
		DEFINE_METHOD(AFGC4Dispenser::OnPrimaryFirePressed);

		class AFGChainsaw {
		public:
			void  OnPrimaryFirePressed();
		};

		DEFINE_METHOD(AFGChainsaw::OnPrimaryFirePressed);

		class AFGColorGun {
		public:
			void  OnSecondaryFirePressed();
		};

		DEFINE_METHOD(AFGColorGun::OnSecondaryFirePressed);


		class AFGConsumableEquipment {
		public:
			void  OnPrimaryFirePressed();
		};

		DEFINE_METHOD(AFGConsumableEquipment::OnPrimaryFirePressed);


		class AFGEquipmentStunSpear {
		public:
			void  OnFirePressed();
		};

		DEFINE_METHOD(AFGEquipmentStunSpear::OnFirePressed);

		class AFGHookshot {
		public:
			void  OnPrimaryFirePressed();
			void  OnSecondaryFirePressed();
		};

		DEFINE_METHOD(AFGHookshot::OnPrimaryFirePressed);
		DEFINE_METHOD(AFGHookshot::OnSecondaryFirePressed);

		class AFGPortableMinerDispenser {
		public:
			void  OnPrimaryFirePressed();
		};


		DEFINE_METHOD(AFGPortableMinerDispenser::OnPrimaryFirePressed);

		class AFGResourceScanner {
		public:
			void  OnScanPressed();
		};

		DEFINE_METHOD(AFGResourceScanner::OnScanPressed);

		class AFGWeapon {
		public:
			void  OnPrimaryFirePressed();
			void  OnReloadPressed();
		};

		DEFINE_METHOD(AFGWeapon::OnPrimaryFirePressed);
		DEFINE_METHOD(AFGWeapon::OnReloadPressed);

		class UFGBuildGunStateDismantle {
		public:
			void  BeginBuildGunDelay();
			void  ResetBuildGunDelay();
		};

		DEFINE_METHOD(UFGBuildGunStateDismantle::BeginBuildGunDelay);
		DEFINE_METHOD(UFGBuildGunStateDismantle::ResetBuildGunDelay);
	}
}

#pragma warning (pop)
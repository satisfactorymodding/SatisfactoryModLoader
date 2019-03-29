#pragma once
#include <string>
#include <vector>

enum EventType {
	PlayerSuicide,
	PlayerTookDamage,
	PlayerControllerBeginPlay,
	PlayerBeginPlay,
	PlayerSentMessage,
	PlayerStunSpearKey,
	PlayerScanKey,
	PlayerUseKey,
	PlayerSprintKey,
	PlayerColorGunSecondaryKey,
	PlayerAttentionPingKey,
	PlayerC4DetonateDispenserKey,
	PlayerC4PrimaryKey,
	PlayerBuildGunPrimaryKey,
	PlayerChainsawPrimaryKey,
	PlayerConsumablePrimaryKey,
	PlayerBuildGunScrollDownKey,
	PlayerBuildGunSnapToGuideKey,
	PlayerBuildGunNoSnapModKey,
	PlayerBuildGunScrollModeKey,
	PlayerHookshotPrimaryKey,
	PlayerHookshotSecondaryKey,
	PlayerHookshotEquip,
	PlayerPortableMinerDispenserKey,
	PlayerWeaponReloadKey,
	PlayerWeaponPrimaryKey,
	UButtonPressed,
	UButtonSlateHandlePressed,
	UCheckBoxPressed,
	UAkCheckBoxPressed,
	SButtonPressed,
	GameInstanceRecieveInit,
	GameInstanceGetWorld,
	GameGetPlayer,
	LoadItemDescriptor,
	END
};

class Event {
public:
	virtual ~Event();

	virtual EventType type() const = 0;
	virtual const char* name() const = 0;
};

typedef std::vector<void*>(WINAPI* ModFunc)(const Event&, std::vector<void*>&);
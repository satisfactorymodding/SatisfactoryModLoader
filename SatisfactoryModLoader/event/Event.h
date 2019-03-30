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
	GameInstanceGetWorld,
	GameGetPlayer,
	ItemDescriptorConstructor,
	InputKey,
	InventoryRegister,
	InventorySort,
	END
};

#define KEY_ZERO 0x30
#define KEY_ONE 0x31
#define KEY_TWO 0x32
#define KEY_THREE 0x33
#define KEY_FOUR 0x34
#define KEY_FIVE 0x35
#define KEY_SIX 0x36
#define KEY_SEVEN 0x37
#define KEY_EIGHT 0x38
#define KEY_NINE 0x39

#define KEY_A 0x41
#define KEY_B 0x42
#define KEY_C 0x43
#define KEY_D 0x44
#define KEY_E 0x45
#define KEY_F 0x46
#define KEY_G 0x47
#define KEY_H 0x48
#define KEY_I 0x49
#define KEY_J 0x4A
#define KEY_K 0x4B
#define KEY_L 0x4C
#define KEY_M 0x4D
#define KEY_N 0x4E
#define KEY_O 0x4F
#define KEY_P 0x50
#define KEY_Q 0x51
#define KEY_R 0x52
#define KEY_S 0x53
#define KEY_T 0x54
#define KEY_U 0x55
#define KEY_V 0x56
#define KEY_W 0x57
#define KEY_X 0x58
#define KEY_Y 0x59
#define KEY_Z 0x5A
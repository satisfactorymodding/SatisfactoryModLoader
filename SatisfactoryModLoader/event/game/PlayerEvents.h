#pragma once
#include <Windows.h>
#include <detours.h>
#include <event/FunctionHolder.h>
#include <util/Reflection.h>
#include <util/Utility.h>
#include <util/FString.h>

// other extern events
GLOBAL void player_send_message(void* player, std::string message) {
	FString msg = message.c_str();

	auto pointer = (void(WINAPI*)(void*, FString*))hookedFunctions[EventType::PlayerSentMessage];
	pointer(player, &msg);
}

// mod loader events

// ; void __fastcall AFGPlayerController::BeginPlay(AFGPlayerController *this)
void player_controller_begin_play(void* controller) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerControllerBeginPlay];
	localPlayerController = controller;
	auto args = std::vector<void*>{
		controller
	};
	run_mods(modList, EventType::PlayerControllerBeginPlay, args);
	pointer(controller);
}

// ; void __fastcall AFGCharacterPlayer::BeginPlay(AFGCharacterPlayer *this)
void player_begin_play(void* player) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerBeginPlay];
	auto args = std::vector<void*>{
		player
	};
	run_mods(modList, EventType::PlayerBeginPlay, args);
	playerInstance = player;
	pointer(player);
}

//; void __fastcall AFGPlayerController::Suicide(AFGPlayerController *this)
GLOBAL void player_suicide(void* player) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerSuicide];
	auto args = std::vector<void*>{
		player
	};
	run_mods(modList, EventType::PlayerSuicide, args);
	pointer(player);
}


// ; void __fastcall AFGPlayerController::EnterChatMessage(AFGPlayerController *this, FString *inMessage)
void player_sent_message(void* player, FString* message) { //TODO: Fix this to not be redundant
	auto pointer = (void(WINAPI*)(void*, FString*))hookedFunctions[EventType::PlayerSentMessage];
	bool useMessage = true;

	char* chars = new char[message->length];

	for (size_t i = 0; i < message->length; i++) {
		chars[i] = message->data[i];
	}

	std::string str(chars);

	auto args = std::vector<void*>{
		&useMessage, &str
	};

	run_mods(modList, EventType::PlayerSentMessage, args);
	if (!useMessage) { 
		return; 
	}

	pointer(player, message);
}

// ; void __fastcall AFGWeapon::OnReloadPressed(AFGWeapon *this)
void player_reload_key_pressed(void* weapon) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerWeaponReloadKey];
	auto args = std::vector<void*> {
		weapon
	};
	run_mods(modList, EventType::PlayerWeaponReloadKey, args);
	pointer(weapon);
}

// ; void __fastcall AFGWeapon::OnPrimaryFirePressed(AFGWeapon *this)
void player_weapon_primary_key(void* weapon) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerWeaponPrimaryKey];
	auto args = std::vector<void*>{
		weapon
	};
	run_mods(modList, EventType::PlayerBuildGunPrimaryKey, args);
	pointer(weapon);
}

// ; void __fastcall AFGEquipmentStunSpear::OnFirePressed(AFGEquipmentStunSpear *this)
void player_stun_spear_key(void* spear) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerStunSpearKey];
	auto args = std::vector<void*>{
		spear
	};
	run_mods(modList, EventType::PlayerStunSpearKey, args);
	pointer(spear);
}

// ; void __fastcall AFGResourceScanner::OnScanPressed(AFGResourceScanner *this)
void player_scan_key(void* scanner) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerScanKey];
	auto args = std::vector<void*>{
		scanner
	};
	run_mods(modList, EventType::PlayerScanKey, args);
	pointer(scanner);
}

// ; void __fastcall AFGCharacterPlayer::OnUsePressed(AFGCharacterPlayer *this)
void player_use_key(void* player) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerUseKey];
	auto args = std::vector<void*>{
		player
	};
	run_mods(modList, EventType::PlayerUseKey, args);
	pointer(player);
}

// ; void __fastcall AFGCharacterPlayer::SprintPressed(AFGCharacterPlayer *this)
void player_sprint_key(void* player) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerSprintKey];
	auto args = std::vector<void*>{
		player
	};
	run_mods(modList, EventType::PlayerSprintKey, args);
	pointer(player);
}

// ; void __fastcall AFGColorGun::OnSecondaryFirePressed(AFGColorGun *this)
void player_color_gun_secondary_key(void* colorGun) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerColorGunSecondaryKey];
	auto args = std::vector<void*>{
		colorGun
	};
	run_mods(modList, EventType::PlayerColorGunSecondaryKey, args);
	pointer(colorGun);
}

// ; void __fastcall AFGPlayerController::OnAttentionPingPressed(AFGPlayerController *this)
void player_attention_ping_key(void* player) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerAttentionPingKey];
	auto args = std::vector<void*>{
		player
	};
	run_mods(modList, EventType::PlayerAttentionPingKey, args);
	pointer(player);
}

// ; void __fastcall AFGC4Dispenser::OnDetonatePressed(AFGC4Dispenser *this)
void player_c4_detonator_key(void* dispenser) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerC4DetonateDispenserKey];
	auto args = std::vector<void*>{
		dispenser
	};
	run_mods(modList, EventType::PlayerC4DetonateDispenserKey, args);
	pointer(dispenser);
}

// ; void __fastcall AFGC4Dispenser::OnPrimaryFirePressed(AFGC4Dispenser *this)
void player_c4_detonator_primary_key(void* dispenser) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerC4PrimaryKey];
	auto args = std::vector<void*>{
		dispenser
	};
	run_mods(modList, EventType::PlayerC4PrimaryKey, args);
	pointer(dispenser);
}

// ; void __fastcall AFGBuildGun::OnPrimaryFirePressed(AFGBuildGun *this)
void player_build_gun_primary_key(void* buildGun) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerBuildGunPrimaryKey];
	auto args = std::vector<void*>{
		buildGun
	};
	run_mods(modList, EventType::PlayerBuildGunPrimaryKey, args);
	pointer(buildGun);
}

// ; void __fastcall AFGChainsaw::OnPrimaryFirePressed(AFGChainsaw *this)
void player_chainsaw_primary_key(void* chainsaw) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerChainsawPrimaryKey];
	auto args = std::vector<void*>{
		chainsaw
	};
	run_mods(modList, EventType::PlayerChainsawPrimaryKey, args);
	pointer(chainsaw);
}

// ; void __fastcall AFGConsumableEquipment::OnPrimaryFirePressed(AFGConsumableEquipment *this)
void player_consumable_primary_key(void* consumable) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerConsumablePrimaryKey];
	auto args = std::vector<void*>{
		consumable
	};
	run_mods(modList, EventType::PlayerConsumablePrimaryKey, args);
	pointer(consumable);
}

// ; void __fastcall AFGBuildGun::OnScrollDownPressed(AFGBuildGun *this)
void player_build_gun_scroll_down_key(void* buildGun) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerBuildGunScrollDownKey];
	auto args = std::vector<void*>{
		buildGun
	};
	run_mods(modList, EventType::PlayerBuildGunScrollDownKey, args);
	pointer(buildGun);
}

// ; void __fastcall AFGBuildGun::OnSnapToGuideLinesPressed(AFGBuildGun *this)
void player_build_gun_snap_to_guide_key(void* buildGun) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerBuildGunSnapToGuideKey];
	auto args = std::vector<void*>{
		buildGun
	};
	run_mods(modList, EventType::PlayerBuildGunSnapToGuideKey, args);
	pointer(buildGun);
}

// ; void __fastcall AFGBuildGun::OnNoSnapModePressed(AFGBuildGun *this)
void player_build_gun_no_snap_mode_key(void* buildGun) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerBuildGunNoSnapModKey];
	auto args = std::vector<void*>{
		buildGun
	};
	run_mods(modList, EventType::PlayerBuildGunNoSnapModKey, args);
	pointer(buildGun);
}

// ; void __fastcall AFGBuildGun::OnScrollModePressed(AFGBuildGun *this)
void player_build_gun_scroll_mode_key(void* buildGun) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerBuildGunScrollModeKey];
	auto args = std::vector<void*>{
		buildGun
	};
	run_mods(modList, EventType::PlayerBuildGunScrollModeKey, args);
	pointer(buildGun);
}

// ; void __fastcall AFGHookshot::OnPrimaryFirePressed(AFGHookshot *this)
void player_hookshot_primary_key(void* hookshot) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerHookshotPrimaryKey];
	auto args = std::vector<void*>{
		hookshot
	};
	run_mods(modList, EventType::PlayerHookshotPrimaryKey, args);
	pointer(hookshot);
}

// ; void __fastcall AFGHookshot::OnSecondaryFirePressed(AFGHookshot *this)
void player_hookshot_secondary_key(void* hookshot) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerHookshotSecondaryKey];
	auto args = std::vector<void*>{
		hookshot
	};
	run_mods(modList, EventType::PlayerHookshotSecondaryKey, args);
	pointer(hookshot);
}

// ; void __fastcall AFGPortableMinerDispenser::OnPrimaryFirePressed(AFGPortableMinerDispenser *this)
void player_portable_miner_dispenser_primary_key(void* miner) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerPortableMinerDispenserKey];
	auto args = std::vector<void*>{
		miner
	};
	run_mods(modList, EventType::PlayerPortableMinerDispenserKey, args);
	pointer(miner);
}
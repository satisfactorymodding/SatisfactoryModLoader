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
	playerInstance = player;
	pointer(player);
}

//; void __fastcall AFGPlayerController::Suicide(AFGPlayerController *this)
GLOBAL void player_suicide(void* player) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerSuicide];
	pointer(player);
}


// ; void __fastcall AFGPlayerController::EnterChatMessage(AFGPlayerController *this, FString *inMessage)
void player_sent_message(void* player, FString* message) {
	auto pointer = (void(WINAPI*)(void*, FString*))hookedFunctions[EventType::PlayerSentMessage];
	bool useMessage = true;
	auto args = std::vector<void*>{
		&useMessage
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
	pointer(weapon);
}

// ; void __fastcall AFGWeapon::OnPrimaryFirePressed(AFGWeapon *this)
void player_weapon_primary_key(void* weapon) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerWeaponPrimaryKey];
	pointer(weapon);
}

// ; void __fastcall AFGEquipmentStunSpear::OnFirePressed(AFGEquipmentStunSpear *this)
void player_stun_spear_key(void* spear) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerStunSpearKey];
	pointer(spear);
}

// ; void __fastcall AFGResourceScanner::OnScanPressed(AFGResourceScanner *this)
void player_scan_key(void* scanner) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerScanKey];
	pointer(scanner);
}

// ; void __fastcall AFGCharacterPlayer::OnUsePressed(AFGCharacterPlayer *this)
void player_use_key(void* player) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerUseKey];
	pointer(player);
}

// ; void __fastcall AFGCharacterPlayer::SprintPressed(AFGCharacterPlayer *this)
void player_sprint_key(void* player) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerSprintKey];
	pointer(player);
}

// ; void __fastcall AFGColorGun::OnSecondaryFirePressed(AFGColorGun *this)
void player_color_gun_secondary_key(void* colorGun) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerColorGunSecondaryKey];
	pointer(colorGun);
}

// ; void __fastcall AFGPlayerController::OnAttentionPingPressed(AFGPlayerController *this)
void player_attention_ping_key(void* player) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerAttentionPingKey];
	pointer(player);
}

// ; void __fastcall AFGC4Dispenser::OnDetonatePressed(AFGC4Dispenser *this)
void player_c4_detonator_key(void* dispenser) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerC4DetonateDispenserKey];
	pointer(dispenser);
}

// ; void __fastcall AFGC4Dispenser::OnPrimaryFirePressed(AFGC4Dispenser *this)
void player_c4_detonator_primary_key(void* dispenser) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerC4PrimaryKey];
	pointer(dispenser);
}

// ; void __fastcall AFGBuildGun::OnPrimaryFirePressed(AFGBuildGun *this)
void player_build_gun_primary_key(void* buildGun) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerBuildGunPrimaryKey];
	pointer(buildGun);
}

// ; void __fastcall AFGChainsaw::OnPrimaryFirePressed(AFGChainsaw *this)
void player_chainsaw_primary_key(void* chainsaw) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerChainsawPrimaryKey];
	pointer(chainsaw);
}

// ; void __fastcall AFGConsumableEquipment::OnPrimaryFirePressed(AFGConsumableEquipment *this)
void player_consumable_primary_key(void* consumable) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerConsumablePrimaryKey];
	pointer(consumable);
}

// ; void __fastcall AFGBuildGun::OnScrollDownPressed(AFGBuildGun *this)
void player_build_gun_scroll_down_key(void* buildGun) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerBuildGunScrollDownKey];
	pointer(buildGun);
}

// ; void __fastcall AFGBuildGun::OnSnapToGuideLinesPressed(AFGBuildGun *this)
void player_build_gun_snap_to_guide_key(void* buildGun) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerBuildGunSnapToGuideKey];
	pointer(buildGun);
}

// ; void __fastcall AFGBuildGun::OnNoSnapModePressed(AFGBuildGun *this)
void player_build_gun_no_snap_mode_key(void* buildGun) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerBuildGunNoSnapModKey];
	pointer(buildGun);
}

// ; void __fastcall AFGBuildGun::OnScrollModePressed(AFGBuildGun *this)
void player_build_gun_scroll_mode_key(void* buildGun) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerBuildGunScrollModeKey];
	pointer(buildGun);
}

// ; void __fastcall AFGHookshot::OnPrimaryFirePressed(AFGHookshot *this)
void player_hookshot_primary_key(void* hookshot) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerHookshotPrimaryKey];
	pointer(hookshot);
}

// ; void __fastcall AFGHookshot::OnSecondaryFirePressed(AFGHookshot *this)
void player_hookshot_secondary_key(void* hookshot) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerHookshotSecondaryKey];
	pointer(hookshot);
}

// ; void __fastcall AFGPortableMinerDispenser::OnPrimaryFirePressed(AFGPortableMinerDispenser *this)
void player_portable_miner_dispenser_primary_key(void* hookshot) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerPortableMinerDispenserKey];
	pointer(hookshot);
}
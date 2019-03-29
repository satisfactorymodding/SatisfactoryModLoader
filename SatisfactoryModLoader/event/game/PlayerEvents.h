#pragma once
#include <Windows.h>
#include <detours.h>
#include <event/FunctionHolder.h>
#include <util/Reflection.h>
#include <util/Utility.h>
#include <util/FString.h>

// ; void __fastcall UFGItemDescriptor::UFGItemDescriptor(UFGItemDescriptor *this)
EXTERN_DLL_EXPORT void load_item_descriptor(void* itemDescriptor) {
	//log(LogType::Warning, "Item Constructor(", itemDescriptor->mDisplayName.TextData, ")");
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::LoadItemDescriptor];
	pointer(itemDescriptor);
}

// ; void __fastcall AFGPlayerController::BeginPlay(AFGPlayerController *this)
EXTERN_DLL_EXPORT void player_controller_begin_play(void* controller) {
	log(LogType::Normal, __FUNCSIG__);
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerControllerBeginPlay];
	localPlayerController = controller;
	auto args = std::vector<void*>{
		controller
	};
	get_mod_values(modList, "player_controller_begin_play_event", args);
	pointer(controller);
}

// ; void __fastcall AFGCharacterPlayer::BeginPlay(AFGCharacterPlayer *this)
EXTERN_DLL_EXPORT void player_begin_play(void* player) {
	log(LogType::Normal, __FUNCSIG__);
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerBeginPlay];
	playerInstance = player;
	pointer(player);
}

//; void __fastcall AFGPlayerController::Suicide(AFGPlayerController *this)
EXTERN_DLL_EXPORT void player_suicide(void* player) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerSuicide];
	pointer(player);
}

static void create_message(FString* data, const char* message) {
	data->length = strlen(message) + 1;
	int16_t *chars = new int16_t[data->length + 1];
	for (size_t i = 0; i < data->length; i++) {
		chars[i] = message[i];
	}
	chars[data->length] = '\0';
	data->data = chars;
}

// ; void __fastcall AFGPlayerController::EnterChatMessage(AFGPlayerController *this, FString *inMessage)
EXTERN_DLL_EXPORT void player_sent_message(void* player, FString* message) {
	auto pointer = (void(WINAPI*)(void*, FString*))hookedFunctions[EventType::PlayerSentMessage];
	FString msg;
	create_message(&msg, "Testing");
	pointer(player, &msg);
}

// ; void __fastcall AFGWeapon::OnReloadPressed(AFGWeapon *this)
EXTERN_DLL_EXPORT void player_reload_key_pressed(void* weapon) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerWeaponReloadKey];
	pointer(weapon);
}

// ; void __fastcall AFGWeapon::OnPrimaryFirePressed(AFGWeapon *this)
EXTERN_DLL_EXPORT void player_weapon_primary_key(void* weapon) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerWeaponPrimaryKey];
	pointer(weapon);
}

// ; void __fastcall AFGEquipmentStunSpear::OnFirePressed(AFGEquipmentStunSpear *this)
EXTERN_DLL_EXPORT void player_stun_spear_key(void* spear) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerStunSpearKey];
	pointer(spear);
}

// ; void __fastcall AFGResourceScanner::OnScanPressed(AFGResourceScanner *this)
EXTERN_DLL_EXPORT void player_scan_key(void* scanner) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerScanKey];
	pointer(scanner);
}

// ; void __fastcall AFGCharacterPlayer::OnUsePressed(AFGCharacterPlayer *this)
EXTERN_DLL_EXPORT void player_use_key(void* player) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerUseKey];
	pointer(player);
}

// ; void __fastcall AFGCharacterPlayer::SprintPressed(AFGCharacterPlayer *this)
EXTERN_DLL_EXPORT void player_sprint_key(void* player) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerSprintKey];
	pointer(player);
}

// ; void __fastcall AFGColorGun::OnSecondaryFirePressed(AFGColorGun *this)
EXTERN_DLL_EXPORT void player_color_gun_secondary_key(void* colorGun) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerColorGunSecondaryKey];
	pointer(colorGun);
}

// ; void __fastcall AFGPlayerController::OnAttentionPingPressed(AFGPlayerController *this)
EXTERN_DLL_EXPORT void player_attention_ping_key(void* player) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerAttentionPingKey];
	pointer(player);
}

// ; void __fastcall AFGC4Dispenser::OnDetonatePressed(AFGC4Dispenser *this)
EXTERN_DLL_EXPORT void player_c4_detonator_key(void* dispenser) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerC4DetonateDispenserKey];
	pointer(dispenser);
}

// ; void __fastcall AFGC4Dispenser::OnPrimaryFirePressed(AFGC4Dispenser *this)
EXTERN_DLL_EXPORT void player_c4_detonator_primary_key(void* dispenser) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerC4PrimaryKey];
	pointer(dispenser);
}

// ; void __fastcall AFGBuildGun::OnPrimaryFirePressed(AFGBuildGun *this)
EXTERN_DLL_EXPORT void player_build_gun_primary_key(void* buildGun) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerBuildGunPrimaryKey];
	pointer(buildGun);
}

// ; void __fastcall AFGChainsaw::OnPrimaryFirePressed(AFGChainsaw *this)
EXTERN_DLL_EXPORT void player_chainsaw_primary_key(void* chainsaw) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerChainsawPrimaryKey];
	pointer(chainsaw);
}

// ; void __fastcall AFGConsumableEquipment::OnPrimaryFirePressed(AFGConsumableEquipment *this)
EXTERN_DLL_EXPORT void player_consumable_primary_key(void* consumable) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerConsumablePrimaryKey];
	pointer(consumable);
}

// ; void __fastcall AFGBuildGun::OnScrollDownPressed(AFGBuildGun *this)
EXTERN_DLL_EXPORT void player_build_gun_scroll_down_key(void* buildGun) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerBuildGunScrollDownKey];
	pointer(buildGun);
}

// ; void __fastcall AFGBuildGun::OnSnapToGuideLinesPressed(AFGBuildGun *this)
EXTERN_DLL_EXPORT void player_build_gun_snap_to_guide_key(void* buildGun) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerBuildGunSnapToGuideKey];
	pointer(buildGun);
}

// ; void __fastcall AFGBuildGun::OnNoSnapModePressed(AFGBuildGun *this)
EXTERN_DLL_EXPORT void player_build_gun_no_snap_mode_key(void* buildGun) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerBuildGunNoSnapModKey];
	pointer(buildGun);
}

// ; void __fastcall AFGBuildGun::OnScrollModePressed(AFGBuildGun *this)
EXTERN_DLL_EXPORT void player_build_gun_scroll_mode_key(void* buildGun) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerBuildGunScrollModeKey];
	pointer(buildGun);
}

// ; void __fastcall AFGHookshot::OnPrimaryFirePressed(AFGHookshot *this)
EXTERN_DLL_EXPORT void player_hookshot_primary_key(void* hookshot) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerHookshotPrimaryKey];
	pointer(hookshot);
}

// ; void __fastcall AFGHookshot::OnSecondaryFirePressed(AFGHookshot *this)
EXTERN_DLL_EXPORT void player_hookshot_secondary_key(void* hookshot) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerHookshotSecondaryKey];
	pointer(hookshot);
}

// ; void __fastcall AFGPortableMinerDispenser::OnPrimaryFirePressed(AFGPortableMinerDispenser *this)
EXTERN_DLL_EXPORT void player_portable_miner_dispenser_primary_key(void* hookshot) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerPortableMinerDispenserKey];
	pointer(hookshot);
}
#include <stdafx.h>
#include <detours.h>
#include <util/Utility.h>
#include <event/game/PlayerEvents.h>
#include <event/game/EtcEvents.h>
#include <event/game/GlobalEvents.h>
#include <event/game/UiEvents.h>
#include "EventLoader.h";
#include "FunctionHolder.h"

EventLoader::EventLoader(std::vector<Mod> mods) {
	modList = mods;
}

void EventLoader::hook_events() {
	// player events
	hook_event(player_controller_begin_play, EventType::PlayerControllerBeginPlay, "AFGPlayerController::BeginPlay");
	hook_event(player_begin_play, EventType::PlayerBeginPlay, "AFGCharacterPlayer::BeginPlay");
	hook_event(player_suicide, EventType::PlayerSuicide, "AFGPlayerController::Suicide");
	hook_event(player_sent_message, EventType::PlayerSentMessage, "AFGPlayerController::EnterChatMessage");
	hook_event(player_reload_key_pressed, EventType::PlayerWeaponReloadKey, "AFGWeapon::OnReloadPressed");
	hook_event(player_weapon_primary_key, EventType::PlayerWeaponPrimaryKey, "AFGWeapon::OnPrimaryFirePressed");
	hook_event(player_stun_spear_key, EventType::PlayerStunSpearKey, "AFGEquipmentStunSpear::OnFirePressed");
	hook_event(player_scan_key, EventType::PlayerScanKey, "AFGResourceScanner::OnScanPressed");
	hook_event(player_use_key, EventType::PlayerUseKey, "AFGCharacterPlayer::OnUsePressed");
	hook_event(player_sprint_key, EventType::PlayerSprintKey, "AFGCharacterPlayer::SprintPressed");
	hook_event(player_color_gun_secondary_key, EventType::PlayerColorGunSecondaryKey, "AFGColorGun::OnSecondaryFirePressed");
	hook_event(player_attention_ping_key, EventType::PlayerAttentionPingKey, "AFGPlayerController::OnAttentionPingPressed");
	hook_event(player_c4_detonator_key, EventType::PlayerC4DetonateDispenserKey, "AFGC4Dispenser::OnDetonatePressed");
	hook_event(player_c4_detonator_primary_key, EventType::PlayerC4PrimaryKey, "AFGC4Dispenser::OnPrimaryFirePressed");
	hook_event(player_build_gun_primary_key, EventType::PlayerBuildGunPrimaryKey, "AFGBuildGun::OnPrimaryFirePressed");
	hook_event(player_chainsaw_primary_key, EventType::PlayerChainsawPrimaryKey, "AFGChainsaw::OnPrimaryFirePressed");
	hook_event(player_consumable_primary_key, EventType::PlayerConsumablePrimaryKey, "AFGConsumableEquipment::OnPrimaryFirePressed");
	hook_event(player_build_gun_scroll_down_key, EventType::PlayerBuildGunScrollDownKey, "AFGBuildGun::OnScrollDownPressed");
	hook_event(player_build_gun_snap_to_guide_key, EventType::PlayerBuildGunSnapToGuideKey, "AFGBuildGun::OnSnapToGuideLinesPressed");
	hook_event(player_build_gun_no_snap_mode_key, EventType::PlayerBuildGunNoSnapModKey, "AFGBuildGun::OnNoSnapModePressed");
	hook_event(player_build_gun_scroll_mode_key, EventType::PlayerBuildGunScrollModeKey, "AFGBuildGun::OnScrollModePressed");
	hook_event(player_hookshot_primary_key, EventType::PlayerHookshotPrimaryKey, "AFGHookshot::OnPrimaryFirePressed");
	hook_event(player_hookshot_secondary_key, EventType::PlayerHookshotSecondaryKey, "AFGHookshot::OnSecondaryFirePressed");
	hook_event(player_portable_miner_dispenser_primary_key, EventType::PlayerPortableMinerDispenserKey, "AFGPortableMinerDispenser::OnPrimaryFirePressed");
	// ui events
	hook_event(u_button_pressed, EventType::UButtonPressed, "UButton::IsPressed");
	hook_event(u_check_box_pressed, EventType::UCheckBoxPressed, "UCheckBox::IsPressed");
	hook_event(u_button_slate_handle_pressed, EventType::UButtonSlateHandlePressed, "UButton::SlateHandlePressed");
	hook_event(s_button_pressed, EventType::SButtonPressed, "SButton::IsPressed");
	hook_event(uak_check_box_pressed, EventType::UAkCheckBoxPressed, "UAkCheckBox::IsPressed");
	// global events
	hook_event(game_instance_get_world, EventType::GameInstanceGetWorld, "UGameInstance::GetWorld");
	// etc events
	hook_event(input_key, EventType::InputKey, "UPlayerInput::InputKey");
	hook_event(inventory_sort, EventType::InventorySort, "UFGInventoryComponent::SortInventory");
}

// hooks an event into an original function
void EventLoader::hook_event(PVOID hook, EventType type, const char* function) {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// find the function by name
	PVOID func = DetourFindFunction(gameModule, function);
	if (!func) {
		log(LogType::Error, "Invalid function: ", function);
		return;
	}

	log(LogType::Normal, "Hooked function: ", function);

	// attach it, clearly
	DetourAttach(&(PVOID&)func, hook);
	DetourTransactionCommit();

	hookedFunctions.insert(std::pair<EventType, PVOID>(type, func));
}
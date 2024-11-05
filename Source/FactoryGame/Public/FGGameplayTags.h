// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

class UGameplayTagsManager;
/**
 * Class containing native gameplay tags.
 */
class FACTORYGAME_API FFGGameplayTags
{
public:	
	static void InitializeNativeTags();

	/** Input Tags**/
	struct FInputTags
	{
		FGameplayTag Pause;
		FGameplayTag CheatMenu;
		FGameplayTag DebugMenu;

		// Cheats
		struct FCheats
		{
			FGameplayTag ToggleFly;
			FGameplayTag ToggleGhostFly;
			FGameplayTag Teleport;
		} Cheats;

		// Movement
		struct FPlayerMovementTags
		{
			FGameplayTag MoveAxis;
			
			FGameplayTag LookAxis;
			FGameplayTag TurnAxis;
			
			FGameplayTag Jump;

			FGameplayTag Sprint;
			FGameplayTag Crouch;
			
			FGameplayTag RadialMenuDirectionAxis;
			FGameplayTag RadialMenuDirectionCursor;
		} PlayerMovement;

		
		// <FL> ZimmermannA
		// Menus via gamepad
		struct FGamepadMenuTags
		{
			FGameplayTag CancelMenu;
		} GamepadMenu;
		// </FL> 
		
		// Photo Mode
		struct FPhotoModeTags
		{
			FGameplayTag FOVScrollAxis;
			FGameplayTag ToggleInstructionWidgetVisibility;
			FGameplayTag ToggleHiRes;

			FGameplayTag ToggleAdvancedPhotoMode;
			FGameplayTag TogglePhotoModeDebug;
			FGameplayTag ToggleSequencer;
			FGameplayTag ToggleMouseControl;
			FGameplayTag TakePhoto;
		} PhotoMode;

		// Actions
		struct FPlayerActionTags
		{
			struct FHotbarTags
			{
				FGameplayTag Shortcut1;
				FGameplayTag Shortcut2;
				FGameplayTag Shortcut3;
				FGameplayTag Shortcut4;
				FGameplayTag Shortcut5;
				FGameplayTag Shortcut6;
				FGameplayTag Shortcut7;
				FGameplayTag Shortcut8;
				FGameplayTag Shortcut9;
				FGameplayTag Shortcut10;
				FGameplayTag RadialMenu;
				FGameplayTag RadialMenuPageDown;
				FGameplayTag RadialMenuPageUp;
			} Hotbar;
			
			FGameplayTag Use;
			
			FGameplayTag Respawn;

			FGameplayTag Chat;
			
			FGameplayTag PrimaryFire;
			FGameplayTag SecondaryFire;
			
			FGameplayTag EmoteWheel;
			
			FGameplayTag SampleBuilding;

			FGameplayTag CycleHotbarAxis;

			FGameplayTag AttentionPing;
			
			FGameplayTag MapMarkerMode;
			FGameplayTag MapMarkerPlace;

			FGameplayTag ToggleInventory;
			FGameplayTag ToggleCodex;
			FGameplayTag ToggleQuickSearch;
			FGameplayTag ToggleMap;
			FGameplayTag TogglePhotoMode;
			// <FL> PuschkeN Toggling auto pickup on/off
			FGameplayTag ToggleAutoPickup;
			// </FL>

			FGameplayTag ToggleFlashlight;

			// Clipboard
			struct FPlayerClipboardTags
			{
				FGameplayTag Copy;
				FGameplayTag Paste;
			} Clipboard;

			// Buildgun
			struct FPlayerBuildGunTags
			{
				FGameplayTag Build;
				FGameplayTag Dismantle;
				FGameplayTag Paint;
			} BuildGun;

			FGameplayTag HandheldSelectionRadialMenu;	 // <FL> [KajtaziT]
			
		} PlayerActions;

		// Equipment
		struct FEquipmentTags
		{
			FGameplayTag Cycle;
			FGameplayTag CycleNext;
			FGameplayTag Holster;
			FGameplayTag Reload;
			
			// BuildGun
			struct FEquipmentBuildGunTags
			{
				FGameplayTag PrimaryFire;
				FGameplayTag SecondaryFire;
				
				FGameplayTag ModeSelect;
				FGameplayTag Scroll;

				// BuildGunBuild
				struct FEquipmentBuildGunBuildTags
				{
					FGameplayTag HologramLock;
					FGameplayTag HologramNudgeAxis;
					FGameplayTag SnapToGuidelines;
					FGameplayTag HotbarSample;
				} BuildState;

				// BuildGunDismantle
				struct FEquipmentBuildGunDismantleTags
				{
					FGameplayTag ToggleMultiSelect;
					FGameplayTag SetDismantleFilter;
				} DismantleState;

				// BuildGunPaint
				struct FEquipmentBuildGunPaintTags
				{
					FGameplayTag SetCustomizeFilter;
				} PaintState;
				
			} BuildGun;

			// Object Scanner
			struct FObjectScannerTags
			{
				FGameplayTag OpenMenu;
				FGameplayTag Cycle;
			} ObjectScanner;

			// Resource Scanner
			struct FResourceScannerTags
			{
				FGameplayTag Scan;
			} ResourceScanner;

			// BoomBox
			struct FBoomBoxTags
			{
				FGameplayTag PlayPause;
				FGameplayTag Turbobass;
				FGameplayTag ToggleMenu;
				FGameplayTag PutDown;
			} BoomBox;
			
		} Equipment;

		// Vehicles
        struct FVehicleTags
        {
        	FGameplayTag LeaveVehicle;
        	
        	FGameplayTag Handbrake;
        	FGameplayTag Honk;
        	
        	FGameplayTag ToggleCamera;
        	FGameplayTag ToggleLights;

        	// Wheeled Vehicles
        	struct FWheeledVehicleTags
        	{
        		FGameplayTag OpenRecorder;
        		FGameplayTag ThrottleSteerAxis;
				FGameplayTag GamepadThrottle;
				FGameplayTag GamepadBrake;
				FGameplayTag GamepadSteer;
        	} WheeledVehicle;

        	// Trains
        	struct FTrainTags
        	{
        		FGameplayTag OpenLocomotiveMenu;
        		FGameplayTag ThrottleAxis;
        		FGameplayTag SteerAxis;
        	} Train;
        	
        } Vehicle;
		
		// UI
		struct FUITags
		{
			struct FAudioMessageTags
			{
				FGameplayTag SkipAudioMessage;
			} AudioMessage;
		} UI;
		
	} static Input;

	/** Onboarding Step Tags **/
	struct FOnboardingStepTags
	{
		FGameplayTag PlanetFall;
		FGameplayTag Landed;
		FGameplayTag EquipXenoZapper;
		FGameplayTag DismantleDropPod;
		FGameplayTag PickupIronOre;
		FGameplayTag BuildHub;
		FGameplayTag HubUpgrade1;
		FGameplayTag HubUpgrade2;
		FGameplayTag HubUpgrade3;
		FGameplayTag HubUpgrade4;
		FGameplayTag HubUpgrade5;
		FGameplayTag HubUpgrade6;
		FGameplayTag OnboardingComplete;
	} static OnboardingStep;

protected:
	/** Adds all native tags to the manager. */
	static void AddAllTags( UGameplayTagsManager& Manager );

	// Categorized functions for adding tags, just for sanity
	static void AddInputTags( UGameplayTagsManager& Manager );
	
	static void AddInputPlayerMovementTags( UGameplayTagsManager& Manager );
	static void AddInputPlayerActionTags( UGameplayTagsManager& Manager );
	static void AddInputPhotoModeTags( UGameplayTagsManager& Manager );

	static void AddCheatTags( UGameplayTagsManager& Manager );

	static void AddInputBuildGunTags( UGameplayTagsManager& Manager );
	static void AddInputObjectScannerTags( UGameplayTagsManager& Manager );
	static void AddInputResourceScannerTags( UGameplayTagsManager& Manager );
	static void AddInputBoomBoxTags( UGameplayTagsManager& Manager );

	static void AddInputVehicleTags( UGameplayTagsManager& Manager );
	
	static void AddInputUITags( UGameplayTagsManager& Manager );

	// Onboarding tags
	static void AddOnboardingStepTags( UGameplayTagsManager& Manager );
};

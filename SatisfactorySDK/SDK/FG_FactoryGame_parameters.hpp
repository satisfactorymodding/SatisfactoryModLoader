#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_FactoryGame_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function FactoryGame.FGActorRepresentation.OnRep_ShouldShowOnMap
struct UFGActorRepresentation_OnRep_ShouldShowOnMap_Params
{
};

// Function FactoryGame.FGActorRepresentation.OnRep_ShouldShowInCompass
struct UFGActorRepresentation_OnRep_ShouldShowInCompass_Params
{
};

// Function FactoryGame.FGActorRepresentation.OnRep_RepresentationTexture
struct UFGActorRepresentation_OnRep_RepresentationTexture_Params
{
};

// Function FactoryGame.FGActorRepresentation.OnRep_RepresentationText
struct UFGActorRepresentation_OnRep_RepresentationText_Params
{
};

// Function FactoryGame.FGActorRepresentation.OnRep_RepresentationColor
struct UFGActorRepresentation_OnRep_RepresentationColor_Params
{
};

// Function FactoryGame.FGActorRepresentation.OnRep_FogOfWarRevealType
struct UFGActorRepresentation_OnRep_FogOfWarRevealType_Params
{
};

// Function FactoryGame.FGActorRepresentation.OnRep_FogOfWarRevealRadius
struct UFGActorRepresentation_OnRep_FogOfWarRevealRadius_Params
{
};

// Function FactoryGame.FGActorRepresentation.IsActorStatic
struct UFGActorRepresentation_IsActorStatic_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentation.GetShouldShowOnMap
struct UFGActorRepresentation_GetShouldShowOnMap_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentation.GetShouldShowInCompass
struct UFGActorRepresentation_GetShouldShowInCompass_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentation.GetRepresentationType
struct UFGActorRepresentation_GetRepresentationType_Params
{
	ERepresentationType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentation.GetRepresentationTexture
struct UFGActorRepresentation_GetRepresentationTexture_Params
{
	class UTexture2D*                                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentation.GetRepresentationText
struct UFGActorRepresentation_GetRepresentationText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGActorRepresentation.GetRepresentationColor
struct UFGActorRepresentation_GetRepresentationColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentation.GetRealActor
struct UFGActorRepresentation_GetRealActor_Params
{
	class AActor*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentation.GetIsTemporary
struct UFGActorRepresentation_GetIsTemporary_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentation.GetFogOfWarRevealType
struct UFGActorRepresentation_GetFogOfWarRevealType_Params
{
	EFogOfWarRevealType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentation.GetFogOfWarRevealRadius
struct UFGActorRepresentation_GetFogOfWarRevealRadius_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentation.GetActorRotation
struct UFGActorRepresentation_GetActorRotation_Params
{
	struct FRotator                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentation.GetActorLocation
struct UFGActorRepresentation_GetActorLocation_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentationInterface.UpdateRepresentation
struct UFGActorRepresentationInterface_UpdateRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentationInterface.SetActorRepresentationText
struct UFGActorRepresentationInterface_SetActorRepresentationText_Params
{
	struct FText                                       newText;                                                  // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGActorRepresentationInterface.RemoveAsRepresentation
struct UFGActorRepresentationInterface_RemoveAsRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentationInterface.IsActorStatic
struct UFGActorRepresentationInterface_IsActorStatic_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentationInterface.GetRealActorRotation
struct UFGActorRepresentationInterface_GetRealActorRotation_Params
{
	struct FRotator                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentationInterface.GetRealActorLocation
struct UFGActorRepresentationInterface_GetRealActorLocation_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentationInterface.GetActorShouldShowOnMap
struct UFGActorRepresentationInterface_GetActorShouldShowOnMap_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentationInterface.GetActorShouldShowInCompass
struct UFGActorRepresentationInterface_GetActorShouldShowInCompass_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentationInterface.GetActorRepresentationType
struct UFGActorRepresentationInterface_GetActorRepresentationType_Params
{
	ERepresentationType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentationInterface.GetActorRepresentationTexture
struct UFGActorRepresentationInterface_GetActorRepresentationTexture_Params
{
	class UTexture2D*                                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentationInterface.GetActorRepresentationText
struct UFGActorRepresentationInterface_GetActorRepresentationText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGActorRepresentationInterface.GetActorRepresentationColor
struct UFGActorRepresentationInterface_GetActorRepresentationColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentationInterface.GetActorFogOfWarRevealType
struct UFGActorRepresentationInterface_GetActorFogOfWarRevealType_Params
{
	EFogOfWarRevealType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentationInterface.GetActorFogOfWarRevealRadius
struct UFGActorRepresentationInterface_GetActorFogOfWarRevealRadius_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentationInterface.AddAsRepresentation
struct UFGActorRepresentationInterface_AddAsRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentationManager.UpdateRepresentation
struct AFGActorRepresentationManager_UpdateRepresentation_Params
{
	class AActor*                                      realActor;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               isLocal;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentationManager.RemoveRepresentationOfActor
struct AFGActorRepresentationManager_RemoveRepresentationOfActor_Params
{
	class AActor*                                      realActor;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentationManager.OnRep_ReplicatedRepresentations
struct AFGActorRepresentationManager_OnRep_ReplicatedRepresentations_Params
{
};

// Function FactoryGame.FGActorRepresentationManager.GetAllActorRepresentations
struct AFGActorRepresentationManager_GetAllActorRepresentations_Params
{
	TArray<class UFGActorRepresentation*>              out_AllRepresentations;                                   // (Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function FactoryGame.FGActorRepresentationManager.Get
struct AFGActorRepresentationManager_Get_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGActorRepresentationManager*               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentationManager.CreateAndAddNewRepresentationNoActor
struct AFGActorRepresentationManager_CreateAndAddNewRepresentationNoActor_Params
{
	struct FVector                                     Location;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	class UTexture2D*                                  compassTexture;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                compassColor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              LifeTime;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               shouldShowInCompass;                                      // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               shouldShowOnMap;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	ERepresentationType                                representationType;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               isLocal;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGActorRepresentationManager.CreateAndAddNewRepresentation
struct AFGActorRepresentationManager_CreateAndAddNewRepresentation_Params
{
	class AActor*                                      realActor;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               isLocal;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGAggroTargetInterface.UnregisterAttacker
struct UFGAggroTargetInterface_UnregisterAttacker_Params
{
	class AFGEnemyController*                          forController;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGAggroTargetInterface.ShouldAutoregisterAsTargetable
struct UFGAggroTargetInterface_ShouldAutoregisterAsTargetable_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGAggroTargetInterface.RegisterIncomingAttacker
struct UFGAggroTargetInterface_RegisterIncomingAttacker_Params
{
	class AFGEnemyController*                          forController;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGAggroTargetInterface.IsAlive
struct UFGAggroTargetInterface_IsAlive_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGAggroTargetInterface.GetTargetComponent
struct UFGAggroTargetInterface_GetTargetComponent_Params
{
	class UPrimitiveComponent*                         ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGAggroTargetInterface.GetEnemyTargetDesirability
struct UFGAggroTargetInterface_GetEnemyTargetDesirability_Params
{
	class AFGEnemyController*                          forController;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGAggroTargetInterface.GetAttackLocation
struct UFGAggroTargetInterface_GetAttackLocation_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGAggroTargetInterface.GetActor
struct UFGAggroTargetInterface_GetActor_Params
{
	class AActor*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGAISystem.UnpardonActor
struct UFGAISystem_UnpardonActor_Params
{
	class AActor*                                      inActor;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGAISystem.RemoveFromTargetableList
struct UFGAISystem_RemoveFromTargetableList_Params
{
	TScriptInterface<class UFGAggroTargetInterface>    aggroTarget;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGAISystem.PlayerDestroyed
struct UFGAISystem_PlayerDestroyed_Params
{
	class AActor*                                      destroyedPlayer;                                          // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGAISystem.PardonActor
struct UFGAISystem_PardonActor_Params
{
	class AActor*                                      inActor;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGAISystem.IsActorPardoned
struct UFGAISystem_IsActorPardoned_Params
{
	class AActor*                                      inActor;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGAISystem.GetAggroTargetList
struct UFGAISystem_GetAggroTargetList_Params
{
	TArray<TScriptInterface<class UFGAggroTargetInterface>> ReturnValue;                                              // (ConstParm, Parm, OutParm, ZeroConstructor, ReturnParm, ReferenceParm)
};

// Function FactoryGame.FGAISystem.CreatureDestroyed
struct UFGAISystem_CreatureDestroyed_Params
{
	class AActor*                                      destroyedEnemy;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGAISystem.ClearAllPardonedActors
struct UFGAISystem_ClearAllPardonedActors_Params
{
};

// Function FactoryGame.FGAISystem.AggroTargetDestroyed
struct UFGAISystem_AggroTargetDestroyed_Params
{
	class AActor*                                      DestroyedActor;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGAISystem.AddToTargetableList
struct UFGAISystem_AddToTargetableList_Params
{
	TScriptInterface<class UFGAggroTargetInterface>    aggroTarget;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGAmbientSettings.ShouldIgnoreListenerRotation
struct UFGAmbientSettings_ShouldIgnoreListenerRotation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGAmbientSettings.OnExitOuterVolume
struct UFGAmbientSettings_OnExitOuterVolume_Params
{
	class UAkComponent*                                ambientComponent;                                         // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGAmbientSettings.OnExitInnerVolume
struct UFGAmbientSettings_OnExitInnerVolume_Params
{
	class UAkComponent*                                ambientComponent;                                         // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGAmbientSettings.OnEnterOuterVolume
struct UFGAmbientSettings_OnEnterOuterVolume_Params
{
	class UAkComponent*                                ambientComponent;                                         // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGAmbientSettings.OnEnterInnerVolume
struct UFGAmbientSettings_OnEnterInnerVolume_Params
{
	class UAkComponent*                                ambientComponent;                                         // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGAmbientSettings.GetEnterOuterVolumeEvent
struct UFGAmbientSettings_GetEnterOuterVolumeEvent_Params
{
	class UAkAudioEvent*                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGAmbientSettings.GetEnterInnerVolumeEvent
struct UFGAmbientSettings_GetEnterInnerVolumeEvent_Params
{
	class UAkAudioEvent*                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGAmbientSoundSpline.GetSplineComponent
struct AFGAmbientSoundSpline_GetSplineComponent_Params
{
	class USplineComponent*                            ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGCharacterAnimInstance.OnRadialDamageTaken
struct UFGCharacterAnimInstance_OnRadialDamageTaken_Params
{
};

// Function FactoryGame.FGCharacterAnimInstance.OnPointDamageTaken
struct UFGCharacterAnimInstance_OnPointDamageTaken_Params
{
	struct FVector                                     shootDIrection;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterAnimInstance.OnAnyDamageTaken
struct UFGCharacterAnimInstance_OnAnyDamageTaken_Params
{
};

// Function FactoryGame.FGCharacterAnimInstance.GetVelocityDirection
struct UFGCharacterAnimInstance_GetVelocityDirection_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterAnimInstance.GetVelocity
struct UFGCharacterAnimInstance_GetVelocity_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterAnimInstance.GetDesiredWalkRotation
struct UFGCharacterAnimInstance_GetDesiredWalkRotation_Params
{
	struct FRotator                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterAnimInstance.GetDesiredRunLeanRotation
struct UFGCharacterAnimInstance_GetDesiredRunLeanRotation_Params
{
	struct FRotator                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterAnimInstance.GetCachedCharacter
struct UFGCharacterAnimInstance_GetCachedCharacter_Params
{
	class AFGCharacterBase*                            ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterAnimInstance.GetAccelerationVectorLength
struct UFGCharacterAnimInstance_GetAccelerationVectorLength_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGHologram.Server_SetSnapToGuideLines
struct AFGHologram_Server_SetSnapToGuideLines_Params
{
	bool                                               IsEnabled;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHologram.OnRep_PlacementMaterial
struct AFGHologram_OnRep_PlacementMaterial_Params
{
};

// Function FactoryGame.FGHologram.OnRep_InitialScrollModeValue
struct AFGHologram_OnRep_InitialScrollModeValue_Params
{
};

// Function FactoryGame.FGHologram.IsChanged
struct AFGHologram_IsChanged_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGHologram.GetNoSnapMode
struct AFGHologram_GetNoSnapMode_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGHologram.GetConstructDisqualifiers
struct AFGHologram_GetConstructDisqualifiers_Params
{
	TArray<class UClass*>                              out_constructResults;                                     // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGHologram.Client_PlaySnapSound
struct AFGHologram_Client_PlaySnapSound_Params
{
};

// Function FactoryGame.FGHologram.CanConstruct
struct AFGHologram_CanConstruct_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGHologram.AddValidHitClass
struct AFGHologram_AddValidHitClass_Params
{
	class UClass*                                      hitClass;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableHologram.ReceiveConfigureComponents
struct AFGBuildableHologram_ReceiveConfigureComponents_Params
{
	class AFGBuildable*                                inBuildable;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableHologram.ReceiveConfigureActor
struct AFGBuildableHologram_ReceiveConfigureActor_Params
{
	class AFGBuildable*                                inBuildable;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGAttack.GetStopsMovement
struct UFGAttack_GetStopsMovement_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGAttack.GetDamageType
struct UFGAttack_GetDamageType_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGAttack.GetDamage
struct UFGAttack_GetDamage_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGAttack.GetAttackRange
struct UFGAttack_GetAttackRange_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGAttack.GetAttackMontage
struct UFGAttack_GetAttackMontage_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UAnimMontage*                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGAttack.GetAttackAngle
struct UFGAttack_GetAttackAngle_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGAttack.GetAttackActivationDistance
struct UFGAttack_GetAttackActivationDistance_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGAttackMeleeJump.GetPreJumpMontage
struct UFGAttackMeleeJump_GetPreJumpMontage_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UAnimMontage*                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGAttackMeleeJump.GetJumpVelocity
struct UFGAttackMeleeJump_GetJumpVelocity_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGAttackMeleeJump.GetJumpRange
struct UFGAttackMeleeJump_GetJumpRange_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGAttackRanged.SpawnProjectile
struct UFGAttackRanged_SpawnProjectile_Params
{
	class AActor*                                      targetActor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGEnemy*                                    sourceActor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGAttentionPingActor.SpawnAttentionPingEffects
struct AFGAttentionPingActor_SpawnAttentionPingEffects_Params
{
};

// Function FactoryGame.FGAttentionPingActor.OnRep_PlayerSlotIdx
struct AFGAttentionPingActor_OnRep_PlayerSlotIdx_Params
{
};

// Function FactoryGame.FGAttentionPingActor.GetPlayerSlotIdx
struct AFGAttentionPingActor_GetPlayerSlotIdx_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGMessageBase.GetMessageDefaultObject
struct UFGMessageBase_GetMessageDefaultObject_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGAudioMessage.StartPlayback
struct UFGAudioMessage_StartPlayback_Params
{
};

// Function FactoryGame.FGAudioMessage.PlayNextDialogue
struct UFGAudioMessage_PlayNextDialogue_Params
{
};

// Function FactoryGame.FGAudioMessage.GetCurrentDialogue
struct UFGAudioMessage_GetCurrentDialogue_Params
{
	struct FAudioSubtitlePair                          ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGAudioMessage.ContinuePlayback
struct UFGAudioMessage_ContinuePlayback_Params
{
};

// Function FactoryGame.FGAudioMessage.CancelPlayback
struct UFGAudioMessage_CancelPlayback_Params
{
};

// Function FactoryGame.FGAudioMessage.AssignOnConcludedDelegate
struct UFGAudioMessage_AssignOnConcludedDelegate_Params
{
	struct FScriptDelegate                             concludedDelegate;                                        // (Parm, ZeroConstructor)
};

// Function FactoryGame.FGBaseUI.SetPopup
struct UFGBaseUI_SetPopup_Params
{
	class UFGPopupWidget*                              inPopup;                                                  // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBaseUI.PopPopupQueue
struct UFGBaseUI_PopPopupQueue_Params
{
};

// Function FactoryGame.FGBaseUI.GetPopup
struct UFGBaseUI_GetPopup_Params
{
	class UFGPopupWidget*                              ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBaseUI.CreatePopupWidget
struct UFGBaseUI_CreatePopupWidget_Params
{
	struct FPopupData                                  PopupData;                                                // (Parm)
	class UFGPopupWidget*                              ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBaseUI.ClosePopup
struct UFGBaseUI_ClosePopup_Params
{
};

// Function FactoryGame.FGBaseUI.AddPopup
struct UFGBaseUI_AddPopup_Params
{
	struct FText                                       Title;                                                    // (Parm)
	struct FText                                       Body;                                                     // (Parm)
	struct FScriptDelegate                             ConfirmClickDelegate;                                     // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TEnumAsByte<EPopupId>                              PopupID;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      PopupClass;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.UpdateUseState
struct UFGBlueprintFunctionLibrary_UpdateUseState_Params
{
	struct FUseState                                   State;                                                    // (Parm, OutParm, ReferenceParm)
	class UClass*                                      newState;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.TravelToMainMenu
struct UFGBlueprintFunctionLibrary_TravelToMainMenu_Params
{
	class APlayerController*                           PlayerController;                                         // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.ShowOutline
struct UFGBlueprintFunctionLibrary_ShowOutline_Params
{
	class UPrimitiveComponent*                         comp;                                                     // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	EOutlineColor                                      Color;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.RemoveGenericTickObjectFromSignificanceManager
struct UFGBlueprintFunctionLibrary_RemoveGenericTickObjectFromSignificanceManager_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     Obj;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.RemoveGainSignificanceObjectFromSignificanceManager
struct UFGBlueprintFunctionLibrary_RemoveGainSignificanceObjectFromSignificanceManager_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     Obj;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.RemoveFactoryObjectFromSignificanceManager
struct UFGBlueprintFunctionLibrary_RemoveFactoryObjectFromSignificanceManager_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     Obj;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.RemoveConveyorBeltFromSignificanceManager
struct UFGBlueprintFunctionLibrary_RemoveConveyorBeltFromSignificanceManager_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     Obj;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.RemoveAudioVolumeFromSignificanceManager
struct UFGBlueprintFunctionLibrary_RemoveAudioVolumeFromSignificanceManager_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     Obj;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.RemoveAmbientSoundSplineFromSignificanceManager
struct UFGBlueprintFunctionLibrary_RemoveAmbientSoundSplineFromSignificanceManager_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     Obj;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.LogX
struct UFGBlueprintFunctionLibrary_LogX_Params
{
	float                                              Base;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Value;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.LinearColorToHex
struct UFGBlueprintFunctionLibrary_LinearColorToHex_Params
{
	struct FLinearColor                                inColor;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.IsLocationNearABase
struct UFGBlueprintFunctionLibrary_IsLocationNearABase_Params
{
	class UObject*                                     WorldContext;                                             // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     InLocation;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              closeDistance;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.IsLocallyHumanControlled
struct UFGBlueprintFunctionLibrary_IsLocallyHumanControlled_Params
{
	class APawn*                                       Pawn;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.IsInAlwaysLoadedLevel
struct UFGBlueprintFunctionLibrary_IsInAlwaysLoadedLevel_Params
{
	class AActor*                                      Actor;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.IsGameWorld
struct UFGBlueprintFunctionLibrary_IsGameWorld_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.IsEditorWorld
struct UFGBlueprintFunctionLibrary_IsEditorWorld_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.IsAlphaBuild
struct UFGBlueprintFunctionLibrary_IsAlphaBuild_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.ImpactEffectIsWithinDistance
struct UFGBlueprintFunctionLibrary_ImpactEffectIsWithinDistance_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class APawn*                                       Instigator;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     SpawnLocation;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              visibleCullDistance;                                      // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.ImpactEffectIsRelevant
struct UFGBlueprintFunctionLibrary_ImpactEffectIsRelevant_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class APawn*                                       Instigator;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     SpawnLocation;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              visibleCullDistance;                                      // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              alwaysSuccessDistance;                                    // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               skipLOSCheck;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.HideOutline
struct UFGBlueprintFunctionLibrary_HideOutline_Params
{
	class UPrimitiveComponent*                         comp;                                                     // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.GetVersionString
struct UFGBlueprintFunctionLibrary_GetVersionString_Params
{
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.GetOuterActor
struct UFGBlueprintFunctionLibrary_GetOuterActor_Params
{
	class UObject*                                     Obj;                                                      // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.GetLanguage
struct UFGBlueprintFunctionLibrary_GetLanguage_Params
{
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.GetComponentFlagSoftLanding
struct UFGBlueprintFunctionLibrary_GetComponentFlagSoftLanding_Params
{
	struct FName                                       ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.GetAvailableSubCategoriesForCategory
struct UFGBlueprintFunctionLibrary_GetAvailableSubCategoriesForCategory_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      buildCategory;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class UClass*>                              out_subCategories;                                        // (Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.GetAvailableRecipesInSubCategory
struct UFGBlueprintFunctionLibrary_GetAvailableRecipesInSubCategory_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      subCategory;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class UClass*>                              out_recipes;                                              // (Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.GetAvailableRecipesInCategory
struct UFGBlueprintFunctionLibrary_GetAvailableRecipesInCategory_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      buildCategory;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class UClass*>                              out_recipes;                                              // (Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.GetAllWidgetsOfClassInHierarchy
struct UFGBlueprintFunctionLibrary_GetAllWidgetsOfClassInHierarchy_Params
{
	class UWidget*                                     hierarchyContext;                                         // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UClass*                                      WidgetClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class UWidget*>                             FoundWidgets;                                             // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.GetAllDescriptorsSorted
struct UFGBlueprintFunctionLibrary_GetAllDescriptorsSorted_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class UClass*>                              out_descriptors;                                          // (Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.GetAllBuildCategories
struct UFGBlueprintFunctionLibrary_GetAllBuildCategories_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class UClass*>                              out_buildCategories;                                      // (Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.CreateSessionAndTravelToMap
struct UFGBlueprintFunctionLibrary_CreateSessionAndTravelToMap_Params
{
	class APlayerController*                           Player;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class FString                                      mapName;                                                  // (Parm, ZeroConstructor)
	class FString                                      options;                                                  // (Parm, ZeroConstructor)
	class FString                                      SessionName;                                              // (Parm, ZeroConstructor)
	TEnumAsByte<ESessionVisibility>                    sessionVisibility;                                        // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.CmS2KmH
struct UFGBlueprintFunctionLibrary_CmS2KmH_Params
{
	float                                              CmS;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.ClosePopup
struct UFGBlueprintFunctionLibrary_ClosePopup_Params
{
	class APlayerController*                           Controller;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.Cheat_GetAllDescriptors
struct UFGBlueprintFunctionLibrary_Cheat_GetAllDescriptors_Params
{
	TArray<class UClass*>                              out_descriptors;                                          // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.ChangeLanguage
struct UFGBlueprintFunctionLibrary_ChangeLanguage_Params
{
	class FString                                      Target;                                                   // (Parm, ZeroConstructor)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.CanBeOnConveyor
struct UFGBlueprintFunctionLibrary_CanBeOnConveyor_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.AddPopupWithCloseDelegate
struct UFGBlueprintFunctionLibrary_AddPopupWithCloseDelegate_Params
{
	class APlayerController*                           Controller;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       Title;                                                    // (Parm)
	struct FText                                       Body;                                                     // (Parm)
	struct FScriptDelegate                             CloseDelegate;                                            // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TEnumAsByte<EPopupId>                              PopupID;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      PopupClass;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     popupInstigator;                                          // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.AddPopup
struct UFGBlueprintFunctionLibrary_AddPopup_Params
{
	class APlayerController*                           Controller;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       Title;                                                    // (Parm)
	struct FText                                       Body;                                                     // (Parm)
	struct FScriptDelegate                             ConfirmClickDelegate;                                     // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TEnumAsByte<EPopupId>                              PopupID;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      PopupClass;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     popupInstigator;                                          // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.AddGenericTickObjectToSignificanceManager
struct UFGBlueprintFunctionLibrary_AddGenericTickObjectToSignificanceManager_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     Obj;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.AddGainSignificanceObjectToSignificanceManager
struct UFGBlueprintFunctionLibrary_AddGainSignificanceObjectToSignificanceManager_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     Obj;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              desiredGainDistance;                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.AddFactoryObjectToSignificanceManager
struct UFGBlueprintFunctionLibrary_AddFactoryObjectToSignificanceManager_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     Obj;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.AddConveyorBeltToSignificanceManager
struct UFGBlueprintFunctionLibrary_AddConveyorBeltToSignificanceManager_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     Obj;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.AddAudioVolumeToSignificanceManager
struct UFGBlueprintFunctionLibrary_AddAudioVolumeToSignificanceManager_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     Obj;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBlueprintFunctionLibrary.AddAmbientSoundSplineToSignificanceManager
struct UFGBlueprintFunctionLibrary_AddAmbientSoundSplineToSignificanceManager_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     Obj;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBoundedTextRenderComponent.AssignBoundingBox
struct UFGBoundedTextRenderComponent_AssignBoundingBox_Params
{
	class UBoxComponent*                               BoxComponent;                                             // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBuildable.ShowHighlightEffect
struct AFGBuildable_ShowHighlightEffect_Params
{
};

// Function FactoryGame.FGBuildable.RemoveHighlightEffect
struct AFGBuildable_RemoveHighlightEffect_Params
{
};

// Function FactoryGame.FGBuildable.ReapplyColorSlot
struct AFGBuildable_ReapplyColorSlot_Params
{
};

// Function FactoryGame.FGBuildable.PlayDismantleSound
struct AFGBuildable_PlayDismantleSound_Params
{
};

// Function FactoryGame.FGBuildable.PlayDismantleEffects
struct AFGBuildable_PlayDismantleEffects_Params
{
};

// Function FactoryGame.FGBuildable.PlayConstructSound
struct AFGBuildable_PlayConstructSound_Params
{
};

// Function FactoryGame.FGBuildable.PlayBuildEffects
struct AFGBuildable_PlayBuildEffects_Params
{
	class AActor*                                      inInstigator;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildable.OnRep_SecondaryColor
struct AFGBuildable_OnRep_SecondaryColor_Params
{
};

// Function FactoryGame.FGBuildable.OnRep_PrimaryColor
struct AFGBuildable_OnRep_PrimaryColor_Params
{
};

// Function FactoryGame.FGBuildable.OnRep_DidFirstTimeUse
struct AFGBuildable_OnRep_DidFirstTimeUse_Params
{
};

// Function FactoryGame.FGBuildable.OnRep_ColorSlot
struct AFGBuildable_OnRep_ColorSlot_Params
{
};

// Function FactoryGame.FGBuildable.GetNumPowerConnections
struct AFGBuildable_GetNumPowerConnections_Params
{
	unsigned char                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildable.GetMainMeshes
struct AFGBuildable_GetMainMeshes_Params
{
	TArray<class UMeshComponent*>                      ReturnValue;                                              // (ConstParm, ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, ReferenceParm)
};

// Function FactoryGame.FGBuildable.GetInteractWidgetClass
struct AFGBuildable_GetInteractWidgetClass_Params
{
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildable.GetDismantleBlueprintReturns
struct AFGBuildable_GetDismantleBlueprintReturns_Params
{
	TArray<struct FInventoryStack>                     out_returns;                                              // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGBuildable.GetClearanceComponent
struct AFGBuildable_GetClearanceComponent_Params
{
	class UShapeComponent*                             ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBuildable.Factory_ReceiveTick
struct AFGBuildable_Factory_ReceiveTick_Params
{
	float                                              DeltaTime;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildable.Factory_PeekOutput
struct AFGBuildable_Factory_PeekOutput_Params
{
	class UFGFactoryConnectionComponent*               Connection;                                               // (ConstParm, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	TArray<struct FInventoryItem>                      out_items;                                                // (Parm, OutParm, ZeroConstructor)
	class UClass*                                      Type;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildable.Factory_GrabOutput
struct AFGBuildable_Factory_GrabOutput_Params
{
	class UFGFactoryConnectionComponent*               Connection;                                               // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FInventoryItem                              out_item;                                                 // (Parm, OutParm)
	float                                              out_OffsetBeyond;                                         // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      Type;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.StopProductionLoopEffects
struct AFGBuildableFactory_StopProductionLoopEffects_Params
{
};

// Function FactoryGame.FGBuildableFactory.StopIdlingLoopEffects
struct AFGBuildableFactory_StopIdlingLoopEffects_Params
{
};

// Function FactoryGame.FGBuildableFactory.StartProductionLoopEffects
struct AFGBuildableFactory_StartProductionLoopEffects_Params
{
};

// Function FactoryGame.FGBuildableFactory.StartIdlingLoopEffects
struct AFGBuildableFactory_StartIdlingLoopEffects_Params
{
};

// Function FactoryGame.FGBuildableFactory.SetPendingPotential
struct AFGBuildableFactory_SetPendingPotential_Params
{
	float                                              newPendingPotential;                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.SetIsProductionPaused
struct AFGBuildableFactory_SetIsProductionPaused_Params
{
	bool                                               IsPaused;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.RunsOnPower
struct AFGBuildableFactory_RunsOnPower_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.ReceiveUpdateEffects
struct AFGBuildableFactory_ReceiveUpdateEffects_Params
{
	float                                              DeltaSeconds;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.OnRep_ReplicationDetailActor
struct AFGBuildableFactory_OnRep_ReplicationDetailActor_Params
{
};

// Function FactoryGame.FGBuildableFactory.OnRep_IsProducing
struct AFGBuildableFactory_OnRep_IsProducing_Params
{
};

// Function FactoryGame.FGBuildableFactory.OnPotentialInventoryItemRemoved
struct AFGBuildableFactory_OnPotentialInventoryItemRemoved_Params
{
	class UClass*                                      ItemClass;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                numRemoved;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.OnIsProducingChanged
struct AFGBuildableFactory_OnIsProducingChanged_Params
{
	bool                                               newIsProducing;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.OnHasPowerChanged
struct AFGBuildableFactory_OnHasPowerChanged_Params
{
	bool                                               newHasPower;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.IsProductionPaused
struct AFGBuildableFactory_IsProductionPaused_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.IsProducing
struct AFGBuildableFactory_IsProducing_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.IsConfigured
struct AFGBuildableFactory_IsConfigured_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.HasPower
struct AFGBuildableFactory_HasPower_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.GetProductivity
struct AFGBuildableFactory_GetProductivity_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.GetProductionProgress
struct AFGBuildableFactory_GetProductionProgress_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.GetProductionIndicatorStatus
struct AFGBuildableFactory_GetProductionIndicatorStatus_Params
{
	EProductionStatus                                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.GetProductionCycleTimeForRecipe
struct AFGBuildableFactory_GetProductionCycleTimeForRecipe_Params
{
	class UClass*                                      Recipe;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.GetProductionCycleTime
struct AFGBuildableFactory_GetProductionCycleTime_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.GetProducingPowerConsumption
struct AFGBuildableFactory_GetProducingPowerConsumption_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.GetPowerInfo
struct AFGBuildableFactory_GetPowerInfo_Params
{
	class UFGPowerInfoComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.GetPotentialInventory
struct AFGBuildableFactory_GetPotentialInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.GetPendingPotential
struct AFGBuildableFactory_GetPendingPotential_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.GetMinPotential
struct AFGBuildableFactory_GetMinPotential_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.GetMaxPossiblePotential
struct AFGBuildableFactory_GetMaxPossiblePotential_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.GetIsSignificant
struct AFGBuildableFactory_GetIsSignificant_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.GetDefaultProductionCycleTime
struct AFGBuildableFactory_GetDefaultProductionCycleTime_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.GetDefaultProducingPowerConsumption
struct AFGBuildableFactory_GetDefaultProducingPowerConsumption_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.GetCurrentPotential
struct AFGBuildableFactory_GetCurrentPotential_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.GetCurrentMaxPotential
struct AFGBuildableFactory_GetCurrentMaxPotential_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.GetConnectionComponents
struct AFGBuildableFactory_GetConnectionComponents_Params
{
	TArray<class UFGFactoryConnectionComponent*>       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGBuildableFactory.GetCanChangePotential
struct AFGBuildableFactory_GetCanChangePotential_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.Factory_ReceiveTickProducing
struct AFGBuildableFactory_Factory_ReceiveTickProducing_Params
{
	float                                              DeltaTime;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.Factory_ReceiveStopProducing
struct AFGBuildableFactory_Factory_ReceiveStopProducing_Params
{
};

// Function FactoryGame.FGBuildableFactory.Factory_ReceiveStartProducing
struct AFGBuildableFactory_Factory_ReceiveStartProducing_Params
{
};

// Function FactoryGame.FGBuildableFactory.Factory_CollectInput
struct AFGBuildableFactory_Factory_CollectInput_Params
{
};

// Function FactoryGame.FGBuildableFactory.CanProduce
struct AFGBuildableFactory_CanProduce_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.CalcProductionCycleTimeForPotential
struct AFGBuildableFactory_CalcProductionCycleTimeForPotential_Params
{
	float                                              potential;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableFactory.CalcProducingPowerConsumptionForPotential
struct AFGBuildableFactory_CalcProducingPowerConsumptionForPotential_Params
{
	float                                              potential;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableManufacturer.SetRecipe
struct AFGBuildableManufacturer_SetRecipe_Params
{
	class UClass*                                      Recipe;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableManufacturer.OnRep_CurrentRecipe
struct AFGBuildableManufacturer_OnRep_CurrentRecipe_Params
{
};

// Function FactoryGame.FGBuildableManufacturer.MoveOrDropOutputInventory
struct AFGBuildableManufacturer_MoveOrDropOutputInventory_Params
{
	class AFGCharacterPlayer*                          Pawn;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableManufacturer.MoveOrDropInputInventory
struct AFGBuildableManufacturer_MoveOrDropInputInventory_Params
{
	class AFGCharacterPlayer*                          Pawn;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableManufacturer.GetOutputInventory
struct AFGBuildableManufacturer_GetOutputInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBuildableManufacturer.GetManufacturingSpeed
struct AFGBuildableManufacturer_GetManufacturingSpeed_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableManufacturer.GetInputInventory
struct AFGBuildableManufacturer_GetInputInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBuildableManufacturer.GetCurrentRecipe
struct AFGBuildableManufacturer_GetCurrentRecipe_Params
{
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableManufacturer.GetAvailableRecipes
struct AFGBuildableManufacturer_GetAvailableRecipes_Params
{
	TArray<class UClass*>                              out_recipes;                                              // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGBuildableAutomatedWorkBench.SetManufacturingSpeed
struct AFGBuildableAutomatedWorkBench_SetManufacturingSpeed_Params
{
	float                                              newManufacturingSpeed;                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableConverter.SetupItemFilter
struct AFGBuildableConverter_SetupItemFilter_Params
{
};

// Function FactoryGame.FGBuildableConverter.GetNumberOfInputs
struct AFGBuildableConverter_GetNumberOfInputs_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableConverter.FilterIngredientClasses
struct AFGBuildableConverter_FilterIngredientClasses_Params
{
	class UClass*                                      Object;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                idx;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRemoteCallObject.GetGameState
struct UFGRemoteCallObject_GetGameState_Params
{
	class AFGGameState*                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGConveyorRemoteCallObject.Server_OnUse
struct UFGConveyorRemoteCallObject_Server_OnUse_Params
{
	class AFGBuildableConveyorBelt*                    Target;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGCharacterPlayer*                          byCharacter;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ItemIndex;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	int8_t                                             repVersion;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableConveyorBelt.OnRep_SplineData
struct AFGBuildableConveyorBelt_OnRep_SplineData_Params
{
};

// Function FactoryGame.FGBuildableConveyorBelt.GetSplineMesh
struct AFGBuildableConveyorBelt_GetSplineMesh_Params
{
	class UStaticMesh*                                 ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableConveyorBelt.GetSplineData
struct AFGBuildableConveyorBelt_GetSplineData_Params
{
	TArray<struct FSplinePointData>                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGBuildableConveyorBelt.GetSplineComponent
struct AFGBuildableConveyorBelt_GetSplineComponent_Params
{
	class UFGSplineComponent*                          ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBuildableConveyorBelt.GetIsSignificant
struct AFGBuildableConveyorBelt_GetIsSignificant_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableConveyorLift.OnRep_TopTransform
struct AFGBuildableConveyorLift_OnRep_TopTransform_Params
{
};

// Function FactoryGame.FGBuildableDecor.SetDecorMesh
struct AFGBuildableDecor_SetDecorMesh_Params
{
	class UStaticMesh*                                 Mesh;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableDecor.GetDecorMesh
struct AFGBuildableDecor_GetDecorMesh_Params
{
	class UStaticMesh*                                 ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableDockingStation.Undock
struct AFGBuildableDockingStation_Undock_Params
{
};

// Function FactoryGame.FGBuildableDockingStation.SetIsInLoadMode
struct AFGBuildableDockingStation_SetIsInLoadMode_Params
{
	bool                                               isInLoadMode;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableDockingStation.OnTransferComplete
struct AFGBuildableDockingStation_OnTransferComplete_Params
{
};

// Function FactoryGame.FGBuildableDockingStation.OnRep_FuelInventory
struct AFGBuildableDockingStation_OnRep_FuelInventory_Params
{
};

// Function FactoryGame.FGBuildableDockingStation.OnBeginUnloadVehicle
struct AFGBuildableDockingStation_OnBeginUnloadVehicle_Params
{
};

// Function FactoryGame.FGBuildableDockingStation.OnBeginLoadVehicle
struct AFGBuildableDockingStation_OnBeginLoadVehicle_Params
{
};

// Function FactoryGame.FGBuildableDockingStation.IsLoadUnloading
struct AFGBuildableDockingStation_IsLoadUnloading_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableDockingStation.GetIsInLoadMode
struct AFGBuildableDockingStation_GetIsInLoadMode_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableDockingStation.GetInventory
struct AFGBuildableDockingStation_GetInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBuildableDockingStation.GetFuelInventory
struct AFGBuildableDockingStation_GetFuelInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBuildableDockingStation.GetDockedActor
struct AFGBuildableDockingStation_GetDockedActor_Params
{
	class AActor*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableDockingStation.FilterFuelClasses
struct AFGBuildableDockingStation_FilterFuelClasses_Params
{
	class UClass*                                      Object;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                idx;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableDockingStation.Dock
struct AFGBuildableDockingStation_Dock_Params
{
	class AActor*                                      Actor;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableGenerator.IsFuseTriggered
struct AFGBuildableGenerator_IsFuseTriggered_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableGenerator.GetPowerProductionCapacity
struct AFGBuildableGenerator_GetPowerProductionCapacity_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableGenerator.GetLoadPercentage
struct AFGBuildableGenerator_GetLoadPercentage_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableGenerator.GetDefaultPowerProductionCapacity
struct AFGBuildableGenerator_GetDefaultPowerProductionCapacity_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableGenerator.Factory_TickPowerProduction
struct AFGBuildableGenerator_Factory_TickPowerProduction_Params
{
	float                                              dt;                                                       // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableGenerator.Factory_StopPowerProduction
struct AFGBuildableGenerator_Factory_StopPowerProduction_Params
{
};

// Function FactoryGame.FGBuildableGenerator.Factory_StartPowerProduction
struct AFGBuildableGenerator_Factory_StartPowerProduction_Params
{
};

// Function FactoryGame.FGBuildableGenerator.CanStartPowerProduction
struct AFGBuildableGenerator_CanStartPowerProduction_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableGenerator.CalcPowerProductionCapacityForPotential
struct AFGBuildableGenerator_CalcPowerProductionCapacityForPotential_Params
{
	float                                              potential;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableGeneratorFuel.OnRep_FuelInventory
struct AFGBuildableGeneratorFuel_OnRep_FuelInventory_Params
{
};

// Function FactoryGame.FGBuildableGeneratorFuel.IsValidFuel
struct AFGBuildableGeneratorFuel_IsValidFuel_Params
{
	class UClass*                                      Resource;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableGeneratorFuel.HasFuel
struct AFGBuildableGeneratorFuel_HasFuel_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableGeneratorFuel.GetFuelInventory
struct AFGBuildableGeneratorFuel_GetFuelInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBuildableGeneratorFuel.GetFuelAmount
struct AFGBuildableGeneratorFuel_GetFuelAmount_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableGeneratorFuel.FilterFuelClasses
struct AFGBuildableGeneratorFuel_FilterFuelClasses_Params
{
	class UClass*                                      Object;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                idx;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableGeneratorNuclear.GetWasteInventory
struct AFGBuildableGeneratorNuclear_GetWasteInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBuildableHubTerminal.GetTradingPost
struct AFGBuildableHubTerminal_GetTradingPost_Params
{
	class AFGBuildableTradingPost*                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildablePoweredWall.GetFoundationConnection
struct AFGBuildablePoweredWall_GetFoundationConnection_Params
{
	class UFGPowerConnectionComponent*                 ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBuildablePowerPole.GetPowerConnection
struct AFGBuildablePowerPole_GetPowerConnection_Params
{
	class UFGPowerConnectionComponent*                 ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBuildablePowerPole.GetPowerCircuit
struct AFGBuildablePowerPole_GetPowerCircuit_Params
{
	class UFGPowerCircuit*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildablePowerPole.GetCachedNumConnections
struct AFGBuildablePowerPole_GetCachedNumConnections_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableRadarTower.Multicast_ExpandRadarRadius
struct AFGBuildableRadarTower_Multicast_ExpandRadarRadius_Params
{
};

// Function FactoryGame.FGBuildableRadarTower.GetTimeToNextExpansion
struct AFGBuildableRadarTower_GetTimeToNextExpansion_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableRadarTower.GetNumRadarExpansionSteps
struct AFGBuildableRadarTower_GetNumRadarExpansionSteps_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableRadarTower.GetMinRevealRadius
struct AFGBuildableRadarTower_GetMinRevealRadius_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableRadarTower.GetMaxRevealRadius
struct AFGBuildableRadarTower_GetMaxRevealRadius_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableRadarTower.GetCurrentRevealRadius
struct AFGBuildableRadarTower_GetCurrentRevealRadius_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableRadarTower.GetCurrentExpansionStep
struct AFGBuildableRadarTower_GetCurrentExpansionStep_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableRailroadBridge.GetLength
struct AFGBuildableRailroadBridge_GetLength_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableTrainPlatform.OnRep_UpdateDockingStatus
struct AFGBuildableTrainPlatform_OnRep_UpdateDockingStatus_Params
{
};

// Function FactoryGame.FGBuildableTrainPlatform.GetDockingStatus
struct AFGBuildableTrainPlatform_GetDockingStatus_Params
{
	ETrainPlatformDockingStatus                        ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableRailroadStation.PerformIsDockedCheck
struct AFGBuildableRailroadStation_PerformIsDockedCheck_Params
{
};

// Function FactoryGame.FGBuildableRailroadStation.OnNameChanged
struct AFGBuildableRailroadStation_OnNameChanged_Params
{
};

// Function FactoryGame.FGBuildableRailroadStation.OnLocomotiveDocked
struct AFGBuildableRailroadStation_OnLocomotiveDocked_Params
{
};

// Function FactoryGame.FGBuildableRailroadStation.OnDockingColliderEndOverlap
struct AFGBuildableRailroadStation_OnDockingColliderEndOverlap_Params
{
	class UPrimitiveComponent*                         OverlappedComponent;                                      // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableRailroadStation.OnDockingColliderBeginOverlap
struct AFGBuildableRailroadStation_OnDockingColliderBeginOverlap_Params
{
	class UPrimitiveComponent*                         OverlappedComp;                                           // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bFromSweep;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  SweepResult;                                              // (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableRailroadStation.GetStationIdentifier
struct AFGBuildableRailroadStation_GetStationIdentifier_Params
{
	class AFGTrainStationIdentifier*                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableRailroadSwitchControl.GetSwitchPosition
struct AFGBuildableRailroadSwitchControl_GetSwitchPosition_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableRailroadTrack.GetSplineComponent
struct AFGBuildableRailroadTrack_GetSplineComponent_Params
{
	class USplineComponent*                            ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBuildableRailroadTrack.GetLength
struct AFGBuildableRailroadTrack_GetLength_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableResourceExtractor.IsStartupComplete
struct AFGBuildableResourceExtractor_IsStartupComplete_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableResourceExtractor.GetResourceNode
struct AFGBuildableResourceExtractor_GetResourceNode_Params
{
	class AFGResourceNode*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableResourceExtractor.GetOutputInventory
struct AFGBuildableResourceExtractor_GetOutputInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBuildableResourceExtractor.GetMiningParticle
struct AFGBuildableResourceExtractor_GetMiningParticle_Params
{
	class UParticleSystem*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableSignWall.SetSignData
struct AFGBuildableSignWall_SetSignData_Params
{
	struct FSignWallData                               SignData;                                                 // (Parm)
	bool                                               bUpdate;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableSignWall.OnRep_SignData
struct AFGBuildableSignWall_OnRep_SignData_Params
{
};

// Function FactoryGame.FGBuildableSignWall.GetSignData
struct AFGBuildableSignWall_GetSignData_Params
{
	struct FSignWallData                               ReturnValue;                                              // (ConstParm, Parm, OutParm, ReturnParm, ReferenceParm)
};

// Function FactoryGame.FGBuildableSpaceElevator.UpgradeTowTruck
struct AFGBuildableSpaceElevator_UpgradeTowTruck_Params
{
};

// Function FactoryGame.FGBuildableSpaceElevator.PayOffFromInventory
struct AFGBuildableSpaceElevator_PayOffFromInventory_Params
{
	class UFGInventoryComponent*                       inventory;                                                // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                inventorySlotIndex;                                       // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableSpaceElevator.LaunchTowTruck
struct AFGBuildableSpaceElevator_LaunchTowTruck_Params
{
};

// Function FactoryGame.FGBuildableSpaceElevator.IsReadyToUpgrade
struct AFGBuildableSpaceElevator_IsReadyToUpgrade_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableSpaceElevator.IsFullyUpgraded
struct AFGBuildableSpaceElevator_IsFullyUpgraded_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableSpaceElevator.GetNextPhaseCost
struct AFGBuildableSpaceElevator_GetNextPhaseCost_Params
{
	TArray<struct FItemAmount>                         out_cost;                                                 // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGBuildableSpaceElevator.GetInputInventory
struct AFGBuildableSpaceElevator_GetInputInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBuildableSplitterSmart.SetSortRuleAt
struct AFGBuildableSplitterSmart_SetSortRuleAt_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	struct FSplitterSortRule                           Rule;                                                     // (Parm)
};

// Function FactoryGame.FGBuildableSplitterSmart.RemoveSortRuleAt
struct AFGBuildableSplitterSmart_RemoveSortRuleAt_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableSplitterSmart.OnRep_SortRules
struct AFGBuildableSplitterSmart_OnRep_SortRules_Params
{
};

// Function FactoryGame.FGBuildableSplitterSmart.IsValidSortRuleAt
struct AFGBuildableSplitterSmart_IsValidSortRuleAt_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableSplitterSmart.GetSortRuleAt
struct AFGBuildableSplitterSmart_GetSortRuleAt_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	struct FSplitterSortRule                           ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGBuildableSplitterSmart.GetNumSortRules
struct AFGBuildableSplitterSmart_GetNumSortRules_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableSplitterSmart.GetMaxNumSortRules
struct AFGBuildableSplitterSmart_GetMaxNumSortRules_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableSplitterSmart.AddSortRule
struct AFGBuildableSplitterSmart_AddSortRule_Params
{
	struct FSplitterSortRule                           Rule;                                                     // (Parm)
};

// Function FactoryGame.FGBuildableStandaloneSign.OnRep_SignData
struct AFGBuildableStandaloneSign_OnRep_SignData_Params
{
};

// Function FactoryGame.FGBuildableStandaloneSign.GetTextScaleFromNormalizedValue
struct AFGBuildableStandaloneSign_GetTextScaleFromNormalizedValue_Params
{
	float                                              Value;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableStandaloneSign.GetSignConstraints
struct AFGBuildableStandaloneSign_GetSignConstraints_Params
{
	struct FSignElementConstraints                     ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGBuildableStandaloneSign.GetCurrentNormalizedTextScale
struct AFGBuildableStandaloneSign_GetCurrentNormalizedTextScale_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableStandaloneSign.GetCurrentNormalizedTextOffsetZ
struct AFGBuildableStandaloneSign_GetCurrentNormalizedTextOffsetZ_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableStorage.GetStorageInventory
struct AFGBuildableStorage_GetStorageInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBuildableSubsystem.setColorSlotSecondary
struct AFGBuildableSubsystem_setColorSlotSecondary_Params
{
	unsigned char                                      Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	struct FColor                                      Color;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableSubsystem.setColorSlotPrimary
struct AFGBuildableSubsystem_setColorSlotPrimary_Params
{
	unsigned char                                      Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	struct FColor                                      Color;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableSubsystem.ReplayBuildingEffects
struct AFGBuildableSubsystem_ReplayBuildingEffects_Params
{
};

// Function FactoryGame.FGBuildableSubsystem.GetTypedBuildable
struct AFGBuildableSubsystem_GetTypedBuildable_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class AFGBuildable*>                        out_buildables;                                           // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGBuildableSubsystem.getColorSlotSecondaryLinear
struct AFGBuildableSubsystem_getColorSlotSecondaryLinear_Params
{
	unsigned char                                      Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableSubsystem.getColorSlotSecondary
struct AFGBuildableSubsystem_getColorSlotSecondary_Params
{
	unsigned char                                      Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	struct FColor                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableSubsystem.getColorSlotPrimaryLinear
struct AFGBuildableSubsystem_getColorSlotPrimaryLinear_Params
{
	unsigned char                                      Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableSubsystem.getColorSlotPrimary
struct AFGBuildableSubsystem_getColorSlotPrimary_Params
{
	unsigned char                                      Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	struct FColor                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableSubsystem.Get
struct AFGBuildableSubsystem_Get_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGBuildableSubsystem*                       ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableTradingPost.UpdateStorageVisibility
struct AFGBuildableTradingPost_UpdateStorageVisibility_Params
{
};

// Function FactoryGame.FGBuildableTradingPost.UpdateMAMVisibility
struct AFGBuildableTradingPost_UpdateMAMVisibility_Params
{
};

// Function FactoryGame.FGBuildableTradingPost.UpdateGeneratorVisibility
struct AFGBuildableTradingPost_UpdateGeneratorVisibility_Params
{
};

// Function FactoryGame.FGBuildableTradingPost.OnTradingPostUpgraded
struct AFGBuildableTradingPost_OnTradingPostUpgraded_Params
{
	int                                                Level;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               suppressBuildEffects;                                     // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableTradingPost.OnRep_NeedPlayingBuildEffect
struct AFGBuildableTradingPost_OnRep_NeedPlayingBuildEffect_Params
{
};

// Function FactoryGame.FGBuildableTradingPost.GetTradingPostLevel
struct AFGBuildableTradingPost_GetTradingPostLevel_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableTradingPost.GetStorageInventory
struct AFGBuildableTradingPost_GetStorageInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBuildableTradingPost.AreChildBuildingsLoaded
struct AFGBuildableTradingPost_AreChildBuildingsLoaded_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableTrainPlatformCargo.Undock
struct AFGBuildableTrainPlatformCargo_Undock_Params
{
};

// Function FactoryGame.FGBuildableTrainPlatformCargo.SetIsInLoadMode
struct AFGBuildableTrainPlatformCargo_SetIsInLoadMode_Params
{
	bool                                               isInLoadMode;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableTrainPlatformCargo.OnTransferComplete
struct AFGBuildableTrainPlatformCargo_OnTransferComplete_Params
{
};

// Function FactoryGame.FGBuildableTrainPlatformCargo.OnCargoPowerStateChanged
struct AFGBuildableTrainPlatformCargo_OnCargoPowerStateChanged_Params
{
	bool                                               HasPower;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildableTrainPlatformCargo.OnBeginUnloadSequence
struct AFGBuildableTrainPlatformCargo_OnBeginUnloadSequence_Params
{
};

// Function FactoryGame.FGBuildableTrainPlatformCargo.OnBeginLoadSequence
struct AFGBuildableTrainPlatformCargo_OnBeginLoadSequence_Params
{
};

// Function FactoryGame.FGBuildableTrainPlatformCargo.IsLoadUnloading
struct AFGBuildableTrainPlatformCargo_IsLoadUnloading_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableTrainPlatformCargo.GetIsInLoadMode
struct AFGBuildableTrainPlatformCargo_GetIsInLoadMode_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableTrainPlatformCargo.GetInventory
struct AFGBuildableTrainPlatformCargo_GetInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBuildableTrainPlatformCargo.GetDockedVehicleOffset
struct AFGBuildableTrainPlatformCargo_GetDockedVehicleOffset_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableTrainPlatformCargo.GetDockedActor
struct AFGBuildableTrainPlatformCargo_GetDockedActor_Params
{
	class AFGRailroadVehicle*                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableTrainPlatformCargo.Dock
struct AFGBuildableTrainPlatformCargo_Dock_Params
{
	class AFGRailroadVehicle*                          Actor;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableWire.GetLength
struct AFGBuildableWire_GetLength_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildableWire.GetConnection
struct AFGBuildableWire_GetConnection_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGCircuitConnectionComponent*               ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBuildCategory.GetCategoryName
struct UFGBuildCategory_GetCategoryName_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGBuildCategory.GetCategoryIcon
struct UFGBuildCategory_GetCategoryIcon_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FSlateBrush                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGItemDescriptor.GetStackSize
struct UFGItemDescriptor_GetStackSize_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGItemDescriptor.GetSmallIcon
struct UFGItemDescriptor_GetSmallIcon_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UTexture2D*                                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGItemDescriptor.GetRadioactiveDecay
struct UFGItemDescriptor_GetRadioactiveDecay_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGItemDescriptor.GetPreviewView
struct UFGItemDescriptor_GetPreviewView_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FItemView                                   out_previewView;                                          // (Parm, OutParm)
};

// Function FactoryGame.FGItemDescriptor.GetItemName
struct UFGItemDescriptor_GetItemName_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGItemDescriptor.GetItemMesh
struct UFGItemDescriptor_GetItemMesh_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UStaticMesh*                                 ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGItemDescriptor.GetItemIcon
struct UFGItemDescriptor_GetItemIcon_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FSlateBrush                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGItemDescriptor.GetItemDescription
struct UFGItemDescriptor_GetItemDescription_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGItemDescriptor.GetIconView
struct UFGItemDescriptor_GetIconView_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FItemView                                   out_itemView;                                             // (Parm, OutParm)
};

// Function FactoryGame.FGItemDescriptor.GetForm
struct UFGItemDescriptor_GetForm_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	EResourceForm                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGItemDescriptor.GetEnergyValue
struct UFGItemDescriptor_GetEnergyValue_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGItemDescriptor.GetBigIcon
struct UFGItemDescriptor_GetBigIcon_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UTexture2D*                                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGItemDescriptor.CanBeDiscarded
struct UFGItemDescriptor_CanBeDiscarded_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildDescriptor.GetSubCategories
struct UFGBuildDescriptor_GetSubCategories_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class UClass*>                              out_subCategories;                                        // (Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function FactoryGame.FGBuildDescriptor.GetBuildMenuPriority
struct UFGBuildDescriptor_GetBuildMenuPriority_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildDescriptor.GetBuildCategory
struct UFGBuildDescriptor_GetBuildCategory_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildGuide.SetBuildGuideStartEnd
struct AFGBuildGuide_SetBuildGuideStartEnd_Params
{
	struct FVector                                     startPoint;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     endPoint;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              meshSize;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildGunState.TickState
struct UFGBuildGunState_TickState_Params
{
	float                                              DeltaTime;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildGunState.SecondaryFire
struct UFGBuildGunState_SecondaryFire_Params
{
};

// Function FactoryGame.FGBuildGunState.ScrollUp
struct UFGBuildGunState_ScrollUp_Params
{
};

// Function FactoryGame.FGBuildGunState.ScrollDown
struct UFGBuildGunState_ScrollDown_Params
{
};

// Function FactoryGame.FGBuildGunState.ResetBuildGunDelay
struct UFGBuildGunState_ResetBuildGunDelay_Params
{
};

// Function FactoryGame.FGBuildGunState.PrimaryFire
struct UFGBuildGunState_PrimaryFire_Params
{
};

// Function FactoryGame.FGBuildGunState.IsActive
struct UFGBuildGunState_IsActive_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildGunState.HasBuildGunDelay
struct UFGBuildGunState_HasBuildGunDelay_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildGunState.HasAuthority
struct UFGBuildGunState_HasAuthority_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildGunState.GetBuildGunDelayPercentage
struct UFGBuildGunState_GetBuildGunDelayPercentage_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildGunState.GetBuildGunDelayMessage
struct UFGBuildGunState_GetBuildGunDelayMessage_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGBuildGunState.GetBuildGun
struct UFGBuildGunState_GetBuildGun_Params
{
	class AFGBuildGun*                                 ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildGunState.EndState
struct UFGBuildGunState_EndState_Params
{
};

// Function FactoryGame.FGBuildGunState.ChangeScrollMode
struct UFGBuildGunState_ChangeScrollMode_Params
{
};

// Function FactoryGame.FGBuildGunState.ChangeNoSnapMode
struct UFGBuildGunState_ChangeNoSnapMode_Params
{
};

// Function FactoryGame.FGBuildGunState.ChangeGuideLinesSnapMode
struct UFGBuildGunState_ChangeGuideLinesSnapMode_Params
{
	bool                                               Enabled;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildGunState.BuildGunDelayIsComplete
struct UFGBuildGunState_BuildGunDelayIsComplete_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildGunState.BeginState
struct UFGBuildGunState_BeginState_Params
{
};

// Function FactoryGame.FGBuildGunState.BeginBuildGunDelay
struct UFGBuildGunState_BeginBuildGunDelay_Params
{
};

// Function FactoryGame.FGEquipment.WasUnEquipped
struct AFGEquipment_WasUnEquipped_Params
{
};

// Function FactoryGame.FGEquipment.WasEquipped
struct AFGEquipment_WasEquipped_Params
{
};

// Function FactoryGame.FGEquipment.UnEquip
struct AFGEquipment_UnEquip_Params
{
};

// Function FactoryGame.FGEquipment.ShouldShowStinger
struct AFGEquipment_ShouldShowStinger_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEquipment.Server_UpdateAttachmentUseState
struct AFGEquipment_Server_UpdateAttachmentUseState_Params
{
	int                                                newUseState;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGEquipment.Server_ChargeForUse
struct AFGEquipment_Server_ChargeForUse_Params
{
};

// Function FactoryGame.FGEquipment.IsLocalInstigator
struct AFGEquipment_IsLocalInstigator_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEquipment.IsEquipped
struct AFGEquipment_IsEquipped_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEquipment.GetSecondaryAttachment
struct AFGEquipment_GetSecondaryAttachment_Params
{
	class AFGEquipmentAttachment*                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEquipment.GetInstigatorCharacter
struct AFGEquipment_GetInstigatorCharacter_Params
{
	class AFGCharacterPlayer*                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEquipment.GetEquipmentSlot
struct AFGEquipment_GetEquipmentSlot_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	EEquipmentSlot                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEquipment.GetAttachment
struct AFGEquipment_GetAttachment_Params
{
	class AFGEquipmentAttachment*                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEquipment.Equip
struct AFGEquipment_Equip_Params
{
	class AFGCharacterPlayer*                          Character;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGEquipment.DidNotAffordUse
struct AFGEquipment_DidNotAffordUse_Params
{
};

// Function FactoryGame.FGEquipment.ChargeForUse
struct AFGEquipment_ChargeForUse_Params
{
};

// Function FactoryGame.FGEquipment.CanAffordUse
struct AFGEquipment_CanAffordUse_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEquipment.AdjustDamage
struct AFGEquipment_AdjustDamage_Params
{
	float                                              damageAmount;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildGun.Server_SecondaryFire
struct AFGBuildGun_Server_SecondaryFire_Params
{
};

// Function FactoryGame.FGBuildGun.Server_ScrollUp
struct AFGBuildGun_Server_ScrollUp_Params
{
};

// Function FactoryGame.FGBuildGun.Server_ScrollMode
struct AFGBuildGun_Server_ScrollMode_Params
{
};

// Function FactoryGame.FGBuildGun.Server_ScrollDown
struct AFGBuildGun_Server_ScrollDown_Params
{
};

// Function FactoryGame.FGBuildGun.Server_PrimaryFire
struct AFGBuildGun_Server_PrimaryFire_Params
{
};

// Function FactoryGame.FGBuildGun.Server_NoSnapMode
struct AFGBuildGun_Server_NoSnapMode_Params
{
};

// Function FactoryGame.FGBuildGun.Server_GotoState
struct AFGBuildGun_Server_GotoState_Params
{
	EBuildGunState                                     State;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildGun.Server_GotoBuildState
struct AFGBuildGun_Server_GotoBuildState_Params
{
	class UClass*                                      Recipe;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildGun.IsInState
struct AFGBuildGun_IsInState_Params
{
	EBuildGunState                                     inState;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildGun.GotoMenuState
struct AFGBuildGun_GotoMenuState_Params
{
};

// Function FactoryGame.FGBuildGun.GotoDismantleState
struct AFGBuildGun_GotoDismantleState_Params
{
};

// Function FactoryGame.FGBuildGun.GotoBuildState
struct AFGBuildGun_GotoBuildState_Params
{
	class UClass*                                      Recipe;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildGun.GetInventory
struct AFGBuildGun_GetInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGBuildGun.GetCurrentBuildGunDelayPercentage
struct AFGBuildGun_GetCurrentBuildGunDelayPercentage_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildGun.GetCurrentBuildGunDelayMessage
struct AFGBuildGun_GetCurrentBuildGunDelayMessage_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGBuildGun.GetCostForRecipe
struct AFGBuildGun_GetCostForRecipe_Params
{
	class UClass*                                      Recipe;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FItemAmount>                         ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGBuildGun.GetBuildGunStateFor
struct AFGBuildGun_GetBuildGunStateFor_Params
{
	EBuildGunState                                     gunState;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGBuildGunState*                            ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildGun.GetAvailableRecipes
struct AFGBuildGun_GetAvailableRecipes_Params
{
	TArray<class UClass*>                              out_recipes;                                              // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGBuildGun.CompareActiveRecipeTo
struct AFGBuildGun_CompareActiveRecipeTo_Params
{
	class UClass*                                      Recipe;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEquipmentAttachment.PlayUseEffect
struct AFGEquipmentAttachment_PlayUseEffect_Params
{
	struct FVector                                     UseLocation;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGEquipmentAttachment.PlayDetachEffects3P
struct AFGEquipmentAttachment_PlayDetachEffects3P_Params
{
};

// Function FactoryGame.FGEquipmentAttachment.PlayAttachEffects3P
struct AFGEquipmentAttachment_PlayAttachEffects3P_Params
{
};

// Function FactoryGame.FGEquipmentAttachment.OnRep_UseLocationUpdated
struct AFGEquipmentAttachment_OnRep_UseLocationUpdated_Params
{
};

// Function FactoryGame.FGEquipmentAttachment.OnRep_OnAnimationStateUpdated
struct AFGEquipmentAttachment_OnRep_OnAnimationStateUpdated_Params
{
};

// Function FactoryGame.FGEquipmentAttachment.OnDetach
struct AFGEquipmentAttachment_OnDetach_Params
{
};

// Function FactoryGame.FGEquipmentAttachment.OnAttachmentUseStateUpdated
struct AFGEquipmentAttachment_OnAttachmentUseStateUpdated_Params
{
	int                                                newUseState;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGEquipmentAttachment.OnAttach
struct AFGEquipmentAttachment_OnAttach_Params
{
};

// Function FactoryGame.FGEquipmentAttachment.IsAttached
struct AFGEquipmentAttachment_IsAttached_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEquipmentAttachment.GetEquippedSlot
struct AFGEquipmentAttachment_GetEquippedSlot_Params
{
	EEquipmentSlot                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEquipmentAttachment.GetAttachSocket
struct AFGEquipmentAttachment_GetAttachSocket_Params
{
	struct FName                                       ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEquipmentAttachment.GetAttachedTo
struct AFGEquipmentAttachment_GetAttachedTo_Params
{
	class AFGCharacterPlayer*                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildGunStateBuild.ResetHologram
struct UFGBuildGunStateBuild_ResetHologram_Params
{
};

// Function FactoryGame.FGBuildGunStateBuild.OnResetHologram
struct UFGBuildGunStateBuild_OnResetHologram_Params
{
};

// Function FactoryGame.FGBuildGunStateBuild.OnRep_Hologram
struct UFGBuildGunStateBuild_OnRep_Hologram_Params
{
};

// Function FactoryGame.FGBuildGunStateBuild.OnMultiStepPlacement
struct UFGBuildGunStateBuild_OnMultiStepPlacement_Params
{
	bool                                               isFinalStep;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildGunStateBuild.OnActiveDescriptorChanged
struct UFGBuildGunStateBuild_OnActiveDescriptorChanged_Params
{
};

// Function FactoryGame.FGBuildGunStateBuild.GetHologramCost
struct UFGBuildGunStateBuild_GetHologramCost_Params
{
	TArray<struct FItemAmount>                         ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGBuildGunStateBuild.GetHologram
struct UFGBuildGunStateBuild_GetHologram_Params
{
	class AFGHologram*                                 ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildGunStateBuild.GetDescriptor
struct UFGBuildGunStateBuild_GetDescriptor_Params
{
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildGunStateBuild.EndClearanceOverlap
struct UFGBuildGunStateBuild_EndClearanceOverlap_Params
{
	class UPrimitiveComponent*                         OverlappedComponent;                                      // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildGunStateBuild.Client_OnResetHologram
struct UFGBuildGunStateBuild_Client_OnResetHologram_Params
{
};

// Function FactoryGame.FGBuildGunStateBuild.Client_OnBuildableConstructed
struct UFGBuildGunStateBuild_Client_OnBuildableConstructed_Params
{
	class UClass*                                      Desc;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildGunStateBuild.BeginClearanceOverlap
struct UFGBuildGunStateBuild_BeginClearanceOverlap_Params
{
	class UPrimitiveComponent*                         OverlappedComponent;                                      // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bFromSweep;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  SweepResult;                                              // (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildGunStateDismantle.Server_PeekAtDismantleRefund
struct UFGBuildGunStateDismantle_Server_PeekAtDismantleRefund_Params
{
	class AActor*                                      selected;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildGunStateDismantle.Server_DismantleActor
struct UFGBuildGunStateDismantle_Server_DismantleActor_Params
{
	class AActor*                                      actorToDismantle;                                         // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGBuildGunStateDismantle.OnStopDismantle
struct UFGBuildGunStateDismantle_OnStopDismantle_Params
{
};

// Function FactoryGame.FGBuildGunStateDismantle.OnStartDismantle
struct UFGBuildGunStateDismantle_OnStartDismantle_Params
{
};

// Function FactoryGame.FGBuildGunStateDismantle.OnRep_PeekDismantleRefund
struct UFGBuildGunStateDismantle_OnRep_PeekDismantleRefund_Params
{
};

// Function FactoryGame.FGBuildGunStateDismantle.GetSelectedActor
struct UFGBuildGunStateDismantle_GetSelectedActor_Params
{
	class AActor*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildGunStateDismantle.GetPeekDismantleRefund
struct UFGBuildGunStateDismantle_GetPeekDismantleRefund_Params
{
	TArray<struct FInventoryStack>                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGBuildGunStateDismantle.GetDismantleRefund
struct UFGBuildGunStateDismantle_GetDismantleRefund_Params
{
	TArray<struct FInventoryStack>                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGBuildGunStateDismantle.CanDismantle
struct UFGBuildGunStateDismantle_CanDismantle_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildingDescriptor.GetPowerProduction
struct UFGBuildingDescriptor_GetPowerProduction_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildingDescriptor.GetPowerConsumption
struct UFGBuildingDescriptor_GetPowerConsumption_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGBuildingDescriptor.GetBuildableClass
struct UFGBuildingDescriptor_GetBuildableClass_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGButtonWidget.SetButton
struct UFGButtonWidget_SetButton_Params
{
	class UButton*                                     inButton;                                                 // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGWeapon.Server_StartPrimaryFire
struct AFGWeapon_Server_StartPrimaryFire_Params
{
};

// Function FactoryGame.FGWeapon.Server_Reload
struct AFGWeapon_Server_Reload_Params
{
};

// Function FactoryGame.FGWeapon.Server_EndPrimaryFire
struct AFGWeapon_Server_EndPrimaryFire_Params
{
};

// Function FactoryGame.FGWeapon.PlayReloadEffects
struct AFGWeapon_PlayReloadEffects_Params
{
};

// Function FactoryGame.FGWeapon.PlayFireReleasedEffects
struct AFGWeapon_PlayFireReleasedEffects_Params
{
};

// Function FactoryGame.FGWeapon.PlayFireEffect
struct AFGWeapon_PlayFireEffect_Params
{
};

// Function FactoryGame.FGWeapon.PlayFailedToFireEffects
struct AFGWeapon_PlayFailedToFireEffects_Params
{
};

// Function FactoryGame.FGWeapon.HasAmmunition
struct AFGWeapon_HasAmmunition_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWeapon.GetSpareAmmunition
struct AFGWeapon_GetSpareAmmunition_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWeapon.GetReloadTimeLeft
struct AFGWeapon_GetReloadTimeLeft_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWeapon.GetMagSize
struct AFGWeapon_GetMagSize_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWeapon.GetIsReloading
struct AFGWeapon_GetIsReloading_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWeapon.GetIsFiring
struct AFGWeapon_GetIsFiring_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWeapon.GetCurrentAmmo
struct AFGWeapon_GetCurrentAmmo_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWeapon.GetAssosiatedHud
struct AFGWeapon_GetAssosiatedHud_Params
{
	class AFGHUD*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWeapon.FireAmmunition
struct AFGWeapon_FireAmmunition_Params
{
};

// Function FactoryGame.FGWeapon.CanReload
struct AFGWeapon_CanReload_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWeapon.ActualReload
struct AFGWeapon_ActualReload_Params
{
};

// Function FactoryGame.FGC4Dispenser.Server_SpawnC4
struct AFGC4Dispenser_Server_SpawnC4_Params
{
	int                                                throwForce;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGC4Dispenser.Server_DetonatePressed
struct AFGC4Dispenser_Server_DetonatePressed_Params
{
};

// Function FactoryGame.FGC4Dispenser.GetChargePct
struct AFGC4Dispenser_GetChargePct_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGC4Explosive.PlayExplosionEffects
struct AFGC4Explosive_PlayExplosionEffects_Params
{
};

// Function FactoryGame.FGC4Explosive.OnRep_IsDetonated
struct AFGC4Explosive_OnRep_IsDetonated_Params
{
};

// Function FactoryGame.FGCameraModifierLimitLook.SetDefaultLookRotator
struct UFGCameraModifierLimitLook_SetDefaultLookRotator_Params
{
	struct FRotator                                    inRotator;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCameraModifierLimitLook.GetDefaultLookRotator
struct UFGCameraModifierLimitLook_GetDefaultLookRotator_Params
{
	struct FRotator                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCentralStorageContainer.AddToCentralStorageSubsystem
struct AFGCentralStorageContainer_AddToCentralStorageSubsystem_Params
{
};

// Function FactoryGame.FGCentralStorageSubsystem.RemoveItemsFromCentralStorage
struct AFGCentralStorageSubsystem_RemoveItemsFromCentralStorage_Params
{
	class UClass*                                      ItemClass;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                Num;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCentralStorageSubsystem.IsCentralStorageBuilt
struct AFGCentralStorageSubsystem_IsCentralStorageBuilt_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCentralStorageSubsystem.GetNumItemsFromCentralStorage
struct AFGCentralStorageSubsystem_GetNumItemsFromCentralStorage_Params
{
	class UClass*                                      ItemClass;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCentralStorageSubsystem.GetCentralStorageContainers
struct AFGCentralStorageSubsystem_GetCentralStorageContainers_Params
{
	TArray<class AFGCentralStorageContainer*>          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGCentralStorageSubsystem.Get
struct AFGCentralStorageSubsystem_Get_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGCentralStorageSubsystem*                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGChainsaw.Server_StopSawing
struct AFGChainsaw_Server_StopSawing_Params
{
};

// Function FactoryGame.FGChainsaw.Server_StartSawing
struct AFGChainsaw_Server_StartSawing_Params
{
};

// Function FactoryGame.FGChainsaw.Server_RemoveChainsawedObject
struct AFGChainsaw_Server_RemoveChainsawedObject_Params
{
	class USceneComponent*                             sawingComponent;                                          // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FTransform                                  foliageToRemoveTransform;                                 // (Parm, IsPlainOldData)
	struct FVector                                     effectLocation;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGChainsaw.SawProgress
struct AFGChainsaw_SawProgress_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGChainsaw.IsSawing
struct AFGChainsaw_IsSawing_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGChainsaw.IsSawEngaged
struct AFGChainsaw_IsSawEngaged_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGChainsaw.HasAnyFuel
struct AFGChainsaw_HasAnyFuel_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGChainsaw.GetFuelClass
struct AFGChainsaw_GetFuelClass_Params
{
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGChainsaw.CanStartSawing
struct AFGChainsaw_CanStartSawing_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGChainsaw.BroadcastPickup
struct AFGChainsaw_BroadcastPickup_Params
{
	TArray<struct FPickedUpInstance>                   pickups;                                                  // (ConstParm, Parm, ZeroConstructor, ReferenceParm)
	class AFGFoliagePickup*                            instigatorPlayer;                                         // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGChainsawableInterface.IsChainsawable
struct UFGChainsawableInterface_IsChainsawable_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGChainsawableInterface.GetMeshComponent
struct UFGChainsawableInterface_GetMeshComponent_Params
{
	class UStaticMeshComponent*                        ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.TraceForGround
struct AFGCharacterBase_TraceForGround_Params
{
	struct FVector                                     TraceStart;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     TraceEnd;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  out_hitResult;                                            // (Parm, OutParm, IsPlainOldData)
	float                                              out_waterDepth;                                           // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.SetFallDamageOverride
struct AFGCharacterBase_SetFallDamageOverride_Params
{
	class UCurveFloat*                                 fallDamageCurveOverride;                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.ReceiveDied
struct AFGCharacterBase_ReceiveDied_Params
{
};

// Function FactoryGame.FGCharacterBase.ReceivedAdjustDamage
struct AFGCharacterBase_ReceivedAdjustDamage_Params
{
	float                                              damageAmount;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.RagdollCharacter
struct AFGCharacterBase_RagdollCharacter_Params
{
	bool                                               newRagdoll;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.PushedByVehicle
struct AFGCharacterBase_PushedByVehicle_Params
{
	class AFGVehicle*                                  Vehicle;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     pushVelocity;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.PlayFootstepEffect
struct AFGCharacterBase_PlayFootstepEffect_Params
{
	int                                                footDown;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               PlaySound;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.OnTakeRadialDamage
struct AFGCharacterBase_OnTakeRadialDamage_Params
{
	class AActor*                                      damagedActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Damage;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     HitLocation;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  HitInfo;                                                  // (Parm, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.OnTakePointDamage
struct AFGCharacterBase_OnTakePointDamage_Params
{
	class AActor*                                      damagedActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Damage;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     HitLocation;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         HitComponent;                                             // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FName                                       BoneName;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ShotFromDirection;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.OnTakeDamage
struct AFGCharacterBase_OnTakeDamage_Params
{
	class AActor*                                      damagedActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              damageAmount;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.OnRep_IsRagdolled
struct AFGCharacterBase_OnRep_IsRagdolled_Params
{
};

// Function FactoryGame.FGCharacterBase.NotifyOnWeakspotHit
struct AFGCharacterBase_NotifyOnWeakspotHit_Params
{
};

// Function FactoryGame.FGCharacterBase.NotifyOnTakeRadialDamage
struct AFGCharacterBase_NotifyOnTakeRadialDamage_Params
{
	class AActor*                                      damagedActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Damage;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.NotifyOnTakePointDamage
struct AFGCharacterBase_NotifyOnTakePointDamage_Params
{
	class AActor*                                      damagedActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Damage;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     HitLocation;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         HitComponent;                                             // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FName                                       BoneName;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ShotFromDirection;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.NotifyOnTakeDamage
struct AFGCharacterBase_NotifyOnTakeDamage_Params
{
	class AActor*                                      damagedActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              damageAmount;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.IsRagdolled
struct AFGCharacterBase_IsRagdolled_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.IsAliveAndWell
struct AFGCharacterBase_IsAliveAndWell_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.GetTakeDamageSound
struct AFGCharacterBase_GetTakeDamageSound_Params
{
	class UAkAudioEvent*                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.GetTakeDamageParticle
struct AFGCharacterBase_GetTakeDamageParticle_Params
{
	class UParticleSystem*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.GetMesh3P
struct AFGCharacterBase_GetMesh3P_Params
{
	class USkeletalMeshComponent*                      ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.GetHealthComponent
struct AFGCharacterBase_GetHealthComponent_Params
{
	class UFGHealthComponent*                          ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.GetFallDamageDamageType
struct AFGCharacterBase_GetFallDamageDamageType_Params
{
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.GetDeathSound
struct AFGCharacterBase_GetDeathSound_Params
{
	class UAkAudioEvent*                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.Died
struct AFGCharacterBase_Died_Params
{
	class AActor*                                      thisActor;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.CheckIfShouldDestroy
struct AFGCharacterBase_CheckIfShouldDestroy_Params
{
};

// Function FactoryGame.FGCharacterBase.CalculateFallDamage
struct AFGCharacterBase_CalculateFallDamage_Params
{
	float                                              zSpeed;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterBase.AdjustDamage
struct AFGCharacterBase_AdjustDamage_Params
{
	class AActor*                                      damagedActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              damageAmount;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterMovementComponent.ServerSetHookLocation
struct UFGCharacterMovementComponent_ServerSetHookLocation_Params
{
	struct FVector                                     hookLocation;                                             // (ConstParm, Parm, ZeroConstructor, ReferenceParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterMovementComponent.GetWantsToSprint
struct UFGCharacterMovementComponent_GetWantsToSprint_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterMovementComponent.GetOnLadder
struct UFGCharacterMovementComponent_GetOnLadder_Params
{
	class UFGLadderComponent*                          ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGCharacterMovementComponent.GetIsSprinting
struct UFGCharacterMovementComponent_GetIsSprinting_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.UsePreferredCameraMode
struct AFGCharacterPlayer_UsePreferredCameraMode_Params
{
};

// Function FactoryGame.FGCharacterPlayer.UnequipEquipment
struct AFGCharacterPlayer_UnequipEquipment_Params
{
	class AFGEquipment*                                equipment;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.ToggleCameraMode
struct AFGCharacterPlayer_ToggleCameraMode_Params
{
};

// Function FactoryGame.FGCharacterPlayer.ToggleBuildGun
struct AFGCharacterPlayer_ToggleBuildGun_Params
{
};

// Function FactoryGame.FGCharacterPlayer.StopReceivingRadiation
struct AFGCharacterPlayer_StopReceivingRadiation_Params
{
};

// Function FactoryGame.FGCharacterPlayer.StopFreeRotate3P
struct AFGCharacterPlayer_StopFreeRotate3P_Params
{
};

// Function FactoryGame.FGCharacterPlayer.StopFocusAim
struct AFGCharacterPlayer_StopFocusAim_Params
{
};

// Function FactoryGame.FGCharacterPlayer.StartReceivingRadiation
struct AFGCharacterPlayer_StartReceivingRadiation_Params
{
};

// Function FactoryGame.FGCharacterPlayer.StartFreeRotate3P
struct AFGCharacterPlayer_StartFreeRotate3P_Params
{
};

// Function FactoryGame.FGCharacterPlayer.StartFocusAim
struct AFGCharacterPlayer_StartFocusAim_Params
{
};

// Function FactoryGame.FGCharacterPlayer.SpawnInitialGear
struct AFGCharacterPlayer_SpawnInitialGear_Params
{
};

// Function FactoryGame.FGCharacterPlayer.SnapSpringArmToDesiredLocation
struct AFGCharacterPlayer_SnapSpringArmToDesiredLocation_Params
{
};

// Function FactoryGame.FGCharacterPlayer.SetWantSprintBobbing
struct AFGCharacterPlayer_SetWantSprintBobbing_Params
{
	bool                                               wantBobbing;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.SetThirdPersonMode
struct AFGCharacterPlayer_SetThirdPersonMode_Params
{
};

// Function FactoryGame.FGCharacterPlayer.SetRadiationImmunity
struct AFGCharacterPlayer_SetRadiationImmunity_Params
{
	float                                              newImmunity;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.SetMeshVisibility
struct AFGCharacterPlayer_SetMeshVisibility_Params
{
	bool                                               IsFirstPerson;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.SetFirstPersonMode
struct AFGCharacterPlayer_SetFirstPersonMode_Params
{
};

// Function FactoryGame.FGCharacterPlayer.SetCameraMode
struct AFGCharacterPlayer_SetCameraMode_Params
{
	ECameraMode                                        newCameraMode;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.Server_UnequipEquipment
struct AFGCharacterPlayer_Server_UnequipEquipment_Params
{
	class AFGEquipment*                                newEquipment;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.Server_ToggleSwitchControl
struct AFGCharacterPlayer_Server_ToggleSwitchControl_Params
{
	class AFGBuildableRailroadSwitchControl*           switchControl;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.Server_RevivePlayer
struct AFGCharacterPlayer_Server_RevivePlayer_Params
{
	class AFGCharacterPlayer*                          playerToRevive;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.Server_PickUpItem
struct AFGCharacterPlayer_Server_PickUpItem_Params
{
	class AFGItemPickup*                               itemPickup;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.Server_OnUseReleased
struct AFGCharacterPlayer_Server_OnUseReleased_Params
{
};

// Function FactoryGame.FGCharacterPlayer.Server_OnUse
struct AFGCharacterPlayer_Server_OnUse_Params
{
};

// Function FactoryGame.FGCharacterPlayer.Server_EquipEquipment
struct AFGCharacterPlayer_Server_EquipEquipment_Params
{
	class AFGEquipment*                                newEquipment;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.Server_CycleHandEquipmentPressed
struct AFGCharacterPlayer_Server_CycleHandEquipmentPressed_Params
{
	int                                                dir;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.PlayPickupEffects
struct AFGCharacterPlayer_PlayPickupEffects_Params
{
};

// Function FactoryGame.FGCharacterPlayer.OnSpawnDeathMarker
struct AFGCharacterPlayer_OnSpawnDeathMarker_Params
{
};

// Function FactoryGame.FGCharacterPlayer.OnReviveComplete
struct AFGCharacterPlayer_OnReviveComplete_Params
{
};

// Function FactoryGame.FGCharacterPlayer.OnRep_RadiationIntensity
struct AFGCharacterPlayer_OnRep_RadiationIntensity_Params
{
};

// Function FactoryGame.FGCharacterPlayer.OnRep_PickupCounter
struct AFGCharacterPlayer_OnRep_PickupCounter_Params
{
};

// Function FactoryGame.FGCharacterPlayer.OnRep_InRadioactiveZone
struct AFGCharacterPlayer_OnRep_InRadioactiveZone_Params
{
};

// Function FactoryGame.FGCharacterPlayer.OnRep_DrivenVehicle
struct AFGCharacterPlayer_OnRep_DrivenVehicle_Params
{
};

// Function FactoryGame.FGCharacterPlayer.OnRep_ActiveEquipments
struct AFGCharacterPlayer_OnRep_ActiveEquipments_Params
{
};

// Function FactoryGame.FGCharacterPlayer.OnRep_ActiveAttachments
struct AFGCharacterPlayer_OnRep_ActiveAttachments_Params
{
};

// Function FactoryGame.FGCharacterPlayer.OnReceiveRadiationStop
struct AFGCharacterPlayer_OnReceiveRadiationStop_Params
{
};

// Function FactoryGame.FGCharacterPlayer.OnReceiveRadiationStart
struct AFGCharacterPlayer_OnReceiveRadiationStart_Params
{
};

// Function FactoryGame.FGCharacterPlayer.OnRadiationIntensityUpdated
struct AFGCharacterPlayer_OnRadiationIntensityUpdated_Params
{
	float                                              radiationIntensity;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              radiationImmunity;                                        // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.OnItemAddedToInventory
struct AFGCharacterPlayer_OnItemAddedToInventory_Params
{
	class UClass*                                      ItemClass;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                numAdded;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.OnInventorySlotsUnlocked
struct AFGCharacterPlayer_OnInventorySlotsUnlocked_Params
{
	int                                                newUnlockedSlots;                                         // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.OnDisabledInputGateChanged
struct AFGCharacterPlayer_OnDisabledInputGateChanged_Params
{
	struct FDisabledInputGate                          NewValue;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.OnArmsSlotsUnlocked
struct AFGCharacterPlayer_OnArmsSlotsUnlocked_Params
{
	int                                                newUnlockedSlots;                                         // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.IsFirstPerson
struct AFGCharacterPlayer_IsFirstPerson_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.IsDrivingVehicle
struct AFGCharacterPlayer_IsDrivingVehicle_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.IsBuildGunEquipped
struct AFGCharacterPlayer_IsBuildGunEquipped_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.HotKeyRecipe
struct AFGCharacterPlayer_HotKeyRecipe_Params
{
	class UClass*                                      Recipe;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.HotKeyDismantle
struct AFGCharacterPlayer_HotKeyDismantle_Params
{
};

// Function FactoryGame.FGCharacterPlayer.GetWantSprintBobbing
struct AFGCharacterPlayer_GetWantSprintBobbing_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetUseDistance
struct AFGCharacterPlayer_GetUseDistance_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetTrashSlot
struct AFGCharacterPlayer_GetTrashSlot_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetSpringArmComponent
struct AFGCharacterPlayer_GetSpringArmComponent_Params
{
	class USpringArmComponent*                         ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetReviveProgress
struct AFGCharacterPlayer_GetReviveProgress_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetResourceScanner
struct AFGCharacterPlayer_GetResourceScanner_Params
{
	class AFGResourceScanner*                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetResourceMiner
struct AFGCharacterPlayer_GetResourceMiner_Params
{
	class AFGResourceMiner*                            ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetRadiationIntensity
struct AFGCharacterPlayer_GetRadiationIntensity_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetRadiationImmunity
struct AFGCharacterPlayer_GetRadiationImmunity_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetRadiationDamageAngle
struct AFGCharacterPlayer_GetRadiationDamageAngle_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetPickupProgress
struct AFGCharacterPlayer_GetPickupProgress_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetOutline
struct AFGCharacterPlayer_GetOutline_Params
{
	class UFGOutlineComponent*                         ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetMesh1P
struct AFGCharacterPlayer_GetMesh1P_Params
{
	class USkeletalMeshComponent*                      ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetInventoryDropLocation
struct AFGCharacterPlayer_GetInventoryDropLocation_Params
{
	class UFGInventoryComponent*                       component;                                                // (ConstParm, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FInventoryStack                             stack;                                                    // (Parm)
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetInventory
struct AFGCharacterPlayer_GetInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetEquipmentSlot
struct AFGCharacterPlayer_GetEquipmentSlot_Params
{
	EEquipmentSlot                                     Slot;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGInventoryComponentEquipment*              ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetEquipmentInSlot
struct AFGCharacterPlayer_GetEquipmentInSlot_Params
{
	EEquipmentSlot                                     Slot;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGEquipment*                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetDrivenVehicle
struct AFGCharacterPlayer_GetDrivenVehicle_Params
{
	class AFGDriveablePawn*                            ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetDesiredWalkHeadBobShake
struct AFGCharacterPlayer_GetDesiredWalkHeadBobShake_Params
{
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetDesiredSprintHeadBobShake
struct AFGCharacterPlayer_GetDesiredSprintHeadBobShake_Params
{
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetCurrentLadderComponent
struct AFGCharacterPlayer_GetCurrentLadderComponent_Params
{
	class UFGLadderComponent*                          ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetCameraMode
struct AFGCharacterPlayer_GetCameraMode_Params
{
	ECameraMode                                        ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetCameraComponent
struct AFGCharacterPlayer_GetCameraComponent_Params
{
	class UCameraComponent*                            ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetBuildGun
struct AFGCharacterPlayer_GetBuildGun_Params
{
	class AFGBuildGun*                                 ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetBestUsableActor
struct AFGCharacterPlayer_GetBestUsableActor_Params
{
	class AActor*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetBeltSlot
struct AFGCharacterPlayer_GetBeltSlot_Params
{
	class UFGInventoryComponentBeltSlot*               ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetActiveEquipments
struct AFGCharacterPlayer_GetActiveEquipments_Params
{
	TArray<class AFGEquipment*>                        ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGCharacterPlayer.GetActiveEquipmentItem
struct AFGCharacterPlayer_GetActiveEquipmentItem_Params
{
	EEquipmentSlot                                     Slot;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	struct FInventoryItem                              ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGCharacterPlayer.GetActiveCrosshairState
struct AFGCharacterPlayer_GetActiveCrosshairState_Params
{
	ECrosshairState                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.GetActiveAttachments
struct AFGCharacterPlayer_GetActiveAttachments_Params
{
	TArray<class AFGEquipmentAttachment*>              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGCharacterPlayer.EquipEquipment
struct AFGCharacterPlayer_EquipEquipment_Params
{
	class AFGEquipment*                                equipment;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCharacterPlayer.Client_Revived
struct AFGCharacterPlayer_Client_Revived_Params
{
};

// Function FactoryGame.FGCharacterPlayer.CameraZoomOut
struct AFGCharacterPlayer_CameraZoomOut_Params
{
};

// Function FactoryGame.FGCharacterPlayer.CameraZoomIn
struct AFGCharacterPlayer_CameraZoomIn_Params
{
};

// Function FactoryGame.FGCharacterPlayer.AddRadiationImmunity
struct AFGCharacterPlayer_AddRadiationImmunity_Params
{
	float                                              toAdd;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGChatManager.Multicast_BroadcastChatMessage
struct AFGChatManager_Multicast_BroadcastChatMessage_Params
{
	struct FChatMessageStruct                          newMessage;                                               // (ConstParm, Parm, ReferenceParm)
};

// Function FactoryGame.FGChatManager.GetReceivedChatMessages
struct AFGChatManager_GetReceivedChatMessages_Params
{
	TArray<struct FChatMessageStruct>                  out_messages;                                             // (Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function FactoryGame.FGChatManager.GetMessageVisibleDuration
struct AFGChatManager_GetMessageVisibleDuration_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGChatManager.GetMaxNumMessagesInHistory
struct AFGChatManager_GetMaxNumMessagesInHistory_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGChatManager.GetChatMessageName
struct AFGChatManager_GetChatMessageName_Params
{
	struct FChatMessageStruct                          inMessage;                                                // (ConstParm, Parm, OutParm, ReferenceParm)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGChatManager.GetChatMessageColor
struct AFGChatManager_GetChatMessageColor_Params
{
	struct FChatMessageStruct                          inMessage;                                                // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGChatManager.Get
struct AFGChatManager_Get_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGChatManager*                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.VisitAllMapAreas
struct UFGCheatManager_VisitAllMapAreas_Params
{
};

// Function FactoryGame.FGCheatManager.UpdateSessionToOSS
struct UFGCheatManager_UpdateSessionToOSS_Params
{
};

// Function FactoryGame.FGCheatManager.TurboMode
struct UFGCheatManager_TurboMode_Params
{
	bool                                               Enabled;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.TriggerPresenceUpdate
struct UFGCheatManager_TriggerPresenceUpdate_Params
{
};

// Function FactoryGame.FGCheatManager.ToggleCameraMode
struct UFGCheatManager_ToggleCameraMode_Params
{
};

// Function FactoryGame.FGCheatManager.ToggleAudioLandingDebug
struct UFGCheatManager_ToggleAudioLandingDebug_Params
{
};

// Function FactoryGame.FGCheatManager.ToggleAudioDebug
struct UFGCheatManager_ToggleAudioDebug_Params
{
};

// Function FactoryGame.FGCheatManager.TestSharedInventoryPtr
struct UFGCheatManager_TestSharedInventoryPtr_Params
{
};

// Function FactoryGame.FGCheatManager.SplitAllConveyors
struct UFGCheatManager_SplitAllConveyors_Params
{
};

// Function FactoryGame.FGCheatManager.ShowSequenceList
struct UFGCheatManager_ShowSequenceList_Params
{
};

// Function FactoryGame.FGCheatManager.ShowFactoryOnly
struct UFGCheatManager_ShowFactoryOnly_Params
{
	bool                                               environmentHidden;                                        // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.SetTradingPostLevel
struct UFGCheatManager_SetTradingPostLevel_Params
{
	int                                                inLevel;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.SetTimeSpeedMultiplier
struct UFGCheatManager_SetTimeSpeedMultiplier_Params
{
	float                                              Speed;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.SetTimeOfDay
struct UFGCheatManager_SetTimeOfDay_Params
{
	int                                                hour;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                minute;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.SetSlomo
struct UFGCheatManager_SetSlomo_Params
{
	float                                              Slomo;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.SetRandomDebugStartingPoint
struct UFGCheatManager_SetRandomDebugStartingPoint_Params
{
};

// Function FactoryGame.FGCheatManager.SetGamePhase
struct UFGCheatManager_SetGamePhase_Params
{
	TEnumAsByte<EGamePhase>                            phase;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.SetFactoryDetailReplication
struct UFGCheatManager_SetFactoryDetailReplication_Params
{
	bool                                               enable;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.SetDebugStartingPoint
struct UFGCheatManager_SetDebugStartingPoint_Params
{
	struct FName                                       startingPoint;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.SetAITickDistance
struct UFGCheatManager_SetAITickDistance_Params
{
	float                                              Distance;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.SendInviteToFriend
struct UFGCheatManager_SendInviteToFriend_Params
{
	class FString                                      friendName;                                               // (Parm, ZeroConstructor)
};

// Function FactoryGame.FGCheatManager.SaveWithNewSessionName
struct UFGCheatManager_SaveWithNewSessionName_Params
{
	class FString                                      saveName;                                                 // (Parm, ZeroConstructor)
	class FString                                      SessionName;                                              // (Parm, ZeroConstructor)
};

// Function FactoryGame.FGCheatManager.RunDebugMetric
struct UFGCheatManager_RunDebugMetric_Params
{
};

// Function FactoryGame.FGCheatManager.ResetSchematics
struct UFGCheatManager_ResetSchematics_Params
{
};

// Function FactoryGame.FGCheatManager.ResetHubTutorial
struct UFGCheatManager_ResetHubTutorial_Params
{
};

// Function FactoryGame.FGCheatManager.ResetFuses
struct UFGCheatManager_ResetFuses_Params
{
};

// Function FactoryGame.FGCheatManager.ReplayBuildingEffects
struct UFGCheatManager_ReplayBuildingEffects_Params
{
};

// Function FactoryGame.FGCheatManager.RemoveAllFoliage
struct UFGCheatManager_RemoveAllFoliage_Params
{
	int                                                maxNumInstances;                                          // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.RebuildPowerCircuits
struct UFGCheatManager_RebuildPowerCircuits_Params
{
};

// Function FactoryGame.FGCheatManager.RandomizeBuildingsColorSlot
struct UFGCheatManager_RandomizeBuildingsColorSlot_Params
{
	unsigned char                                      SlotIndex;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.PurgeInactiveClientsFromSave
struct UFGCheatManager_PurgeInactiveClientsFromSave_Params
{
	bool                                               fetchInventories;                                         // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.PurgeAllTrainState
struct UFGCheatManager_PurgeAllTrainState_Params
{
};

// Function FactoryGame.FGCheatManager.PurgeAllBeaconsFromSave
struct UFGCheatManager_PurgeAllBeaconsFromSave_Params
{
};

// Function FactoryGame.FGCheatManager.PumpiMode
struct UFGCheatManager_PumpiMode_Params
{
	bool                                               enable;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.PrintStatichMeshesHirarchy
struct UFGCheatManager_PrintStatichMeshesHirarchy_Params
{
};

// Function FactoryGame.FGCheatManager.PardonAllPlayers
struct UFGCheatManager_PardonAllPlayers_Params
{
};

// Function FactoryGame.FGCheatManager.OpenModMap
struct UFGCheatManager_OpenModMap_Params
{
};

// Function FactoryGame.FGCheatManager.NoPower
struct UFGCheatManager_NoPower_Params
{
	bool                                               Enabled;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.NoCost
struct UFGCheatManager_NoCost_Params
{
	bool                                               Enabled;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.MergeAllConveyors
struct UFGCheatManager_MergeAllConveyors_Params
{
};

// Function FactoryGame.FGCheatManager.MCP_UpdatePresenceString
struct UFGCheatManager_MCP_UpdatePresenceString_Params
{
	class FString                                      String;                                                   // (Parm, ZeroConstructor)
};

// Function FactoryGame.FGCheatManager.MCP_UpdatePresence
struct UFGCheatManager_MCP_UpdatePresence_Params
{
	class FString                                      Key;                                                      // (Parm, ZeroConstructor)
	class FString                                      Value;                                                    // (Parm, ZeroConstructor)
};

// Function FactoryGame.FGCheatManager.MCP_LogPresence
struct UFGCheatManager_MCP_LogPresence_Params
{
};

// Function FactoryGame.FGCheatManager.MCP_Logout
struct UFGCheatManager_MCP_Logout_Params
{
};

// Function FactoryGame.FGCheatManager.MCP_Login
struct UFGCheatManager_MCP_Login_Params
{
	class FString                                      UserName;                                                 // (Parm, ZeroConstructor)
	class FString                                      password;                                                 // (Parm, ZeroConstructor)
};

// Function FactoryGame.FGCheatManager.MCP_GetOnlineStatus
struct UFGCheatManager_MCP_GetOnlineStatus_Params
{
	int                                                localPlayerNum;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.MCP_GetFriends
struct UFGCheatManager_MCP_GetFriends_Params
{
};

// Function FactoryGame.FGCheatManager.ListUnlockedRecipesAndSchematics
struct UFGCheatManager_ListUnlockedRecipesAndSchematics_Params
{
};

// Function FactoryGame.FGCheatManager.ListItemPickups
struct UFGCheatManager_ListItemPickups_Params
{
};

// Function FactoryGame.FGCheatManager.ListDebugStartingPoint
struct UFGCheatManager_ListDebugStartingPoint_Params
{
};

// Function FactoryGame.FGCheatManager.HideFactoryOnly
struct UFGCheatManager_HideFactoryOnly_Params
{
	bool                                               factoryHidden;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.HideAllBuildings
struct UFGCheatManager_HideAllBuildings_Params
{
	bool                                               InVisibility;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.GiveItem
struct UFGCheatManager_GiveItem_Params
{
	class UClass*                                      Resource;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                amount;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.GiefStorySchematics
struct UFGCheatManager_GiefStorySchematics_Params
{
};

// Function FactoryGame.FGCheatManager.GiefStartingResearch
struct UFGCheatManager_GiefStartingResearch_Params
{
};

// Function FactoryGame.FGCheatManager.GiefSchematicsOfTier
struct UFGCheatManager_GiefSchematicsOfTier_Params
{
	int                                                tier;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.GiefCheatSchematics
struct UFGCheatManager_GiefCheatSchematics_Params
{
};

// Function FactoryGame.FGCheatManager.GiefAvailableSchematics
struct UFGCheatManager_GiefAvailableSchematics_Params
{
};

// Function FactoryGame.FGCheatManager.GiefAllSchematicsAndPhases
struct UFGCheatManager_GiefAllSchematicsAndPhases_Params
{
};

// Function FactoryGame.FGCheatManager.GiefALLSchematics
struct UFGCheatManager_GiefALLSchematics_Params
{
};

// Function FactoryGame.FGCheatManager.GetVehicleInfo
struct UFGCheatManager_GetVehicleInfo_Params
{
};

// Function FactoryGame.FGCheatManager.ForceSpawnCreatures
struct UFGCheatManager_ForceSpawnCreatures_Params
{
};

// Function FactoryGame.FGCheatManager.FlipVehicle
struct UFGCheatManager_FlipVehicle_Params
{
};

// Function FactoryGame.FGCheatManager.FixupBuiltByRecipeInOldSave
struct UFGCheatManager_FixupBuiltByRecipeInOldSave_Params
{
	bool                                               reapplyRecipeIfBetterMatchFound;                          // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.EnablePlayerFOV
struct UFGCheatManager_EnablePlayerFOV_Params
{
	bool                                               enable;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.EnableInstancingOnFactory
struct UFGCheatManager_EnableInstancingOnFactory_Params
{
	bool                                               Enabled;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.EnableBuildableTick
struct UFGCheatManager_EnableBuildableTick_Params
{
	bool                                               enable;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.DumpTicking
struct UFGCheatManager_DumpTicking_Params
{
	bool                                               detailed;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.DumpSchematics
struct UFGCheatManager_DumpSchematics_Params
{
};

// Function FactoryGame.FGCheatManager.DumpPlayerStates
struct UFGCheatManager_DumpPlayerStates_Params
{
};

// Function FactoryGame.FGCheatManager.DumpNonDormantActors
struct UFGCheatManager_DumpNonDormantActors_Params
{
};

// Function FactoryGame.FGCheatManager.DumpFactoryStatsToLog
struct UFGCheatManager_DumpFactoryStatsToLog_Params
{
};

// Function FactoryGame.FGCheatManager.DumpAttachedToSkelMesh
struct UFGCheatManager_DumpAttachedToSkelMesh_Params
{
	bool                                               detailed;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCheatManager.DumpAllAvailableRecipes
struct UFGCheatManager_DumpAllAvailableRecipes_Params
{
};

// Function FactoryGame.FGCheatManager.DumpActorRepresentations
struct UFGCheatManager_DumpActorRepresentations_Params
{
};

// Function FactoryGame.FGCheatManager.DumpActiveGPUParticles
struct UFGCheatManager_DumpActiveGPUParticles_Params
{
};

// Function FactoryGame.FGCheatManager.DestroyPawn
struct UFGCheatManager_DestroyPawn_Params
{
};

// Function FactoryGame.FGCheatManager.DebugCrash
struct UFGCheatManager_DebugCrash_Params
{
};

// Function FactoryGame.FGCheatManager.CompleteResearch
struct UFGCheatManager_CompleteResearch_Params
{
};

// Function FactoryGame.FGCheatManager.ClearPardon
struct UFGCheatManager_ClearPardon_Params
{
};

// Function FactoryGame.FGCheatManager.ClearGiveItemPopularList
struct UFGCheatManager_ClearGiveItemPopularList_Params
{
};

// Function FactoryGame.FGCircuit.GetCircuitID
struct UFGCircuit_GetCircuitID_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCircuitConnectionComponent.ReceiveOnCircuitIDChanged
struct UFGCircuitConnectionComponent_ReceiveOnCircuitIDChanged_Params
{
};

// Function FactoryGame.FGCircuitConnectionComponent.IsHidden
struct UFGCircuitConnectionComponent_IsHidden_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCircuitConnectionComponent.IsConnected
struct UFGCircuitConnectionComponent_IsConnected_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCircuitConnectionComponent.GetNumHiddenConnections
struct UFGCircuitConnectionComponent_GetNumHiddenConnections_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCircuitConnectionComponent.GetNumFreeConnections
struct UFGCircuitConnectionComponent_GetNumFreeConnections_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCircuitConnectionComponent.GetNumConnections
struct UFGCircuitConnectionComponent_GetNumConnections_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCircuitConnectionComponent.GetMaxNumConnections
struct UFGCircuitConnectionComponent_GetMaxNumConnections_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCircuitConnectionComponent.GetCircuitID
struct UFGCircuitConnectionComponent_GetCircuitID_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCircuitSubsystem.PowerCircuit_OnFuseSet
struct AFGCircuitSubsystem_PowerCircuit_OnFuseSet_Params
{
};

// Function FactoryGame.FGCircuitSubsystem.PowerCircuit_OnFuseReset
struct AFGCircuitSubsystem_PowerCircuit_OnFuseReset_Params
{
};

// Function FactoryGame.FGCircuitSubsystem.OnRep_ReplicatedCircuits
struct AFGCircuitSubsystem_OnRep_ReplicatedCircuits_Params
{
};

// Function FactoryGame.FGCircuitSubsystem.GetCircuitSubsystem
struct AFGCircuitSubsystem_GetCircuitSubsystem_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGCircuitSubsystem*                         ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCircuitSubsystem.FindCircuit
struct AFGCircuitSubsystem_FindCircuit_Params
{
	int                                                circuitID;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGCircuit*                                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWeaponInstantFire.Server_NotifyMiss
struct AFGWeaponInstantFire_Server_NotifyMiss_Params
{
};

// Function FactoryGame.FGWeaponInstantFire.Server_NotifyHit
struct AFGWeaponInstantFire_Server_NotifyHit_Params
{
	struct FHitResult                                  HitResult;                                                // (ConstParm, Parm, ReferenceParm, IsPlainOldData)
};

// Function FactoryGame.FGColorGun.ToggleColorPickerUI
struct AFGColorGun_ToggleColorPickerUI_Params
{
};

// Function FactoryGame.FGColorGun.Sever_SetSecondaryColorForSlot
struct AFGColorGun_Sever_SetSecondaryColorForSlot_Params
{
	unsigned char                                      SlotIndex;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                NewColor;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGColorGun.Sever_SetSecondaryColor
struct AFGColorGun_Sever_SetSecondaryColor_Params
{
	struct FLinearColor                                NewColor;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGColorGun.Sever_SetPrimaryColorForSlot
struct AFGColorGun_Sever_SetPrimaryColorForSlot_Params
{
	unsigned char                                      SlotIndex;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                NewColor;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGColorGun.Sever_SetPrimaryColor
struct AFGColorGun_Sever_SetPrimaryColor_Params
{
	struct FLinearColor                                NewColor;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGColorGun.Sever_SetColorSlot
struct AFGColorGun_Sever_SetColorSlot_Params
{
	unsigned char                                      SlotIndex;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGColorGun.SetSecondaryColorForSlot
struct AFGColorGun_SetSecondaryColorForSlot_Params
{
	unsigned char                                      SlotIndex;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                NewColor;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGColorGun.SetSecondaryColor
struct AFGColorGun_SetSecondaryColor_Params
{
	struct FLinearColor                                NewColor;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGColorGun.SetPrimaryColorForSlot
struct AFGColorGun_SetPrimaryColorForSlot_Params
{
	unsigned char                                      SlotIndex;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                NewColor;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGColorGun.SetPrimaryColor
struct AFGColorGun_SetPrimaryColor_Params
{
	struct FLinearColor                                NewColor;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGColorGun.SetColorSlot
struct AFGColorGun_SetColorSlot_Params
{
	unsigned char                                      SlotIndex;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGColorGun.OnTargetStateChanged
struct AFGColorGun_OnTargetStateChanged_Params
{
	EFGColorGunTargetType                              targetType;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGColorGun.OnSecondaryFirePressed
struct AFGColorGun_OnSecondaryFirePressed_Params
{
};

// Function FactoryGame.FGColorGun.GetSecondaryColorForSlot
struct AFGColorGun_GetSecondaryColorForSlot_Params
{
	unsigned char                                      Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGColorGun.GetSecondaryColor
struct AFGColorGun_GetSecondaryColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGColorGun.GetPrimaryColorForSlot
struct AFGColorGun_GetPrimaryColorForSlot_Params
{
	unsigned char                                      Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGColorGun.GetPrimaryColor
struct AFGColorGun_GetPrimaryColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGColorGun.GetMaxNumColorSlots
struct AFGColorGun_GetMaxNumColorSlots_Params
{
	unsigned char                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGColorGun.GetColorSlotIndex
struct AFGColorGun_GetColorSlotIndex_Params
{
	unsigned char                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGColorInterface.StopIsAimedAtForColor
struct UFGColorInterface_StopIsAimedAtForColor_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGColorInterface.StartIsAimedAtForColor
struct UFGColorInterface_StartIsAimedAtForColor_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGColorInterface.SetSecondaryColor
struct UFGColorInterface_SetSecondaryColor_Params
{
	struct FLinearColor                                NewColor;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGColorInterface.SetPrimaryColor
struct UFGColorInterface_SetPrimaryColor_Params
{
	struct FLinearColor                                NewColor;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGColorInterface.SetColorSlot
struct UFGColorInterface_SetColorSlot_Params
{
	unsigned char                                      Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGColorInterface.GetSecondaryColor
struct UFGColorInterface_GetSecondaryColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGColorInterface.GetPrimaryColor
struct UFGColorInterface_GetPrimaryColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGColorInterface.GetColorSlot
struct UFGColorInterface_GetColorSlot_Params
{
	unsigned char                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGColorInterface.GetCanBeColored
struct UFGColorInterface_GetCanBeColored_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCombatFunctionLibrary.TryGetCharacterFromDamageCauser
struct UFGCombatFunctionLibrary_TryGetCharacterFromDamageCauser_Params
{
	class AActor*                                      damageCauser;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGCharacterBase*                            ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCombatFunctionLibrary.IsWithinRange
struct UFGCombatFunctionLibrary_IsWithinRange_Params
{
	class APawn*                                       attacker;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	TScriptInterface<class UFGAggroTargetInterface>    victim;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              range;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCombatFunctionLibrary.IsWithinAttackRange
struct UFGCombatFunctionLibrary_IsWithinAttackRange_Params
{
	class APawn*                                       attacker;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	TScriptInterface<class UFGAggroTargetInterface>    victim;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      attackClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCombatFunctionLibrary.DoRadialDamageWithinCollision
struct UFGCombatFunctionLibrary_DoRadialDamageWithinCollision_Params
{
	class AController*                                 Controller;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class UShapeComponent*                             collisionShape;                                           // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FVector                                     centerLocation;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      DamageType;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Damage;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Radius;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCompassObjectWidget.SetAsStaticDirection
struct UFGCompassObjectWidget_SetAsStaticDirection_Params
{
	struct FVector                                     Direction;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCompassObjectWidget.SetActorRepresentation
struct UFGCompassObjectWidget_SetActorRepresentation_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCompassObjectWidget.OnObjectCentered
struct UFGCompassObjectWidget_OnObjectCentered_Params
{
	bool                                               centered;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCompassObjectWidget.OnCompassObjectUpdated
struct UFGCompassObjectWidget_OnCompassObjectUpdated_Params
{
};

// Function FactoryGame.FGCompassObjectWidget.OnCompassObjectAddedToPanel
struct UFGCompassObjectWidget_OnCompassObjectAddedToPanel_Params
{
	class UCanvasPanelSlot*                            parentSlot;                                               // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGCompassObjectWidget.GetRepresentationType
struct UFGCompassObjectWidget_GetRepresentationType_Params
{
	ERepresentationType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCompassObjectWidget.GetDirectionFromLocation
struct UFGCompassObjectWidget_GetDirectionFromLocation_Params
{
	struct FVector                                     Location;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCompassObjectWidget.GetBlockingAmount
struct UFGCompassObjectWidget_GetBlockingAmount_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCompassObjectWidget.GetAngleFromDirection
struct UFGCompassObjectWidget_GetAngleFromDirection_Params
{
	struct FVector                                     Direction;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCompassObjectWidget.GetAlphaAmount
struct UFGCompassObjectWidget_GetAlphaAmount_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCompassObjectWidget.GetActorRepresentation
struct UFGCompassObjectWidget_GetActorRepresentation_Params
{
	class UFGActorRepresentation*                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCompassWidget.RemoveCompassObjectForRepresentation
struct UFGCompassWidget_RemoveCompassObjectForRepresentation_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCompassWidget.RemoveAllCompassRepresentations
struct UFGCompassWidget_RemoveAllCompassRepresentations_Params
{
};

// Function FactoryGame.FGCompassWidget.OnActorRepresentationUpdated
struct UFGCompassWidget_OnActorRepresentationUpdated_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCompassWidget.OnActorRepresentationRemoved
struct UFGCompassWidget_OnActorRepresentationRemoved_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCompassWidget.OnActorRepresentationAdded
struct UFGCompassWidget_OnActorRepresentationAdded_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCompassWidget.GetCompassObjectWidgetClass
struct UFGCompassWidget_GetCompassObjectWidgetClass_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCompassWidget.GetCompassLineOffset
struct UFGCompassWidget_GetCompassLineOffset_Params
{
	struct FVector2D                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCompassWidget.CreatePrimitiveCompassObject
struct UFGCompassWidget_CreatePrimitiveCompassObject_Params
{
	class UClass*                                      compassObjectTemplate;                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class UTexture2D*                                  Texture;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGCompassObjectWidget*                      ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGCompassWidget.CreateCompassObject
struct UFGCompassWidget_CreateCompassObject_Params
{
	class UClass*                                      compassObjectTemplate;                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGActorRepresentation*                      actorRepresentation;                                      // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGCompassObjectWidget*                      ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGCompassWidget.BindActorRepresentationManager
struct UFGCompassWidget_BindActorRepresentationManager_Params
{
	class AFGActorRepresentationManager*               representationManager;                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCompassWidget.AddCompassObjectForRepresentation
struct UFGCompassWidget_AddCompassObjectForRepresentation_Params
{
	class UClass*                                      compassObjectTemplate;                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGActorRepresentation*                      actorRepresentation;                                      // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGCompassObjectWidget*                      ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGCompassWidget.AddAllCompassRepresentations
struct UFGCompassWidget_AddAllCompassRepresentations_Params
{
	class AFGActorRepresentationManager*               representationManager;                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCompassWidget.AddAllCardinalDirections
struct UFGCompassWidget_AddAllCardinalDirections_Params
{
	class UClass*                                      compassObjectTemplate;                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class UTexture2D*                                  northTex;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	class UTexture2D*                                  eastTex;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UTexture2D*                                  southTex;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	class UTexture2D*                                  westTex;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UTexture2D*                                  northWestTex;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UTexture2D*                                  southEastTex;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UTexture2D*                                  southWestText;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	class UTexture2D*                                  northEastTex;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGConstructDisqualifier.GetDisqualifyingText
struct UFGConstructDisqualifier_GetDisqualifyingText_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGEquipmentDescriptor.GetEquipmentClass
struct UFGEquipmentDescriptor_GetEquipmentClass_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGConsumableDescriptor.GetTPOverrideMesh
struct UFGConsumableDescriptor_GetTPOverrideMesh_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UStaticMesh*                                 ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGConsumableDescriptor.GetFPOverrideMesh
struct UFGConsumableDescriptor_GetFPOverrideMesh_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class USkeletalMesh*                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGConsumableDescriptor.ConsumedBy
struct UFGConsumableDescriptor_ConsumedBy_Params
{
	class AFGCharacterPlayer*                          Player;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGConsumableEquipment.Server_PrimaryFire
struct AFGConsumableEquipment_Server_PrimaryFire_Params
{
};

// Function FactoryGame.FGConsumableEquipment.PlayConsumeEffects
struct AFGConsumableEquipment_PlayConsumeEffects_Params
{
	class UFGConsumableDescriptor*                     consumable;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGConsumableEquipment.GetConsumeable
struct AFGConsumableEquipment_GetConsumeable_Params
{
	class UClass*                                      out_consumeable;                                          // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	int                                                out_numConsumeable;                                       // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGConveyorBeltHologram.OnRep_SplineData
struct AFGConveyorBeltHologram_OnRep_SplineData_Params
{
};

// Function FactoryGame.FGConveyorBeltHologram.OnRep_ConnectionArrowComponentDirection
struct AFGConveyorBeltHologram_OnRep_ConnectionArrowComponentDirection_Params
{
};

// Function FactoryGame.FGSplineHologram.OnRep_SplineData
struct AFGSplineHologram_OnRep_SplineData_Params
{
};

// Function FactoryGame.FGConveyorLiftHologram.OnRep_TopTransform
struct AFGConveyorLiftHologram_OnRep_TopTransform_Params
{
};

// Function FactoryGame.FGConveyorLiftHologram.OnRep_ArrowDirection
struct AFGConveyorLiftHologram_OnRep_ArrowDirection_Params
{
};

// Function FactoryGame.FGPoleHologram.OnRep_PoleMesh
struct AFGPoleHologram_OnRep_PoleMesh_Params
{
};

// Function FactoryGame.FGCreature.StartRotationMovement
struct AFGCreature_StartRotationMovement_Params
{
	struct FRotator                                    TargetRotation;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCreature.SpawnDeathItem
struct AFGCreature_SpawnDeathItem_Params
{
};

// Function FactoryGame.FGCreature.SetPersistent
struct AFGCreature_SetPersistent_Params
{
	bool                                               persist;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCreature.SetMoveSpeed
struct AFGCreature_SetMoveSpeed_Params
{
	EMoveSpeed                                         newMoveSpeedType;                                         // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCreature.PlayConsumeItemEffect
struct AFGCreature_PlayConsumeItemEffect_Params
{
	class UClass*                                      itemDescriptor;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                amount;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCreature.OnRep_TargetRotation
struct AFGCreature_OnRep_TargetRotation_Params
{
};

// Function FactoryGame.FGCreature.OnRep_IsEnabled
struct AFGCreature_OnRep_IsEnabled_Params
{
};

// Function FactoryGame.FGCreature.OnArachnophobiaModeChanged
struct AFGCreature_OnArachnophobiaModeChanged_Params
{
	bool                                               isArachnophobiaMode;                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCreature.Multicast_ConsumeItem
struct AFGCreature_Multicast_ConsumeItem_Params
{
	class UClass*                                      itemDescriptor;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                amount;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCreature.IsPersistent
struct AFGCreature_IsPersistent_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCreature.GetTargetRotation
struct AFGCreature_GetTargetRotation_Params
{
	struct FRotator                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCreature.GetSplinePath
struct AFGCreature_GetSplinePath_Params
{
	class AFGSplinePath*                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCreature.GetIsEnabled
struct AFGCreature_GetIsEnabled_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCreature.GetIsArachnid
struct AFGCreature_GetIsArachnid_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCreature.GetDayTimePctAsNight
struct AFGCreature_GetDayTimePctAsNight_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCreature.GetArachnophobiaModeMaterials
struct AFGCreature_GetArachnophobiaModeMaterials_Params
{
	TArray<class UMaterialInstance*>                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGCreature.ConfigureArachnophobiaMode
struct AFGCreature_ConfigureArachnophobiaMode_Params
{
	bool                                               isArachnophobiaMode;                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCreature.CheckRotationMovement
struct AFGCreature_CheckRotationMovement_Params
{
};

// Function FactoryGame.FGCreature.CancelRotationMovement
struct AFGCreature_CancelRotationMovement_Params
{
};

// Function FactoryGame.FGCreature.AiCalculateLeadTrajectory
struct AFGCreature_AiCalculateLeadTrajectory_Params
{
	struct FVector                                     targetPos;                                                // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     targetVelocity;                                           // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     fromPos;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	float                                              interceptorSpeed;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               isPosibleToLead;                                          // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     interceptPoint;                                           // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	float                                              leadScaling;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGEnemy.PerformCustomRadialAttack
struct AFGEnemy_PerformCustomRadialAttack_Params
{
};

// Function FactoryGame.FGEnemy.OnRep_CurrentAggroTarget
struct AFGEnemy_OnRep_CurrentAggroTarget_Params
{
};

// Function FactoryGame.FGEnemy.OnCurrentAggroTargetReplicated
struct AFGEnemy_OnCurrentAggroTargetReplicated_Params
{
};

// Function FactoryGame.FGEnemy.GetCurrentAttackTask
struct AFGEnemy_GetCurrentAttackTask_Params
{
	class UFGGameplayTask_Attack*                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEnemy.GetCurrentAggroTarget
struct AFGEnemy_GetCurrentAggroTarget_Params
{
	class AActor*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEnemy.GetAttackLocation
struct AFGEnemy_GetAttackLocation_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCrabHatcher.StartExpanding
struct AFGCrabHatcher_StartExpanding_Params
{
};

// Function FactoryGame.FGCrabHatcher.SpawnCrabs
struct AFGCrabHatcher_SpawnCrabs_Params
{
};

// Function FactoryGame.FGCrabHatcher.SetThreatNearby
struct AFGCrabHatcher_SetThreatNearby_Params
{
	bool                                               inNearby;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCrabHatcher.SetDidSpawnCrabs
struct AFGCrabHatcher_SetDidSpawnCrabs_Params
{
	bool                                               inDidSPawn;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCrabHatcher.SetAnimationLength
struct AFGCrabHatcher_SetAnimationLength_Params
{
	float                                              animLength;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCrabHatcher.OnRep_DidSpawnCrabs
struct AFGCrabHatcher_OnRep_DidSpawnCrabs_Params
{
};

// Function FactoryGame.FGCrabHatcher.GetThreatNearby
struct AFGCrabHatcher_GetThreatNearby_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCrabHatcher.GetDidSpawnCrabs
struct AFGCrabHatcher_GetDidSpawnCrabs_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInteractActor.OnInteract
struct AFGInteractActor_OnInteract_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCrate.OnRequestReprecentMarker
struct AFGCrate_OnRequestReprecentMarker_Params
{
};

// Function FactoryGame.FGCrate.GetInventory
struct AFGCrate_GetInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGCrate.FilterInventoryClasses
struct AFGCrate_FilterInventoryClasses_Params
{
	class UClass*                                      Object;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                idx;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCreatureController.StopPanic
struct AFGCreatureController_StopPanic_Params
{
};

// Function FactoryGame.FGCreatureController.StartPanic
struct AFGCreatureController_StartPanic_Params
{
};

// Function FactoryGame.FGCreatureController.SetEnabled
struct AFGCreatureController_SetEnabled_Params
{
	bool                                               Enabled;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCreatureController.OnTargetPerceptionUpdated
struct AFGCreatureController_OnTargetPerceptionUpdated_Params
{
	class AActor*                                      inActor;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FAIStimulus                                 Stimulus;                                                 // (Parm)
};

// Function FactoryGame.FGDriveablePawn.ShouldAttachDriver
struct AFGDriveablePawn_ShouldAttachDriver_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGDriveablePawn.ReceiveOnDriverLeave
struct AFGDriveablePawn_ReceiveOnDriverLeave_Params
{
};

// Function FactoryGame.FGDriveablePawn.ReceiveOnDriverEnter
struct AFGDriveablePawn_ReceiveOnDriverEnter_Params
{
};

// Function FactoryGame.FGDriveablePawn.PlaceExitingDriver
struct AFGDriveablePawn_PlaceExitingDriver_Params
{
};

// Function FactoryGame.FGDriveablePawn.OnRep_IsDriving
struct AFGDriveablePawn_OnRep_IsDriving_Params
{
};

// Function FactoryGame.FGDriveablePawn.IsDriving
struct AFGDriveablePawn_IsDriving_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGDriveablePawn.IsDriverVisible
struct AFGDriveablePawn_IsDriverVisible_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGDriveablePawn.HasPendingDriver
struct AFGDriveablePawn_HasPendingDriver_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGDriveablePawn.GetDriverSeatSocket
struct AFGDriveablePawn_GetDriverSeatSocket_Params
{
	struct FName                                       ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGDriveablePawn.GetDriverSeatAnimation
struct AFGDriveablePawn_GetDriverSeatAnimation_Params
{
	class UAnimSequence*                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGDriveablePawn.GetDriverExitOffset
struct AFGDriveablePawn_GetDriverExitOffset_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGDriveablePawn.GetDriver
struct AFGDriveablePawn_GetDriver_Params
{
	class AFGCharacterPlayer*                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGDriveablePawn.DriverLeave
struct AFGDriveablePawn_DriverLeave_Params
{
	bool                                               keepDriving;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGDriveablePawn.DriverEnter
struct AFGDriveablePawn_DriverEnter_Params
{
	class AFGCharacterPlayer*                          Driver;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGDriveablePawn.CanDriverEnter
struct AFGDriveablePawn_CanDriverEnter_Params
{
	class AFGCharacterPlayer*                          Character;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCreatureSeat.GetMountedCreature
struct AFGCreatureSeat_GetMountedCreature_Params
{
	class AFGCreature*                                 ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCreatureSpawner.SpawnCreatures
struct AFGCreatureSpawner_SpawnCreatures_Params
{
};

// Function FactoryGame.FGCreatureSpawner.IsSpawnerActive
struct AFGCreatureSpawner_IsSpawnerActive_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGCreatureSpawner.GetSplines
struct AFGCreatureSpawner_GetSplines_Params
{
	TArray<class AFGSplinePath*>                       ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGCreatureSpawner.DestroyCreatures
struct AFGCreatureSpawner_DestroyCreatures_Params
{
};

// Function FactoryGame.FGCreatureSpawner.CreatureDied
struct AFGCreatureSpawner_CreatureDied_Params
{
	class AActor*                                      thisActor;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGCreatureSpawner.CalculateSpawningLocations
struct AFGCreatureSpawner_CalculateSpawningLocations_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGDamageOverTime.ShouldBeAppliedToActor
struct UFGDamageOverTime_ShouldBeAppliedToActor_Params
{
	class UClass*                                      dotClass;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      Actor;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGDamageOverTime.GetDamageInterval
struct UFGDamageOverTime_GetDamageInterval_Params
{
	class UClass*                                      dotClass;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGDamageOverTime.GetDamageClass
struct UFGDamageOverTime_GetDamageClass_Params
{
	class UClass*                                      dotClass;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGDamageOverTime.GetDamageAmount
struct UFGDamageOverTime_GetDamageAmount_Params
{
	class UClass*                                      dotClass;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGDecorDescriptor.GetDecorMesh
struct UFGDecorDescriptor_GetDecorMesh_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UStaticMesh*                                 ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGDestructibleActor.PlayDestructEffects
struct AFGDestructibleActor_PlayDestructEffects_Params
{
};

// Function FactoryGame.FGDestructibleActor.OnDestructibleFractured
struct AFGDestructibleActor_OnDestructibleFractured_Params
{
	struct FVector                                     HitPoint;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     HitDirection;                                             // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
};

// Function FactoryGame.FGDestructibleActor.Multicast_OnDestructibleFractured
struct AFGDestructibleActor_Multicast_OnDestructibleFractured_Params
{
	struct FVector                                     HitPoint;                                                 // (ConstParm, Parm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     HitDirection;                                             // (ConstParm, Parm, ZeroConstructor, ReferenceParm, IsPlainOldData)
};

// Function FactoryGame.FGProjectile.SetTargetLocation
struct AFGProjectile_SetTargetLocation_Params
{
	struct FVector                                     TargetLocation;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGProjectile.SetInitialVelocity
struct AFGProjectile_SetInitialVelocity_Params
{
	struct FVector                                     inVelocity;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGProjectile.PlayExplosionEffects
struct AFGProjectile_PlayExplosionEffects_Params
{
};

// Function FactoryGame.FGProjectile.PlayAttachEffect
struct AFGProjectile_PlayAttachEffect_Params
{
};

// Function FactoryGame.FGProjectile.OnRep_InitialVelocity
struct AFGProjectile_OnRep_InitialVelocity_Params
{
};

// Function FactoryGame.FGProjectile.OnRep_Exploded
struct AFGProjectile_OnRep_Exploded_Params
{
};

// Function FactoryGame.FGProjectile.OnImpact
struct AFGProjectile_OnImpact_Params
{
	struct FHitResult                                  HitResult;                                                // (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function FactoryGame.FGProjectile.OnBounce
struct AFGProjectile_OnBounce_Params
{
	struct FHitResult                                  HitResult;                                                // (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
	struct FVector                                     hitVelocity;                                              // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
};

// Function FactoryGame.FGProjectile.GetProjectileTargetLocation
struct AFGProjectile_GetProjectileTargetLocation_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGProjectile.GetCollisionSphere
struct AFGProjectile_GetCollisionSphere_Params
{
	class USphereComponent*                            ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGDismantleInterface.Upgrade
struct UFGDismantleInterface_Upgrade_Params
{
	class AActor*                                      newActor;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGDismantleInterface.StopIsLookedAtForDismantle
struct UFGDismantleInterface_StopIsLookedAtForDismantle_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGDismantleInterface.StartIsLookedAtForDismantle
struct UFGDismantleInterface_StartIsLookedAtForDismantle_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGDismantleInterface.PreUpgrade
struct UFGDismantleInterface_PreUpgrade_Params
{
};

// Function FactoryGame.FGDismantleInterface.GetRefundSpawnLocationAndArea
struct UFGDismantleInterface_GetRefundSpawnLocationAndArea_Params
{
	struct FVector                                     aimHitLocation;                                           // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	float                                              out_radius;                                               // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGDismantleInterface.GetDismantleRefund
struct UFGDismantleInterface_GetDismantleRefund_Params
{
	TArray<struct FInventoryStack>                     out_refund;                                               // (Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function FactoryGame.FGDismantleInterface.Dismantle
struct UFGDismantleInterface_Dismantle_Params
{
};

// Function FactoryGame.FGDismantleInterface.CanDismantle
struct UFGDismantleInterface_CanDismantle_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGHotbarShortcut.IsValidShortcut
struct UFGHotbarShortcut_IsValidShortcut_Params
{
	class AFGPlayerController*                         Owner;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGHotbarShortcut.IsActive
struct UFGHotbarShortcut_IsActive_Params
{
	class AFGPlayerController*                         Owner;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGHotbarShortcut.GetDisplayImage
struct UFGHotbarShortcut_GetDisplayImage_Params
{
	class UTexture2D*                                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGHotbarShortcut.Execute
struct UFGHotbarShortcut_Execute_Params
{
	class AFGPlayerController*                         Owner;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGDockableInterface.WasUndocked
struct UFGDockableInterface_WasUndocked_Params
{
};

// Function FactoryGame.FGDockableInterface.WasDocked
struct UFGDockableInterface_WasDocked_Params
{
	class AFGBuildableDockingStation*                  atStation;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGDockableInterface.OnTransferComplete
struct UFGDockableInterface_OnTransferComplete_Params
{
};

// Function FactoryGame.FGDockableInterface.OnBeginUnloadVehicle
struct UFGDockableInterface_OnBeginUnloadVehicle_Params
{
};

// Function FactoryGame.FGDockableInterface.OnBeginLoadVehicle
struct UFGDockableInterface_OnBeginLoadVehicle_Params
{
};

// Function FactoryGame.FGDockableInterface.GetDockInventory
struct UFGDockableInterface_GetDockInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGDockableInterface.GetDockFuelInventory
struct UFGDockableInterface_GetDockFuelInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGDockableInterface.CanDock
struct UFGDockableInterface_CanDock_Params
{
	EDockStationType                                   atStation;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGDotComponent.OnPrimitiveComponentExited
struct UFGDotComponent_OnPrimitiveComponentExited_Params
{
	class UPrimitiveComponent*                         OverlappedComp;                                           // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      Other;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGDotComponent.OnPrimitiveComponentEntered
struct UFGDotComponent_OnPrimitiveComponentEntered_Params
{
	class UPrimitiveComponent*                         OverlappedComp;                                           // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      Other;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               fromSweep;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  SweepResult;                                              // (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function FactoryGame.FGDotComponent.DamageContainingActors
struct UFGDotComponent_DamageContainingActors_Params
{
};

// Function FactoryGame.FGDropPod.RollLoot
struct AFGDropPod_RollLoot_Params
{
};

// Function FactoryGame.FGDropPod.RollDropPackage
struct AFGDropPod_RollDropPackage_Params
{
	TArray<class UClass*>                              includedItems;                                            // (Parm, ZeroConstructor)
	struct FDropPackage                                ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGDropPod.Open
struct AFGDropPod_Open_Params
{
};

// Function FactoryGame.FGDropPod.OnRep_HasBeenOpened
struct AFGDropPod_OnRep_HasBeenOpened_Params
{
};

// Function FactoryGame.FGDropPod.OnOpened
struct AFGDropPod_OnOpened_Params
{
};

// Function FactoryGame.FGDropPod.HasBeenOpened
struct AFGDropPod_HasBeenOpened_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGDropPod.GetLootInventory
struct AFGDropPod_GetLootInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGDropPod.GenerateDropPodInventory
struct AFGDropPod_GenerateDropPodInventory_Params
{
	TArray<class UClass*>                              includedItems;                                            // (Parm, ZeroConstructor)
	int                                                numItemsCreated;                                          // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGDropPodSettings.GetRandomDropPackage
struct UFGDropPodSettings_GetRandomDropPackage_Params
{
	class UWorld*                                      World;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	struct FDropPackage                                ReturnValue;                                              // (ConstParm, Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGEnemyController.UpdateAttackPattern
struct AFGEnemyController_UpdateAttackPattern_Params
{
};

// Function FactoryGame.FGEnemyController.UpdateAggroTargets
struct AFGEnemyController_UpdateAggroTargets_Params
{
	float                                              dt;                                                       // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               fullCheck;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGEnemyController.UpdateAggroAndFindAndAssignTarget
struct AFGEnemyController_UpdateAggroAndFindAndAssignTarget_Params
{
};

// Function FactoryGame.FGEnemyController.ShouldAddAggroTarget
struct AFGEnemyController_ShouldAddAggroTarget_Params
{
	TScriptInterface<class UFGAggroTargetInterface>    aggroTargetInterface;                                     // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEnemyController.SetCurrentAggroTarget
struct AFGEnemyController_SetCurrentAggroTarget_Params
{
	TScriptInterface<class UFGAggroTargetInterface>    newAggroTargetInterface;                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGEnemyController.ResetLastValidTargetLocation
struct AFGEnemyController_ResetLastValidTargetLocation_Params
{
};

// Function FactoryGame.FGEnemyController.RemoveInvalidAggroTargets
struct AFGEnemyController_RemoveInvalidAggroTargets_Params
{
};

// Function FactoryGame.FGEnemyController.OnPawnTakeDamage
struct AFGEnemyController_OnPawnTakeDamage_Params
{
	class AActor*                                      damagedActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              damageAmount;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGEnemyController.OnAggroTargetUpdated
struct AFGEnemyController_OnAggroTargetUpdated_Params
{
};

// Function FactoryGame.FGEnemyController.OnAggroTargetLost
struct AFGEnemyController_OnAggroTargetLost_Params
{
	class AActor*                                      lostActor;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGEnemyController.IsOnIgnoreList
struct AFGEnemyController_IsOnIgnoreList_Params
{
	TScriptInterface<class UFGAggroTargetInterface>    aggroTargetInterface;                                     // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEnemyController.GetTargetLastValidLocation
struct AFGEnemyController_GetTargetLastValidLocation_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEnemyController.GetTargetingDesireFromAggroEntry
struct AFGEnemyController_GetTargetingDesireFromAggroEntry_Params
{
	struct FAggroEntry                                 outTarget;                                                // (Parm)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEnemyController.GetTargetingDesire
struct AFGEnemyController_GetTargetingDesire_Params
{
	TScriptInterface<class UFGAggroTargetInterface>    aggroTarget;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEnemyController.GetMostDesirableAggroTarget
struct AFGEnemyController_GetMostDesirableAggroTarget_Params
{
	TScriptInterface<class UFGAggroTargetInterface>    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEnemyController.GetCurrentAttackFromPattern
struct AFGEnemyController_GetCurrentAttackFromPattern_Params
{
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEnemyController.GetAttackPatternIndex
struct AFGEnemyController_GetAttackPatternIndex_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEnemyController.GetAggroThreshold
struct AFGEnemyController_GetAggroThreshold_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEnemyController.GatherAggroTargets
struct AFGEnemyController_GatherAggroTargets_Params
{
};

// Function FactoryGame.FGEnemyController.FindAndAssignTarget
struct AFGEnemyController_FindAndAssignTarget_Params
{
};

// Function FactoryGame.FGEnemyController.ClearAllAggroTargetsAndUpdate
struct AFGEnemyController_ClearAllAggroTargetsAndUpdate_Params
{
};

// Function FactoryGame.FGEnemyController.CanSeeActor
struct AFGEnemyController_CanSeeActor_Params
{
	class AActor*                                      Target;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEnemyController.AggroTargetRemoved
struct AFGEnemyController_AggroTargetRemoved_Params
{
	TScriptInterface<class UFGAggroTargetInterface>    aggroTarget;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGEnemyController.AggroTargetAdded
struct AFGEnemyController_AggroTargetAdded_Params
{
	TScriptInterface<class UFGAggroTargetInterface>    aggroTarget;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGEnemyController.AddToAggroByTarget
struct AFGEnemyController_AddToAggroByTarget_Params
{
	TScriptInterface<class UFGAggroTargetInterface>    Target;                                                   // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	float                                              Damage;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGEquipmentChild.OnUnEquip
struct AFGEquipmentChild_OnUnEquip_Params
{
};

// Function FactoryGame.FGEquipmentChild.OnEquip
struct AFGEquipmentChild_OnEquip_Params
{
	class AFGCharacterPlayer*                          Character;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGEquipmentChild.GetAttachSocketTransform
struct AFGEquipmentChild_GetAttachSocketTransform_Params
{
	struct FTransform                                  ReturnValue;                                              // (Parm, OutParm, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEquipmentStunSpear.Server_ShockEnemy
struct AFGEquipmentStunSpear_Server_ShockEnemy_Params
{
};

// Function FactoryGame.FGEquipmentStunSpear.PlayStunEffects
struct AFGEquipmentStunSpear_PlayStunEffects_Params
{
};

// Function FactoryGame.FGEquipmentStunSpear.OnHitTarget
struct AFGEquipmentStunSpear_OnHitTarget_Params
{
};

// Function FactoryGame.FGEquipmentStunSpear.GetShouldPlaySecondSwing
struct AFGEquipmentStunSpear_GetShouldPlaySecondSwing_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGEquipmentStunSpear.DoAttack
struct AFGEquipmentStunSpear_DoAttack_Params
{
};

// Function FactoryGame.FGErrorMessage.GetErrorResponse
struct UFGErrorMessage_GetErrorResponse_Params
{
	TEnumAsByte<EErrorResponse>                        ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGErrorMessage.GetErrorMessage
struct UFGErrorMessage_GetErrorMessage_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGExplosiveDestroyableInterface.NotifyExploded
struct UFGExplosiveDestroyableInterface_NotifyExploded_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGExplosiveDestroyableInterface.GetDestroyEffect
struct UFGExplosiveDestroyableInterface_GetDestroyEffect_Params
{
	class UParticleSystem*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFactoryConnectionComponent.IsConnected
struct UFGFactoryConnectionComponent_IsConnected_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFactoryConnectionComponent.GetInventory
struct UFGFactoryConnectionComponent_GetInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGFactoryConnectionComponent.GetDirection
struct UFGFactoryConnectionComponent_GetDirection_Params
{
	EFactoryConnectionDirection                        ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFactoryConnectionComponent.GetConnectorClearance
struct UFGFactoryConnectionComponent_GetConnectorClearance_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFactoryConnectionComponent.GetConnector
struct UFGFactoryConnectionComponent_GetConnector_Params
{
	EFactoryConnectionConnector                        ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFactoryConnectionComponent.Factory_PeekOutput
struct UFGFactoryConnectionComponent_Factory_PeekOutput_Params
{
	TArray<struct FInventoryItem>                      out_items;                                                // (Parm, OutParm, ZeroConstructor)
	class UClass*                                      Type;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFactoryConnectionComponent.Factory_Internal_PeekOutputInventory
struct UFGFactoryConnectionComponent_Factory_Internal_PeekOutputInventory_Params
{
	TArray<struct FInventoryItem>                      out_items;                                                // (Parm, OutParm, ZeroConstructor)
	class UClass*                                      Type;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFactoryConnectionComponent.Factory_Internal_GrabOutputInventory
struct UFGFactoryConnectionComponent_Factory_Internal_GrabOutputInventory_Params
{
	struct FInventoryItem                              out_item;                                                 // (Parm, OutParm)
	class UClass*                                      Type;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFactoryConnectionComponent.Factory_GrabOutput
struct UFGFactoryConnectionComponent_Factory_GrabOutput_Params
{
	struct FInventoryItem                              out_item;                                                 // (Parm, OutParm)
	float                                              out_OffsetBeyond;                                         // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      Type;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFactoryLegsComponent.GetLegMeshComponents
struct UFGFactoryLegsComponent_GetLegMeshComponents_Params
{
	TArray<class UStaticMeshComponent*>                ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGFactoryLegsComponent.GetFootMeshComponents
struct UFGFactoryLegsComponent_GetFootMeshComponents_Params
{
	TArray<class UStaticMeshComponent*>                ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGFactorySettings.GetRandomDismantleSound
struct UFGFactorySettings_GetRandomDismantleSound_Params
{
	class UAkAudioEvent*                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFactorySettings.GetRandomConstructionSound
struct UFGFactorySettings_GetRandomConstructionSound_Params
{
	class UAkAudioEvent*                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFoliagePickup.Server_PickupWithTransform
struct AFGFoliagePickup_Server_PickupWithTransform_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGFoliageRemoval*                           foliageRemoval;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	struct FTransform                                  withTransform;                                            // (Parm, IsPlainOldData)
};

// Function FactoryGame.FGFoliagePickup.PlayPickupEffect
struct AFGFoliagePickup_PlayPickupEffect_Params
{
	class UFGFoliageResourceUserData*                  foliageUserData;                                          // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FVector                                     atLocation;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGFoliagePickup.BroadcastPickup
struct AFGFoliagePickup_BroadcastPickup_Params
{
	class UStaticMesh*                                 fromStaticMesh;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     atLocation;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGFoliageRemoval.RemoveInstance
struct AFGFoliageRemoval_RemoveInstance_Params
{
	struct FTransform                                  foliageTransform;                                         // (Parm, IsPlainOldData)
	bool                                               localSpace;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                InstanceId;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFoliageRemoval.RegisterWithSubsystem
struct AFGFoliageRemoval_RegisterWithSubsystem_Params
{
};

// Function FactoryGame.FGFoliageRemovalSubsystem.OnLevelRemovedFromWorld
struct AFGFoliageRemovalSubsystem_OnLevelRemovedFromWorld_Params
{
	class ULevel*                                      inLevel;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UWorld*                                      inWorld;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGFoliageRemovalSubsystem.OnLevelAddedToWorld
struct AFGFoliageRemovalSubsystem_OnLevelAddedToWorld_Params
{
	class ULevel*                                      inLevel;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UWorld*                                      inWorld;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGFoliageRemovalSubsystem.HasIdentifier
struct AFGFoliageRemovalSubsystem_HasIdentifier_Params
{
	class UHierarchicalInstancedStaticMeshComponent*   component;                                                // (ConstParm, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UClass*                                      foliageIdentifier;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFoliageRemovalSubsystem.GetLookAtFoliage
struct AFGFoliageRemovalSubsystem_GetLookAtFoliage_Params
{
	struct FVector                                     ViewLocation;                                             // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     endViewLocation;                                          // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	class UClass*                                      foliageIdentifier;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	class UHierarchicalInstancedStaticMeshComponent*   out_component;                                            // (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                out_instanceId;                                           // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     out_instanceLocation;                                     // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFoliageRemovalSubsystem.GetFoliageWithinRadius
struct AFGFoliageRemovalSubsystem_GetFoliageWithinRadius_Params
{
	struct FVector                                     Location;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	float                                              Radius;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               isLocalSpace;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<int>                                        out_instanceArray;                                        // (Parm, OutParm, ZeroConstructor)
	TArray<struct FVector>                             out_locationArray;                                        // (Parm, OutParm, ZeroConstructor)
	TArray<class UHierarchicalInstancedStaticMeshComponent*> out_componentArray;                                       // (Parm, OutParm, ZeroConstructor)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFoliageRemovalSubsystem.GetFoliageRemovalSubsystem
struct AFGFoliageRemovalSubsystem_GetFoliageRemovalSubsystem_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGFoliageRemovalSubsystem*                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFoliageRemovalSubsystem.GetFoliageRemovalActor
struct AFGFoliageRemovalSubsystem_GetFoliageRemovalActor_Params
{
	class UHierarchicalInstancedStaticMeshComponent*   fromComponent;                                            // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AFGFoliageRemoval*                           ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFoliageRemovalSubsystem.GetClosestFoliageForComponent
struct AFGFoliageRemovalSubsystem_GetClosestFoliageForComponent_Params
{
	struct FVector                                     Location;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	float                                              MaxDistance;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class UHierarchicalInstancedStaticMeshComponent*   component;                                                // (ConstParm, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               isLocalSpace;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                out_instanceId;                                           // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     out_instanceLocation;                                     // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFoliageRemovalSubsystem.GetClosestFoliageArrayForComponent
struct AFGFoliageRemovalSubsystem_GetClosestFoliageArrayForComponent_Params
{
	TArray<struct FVector>                             Locations;                                                // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	float                                              MaxDistance;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class UHierarchicalInstancedStaticMeshComponent*   component;                                                // (ConstParm, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               isLocalSpace;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<int>                                        out_instanceArray;                                        // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGFoliageRemovalSubsystem.GetClosestFoliage
struct AFGFoliageRemovalSubsystem_GetClosestFoliage_Params
{
	struct FVector                                     Location;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	float                                              MaxDistance;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      foliageIdentifier;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	class UHierarchicalInstancedStaticMeshComponent*   out_component;                                            // (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               isLocalSpace;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                out_instanceId;                                           // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     out_instanceLocation;                                     // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGVehicle.UpdatePhysicsVolume
struct AFGVehicle_UpdatePhysicsVolume_Params
{
	class APhysicsVolume*                              PhysicsVolume;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGVehicle.SelfDriverEnter
struct AFGVehicle_SelfDriverEnter_Params
{
	class AAIController*                               AI;                                                       // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGVehicle.ReceiveOnVehicleStartup
struct AFGVehicle_ReceiveOnVehicleStartup_Params
{
};

// Function FactoryGame.FGVehicle.ReceiveOnVehicleShutDown
struct AFGVehicle_ReceiveOnVehicleShutDown_Params
{
};

// Function FactoryGame.FGVehicle.ReceiveDied
struct AFGVehicle_ReceiveDied_Params
{
	class AActor*                                      thisActor;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGVehicle.OnTakeDamage
struct AFGVehicle_OnTakeDamage_Params
{
	class AActor*                                      damagedActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              damageAmount;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGVehicle.OnRep_SecondaryColor
struct AFGVehicle_OnRep_SecondaryColor_Params
{
};

// Function FactoryGame.FGVehicle.OnRep_PrimaryColor
struct AFGVehicle_OnRep_PrimaryColor_Params
{
};

// Function FactoryGame.FGVehicle.NotifyOnTakeDamage
struct AFGVehicle_NotifyOnTakeDamage_Params
{
	class AActor*                                      damagedActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              damageAmount;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGVehicle.KickAllPlayers
struct AFGVehicle_KickAllPlayers_Params
{
};

// Function FactoryGame.FGVehicle.IsSelfDriving
struct AFGVehicle_IsSelfDriving_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGVehicle.IsDestructible
struct AFGVehicle_IsDestructible_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGVehicle.HasAnyPassengerSeatAvailable
struct AFGVehicle_HasAnyPassengerSeatAvailable_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGVehicle.GetHealthComponent
struct AFGVehicle_GetHealthComponent_Params
{
	class UFGHealthComponent*                          ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGVehicle.GetDismantleBlueprintReturns
struct AFGVehicle_GetDismantleBlueprintReturns_Params
{
	TArray<struct FInventoryStack>                     out_returns;                                              // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGVehicle.Died
struct AFGVehicle_Died_Params
{
	class AActor*                                      thisActor;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGVehicle.CanSelfDriverEnter
struct AFGVehicle_CanSelfDriverEnter_Params
{
	class AAIController*                               AI;                                                       // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicle.IsOrientationReversed
struct AFGRailroadVehicle_IsOrientationReversed_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicle.IsCoupledAt
struct AFGRailroadVehicle_IsCoupledAt_Params
{
	ERailroadVehicleCoupler                            coupler;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicle.GetTrain
struct AFGRailroadVehicle_GetTrain_Params
{
	class AFGTrain*                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicle.GetTrackPosition
struct AFGRailroadVehicle_GetTrackPosition_Params
{
	struct FRailroadTrackPosition                      ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGRailroadVehicle.GetTrackGraphID
struct AFGRailroadVehicle_GetTrackGraphID_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicle.GetRailroadVehicleMovementComponent
struct AFGRailroadVehicle_GetRailroadVehicleMovementComponent_Params
{
	class UFGRailroadVehicleMovementComponent*         ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicle.GetLength
struct AFGRailroadVehicle_GetLength_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicle.GetCoupledVehicleAt
struct AFGRailroadVehicle_GetCoupledVehicleAt_Params
{
	ERailroadVehicleCoupler                            coupler;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGRailroadVehicle*                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFreightWagon.OnItemRemovedFromFreight
struct AFGFreightWagon_OnItemRemovedFromFreight_Params
{
	class UClass*                                      ItemClass;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                numRemoved;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGFreightWagon.OnItemAddedToFreight
struct AFGFreightWagon_OnItemAddedToFreight_Params
{
	class UClass*                                      ItemClass;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                numAdded;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGFreightWagon.InitializeInventoryComponent
struct AFGFreightWagon_InitializeInventoryComponent_Params
{
};

// Function FactoryGame.FGFreightWagon.GetFreightInventoryFilledPercent
struct AFGFreightWagon_GetFreightInventoryFilledPercent_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFreightWagon.GetFreightInventory
struct AFGFreightWagon_GetFreightInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGGameInstance.SetSkipOnboarding
struct UFGGameInstance_SetSkipOnboarding_Params
{
	bool                                               doSkip;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameInstance.SetHasSeenAlphaInfoScreen
struct UFGGameInstance_SetHasSeenAlphaInfoScreen_Params
{
	bool                                               hasSeen;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameInstance.PushError
struct UFGGameInstance_PushError_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      errorMessage;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameInstance.PeekNextError
struct UFGGameInstance_PeekNextError_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGErrorMessage*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameInstance.HasPlayerSeenAlphaInfoScreen
struct UFGGameInstance_HasPlayerSeenAlphaInfoScreen_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameInstance.GetSkipOnboarding
struct UFGGameInstance_GetSkipOnboarding_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameInstance.GetNextError
struct UFGGameInstance_GetNextError_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGErrorMessage*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameInstance.GetGameAnalyticsService
struct UFGGameInstance_GetGameAnalyticsService_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UAnalyticsService*                           ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameInstance.GetFGUGC
struct UFGGameInstance_GetFGUGC_Params
{
	class UClass*                                      WeaponClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      EnemyClass;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      BossClass;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      PlayerPawnClass;                                          // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameInstance.FindModPackages
struct UFGGameInstance_FindModPackages_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameMode.TriggerWorldSave
struct AFGGameMode_TriggerWorldSave_Params
{
	class FString                                      saveGameName;                                             // (Parm, ZeroConstructor)
};

// Function FactoryGame.FGGameMode.TriggerBundledWorldSave
struct AFGGameMode_TriggerBundledWorldSave_Params
{
	class FString                                      saveGameName;                                             // (Parm, ZeroConstructor)
};

// Function FactoryGame.FGGameMode.RegisterRemoteCallObjectClass
struct AFGGameMode_RegisterRemoteCallObjectClass_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameMode.KickPlayer
struct AFGGameMode_KickPlayer_Params
{
	class APlayerState*                                ps;                                                       // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGamePhaseManager.SetGamePhase
struct AFGGamePhaseManager_SetGamePhase_Params
{
	TEnumAsByte<EGamePhase>                            newPhase;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGamePhaseManager.PayOffOnGamePhase
struct AFGGamePhaseManager_PayOffOnGamePhase_Params
{
	struct FItemAmount                                 payOff;                                                   // (Parm)
	TEnumAsByte<EGamePhase>                            gamePhase;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGamePhaseManager.OnRep_GamePhase
struct AFGGamePhaseManager_OnRep_GamePhase_Params
{
};

// Function FactoryGame.FGGamePhaseManager.GetGamePhaseName
struct AFGGamePhaseManager_GetGamePhaseName_Params
{
	TEnumAsByte<EGamePhase>                            gamePhase;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGGamePhaseManager.GetGamePhaseForTechTier
struct AFGGamePhaseManager_GetGamePhaseForTechTier_Params
{
	int                                                techTier;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EGamePhase>                            ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGamePhaseManager.GetGamePhaseForSchematic
struct AFGGamePhaseManager_GetGamePhaseForSchematic_Params
{
	class UClass*                                      inSchematic;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EGamePhase>                            ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGamePhaseManager.GetGamePhase
struct AFGGamePhaseManager_GetGamePhase_Params
{
	TEnumAsByte<EGamePhase>                            ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGamePhaseManager.GetCostForGamePhase
struct AFGGamePhaseManager_GetCostForGamePhase_Params
{
	TEnumAsByte<EGamePhase>                            gamePhase;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FItemAmount>                         out_cost;                                                 // (Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function FactoryGame.FGGamePhaseManager.GetBaseCostForGamePhase
struct AFGGamePhaseManager_GetBaseCostForGamePhase_Params
{
	TEnumAsByte<EGamePhase>                            gamePhase;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FItemAmount>                         out_cost;                                                 // (Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function FactoryGame.FGGamePhaseManager.Get
struct AFGGamePhaseManager_Get_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGGamePhaseManager*                         ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameplayTask_Attack.GetAttackClass
struct UFGGameplayTask_Attack_GetAttackClass_Params
{
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameplayTask_AttackJump.StartJump
struct UFGGameplayTask_AttackJump_StartJump_Params
{
	class AFGEnemy*                                    Enemy;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      attackClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               StartJump;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGGameplayTask_AttackJump*                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameplayTask_AttackJump.OnMontageEnded
struct UFGGameplayTask_AttackJump_OnMontageEnded_Params
{
	class UAnimMontage*                                Montage;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               interrupted;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameplayTask_AttackJump.OnLandedCallback
struct UFGGameplayTask_AttackJump_OnLandedCallback_Params
{
	struct FHitResult                                  Hit;                                                      // (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function FactoryGame.FGGameplayTask_AttackMelee.OnMontageEnded
struct UFGGameplayTask_AttackMelee_OnMontageEnded_Params
{
	class UAnimMontage*                                Montage;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               interrupted;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameplayTask_AttackMelee.OnMontageBlendingOut
struct UFGGameplayTask_AttackMelee_OnMontageBlendingOut_Params
{
	class UAnimMontage*                                Montage;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               interrupted;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameplayTask_AttackMelee.Attack
struct UFGGameplayTask_AttackMelee_Attack_Params
{
	class AFGEnemy*                                    Enemy;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	TScriptInterface<class UFGAggroTargetInterface>    attackTarget;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      attackClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGGameplayTask_AttackMelee*                 ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameSession.ListenForIntroSequenceUpdated
struct AFGGameSession_ListenForIntroSequenceUpdated_Params
{
};

// Function FactoryGame.FGGameSession.IntroSequenceUpdated
struct AFGGameSession_IntroSequenceUpdated_Params
{
};

// Function FactoryGame.FGGameState.SetIsSpaceElevatorBuilt
struct AFGGameState_SetIsSpaceElevatorBuilt_Params
{
	bool                                               IsSpaceElevatorBuilt;                                     // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameState.SetHasInitalTradingPostLandAnimPlayed
struct AFGGameState_SetHasInitalTradingPostLandAnimPlayed_Params
{
};

// Function FactoryGame.FGGameState.SetCheatNoPower
struct AFGGameState_SetCheatNoPower_Params
{
	bool                                               NoPower;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameState.SetCheatNoCost
struct AFGGameState_SetCheatNoCost_Params
{
	bool                                               NoCost;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameState.SetAndReplicateBuildingColorInSlot
struct AFGGameState_SetAndReplicateBuildingColorInSlot_Params
{
	unsigned char                                      Slot;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	struct FColor                                      pColor;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	struct FColor                                      sColor;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameState.SendMessageToPlayer
struct AFGGameState_SendMessageToPlayer_Params
{
	class UClass*                                      inMessage;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	class APlayerController*                           Controller;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameState.SendMessageToAllPlayers
struct AFGGameState_SendMessageToAllPlayers_Params
{
	class UClass*                                      inMessage;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameState.RemoveAllScannableResources
struct AFGGameState_RemoveAllScannableResources_Params
{
};

// Function FactoryGame.FGGameState.OnSchematicPurchased
struct AFGGameState_OnSchematicPurchased_Params
{
	class UClass*                                      newSchematic;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameState.OnRep_MapAreaVisited
struct AFGGameState_OnRep_MapAreaVisited_Params
{
};

// Function FactoryGame.FGGameState.OnRep_BuildingColorSlot
struct AFGGameState_OnRep_BuildingColorSlot_Params
{
};

// Function FactoryGame.FGGameState.NotifyPlayerAdded
struct AFGGameState_NotifyPlayerAdded_Params
{
	class AFGCharacterPlayer*                          inPlayer;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameState.IsTradingPostBuilt
struct AFGGameState_IsTradingPostBuilt_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameState.IsSpaceElevatorBuilt
struct AFGGameState_IsSpaceElevatorBuilt_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameState.IsMapAreaVisisted
struct AFGGameState_IsMapAreaVisisted_Params
{
	class UClass*                                      inArea;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameState.HasInitalTradingPostLandAnimPlayed
struct AFGGameState_HasInitalTradingPostLandAnimPlayed_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameState.GetVisitedMapAreas
struct AFGGameState_GetVisitedMapAreas_Params
{
	TArray<class UClass*>                              out_VisitedAreas;                                         // (Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function FactoryGame.FGGameState.GetTutorialIntroManager
struct AFGGameState_GetTutorialIntroManager_Params
{
	class AFGTutorialIntroManager*                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameState.GetTotalPlayerInventorySlots
struct AFGGameState_GetTotalPlayerInventorySlots_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameState.GetTotalPlayerArmEquipmentSlots
struct AFGGameState_GetTotalPlayerArmEquipmentSlots_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameState.GetTotalPlayDuration
struct AFGGameState_GetTotalPlayDuration_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameState.GetSessionName
struct AFGGameState_GetSessionName_Params
{
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGGameState.GetSchematicManager
struct AFGGameState_GetSchematicManager_Params
{
	class AFGSchematicManager*                         ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameState.GetResearchManager
struct AFGGameState_GetResearchManager_Params
{
	class AFGResearchManager*                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameState.GetNumInventorySlotsUnlocked
struct AFGGameState_GetNumInventorySlotsUnlocked_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameState.GetNumArmEquipmentSlotsUnlocked
struct AFGGameState_GetNumArmEquipmentSlotsUnlocked_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameState.GetIsMapUnlocked
struct AFGGameState_GetIsMapUnlocked_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameState.GetGamePhaseManager
struct AFGGameState_GetGamePhaseManager_Params
{
	class AFGGamePhaseManager*                         ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameState.GetCheatNoPower
struct AFGGameState_GetCheatNoPower_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameState.GetCheatNoCost
struct AFGGameState_GetCheatNoCost_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameState.GetBuildingOverclockUnlocked
struct AFGGameState_GetBuildingOverclockUnlocked_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameState.GetBuildingEfficiencyUnlocked
struct AFGGameState_GetBuildingEfficiencyUnlocked_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameState.GetActorRepresentationManager
struct AFGGameState_GetActorRepresentationManager_Params
{
	class AFGActorRepresentationManager*               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameUI.SetWindowWantsInventoryAddon
struct UFGGameUI_SetWindowWantsInventoryAddon_Params
{
	bool                                               doWantAddon;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameUI.SetShowInventory
struct UFGGameUI_SetShowInventory_Params
{
	bool                                               doShow;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameUI.SetCurrentAudioMessage
struct UFGGameUI_SetCurrentAudioMessage_Params
{
	class UFGAudioMessage*                             newMessage;                                               // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGGameUI.RemovePawnHUD
struct UFGGameUI_RemovePawnHUD_Params
{
};

// Function FactoryGame.FGGameUI.RemoveInteractWidget
struct UFGGameUI_RemoveInteractWidget_Params
{
	class UFGInteractWidget*                           widgetToRemove;                                           // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGGameUI.RemoveAudioMessage
struct UFGGameUI_RemoveAudioMessage_Params
{
};

// Function FactoryGame.FGGameUI.ReceivedMessage
struct UFGGameUI_ReceivedMessage_Params
{
	class UClass*                                      inMessage;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameUI.PopAllWidgets
struct UFGGameUI_PopAllWidgets_Params
{
};

// Function FactoryGame.FGGameUI.OnReceiveRadiationStop
struct UFGGameUI_OnReceiveRadiationStop_Params
{
};

// Function FactoryGame.FGGameUI.OnReceiveRadiationStart
struct UFGGameUI_OnReceiveRadiationStart_Params
{
};

// Function FactoryGame.FGGameUI.OnRadiationIntensityUpdated
struct UFGGameUI_OnRadiationIntensityUpdated_Params
{
	float                                              radiationIntensity;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              radiationImmunity;                                        // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameUI.HandlePendingMessages
struct UFGGameUI_HandlePendingMessages_Params
{
};

// Function FactoryGame.FGGameUI.HandleFocusLost
struct UFGGameUI_HandleFocusLost_Params
{
};

// Function FactoryGame.FGGameUI.GetWindowWantsInventoryAddon
struct UFGGameUI_GetWindowWantsInventoryAddon_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameUI.GetShowInventory
struct UFGGameUI_GetShowInventory_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameUI.GetPendingMessages
struct UFGGameUI_GetPendingMessages_Params
{
	TArray<class UClass*>                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGGameUI.GetInteractWidgetStack
struct UFGGameUI_GetInteractWidgetStack_Params
{
	TArray<class UFGInteractWidget*>                   ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGGameUI.GetCurrentAudioMessage
struct UFGGameUI_GetCurrentAudioMessage_Params
{
	class UFGAudioMessage*                             ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGGameUI.ClearHintOnTutorialStepCompleted
struct UFGGameUI_ClearHintOnTutorialStepCompleted_Params
{
};

// Function FactoryGame.FGGameUI.CanReceiveMessage
struct UFGGameUI_CanReceiveMessage_Params
{
	class UClass*                                      inMessage;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameUI.CancelPressed
struct UFGGameUI_CancelPressed_Params
{
};

// Function FactoryGame.FGGameUI.AddPendingMessage
struct UFGGameUI_AddPendingMessage_Params
{
	class UClass*                                      newMessage;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameUI.AddPawnHUD
struct UFGGameUI_AddPawnHUD_Params
{
	class UUserWidget*                                 newContent;                                               // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGGameUI.AddIntroTutorialInfo
struct UFGGameUI_AddIntroTutorialInfo_Params
{
	struct FTutorialHintData                           TutorialHintData;                                         // (Parm)
};

// Function FactoryGame.FGGameUI.AddInteractWidget
struct UFGGameUI_AddInteractWidget_Params
{
	class UFGInteractWidget*                           widgetToAdd;                                              // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGGameUI.AddCheatWidget
struct UFGGameUI_AddCheatWidget_Params
{
	struct FPopupData                                  PopupData;                                                // (Parm)
	class UFGPopupWidget*                              ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.UpdatePostProcessSettings
struct UFGGameUserSettings_UpdatePostProcessSettings_Params
{
};

// Function FactoryGame.FGGameUserSettings.SetNeworkQuality
struct UFGGameUserSettings_SetNeworkQuality_Params
{
	int                                                newNetworkQuality;                                        // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.SetMotionBlurEnabled
struct UFGGameUserSettings_SetMotionBlurEnabled_Params
{
	bool                                               enable;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.SetInvertedLook
struct UFGGameUserSettings_SetInvertedLook_Params
{
	bool                                               newInvertLook;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.SetHoldToSprint
struct UFGGameUserSettings_SetHoldToSprint_Params
{
	bool                                               newHoldToSprint;                                          // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.SetHeadBobScale
struct UFGGameUserSettings_SetHeadBobScale_Params
{
	float                                              newHeadBobScale;                                          // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.SetFOV
struct UFGGameUserSettings_SetFOV_Params
{
	int                                                NewFOV;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.SetAutoSortInventory
struct UFGGameUserSettings_SetAutoSortInventory_Params
{
	bool                                               shouldAutoSort;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.SetAudioVolume
struct UFGGameUserSettings_SetAudioVolume_Params
{
	class FString                                      Name;                                                     // (Parm, ZeroConstructor)
	float                                              Value;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.SetAudioToDefaults
struct UFGGameUserSettings_SetAudioToDefaults_Params
{
};

// Function FactoryGame.FGGameUserSettings.SetArachnophobiaMode
struct UFGGameUserSettings_SetArachnophobiaMode_Params
{
	bool                                               newArachnophobiaMode;                                     // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.SetAnalyticsDisabled
struct UFGGameUserSettings_SetAnalyticsDisabled_Params
{
	bool                                               IsDisabled;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class UAnalyticsService*                           AnalyticsService;                                         // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.ResetAudioToCurrentSettings
struct UFGGameUserSettings_ResetAudioToCurrentSettings_Params
{
};

// Function FactoryGame.FGGameUserSettings.IsUsingCustomQualitySetting
struct UFGGameUserSettings_IsUsingCustomQualitySetting_Params
{
	class FString                                      SettingName;                                              // (Parm, ZeroConstructor)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.IsPostProcessUsingCustomSettings
struct UFGGameUserSettings_IsPostProcessUsingCustomSettings_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.IsMotionBlurEnabled
struct UFGGameUserSettings_IsMotionBlurEnabled_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.IsMotionBlurDirty
struct UFGGameUserSettings_IsMotionBlurDirty_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.GetRequireRestart
struct UFGGameUserSettings_GetRequireRestart_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.GetNeworkQuality
struct UFGGameUserSettings_GetNeworkQuality_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.GetKeyMappings
struct UFGGameUserSettings_GetKeyMappings_Params
{
	TArray<struct FFGKeyMapping>                       ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGGameUserSettings.GetInvertedLook
struct UFGGameUserSettings_GetInvertedLook_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.GetHoldToSprint
struct UFGGameUserSettings_GetHoldToSprint_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.GetHeadBobScale
struct UFGGameUserSettings_GetHeadBobScale_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.GetFOV
struct UFGGameUserSettings_GetFOV_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.GetFGGameUserSettings
struct UFGGameUserSettings_GetFGGameUserSettings_Params
{
	class UFGGameUserSettings*                         ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.GetDefaultQualitySetting
struct UFGGameUserSettings_GetDefaultQualitySetting_Params
{
	class FString                                      SettingName;                                              // (Parm, ZeroConstructor)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.GetAutoSortInventory
struct UFGGameUserSettings_GetAutoSortInventory_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.GetAudioVolume
struct UFGGameUserSettings_GetAudioVolume_Params
{
	class FString                                      Name;                                                     // (Parm, ZeroConstructor)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.GetArachnophobiaMode
struct UFGGameUserSettings_GetArachnophobiaMode_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.GetAnalyticsDisabled
struct UFGGameUserSettings_GetAnalyticsDisabled_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGameUserSettings.ClearRequireRestart
struct UFGGameUserSettings_ClearRequireRestart_Params
{
};

// Function FactoryGame.FGGlobalSettings.GetSubsystemClassesCDO
struct UFGGlobalSettings_GetSubsystemClassesCDO_Params
{
	class UFGSubsystemClasses*                         ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGlobalSettings.GetSignSettingsCDO
struct UFGGlobalSettings_GetSignSettingsCDO_Params
{
	class UFGSignSettings*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGlobalSettings.GetResourceSettingsCDO
struct UFGGlobalSettings_GetResourceSettingsCDO_Params
{
	class UFGResourceSettings*                         ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGlobalSettings.GetHardDriveSettingsCDO
struct UFGGlobalSettings_GetHardDriveSettingsCDO_Params
{
	class UFGHardDriveSettings*                        ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGlobalSettings.GetGlobalSettingsClassCDO
struct UFGGlobalSettings_GetGlobalSettingsClassCDO_Params
{
	class UFGGlobalSettings*                           ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGlobalSettings.GetFactorySettingsCDO
struct UFGGlobalSettings_GetFactorySettingsCDO_Params
{
	class UFGFactorySettings*                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGlobalSettings.GetEnvironmentSettingsCDO
struct UFGGlobalSettings_GetEnvironmentSettingsCDO_Params
{
	class UFGEnvironmentSettings*                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGGlobalSettings.GetDropPodSettingsCDO
struct UFGGlobalSettings_GetDropPodSettingsCDO_Params
{
	class UFGDropPodSettings*                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGHardDriveSettings.GetResearchRewardPackages
struct UFGHardDriveSettings_GetResearchRewardPackages_Params
{
	class UWorld*                                      World;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      calledByResearch;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FResearchRecipeReward>               ReturnValue;                                              // (ConstParm, Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGHealthComponent.TakeRadialDamage
struct UFGHealthComponent_TakeRadialDamage_Params
{
	class AActor*                                      damagedActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Damage;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     HitLocation;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  HitInfo;                                                  // (Parm, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHealthComponent.TakePointDamage
struct UFGHealthComponent_TakePointDamage_Params
{
	class AActor*                                      damagedActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Damage;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     HitLocation;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         HitComponent;                                             // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FName                                       BoneName;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ShotFromDirection;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHealthComponent.TakeDamage
struct UFGHealthComponent_TakeDamage_Params
{
	class AActor*                                      damagedActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              damageAmount;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHealthComponent.ReviveResetHealth
struct UFGHealthComponent_ReviveResetHealth_Params
{
};

// Function FactoryGame.FGHealthComponent.ResetHealthFromDeath
struct UFGHealthComponent_ResetHealthFromDeath_Params
{
};

// Function FactoryGame.FGHealthComponent.ResetHealth
struct UFGHealthComponent_ResetHealth_Params
{
};

// Function FactoryGame.FGHealthComponent.RemoveAdjustDamageListener
struct UFGHealthComponent_RemoveAdjustDamageListener_Params
{
	struct FScriptDelegate                             AdjustDamage;                                             // (Parm, ZeroConstructor)
};

// Function FactoryGame.FGHealthComponent.Kill
struct UFGHealthComponent_Kill_Params
{
};

// Function FactoryGame.FGHealthComponent.IsDead
struct UFGHealthComponent_IsDead_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGHealthComponent.Heal
struct UFGHealthComponent_Heal_Params
{
	float                                              healAmount;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHealthComponent.GetMaxHealth
struct UFGHealthComponent_GetMaxHealth_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGHealthComponent.GetCurrentHealth
struct UFGHealthComponent_GetCurrentHealth_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGHealthComponent.Client_TakeRadialDamage
struct UFGHealthComponent_Client_TakeRadialDamage_Params
{
	class AActor*                                      damagedActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Damage;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     HitLocation;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  HitInfo;                                                  // (Parm, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHealthComponent.Client_TakePointDamage
struct UFGHealthComponent_Client_TakePointDamage_Params
{
	class AActor*                                      damagedActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Damage;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     HitLocation;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         HitComponent;                                             // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FName                                       BoneName;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ShotFromDirection;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHealthComponent.Client_TakeDamage
struct UFGHealthComponent_Client_TakeDamage_Params
{
	class AActor*                                      damagedActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              damageAmount;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHealthComponent.Client_Heal
struct UFGHealthComponent_Client_Heal_Params
{
	float                                              amount;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHealthComponent.Client_Died
struct UFGHealthComponent_Client_Died_Params
{
	class AActor*                                      DeadActor;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHealthComponent.AddAdjustDamageListener
struct UFGHealthComponent_AddAdjustDamageListener_Params
{
	struct FScriptDelegate                             AdjustDamage;                                             // (Parm, ZeroConstructor)
};

// Function FactoryGame.FGHookshot.RestoreAudioSourceToOriginalLocation
struct AFGHookshot_RestoreAudioSourceToOriginalLocation_Params
{
};

// Function FactoryGame.FGHookshot.OwnerLanded
struct AFGHookshot_OwnerLanded_Params
{
	struct FHitResult                                  Hit;                                                      // (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function FactoryGame.FGHookshot.OnWireDetach
struct AFGHookshot_OnWireDetach_Params
{
};

// Function FactoryGame.FGHookshot.OnFire
struct AFGHookshot_OnFire_Params
{
	bool                                               attachedToSomething;                                      // (Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  HitResult;                                                // (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function FactoryGame.FGHookshot.MoveAudioSourceInFrontOfPlayer
struct AFGHookshot_MoveAudioSourceInFrontOfPlayer_Params
{
};

// Function FactoryGame.FGHUDBase.GetBaseUI
struct AFGHUDBase_GetBaseUI_Params
{
	class UFGBaseUI*                                   ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGHUD.UpdateCrosshairState
struct AFGHUD_UpdateCrosshairState_Params
{
	class AFGCharacterPlayer*                          Player;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHUD.UpdateCrosshairColorState
struct AFGHUD_UpdateCrosshairColorState_Params
{
	struct FLinearColor                                NewColor;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
};

// Function FactoryGame.FGHUD.ShowRespawnUI
struct AFGHUD_ShowRespawnUI_Params
{
};

// Function FactoryGame.FGHUD.SetShowCrossHair
struct AFGHUD_SetShowCrossHair_Params
{
	bool                                               showCrosshair;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHUD.SetPumpiMode
struct AFGHUD_SetPumpiMode_Params
{
	bool                                               hideHUD;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHUD.SetPreviewView
struct AFGHUD_SetPreviewView_Params
{
	struct FItemView                                   View;                                                     // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function FactoryGame.FGHUD.SetPreviewDistance
struct AFGHUD_SetPreviewDistance_Params
{
	float                                              previewDistance;                                          // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHUD.SetPreviewActorClass
struct AFGHUD_SetPreviewActorClass_Params
{
	class UClass*                                      ActorClass;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHUD.SetPartialPumpiMode
struct AFGHUD_SetPartialPumpiMode_Params
{
	bool                                               hideHUD;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHUD.SetHUDVisibility
struct AFGHUD_SetHUDVisibility_Params
{
	bool                                               hudVisibility;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHUD.SetForceHideCrossHair
struct AFGHUD_SetForceHideCrossHair_Params
{
	bool                                               forceHide;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHUD.SetCrustomCrosshairTexture
struct AFGHUD_SetCrustomCrosshairTexture_Params
{
	class UTexture2D*                                  newTexture;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHUD.SetCrosshairState
struct AFGHUD_SetCrosshairState_Params
{
	ECrosshairState                                    crosshairState;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHUD.RemoveEquipmentHUD
struct AFGHUD_RemoveEquipmentHUD_Params
{
	EEquipmentSlot                                     Slot;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHUD.OpenInteractUI
struct AFGHUD_OpenInteractUI_Params
{
	class UClass*                                      WidgetClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     interactObject;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHUD.GetShowCrosshair
struct AFGHUD_GetShowCrosshair_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGHUD.GetPumpiMode
struct AFGHUD_GetPumpiMode_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGHUD.GetPreviewTexture
struct AFGHUD_GetPreviewTexture_Params
{
	class UTextureRenderTarget2D*                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGHUD.GetPawnHUD
struct AFGHUD_GetPawnHUD_Params
{
	class UUserWidget*                                 ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGHUD.GetPartialPumpiMode
struct AFGHUD_GetPartialPumpiMode_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGHUD.GetHUDVisibility
struct AFGHUD_GetHUDVisibility_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGHUD.GetGameUI
struct AFGHUD_GetGameUI_Params
{
	class UFGGameUI*                                   ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGHUD.GetCrosshairState
struct AFGHUD_GetCrosshairState_Params
{
	ECrosshairState                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGHUD.EndPreviewActor
struct AFGHUD_EndPreviewActor_Params
{
};

// Function FactoryGame.FGHUD.CloseRespawnUI
struct AFGHUD_CloseRespawnUI_Params
{
};

// Function FactoryGame.FGHUD.BeginPreviewActor
struct AFGHUD_BeginPreviewActor_Params
{
};

// Function FactoryGame.FGHUD.AddPawnHUD
struct AFGHUD_AddPawnHUD_Params
{
	class UClass*                                      WidgetClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class APawn*                                       Pawn;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGHUD.AddEquipmentHUD
struct AFGHUD_AddEquipmentHUD_Params
{
	class UClass*                                      WidgetClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	EEquipmentSlot                                     Slot;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGInputLibrary.UpdateInputMappings
struct UFGInputLibrary_UpdateInputMappings_Params
{
	class APlayerController*                           PlayerController;                                         // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGInputLibrary.RebindKey
struct UFGInputLibrary_RebindKey_Params
{
	class APlayerController*                           PlayerController;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	struct FFGKeyMapping                               newKeyMapping;                                            // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInputLibrary.NullKeyMappingWithSameKeyCombo
struct UFGInputLibrary_NullKeyMappingWithSameKeyCombo_Params
{
	class APlayerController*                           PlayerController;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	struct FFGKeyMapping                               keyMapping;                                               // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function FactoryGame.FGInputLibrary.IsKeyMappingRelevant
struct UFGInputLibrary_IsKeyMappingRelevant_Params
{
	struct FName                                       keyMappingName;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInputLibrary.IsFGKeyMappingAvailable
struct UFGInputLibrary_IsFGKeyMappingAvailable_Params
{
	class APlayerController*                           PlayerController;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	struct FFGKeyMapping                               keyMapping;                                               // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInputLibrary.IsAxisMappingUsingSameKeys
struct UFGInputLibrary_IsAxisMappingUsingSameKeys_Params
{
	struct FInputAxisKeyMapping                        mappingA;                                                 // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FInputAxisKeyMapping                        mappingB;                                                 // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInputLibrary.IsAxisKeyMappingAvailable
struct UFGInputLibrary_IsAxisKeyMappingAvailable_Params
{
	class APlayerController*                           PlayerController;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	struct FFGKeyMapping                               keyMapping;                                               // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInputLibrary.IsActionMappingUsingSameKeys
struct UFGInputLibrary_IsActionMappingUsingSameKeys_Params
{
	struct FInputActionKeyMapping                      mappingA;                                                 // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FInputActionKeyMapping                      mappingB;                                                 // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInputLibrary.IsActionKeyMappingAvailable
struct UFGInputLibrary_IsActionKeyMappingAvailable_Params
{
	class APlayerController*                           PlayerController;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	struct FFGKeyMapping                               keyMapping;                                               // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInputLibrary.IsActionAndAxisMappingUsingSameKeys
struct UFGInputLibrary_IsActionAndAxisMappingUsingSameKeys_Params
{
	struct FInputActionKeyMapping                      actionMapping;                                            // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FInputAxisKeyMapping                        axisMapping;                                              // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInputLibrary.GetOverlappingKeyMapping
struct UFGInputLibrary_GetOverlappingKeyMapping_Params
{
	class APlayerController*                           PlayerController;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	struct FFGKeyMapping                               keyMapping;                                               // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FFGKeyMapping                               ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGInputLibrary.GetKeyNameForAxis
struct UFGInputLibrary_GetKeyNameForAxis_Params
{
	class APlayerController*                           PlayerController;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	struct FName                                       AxisName;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               positiveAxisScale;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               getGamepadKey;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGInputLibrary.GetKeyNameForAction
struct UFGInputLibrary_GetKeyNameForAction_Params
{
	class APlayerController*                           PlayerController;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	struct FName                                       ActionName;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               getGamepadKey;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               abbreviateKeyName;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGInputLibrary.GetKeyMappingForAction
struct UFGInputLibrary_GetKeyMappingForAction_Params
{
	class APlayerController*                           PlayerController;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	struct FName                                       inAction;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               getGamepadKey;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	struct FInputActionKeyMapping                      ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGInputLibrary.GetKeyForAxis
struct UFGInputLibrary_GetKeyForAxis_Params
{
	class APlayerController*                           PlayerController;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	struct FName                                       AxisName;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               positiveAxisScale;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               getGamepadKey;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	struct FKey                                        ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGInputLibrary.GetAbbreviatedKeyName
struct UFGInputLibrary_GetAbbreviatedKeyName_Params
{
	struct FKey                                        Key;                                                      // (Parm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGInputLibrary.FormatStringWithKeyNames
struct UFGInputLibrary_FormatStringWithKeyNames_Params
{
	class APlayerController*                           PlayerController;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       textToFormat;                                             // (Parm)
	bool                                               abbreviateKeyNames;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGInputLibrary.CreateFGKeyMappingStruct
struct UFGInputLibrary_CreateFGKeyMappingStruct_Params
{
	struct FName                                       ActionName;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               IsAxisMapping;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               positiveAxisScale;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	struct FInputEvent                                 InputEvent;                                               // (Parm)
	struct FKey                                        keyPressed;                                               // (Parm)
	struct FFGKeyMapping                               ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGInteractableMarker.SetTrackedActor
struct AFGInteractableMarker_SetTrackedActor_Params
{
	class AActor*                                      trackedActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGInteractableMarker.OnSetActorTracked
struct AFGInteractableMarker_OnSetActorTracked_Params
{
};

// Function FactoryGame.FGInteractableMarker.GetTrackedActor
struct AFGInteractableMarker_GetTrackedActor_Params
{
	class AActor*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInteractWidget.UpdateIgnoreMoveInput
struct UFGInteractWidget_UpdateIgnoreMoveInput_Params
{
};

// Function FactoryGame.FGInteractWidget.UpdateIgnoreLookInput
struct UFGInteractWidget_UpdateIgnoreLookInput_Params
{
};

// Function FactoryGame.FGInteractWidget.SetupDefaultFocus
struct UFGInteractWidget_SetupDefaultFocus_Params
{
};

// Function FactoryGame.FGInteractWidget.SetInputMode
struct UFGInteractWidget_SetInputMode_Params
{
};

// Function FactoryGame.FGInteractWidget.SetDesiredVerticalAlignment
struct UFGInteractWidget_SetDesiredVerticalAlignment_Params
{
	TEnumAsByte<EVerticalAlignment>                    newAlignment;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGInteractWidget.SetDesiredHorizontalAlignment
struct UFGInteractWidget_SetDesiredHorizontalAlignment_Params
{
	TEnumAsByte<EHorizontalAlignment>                  newAlignment;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGInteractWidget.SetDesiredAlignmentSize
struct UFGInteractWidget_SetDesiredAlignmentSize_Params
{
	struct FSlateChildSize                             newSize;                                                  // (Parm)
};

// Function FactoryGame.FGInteractWidget.SetDefaultFocusWidget
struct UFGInteractWidget_SetDefaultFocusWidget_Params
{
	class UWidget*                                     FocusWidget;                                              // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGInteractWidget.OnEscapePressed
struct UFGInteractWidget_OnEscapePressed_Params
{
};

// Function FactoryGame.FGInteractWidget.OnConsume
struct UFGInteractWidget_OnConsume_Params
{
};

// Function FactoryGame.FGInteractWidget.Init
struct UFGInteractWidget_Init_Params
{
};

// Function FactoryGame.FGInteractWidget.GetUseGamepadCursor
struct UFGInteractWidget_GetUseGamepadCursor_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInteractWidget.GetSupportsStacking
struct UFGInteractWidget_GetSupportsStacking_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInteractWidget.GetDesiredVerticalAlignment
struct UFGInteractWidget_GetDesiredVerticalAlignment_Params
{
	TEnumAsByte<EVerticalAlignment>                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInteractWidget.GetDesiredHorizontalAlignment
struct UFGInteractWidget_GetDesiredHorizontalAlignment_Params
{
	TEnumAsByte<EHorizontalAlignment>                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInteractWidget.GetDesiredAlignmentSize
struct UFGInteractWidget_GetDesiredAlignmentSize_Params
{
	struct FSlateChildSize                             ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGInteractWidget.GetDefaultFocusWidget
struct UFGInteractWidget_GetDefaultFocusWidget_Params
{
	class UWidget*                                     ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.SplitStackAtIdx
struct UFGInventoryComponent_SplitStackAtIdx_Params
{
	int                                                idx;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                numItemsToMove;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.SortInventory
struct UFGInventoryComponent_SortInventory_Params
{
};

// Function FactoryGame.FGInventoryComponent.SetCanBeRearranged
struct UFGInventoryComponent_SetCanBeRearranged_Params
{
	bool                                               canBeRearranged;                                          // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.SetAllowedItemOnIndex
struct UFGInventoryComponent_SetAllowedItemOnIndex_Params
{
	int                                                idx;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      allowedItemClass;                                         // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.Server_SortInventory
struct UFGInventoryComponent_Server_SortInventory_Params
{
};

// Function FactoryGame.FGInventoryComponent.Resize
struct UFGInventoryComponent_Resize_Params
{
	int                                                newSize;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.RemoveFromIndex
struct UFGInventoryComponent_RemoveFromIndex_Params
{
	int                                                idx;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                Num;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.RemoveAllFromIndex
struct UFGInventoryComponent_RemoveAllFromIndex_Params
{
	int                                                idx;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.Remove
struct UFGInventoryComponent_Remove_Params
{
	class UClass*                                      ItemClass;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                Num;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.OnRep_InventoryStacks
struct UFGInventoryComponent_OnRep_InventoryStacks_Params
{
};

// Function FactoryGame.FGInventoryComponent.IsValidIndex
struct UFGInventoryComponent_IsValidIndex_Params
{
	int                                                idx;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.IsSomethingOnIndex
struct UFGInventoryComponent_IsSomethingOnIndex_Params
{
	int                                                idx;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.IsItemAllowed
struct UFGInventoryComponent_IsItemAllowed_Params
{
	class UClass*                                      Item;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                idx;                                                      // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.IsIndexEmpty
struct UFGInventoryComponent_IsIndexEmpty_Params
{
	int                                                idx;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.IsEmpty
struct UFGInventoryComponent_IsEmpty_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.HasItems
struct UFGInventoryComponent_HasItems_Params
{
	class UClass*                                      ItemClass;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                Num;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.HasEnoughSpaceForStacks
struct UFGInventoryComponent_HasEnoughSpaceForStacks_Params
{
	TArray<struct FInventoryStack>                     stacks;                                                   // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.HasEnoughSpaceForStack
struct UFGInventoryComponent_HasEnoughSpaceForStack_Params
{
	struct FInventoryStack                             stack;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.HasEnoughSpaceForItem
struct UFGInventoryComponent_HasEnoughSpaceForItem_Params
{
	struct FInventoryItem                              stack;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.HasAuthority
struct UFGInventoryComponent_HasAuthority_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.GetStackFromIndex
struct UFGInventoryComponent_GetStackFromIndex_Params
{
	int                                                idx;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
	struct FInventoryStack                             out_stack;                                                // (Parm, OutParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.GetSlotSize
struct UFGInventoryComponent_GetSlotSize_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      itemDesc;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.GetSizeLinear
struct UFGInventoryComponent_GetSizeLinear_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.GetNumItems
struct UFGInventoryComponent_GetNumItems_Params
{
	class UClass*                                      ItemClass;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.GetInventoryStacks
struct UFGInventoryComponent_GetInventoryStacks_Params
{
	TArray<struct FInventoryStack>                     out_stacks;                                               // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGInventoryComponent.GetFullestStackIndex
struct UFGInventoryComponent_GetFullestStackIndex_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.GetCanBeRearranged
struct UFGInventoryComponent_GetCanBeRearranged_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.GetAllowedItemOnIndex
struct UFGInventoryComponent_GetAllowedItemOnIndex_Params
{
	int                                                idx;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.FindEmptyIndex
struct UFGInventoryComponent_FindEmptyIndex_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.Empty
struct UFGInventoryComponent_Empty_Params
{
};

// Function FactoryGame.FGInventoryComponent.CanSplitStackAtIdx
struct UFGInventoryComponent_CanSplitStackAtIdx_Params
{
	int                                                idx;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.AddStackToIndex
struct UFGInventoryComponent_AddStackToIndex_Params
{
	int                                                idx;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
	struct FInventoryStack                             stack;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               allowPartial;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.AddStacks
struct UFGInventoryComponent_AddStacks_Params
{
	TArray<struct FInventoryStack>                     stacks;                                                   // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function FactoryGame.FGInventoryComponent.AddStack
struct UFGInventoryComponent_AddStack_Params
{
	struct FInventoryStack                             stack;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               allowPartialAdd;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponent.AddArbitrarySlotSize
struct UFGInventoryComponent_AddArbitrarySlotSize_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                arbitrarySlotSize;                                        // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponentEquipment.GetEquipmentSlotEnum
struct UFGInventoryComponentEquipment_GetEquipmentSlotEnum_Params
{
	EEquipmentSlot                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponentEquipment.GetActiveIndex
struct UFGInventoryComponentEquipment_GetActiveIndex_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryComponentTrash.IsValidItem
struct UFGInventoryComponentTrash_IsValidItem_Params
{
	class UClass*                                      Resource;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryLibrary.MoveInventoryItem
struct UFGInventoryLibrary_MoveInventoryItem_Params
{
	class UFGInventoryComponent*                       SourceComponent;                                          // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                sourceIdx;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGInventoryComponent*                       destinationComponent;                                     // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                destinationIdx;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryLibrary.MergeInventoryItem
struct UFGInventoryLibrary_MergeInventoryItem_Params
{
	TArray<struct FInventoryStack>                     Items;                                                    // (Parm, OutParm, ZeroConstructor, ReferenceParm)
	struct FInventoryStack                             Item;                                                     // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function FactoryGame.FGInventoryLibrary.MakeInventoryStack
struct UFGInventoryLibrary_MakeInventoryStack_Params
{
	int                                                NumItems;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	struct FInventoryItem                              Item;                                                     // (Parm)
	struct FInventoryStack                             ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGInventoryLibrary.MakeInventoryItem
struct UFGInventoryLibrary_MakeInventoryItem_Params
{
	class UClass*                                      ItemClass;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FInventoryItem                              ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGInventoryLibrary.IsValidItem
struct UFGInventoryLibrary_IsValidItem_Params
{
	struct FInventoryItem                              Item;                                                     // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryLibrary.HasState
struct UFGInventoryLibrary_HasState_Params
{
	struct FInventoryItem                              Item;                                                     // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryLibrary.HasItems
struct UFGInventoryLibrary_HasItems_Params
{
	struct FInventoryStack                             stack;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryLibrary.GrabAllItemsFromInventory
struct UFGInventoryLibrary_GrabAllItemsFromInventory_Params
{
	class UFGInventoryComponent*                       SourceComponent;                                          // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGInventoryComponent*                       destinationComponent;                                     // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UClass*                                      onlyGrabOfDesc;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryLibrary.GetMinNumSlotsForItems
struct UFGInventoryLibrary_GetMinNumSlotsForItems_Params
{
	TArray<struct FInventoryStack>                     Items;                                                    // (Parm, OutParm, ZeroConstructor, ReferenceParm)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInventoryLibrary.CreateInventoryComponentOfClass
struct UFGInventoryLibrary_CreateInventoryComponentOfClass_Params
{
	class AActor*                                      Owner;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FName                                       Name;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGInventoryLibrary.CreateInventoryComponent
struct UFGInventoryLibrary_CreateInventoryComponent_Params
{
	class AActor*                                      Owner;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	struct FName                                       Name;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGInventoryLibrary.ConsolidateItemsAmount
struct UFGInventoryLibrary_ConsolidateItemsAmount_Params
{
	TArray<struct FItemAmount>                         Items;                                                    // (Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function FactoryGame.FGInventoryLibrary.ConsolidateInventoryItems
struct UFGInventoryLibrary_ConsolidateInventoryItems_Params
{
	TArray<struct FInventoryStack>                     Items;                                                    // (Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function FactoryGame.FGInventoryLibrary.BreakInventoryStack
struct UFGInventoryLibrary_BreakInventoryStack_Params
{
	struct FInventoryStack                             stack;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
	int                                                out_numItems;                                             // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	struct FInventoryItem                              out_item;                                                 // (Parm, OutParm)
};

// Function FactoryGame.FGInventoryLibrary.BreakInventoryItem
struct UFGInventoryLibrary_BreakInventoryItem_Params
{
	struct FInventoryItem                              Item;                                                     // (ConstParm, Parm, OutParm, ReferenceParm)
	class UClass*                                      out_itemClass;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      out_itemState;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGItemDescriptorNuclearFuel.GetSpentFuelClass
struct UFGItemDescriptorNuclearFuel_GetSpentFuelClass_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGItemDescriptorNuclearFuel.GetAmountWasteCreated
struct UFGItemDescriptorNuclearFuel_GetAmountWasteCreated_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGItemPickup.SetNumItems
struct AFGItemPickup_SetNumItems_Params
{
	int                                                NumItems;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGItemPickup.PlayPickupEffect
struct AFGItemPickup_PlayPickupEffect_Params
{
};

// Function FactoryGame.FGItemPickup.PickUpByCharacter
struct AFGItemPickup_PickUpByCharacter_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGItemPickup.PickupByAmount
struct AFGItemPickup_PickupByAmount_Params
{
	int                                                amount;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGItemPickup.OnRep_PickedUp
struct AFGItemPickup_OnRep_PickedUp_Params
{
};

// Function FactoryGame.FGItemPickup.OnPickup
struct AFGItemPickup_OnPickup_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGItemPickup.IsPickedUp
struct AFGItemPickup_IsPickedUp_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGItemPickup.GetPickupItems
struct AFGItemPickup_GetPickupItems_Params
{
	struct FInventoryStack                             ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGItemPickup.GetNumItems
struct AFGItemPickup_GetNumItems_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGItemPickup.GetNormalizedCollectionProgress
struct AFGItemPickup_GetNormalizedCollectionProgress_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGItemPickup_Spawnable.PlaySpawnEffect
struct AFGItemPickup_Spawnable_PlaySpawnEffect_Params
{
};

// Function FactoryGame.FGItemPickup_Spawnable.FindGroundLocationInfrontOfActor
struct AFGItemPickup_Spawnable_FindGroundLocationInfrontOfActor_Params
{
	class AActor*                                      sourceActor;                                              // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	float                                              offsetLength;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FInventoryStack                             Item;                                                     // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FVector                                     out_location;                                             // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	struct FRotator                                    out_rotation;                                             // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGItemPickup_Spawnable.FindGroundLocationAndRotation
struct AFGItemPickup_Spawnable_FindGroundLocationAndRotation_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     fromLocation;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class AActor*>                              ActorsToIgnore;                                           // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	struct FVector                                     out_location;                                             // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	struct FRotator                                    out_rotation;                                             // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGItemPickup_Spawnable.CreateItemDropsInCylinder
struct AFGItemPickup_Spawnable_CreateItemDropsInCylinder_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FInventoryStack>                     Items;                                                    // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	struct FVector                                     aroundLocation;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              SphereRadius;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class AActor*>                              ActorsToIgnore;                                           // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<class AFGItemPickup_Spawnable*>             out_itemDrops;                                            // (Parm, OutParm, ZeroConstructor)
	class UClass*                                      itemDropClass;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGItemPickup_Spawnable.CreateItemDrop
struct AFGItemPickup_Spawnable_CreateItemDrop_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FInventoryStack                             Item;                                                     // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FVector                                     SpawnLocation;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	struct FRotator                                    spawnRotation;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      itemDropClass;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGItemPickup_Spawnable*                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGItemPickup_Spawnable.AddItemToWorldStackAtLocation
struct AFGItemPickup_Spawnable_AddItemToWorldStackAtLocation_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FInventoryStack                             Item;                                                     // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FVector                                     SpawnLocation;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	struct FRotator                                    spawnRotation;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      itemDropClass;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGItemPickup_Spawnable*                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGJetPack.OnStopThrusting
struct AFGJetPack_OnStopThrusting_Params
{
};

// Function FactoryGame.FGJetPack.OnStartThrusting
struct AFGJetPack_OnStartThrusting_Params
{
};

// Function FactoryGame.FGJetPack.GetNewVelocityWhenThrusting
struct AFGJetPack_GetNewVelocityWhenThrusting_Params
{
	float                                              Delta;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGJetPack.GetMaxFuel
struct AFGJetPack_GetMaxFuel_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGJetPack.GetCurrentFuel
struct AFGJetPack_GetCurrentFuel_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGJetPack.CanThrust
struct AFGJetPack_CanThrust_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGJetPackAttachment.OnStopThrusting
struct AFGJetPackAttachment_OnStopThrusting_Params
{
};

// Function FactoryGame.FGJetPackAttachment.OnStartThrusting
struct AFGJetPackAttachment_OnStartThrusting_Params
{
};

// Function FactoryGame.FGJetPackAttachment.OnRep_IsThrusting
struct AFGJetPackAttachment_OnRep_IsThrusting_Params
{
};

// Function FactoryGame.FGJumpingStilts.GetNormalizedFallSpeedUntilDamaged
struct AFGJumpingStilts_GetNormalizedFallSpeedUntilDamaged_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGJumpingStilts.GetMaxFallSpeedBeforeDamage
struct AFGJumpingStilts_GetMaxFallSpeedBeforeDamage_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGJumpingStilts.GetCurrentFallSpeed
struct AFGJumpingStilts_GetCurrentFallSpeed_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGJumpingStilts.GetAdjustedZJumpSpeed
struct AFGJumpingStilts_GetAdjustedZJumpSpeed_Params
{
	float                                              defaultJumpZ;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGJumpingStilts.GetAdjustedMaxSpeed
struct AFGJumpingStilts_GetAdjustedMaxSpeed_Params
{
	float                                              defaultMaxSpeed;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGLadderComponent.EndPotentialClimberOverlap
struct UFGLadderComponent_EndPotentialClimberOverlap_Params
{
	class UPrimitiveComponent*                         OverlappedComp;                                           // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      Other;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGLadderComponent.BeginPotentialClimberOverlap
struct UFGLadderComponent_BeginPotentialClimberOverlap_Params
{
	class UPrimitiveComponent*                         OverlappedComp;                                           // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      Other;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               isFromSweep;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  SweepResult;                                              // (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function FactoryGame.FGListView.Refresh
struct UFGListView_Refresh_Params
{
};

// DelegateFunction FactoryGame.FGListView.OnGenerateRow__DelegateSignature
struct UFGListView_OnGenerateRow__DelegateSignature_Params
{
	int                                                Item;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	class UWidget*                                     ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// DelegateFunction FactoryGame.FGListView.GetNumRows__DelegateSignature
struct UFGListView_GetNumRows__DelegateSignature_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGLocalPlayer.UpdatePresence
struct UFGLocalPlayer_UpdatePresence_Params
{
};

// Function FactoryGame.FGLocalPlayer.OpenMap_SetupServer
struct UFGLocalPlayer_OpenMap_SetupServer_Params
{
};

// Function FactoryGame.FGLocalPlayer.GetUsername
struct UFGLocalPlayer_GetUsername_Params
{
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGLocalPlayer.GetLoginState
struct UFGLocalPlayer_GetLoginState_Params
{
	TEnumAsByte<ELoginState>                           ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGLocalPlayer.GetFriendList
struct UFGLocalPlayer_GetFriendList_Params
{
	TArray<struct FFGOnlineFriend>                     out_friends;                                              // (Parm, OutParm, ZeroConstructor)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGLocalPlayer.CreateOfflineSession_SetupServer
struct UFGLocalPlayer_CreateOfflineSession_SetupServer_Params
{
	bool                                               startOffline;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGLocalPlayer.AutoLogin
struct UFGLocalPlayer_AutoLogin_Params
{
};

// Function FactoryGame.FGLocomotive.UpdateTargetPoints
struct AFGLocomotive_UpdateTargetPoints_Params
{
	float                                              MaxDistance;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGLocomotive.UpdatePathSegment
struct AFGLocomotive_UpdatePathSegment_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGLocomotive.SetSelfDrivingEnabled
struct AFGLocomotive_SetSelfDrivingEnabled_Params
{
	bool                                               IsEnabled;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGLocomotive.SetPath
struct AFGLocomotive_SetPath_Params
{
	struct FRailroadPathFindingResult                  Result;                                                   // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGLocomotive.SetMultipleUnitControlMaster
struct AFGLocomotive_SetMultipleUnitControlMaster_Params
{
	bool                                               Force;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGLocomotive.ReportSelfDrivingError
struct AFGLocomotive_ReportSelfDrivingError_Params
{
	ESelfDrivingLocomotiveError                        Error;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGLocomotive.OnRep_ReplicatedMovementTransform
struct AFGLocomotive_OnRep_ReplicatedMovementTransform_Params
{
};

// Function FactoryGame.FGLocomotive.IsSelfDrivingEnabled
struct AFGLocomotive_IsSelfDrivingEnabled_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGLocomotive.HasPath
struct AFGLocomotive_HasPath_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGLocomotive.GetTargetPoints
struct AFGLocomotive_GetTargetPoints_Params
{
	TArray<struct FRailroadPathPoint>                  out_points;                                               // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGLocomotive.GetSelfDrivingError
struct AFGLocomotive_GetSelfDrivingError_Params
{
	ESelfDrivingLocomotiveError                        ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGLocomotive.GetPowerInfo
struct AFGLocomotive_GetPowerInfo_Params
{
	class UFGPowerInfoComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGLocomotive.GetPath
struct AFGLocomotive_GetPath_Params
{
	TArray<struct FRailroadPathPoint>                  out_points;                                               // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGLocomotive.GetMultipleUnitRole
struct AFGLocomotive_GetMultipleUnitRole_Params
{
	EMultipleUnitControl                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGLocomotive.GetLocomotiveMovementComponent
struct AFGLocomotive_GetLocomotiveMovementComponent_Params
{
	class UFGLocomotiveMovementComponent*              ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGLocomotive.ClearSelfDrivingError
struct AFGLocomotive_ClearSelfDrivingError_Params
{
};

// Function FactoryGame.FGLocomotive.ClearPath
struct AFGLocomotive_ClearPath_Params
{
};

// Function FactoryGame.FGLocomotive.ClearMultipleUnitControlMaster
struct AFGLocomotive_ClearMultipleUnitControlMaster_Params
{
};

// Function FactoryGame.FGLocomotive.CanSetTrainMultipleUnitMaster
struct AFGLocomotive_CanSetTrainMultipleUnitMaster_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicleMovementComponent.SetPayloadMass
struct UFGRailroadVehicleMovementComponent_SetPayloadMass_Params
{
	float                                              payload;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicleMovementComponent.IsMoving
struct UFGRailroadVehicleMovementComponent_IsMoving_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicleMovementComponent.GetWheelsetRotation
struct UFGRailroadVehicleMovementComponent_GetWheelsetRotation_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicleMovementComponent.GetWheelsetOffset
struct UFGRailroadVehicleMovementComponent_GetWheelsetOffset_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicleMovementComponent.GetWheelsetAngle
struct UFGRailroadVehicleMovementComponent_GetWheelsetAngle_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicleMovementComponent.GetWheelRotation
struct UFGRailroadVehicleMovementComponent_GetWheelRotation_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicleMovementComponent.GetTractiveForce
struct UFGRailroadVehicleMovementComponent_GetTractiveForce_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicleMovementComponent.GetTrackGrade
struct UFGRailroadVehicleMovementComponent_GetTrackGrade_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicleMovementComponent.GetTrackCurvature
struct UFGRailroadVehicleMovementComponent_GetTrackCurvature_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicleMovementComponent.GetRelativeForwardSpeed
struct UFGRailroadVehicleMovementComponent_GetRelativeForwardSpeed_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicleMovementComponent.GetPayloadMass
struct UFGRailroadVehicleMovementComponent_GetPayloadMass_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicleMovementComponent.GetNumWheelsets
struct UFGRailroadVehicleMovementComponent_GetNumWheelsets_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicleMovementComponent.GetMaxForwardSpeed
struct UFGRailroadVehicleMovementComponent_GetMaxForwardSpeed_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicleMovementComponent.GetMaxAirBrakingEffort
struct UFGRailroadVehicleMovementComponent_GetMaxAirBrakingEffort_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicleMovementComponent.GetMass
struct UFGRailroadVehicleMovementComponent_GetMass_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicleMovementComponent.GetForwardSpeed
struct UFGRailroadVehicleMovementComponent_GetForwardSpeed_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicleMovementComponent.GetDynamicBrakingForce
struct UFGRailroadVehicleMovementComponent_GetDynamicBrakingForce_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicleMovementComponent.GetCouplerRotationAndExtention
struct UFGRailroadVehicleMovementComponent_GetCouplerRotationAndExtention_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              out_extention;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicleMovementComponent.GetBrakingForce
struct UFGRailroadVehicleMovementComponent_GetBrakingForce_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicleMovementComponent.GetAirBrakingForce
struct UFGRailroadVehicleMovementComponent_GetAirBrakingForce_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGLocomotiveMovementComponent.UseReplicatedState
struct UFGLocomotiveMovementComponent_UseReplicatedState_Params
{
};

// Function FactoryGame.FGLocomotiveMovementComponent.SetThrottleInput
struct UFGLocomotiveMovementComponent_SetThrottleInput_Params
{
	float                                              Throttle;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGLocomotiveMovementComponent.SetSteeringInput
struct UFGLocomotiveMovementComponent_SetSteeringInput_Params
{
	float                                              Steering;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGLocomotiveMovementComponent.SetReverserInput
struct UFGLocomotiveMovementComponent_SetReverserInput_Params
{
	int                                                reverser;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGLocomotiveMovementComponent.SetEmergencyBrake
struct UFGLocomotiveMovementComponent_SetEmergencyBrake_Params
{
};

// Function FactoryGame.FGLocomotiveMovementComponent.SetAirBrakeInput
struct UFGLocomotiveMovementComponent_SetAirBrakeInput_Params
{
	float                                              Brake;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGLocomotiveMovementComponent.ServerUpdateState
struct UFGLocomotiveMovementComponent_ServerUpdateState_Params
{
	int                                                inReverserInput;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              InSteeringInput;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              InThrottleInput;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              inDynamicBrakeInput;                                      // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              inAirBrakeInput;                                          // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGLocomotiveMovementComponent.GetThrottle
struct UFGLocomotiveMovementComponent_GetThrottle_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGLocomotiveMovementComponent.GetReverser
struct UFGLocomotiveMovementComponent_GetReverser_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGLocomotiveMovementComponent.GetMaxTractiveEffort
struct UFGLocomotiveMovementComponent_GetMaxTractiveEffort_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGLocomotiveMovementComponent.GetMaxDynamicBrakingEffort
struct UFGLocomotiveMovementComponent_GetMaxDynamicBrakingEffort_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGLocomotiveMovementComponent.GetDynamicBrake
struct UFGLocomotiveMovementComponent_GetDynamicBrake_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGLocomotiveMovementComponent.GetAirBrake
struct UFGLocomotiveMovementComponent_GetAirBrake_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGLootSettings.GetLootSettingsDefaultObject
struct UFGLootSettings_GetLootSettingsDefaultObject_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGManta.GetSpline
struct AFGManta_GetSpline_Params
{
	class USplineComponent*                            ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGManta.GetCurrentTime
struct AFGManta_GetCurrentTime_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGManufacturingButton.SetButton
struct UFGManufacturingButton_SetButton_Params
{
	class UButton*                                     inButton;                                                 // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGManufacturingButton.OnReleasedButton
struct UFGManufacturingButton_OnReleasedButton_Params
{
};

// Function FactoryGame.FGManufacturingButton.OnPressedButton
struct UFGManufacturingButton_OnPressedButton_Params
{
};

// Function FactoryGame.FGMapArea.GetZoneType
struct UFGMapArea_GetZoneType_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGMapArea.GetUserSetAreaDisplayName
struct UFGMapArea_GetUserSetAreaDisplayName_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGMapArea.GetAreaDisplayName
struct UFGMapArea_GetAreaDisplayName_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGMapAreaTexture.OnNewMapAreaVisisted
struct UFGMapAreaTexture_OnNewMapAreaVisisted_Params
{
	class UClass*                                      newMapArea;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGMapAreaTexture.GetFogOfWarTexture
struct UFGMapAreaTexture_GetFogOfWarTexture_Params
{
	class UTexture2D*                                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGMapAreaZoneDescriptor.GetZoneType
struct UFGMapAreaZoneDescriptor_GetZoneType_Params
{
	class FString                                      out_zoneType;                                             // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGMapFunctionLibrary.GetWorldBounds
struct UFGMapFunctionLibrary_GetWorldBounds_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   Min;                                                      // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   Max;                                                      // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGMapFunctionLibrary.GetNormalizedPosition
struct UFGMapFunctionLibrary_GetNormalizedPosition_Params
{
	class AFGMinimapCaptureActor*                      minimapCaptureActor;                                      // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     WorldLocation;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGMapFunctionLibrary.GetMinimapCaptureActor
struct UFGMapFunctionLibrary_GetMinimapCaptureActor_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGMinimapCaptureActor*                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGMapFunctionLibrary.GetMapPosition
struct UFGMapFunctionLibrary_GetMapPosition_Params
{
	class AFGMinimapCaptureActor*                      minimapCaptureActor;                                      // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     WorldLocation;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              mapResolution;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGMapFunctionLibrary.GetMapDistance
struct UFGMapFunctionLibrary_GetMapDistance_Params
{
	class AFGMinimapCaptureActor*                      minimapCaptureActor;                                      // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	float                                              worldDistance;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              mapResolution;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGMapManager.OnActorRepresentationUpdated
struct AFGMapManager_OnActorRepresentationUpdated_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGMapManager.OnActorRepresentationRemoved
struct AFGMapManager_OnActorRepresentationRemoved_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGMapManager.OnActorRepresentationAdded
struct AFGMapManager_OnActorRepresentationAdded_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGMapManager.GetFogOfWarTexture
struct AFGMapManager_GetFogOfWarTexture_Params
{
	class UTexture2D*                                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGMapManager.Get
struct AFGMapManager_Get_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGMapManager*                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGMapObjectWidget.OnObjectMoved
struct UFGMapObjectWidget_OnObjectMoved_Params
{
	struct FVector2D                                   normalizedLocation;                                       // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGMapObjectWidget.OnObjectFiltered
struct UFGMapObjectWidget_OnObjectFiltered_Params
{
	bool                                               FilteredIn;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGMapObjectWidget.OnActorRepresentationUpdated
struct UFGMapObjectWidget_OnActorRepresentationUpdated_Params
{
};

// Function FactoryGame.FGMapWidget.OnObjectUpdatedOnMap
struct UFGMapWidget_OnObjectUpdatedOnMap_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGMapWidget.OnObjectRemovedFromMap
struct UFGMapWidget_OnObjectRemovedFromMap_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGMapWidget.OnObjectAddedToMap
struct UFGMapWidget_OnObjectAddedToMap_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGMapWidget.OnMapCentered
struct UFGMapWidget_OnMapCentered_Params
{
	struct FVector2D                                   normalizedWorldLocation;                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGMapWidget.OnActorRepresentationUpdated
struct UFGMapWidget_OnActorRepresentationUpdated_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGMapWidget.OnActorRepresentationRemoved
struct UFGMapWidget_OnActorRepresentationRemoved_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGMapWidget.OnActorRepresentationAdded
struct UFGMapWidget_OnActorRepresentationAdded_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGMapWidget.GetFogOfWarTexture
struct UFGMapWidget_GetFogOfWarTexture_Params
{
	class UTexture2D*                                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGMaterialEffectComponent.SetMeshes
struct UFGMaterialEffectComponent_SetMeshes_Params
{
	TArray<class UMeshComponent*>                      meshes;                                                   // (Parm, ZeroConstructor)
};

// Function FactoryGame.FGMaterialEffectComponent.SetMaterialScalarParameterValue
struct UFGMaterialEffectComponent_SetMaterialScalarParameterValue_Params
{
	struct FName                                       Name;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Value;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGMaterialEffectComponent.SetDuration
struct UFGMaterialEffectComponent_SetDuration_Params
{
	float                                              Duration;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGMaterialEffectComponent.PreStarted
struct UFGMaterialEffectComponent_PreStarted_Params
{
};

// Function FactoryGame.FGMaterialEffectComponent.OnUpdate
struct UFGMaterialEffectComponent_OnUpdate_Params
{
	float                                              DeltaTime;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGMaterialEffectComponent.OnStarted
struct UFGMaterialEffectComponent_OnStarted_Params
{
};

// Function FactoryGame.FGMaterialEffectComponent.OnEnded
struct UFGMaterialEffectComponent_OnEnded_Params
{
};

// Function FactoryGame.FGMaterialEffectComponent.GetMeshesBounds
struct UFGMaterialEffectComponent_GetMeshesBounds_Params
{
	bool                                               onlyVisible;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               onlyColliding;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     out_origin;                                               // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     out_boxExtent;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGMaterialEffectComponent.GetMeshes
struct UFGMaterialEffectComponent_GetMeshes_Params
{
	TArray<class UMeshComponent*>                      ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGMaterialEffectComponent.GetDuration
struct UFGMaterialEffectComponent_GetDuration_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGMaterialEffect_Build.GetSpeed
struct UFGMaterialEffect_Build_GetSpeed_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGMaterialEffect_Build.GetInstigator
struct UFGMaterialEffect_Build_GetInstigator_Params
{
	class AActor*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGMaterialEffect_Build.GetCost
struct UFGMaterialEffect_Build_GetCost_Params
{
	TArray<struct FItemAmount>                         ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGMaterialFlowAnalysisFunctionLibrary.PerformMaterialFlowAnalysis
struct UFGMaterialFlowAnalysisFunctionLibrary_PerformMaterialFlowAnalysis_Params
{
	TArray<class UClass*>                              recipes;                                                  // (Parm, ZeroConstructor)
	class AFGRecipeManager*                            recipeManager;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	struct FMaterialFlowGraph                          ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGMaterialFlowAnalysisFunctionLibrary.GetGraphNodes
struct UFGMaterialFlowAnalysisFunctionLibrary_GetGraphNodes_Params
{
	struct FMaterialFlowGraph                          graph;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
	int                                                Depth;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FMaterialFlowNode>                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGMaterialFlowAnalysisFunctionLibrary.GetGraphDepth
struct UFGMaterialFlowAnalysisFunctionLibrary_GetGraphDepth_Params
{
	struct FMaterialFlowGraph                          graph;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGMenuBase.OnMenuExitDone
struct UFGMenuBase_OnMenuExitDone_Params
{
};

// Function FactoryGame.FGMenuBase.OnMenuExit
struct UFGMenuBase_OnMenuExit_Params
{
	class UWidget*                                     prevMenu;                                                 // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               noAnimation;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGMenuBase.OnMenuEnterDone
struct UFGMenuBase_OnMenuEnterDone_Params
{
};

// Function FactoryGame.FGMenuBase.OnMenuEnter
struct UFGMenuBase_OnMenuEnter_Params
{
	class UWidget*                                     prevMenu;                                                 // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGMessageSender.GetSenderDefaultObject
struct UFGMessageSender_GetSenderDefaultObject_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGMinimapCaptureActor.GetMapAreaTexture
struct AFGMinimapCaptureActor_GetMapAreaTexture_Params
{
	class UFGMapAreaTexture*                           ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGMultiplayerVerticalBox.Sort
struct UFGMultiplayerVerticalBox_Sort_Params
{
};

// Function FactoryGame.FGMusicManager.Stop
struct UFGMusicManager_Stop_Params
{
};

// Function FactoryGame.FGMusicManager.Play
struct UFGMusicManager_Play_Params
{
};

// Function FactoryGame.FGMusicManager.Pause
struct UFGMusicManager_Pause_Params
{
};

// Function FactoryGame.FGMusicManager.OnPlayerNearBaseChanged
struct UFGMusicManager_OnPlayerNearBaseChanged_Params
{
	bool                                               isNear;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGMusicManager.OnPlayerEnteredArea
struct UFGMusicManager_OnPlayerEnteredArea_Params
{
	class UClass*                                      mapArea;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGMusicManager.NotifyPostLoadMap
struct UFGMusicManager_NotifyPostLoadMap_Params
{
	class UWorld*                                      loadedWorld;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class AWorldSettings*                              WorldSettings;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGMusicManager.Get
struct UFGMusicManager_Get_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGMusicManager*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPresenceLibrary.NetIdHasValidPresence
struct UFGPresenceLibrary_NetIdHasValidPresence_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FUniqueNetIdRepl                            netId;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPresenceLibrary.IsValid_OnlinePresence
struct UFGPresenceLibrary_IsValid_OnlinePresence_Params
{
	struct FOnlinePresence                             A;                                                        // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPresenceLibrary.IsPlayingThisGame
struct UFGPresenceLibrary_IsPlayingThisGame_Params
{
	struct FOnlinePresence                             presence;                                                 // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPresenceLibrary.IsPlayingOtherGame
struct UFGPresenceLibrary_IsPlayingOtherGame_Params
{
	struct FOnlinePresence                             presence;                                                 // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPresenceLibrary.IsOnline
struct UFGPresenceLibrary_IsOnline_Params
{
	struct FOnlinePresence                             presence;                                                 // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPresenceLibrary.GetSessionFromPresence
struct UFGPresenceLibrary_GetSessionFromPresence_Params
{
	struct FOnlinePresence                             presence;                                                 // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FBlueprintSessionResult                     ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGPresenceLibrary.GetPresenceString
struct UFGPresenceLibrary_GetPresenceString_Params
{
	struct FOnlinePresence                             presence;                                                 // (ConstParm, Parm, OutParm, ReferenceParm)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGPresenceLibrary.GetPresenceFromNetId
struct UFGPresenceLibrary_GetPresenceFromNetId_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FUniqueNetIdRepl                            netId;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FOnlinePresence                             ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGFriendsLibrary.IsWaitingForData
struct UFGFriendsLibrary_IsWaitingForData_Params
{
	class ULocalPlayer*                                friendOf;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	struct FFGOnlineFriend                             onlineFriend;                                             // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFriendsLibrary.IsValid_Friend
struct UFGFriendsLibrary_IsValid_Friend_Params
{
	struct FFGOnlineFriend                             A;                                                        // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFriendsLibrary.IsFriendJoinable
struct UFGFriendsLibrary_IsFriendJoinable_Params
{
	class ULocalPlayer*                                friendOf;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	struct FFGOnlineFriend                             onlineFriend;                                             // (ConstParm, Parm, OutParm, ReferenceParm)
	TEnumAsByte<ECantJoinReason>                       ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFriendsLibrary.GetFriendUniqueNetId
struct UFGFriendsLibrary_GetFriendUniqueNetId_Params
{
	struct FFGOnlineFriend                             onlineFriend;                                             // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FUniqueNetIdRepl                            ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGFriendsLibrary.GetFriendName
struct UFGFriendsLibrary_GetFriendName_Params
{
	class ULocalPlayer*                                friendOf;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	struct FFGOnlineFriend                             onlineFriend;                                             // (ConstParm, Parm, OutParm, ReferenceParm)
	class FString                                      out_displayName;                                          // (Parm, OutParm, ZeroConstructor)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGFriendsLibrary.GetFriendFromNetId
struct UFGFriendsLibrary_GetFriendFromNetId_Params
{
	class ULocalPlayer*                                friendOf;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	struct FUniqueNetIdRepl                            netId;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FFGOnlineFriend                             ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGFriendsLibrary.EqualEqual_FriendFriend
struct UFGFriendsLibrary_EqualEqual_FriendFriend_Params
{
	struct FFGOnlineFriend                             A;                                                        // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FFGOnlineFriend                             B;                                                        // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSessionLibrary.SetSessionVisibility
struct UFGSessionLibrary_SetSessionVisibility_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ESessionVisibility>                    Visibility;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGSessionLibrary.JoinSession
struct UFGSessionLibrary_JoinSession_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlueprintSessionResult                     session;                                                  // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function FactoryGame.FGSessionLibrary.IsSessionValid
struct UFGSessionLibrary_IsSessionValid_Params
{
	struct FBlueprintSessionResult                     session;                                                  // (Parm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSessionLibrary.IsInGameSession
struct UFGSessionLibrary_IsInGameSession_Params
{
	class ULocalPlayer*                                LocalPlayer;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSessionLibrary.InOnlineSession
struct UFGSessionLibrary_InOnlineSession_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FUniqueNetIdRepl                            PlayerId;                                                 // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSessionLibrary.GetSessionVisibility
struct UFGSessionLibrary_GetSessionVisibility_Params
{
	struct FBlueprintSessionResult                     session;                                                  // (ConstParm, Parm, OutParm, ReferenceParm)
	TEnumAsByte<ESessionVisibility>                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSessionLibrary.GetSessionSettings
struct UFGSessionLibrary_GetSessionSettings_Params
{
	struct FBlueprintSessionResult                     session;                                                  // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FFGOnlineSessionSettings                    ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGSessionLibrary.GetMySession
struct UFGSessionLibrary_GetMySession_Params
{
	class ULocalPlayer*                                LocalPlayer;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlueprintSessionResult                     ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGSessionLibrary.GetMaxNumberOfPlayers
struct UFGSessionLibrary_GetMaxNumberOfPlayers_Params
{
	struct FBlueprintSessionResult                     session;                                                  // (ConstParm, Parm, OutParm, ReferenceParm)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGInviteLibrary.SendInviteToFriend
struct UFGInviteLibrary_SendInviteToFriend_Params
{
	class ULocalPlayer*                                fromPlayer;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FFGOnlineFriend                             toFriend;                                                 // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function FactoryGame.FGInviteLibrary.JoinInvite
struct UFGInviteLibrary_JoinInvite_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FPendingInvite                              invite;                                                   // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function FactoryGame.FGInviteLibrary.GetPendingInvites
struct UFGInviteLibrary_GetPendingInvites_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FPendingInvite>                      out_invites;                                              // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGInviteLibrary.GetInviteSenderUniqueNetId
struct UFGInviteLibrary_GetInviteSenderUniqueNetId_Params
{
	struct FPendingInvite                              invite;                                                   // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FUniqueNetIdRepl                            ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGInviteLibrary.GetInviteFromSender
struct UFGInviteLibrary_GetInviteFromSender_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FUniqueNetIdRepl                            Sender;                                                   // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FPendingInvite                              ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGInviteLibrary.DiscardInvite
struct UFGInviteLibrary_DiscardInvite_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FPendingInvite                              invite;                                                   // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function FactoryGame.FGNetworkLibrary.SubmitFeedback
struct UFGNetworkLibrary_SubmitFeedback_Params
{
	struct FUserFeedbackFrontEndData                   frontEndFeedbackData;                                     // (Parm)
	class APlayerController*                           PlayerController;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGNetworkLibrary.QueryNATType
struct UFGNetworkLibrary_QueryNATType_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGNetworkLibrary.OpenWebURL
struct UFGNetworkLibrary_OpenWebURL_Params
{
	class FString                                      URL;                                                      // (Parm, ZeroConstructor)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGNetworkLibrary.NATTypeToText
struct UFGNetworkLibrary_NATTypeToText_Params
{
	ECachedNATType                                     natType;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGNetworkLibrary.IsValid_UniqueNetId
struct UFGNetworkLibrary_IsValid_UniqueNetId_Params
{
	struct FUniqueNetIdRepl                            A;                                                        // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGNetworkLibrary.IsServer
struct UFGNetworkLibrary_IsServer_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGNetworkLibrary.GetNameFromUniqueNetId
struct UFGNetworkLibrary_GetNameFromUniqueNetId_Params
{
	class ULocalPlayer*                                querier;                                                  // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	struct FUniqueNetIdRepl                            netId;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
	class FString                                      out_name;                                                 // (Parm, OutParm, ZeroConstructor)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGNetworkLibrary.GetCachedNATType
struct UFGNetworkLibrary_GetCachedNATType_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	ECachedNATType                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGNetworkLibrary.EqualEqual_NetIdNetId
struct UFGNetworkLibrary_EqualEqual_NetIdNetId_Params
{
	struct FUniqueNetIdRepl                            A;                                                        // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FUniqueNetIdRepl                            B;                                                        // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGNobeliskDetonator.Server_StartDetonations
struct AFGNobeliskDetonator_Server_StartDetonations_Params
{
};

// Function FactoryGame.FGNobeliskDetonator.Server_SpawnExplosive
struct AFGNobeliskDetonator_Server_SpawnExplosive_Params
{
	struct FTransform                                  SpawnTransform;                                           // (Parm, IsPlainOldData)
	int                                                throwForce;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGNobeliskDetonator.Server_ExecuteSecondaryFire
struct AFGNobeliskDetonator_Server_ExecuteSecondaryFire_Params
{
};

// Function FactoryGame.FGNobeliskDetonator.Server_ExecutePrimaryFire
struct AFGNobeliskDetonator_Server_ExecutePrimaryFire_Params
{
};

// Function FactoryGame.FGNobeliskDetonator.OnViewportFocusChanged
struct AFGNobeliskDetonator_OnViewportFocusChanged_Params
{
	bool                                               IsOpen;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      interactionClass;                                         // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGNobeliskDetonator.OnSecondaryFirePressed
struct AFGNobeliskDetonator_OnSecondaryFirePressed_Params
{
};

// Function FactoryGame.FGNobeliskDetonator.GetChargePct
struct AFGNobeliskDetonator_GetChargePct_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGNobeliskDetonator.ExecuteSecondaryFire
struct AFGNobeliskDetonator_ExecuteSecondaryFire_Params
{
};

// Function FactoryGame.FGNobeliskDetonator.ExecutePrimaryFire
struct AFGNobeliskDetonator_ExecutePrimaryFire_Params
{
};

// Function FactoryGame.FGWeaponAttachment.PlayFireEffect
struct AFGWeaponAttachment_PlayFireEffect_Params
{
	struct FVector                                     flashLocation;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGWeaponAttachment.Multicast_SetFlashLocation
struct AFGWeaponAttachment_Multicast_SetFlashLocation_Params
{
	struct FVector                                     newFlashLocation;                                         // (ConstParm, Parm, ZeroConstructor, ReferenceParm, IsPlainOldData)
};

// Function FactoryGame.FGWeaponAttachment.Multicast_PlayReloadEffectMulticast
struct AFGWeaponAttachment_Multicast_PlayReloadEffectMulticast_Params
{
};

// Function FactoryGame.FGWeaponAttachment.ClientPlayReloadEffect
struct AFGWeaponAttachment_ClientPlayReloadEffect_Params
{
};

// Function FactoryGame.FGNobeliskDetonatorAttachment.OnIsLoadedSet
struct AFGNobeliskDetonatorAttachment_OnIsLoadedSet_Params
{
};

// Function FactoryGame.FGNobeliskDetonatorAttachment.Multicast_SetIsLoaded
struct AFGNobeliskDetonatorAttachment_Multicast_SetIsLoaded_Params
{
	bool                                               isLoaded;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGNobeliskExplosive.OnRep_DetonateIn
struct AFGNobeliskExplosive_OnRep_DetonateIn_Params
{
};

// Function FactoryGame.FGNobeliskExplosiveAttachment.OnIsLoadedSet
struct AFGNobeliskExplosiveAttachment_OnIsLoadedSet_Params
{
};

// Function FactoryGame.FGNobeliskExplosiveAttachment.OnBeginFireEffect
struct AFGNobeliskExplosiveAttachment_OnBeginFireEffect_Params
{
	struct FVector                                     Location;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGNobeliskExplosiveAttachment.Multicast_SetIsLoaded
struct AFGNobeliskExplosiveAttachment_Multicast_SetIsLoaded_Params
{
	bool                                               isLoaded;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGNobeliskExplosiveAttachment.Multicast_PlayBeginFireEffect
struct AFGNobeliskExplosiveAttachment_Multicast_PlayBeginFireEffect_Params
{
	struct FVector                                     Location;                                                 // (ConstParm, Parm, ZeroConstructor, ReferenceParm, IsPlainOldData)
};

// Function FactoryGame.FGObjectScanner.UpdateScannerVisuals
struct AFGObjectScanner_UpdateScannerVisuals_Params
{
	bool                                               wasChange;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGObjectScanner.SetScannableEntry
struct AFGObjectScanner_SetScannableEntry_Params
{
	class UClass*                                      ScannableClass;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGObjectScanner.PlayBeep
struct AFGObjectScanner_PlayBeep_Params
{
	bool                                               isObjectInRange;                                          // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGObjectScanner.IsBeeping
struct AFGObjectScanner_IsBeeping_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGObjectScanner.GetCurrentDetails
struct AFGObjectScanner_GetCurrentDetails_Params
{
	struct FScannableDetails                           ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGObjectScanner.GetAvailableObjectDetails
struct AFGObjectScanner_GetAvailableObjectDetails_Params
{
	TArray<struct FScannableDetails>                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGObjectScanner.CycleForward
struct AFGObjectScanner_CycleForward_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGObjectScanner.CycleBackward
struct AFGObjectScanner_CycleBackward_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGObjectScannerAttachment.UpdateScannerVisuals
struct AFGObjectScannerAttachment_UpdateScannerVisuals_Params
{
};

// Function FactoryGame.FGObjectScannerAttachment.OnRep_ScannerLightColor
struct AFGObjectScannerAttachment_OnRep_ScannerLightColor_Params
{
};

// Function FactoryGame.FGObjectScannerAttachment.OnRep_IsBeeping
struct AFGObjectScannerAttachment_OnRep_IsBeeping_Params
{
};

// Function FactoryGame.FGObjectScannerAttachment.IsBeeping
struct AFGObjectScannerAttachment_IsBeeping_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGObjectScannerAttachment.GetScannerLightColor
struct AFGObjectScannerAttachment_GetScannerLightColor_Params
{
	struct FColor                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGOutlineComponent.UpdateProxyOutlineMesh
struct UFGOutlineComponent_UpdateProxyOutlineMesh_Params
{
	class UStaticMesh*                                 newOutlineMesh;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGOutlineComponent.UpdateProxyOutlineLocationAndRotation
struct UFGOutlineComponent_UpdateProxyOutlineLocationAndRotation_Params
{
	struct FVector                                     NewLocation;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FRotator                                    NewRotation;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGOutlineComponent.ShowProxyOutline
struct UFGOutlineComponent_ShowProxyOutline_Params
{
	class UStaticMesh*                                 outlineMesh;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FTransform                                  Transform;                                                // (ConstParm, Parm, IsPlainOldData)
	EOutlineColor                                      Color;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGOutlineComponent.ShowOutline
struct UFGOutlineComponent_ShowOutline_Params
{
	class AActor*                                      actorToOutline;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	EOutlineColor                                      Color;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGOutlineComponent.ShowMultiActorOutline
struct UFGOutlineComponent_ShowMultiActorOutline_Params
{
	TArray<class AActor*>                              actorsToOutline;                                          // (Parm, ZeroConstructor)
	EOutlineColor                                      Color;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGOutlineComponent.IsOutlineVisible
struct UFGOutlineComponent_IsOutlineVisible_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGOutlineComponent.HideOutline
struct UFGOutlineComponent_HideOutline_Params
{
};

// Function FactoryGame.FGOutlineComponent.GetOutlineColor
struct UFGOutlineComponent_GetOutlineColor_Params
{
	EOutlineColor                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGParachute.OnDeployStop
struct AFGParachute_OnDeployStop_Params
{
};

// Function FactoryGame.FGParachute.OnDeployed
struct AFGParachute_OnDeployed_Params
{
};

// Function FactoryGame.FGParachute.ModifyVelocity
struct AFGParachute_ModifyVelocity_Params
{
	float                                              DeltaTime;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     OldVelocity;                                              // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGParachute.IsDeployed
struct AFGParachute_IsDeployed_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGParachuteAttachment.OnRep_IsDeployed
struct AFGParachuteAttachment_OnRep_IsDeployed_Params
{
};

// Function FactoryGame.FGParachuteAttachment.OnDeployStop
struct AFGParachuteAttachment_OnDeployStop_Params
{
};

// Function FactoryGame.FGParachuteAttachment.OnDeployed
struct AFGParachuteAttachment_OnDeployed_Params
{
};

// Function FactoryGame.FGPassengerSeat.UpdateCamera
struct AFGPassengerSeat_UpdateCamera_Params
{
};

// Function FactoryGame.FGPassengerSeat.GetOuterVehicle
struct AFGPassengerSeat_GetOuterVehicle_Params
{
	class AFGVehicle*                                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlanet.UpdatePreview
struct AFGPlanet_UpdatePreview_Params
{
};

// Function FactoryGame.FGPlayerControllerBase.SetMouseSensitivity
struct AFGPlayerControllerBase_SetMouseSensitivity_Params
{
	float                                              newSense;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerControllerBase.SetIsUsingGamepad
struct AFGPlayerControllerBase_SetIsUsingGamepad_Params
{
	bool                                               newIsUsingGamepad;                                        // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerControllerBase.Server_UpdateCappedBandwidth
struct AFGPlayerControllerBase_Server_UpdateCappedBandwidth_Params
{
	int                                                Cap;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerControllerBase.ResetInputBindings
struct AFGPlayerControllerBase_ResetInputBindings_Params
{
};

// Function FactoryGame.FGPlayerControllerBase.RebindActionKey
struct AFGPlayerControllerBase_RebindActionKey_Params
{
	struct FFGKeyMapping                               newKeyMapping;                                            // (Parm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerControllerBase.GetPresenceString
struct AFGPlayerControllerBase_GetPresenceString_Params
{
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGPlayerControllerBase.GetMouseSensitivityY
struct AFGPlayerControllerBase_GetMouseSensitivityY_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerControllerBase.GetMouseSensitivityX
struct AFGPlayerControllerBase_GetMouseSensitivityX_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerControllerBase.GetMouseSensitivity
struct AFGPlayerControllerBase_GetMouseSensitivity_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerControllerBase.GetKeyNameForAction
struct AFGPlayerControllerBase_GetKeyNameForAction_Params
{
	struct FName                                       inAction;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               getGamepadKey;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGPlayerControllerBase.GetIsUsingGamepad
struct AFGPlayerControllerBase_GetIsUsingGamepad_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerControllerBase.GetDefaultMouseSensitivityY
struct AFGPlayerControllerBase_GetDefaultMouseSensitivityY_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerControllerBase.GetDefaultMouseSensitivityX
struct AFGPlayerControllerBase_GetDefaultMouseSensitivityX_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerControllerBase.GetDefaultMouseSensitivity
struct AFGPlayerControllerBase_GetDefaultMouseSensitivity_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerControllerBase.FlushPressedKeys
struct AFGPlayerControllerBase_FlushPressedKeys_Params
{
};

// Function FactoryGame.FGPlayerControllerBase.DiscardInput
struct AFGPlayerControllerBase_DiscardInput_Params
{
};

// Function FactoryGame.FGPlayerControllerBase.Client_UpdateCappedBandwidth
struct AFGPlayerControllerBase_Client_UpdateCappedBandwidth_Params
{
	int                                                Cap;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.TrackAkMemoryPools
struct AFGPlayerController_TrackAkMemoryPools_Params
{
};

// Function FactoryGame.FGPlayerController.TrackAkComponentsWithNoPositionOrOwner
struct AFGPlayerController_TrackAkComponentsWithNoPositionOrOwner_Params
{
};

// Function FactoryGame.FGPlayerController.TrackAkComponents
struct AFGPlayerController_TrackAkComponents_Params
{
	bool                                               byClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.TogglePhotoModeInstructionsWidget
struct AFGPlayerController_TogglePhotoModeInstructionsWidget_Params
{
};

// Function FactoryGame.FGPlayerController.TogglePhotoMode
struct AFGPlayerController_TogglePhotoMode_Params
{
};

// Function FactoryGame.FGPlayerController.ToggleHiResPhotoMode
struct AFGPlayerController_ToggleHiResPhotoMode_Params
{
};

// Function FactoryGame.FGPlayerController.TakePhoto
struct AFGPlayerController_TakePhoto_Params
{
};

// Function FactoryGame.FGPlayerController.Suicide
struct AFGPlayerController_Suicide_Params
{
};

// Function FactoryGame.FGPlayerController.StartRespawn
struct AFGPlayerController_StartRespawn_Params
{
};

// Function FactoryGame.FGPlayerController.SetSessionName
struct AFGPlayerController_SetSessionName_Params
{
	class FString                                      newSessionName;                                           // (Parm, ZeroConstructor)
};

// Function FactoryGame.FGPlayerController.SetRecipeShortcutOnIndex
struct AFGPlayerController_SetRecipeShortcutOnIndex_Params
{
	class UClass*                                      Recipe;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                onIndex;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.SetDismantleShortcutOnIndex
struct AFGPlayerController_SetDismantleShortcutOnIndex_Params
{
	int                                                onIndex;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.SetDisabledInputGate
struct AFGPlayerController_SetDisabledInputGate_Params
{
	struct FDisabledInputGate                          newDisabledInputGate;                                     // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.Server_Suicide
struct AFGPlayerController_Server_Suicide_Params
{
};

// Function FactoryGame.FGPlayerController.Server_StartRespawn
struct AFGPlayerController_Server_StartRespawn_Params
{
};

// Function FactoryGame.FGPlayerController.Server_SpawnAttentionPingActor
struct AFGPlayerController_Server_SpawnAttentionPingActor_Params
{
	struct FVector                                     pingLocation;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     pingNormal;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.Server_SetRecipeShortcutOnIndex
struct AFGPlayerController_Server_SetRecipeShortcutOnIndex_Params
{
	class UClass*                                      Recipe;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                onIndex;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.Server_SetDismantleShortcutOnIndex
struct AFGPlayerController_Server_SetDismantleShortcutOnIndex_Params
{
	int                                                onIndex;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.Server_SendChatMessage
struct AFGPlayerController_Server_SendChatMessage_Params
{
	struct FChatMessageStruct                          newMessage;                                               // (ConstParm, Parm, ReferenceParm)
};

// Function FactoryGame.FGPlayerController.Server_Respawn
struct AFGPlayerController_Server_Respawn_Params
{
};

// Function FactoryGame.FGPlayerController.Server_RequestFogOfWarData
struct AFGPlayerController_Server_RequestFogOfWarData_Params
{
};

// Function FactoryGame.FGPlayerController.Server_FinishRespawn
struct AFGPlayerController_Server_FinishRespawn_Params
{
};

// Function FactoryGame.FGPlayerController.Server_DealRadialDamage
struct AFGPlayerController_Server_DealRadialDamage_Params
{
	struct FHitResult                                  impact;                                                   // (ConstParm, Parm, ReferenceParm, IsPlainOldData)
	float                                              Damage;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Radius;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      DamageType;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      inInstigator;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.Server_DealImpactDamage
struct AFGPlayerController_Server_DealImpactDamage_Params
{
	struct FHitResult                                  impact;                                                   // (ConstParm, Parm, ReferenceParm, IsPlainOldData)
	struct FVector                                     forwardVector;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Damage;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      DamageType;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      inInstigator;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.RegisterRemoteCallObjectClass
struct AFGPlayerController_RegisterRemoteCallObjectClass_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGRemoteCallObject*                         ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.OnStartRespawn
struct AFGPlayerController_OnStartRespawn_Params
{
	bool                                               isJoining;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.OnSetupMovementWind
struct AFGPlayerController_OnSetupMovementWind_Params
{
	class UAkComponent*                                ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.OnRep_IsRespawning
struct AFGPlayerController_OnRep_IsRespawning_Params
{
};

// Function FactoryGame.FGPlayerController.OnPrimaryFire
struct AFGPlayerController_OnPrimaryFire_Params
{
};

// Function FactoryGame.FGPlayerController.OnFinishRespawn
struct AFGPlayerController_OnFinishRespawn_Params
{
};

// Function FactoryGame.FGPlayerController.OnDisabledInputGateChanged
struct AFGPlayerController_OnDisabledInputGateChanged_Params
{
};

// Function FactoryGame.FGPlayerController.NeedRespawn
struct AFGPlayerController_NeedRespawn_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.MaterialLookup
struct AFGPlayerController_MaterialLookup_Params
{
	class FString                                      ItemName;                                                 // (Parm, ZeroConstructor)
};

// Function FactoryGame.FGPlayerController.MaterialFlowAnalysis
struct AFGPlayerController_MaterialFlowAnalysis_Params
{
	class FString                                      recipeName;                                               // (Parm, ZeroConstructor)
};

// Function FactoryGame.FGPlayerController.IsRespawning
struct AFGPlayerController_IsRespawning_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.IsInTutorialMode
struct AFGPlayerController_IsInTutorialMode_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.IncrementPhotoModeFOV
struct AFGPlayerController_IncrementPhotoModeFOV_Params
{
};

// Function FactoryGame.FGPlayerController.GetValidShortcuts
struct AFGPlayerController_GetValidShortcuts_Params
{
	TArray<class UFGHotbarShortcut*>                   out_shortcuts;                                            // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGPlayerController.GetShortcutIndexFromKey
struct AFGPlayerController_GetShortcutIndexFromKey_Params
{
	struct FKeyEvent                                   Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.GetScreenshotPath
struct AFGPlayerController_GetScreenshotPath_Params
{
	bool                                               isHighRes;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGPlayerController.GetScreenBasedObjectRadius
struct AFGPlayerController_GetScreenBasedObjectRadius_Params
{
	class AActor*                                      Actor;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              screenRadius;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.GetRemoteCallObjectOfClass
struct AFGPlayerController_GetRemoteCallObjectOfClass_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGRemoteCallObject*                         ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.GetRecipeShortcutIndex
struct AFGPlayerController_GetRecipeShortcutIndex_Params
{
	class UClass*                                      Recipe;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.GetPlayerHasMessage
struct AFGPlayerController_GetPlayerHasMessage_Params
{
	class UClass*                                      newMessage;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.GetPhotoModeFOV
struct AFGPlayerController_GetPhotoModeFOV_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.GetObjectScreenRadius
struct AFGPlayerController_GetObjectScreenRadius_Params
{
	class AActor*                                      Actor;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              boundingRadius;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.GetIsPhotoMode
struct AFGPlayerController_GetIsPhotoMode_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.GetHiResPhotoModeEnabled
struct AFGPlayerController_GetHiResPhotoModeEnabled_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.GetDismantleShortcutIndex
struct AFGPlayerController_GetDismantleShortcutIndex_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.GetDisabledInputGate
struct AFGPlayerController_GetDisabledInputGate_Params
{
	struct FDisabledInputGate                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.GetCurrentMapArea
struct AFGPlayerController_GetCurrentMapArea_Params
{
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.GetAllShortcuts
struct AFGPlayerController_GetAllShortcuts_Params
{
	TArray<class UFGHotbarShortcut*>                   out_shortcuts;                                            // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGPlayerController.ExecuteShortcut
struct AFGPlayerController_ExecuteShortcut_Params
{
	int                                                shortcutIndex;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.EnterChatMessage
struct AFGPlayerController_EnterChatMessage_Params
{
	class FString                                      inMessage;                                                // (Parm, ZeroConstructor)
};

// Function FactoryGame.FGPlayerController.EnablePhotoMode
struct AFGPlayerController_EnablePhotoMode_Params
{
	bool                                               IsEnabled;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.DecrementPhotoModeFOV
struct AFGPlayerController_DecrementPhotoModeFOV_Params
{
};

// Function FactoryGame.FGPlayerController.CreateSequenceList
struct AFGPlayerController_CreateSequenceList_Params
{
};

// Function FactoryGame.FGPlayerController.Client_WaitForLevelStreaming
struct AFGPlayerController_Client_WaitForLevelStreaming_Params
{
};

// Function FactoryGame.FGPlayerController.Client_TransferFogOfWarData
struct AFGPlayerController_Client_TransferFogOfWarData_Params
{
	TArray<unsigned char>                              fogOfWarRawData;                                          // (ConstParm, Parm, ZeroConstructor, ReferenceParm)
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.Client_AddMessage
struct AFGPlayerController_Client_AddMessage_Params
{
	class UClass*                                      newMessage;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerController.CheckPawnMapArea
struct AFGPlayerController_CheckPawnMapArea_Params
{
};

// Function FactoryGame.FGPlayerState.Server_RemoveRecipe
struct AFGPlayerState_Server_RemoveRecipe_Params
{
	class UClass*                                      Recipe;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerState.RemoveRecipe
struct AFGPlayerState_RemoveRecipe_Params
{
	class UClass*                                      Recipe;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerState.RemoveMessage
struct AFGPlayerState_RemoveMessage_Params
{
	class UClass*                                      inMessage;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerState.ReadMessage
struct AFGPlayerState_ReadMessage_Params
{
	class UClass*                                      inMessage;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerState.OnRep_HotbarShortcuts
struct AFGPlayerState_OnRep_HotbarShortcuts_Params
{
};

// Function FactoryGame.FGPlayerState.GetUsername
struct AFGPlayerState_GetUsername_Params
{
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGPlayerState.GetUserID
struct AFGPlayerState_GetUserID_Params
{
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGPlayerState.GetUniqeNetId
struct AFGPlayerState_GetUniqeNetId_Params
{
	struct FUniqueNetIdRepl                            ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGPlayerState.GetTutorialSubsystem
struct AFGPlayerState_GetTutorialSubsystem_Params
{
	class UFGTutorialSubsystem*                        ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerState.GetSteamID
struct AFGPlayerState_GetSteamID_Params
{
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGPlayerState.GetSlotNum
struct AFGPlayerState_GetSlotNum_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerState.GetSlotData
struct AFGPlayerState_GetSlotData_Params
{
	TArray<struct FSlotData>                           ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGPlayerState.GetNumArmSlots
struct AFGPlayerState_GetNumArmSlots_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerState.GetAllMessages
struct AFGPlayerState_GetAllMessages_Params
{
	EMessageType                                       MessageType;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class UClass*>                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGPlayerState.GetAllMessageData
struct AFGPlayerState_GetAllMessageData_Params
{
	TArray<struct FMessageData>                        ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGPlayerState.CreateShortcut
struct AFGPlayerState_CreateShortcut_Params
{
	class UClass*                                      shortcutClass;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGHotbarShortcut*                           ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPlayerState.AddMessage
struct AFGPlayerState_AddMessage_Params
{
	class UClass*                                      inMessage;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPlayerState.AddArmSlots
struct AFGPlayerState_AddArmSlots_Params
{
	int                                                slotsToAdd;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPoleDescriptor.GetHeightMeshes
struct UFGPoleDescriptor_GetHeightMeshes_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FPoleHeightMesh>                     out_heightMeshes;                                         // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGPopupInstigatorInterface.WidgetFactory
struct UFGPopupInstigatorInterface_WidgetFactory_Params
{
	class UClass*                                      PopupClass;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class UUserWidget*>                         out_widgets;                                              // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGPopupInstigatorInterface.NotifyPopupClosed
struct UFGPopupInstigatorInterface_NotifyPopupClosed_Params
{
	class UClass*                                      PopupClass;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                exitCode;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPopupWidget.CallPopupConfirmClicked
struct UFGPopupWidget_CallPopupConfirmClicked_Params
{
};

// Function FactoryGame.FGPopupWidget.CallPopupClosedClicked
struct UFGPopupWidget_CallPopupClosedClicked_Params
{
	bool                                               confirm;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPopupWidgetContent.SetOptionalTextElements
struct UFGPopupWidgetContent_SetOptionalTextElements_Params
{
	struct FText                                       Title;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FText                                       Desc;                                                     // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function FactoryGame.FGPopupWidgetContent.SetInstigatorAndInitialize
struct UFGPopupWidgetContent_SetInstigatorAndInitialize_Params
{
	class UObject*                                     Instigator;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPopupWidgetContent.NotifyPopupConfirmed
struct UFGPopupWidgetContent_NotifyPopupConfirmed_Params
{
};

// Function FactoryGame.FGPopupWidgetContent.NotifyPopupCanceled
struct UFGPopupWidgetContent_NotifyPopupCanceled_Params
{
};

// Function FactoryGame.FGPopupWidgetContent.GetShouldOkayBeEnabled
struct UFGPopupWidgetContent_GetShouldOkayBeEnabled_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPortableMiner.OnRep_IsProducing
struct AFGPortableMiner_OnRep_IsProducing_Params
{
};

// Function FactoryGame.FGPortableMiner.IsProducing
struct AFGPortableMiner_IsProducing_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPortableMiner.GetOutputInventory
struct AFGPortableMiner_GetOutputInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGPortableMiner.GetExtractionProgress
struct AFGPortableMiner_GetExtractionProgress_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPortableMiner.GetDismantleInventoryReturns
struct AFGPortableMiner_GetDismantleInventoryReturns_Params
{
	TArray<struct FInventoryStack>                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGPortableMiner.CanProduce
struct AFGPortableMiner_CanProduce_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPortableMinerDispenser.SpawnPortableMiner
struct AFGPortableMinerDispenser_SpawnPortableMiner_Params
{
	class AFGResourceNode*                             resourceNode;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPortableMinerDispenser.Server_PrimaryFire
struct AFGPortableMinerDispenser_Server_PrimaryFire_Params
{
};

// Function FactoryGame.FGPowerCircuit.ResetFuse
struct UFGPowerCircuit_ResetFuse_Params
{
};

// Function FactoryGame.FGPowerCircuit.IsFuseTriggered
struct UFGPowerCircuit_IsFuseTriggered_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPowerCircuit.GetStats
struct UFGPowerCircuit_GetStats_Params
{
	struct FPowerCircuitStats                          out_stats;                                                // (Parm, OutParm)
};

// Function FactoryGame.FGPowerCircuit.GetNumGraphPoint
struct UFGPowerCircuit_GetNumGraphPoint_Params
{
	struct FPowerCircuitStats                          stats;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPowerCircuit.GetGraphPointAtIndex
struct UFGPowerCircuit_GetGraphPointAtIndex_Params
{
	struct FPowerCircuitStats                          stats;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
	int                                                idx;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
	struct FPowerGraphPoint                            out_item;                                                 // (Parm, OutParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// DelegateFunction FactoryGame.FGPowerCircuitWidget.GetPowerCircuit__DelegateSignature
struct UFGPowerCircuitWidget_GetPowerCircuit__DelegateSignature_Params
{
	class UFGPowerCircuit*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPowerCircuitWidget.GetPowerCircuit
struct UFGPowerCircuitWidget_GetPowerCircuit_Params
{
	class UFGPowerCircuit*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPowerConnectionComponent.SetPowerInfo
struct UFGPowerConnectionComponent_SetPowerInfo_Params
{
	class UFGPowerInfoComponent*                       powerInfo;                                                // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGPowerConnectionComponent.GetPowerInfo
struct UFGPowerConnectionComponent_GetPowerInfo_Params
{
	class UFGPowerInfoComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGPowerConnectionComponent.GetPowerCircuit
struct UFGPowerConnectionComponent_GetPowerCircuit_Params
{
	class UFGPowerCircuit*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPowerInfoComponent.SetTargetConsumption
struct UFGPowerInfoComponent_SetTargetConsumption_Params
{
	float                                              newConsumption;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPowerInfoComponent.SetDynamicProductionCapacity
struct UFGPowerInfoComponent_SetDynamicProductionCapacity_Params
{
	float                                              newProduction;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPowerInfoComponent.SetBaseProduction
struct UFGPowerInfoComponent_SetBaseProduction_Params
{
	float                                              newProduction;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGPowerInfoComponent.IsFuseTriggered
struct UFGPowerInfoComponent_IsFuseTriggered_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPowerInfoComponent.IsConnected
struct UFGPowerInfoComponent_IsConnected_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPowerInfoComponent.HasPower
struct UFGPowerInfoComponent_HasPower_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPowerInfoComponent.GetTargetConsumption
struct UFGPowerInfoComponent_GetTargetConsumption_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPowerInfoComponent.GetRegulatedDynamicProduction
struct UFGPowerInfoComponent_GetRegulatedDynamicProduction_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPowerInfoComponent.GetPowerCircuit
struct UFGPowerInfoComponent_GetPowerCircuit_Params
{
	class UFGPowerCircuit*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPowerInfoComponent.GetDynamicProductionDemandFactor
struct UFGPowerInfoComponent_GetDynamicProductionDemandFactor_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPowerInfoComponent.GetDynamicProductionCapacity
struct UFGPowerInfoComponent_GetDynamicProductionCapacity_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPowerInfoComponent.GetBaseProduction
struct UFGPowerInfoComponent_GetBaseProduction_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGPowerInfoComponent.GetActualConsumption
struct UFGPowerInfoComponent_GetActualConsumption_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGProfileSpline.StartProfile
struct AFGProfileSpline_StartProfile_Params
{
};

// Function FactoryGame.FGRadiationInterface.ReceiveRadiation
struct UFGRadiationInterface_ReceiveRadiation_Params
{
	float                                              amount;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Duration;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Direction;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      DamageType;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGRadioactivitySubsystem.OnActorSpawned
struct AFGRadioactivitySubsystem_OnActorSpawned_Params
{
	class AActor*                                      SpawnedActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGRadioactivitySubsystem.OnActorDestroyed
struct AFGRadioactivitySubsystem_OnActorDestroyed_Params
{
	class AActor*                                      DestroyedActor;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGRadioactivitySubsystem.Get
struct AFGRadioactivitySubsystem_Get_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGRadioactivitySubsystem*                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadFunctionLibrary.IsValid
struct UFGRailroadFunctionLibrary_IsValid_Params
{
	struct FRailroadTrackPosition                      Position;                                                 // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadFunctionLibrary.GetWorldLocationAndDirection
struct UFGRailroadFunctionLibrary_GetWorldLocationAndDirection_Params
{
	struct FRailroadTrackPosition                      Position;                                                 // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FVector                                     out_location;                                             // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     out_direction;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGRailroadFunctionLibrary.GetTrack
struct UFGRailroadFunctionLibrary_GetTrack_Params
{
	struct FRailroadTrackPosition                      Position;                                                 // (ConstParm, Parm, OutParm, ReferenceParm)
	class AFGBuildableRailroadTrack*                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadFunctionLibrary.DrawDebugTrackPosition
struct UFGRailroadFunctionLibrary_DrawDebugTrackPosition_Params
{
	struct FRailroadTrackPosition                      Position;                                                 // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FColor                                      Color;                                                    // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	bool                                               isPersistentLines;                                        // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGRailroadFunctionLibrary.DrawDebugRailroadPathResult
struct UFGRailroadFunctionLibrary_DrawDebugRailroadPathResult_Params
{
	struct FRailroadTrackPosition                      Start;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FRailroadPathFindingResult                  Result;                                                   // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               isPersistentLines;                                        // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGRailroadInterface.UnregisteredFromTrack
struct UFGRailroadInterface_UnregisteredFromTrack_Params
{
};

// Function FactoryGame.FGRailroadInterface.RegisteredOnTrack
struct UFGRailroadInterface_RegisteredOnTrack_Params
{
	struct FRailroadTrackPosition                      Position;                                                 // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function FactoryGame.FGRailroadInterface.GetTrackPosition
struct UFGRailroadInterface_GetTrackPosition_Params
{
	struct FRailroadTrackPosition                      ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGRailroadInterface.GetTrackGraphID
struct UFGRailroadInterface_GetTrackGraphID_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadSubsystem.GetTrainStations
struct AFGRailroadSubsystem_GetTrainStations_Params
{
	int                                                trackID;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class AFGTrainStationIdentifier*>           out_stations;                                             // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGRailroadSubsystem.GetTrains
struct AFGRailroadSubsystem_GetTrains_Params
{
	int                                                trackID;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class AFGTrain*>                            out_trains;                                               // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGRailroadSubsystem.GetAllTrainStations
struct AFGRailroadSubsystem_GetAllTrainStations_Params
{
	TArray<class AFGTrainStationIdentifier*>           out_stations;                                             // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGRailroadSubsystem.GetAllTrains
struct AFGRailroadSubsystem_GetAllTrains_Params
{
	TArray<class AFGTrain*>                            out_trains;                                               // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGRailroadSubsystem.Get
struct AFGRailroadSubsystem_Get_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGRailroadSubsystem*                        ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadSubsystem.FindPathSync
struct AFGRailroadSubsystem_FindPathSync_Params
{
	class AFGLocomotive*                               Locomotive;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGTrainStationIdentifier*                   Station;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FRailroadPathFindingResult                  ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGRailroadTimeTable.SetStops
struct AFGRailroadTimeTable_SetStops_Params
{
	TArray<struct FTimeTableStop>                      stops;                                                    // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadTimeTable.SetStopDuration
struct AFGRailroadTimeTable_SetStopDuration_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Duration;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGRailroadTimeTable.SetCurrentStop
struct AFGRailroadTimeTable_SetCurrentStop_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGRailroadTimeTable.RemoveStop
struct AFGRailroadTimeTable_RemoveStop_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGRailroadTimeTable.IsValidStop
struct AFGRailroadTimeTable_IsValidStop_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadTimeTable.GetStops
struct AFGRailroadTimeTable_GetStops_Params
{
	TArray<struct FTimeTableStop>                      out_stops;                                                // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGRailroadTimeTable.GetStop
struct AFGRailroadTimeTable_GetStop_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	struct FTimeTableStop                              ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGRailroadTimeTable.GetNumStops
struct AFGRailroadTimeTable_GetNumStops_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadTimeTable.GetMaxNumStops
struct AFGRailroadTimeTable_GetMaxNumStops_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadTimeTable.GetCurrentStop
struct AFGRailroadTimeTable_GetCurrentStop_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadTimeTable.AddStop
struct AFGRailroadTimeTable_AddStop_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	struct FTimeTableStop                              Stop;                                                     // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadTrackConnectionComponent.SetSwitchPosition
struct UFGRailroadTrackConnectionComponent_SetSwitchPosition_Params
{
	int                                                Position;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGRailroadTrackConnectionComponent.GetSwitchPosition
struct UFGRailroadTrackConnectionComponent_GetSwitchPosition_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadTrackConnectionComponent.GetNumSwitchPositions
struct UFGRailroadTrackConnectionComponent_GetNumSwitchPositions_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRailroadTrackConnectionComponent.GetConnection
struct UFGRailroadTrackConnectionComponent_GetConnection_Params
{
	int                                                Position;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGRailroadTrackConnectionComponent*         ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGRailroadVehicleSoundComponent.UpdateRTPCs
struct UFGRailroadVehicleSoundComponent_UpdateRTPCs_Params
{
};

// Function FactoryGame.FGRailroadVehicleSoundComponent.OnThrottleReleased
struct UFGRailroadVehicleSoundComponent_OnThrottleReleased_Params
{
};

// Function FactoryGame.FGRailroadVehicleSoundComponent.OnThrottleApplied
struct UFGRailroadVehicleSoundComponent_OnThrottleApplied_Params
{
};

// Function FactoryGame.FGRailroadVehicleSoundComponent.OnStoppedMoving
struct UFGRailroadVehicleSoundComponent_OnStoppedMoving_Params
{
};

// Function FactoryGame.FGRailroadVehicleSoundComponent.OnStartedMoving
struct UFGRailroadVehicleSoundComponent_OnStartedMoving_Params
{
};

// Function FactoryGame.FGRailroadVehicleSoundComponent.OnDynamicBrakesReleased
struct UFGRailroadVehicleSoundComponent_OnDynamicBrakesReleased_Params
{
};

// Function FactoryGame.FGRailroadVehicleSoundComponent.OnDynamicBrakesApplied
struct UFGRailroadVehicleSoundComponent_OnDynamicBrakesApplied_Params
{
};

// Function FactoryGame.FGRailroadVehicleSoundComponent.OnAirBrakesReleased
struct UFGRailroadVehicleSoundComponent_OnAirBrakesReleased_Params
{
};

// Function FactoryGame.FGRailroadVehicleSoundComponent.OnAirBrakesApplied
struct UFGRailroadVehicleSoundComponent_OnAirBrakesApplied_Params
{
};

// Function FactoryGame.FGRecipe.SortByName
struct UFGRecipe_SortByName_Params
{
	TArray<class UClass*>                              recipes;                                                  // (Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function FactoryGame.FGRecipe.GetRewardedRecipes
struct UFGRecipe_GetRewardedRecipes_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class UClass*>                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGRecipe.GetRecipeName
struct UFGRecipe_GetRecipeName_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGRecipe.GetProducts
struct UFGRecipe_GetProducts_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               allowChildRecipes;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FItemAmount>                         ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGRecipe.GetProducedIn
struct UFGRecipe_GetProducedIn_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class UClass*>                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGRecipe.GetManufacturingDuration
struct UFGRecipe_GetManufacturingDuration_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRecipe.GetIngredients
struct UFGRecipe_GetIngredients_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FItemAmount>                         ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGRecipeManager.IsRecipeAvailable
struct AFGRecipeManager_IsRecipeAvailable_Params
{
	class UClass*                                      recipeClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRecipeManager.GetAvailableRecipesForProducer
struct AFGRecipeManager_GetAvailableRecipesForProducer_Params
{
	class UClass*                                      forProducer;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class UClass*>                              out_recipes;                                              // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGRecipeManager.GetAllAvailableRecipes
struct AFGRecipeManager_GetAllAvailableRecipes_Params
{
	TArray<class UClass*>                              out_recipes;                                              // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGRecipeManager.Get
struct AFGRecipeManager_Get_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGRecipeManager*                            ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRecipeManager.FindRecipesByProduct
struct AFGRecipeManager_FindRecipesByProduct_Params
{
	class UClass*                                      product;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class UClass*>                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGRecipeManager.FindRecipesByIngredient
struct AFGRecipeManager_FindRecipesByIngredient_Params
{
	class UClass*                                      ingredient;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class UClass*>                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGRecipeShortcut.SetRecipe
struct UFGRecipeShortcut_SetRecipe_Params
{
	class UClass*                                      Recipe;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGRecipeShortcut.OnRep_Recipe
struct UFGRecipeShortcut_OnRep_Recipe_Params
{
};

// Function FactoryGame.FGRecipeShortcut.GetRecipe
struct UFGRecipeShortcut_GetRecipe_Params
{
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRenderTargetStage.UpdateRenderedComponents
struct AFGRenderTargetStage_UpdateRenderedComponents_Params
{
};

// Function FactoryGame.FGRenderTargetStage.SetView
struct AFGRenderTargetStage_SetView_Params
{
	struct FItemView                                   View;                                                     // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function FactoryGame.FGRenderTargetStage.SetPreviewDistance
struct AFGRenderTargetStage_SetPreviewDistance_Params
{
	float                                              Distance;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGRenderTargetStage.GetStage
struct AFGRenderTargetStage_GetStage_Params
{
	class USceneComponent*                             ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGRenderTargetStage.GetRenderTarget
struct AFGRenderTargetStage_GetRenderTarget_Params
{
	class UTextureRenderTarget2D*                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGRenderTargetStage.EndCapture
struct AFGRenderTargetStage_EndCapture_Params
{
};

// Function FactoryGame.FGRenderTargetStage.CaptureOnce
struct AFGRenderTargetStage_CaptureOnce_Params
{
};

// Function FactoryGame.FGRenderTargetStage.BeginCapture
struct AFGRenderTargetStage_BeginCapture_Params
{
};

// Function FactoryGame.FGResearchMachine.SetResearchRecipe
struct UFGResearchMachine_SetResearchRecipe_Params
{
	class UClass*                                      researchRecipe;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGResearchMachine.SetResearchMeshCurveScale
struct UFGResearchMachine_SetResearchMeshCurveScale_Params
{
	class UCurveFloat*                                 curveScale;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGResearchMachine.SetResearchMeshComponent
struct UFGResearchMachine_SetResearchMeshComponent_Params
{
	class UStaticMeshComponent*                        StaticMeshComponent;                                      // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGResearchMachine.SetMachineUser
struct UFGResearchMachine_SetMachineUser_Params
{
	class AFGCharacterPlayer*                          Player;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGResearchMachine.OnResearchStarted
struct UFGResearchMachine_OnResearchStarted_Params
{
	class UClass*                                      researchRecipe;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGResearchMachine.OnResearchConcluded
struct UFGResearchMachine_OnResearchConcluded_Params
{
	class UClass*                                      researchRecipe;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGResearchMachine.OnRep_ResearchMesh
struct UFGResearchMachine_OnRep_ResearchMesh_Params
{
};

// Function FactoryGame.FGResearchMachine.IsResearchBeingConducted
struct UFGResearchMachine_IsResearchBeingConducted_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchMachine.GetResearchMeshComponent
struct UFGResearchMachine_GetResearchMeshComponent_Params
{
	class UStaticMeshComponent*                        ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGResearchMachine.GetMachineUser
struct UFGResearchMachine_GetMachineUser_Params
{
	class AFGCharacterPlayer*                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.UnlockResearchWithItem
struct AFGResearchManager_UnlockResearchWithItem_Params
{
	class UClass*                                      ItemClass;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.SetSelectedRewardIndexByRecipe
struct AFGResearchManager_SetSelectedRewardIndexByRecipe_Params
{
	class UClass*                                      CompletedResearch;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                selectedIndex;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.PayOffOnResearch
struct AFGResearchManager_PayOffOnResearch_Params
{
	struct FItemAmount                                 payOff;                                                   // (Parm)
	class UClass*                                      researchRecipe;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.PayOffFromInventory
struct AFGResearchManager_PayOffFromInventory_Params
{
	class UClass*                                      researchRecipe;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGInventoryComponent*                       inventory;                                                // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                inventorySlotIndex;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.OnResearchTimerComplete
struct AFGResearchManager_OnResearchTimerComplete_Params
{
	class UClass*                                      researchRecipe;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.IsResearchRecipeAccessible
struct AFGResearchManager_IsResearchRecipeAccessible_Params
{
	class UClass*                                      researchRecipe;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.IsResearchComplete
struct AFGResearchManager_IsResearchComplete_Params
{
	class UClass*                                      researchRecipe;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.IsResearchBeingConducted
struct AFGResearchManager_IsResearchBeingConducted_Params
{
	class UClass*                                      researchRecipe;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.IsResearchAccessibleAndPaidOff
struct AFGResearchManager_IsResearchAccessibleAndPaidOff_Params
{
	class UClass*                                      researchRecipe;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.IsCompletedResearchResultSelectable
struct AFGResearchManager_IsCompletedResearchResultSelectable_Params
{
	class UClass*                                      researchRecipe;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.IsAnyResearchBeingConducted
struct AFGResearchManager_IsAnyResearchBeingConducted_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.InitiateResearch
struct AFGResearchManager_InitiateResearch_Params
{
	class UClass*                                      researchRecipe;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.GiveAccessToResearch
struct AFGResearchManager_GiveAccessToResearch_Params
{
	class UClass*                                      researchRecipeClass;                                      // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               accessedViaCheats;                                        // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.GetStructurePoints
struct AFGResearchManager_GetStructurePoints_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.GetRewardsFromCompletedResearch
struct AFGResearchManager_GetRewardsFromCompletedResearch_Params
{
	struct FCompletedResearch                          CompletedResearch;                                        // (Parm)
	TArray<struct FResearchRecipeReward>               ReturnValue;                                              // (ConstParm, Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGResearchManager.GetResearchDuration
struct AFGResearchManager_GetResearchDuration_Params
{
	class UClass*                                      researchRecipe;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.GetResearchBeingConducted
struct AFGResearchManager_GetResearchBeingConducted_Params
{
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.GetPayOffBalanceForResearch
struct AFGResearchManager_GetPayOffBalanceForResearch_Params
{
	class UClass*                                      researchRecipe;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FItemAmount>                         out_cost;                                                 // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGResearchManager.GetOngoingResearchTimeLeft
struct AFGResearchManager_GetOngoingResearchTimeLeft_Params
{
	class UClass*                                      researchRecipe;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.GetDecorPoints
struct AFGResearchManager_GetDecorPoints_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.GetCompletedResearchRewardByRecipe
struct AFGResearchManager_GetCompletedResearchRewardByRecipe_Params
{
	class UClass*                                      CompletedResearch;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	struct FCompletedResearch                          ReturnValue;                                              // (ConstParm, Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGResearchManager.GetAllResearchRecipes
struct AFGResearchManager_GetAllResearchRecipes_Params
{
	TArray<class UClass*>                              out_ResearchRecipes;                                      // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGResearchManager.GetAllCompletedAndClaimedResearch
struct AFGResearchManager_GetAllCompletedAndClaimedResearch_Params
{
	TArray<class UClass*>                              out_ResearchRecipes;                                      // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGResearchManager.GetAllAccessibleResearch
struct AFGResearchManager_GetAllAccessibleResearch_Params
{
	TArray<class UClass*>                              out_ResearchRecipes;                                      // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGResearchManager.Get
struct AFGResearchManager_Get_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGResearchManager*                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.ContainsAnyCompletedButUnclaimedResearch
struct AFGResearchManager_ContainsAnyCompletedButUnclaimedResearch_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.ConsumeStructurePoints
struct AFGResearchManager_ConsumeStructurePoints_Params
{
	int                                                amount;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.ConsumeDecorPoints
struct AFGResearchManager_ConsumeDecorPoints_Params
{
	int                                                amount;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.ClaimResearchResults
struct AFGResearchManager_ClaimResearchResults_Params
{
	class AFGCharacterPlayer*                          instigatorPlayer;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      CompletedResearch;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                selectedRewardIndex;                                      // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.CanResearchRewardBeClaimed
struct AFGResearchManager_CanResearchRewardBeClaimed_Params
{
	class UClass*                                      researchRecipe;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.CanResearchBeInitiated
struct AFGResearchManager_CanResearchBeInitiated_Params
{
	class UClass*                                      researchRecipe;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.CanConsumeStructurePoints
struct AFGResearchManager_CanConsumeStructurePoints_Params
{
	int                                                amount;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.CanConsumeDecorPoints
struct AFGResearchManager_CanConsumeDecorPoints_Params
{
	int                                                amount;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.AddStructurePoints
struct AFGResearchManager_AddStructurePoints_Params
{
	int                                                amount;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGResearchManager.AddDecorPoints
struct AFGResearchManager_AddDecorPoints_Params
{
	int                                                amount;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGResearchRecipe.IsValidResearchRecipeReward
struct UFGResearchRecipe_IsValidResearchRecipeReward_Params
{
	struct FResearchRecipeReward                       recipeReward;                                             // (Parm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchRecipe.IsResearchRepeatable
struct UFGResearchRecipe_IsResearchRepeatable_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResearchRecipe.GetResearcResults
struct UFGResearchRecipe_GetResearcResults_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FResearchRecipeReward                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGResearchRecipe.GetResearchTriggerItems
struct UFGResearchRecipe_GetResearchTriggerItems_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class UClass*>                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGResearchRecipe.GetResearchTime
struct UFGResearchRecipe_GetResearchTime_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceNode.ToggleResourcePickUI
struct AFGResourceNode_ToggleResourcePickUI_Params
{
	class AFGCharacterPlayer*                          Player;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGResourceNode.SetIsOccupied
struct AFGResourceNode_SetIsOccupied_Params
{
	bool                                               occupied;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGResourceNode.OnRep_IsOccupied
struct AFGResourceNode_OnRep_IsOccupied_Params
{
};

// Function FactoryGame.FGResourceNode.OnIsOccupiedChanged
struct AFGResourceNode_OnIsOccupiedChanged_Params
{
	bool                                               newIsOccupied;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGResourceNode.IsOccupied
struct AFGResourceNode_IsOccupied_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceNode.InitResource
struct AFGResourceNode_InitResource_Params
{
	class UClass*                                      ResourceClass;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EResourceAmount>                       amount;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EResourcePurity>                       Purity;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGResourceNode.HasAnyResources
struct AFGResourceNode_HasAnyResources_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceNode.GetResourceName
struct AFGResourceNode_GetResourceName_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGResourceNode.GetResourceClass
struct AFGResourceNode_GetResourceClass_Params
{
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceNode.GetResourceAmount
struct AFGResourceNode_GetResourceAmount_Params
{
	TEnumAsByte<EResourceAmount>                       ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceNode.GetResoucesLeftText
struct AFGResourceNode_GetResoucesLeftText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGResourceNode.GetResoucePurityText
struct AFGResourceNode_GetResoucePurityText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGResourceNode.GetResoucePurity
struct AFGResourceNode_GetResoucePurity_Params
{
	TEnumAsByte<EResourcePurity>                       ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceNode.GetIsLonerNode
struct AFGResourceNode_GetIsLonerNode_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceNode.GetExtractMultiplier
struct AFGResourceNode_GetExtractMultiplier_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceNode.GetExtractionSpeedMultiplier
struct AFGResourceNode_GetExtractionSpeedMultiplier_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceNode.ExtractResourceAndGiveToPlayer
struct AFGResourceNode_ExtractResourceAndGiveToPlayer_Params
{
	class AFGCharacterPlayer*                          toPlayer;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                amount;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGResourceNode.ClearWidget
struct AFGResourceNode_ClearWidget_Params
{
};

// Function FactoryGame.FGResourceNode.CanPlaceResourceExtractor
struct AFGResourceNode_CanPlaceResourceExtractor_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceDeposit.PlayDepletedEffect
struct AFGResourceDeposit_PlayDepletedEffect_Params
{
	class UClass*                                      Descriptor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGResourceDeposit.OnRep_ResourceDepositEmptied
struct AFGResourceDeposit_OnRep_ResourceDepositEmptied_Params
{
};

// Function FactoryGame.FGResourceDeposit.IsDepositEmpty
struct AFGResourceDeposit_IsDepositEmpty_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceDeposit.GetMineAmount
struct AFGResourceDeposit_GetMineAmount_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceDescriptor.GetPingColor
struct UFGResourceDescriptor_GetPingColor_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceDescriptor.GetMeshOverrideMaterial
struct UFGResourceDescriptor_GetMeshOverrideMaterial_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UMaterialInstance*                           ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceDescriptor.GetManualMiningParticle
struct UFGResourceDescriptor_GetManualMiningParticle_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UParticleSystem*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceDescriptor.GetManualMiningAudioName
struct UFGResourceDescriptor_GetManualMiningAudioName_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FName                                       ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceDescriptor.GetGroundMesh
struct UFGResourceDescriptor_GetGroundMesh_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UStaticMesh*                                 ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceDescriptor.GetFactoryMiningParticle
struct UFGResourceDescriptor_GetFactoryMiningParticle_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UParticleSystem*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceDescriptor.GetDestroyedParticle
struct UFGResourceDescriptor_GetDestroyedParticle_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UParticleSystem*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceDescriptor.GetDepositMesh
struct UFGResourceDescriptor_GetDepositMesh_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UStaticMesh*                                 ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceDescriptor.GetDepositMaterial
struct UFGResourceDescriptor_GetDepositMaterial_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UMaterialInstance*                           ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceDescriptor.GetDecalSize
struct UFGResourceDescriptor_GetDecalSize_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceDescriptor.GetDecalMaterial
struct UFGResourceDescriptor_GetDecalMaterial_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UMaterial*                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceDescriptor.GetCompasTexture
struct UFGResourceDescriptor_GetCompasTexture_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UTexture2D*                                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceDescriptor.GetCollectSpeedMultiplier
struct UFGResourceDescriptor_GetCollectSpeedMultiplier_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceDescriptor.CanBeHandMined
struct UFGResourceDescriptor_CanBeHandMined_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceMiner.StopMining
struct AFGResourceMiner_StopMining_Params
{
};

// Function FactoryGame.FGResourceMiner.StartMining
struct AFGResourceMiner_StartMining_Params
{
};

// Function FactoryGame.FGResourceMiner.SetResourceNode
struct AFGResourceMiner_SetResourceNode_Params
{
	class AFGResourceNode*                             inNode;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGResourceMiner.Server_ExtractResources
struct AFGResourceMiner_Server_ExtractResources_Params
{
};

// Function FactoryGame.FGResourceMiner.RemoveEquipment
struct AFGResourceMiner_RemoveEquipment_Params
{
};

// Function FactoryGame.FGResourceMiner.GetResourceNode
struct AFGResourceMiner_GetResourceNode_Params
{
	class AFGResourceNode*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceMiner.DoMine
struct AFGResourceMiner_DoMine_Params
{
};

// Function FactoryGame.FGResourceScanner.ShowResourceDescriptorSelectUI
struct AFGResourceScanner_ShowResourceDescriptorSelectUI_Params
{
};

// Function FactoryGame.FGResourceScanner.SetResourceDescriptorToScanFor
struct AFGResourceScanner_SetResourceDescriptorToScanFor_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGResourceScanner.SetPressingScan
struct AFGResourceScanner_SetPressingScan_Params
{
	bool                                               isPressingScan;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGResourceScanner.Server_ScanReleased
struct AFGResourceScanner_Server_ScanReleased_Params
{
};

// Function FactoryGame.FGResourceScanner.PlayClusterEffects
struct AFGResourceScanner_PlayClusterEffects_Params
{
	TArray<struct FNodeClusterData>                    clusters;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function FactoryGame.FGResourceScanner.GetScannableResources
struct AFGResourceScanner_GetScannableResources_Params
{
	TArray<class UClass*>                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGResourceScanner.GetResourceDescriptorToScanFor
struct AFGResourceScanner_GetResourceDescriptorToScanFor_Params
{
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGResourceScanner.CloseResourceDescriptorSelectUI
struct AFGResourceScanner_CloseResourceDescriptorSelectUI_Params
{
};

// Function FactoryGame.FGResourceSettings.GetResourceDepositDataFromClass
struct UFGResourceSettings_GetResourceDepositDataFromClass_Params
{
	class UClass*                                      desiredResourceClass;                                     // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                out_resourceDepositPackageIdx;                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FResourceDepositPackage                     ReturnValue;                                              // (ConstParm, Parm, OutParm, ReturnParm, ReferenceParm)
};

// Function FactoryGame.FGResourceSettings.GetRandomResourceDepositData
struct UFGResourceSettings_GetRandomResourceDepositData_Params
{
	int                                                out_resourceDepositPackageIdx;                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FResourceDepositPackage                     ReturnValue;                                              // (ConstParm, Parm, OutParm, ReturnParm, ReferenceParm)
};

// Function FactoryGame.FGSaveInterface.ShouldSave
struct UFGSaveInterface_ShouldSave_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSaveInterface.PreSaveGame
struct UFGSaveInterface_PreSaveGame_Params
{
	int                                                SaveVersion;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                GameVersion;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGSaveInterface.PreLoadGame
struct UFGSaveInterface_PreLoadGame_Params
{
	int                                                SaveVersion;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                GameVersion;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGSaveInterface.PostSaveGame
struct UFGSaveInterface_PostSaveGame_Params
{
	int                                                SaveVersion;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                GameVersion;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGSaveInterface.PostLoadGame
struct UFGSaveInterface_PostLoadGame_Params
{
	int                                                SaveVersion;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                GameVersion;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGSaveInterface.NeedTransform
struct UFGSaveInterface_NeedTransform_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSaveInterface.GatherDependencies
struct UFGSaveInterface_GatherDependencies_Params
{
	TArray<class UObject*>                             out_dependentObjects;                                     // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGSaveSession.SaveGame
struct UFGSaveSession_SaveGame_Params
{
	class FString                                      Filename;                                                 // (Parm, ZeroConstructor)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSaveSession.OnActorDestroyed
struct UFGSaveSession_OnActorDestroyed_Params
{
	class AActor*                                      DestroyedActor;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGSaveSession.LoadGame
struct UFGSaveSession_LoadGame_Params
{
	class FString                                      saveName;                                                 // (Parm, ZeroConstructor)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSaveSession.GetVersion
struct UFGSaveSession_GetVersion_Params
{
	struct FSaveHeader                                 Header;                                                   // (Parm, OutParm, ReferenceParm)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSaveSession.GetSessionName
struct UFGSaveSession_GetSessionName_Params
{
	struct FSaveHeader                                 Header;                                                   // (Parm, OutParm, ReferenceParm)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGSaveSession.GetSessionID
struct UFGSaveSession_GetSessionID_Params
{
	struct FSaveHeader                                 Header;                                                   // (Parm, OutParm, ReferenceParm)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGSaveSession.GetSaveSessionVisibility
struct UFGSaveSession_GetSaveSessionVisibility_Params
{
	struct FSaveHeader                                 Header;                                                   // (Parm, OutParm, ReferenceParm)
	TEnumAsByte<ESessionVisibility>                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSaveSession.GetSaveSessionName
struct UFGSaveSession_GetSaveSessionName_Params
{
	struct FSessionSaveStruct                          session;                                                  // (Parm, OutParm, ReferenceParm)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGSaveSession.GetSaveSessionID
struct UFGSaveSession_GetSaveSessionID_Params
{
	struct FSessionSaveStruct                          session;                                                  // (Parm, OutParm, ReferenceParm)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGSaveSession.GetSaveDateTime
struct UFGSaveSession_GetSaveDateTime_Params
{
	struct FSaveHeader                                 Header;                                                   // (Parm, OutParm, ReferenceParm)
	struct FDateTime                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGSaveSession.GetPlayDurationSeconds
struct UFGSaveSession_GetPlayDurationSeconds_Params
{
	struct FSaveHeader                                 Header;                                                   // (Parm, OutParm, ReferenceParm)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSaveSession.GetName
struct UFGSaveSession_GetName_Params
{
	struct FSaveHeader                                 Header;                                                   // (Parm, OutParm, ReferenceParm)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGSaveSession.GetMapOptions
struct UFGSaveSession_GetMapOptions_Params
{
	struct FSaveHeader                                 Header;                                                   // (Parm, OutParm, ReferenceParm)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGSaveSession.GetMapName
struct UFGSaveSession_GetMapName_Params
{
	struct FSaveHeader                                 Header;                                                   // (Parm, OutParm, ReferenceParm)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGSaveSession.GetBuildVersion
struct UFGSaveSession_GetBuildVersion_Params
{
	struct FSaveHeader                                 Header;                                                   // (Parm, OutParm, ReferenceParm)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSaveSession.Get
struct UFGSaveSession_Get_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGSaveSession*                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSaveSession.Autosave
struct UFGSaveSession_Autosave_Params
{
};

// Function FactoryGame.FGSaveSystem.IsValidSaveName
struct UFGSaveSystem_IsValidSaveName_Params
{
	class FString                                      saveName;                                                 // (Parm, ZeroConstructor)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSaveSystem.IsSessionNameUsed
struct UFGSaveSystem_IsSessionNameUsed_Params
{
	class FString                                      SessionName;                                              // (Parm, ZeroConstructor)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSaveSystem.GetSaveExists
struct UFGSaveSystem_GetSaveExists_Params
{
	class FString                                      saveName;                                                 // (Parm, ZeroConstructor)
	class FString                                      currentSessionName;                                       // (Parm, ZeroConstructor)
	ESaveExists                                        ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSaveSystem.GetAllSavesPerSession
struct UFGSaveSystem_GetAllSavesPerSession_Params
{
	TArray<struct FSessionSaveStruct>                  out_sessions;                                             // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGSaveSystem.Get
struct UFGSaveSystem_Get_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGSaveSystem*                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSaveSystem.FindSaveGames
struct UFGSaveSystem_FindSaveGames_Params
{
	TArray<struct FSaveHeader>                         out_saveGames;                                            // (Parm, OutParm, ZeroConstructor)
	bool                                               newestFirst;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGSaveSystem.DeleteSave
struct UFGSaveSystem_DeleteSave_Params
{
	class FString                                      saveName;                                                 // (Parm, ZeroConstructor)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematic.IsIncludedInBuild
struct UFGSchematic_IsIncludedInBuild_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematic.GetUnlocksMap
struct UFGSchematic_GetUnlocksMap_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematic.GetUnlocksInventorySlots
struct UFGSchematic_GetUnlocksInventorySlots_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematic.GetUnlocksBuildOverclock
struct UFGSchematic_GetUnlocksBuildOverclock_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematic.GetUnlocksBuildEfficiencyDisplay
struct UFGSchematic_GetUnlocksBuildEfficiencyDisplay_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematic.GetUnlocksArmEquipmentSlots
struct UFGSchematic_GetUnlocksArmEquipmentSlots_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematic.GetType
struct UFGSchematic_GetType_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	ESchematicType                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematic.GetTechTier
struct UFGSchematic_GetTechTier_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematic.GetShipTravelTimeAfterPurchase
struct UFGSchematic_GetShipTravelTimeAfterPurchase_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematic.GetSchematicDisplayName
struct UFGSchematic_GetSchematicDisplayName_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGSchematic.GetSchematicCategory
struct UFGSchematic_GetSchematicCategory_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	ESchematicCategory                                 ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematic.GetResourceToAddToScanner
struct UFGSchematic_GetResourceToAddToScanner_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class UClass*>                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGSchematic.GetRecipes
struct UFGSchematic_GetRecipes_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class UClass*>                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGSchematic.GetNumInventorySlotsUnlocked
struct UFGSchematic_GetNumInventorySlotsUnlocked_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematic.GetNumArmEquipmentSlotsUnlocked
struct UFGSchematic_GetNumArmEquipmentSlotsUnlocked_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematic.GetItemIcon
struct UFGSchematic_GetItemIcon_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FSlateBrush                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGSchematic.GetDependentOnSchematic
struct UFGSchematic_GetDependentOnSchematic_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematic.GetCost
struct UFGSchematic_GetCost_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FItemAmount>                         ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGSchematic.GetAdditionalSchematicDependencies
struct UFGSchematic_GetAdditionalSchematicDependencies_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class UClass*>                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGSchematicManager.SetActiveSchematic
struct AFGSchematicManager_SetActiveSchematic_Params
{
	class UClass*                                      newActiveSchematic;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematicManager.PayOffOnSchematic
struct AFGSchematicManager_PayOffOnSchematic_Params
{
	class UClass*                                      Schematic;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FItemAmount>                         amount;                                                   // (Parm, OutParm, ZeroConstructor, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematicManager.OnRep_PurchasedSchematic
struct AFGSchematicManager_OnRep_PurchasedSchematic_Params
{
};

// Function FactoryGame.FGSchematicManager.OnRep_PaidOffOnSchematic
struct AFGSchematicManager_OnRep_PaidOffOnSchematic_Params
{
};

// Function FactoryGame.FGSchematicManager.OnRep_ActiveSchematic
struct AFGSchematicManager_OnRep_ActiveSchematic_Params
{
};

// Function FactoryGame.FGSchematicManager.LaunchShip
struct AFGSchematicManager_LaunchShip_Params
{
};

// Function FactoryGame.FGSchematicManager.IsShipAtTradingPost
struct AFGSchematicManager_IsShipAtTradingPost_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematicManager.IsSchematicPurchased
struct AFGSchematicManager_IsSchematicPurchased_Params
{
	class UClass*                                      SchematicClass;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematicManager.IsSchematicPaidOff
struct AFGSchematicManager_IsSchematicPaidOff_Params
{
	class UClass*                                      Schematic;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematicManager.GiveAccessToSchematic
struct AFGSchematicManager_GiveAccessToSchematic_Params
{
	class UClass*                                      SchematicClass;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               accessedViaCheats;                                        // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGSchematicManager.GetTimeUntilShipReturn
struct AFGSchematicManager_GetTimeUntilShipReturn_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematicManager.GetRemainingCostFor
struct AFGSchematicManager_GetRemainingCostFor_Params
{
	class UClass*                                      Schematic;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FItemAmount>                         ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGSchematicManager.GetPurchasedSchematics
struct AFGSchematicManager_GetPurchasedSchematics_Params
{
	TArray<class UClass*>                              out_schematics;                                           // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGSchematicManager.GetPaidOffCostFor
struct AFGSchematicManager_GetPaidOffCostFor_Params
{
	class UClass*                                      Schematic;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FItemAmount>                         ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGSchematicManager.GetMaxAllowedTechTier
struct AFGSchematicManager_GetMaxAllowedTechTier_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematicManager.GetHighestAvailableTechTier
struct AFGSchematicManager_GetHighestAvailableTechTier_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematicManager.GetCostFor
struct AFGSchematicManager_GetCostFor_Params
{
	class UClass*                                      Schematic;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FItemAmount>                         ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGSchematicManager.GetAvailableSchematics
struct AFGSchematicManager_GetAvailableSchematics_Params
{
	TArray<class UClass*>                              out_schematics;                                           // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGSchematicManager.GetAllSchematicsOfType
struct AFGSchematicManager_GetAllSchematicsOfType_Params
{
	ESchematicType                                     Type;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class UClass*>                              out_schematics;                                           // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGSchematicManager.GetAllSchematics
struct AFGSchematicManager_GetAllSchematics_Params
{
	TArray<class UClass*>                              out_schematics;                                           // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGSchematicManager.GetActiveSchematic
struct AFGSchematicManager_GetActiveSchematic_Params
{
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematicManager.Get
struct AFGSchematicManager_Get_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGSchematicManager*                         ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematicManager.CanSetAsActiveSchematic
struct AFGSchematicManager_CanSetAsActiveSchematic_Params
{
	class UClass*                                      inSchematic;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSchematicManager.AddAvailableSchematic
struct AFGSchematicManager_AddAvailableSchematic_Params
{
	class UClass*                                      schematicClassToAdd;                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGSignCanvasWidget.OnElementSelected
struct UFGSignCanvasWidget_OnElementSelected_Params
{
	class UFGSignElementData*                          elementData;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGSignCanvasWidget.GetComponentToCanvasLocation
struct UFGSignCanvasWidget_GetComponentToCanvasLocation_Params
{
	struct FVector2D                                   locationInComponent;                                      // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSignCanvasWidget.GetCanvasToComponentLocation
struct UFGSignCanvasWidget_GetCanvasToComponentLocation_Params
{
	struct FVector2D                                   locationInCanvas;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSignCanvasWidget.AddSignCanvasElement
struct UFGSignCanvasWidget_AddSignCanvasElement_Params
{
	class UFGSignElementData*                          elementData;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGSignElementDragWidget.OnExitCanavasBounds
struct UFGSignElementDragWidget_OnExitCanavasBounds_Params
{
};

// Function FactoryGame.FGSignElementDragWidget.OnEnterCanvasBounds
struct UFGSignElementDragWidget_OnEnterCanvasBounds_Params
{
};

// Function FactoryGame.FGSignElementDragWidget.Init
struct UFGSignElementDragWidget_Init_Params
{
	class UFGSignElementData*                          elementData;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGSignElementSettingsWidget.OnElementDataChanged
struct UFGSignElementSettingsWidget_OnElementDataChanged_Params
{
};

// Function FactoryGame.FGSignElementSettingsWidget.OnColorIndexSelected
struct UFGSignElementSettingsWidget_OnColorIndexSelected_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGSignElementSettingsWidget.Init
struct UFGSignElementSettingsWidget_Init_Params
{
};

// Function FactoryGame.FGSignElementWidget.RefreshElement
struct UFGSignElementWidget_RefreshElement_Params
{
	bool                                               isInitialization;                                         // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGSignElementWidget.OnElementSelected
struct UFGSignElementWidget_OnElementSelected_Params
{
};

// Function FactoryGame.FGSignElementWidget.OnElementDeselected
struct UFGSignElementWidget_OnElementDeselected_Params
{
};

// Function FactoryGame.FGSignElementWidget.GetElementData
struct UFGSignElementWidget_GetElementData_Params
{
	class UFGSignElementData*                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSignificanceInterface.LostSignificance
struct UFGSignificanceInterface_LostSignificance_Params
{
};

// Function FactoryGame.FGSignificanceInterface.GetSignificanceRange
struct UFGSignificanceInterface_GetSignificanceRange_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSignificanceInterface.GetSignificanceBias
struct UFGSignificanceInterface_GetSignificanceBias_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSignificanceInterface.GainedSignificance
struct UFGSignificanceInterface_GainedSignificance_Params
{
};

// Function FactoryGame.FGSignInteractWidget.ApplySignData
struct UFGSignInteractWidget_ApplySignData_Params
{
};

// Function FactoryGame.FGSignInteractWidget.AddNewTextElement
struct UFGSignInteractWidget_AddNewTextElement_Params
{
};

// Function FactoryGame.FGSignInteractWidget.AddNewSignElement
struct UFGSignInteractWidget_AddNewSignElement_Params
{
	class UFGSignElementData*                          elementData;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGSignInteractWidget.AddNewIconElement
struct UFGSignInteractWidget_AddNewIconElement_Params
{
};

// Function FactoryGame.FGSignInterface.SetSignData
struct UFGSignInterface_SetSignData_Params
{
	struct FSignData                                   Data;                                                     // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               bUpdate;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGSignInterface.GetSignDimensions
struct UFGSignInterface_GetSignDimensions_Params
{
	struct FVector2D                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSignInterface.GetSignData
struct UFGSignInterface_GetSignData_Params
{
	struct FSignData                                   ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGSignInterface.GetAvailableElementID
struct UFGSignInterface_GetAvailableElementID_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSignSettings.GetTextMaterialInstanceFromIndex
struct UFGSignSettings_GetTextMaterialInstanceFromIndex_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class UMaterialInterface*                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSignSettings.GetSignColorData
struct UFGSignSettings_GetSignColorData_Params
{
	TArray<struct FSignColorData>                      ReturnValue;                                              // (ConstParm, Parm, OutParm, ZeroConstructor, ReturnParm, ReferenceParm)
};

// Function FactoryGame.FGSignSettings.GetIconMaterialInstanceFromIndex
struct UFGSignSettings_GetIconMaterialInstanceFromIndex_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class UMaterialInterface*                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSignSettings.GetBackgroundMaterialInstanceFromIndex
struct UFGSignSettings_GetBackgroundMaterialInstanceFromIndex_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class UMaterialInterface*                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSignTextWidget.GetTextBlock
struct UFGSignTextWidget_GetTextBlock_Params
{
	class UTextBlock*                                  ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGSkySphere.UpdatePreview
struct AFGSkySphere_UpdatePreview_Params
{
};

// Function FactoryGame.FGSkySphere.GetFloatCurveValue
struct AFGSkySphere_GetFloatCurveValue_Params
{
	struct FRuntimeFloatCurve                          Curve;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
	float                                              Time;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSkySphere.GetColorCurveValue
struct AFGSkySphere_GetColorCurveValue_Params
{
	struct FRuntimeCurveLinearColor                    Curve;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
	float                                              Time;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSkySphere.ApplySkySphereSettings
struct AFGSkySphere_ApplySkySphereSettings_Params
{
	struct FSkySphereSettings                          Settings;                                                 // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function FactoryGame.FGSoundSplineComponent.SetEmitterInterval
struct UFGSoundSplineComponent_SetEmitterInterval_Params
{
	float                                              newEmitterInterval;                                       // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGSoundSplineComponent.GetEmitterInterval
struct UFGSoundSplineComponent_GetEmitterInterval_Params
{
	float                                              newEmitterInterval;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGSplineComponent.UpdateSplineMeshes
struct UFGSplineComponent_UpdateSplineMeshes_Params
{
};

// Function FactoryGame.FGSplineComponent.SetOverrideMaterial
struct UFGSplineComponent_SetOverrideMaterial_Params
{
	class UMaterialInterface*                          Material;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGSplineComponent.DrawDebugSpline
struct UFGSplineComponent_DrawDebugSpline_Params
{
	struct FColor                                      color1;                                                   // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FColor                                      color2;                                                   // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	float                                              Thickness;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGSporeFlower.ActorShouldTriggerFlower
struct AFGSporeFlower_ActorShouldTriggerFlower_Params
{
	class AActor*                                      Actor;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGStartingPod.StartSequence
struct AFGStartingPod_StartSequence_Params
{
};

// Function FactoryGame.FGStartingPod.OnPlayerSkipIntroSequence
struct AFGStartingPod_OnPlayerSkipIntroSequence_Params
{
};

// Function FactoryGame.FGStartingPod.GetCachedPlayer
struct AFGStartingPod_GetCachedPlayer_Params
{
	class AFGCharacterPlayer*                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGStorySubsystem.SetupDelegates
struct AFGStorySubsystem_SetupDelegates_Params
{
};

// Function FactoryGame.FGStorySubsystem.OnSchematicPurchased
struct AFGStorySubsystem_OnSchematicPurchased_Params
{
	class UClass*                                      newSchematic;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGStorySubsystem.OnResearchRewardClaimed
struct AFGStorySubsystem_OnResearchRewardClaimed_Params
{
	class UClass*                                      researchRecipe;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGStorySubsystem.OnResearchRecipeTimerComplete
struct AFGStorySubsystem_OnResearchRecipeTimerComplete_Params
{
	class UClass*                                      researchRecipe;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGStorySubsystem.OnPlayerAddedItemToInventory
struct AFGStorySubsystem_OnPlayerAddedItemToInventory_Params
{
	class UClass*                                      ItemClass;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                numAdded;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGStorySubsystem.OnNewResearchRecipeAvailable
struct AFGStorySubsystem_OnNewResearchRecipeAvailable_Params
{
	class UClass*                                      researchRecipe;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGStorySubsystem.OnMapAreaVisited
struct AFGStorySubsystem_OnMapAreaVisited_Params
{
	class UClass*                                      mapArea;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGStorySubsystem.AddPlayer
struct AFGStorySubsystem_AddPlayer_Params
{
	class AFGCharacterPlayer*                          inPlayer;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGTargetPoint.SetWaitTime
struct AFGTargetPoint_SetWaitTime_Params
{
	float                                              newWaitTime;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGTargetPoint.SetVisibility
struct AFGTargetPoint_SetVisibility_Params
{
	bool                                               inVisible;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGTargetPoint.SetTargetSpeed
struct AFGTargetPoint_SetTargetSpeed_Params
{
	int                                                newSpeed;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGTargetPoint.SetOwningVehicle
struct AFGTargetPoint_SetOwningVehicle_Params
{
	class AFGWheeledVehicle*                           newVehicle;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGTargetPoint.OnRep_Visibility
struct AFGTargetPoint_OnRep_Visibility_Params
{
};

// Function FactoryGame.FGTargetPoint.IsTargetSpeedStill
struct AFGTargetPoint_IsTargetSpeedStill_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTargetPoint.IncreaseWaitTime
struct AFGTargetPoint_IncreaseWaitTime_Params
{
	float                                              addedWaitTime;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGTargetPoint.GetWaitTime
struct AFGTargetPoint_GetWaitTime_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTargetPoint.GetTargetSpeed
struct AFGTargetPoint_GetTargetSpeed_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTargetPoint.GetOwningVehicle
struct AFGTargetPoint_GetOwningVehicle_Params
{
	class AFGWheeledVehicle*                           ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTargetPointLinkedList.SetPathVisibility
struct UFGTargetPointLinkedList_SetPathVisibility_Params
{
	bool                                               inVisible;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGTargetPointLinkedList.SetNextTarget
struct UFGTargetPointLinkedList_SetNextTarget_Params
{
};

// Function FactoryGame.FGTargetPointLinkedList.SetCurrentTarget
struct UFGTargetPointLinkedList_SetCurrentTarget_Params
{
	class AFGTargetPoint*                              newTarget;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGTargetPointLinkedList.SetClosestPointAsTarget
struct UFGTargetPointLinkedList_SetClosestPointAsTarget_Params
{
};

// Function FactoryGame.FGTargetPointLinkedList.RemoveItem
struct UFGTargetPointLinkedList_RemoveItem_Params
{
	class AFGTargetPoint*                              targetToRemove;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGTargetPointLinkedList.InsertItem
struct UFGTargetPointLinkedList_InsertItem_Params
{
	class AFGTargetPoint*                              newTarget;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGTargetPointLinkedList.GetLastTarget
struct UFGTargetPointLinkedList_GetLastTarget_Params
{
	class AFGTargetPoint*                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTargetPointLinkedList.GetFirstTarget
struct UFGTargetPointLinkedList_GetFirstTarget_Params
{
	class AFGTargetPoint*                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTargetPointLinkedList.GetCurrentTarget
struct UFGTargetPointLinkedList_GetCurrentTarget_Params
{
	class AFGTargetPoint*                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTargetPointLinkedList.ClearRecording
struct UFGTargetPointLinkedList_ClearRecording_Params
{
};

// Function FactoryGame.FGTimeOfDaySubsystem.UpdateServerDaySeconds
struct AFGTimeOfDaySubsystem_UpdateServerDaySeconds_Params
{
};

// Function FactoryGame.FGTimeOfDaySubsystem.SetTimeSpeedMultiplier
struct AFGTimeOfDaySubsystem_SetTimeSpeedMultiplier_Params
{
	float                                              Multiplier;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGTimeOfDaySubsystem.OnRep_ReplicatedDaySeconds
struct AFGTimeOfDaySubsystem_OnRep_ReplicatedDaySeconds_Params
{
};

// Function FactoryGame.FGTimeOfDaySubsystem.IsNight
struct AFGTimeOfDaySubsystem_IsNight_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTimeOfDaySubsystem.IsDay
struct AFGTimeOfDaySubsystem_IsDay_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTimeOfDaySubsystem.GetTimeOfDayHours
struct AFGTimeOfDaySubsystem_GetTimeOfDayHours_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTimeOfDaySubsystem.GetSeconds
struct AFGTimeOfDaySubsystem_GetSeconds_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTimeOfDaySubsystem.GetPassedDays
struct AFGTimeOfDaySubsystem_GetPassedDays_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTimeOfDaySubsystem.GetNormalizedTimeOfDay
struct AFGTimeOfDaySubsystem_GetNormalizedTimeOfDay_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTimeOfDaySubsystem.GetNighttimeSeconds
struct AFGTimeOfDaySubsystem_GetNighttimeSeconds_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTimeOfDaySubsystem.GetNightPct
struct AFGTimeOfDaySubsystem_GetNightPct_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTimeOfDaySubsystem.GetMinutes
struct AFGTimeOfDaySubsystem_GetMinutes_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTimeOfDaySubsystem.GetHours
struct AFGTimeOfDaySubsystem_GetHours_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTimeOfDaySubsystem.GetDaytimeSeconds
struct AFGTimeOfDaySubsystem_GetDaytimeSeconds_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTimeOfDaySubsystem.GetDaySeconds
struct AFGTimeOfDaySubsystem_GetDaySeconds_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTimeOfDaySubsystem.GetDayPct
struct AFGTimeOfDaySubsystem_GetDayPct_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTimeOfDaySubsystem.GetDayMinutes
struct AFGTimeOfDaySubsystem_GetDayMinutes_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTimeOfDaySubsystem.Get
struct AFGTimeOfDaySubsystem_Get_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGTimeOfDaySubsystem*                       ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTrain.SetTrainName
struct AFGTrain_SetTrainName_Params
{
	struct FText                                       Name;                                                     // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function FactoryGame.FGTrain.NewTimeTable
struct AFGTrain_NewTimeTable_Params
{
	class AFGRailroadTimeTable*                        ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTrain.GetTrainName
struct AFGTrain_GetTrainName_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGTrain.GetTrackGraphID
struct AFGTrain_GetTrackGraphID_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTrain.GetTimeTable
struct AFGTrain_GetTimeTable_Params
{
	class AFGRailroadTimeTable*                        ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTrain.GetSelfDrivingError
struct AFGTrain_GetSelfDrivingError_Params
{
	ESelfDrivingLocomotiveError                        ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTrain.GetMaxAirBrakeDeceleration
struct AFGTrain_GetMaxAirBrakeDeceleration_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTrain.GetLastVehicle
struct AFGTrain_GetLastVehicle_Params
{
	class AFGRailroadVehicle*                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTrain.GetIsDocked
struct AFGTrain_GetIsDocked_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTrain.GetFirstVehicle
struct AFGTrain_GetFirstVehicle_Params
{
	class AFGRailroadVehicle*                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTrainStationIdentifier.SetStationName
struct AFGTrainStationIdentifier_SetStationName_Params
{
	struct FText                                       Text;                                                     // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function FactoryGame.FGTrainStationIdentifier.OnRep_StationName
struct AFGTrainStationIdentifier_OnRep_StationName_Params
{
};

// Function FactoryGame.FGTrainStationIdentifier.GetTrackGraphID
struct AFGTrainStationIdentifier_GetTrackGraphID_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTrainStationIdentifier.GetStationName
struct AFGTrainStationIdentifier_GetStationName_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGTrainStationIdentifier.GetStation
struct AFGTrainStationIdentifier_GetStation_Params
{
	class AFGBuildableRailroadStation*                 ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTutorialIntroManager.UpdateTutorial
struct AFGTutorialIntroManager_UpdateTutorial_Params
{
	EIntroTutorialSteps                                nextTutorialStep;                                         // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGTutorialIntroManager.StartSkipIntroSequence
struct AFGTutorialIntroManager_StartSkipIntroSequence_Params
{
};

// Function FactoryGame.FGTutorialIntroManager.SetInputGatesFromTutorialLevel
struct AFGTutorialIntroManager_SetInputGatesFromTutorialLevel_Params
{
	class AFGPlayerController*                         PlayerController;                                         // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGTutorialIntroManager.SetCanSkipTutorialIntro
struct AFGTutorialIntroManager_SetCanSkipTutorialIntro_Params
{
	bool                                               canSkip;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGTutorialIntroManager.OnSchematicPurchased
struct AFGTutorialIntroManager_OnSchematicPurchased_Params
{
	class UClass*                                      newSchematic;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGTutorialIntroManager.OnRep_TradingPostLevel
struct AFGTutorialIntroManager_OnRep_TradingPostLevel_Params
{
};

// Function FactoryGame.FGTutorialIntroManager.OnPlayerAddedItemToInventory
struct AFGTutorialIntroManager_OnPlayerAddedItemToInventory_Params
{
	class UClass*                                      ItemClass;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                numAdded;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGTutorialIntroManager.OnPlayerAddedItemToArmSlot
struct AFGTutorialIntroManager_OnPlayerAddedItemToArmSlot_Params
{
	class UClass*                                      ItemClass;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                numAdded;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGTutorialIntroManager.OnBuildingBuiltGlobal
struct AFGTutorialIntroManager_OnBuildingBuiltGlobal_Params
{
	class AFGBuildable*                                buildable;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGTutorialIntroManager.IntroDone
struct AFGTutorialIntroManager_IntroDone_Params
{
};

// Function FactoryGame.FGTutorialIntroManager.HasTradingpostBeenBuilt
struct AFGTutorialIntroManager_HasTradingpostBeenBuilt_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTutorialIntroManager.GetTradingPostLevel
struct AFGTutorialIntroManager_GetTradingPostLevel_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTutorialIntroManager.GetNormalizedProgressToSkip
struct AFGTutorialIntroManager_GetNormalizedProgressToSkip_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTutorialIntroManager.GetIsTutorialCompleted
struct AFGTutorialIntroManager_GetIsTutorialCompleted_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTutorialIntroManager.GetIsIntroSequenceDone
struct AFGTutorialIntroManager_GetIsIntroSequenceDone_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTutorialIntroManager.GetCurrentTutorialStep
struct AFGTutorialIntroManager_GetCurrentTutorialStep_Params
{
	EIntroTutorialSteps                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTutorialIntroManager.GetCanSkipTutorial
struct AFGTutorialIntroManager_GetCanSkipTutorial_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTutorialIntroManager.Get
struct AFGTutorialIntroManager_Get_Params
{
	class UObject*                                     WorldContext;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGTutorialIntroManager*                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGTutorialIntroManager.EndSkipIntroSequence
struct AFGTutorialIntroManager_EndSkipIntroSequence_Params
{
};

// Function FactoryGame.FGTutorialIntroManager.CompleteTutorial
struct AFGTutorialIntroManager_CompleteTutorial_Params
{
};

// Function FactoryGame.FGTutorialIntroManager.CancelSkipIntroSequence
struct AFGTutorialIntroManager_CancelSkipIntroSequence_Params
{
};

// Function FactoryGame.FGTutorialSubsystem.OnBuildingBuilt
struct UFGTutorialSubsystem_OnBuildingBuilt_Params
{
	class UClass*                                      itemDesc;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGTutorialSubsystem.ClearBuiltData
struct UFGTutorialSubsystem_ClearBuiltData_Params
{
};

// Function FactoryGame.FGTutorialSubsystem.AddToBuiltClasses
struct UFGTutorialSubsystem_AddToBuiltClasses_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGUseableInterface.UpdateUseState
struct UFGUseableInterface_UpdateUseState_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     atLocation;                                               // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	class UPrimitiveComponent*                         componentHit;                                             // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FUseState                                   out_useState;                                             // (Parm, OutParm, ReferenceParm)
};

// Function FactoryGame.FGUseableInterface.UnregisterInteractingPlayer
struct UFGUseableInterface_UnregisterInteractingPlayer_Params
{
	class AFGCharacterPlayer*                          Player;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGUseableInterface.StopIsLookedAt
struct UFGUseableInterface_StopIsLookedAt_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function FactoryGame.FGUseableInterface.StartIsLookedAt
struct UFGUseableInterface_StartIsLookedAt_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function FactoryGame.FGUseableInterface.RegisterInteractingPlayer
struct UFGUseableInterface_RegisterInteractingPlayer_Params
{
	class AFGCharacterPlayer*                          Player;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGUseableInterface.OnUseStop
struct UFGUseableInterface_OnUseStop_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function FactoryGame.FGUseableInterface.OnUse
struct UFGUseableInterface_OnUse_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function FactoryGame.FGUseableInterface.IsUseable
struct UFGUseableInterface_IsUseable_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGUseableInterface.GetLookAtDecription
struct UFGUseableInterface_GetLookAtDecription_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function FactoryGame.FGVehicleCollisionBoxComponent.OnOverlapBegin
struct UFGVehicleCollisionBoxComponent_OnOverlapBegin_Params
{
	class UPrimitiveComponent*                         OverlappedComp;                                           // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bFromSweep;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  SweepResult;                                              // (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function FactoryGame.FGVehicleDescriptor.GetVehicleClass
struct UFGVehicleDescriptor_GetVehicleClass_Params
{
	class UClass*                                      inClass;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGVehicleDestroyableInterface.GetForceThreshold
struct UFGVehicleDestroyableInterface_GetForceThreshold_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGVehicleDestroyableInterface.GetDestroyEffect
struct UFGVehicleDestroyableInterface_GetDestroyEffect_Params
{
	class UParticleSystem*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGVehicleDestroyableInterface.GetDestroyAudioEvent
struct UFGVehicleDestroyableInterface_GetDestroyAudioEvent_Params
{
	class UAkAudioEvent*                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGVersionFunctionLibrary.IsPublicBuild
struct UFGVersionFunctionLibrary_IsPublicBuild_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGVersionFunctionLibrary.GetVersionString
struct UFGVersionFunctionLibrary_GetVersionString_Params
{
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function FactoryGame.FGVersionFunctionLibrary.GetGameVersion
struct UFGVersionFunctionLibrary_GetGameVersion_Params
{
	EGameVersion                                       ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGVirtualCursorFunctionLibrary.EnableVirtualCursor
struct UFGVirtualCursorFunctionLibrary_EnableVirtualCursor_Params
{
	class APlayerController*                           PC;                                                       // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGVirtualCursorFunctionLibrary.DisableVirtualCursor
struct UFGVirtualCursorFunctionLibrary_DisableVirtualCursor_Params
{
	class APlayerController*                           PC;                                                       // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGVolumeMapArea.OnPrimitiveComponentEntered
struct AFGVolumeMapArea_OnPrimitiveComponentEntered_Params
{
	class UPrimitiveComponent*                         OverlappedComp;                                           // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      Other;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               fromSweep;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  SweepResult;                                              // (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function FactoryGame.FGVolumeMapArea.GetMapArea
struct AFGVolumeMapArea_GetMapArea_Params
{
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWaterAudio.OnPawnHitSurface
struct UFGWaterAudio_OnPawnHitSurface_Params
{
	class AFGWaterVolume*                              waterVolume;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class APawn*                                       Pawn;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     surfaceLocation;                                          // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGWaterAudio.OnCameraExitedWater
struct UFGWaterAudio_OnCameraExitedWater_Params
{
	class AFGWaterVolume*                              waterVolume;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     exitLocation;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGPlayerController*                         PC;                                                       // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGWaterAudio.OnCameraEnteredWater
struct UFGWaterAudio_OnCameraEnteredWater_Params
{
	class AFGWaterVolume*                              waterVolume;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     enterLocation;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	class AFGPlayerController*                         PC;                                                       // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGWaterAudio.GetImpactEvent
struct UFGWaterAudio_GetImpactEvent_Params
{
	class APawn*                                       Pawn;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	class UAkAudioEvent*                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWaterVolume.OnPrimitiveComponentExited
struct AFGWaterVolume_OnPrimitiveComponentExited_Params
{
	class UPrimitiveComponent*                         OverlappedComp;                                           // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      Other;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGWaterVolume.OnPrimitiveComponentEntered
struct AFGWaterVolume_OnPrimitiveComponentEntered_Params
{
	class UPrimitiveComponent*                         OverlappedComp;                                           // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      Other;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               fromSweep;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  SweepResult;                                              // (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function FactoryGame.FGWeaponChild.NotifyReloading
struct AFGWeaponChild_NotifyReloading_Params
{
};

// Function FactoryGame.FGWeaponChild.NotifyReloadComplete
struct AFGWeaponChild_NotifyReloadComplete_Params
{
};

// Function FactoryGame.FGWeaponChild.NotifyPrimaryFireExecuted
struct AFGWeaponChild_NotifyPrimaryFireExecuted_Params
{
};

// Function FactoryGame.FGWeaponChild.NotifyFailedToFire
struct AFGWeaponChild_NotifyFailedToFire_Params
{
};

// Function FactoryGame.FGWeaponChild.NotifyEndSecondaryFire
struct AFGWeaponChild_NotifyEndSecondaryFire_Params
{
};

// Function FactoryGame.FGWeaponChild.NotifyEndPrimaryFire
struct AFGWeaponChild_NotifyEndPrimaryFire_Params
{
};

// Function FactoryGame.FGWeaponChild.NotifyBeginSecondaryFire
struct AFGWeaponChild_NotifyBeginSecondaryFire_Params
{
};

// Function FactoryGame.FGWeaponChild.NotifyBeginPrimaryFire
struct AFGWeaponChild_NotifyBeginPrimaryFire_Params
{
};

// Function FactoryGame.FGWheeledVehicle.WantsToMove
struct AFGWheeledVehicle_WantsToMove_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.UseReplicatedState
struct AFGWheeledVehicle_UseReplicatedState_Params
{
};

// Function FactoryGame.FGWheeledVehicle.SetPathVisibility
struct AFGWheeledVehicle_SetPathVisibility_Params
{
	bool                                               inVisible;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.SetPathFromArray
struct AFGWheeledVehicle_SetPathFromArray_Params
{
	TArray<class AFGTargetPoint*>                      targetPoints;                                             // (Parm, ZeroConstructor)
};

// Function FactoryGame.FGWheeledVehicle.SetMovementComponent
struct AFGWheeledVehicle_SetMovementComponent_Params
{
	class UWheeledVehicleMovementComponent*            MovementComponent;                                        // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.SetIsDrifting
struct AFGWheeledVehicle_SetIsDrifting_Params
{
	bool                                               newDrifting;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.SetAddedAngularVelocityYaw
struct AFGWheeledVehicle_SetAddedAngularVelocityYaw_Params
{
	float                                              yawToAdd;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.SetAddedAngularVelocityPitch
struct AFGWheeledVehicle_SetAddedAngularVelocityPitch_Params
{
	float                                              pitchToAdd;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.ServerUpdateAssistedVelocitiesState
struct AFGWheeledVehicle_ServerUpdateAssistedVelocitiesState_Params
{
	bool                                               inDrifting;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              inInputYaw;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              inInputPitch;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.ResetAddedAngularVelocityValues
struct AFGWheeledVehicle_ResetAddedAngularVelocityValues_Params
{
};

// Function FactoryGame.FGWheeledVehicle.RemoveTargetPoint
struct AFGWheeledVehicle_RemoveTargetPoint_Params
{
	class AFGTargetPoint*                              targetToRemove;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.PlayFoliageDestroyedEffect
struct AFGWheeledVehicle_PlayFoliageDestroyedEffect_Params
{
	class UParticleSystem*                             destroyEffect;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	class UAkAudioEvent*                               destroyAudioEvent;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Location;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.OnRep_TransferStatusChanged
struct AFGWheeledVehicle_OnRep_TransferStatusChanged_Params
{
};

// Function FactoryGame.FGWheeledVehicle.OnRep_IsSimulated
struct AFGWheeledVehicle_OnRep_IsSimulated_Params
{
};

// Function FactoryGame.FGWheeledVehicle.OnOverlapEnd
struct AFGWheeledVehicle_OnOverlapEnd_Params
{
	class UPrimitiveComponent*                         OverlappedComp;                                           // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.OnOverlapBegin
struct AFGWheeledVehicle_OnOverlapBegin_Params
{
	class UPrimitiveComponent*                         OverlappedComp;                                           // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bFromSweep;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  SweepResult;                                              // (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.NumWheelsOnGround
struct AFGWheeledVehicle_NumWheelsOnGround_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.IsValidFuel
struct AFGWheeledVehicle_IsValidFuel_Params
{
	class UClass*                                      Resource;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.IsSimulated
struct AFGWheeledVehicle_IsSimulated_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.HasFuel
struct AFGWheeledVehicle_HasFuel_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.GetVehicleMovementComponent
struct AFGWheeledVehicle_GetVehicleMovementComponent_Params
{
	class UWheeledVehicleMovementComponent*            ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.GetTireData
struct AFGWheeledVehicle_GetTireData_Params
{
	TArray<struct FTireData>                           out_tireData;                                             // (Parm, OutParm, ZeroConstructor)
};

// Function FactoryGame.FGWheeledVehicle.GetTargetNodeLinkedList
struct AFGWheeledVehicle_GetTargetNodeLinkedList_Params
{
	class UFGTargetPointLinkedList*                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.GetStorageInventory
struct AFGWheeledVehicle_GetStorageInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.GetSimulationComponent
struct AFGWheeledVehicle_GetSimulationComponent_Params
{
	class UFloatingPawnMovement*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.GetPathVisibility
struct AFGWheeledVehicle_GetPathVisibility_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.GetIsInAir
struct AFGWheeledVehicle_GetIsInAir_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.GetIsGrounded
struct AFGWheeledVehicle_GetIsGrounded_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.GetIsDrifting
struct AFGWheeledVehicle_GetIsDrifting_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.GetFuelInventory
struct AFGWheeledVehicle_GetFuelInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.GetForwardSpeed
struct AFGWheeledVehicle_GetForwardSpeed_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.GetDriftForceOffset
struct AFGWheeledVehicle_GetDriftForceOffset_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.FilterFuelClasses
struct AFGWheeledVehicle_FilterFuelClasses_Params
{
	class UClass*                                      Object;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                idx;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicle.CreateInventoryItemDrops
struct AFGWheeledVehicle_CreateInventoryItemDrops_Params
{
};

// Function FactoryGame.FGWheeledVehicleMovementComponent4W.GetLargestTireLoadValue
struct UFGWheeledVehicleMovementComponent4W_GetLargestTireLoadValue_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicleMovementComponent4W.GetLargestLongitudinalSlip
struct UFGWheeledVehicleMovementComponent4W_GetLargestLongitudinalSlip_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicleMovementComponent4W.GetLargestLateralSlip
struct UFGWheeledVehicleMovementComponent4W_GetLargestLateralSlip_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicleMovementComponent6W.GetLargestTireLoadValue
struct UFGWheeledVehicleMovementComponent6W_GetLargestTireLoadValue_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicleMovementComponent6W.GetLargestLongitudinalSlip
struct UFGWheeledVehicleMovementComponent6W_GetLargestLongitudinalSlip_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWheeledVehicleMovementComponent6W.GetLargestLateralSlip
struct UFGWheeledVehicleMovementComponent6W_GetLargestLateralSlip_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWidgetSwitcher.FadeOut
struct UFGWidgetSwitcher_FadeOut_Params
{
};

// Function FactoryGame.FGWidgetSwitcher.ExitAnimationTookToLong
struct UFGWidgetSwitcher_ExitAnimationTookToLong_Params
{
};

// Function FactoryGame.FGWidgetSwitcher.EnterAnimationTookToLong
struct UFGWidgetSwitcher_EnterAnimationTookToLong_Params
{
};

// Function FactoryGame.FGWindow.GetCloseButton
struct UFGWindow_GetCloseButton_Params
{
	class UUserWidget*                                 ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGWireHologram.OnAutomaticPoleDisableToggle
struct AFGWireHologram_OnAutomaticPoleDisableToggle_Params
{
	bool                                               Disabled;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGWorkBench.SetWorkBenchUser
struct UFGWorkBench_SetWorkBenchUser_Params
{
	class AFGCharacterPlayer*                          newUser;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGWorkBench.SetRecipe
struct UFGWorkBench_SetRecipe_Params
{
	class UClass*                                      Recipe;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGWorkBench.SetIsPressingProduce
struct UFGWorkBench_SetIsPressingProduce_Params
{
	bool                                               isPressingProduce;                                        // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGWorkBench.SetInventory
struct UFGWorkBench_SetInventory_Params
{
	class UFGInventoryComponent*                       newInventory;                                             // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGWorkBench.SetHoldToProduce
struct UFGWorkBench_SetHoldToProduce_Params
{
	bool                                               newHold;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGWorkBench.RemoveIngredientsAndAwardRewards
struct UFGWorkBench_RemoveIngredientsAndAwardRewards_Params
{
	class UFGInventoryComponent*                       inventory;                                                // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UClass*                                      Recipe;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGWorkBench.Produce
struct UFGWorkBench_Produce_Params
{
	float                                              produceSpeed;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function FactoryGame.FGWorkBench.IsProducing
struct UFGWorkBench_IsProducing_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWorkBench.GetWorkBenchUser
struct UFGWorkBench_GetWorkBenchUser_Params
{
	class AFGCharacterPlayer*                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWorkBench.GetProduceClickSpeed
struct UFGWorkBench_GetProduceClickSpeed_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWorkBench.GetPlayerWorkingAtBench
struct UFGWorkBench_GetPlayerWorkingAtBench_Params
{
	class AFGCharacterPlayer*                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWorkBench.GetManufacturingSpeed
struct UFGWorkBench_GetManufacturingSpeed_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWorkBench.GetManufacturingProgress
struct UFGWorkBench_GetManufacturingProgress_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWorkBench.GetInventory
struct UFGWorkBench_GetInventory_Params
{
	class UFGInventoryComponent*                       ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function FactoryGame.FGWorkBench.GetHoldToProduce
struct UFGWorkBench_GetHoldToProduce_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWorkBench.GetCurrentRecipe
struct UFGWorkBench_GetCurrentRecipe_Params
{
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWorkBench.CraftComplete
struct UFGWorkBench_CraftComplete_Params
{
};

// Function FactoryGame.FGWorkBench.CanProduce
struct UFGWorkBench_CanProduce_Params
{
	class UClass*                                      Recipe;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class UFGInventoryComponent*                       inventory;                                                // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function FactoryGame.FGWorldSettings.UpdateWorldBounds
struct AFGWorldSettings_UpdateWorldBounds_Params
{
};

// Function FactoryGame.FGWorldSettings.GetLevelStartedAkEvent
struct AFGWorldSettings_GetLevelStartedAkEvent_Params
{
	class UAkAudioEvent*                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

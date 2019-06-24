#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_AIModule_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function AIModule.AISystem.AILoggingVerbose
struct UAISystem_AILoggingVerbose_Params
{
};

// Function AIModule.AISystem.AIIgnorePlayers
struct UAISystem_AIIgnorePlayers_Params
{
};

// Function AIModule.AIController.UseBlackboard
struct AAIController_UseBlackboard_Params
{
	class UBlackboardData*                             BlackboardAsset;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	class UBlackboardComponent*                        BlackboardComponent;                                      // (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.AIController.UnclaimTaskResource
struct AAIController_UnclaimTaskResource_Params
{
	class UClass*                                      ResourceClass;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AIController.SetPathFollowingComponent
struct AAIController_SetPathFollowingComponent_Params
{
	class UPathFollowingComponent*                     NewPFComponent;                                           // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function AIModule.AIController.SetMoveBlockDetection
struct AAIController_SetMoveBlockDetection_Params
{
	bool                                               bEnable;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AIController.RunBehaviorTree
struct AAIController_RunBehaviorTree_Params
{
	class UBehaviorTree*                               BTAsset;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.AIController.OnUsingBlackBoard
struct AAIController_OnUsingBlackBoard_Params
{
	class UBlackboardComponent*                        BlackboardComp;                                           // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBlackboardData*                             BlackboardAsset;                                          // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AIController.OnUnpossess
struct AAIController_OnUnpossess_Params
{
	class APawn*                                       UnpossessedPawn;                                          // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AIController.OnPossess
struct AAIController_OnPossess_Params
{
	class APawn*                                       PossessedPawn;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AIController.OnGameplayTaskResourcesClaimed
struct AAIController_OnGameplayTaskResourcesClaimed_Params
{
	struct FGameplayResourceSet                        NewlyClaimed;                                             // (Parm)
	struct FGameplayResourceSet                        FreshlyReleased;                                          // (Parm)
};

// Function AIModule.AIController.MoveToLocation
struct AAIController_MoveToLocation_Params
{
	struct FVector                                     Dest;                                                     // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	float                                              AcceptanceRadius;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bStopOnOverlap;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bUsePathfinding;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bProjectDestinationToNavigation;                          // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bCanStrafe;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      FilterClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bAllowPartialPath;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EPathFollowingRequestResult>           ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.AIController.MoveToActor
struct AAIController_MoveToActor_Params
{
	class AActor*                                      Goal;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              AcceptanceRadius;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bStopOnOverlap;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bUsePathfinding;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bCanStrafe;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      FilterClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bAllowPartialPath;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EPathFollowingRequestResult>           ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.AIController.K2_SetFocus
struct AAIController_K2_SetFocus_Params
{
	class AActor*                                      NewFocus;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AIController.K2_SetFocalPoint
struct AAIController_K2_SetFocalPoint_Params
{
	struct FVector                                     FP;                                                       // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AIController.K2_ClearFocus
struct AAIController_K2_ClearFocus_Params
{
};

// Function AIModule.AIController.HasPartialPath
struct AAIController_HasPartialPath_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.AIController.GetPathFollowingComponent
struct AAIController_GetPathFollowingComponent_Params
{
	class UPathFollowingComponent*                     ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function AIModule.AIController.GetMoveStatus
struct AAIController_GetMoveStatus_Params
{
	TEnumAsByte<EPathFollowingStatus>                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.AIController.GetImmediateMoveDestination
struct AAIController_GetImmediateMoveDestination_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.AIController.GetFocusActor
struct AAIController_GetFocusActor_Params
{
	class AActor*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.AIController.GetFocalPointOnActor
struct AAIController_GetFocalPointOnActor_Params
{
	class AActor*                                      Actor;                                                    // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.AIController.GetFocalPoint
struct AAIController_GetFocalPoint_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.AIController.GetAIPerceptionComponent
struct AAIController_GetAIPerceptionComponent_Params
{
	class UAIPerceptionComponent*                      ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function AIModule.AIController.ClaimTaskResource
struct AAIController_ClaimTaskResource_Params
{
	class UClass*                                      ResourceClass;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AIAsyncTaskBlueprintProxy.OnMoveCompleted
struct UAIAsyncTaskBlueprintProxy_OnMoveCompleted_Params
{
	struct FAIRequestID                                RequestID;                                                // (Parm)
	TEnumAsByte<EPathFollowingResult>                  MovementResult;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AIBlueprintHelperLibrary.UnlockAIResourcesWithAnimation
struct UAIBlueprintHelperLibrary_UnlockAIResourcesWithAnimation_Params
{
	class UAnimInstance*                               AnimInstance;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bUnlockMovement;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               UnlockAILogic;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AIBlueprintHelperLibrary.SpawnAIFromClass
struct UAIBlueprintHelperLibrary_SpawnAIFromClass_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      PawnClass;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	class UBehaviorTree*                               BehaviorTree;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Location;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	struct FRotator                                    Rotation;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bNoCollisionFail;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	class APawn*                                       ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.AIBlueprintHelperLibrary.SimpleMoveToLocation
struct UAIBlueprintHelperLibrary_SimpleMoveToLocation_Params
{
	class AController*                                 Controller;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Goal;                                                     // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
};

// Function AIModule.AIBlueprintHelperLibrary.SimpleMoveToActor
struct UAIBlueprintHelperLibrary_SimpleMoveToActor_Params
{
	class AController*                                 Controller;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      Goal;                                                     // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AIBlueprintHelperLibrary.SendAIMessage
struct UAIBlueprintHelperLibrary_SendAIMessage_Params
{
	class APawn*                                       Target;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	struct FName                                       MESSAGE;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     MessageSource;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bSuccess;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AIBlueprintHelperLibrary.LockAIResourcesWithAnimation
struct UAIBlueprintHelperLibrary_LockAIResourcesWithAnimation_Params
{
	class UAnimInstance*                               AnimInstance;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bLockMovement;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               LockAILogic;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AIBlueprintHelperLibrary.IsValidAIRotation
struct UAIBlueprintHelperLibrary_IsValidAIRotation_Params
{
	struct FRotator                                    Rotation;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.AIBlueprintHelperLibrary.IsValidAILocation
struct UAIBlueprintHelperLibrary_IsValidAILocation_Params
{
	struct FVector                                     Location;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.AIBlueprintHelperLibrary.IsValidAIDirection
struct UAIBlueprintHelperLibrary_IsValidAIDirection_Params
{
	struct FVector                                     DirectionVector;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.AIBlueprintHelperLibrary.GetCurrentPath
struct UAIBlueprintHelperLibrary_GetCurrentPath_Params
{
	class AController*                                 Controller;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class UNavigationPath*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.AIBlueprintHelperLibrary.GetBlackboard
struct UAIBlueprintHelperLibrary_GetBlackboard_Params
{
	class AActor*                                      Target;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class UBlackboardComponent*                        ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function AIModule.AIBlueprintHelperLibrary.GetAIController
struct UAIBlueprintHelperLibrary_GetAIController_Params
{
	class AActor*                                      ControlledActor;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	class AAIController*                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.AIBlueprintHelperLibrary.CreateMoveToProxyObject
struct UAIBlueprintHelperLibrary_CreateMoveToProxyObject_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class APawn*                                       Pawn;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Destination;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      targetActor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              AcceptanceRadius;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bStopOnOverlap;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	class UAIAsyncTaskBlueprintProxy*                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.AIPerceptionComponent.SetSenseEnabled
struct UAIPerceptionComponent_SetSenseEnabled_Params
{
	class UClass*                                      SenseClass;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bEnable;                                                  // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AIPerceptionComponent.RequestStimuliListenerUpdate
struct UAIPerceptionComponent_RequestStimuliListenerUpdate_Params
{
};

// Function AIModule.AIPerceptionComponent.OnOwnerEndPlay
struct UAIPerceptionComponent_OnOwnerEndPlay_Params
{
	class AActor*                                      Actor;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EEndPlayReason>                        EndPlayReason;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AIPerceptionComponent.GetPerceivedHostileActors
struct UAIPerceptionComponent_GetPerceivedHostileActors_Params
{
	TArray<class AActor*>                              OutActors;                                                // (Parm, OutParm, ZeroConstructor)
};

// Function AIModule.AIPerceptionComponent.GetPerceivedActors
struct UAIPerceptionComponent_GetPerceivedActors_Params
{
	class UClass*                                      SenseToUse;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class AActor*>                              OutActors;                                                // (Parm, OutParm, ZeroConstructor)
};

// Function AIModule.AIPerceptionComponent.GetKnownPerceivedActors
struct UAIPerceptionComponent_GetKnownPerceivedActors_Params
{
	class UClass*                                      SenseToUse;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class AActor*>                              OutActors;                                                // (Parm, OutParm, ZeroConstructor)
};

// Function AIModule.AIPerceptionComponent.GetCurrentlyPerceivedActors
struct UAIPerceptionComponent_GetCurrentlyPerceivedActors_Params
{
	class UClass*                                      SenseToUse;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class AActor*>                              OutActors;                                                // (Parm, OutParm, ZeroConstructor)
};

// Function AIModule.AIPerceptionComponent.GetActorsPerception
struct UAIPerceptionComponent_GetActorsPerception_Params
{
	class AActor*                                      Actor;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	struct FActorPerceptionBlueprintInfo               Info;                                                     // (Parm, OutParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.AIPerceptionStimuliSourceComponent.UnregisterFromSense
struct UAIPerceptionStimuliSourceComponent_UnregisterFromSense_Params
{
	class UClass*                                      SenseClass;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AIPerceptionStimuliSourceComponent.UnregisterFromPerceptionSystem
struct UAIPerceptionStimuliSourceComponent_UnregisterFromPerceptionSystem_Params
{
};

// Function AIModule.AIPerceptionStimuliSourceComponent.RegisterWithPerceptionSystem
struct UAIPerceptionStimuliSourceComponent_RegisterWithPerceptionSystem_Params
{
};

// Function AIModule.AIPerceptionStimuliSourceComponent.RegisterForSense
struct UAIPerceptionStimuliSourceComponent_RegisterForSense_Params
{
	class UClass*                                      SenseClass;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AIPerceptionSystem.ReportPerceptionEvent
struct UAIPerceptionSystem_ReportPerceptionEvent_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UAISenseEvent*                               PerceptionEvent;                                          // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AIPerceptionSystem.ReportEvent
struct UAIPerceptionSystem_ReportEvent_Params
{
	class UAISenseEvent*                               PerceptionEvent;                                          // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AIPerceptionSystem.RegisterPerceptionStimuliSource
struct UAIPerceptionSystem_RegisterPerceptionStimuliSource_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      Sense;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      Target;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.AIPerceptionSystem.OnPerceptionStimuliSourceEndPlay
struct UAIPerceptionSystem_OnPerceptionStimuliSourceEndPlay_Params
{
	class AActor*                                      Actor;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EEndPlayReason>                        EndPlayReason;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AIPerceptionSystem.GetSenseClassForStimulus
struct UAIPerceptionSystem_GetSenseClassForStimulus_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	struct FAIStimulus                                 Stimulus;                                                 // (ConstParm, Parm, OutParm, ReferenceParm)
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.AISense_Blueprint.OnUpdate
struct UAISense_Blueprint_OnUpdate_Params
{
	TArray<class UAISenseEvent*>                       EventsToProcess;                                          // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.AISense_Blueprint.OnListenerUpdated
struct UAISense_Blueprint_OnListenerUpdated_Params
{
	class AActor*                                      ActorListener;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	class UAIPerceptionComponent*                      PerceptionComponent;                                      // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function AIModule.AISense_Blueprint.OnListenerUnregistered
struct UAISense_Blueprint_OnListenerUnregistered_Params
{
	class AActor*                                      ActorListener;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	class UAIPerceptionComponent*                      PerceptionComponent;                                      // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function AIModule.AISense_Blueprint.OnListenerRegistered
struct UAISense_Blueprint_OnListenerRegistered_Params
{
	class AActor*                                      ActorListener;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	class UAIPerceptionComponent*                      PerceptionComponent;                                      // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function AIModule.AISense_Blueprint.K2_OnNewPawn
struct UAISense_Blueprint_K2_OnNewPawn_Params
{
	class APawn*                                       NewPawn;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AISense_Blueprint.GetAllListenerComponents
struct UAISense_Blueprint_GetAllListenerComponents_Params
{
	TArray<class UAIPerceptionComponent*>              ListenerComponents;                                       // (Parm, OutParm, ZeroConstructor)
};

// Function AIModule.AISense_Blueprint.GetAllListenerActors
struct UAISense_Blueprint_GetAllListenerActors_Params
{
	TArray<class AActor*>                              ListenerActors;                                           // (Parm, OutParm, ZeroConstructor)
};

// Function AIModule.AISense_Damage.ReportDamageEvent
struct UAISense_Damage_ReportDamageEvent_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damagedActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      Instigator;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              damageAmount;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     EventLocation;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     HitLocation;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AISense_Hearing.ReportNoiseEvent
struct UAISense_Hearing_ReportNoiseEvent_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     NoiseLocation;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Loudness;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      Instigator;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              MaxRange;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	struct FName                                       Tag;                                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AISense_Prediction.RequestPawnPredictionEvent
struct UAISense_Prediction_RequestPawnPredictionEvent_Params
{
	class APawn*                                       Requestor;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      PredictedActor;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              PredictionTime;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AISense_Prediction.RequestControllerPredictionEvent
struct UAISense_Prediction_RequestControllerPredictionEvent_Params
{
	class AAIController*                               Requestor;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      PredictedActor;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              PredictionTime;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.AITask_MoveTo.AIMoveTo
struct UAITask_MoveTo_AIMoveTo_Params
{
	class AAIController*                               Controller;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     GoalLocation;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      GoalActor;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              AcceptanceRadius;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EAIOptionFlag>                         StopOnOverlap;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EAIOptionFlag>                         AcceptPartialPath;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bUsePathfinding;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bLockAILogic;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bUseContinuosGoalTracking;                                // (Parm, ZeroConstructor, IsPlainOldData)
	class UAITask_MoveTo*                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.AITask_RunEQS.RunEQS
struct UAITask_RunEQS_RunEQS_Params
{
	class AAIController*                               Controller;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class UEnvQuery*                                   QueryTemplate;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	class UAITask_RunEQS*                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BrainComponent.StopLogic
struct UBrainComponent_StopLogic_Params
{
	class FString                                      Reason;                                                   // (Parm, ZeroConstructor)
};

// Function AIModule.BrainComponent.RestartLogic
struct UBrainComponent_RestartLogic_Params
{
};

// Function AIModule.BrainComponent.IsRunning
struct UBrainComponent_IsRunning_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BrainComponent.IsPaused
struct UBrainComponent_IsPaused_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BehaviorTreeComponent.SetDynamicSubtree
struct UBehaviorTreeComponent_SetDynamicSubtree_Params
{
	struct FGameplayTag                                InjectTag;                                                // (Parm)
	class UBehaviorTree*                               BehaviorAsset;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BehaviorTreeComponent.GetTagCooldownEndTime
struct UBehaviorTreeComponent_GetTagCooldownEndTime_Params
{
	struct FGameplayTag                                CooldownTag;                                              // (Parm)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BehaviorTreeComponent.AddCooldownTagDuration
struct UBehaviorTreeComponent_AddCooldownTagDuration_Params
{
	struct FGameplayTag                                CooldownTag;                                              // (Parm)
	float                                              CooldownDuration;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bAddToExistingDuration;                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BlackboardComponent.SetValueAsVector
struct UBlackboardComponent_SetValueAsVector_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     VectorValue;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BlackboardComponent.SetValueAsString
struct UBlackboardComponent_SetValueAsString_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	class FString                                      StringValue;                                              // (Parm, ZeroConstructor)
};

// Function AIModule.BlackboardComponent.SetValueAsRotator
struct UBlackboardComponent_SetValueAsRotator_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FRotator                                    VectorValue;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BlackboardComponent.SetValueAsObject
struct UBlackboardComponent_SetValueAsObject_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	class UObject*                                     ObjectValue;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BlackboardComponent.SetValueAsName
struct UBlackboardComponent_SetValueAsName_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FName                                       NameValue;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BlackboardComponent.SetValueAsInt
struct UBlackboardComponent_SetValueAsInt_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	int                                                IntValue;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BlackboardComponent.SetValueAsFloat
struct UBlackboardComponent_SetValueAsFloat_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	float                                              FloatValue;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BlackboardComponent.SetValueAsEnum
struct UBlackboardComponent_SetValueAsEnum_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	unsigned char                                      EnumValue;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BlackboardComponent.SetValueAsClass
struct UBlackboardComponent_SetValueAsClass_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	class UClass*                                      ClassValue;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BlackboardComponent.SetValueAsBool
struct UBlackboardComponent_SetValueAsBool_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	bool                                               BoolValue;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BlackboardComponent.IsVectorValueSet
struct UBlackboardComponent_IsVectorValueSet_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BlackboardComponent.GetValueAsVector
struct UBlackboardComponent_GetValueAsVector_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BlackboardComponent.GetValueAsString
struct UBlackboardComponent_GetValueAsString_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function AIModule.BlackboardComponent.GetValueAsRotator
struct UBlackboardComponent_GetValueAsRotator_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FRotator                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BlackboardComponent.GetValueAsObject
struct UBlackboardComponent_GetValueAsObject_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	class UObject*                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BlackboardComponent.GetValueAsName
struct UBlackboardComponent_GetValueAsName_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FName                                       ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BlackboardComponent.GetValueAsInt
struct UBlackboardComponent_GetValueAsInt_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BlackboardComponent.GetValueAsFloat
struct UBlackboardComponent_GetValueAsFloat_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BlackboardComponent.GetValueAsEnum
struct UBlackboardComponent_GetValueAsEnum_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	unsigned char                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BlackboardComponent.GetValueAsClass
struct UBlackboardComponent_GetValueAsClass_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BlackboardComponent.GetValueAsBool
struct UBlackboardComponent_GetValueAsBool_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BlackboardComponent.GetRotationFromEntry
struct UBlackboardComponent_GetRotationFromEntry_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FRotator                                    ResultRotation;                                           // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BlackboardComponent.GetLocationFromEntry
struct UBlackboardComponent_GetLocationFromEntry_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     ResultLocation;                                           // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BlackboardComponent.ClearValue
struct UBlackboardComponent_ClearValue_Params
{
	struct FName                                       KeyName;                                                  // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
};

// Function AIModule.BTDecorator_BlueprintBase.ReceiveTickAI
struct UBTDecorator_BlueprintBase_ReceiveTickAI_Params
{
	class AAIController*                               OwnerController;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	class APawn*                                       ControlledPawn;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              DeltaSeconds;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTDecorator_BlueprintBase.ReceiveTick
struct UBTDecorator_BlueprintBase_ReceiveTick_Params
{
	class AActor*                                      OwnerActor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              DeltaSeconds;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTDecorator_BlueprintBase.ReceiveObserverDeactivatedAI
struct UBTDecorator_BlueprintBase_ReceiveObserverDeactivatedAI_Params
{
	class AAIController*                               OwnerController;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	class APawn*                                       ControlledPawn;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTDecorator_BlueprintBase.ReceiveObserverDeactivated
struct UBTDecorator_BlueprintBase_ReceiveObserverDeactivated_Params
{
	class AActor*                                      OwnerActor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTDecorator_BlueprintBase.ReceiveObserverActivatedAI
struct UBTDecorator_BlueprintBase_ReceiveObserverActivatedAI_Params
{
	class AAIController*                               OwnerController;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	class APawn*                                       ControlledPawn;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTDecorator_BlueprintBase.ReceiveObserverActivated
struct UBTDecorator_BlueprintBase_ReceiveObserverActivated_Params
{
	class AActor*                                      OwnerActor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTDecorator_BlueprintBase.ReceiveExecutionStartAI
struct UBTDecorator_BlueprintBase_ReceiveExecutionStartAI_Params
{
	class AAIController*                               OwnerController;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	class APawn*                                       ControlledPawn;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTDecorator_BlueprintBase.ReceiveExecutionStart
struct UBTDecorator_BlueprintBase_ReceiveExecutionStart_Params
{
	class AActor*                                      OwnerActor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTDecorator_BlueprintBase.ReceiveExecutionFinishAI
struct UBTDecorator_BlueprintBase_ReceiveExecutionFinishAI_Params
{
	class AAIController*                               OwnerController;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	class APawn*                                       ControlledPawn;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EBTNodeResult>                         NodeResult;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTDecorator_BlueprintBase.ReceiveExecutionFinish
struct UBTDecorator_BlueprintBase_ReceiveExecutionFinish_Params
{
	class AActor*                                      OwnerActor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EBTNodeResult>                         NodeResult;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTDecorator_BlueprintBase.PerformConditionCheckAI
struct UBTDecorator_BlueprintBase_PerformConditionCheckAI_Params
{
	class AAIController*                               OwnerController;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	class APawn*                                       ControlledPawn;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BTDecorator_BlueprintBase.PerformConditionCheck
struct UBTDecorator_BlueprintBase_PerformConditionCheck_Params
{
	class AActor*                                      OwnerActor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BTDecorator_BlueprintBase.IsDecoratorObserverActive
struct UBTDecorator_BlueprintBase_IsDecoratorObserverActive_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BTDecorator_BlueprintBase.IsDecoratorExecutionActive
struct UBTDecorator_BlueprintBase_IsDecoratorExecutionActive_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.StopUsingExternalEvent
struct UBTFunctionLibrary_StopUsingExternalEvent_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.StartUsingExternalEvent
struct UBTFunctionLibrary_StartUsingExternalEvent_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      OwningActor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.SetBlackboardValueAsVector
struct UBTFunctionLibrary_SetBlackboardValueAsVector_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FVector                                     Value;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.SetBlackboardValueAsString
struct UBTFunctionLibrary_SetBlackboardValueAsString_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	class FString                                      Value;                                                    // (Parm, ZeroConstructor)
};

// Function AIModule.BTFunctionLibrary.SetBlackboardValueAsRotator
struct UBTFunctionLibrary_SetBlackboardValueAsRotator_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FRotator                                    Value;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.SetBlackboardValueAsObject
struct UBTFunctionLibrary_SetBlackboardValueAsObject_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	class UObject*                                     Value;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.SetBlackboardValueAsName
struct UBTFunctionLibrary_SetBlackboardValueAsName_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FName                                       Value;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.SetBlackboardValueAsInt
struct UBTFunctionLibrary_SetBlackboardValueAsInt_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	int                                                Value;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.SetBlackboardValueAsFloat
struct UBTFunctionLibrary_SetBlackboardValueAsFloat_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	float                                              Value;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.SetBlackboardValueAsEnum
struct UBTFunctionLibrary_SetBlackboardValueAsEnum_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	unsigned char                                      Value;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.SetBlackboardValueAsClass
struct UBTFunctionLibrary_SetBlackboardValueAsClass_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	class UClass*                                      Value;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.SetBlackboardValueAsBool
struct UBTFunctionLibrary_SetBlackboardValueAsBool_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               Value;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.GetOwnersBlackboard
struct UBTFunctionLibrary_GetOwnersBlackboard_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	class UBlackboardComponent*                        ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.GetOwnerComponent
struct UBTFunctionLibrary_GetOwnerComponent_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	class UBehaviorTreeComponent*                      ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.GetBlackboardValueAsVector
struct UBTFunctionLibrary_GetBlackboardValueAsVector_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.GetBlackboardValueAsString
struct UBTFunctionLibrary_GetBlackboardValueAsString_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function AIModule.BTFunctionLibrary.GetBlackboardValueAsRotator
struct UBTFunctionLibrary_GetBlackboardValueAsRotator_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FRotator                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.GetBlackboardValueAsObject
struct UBTFunctionLibrary_GetBlackboardValueAsObject_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	class UObject*                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.GetBlackboardValueAsName
struct UBTFunctionLibrary_GetBlackboardValueAsName_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FName                                       ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.GetBlackboardValueAsInt
struct UBTFunctionLibrary_GetBlackboardValueAsInt_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.GetBlackboardValueAsFloat
struct UBTFunctionLibrary_GetBlackboardValueAsFloat_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.GetBlackboardValueAsEnum
struct UBTFunctionLibrary_GetBlackboardValueAsEnum_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	unsigned char                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.GetBlackboardValueAsClass
struct UBTFunctionLibrary_GetBlackboardValueAsClass_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.GetBlackboardValueAsBool
struct UBTFunctionLibrary_GetBlackboardValueAsBool_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.GetBlackboardValueAsActor
struct UBTFunctionLibrary_GetBlackboardValueAsActor_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	class AActor*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BTFunctionLibrary.ClearBlackboardValueAsVector
struct UBTFunctionLibrary_ClearBlackboardValueAsVector_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function AIModule.BTFunctionLibrary.ClearBlackboardValue
struct UBTFunctionLibrary_ClearBlackboardValue_Params
{
	class UBTNode*                                     NodeOwner;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      Key;                                                      // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function AIModule.BTService_BlueprintBase.ReceiveTickAI
struct UBTService_BlueprintBase_ReceiveTickAI_Params
{
	class AAIController*                               OwnerController;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	class APawn*                                       ControlledPawn;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              DeltaSeconds;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTService_BlueprintBase.ReceiveTick
struct UBTService_BlueprintBase_ReceiveTick_Params
{
	class AActor*                                      OwnerActor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              DeltaSeconds;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTService_BlueprintBase.ReceiveSearchStartAI
struct UBTService_BlueprintBase_ReceiveSearchStartAI_Params
{
	class AAIController*                               OwnerController;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	class APawn*                                       ControlledPawn;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTService_BlueprintBase.ReceiveSearchStart
struct UBTService_BlueprintBase_ReceiveSearchStart_Params
{
	class AActor*                                      OwnerActor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTService_BlueprintBase.ReceiveDeactivationAI
struct UBTService_BlueprintBase_ReceiveDeactivationAI_Params
{
	class AAIController*                               OwnerController;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	class APawn*                                       ControlledPawn;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTService_BlueprintBase.ReceiveDeactivation
struct UBTService_BlueprintBase_ReceiveDeactivation_Params
{
	class AActor*                                      OwnerActor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTService_BlueprintBase.ReceiveActivationAI
struct UBTService_BlueprintBase_ReceiveActivationAI_Params
{
	class AAIController*                               OwnerController;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	class APawn*                                       ControlledPawn;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTService_BlueprintBase.ReceiveActivation
struct UBTService_BlueprintBase_ReceiveActivation_Params
{
	class AActor*                                      OwnerActor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTService_BlueprintBase.IsServiceActive
struct UBTService_BlueprintBase_IsServiceActive_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BTTask_BlueprintBase.SetFinishOnMessageWithId
struct UBTTask_BlueprintBase_SetFinishOnMessageWithId_Params
{
	struct FName                                       MessageName;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                RequestID;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTTask_BlueprintBase.SetFinishOnMessage
struct UBTTask_BlueprintBase_SetFinishOnMessage_Params
{
	struct FName                                       MessageName;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTTask_BlueprintBase.ReceiveTickAI
struct UBTTask_BlueprintBase_ReceiveTickAI_Params
{
	class AAIController*                               OwnerController;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	class APawn*                                       ControlledPawn;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              DeltaSeconds;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTTask_BlueprintBase.ReceiveTick
struct UBTTask_BlueprintBase_ReceiveTick_Params
{
	class AActor*                                      OwnerActor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              DeltaSeconds;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTTask_BlueprintBase.ReceiveExecuteAI
struct UBTTask_BlueprintBase_ReceiveExecuteAI_Params
{
	class AAIController*                               OwnerController;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	class APawn*                                       ControlledPawn;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTTask_BlueprintBase.ReceiveExecute
struct UBTTask_BlueprintBase_ReceiveExecute_Params
{
	class AActor*                                      OwnerActor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTTask_BlueprintBase.ReceiveAbortAI
struct UBTTask_BlueprintBase_ReceiveAbortAI_Params
{
	class AAIController*                               OwnerController;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	class APawn*                                       ControlledPawn;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTTask_BlueprintBase.ReceiveAbort
struct UBTTask_BlueprintBase_ReceiveAbort_Params
{
	class AActor*                                      OwnerActor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTTask_BlueprintBase.IsTaskExecuting
struct UBTTask_BlueprintBase_IsTaskExecuting_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BTTask_BlueprintBase.IsTaskAborting
struct UBTTask_BlueprintBase_IsTaskAborting_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.BTTask_BlueprintBase.FinishExecute
struct UBTTask_BlueprintBase_FinishExecute_Params
{
	bool                                               bSuccess;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.BTTask_BlueprintBase.FinishAbort
struct UBTTask_BlueprintBase_FinishAbort_Params
{
};

// Function AIModule.PathFollowingComponent.OnNavDataRegistered
struct UPathFollowingComponent_OnNavDataRegistered_Params
{
	class ANavigationData*                             NavData;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.PathFollowingComponent.OnActorBump
struct UPathFollowingComponent_OnActorBump_Params
{
	class AActor*                                      SelfActor;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     NormalImpulse;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  Hit;                                                      // (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function AIModule.PathFollowingComponent.GetPathDestination
struct UPathFollowingComponent_GetPathDestination_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.PathFollowingComponent.GetPathActionType
struct UPathFollowingComponent_GetPathActionType_Params
{
	TEnumAsByte<EPathFollowingAction>                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.CrowdFollowingComponent.SuspendCrowdSteering
struct UCrowdFollowingComponent_SuspendCrowdSteering_Params
{
	bool                                               bSuspend;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.EnvQueryContext_BlueprintBase.ProvideSingleLocation
struct UEnvQueryContext_BlueprintBase_ProvideSingleLocation_Params
{
	class UObject*                                     QuerierObject;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      QuerierActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ResultingLocation;                                        // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.EnvQueryContext_BlueprintBase.ProvideSingleActor
struct UEnvQueryContext_BlueprintBase_ProvideSingleActor_Params
{
	class UObject*                                     QuerierObject;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      QuerierActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      ResultingActor;                                           // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.EnvQueryContext_BlueprintBase.ProvideLocationsSet
struct UEnvQueryContext_BlueprintBase_ProvideLocationsSet_Params
{
	class UObject*                                     QuerierObject;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      QuerierActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FVector>                             ResultingLocationSet;                                     // (Parm, OutParm, ZeroConstructor)
};

// Function AIModule.EnvQueryContext_BlueprintBase.ProvideActorsSet
struct UEnvQueryContext_BlueprintBase_ProvideActorsSet_Params
{
	class UObject*                                     QuerierObject;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      QuerierActor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<class AActor*>                              ResultingActorsSet;                                       // (Parm, OutParm, ZeroConstructor)
};

// Function AIModule.EnvQueryGenerator_BlueprintBase.GetQuerier
struct UEnvQueryGenerator_BlueprintBase_GetQuerier_Params
{
	class UObject*                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.EnvQueryGenerator_BlueprintBase.DoItemGeneration
struct UEnvQueryGenerator_BlueprintBase_DoItemGeneration_Params
{
	TArray<struct FVector>                             ContextLocations;                                         // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function AIModule.EnvQueryGenerator_BlueprintBase.AddGeneratedVector
struct UEnvQueryGenerator_BlueprintBase_AddGeneratedVector_Params
{
	struct FVector                                     GeneratedVector;                                          // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.EnvQueryGenerator_BlueprintBase.AddGeneratedActor
struct UEnvQueryGenerator_BlueprintBase_AddGeneratedActor_Params
{
	class AActor*                                      GeneratedActor;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.EnvQueryInstanceBlueprintWrapper.SetNamedParam
struct UEnvQueryInstanceBlueprintWrapper_SetNamedParam_Params
{
	struct FName                                       ParamName;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Value;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.EnvQueryInstanceBlueprintWrapper.GetResultsAsLocations
struct UEnvQueryInstanceBlueprintWrapper_GetResultsAsLocations_Params
{
	TArray<struct FVector>                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function AIModule.EnvQueryInstanceBlueprintWrapper.GetResultsAsActors
struct UEnvQueryInstanceBlueprintWrapper_GetResultsAsActors_Params
{
	TArray<class AActor*>                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function AIModule.EnvQueryInstanceBlueprintWrapper.GetItemScore
struct UEnvQueryInstanceBlueprintWrapper_GetItemScore_Params
{
	int                                                ItemIndex;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// DelegateFunction AIModule.EnvQueryInstanceBlueprintWrapper.EQSQueryDoneSignature__DelegateSignature
struct UEnvQueryInstanceBlueprintWrapper_EQSQueryDoneSignature__DelegateSignature_Params
{
	class UEnvQueryInstanceBlueprintWrapper*           QueryInstance;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EEnvQueryStatus>                       QueryStatus;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.EnvQueryManager.RunEQSQuery
struct UEnvQueryManager_RunEQSQuery_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UEnvQuery*                                   QueryTemplate;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     querier;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EEnvQueryRunMode>                      RunMode;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      WrapperClass;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UEnvQueryInstanceBlueprintWrapper*           ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.NavLinkProxy.SetSmartLinkEnabled
struct ANavLinkProxy_SetSmartLinkEnabled_Params
{
	bool                                               bEnabled;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.NavLinkProxy.ResumePathFollowing
struct ANavLinkProxy_ResumePathFollowing_Params
{
	class AActor*                                      Agent;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.NavLinkProxy.ReceiveSmartLinkReached
struct ANavLinkProxy_ReceiveSmartLinkReached_Params
{
	class AActor*                                      Agent;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Destination;                                              // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
};

// Function AIModule.NavLinkProxy.IsSmartLinkEnabled
struct ANavLinkProxy_IsSmartLinkEnabled_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.NavLinkProxy.HasMovingAgents
struct ANavLinkProxy_HasMovingAgents_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.NavLocalGridManager.SetLocalNavigationGridDensity
struct UNavLocalGridManager_SetLocalNavigationGridDensity_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              CellSize;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.NavLocalGridManager.RemoveLocalNavigationGrid
struct UNavLocalGridManager_RemoveLocalNavigationGrid_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                GridId;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bRebuildGrids;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.NavLocalGridManager.FindLocalNavigationGridPath
struct UNavLocalGridManager_FindLocalNavigationGridPath_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Start;                                                    // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     End;                                                      // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	TArray<struct FVector>                             PathPoints;                                               // (Parm, OutParm, ZeroConstructor)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.NavLocalGridManager.AddLocalNavigationGridForPoints
struct UNavLocalGridManager_AddLocalNavigationGridForPoints_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FVector>                             Locations;                                                // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	int                                                Radius2D;                                                 // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	float                                              Height;                                                   // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bRebuildGrids;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.NavLocalGridManager.AddLocalNavigationGridForPoint
struct UNavLocalGridManager_AddLocalNavigationGridForPoint_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Location;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	int                                                Radius2D;                                                 // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	float                                              Height;                                                   // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bRebuildGrids;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.NavLocalGridManager.AddLocalNavigationGridForCapsule
struct UNavLocalGridManager_AddLocalNavigationGridForCapsule_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Location;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	float                                              CapsuleRadius;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              CapsuleHalfHeight;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                Radius2D;                                                 // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	float                                              Height;                                                   // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bRebuildGrids;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.NavLocalGridManager.AddLocalNavigationGridForBox
struct UNavLocalGridManager_AddLocalNavigationGridForBox_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Location;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector                                     Extent;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	struct FRotator                                    Rotation;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                Radius2D;                                                 // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	float                                              Height;                                                   // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bRebuildGrids;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.PawnAction.GetActionPriority
struct UPawnAction_GetActionPriority_Params
{
	TEnumAsByte<EAIRequestPriority>                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.PawnAction.Finish
struct UPawnAction_Finish_Params
{
	TEnumAsByte<EPawnActionResult>                     WithResult;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.PawnAction.CreateActionInstance
struct UPawnAction_CreateActionInstance_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      ActionClass;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class UPawnAction*                                 ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.PawnAction_BlueprintBase.ActionTick
struct UPawnAction_BlueprintBase_ActionTick_Params
{
	class APawn*                                       ControlledPawn;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              DeltaSeconds;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.PawnAction_BlueprintBase.ActionStart
struct UPawnAction_BlueprintBase_ActionStart_Params
{
	class APawn*                                       ControlledPawn;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.PawnAction_BlueprintBase.ActionResume
struct UPawnAction_BlueprintBase_ActionResume_Params
{
	class APawn*                                       ControlledPawn;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.PawnAction_BlueprintBase.ActionPause
struct UPawnAction_BlueprintBase_ActionPause_Params
{
	class APawn*                                       ControlledPawn;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.PawnAction_BlueprintBase.ActionFinished
struct UPawnAction_BlueprintBase_ActionFinished_Params
{
	class APawn*                                       ControlledPawn;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EPawnActionResult>                     WithResult;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.PawnActionsComponent.K2_PushAction
struct UPawnActionsComponent_K2_PushAction_Params
{
	class UPawnAction*                                 NewAction;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EAIRequestPriority>                    Priority;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     Instigator;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.PawnActionsComponent.K2_PerformAction
struct UPawnActionsComponent_K2_PerformAction_Params
{
	class APawn*                                       Pawn;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	class UPawnAction*                                 Action;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EAIRequestPriority>                    Priority;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.PawnActionsComponent.K2_ForceAbortAction
struct UPawnActionsComponent_K2_ForceAbortAction_Params
{
	class UPawnAction*                                 ActionToAbort;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EPawnActionAbortState>                 ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.PawnActionsComponent.K2_AbortAction
struct UPawnActionsComponent_K2_AbortAction_Params
{
	class UPawnAction*                                 ActionToAbort;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EPawnActionAbortState>                 ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.PawnSensingComponent.SetSensingUpdatesEnabled
struct UPawnSensingComponent_SetSensingUpdatesEnabled_Params
{
	bool                                               bEnabled;                                                 // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.PawnSensingComponent.SetSensingInterval
struct UPawnSensingComponent_SetSensingInterval_Params
{
	float                                              NewSensingInterval;                                       // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.PawnSensingComponent.SetPeripheralVisionAngle
struct UPawnSensingComponent_SetPeripheralVisionAngle_Params
{
	float                                              NewPeripheralVisionAngle;                                 // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
};

// DelegateFunction AIModule.PawnSensingComponent.SeePawnDelegate__DelegateSignature
struct UPawnSensingComponent_SeePawnDelegate__DelegateSignature_Params
{
	class APawn*                                       Pawn;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
};

// DelegateFunction AIModule.PawnSensingComponent.HearNoiseDelegate__DelegateSignature
struct UPawnSensingComponent_HearNoiseDelegate__DelegateSignature_Params
{
	class APawn*                                       Instigator;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Location;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	float                                              Volume;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AIModule.PawnSensingComponent.GetPeripheralVisionCosine
struct UPawnSensingComponent_GetPeripheralVisionCosine_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AIModule.PawnSensingComponent.GetPeripheralVisionAngle
struct UPawnSensingComponent_GetPeripheralVisionAngle_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

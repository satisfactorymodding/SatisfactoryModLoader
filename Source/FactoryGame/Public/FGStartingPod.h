// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGDismantleInterface.h"
#include "FGActorRepresentationInterface.h"
#include "Engine/SkeletalMesh.h"
#include "FGStartingPod.generated.h"

class USkeletalMesh;
class ULevelSequencePlayer;
class ULevelSequence;
class UFGCameraModifierLimitFOV;
class UFGCameraModifierLimitLook;
class UFGOnboardingStep;
class ALevelSequenceActor;

/** Possible states of the intro sequence */
UENUM( BlueprintType )
enum class EIntroSequencePlayState
{
	/** Intro sequence is not started or has ended */
	None UMETA( DisplayName = "None" ),
	/** Intro sequence is actively playing now, the Drop Pod has been setup */
	SequencePlaying UMETA( DisplayName = "Sequence Playing" ),
	/** Intro sequence is still playing, but the drop pod has already been exited */
	SequencePlaying_DropPodExited UMETA( DisplayName = "Sequence Playing (Drop Pod Exited)" ),
	/** Intro sequence is still playing, drop pod is exited, the player can already look around and the intro is about to end */
	SequencePlaying_LookAround UMETA( DisplayName = "Sequence Playing (Look Around)" ),
	/** Intro sequence has been ended. */
	Finished UMETA( DisplayName = "Finished" )
};

UCLASS()
class FACTORYGAME_API AFGStartingPod : public AActor, public IFGDismantleInterface, public IFGActorRepresentationInterface, public IFGSaveInterface
{
	GENERATED_BODY()
public:	
	AFGStartingPod();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End AActor interface

	//~ Begin IFGDismantleInterface
	virtual FVector GetRefundSpawnLocationAndArea_Implementation( const FVector& aimHitLocation, float& out_radius ) const override;
	virtual bool CanDismantle_Implementation() const override;
	virtual void GetDismantleRefund_Implementation( TArray< FInventoryStack >& out_refund, bool noBuildCostEnabled ) const override;
	virtual void PreUpgrade_Implementation() override;
	virtual void Upgrade_Implementation( AActor* newActor ) override;
	virtual void Dismantle_Implementation() override;
	virtual void StartIsLookedAtForDismantle_Implementation(class AFGCharacterPlayer* byCharacter ) override;
	virtual void StopIsLookedAtForDismantle_Implementation( class AFGCharacterPlayer* byCharacter ) override;
	virtual void GetChildDismantleActors_Implementation( TArray< AActor* >& out_ChildDismantleActors ) const override;
	virtual FText GetDismantleDisplayName_Implementation(AFGCharacterPlayer* byCharacter) const override;
	//~ End IFGDismantleInterface

	// Begin IFGActorRepresentationInterface
	UFUNCTION() virtual bool AddAsRepresentation() override;
	UFUNCTION() virtual bool UpdateRepresentation() override;
	UFUNCTION() virtual bool RemoveAsRepresentation() override;
	UFUNCTION() virtual bool IsActorStatic() override;
	UFUNCTION() virtual FVector GetRealActorLocation() override;
	UFUNCTION() virtual FRotator GetRealActorRotation() override;
	UFUNCTION() virtual class UTexture2D* GetActorRepresentationTexture() override;
	UFUNCTION() virtual FText GetActorRepresentationText() override;
	UFUNCTION() virtual void SetActorRepresentationText( const FText& newText ) override;
	UFUNCTION() virtual FLinearColor GetActorRepresentationColor() override;
	UFUNCTION() virtual void SetActorRepresentationColor( FLinearColor newColor ) override;
	UFUNCTION() virtual ERepresentationType GetActorRepresentationType() override;
	UFUNCTION() virtual bool GetActorShouldShowInCompass() override;
	UFUNCTION() virtual bool GetActorShouldShowOnMap() override;
	UFUNCTION() virtual EFogOfWarRevealType GetActorFogOfWarRevealType() override;
	UFUNCTION() virtual float GetActorFogOfWarRevealRadius() override;
	UFUNCTION() virtual ECompassViewDistance GetActorCompassViewDistance() override;
	UFUNCTION() virtual void SetActorCompassViewDistance( ECompassViewDistance compassViewDistance ) override;
	UFUNCTION() virtual UMaterialInterface* GetActorRepresentationCompassMaterial() override;
	// End IFGActorRepresentationInterface

	// Begin IFGSaveInterface
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFGSaveInterface

	/** Returns the player that owns this drop pod. This will not be persisted across the session restarts. */
	UFUNCTION( BlueprintPure, Category = "Starting Pod" )
	AFGCharacterPlayer* GetOwnerPlayer() const;

	/** Call during the active intro sequence to skip the remaining part of it. Should only be called either on the server or on the local player's side! */
	UFUNCTION( BlueprintCallable, Category = "Starting Pod" )
	void RequestSkipIntroSequence();

	/** Requests the player we are currently playing the animation for to exit the drop pod (locally) */
	UFUNCTION( BlueprintCallable, Category = "Starting Pod" )
	void RequestDropPodExit();

	/** Called to notify the tutorial manager that we are now allowed (or forbidden) to skip the onboarding */
	UFUNCTION( BlueprintCallable, Category = "Starting Pod" )
	void AllowSkippingOnboarding( bool bAllowSkippingOnboarding );

	/** Called to allow the player to look around, be affected by gravity and start fading the FOV back. Called shortly before the intro sequence is done. */
	UFUNCTION( BlueprintCallable, Category = "Starting Pod" )
	void RequestAllowLookAround();

	/** Returns true if the intro sequence is currently active on this drop pod */
	UFUNCTION( BlueprintPure, Category = "Starting Pod" )
	bool IsIntroSequencePlaying() const;

	/** Internal accessor to the level sequence actor. Only to be used by cheat manager */
	FORCEINLINE ALevelSequenceActor* Internal_GetLevelSequenceActor() const { return mLevelSequenceActor; }
protected:
	/** Called when the drop pod should be initialized on the given side. It will only be called when the owner player is valid. Will be called both on authority and on the clients */
	UFUNCTION( BlueprintNativeEvent, Category = "Starting Pod" )
	void Local_SetupIntroSequence();

	/** Called when the player exits the drop pod because the cinematic approaches the end. Also called when skipping the intro sequence. Always called before EndIntroSequence */
	UFUNCTION( BlueprintNativeEvent, Category = "Starting Pod" )
	void Local_ExitDropPod();

	/** Called when the player is allowed to be affected by the gravity and look around. Called right at the end of the intro sequence. */
	UFUNCTION( BlueprintNativeEvent, Category = "Starting Pod" )
	void Local_AllowLookAround();

	/** Called locally when the intro sequence is ending, regardless of whenever it was skipped or finished naturally */
	UFUNCTION( BlueprintNativeEvent, Category = "Starting Pod" )
	void Local_EndIntroSequence();

	/** Called when the player wishes to skip the intro sequence and immediately finish the landing animation. Called on both the authority and all the clients. */
	UFUNCTION( BlueprintNativeEvent, Category = "Starting Pod" )
	void Local_SkipIntroSequence();

	/** Called locally after the player has skipped intro sequence */
	UFUNCTION( BlueprintNativeEvent, Category = "Starting Pod" )
	void Local_PostSkipIntroSequence( AFGCharacterPlayer* CharacterPlayer );

	/**
	 * Binds level sequence actor to actors/objects that it needs to be able to possess/control
	 * This is called early into the drop pod sequence, right before it is started.
	 * Drop pod intro sequence will be played directly after the binding is done. If you need to change the bindings later,
	 * you can hook into one of the native events, such as Local_ExitDropPod/Local_AllowLookAround/Local_EndIntroSequence/Local_SkipIntroSequence
	 */
	UFUNCTION( BlueprintImplementableEvent, Category = "Starting Pod" )
	void Local_BindIntroLevelSequence( ALevelSequenceActor* LevelSequenceActor );
private:
	/** Asks the server to stop playing the intro sequence */
	UFUNCTION( Server, Reliable, Category = "Starting Pod" )
	void Server_RequestSkipIntroSequence();
	
	/** Called to broadcast that we are willing to skip into sequence to everyone */
	UFUNCTION( NetMulticast, Reliable )
	void Multicast_SkipIntroSequence();

	/** Called when the owner has been updated by the server */
	virtual void OnRep_Owner() override;

	/** Called to begin playing the intro sequence locally */
	void RequestSetupIntroSequence();
	/** Forcefully stops the intro sequence locally, optionally stopping the player */
	void StopIntroSequence( bool bStopSequencer );
	/** Called to locally skip the intro sequence */
	void Local_RequestSkipIntroSequence();

	/** Called when the intro sequence has ended from the sequencer */
	UFUNCTION()
	void OnIntroSequenceEnded();
protected:
	/** Camera FOV that the player camera should be forced to during the intro sequence */
	UPROPERTY( EditDefaultsOnly, Category = "Intro Sequence" )
	float mIntroSequencePlayerCameraFOV;

	/** Relative location to the drop pod to attach the player to */
	UPROPERTY( EditDefaultsOnly, Category = "Intro Sequence" )
	FVector mDropPodAttachmentRelativeLocation;

	/** Name of the socket on the drop pod to attach the player character to */
	UPROPERTY( EditDefaultsOnly, Category = "Intro Sequence" )
	TSoftObjectPtr<ULevelSequence> mIntroLevelSequence;

	/** Look rotator for the camera lock during the animation */
	UPROPERTY( EditDefaultsOnly, Category = "Intro Sequence" )
	FRotator mCameraLockLookRotator;

	/** Onboarding step to complete when we are done with the intro sequence */
	UPROPERTY( EditDefaultsOnly, Category = "Intro Sequence" )
	UFGOnboardingStep* mPlanetFallOnboardingStep;

	/** Distance to teleport the player forward after skipping the intro sequence */
	UPROPERTY( EditDefaultsOnly, Category = "Intro Sequence" )
	float mSkipIntroForwardDistance;

	/** Class to use for the limit look camera modifier */
	UPROPERTY( EditDefaultsOnly, Category = "Intro Sequence" )
	TSubclassOf<UFGCameraModifierLimitLook> mLimitLookModifierClass;

	/** Class to use for the limit FOV camera modifier */
	UPROPERTY( EditDefaultsOnly, Category = "Intro Sequence" )
	TSubclassOf<UFGCameraModifierLimitFOV> mLimitFOVModifierClass;

	/** Display name of the starting pod, as visible when dismantling it */
	UPROPERTY( EditDefaultsOnly, Category = "Dismantle" )
	FText mDisplayName;

	/** Representation texture to use for the drop pod */
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	UTexture2D* mActorRepresentationTexture;

	/** Representation color to use for the drop pod */
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	FLinearColor mActorRepresentationColor;
	
	/** Array containing how much to get back when dismantling this bad boy */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Dismantle")
	TArray<FInventoryStack> mDismantleStacks;

	/** Main mesh component of the drop pod */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Starting Pod" )
	USkeletalMeshComponent* mDropPodMeshComponent;

	/** Mesh to lazily load for the drop pod */
	UPROPERTY( EditDefaultsOnly, Category = "Starting Pod" )
	TSoftObjectPtr<USkeletalMesh> mDropModSkeletalMesh;

	/** Flag for whether the actor is being dismantled */
	uint8 mIsDismantled : 1;

	/** Local state of the intro sequence */
	UPROPERTY( Transient )
	EIntroSequencePlayState mLocalIntroSequenceState;

	/** Camera modifier that is used to limit the FOV for the duration of the intro sequence */
	UPROPERTY( Transient )
	UFGCameraModifierLimitFOV* mCameraModifierLimitFOV;

	/** Camera modifier for limiting the look of the player */
	UPROPERTY( Transient )
	UFGCameraModifierLimitLook* mCameraModifierLimitLook;

	/** Level sequence player for the intro level sequence */
	UPROPERTY( Transient, BlueprintReadOnly, Category = "Starting Pod" )
	ALevelSequenceActor* mLevelSequenceActor;

	/** Cached previous owner, when the server wants to immediately end the level sequence */
	UPROPERTY( Transient )
	AActor* mPreviousOwner;

	/** Spawn location of the drop pod as reported by the server before the intro sequence started playing. We do not replicate movement so we need to replicate it separately. */
	UPROPERTY( Replicated )
	FVector mDropPodSpawnLocation;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* mCompassMaterialInstance;
};

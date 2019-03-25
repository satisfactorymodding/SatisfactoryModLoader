/*
 * PDB file: FactoryGame-Win64-Shipping.pdb
 * Image architecture: AMD64 (0x8664)
 *
 * Dumped by pdbex tool v0.11, by wbenny
 */
#include "stdafx.h"
#include <pshpack1.h>
#include <Windows.h>

template<void* A, AFGCharacterPlayer* B, AFGCharacterPlayer* C>
class TMulticastDelegate/*<void, AFGCharacterPlayer *, AFGEquipment *>*/ (A, B, C)
{
}; /* size: 0x0018 */

class TMulticastDelegate<void, AFGCharacterPlayer *, AFGEquipment *, AFGEquipmentAttachment *>
{
}; /* size: 0x0018 */

class TMulticastDelegate<void, AFGCharacterPlayer *, AFGFoliagePickup *>
{
}; /* size: 0x0018 */

class TSubclassOf<UAnimInstance>
{
	/* 0x0000 */ class UClass* Class;
}; /* size: 0x0008 */

class TSubclassOf<AFGFoliagePickup>
{
	/* 0x0000 */ class UClass* Class;
}; /* size: 0x0008 */

struct FVector
{
	union
	{
		struct
		{
			/* 0x0000 */ float X;
			/* 0x0004 */ float Y;
			/* 0x0008 */ float Z;
		}; /* size: 0x000c */
		/* 0x0000 */ const struct FVector ZeroVector;
		/* 0x0000 */ const struct FVector OneVector;
		/* 0x0000 */ const struct FVector UpVector;
		/* 0x0000 */ const struct FVector ForwardVector;
		/* 0x0000 */ const struct FVector RightVector;
	}; /* size: 0x000c */
}; /* size: 0x000c */

class TSubclassOf<UFGUseState>
{
	/* 0x0000 */ class UClass* Class;
}; /* size: 0x0008 */

struct FUseState
{
	/* 0x0000 */ class UFGUseState* AdditionalData;
	/* 0x0008 */ struct FVector UseLocation;
	/* 0x0014 */ long Padding_0;
	/* 0x0018 */ class UPrimitiveComponent* UseComponent;
	/* 0x0020 */ class TSubclassOf<UFGUseState> State;
}; /* size: 0x0028 */

class FHeapAllocator::ForAnyElementType
{
	/* 0x0000 */ struct FScriptContainerElement* Data;
}; /* size: 0x0008 */

class TArray<FItemAmount, FDefaultAllocator>
{
	/* 0x0000 */ class FHeapAllocator::ForAnyElementType AllocatorInstance;
	/* 0x0008 */ int ArrayNum;
	/* 0x000c */ int ArrayMax;
}; /* size: 0x0010 */

class TSubclassOf<UFGDamageType>
{
	/* 0x0000 */ class UClass* Class;
}; /* size: 0x0008 */

struct FFootstepEffect
{
	/* 0x0000 */ class UParticleSystem* Particle;
	/* 0x0008 */ class UMaterialInterface* GroundDecal;
}; /* size: 0x0010 */

class TArray<FFootstepEffectSurface, FDefaultAllocator>
{
	/* 0x0000 */ class FHeapAllocator::ForAnyElementType AllocatorInstance;
	/* 0x0008 */ int ArrayNum;
	/* 0x000c */ int ArrayMax;
}; /* size: 0x0010 */

class TArray<UAkAudioEvent *, FDefaultAllocator>
{
	/* 0x0000 */ class FHeapAllocator::ForAnyElementType AllocatorInstance;
	/* 0x0008 */ int ArrayNum;
	/* 0x000c */ int ArrayMax;
}; /* size: 0x0010 */

class TArray<AFGEquipment *, FDefaultAllocator>
{
	/* 0x0000 */ class FHeapAllocator::ForAnyElementType AllocatorInstance;
	/* 0x0008 */ int ArrayNum;
	/* 0x000c */ int ArrayMax;
}; /* size: 0x0010 */

class TArray<AFGEquipmentAttachment *, FDefaultAllocator>
{
	/* 0x0000 */ class FHeapAllocator::ForAnyElementType AllocatorInstance;
	/* 0x0008 */ int ArrayNum;
	/* 0x000c */ int ArrayMax;
}; /* size: 0x0010 */

enum ECameraMode
{
	ECM_None = 0,
	ECM_FirstPerson = 1,
	ECM_ThirdPerson = 2,
};

struct FTimerHandle
{
	/* 0x0000 */ unsigned __int64 Handle;
}; /* size: 0x0008 */

class TSubclassOf<UCameraShake>
{
	/* 0x0000 */ class UClass* Class;
}; /* size: 0x0008 */

class AFGCharacterPlayer
{
	union
	{
		/* 0x0000 */ class TMulticastDelegate<void, AFGCharacterPlayer *, AFGEquipment *> OnPersistentEquipmentSpawned;
		/* 0x0000 */ class TMulticastDelegate<void, AFGCharacterPlayer *, AFGEquipment *, AFGEquipmentAttachment *> OnEquipmentEquipped;
		/* 0x0000 */ class TMulticastDelegate<void, AFGCharacterPlayer *, AFGEquipment *, AFGEquipmentAttachment *> OnEquipmentUnequipped;
		struct
		{
			/* 0x0000 */ class TMulticastDelegate<void, AFGCharacterPlayer *, AFGFoliagePickup *> OnFoliagePickupSpawned;
			/* 0x0018 */ long Padding_1[556];
			/* 0x08c8 */ float mBaseTurnRate;
			/* 0x08cc */ float mBaseLookUpRate;
			/* 0x08d0 */ class USkeletalMeshComponent* mMesh3P;
			/* 0x08d8 */ class TSubclassOf<UAnimInstance> mMesh1PAnimClass;
			/* 0x08e0 */ class TSubclassOf<AFGFoliagePickup> mFoliagePickupProxyClass;
			/* 0x08e8 */ class AFGFoliagePickup* mFoliagePickupProxy;
			/* 0x08f0 */ class AFGBuildGun* mBuildGun;
			/* 0x08f8 */ class AFGResourceScanner* mResourceScanner;
			/* 0x0900 */ class AFGResourceMiner* mResourceMiner;
			/* 0x0908 */ class AActor* mBestUsableActor;
			/* 0x0910 */ struct FUseState mCachedUseState;
			/* 0x0938 */ class TSubclassOf<UAnimInstance> mAnimInstanceClass;
			/* 0x0940 */ class TSubclassOf<UAnimInstance> mAnimInstanceClass1P;
			/* 0x0948 */ float mReviveDuration;
			/* 0x094c */ long Padding_2;
			/* 0x0950 */ class TArray<FItemAmount, FDefaultAllocator> mStartingResources;
			/* 0x0960 */ class TArray<FItemAmount, FDefaultAllocator> mStartingResourceForTesting;
			/* 0x0970 */ class TSubclassOf<UFGDamageType> mDrownDamageDamageType;
			/* 0x0978 */ float mDrownDamage;
			/* 0x097c */ float mDrownDamageInterval;
			/* 0x0980 */ class AFGCharacterPlayer* mPlayerToRevive;
			/* 0x0988 */ class AFGItemPickup* mPickupToCollect;
			/* 0x0990 */ struct FFootstepEffect m1PDefaultFootstepEffect;
			/* 0x09a0 */ class TArray<FFootstepEffectSurface, FDefaultAllocator> m1PFootstepEffect;
			/* 0x09b0 */ class TArray<UAkAudioEvent *, FDefaultAllocator> m1PFootstepEvent;
			/* 0x09c0 */ float mLastSafeGroundCheckTimer;
		}; /* size: 0x0110 */
		/* 0x0000 */ const int MAX_SAFE_GROUND_POS_BUFFER_SIZE;
	}; /* size: 0x0110 */
	/* 0x0110 */ long Padding_3[557];
	/* 0x09c4 */ struct FVector mLastSafeGroundPositions[3];
	/* 0x09e8 */ int mLastSafeGroundPositionLoopHead;
	/* 0x09ec */ long Padding_4;
	/* 0x09f0 */ class UCameraComponent* mCameraComponent;
	/* 0x09f8 */ class USpringArmComponent* mSpringArmComponent;
	/* 0x0a00 */ class TArray<AFGEquipment *, FDefaultAllocator> mActiveEquipments;
	/* 0x0a10 */ class TArray<AFGEquipment *, FDefaultAllocator> mClientActiveEquipments;
	/* 0x0a20 */ class TArray<AFGEquipmentAttachment *, FDefaultAllocator> mAllAttachments;
	/* 0x0a30 */ class TArray<AFGEquipmentAttachment *, FDefaultAllocator> mActiveAttachments;
	/* 0x0a40 */ enum ECameraMode mCurrentCameraMode;
	/* 0x0a41 */ enum ECameraMode mPlayerPreferredCameraMode;
	/* 0x0a42 */ char Padding_5[6];
	/* 0x0a48 */ class UFGInventoryComponent* mInventory;
	/* 0x0a50 */ class UFGInventoryComponent* mTrashSlot;
	/* 0x0a58 */ BOOL mAllowCameraToggling;
	/* 0x0a59 */ char Padding_6[3];
	/* 0x0a5c */ float mUseDistance;
	/* 0x0a60 */ float mTimeToApplyDrownDamage;
	/* 0x0a64 */ char mPickupCounter;
	/* 0x0a65 */ char Padding_7[3];
	/* 0x0a68 */ class AFGCharacterPlayer* mReviver;
	/* 0x0a70 */ struct FTimerHandle mReviveTimerHandle;
	/* 0x0a78 */ float mMaxDPSFromRadiation;
	/* 0x0a7c */ long Padding_8;
	/* 0x0a80 */ struct FTimerHandle mRadiationTimerHandle;
	/* 0x0a88 */ BOOL mWantsSprintBobbing;
	/* 0x0a89 */ char Padding_9[7];
	/* 0x0a90 */ class TSubclassOf<UCameraShake> mCurrentHeadBobShake;
	/* 0x0a98 */ class TSubclassOf<UCameraShake> mDefaultWalkHeadBobShake;
	/* 0x0aa0 */ class TSubclassOf<UCameraShake> mDefaultSprintHeadBobShake;
	/* 0x0aa8 */ class AFGDriveablePawn* mDrivenVehicle;
	/* 0x0ab0 */ class AFGDriveablePawn* mSavedDrivenVehicle;
	/* 0x0ab8 */ class UFGOutlineComponent* mOutlineComponent;
	/* 0x0ac0 */ float mHealthGenerationThreshold;
	/* 0x0ac4 */ float mHealthGenerationAmount;
	/* 0x0ac8 */ float mHealthGenerationInterval;
	/* 0x0acc */ float mHealthGenerationWaitTime;
	/* 0x0ad0 */ float mHealthGenerationTimer;
	/* 0x0ad4 */ float mLastDamageTakenTime;
}; /* size: 0x0ae0 */

#include <poppack.h>
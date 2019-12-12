#pragma once
#include "UObject/Class.h"

#include "GameFramework/DamageType.h"
#include "FGDamageType.generated.h"

UENUM(BlueprintType)
enum EOverrideSetting
{
	OS_Additive	UMETA( DisplayName = "Additive" ),
	OS_Override	UMETA( DisplayName = "Override" )
};

UENUM(BlueprintType)
enum EPlayOnDamageEvent
{
	PODE_OnTakeAnyDamage UMETA(DisplayName="OnTakeAnyDamage"),
	PODE_OnTakePointDamage UMETA( DisplayName = "OnTakePointDamage" ),
	PODE_OnTakeRadialDamage UMETA( DisplayName = "OnTakeRadialDamage" )
};

UCLASS()
class UFGDamageType : public UDamageType
{
	GENERATED_BODY()
public:
	/** ctor */
	UFGDamageType( const FObjectInitializer& ObjectInitializer );

	/** When pawn take damage from a source, they play this take damage event */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "DamageType|Audio" )
	class UAkAudioEvent* mImpactAudioEvent;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "DamageType|Audio" )
	TEnumAsByte<EPlayOnDamageEvent> mPlayImpactAudioOn;

	/** Specify if the audio from this damage type should overrride the damage sound in hit pawn, or add to it */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "DamageType|Audio" )
	TEnumAsByte<EOverrideSetting> mImpactAudioSetting;

	/** When pawn take damage from a source, they play this take damage event */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "DamageType|Vfx" )
	class UParticleSystem* mImpactParticle;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "DamageType|Vfx" )
	TEnumAsByte<EPlayOnDamageEvent> mPlayImpactParticleOn;

	/** Specify if the audio from this damage type should overrride the damage effect in hit pawn, or add to it */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "DamageType|Vfx" )
	TEnumAsByte<EOverrideSetting> mImpactParticleSetting;

	/** Should this damage type hurt destrucrible actors? */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "DamageType" )
	bool mShouldDamageDestructible;

	/** How much extra impulse should be added in Z direction for this damage type */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "DamageType" )
	float mDamageImpulseZ;

	/** Should this damage type shock and scare the enemy, like the stun spear? */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "DamageType" )
	bool mShouldShockEnemy;
};
#pragma once
#include "CoreMinimal.h"
#include "FGItemDescriptor.h"
#include "FGPowerShardDescriptor.generated.h"

UENUM( BlueprintType )
enum class EPowerShardType : uint8
{
	PST_None UMETA(DisplayName = "None"),
	PST_Overclock UMETA(DisplayName = "Overclock"),
	PST_ProductionBoost UMETA(DisplayName = "Production Boost")
};

UCLASS( Abstract )
class FACTORYGAME_API UFGPowerShardDescriptor : public UFGItemDescriptor
{
	GENERATED_BODY()
public:
	UFGPowerShardDescriptor();

	UFUNCTION( BlueprintPure, Category = "Itme|Power Shard" )
	static EPowerShardType GetPowerShardType( TSubclassOf<UFGPowerShardDescriptor> inClass );

	UFUNCTION( BlueprintPure, Category = "Item|Power Shard" )
	static float GetBoostValue( TSubclassOf<UFGPowerShardDescriptor> inClass );
protected:
	UPROPERTY( EditDefaultsOnly, Category = "Item|Power Shard" )
	EPowerShardType mPowerShardType;

	/** Amount of potential to unlock for a power shard of this type */
	UPROPERTY( EditDefaultsOnly, Category = "Item|Power Shard", meta = (EditCondition = "mPowerShardType == EPowerShardType::PST_Overclock") )
	float mExtraPotential;

	/** Amount of production boost to unlock for a power shard of this type */
	UPROPERTY( EditDefaultsOnly, Category = "Item|Power Shard", meta = (EditCondition = "mPowerShardType == EPowerShardType::PST_ProductionBoost") )
	float mExtraProductionBoost;
};

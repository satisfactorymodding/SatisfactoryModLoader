// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGBuildableSubsystem.h"
#include "Engine/NetDriver.h"
#include "FGConstructionMessageInterface.generated.h"

/**
 * @todo Please comment me
 */
USTRUCT()
struct FConstructHologramMessage
{
	GENERATED_BODY()

	UPROPERTY()
	FNetConstructionID ConstructionID;

	UPROPERTY()
	TSubclassOf< class UFGRecipe > Recipe;

	UPROPERTY()
	AActor* UpgradeActor;

	UPROPERTY()
	TSubclassOf< AFGBuildable > LightweightUpgradeClass;

	UPROPERTY()
	int32 LightweightUpgradeRuntimeIndex;

	UPROPERTY()
	TArray<uint8> SerializedHologramData;

	UPROPERTY()
	int64 NumBits;

	FConstructHologramMessage() :
		Recipe( nullptr ),
		UpgradeActor(nullptr),
		LightweightUpgradeClass( nullptr ),
		LightweightUpgradeRuntimeIndex( INDEX_NONE ),
		SerializedHologramData(),
		NumBits( 0 )
	{}

	bool IsUpgradeConstructionMessage() const
	{
		return UpgradeActor != nullptr;
	}
};


UINTERFACE( NotBlueprintable )
class FACTORYGAME_API UFGConstructionMessageInterface : public UInterface
{
	GENERATED_BODY()
};

/** Implemented on holograms to support custom Client -> Server construction messages */
class FACTORYGAME_API IFGConstructionMessageInterface
{
	GENERATED_BODY()
public:
	virtual void PreConstructMessageSerialization() {};
	virtual void SerializeConstructMessage( FArchive& ar, FNetConstructionID id ) = 0;
	virtual void PostConstructMessageDeserialization() {};
};

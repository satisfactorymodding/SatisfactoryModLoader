#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Interface.h"
#include "SubclassOf.h"

#include "FGBuildableSubsystem.h"
#include "FGConstructionMessageInterface.generated.h"

USTRUCT()
struct FACTORYGAME_API FConstructHologramMessage
{
	GENERATED_BODY()

	UPROPERTY()
	FNetConstructionID ConstructionID;

	UPROPERTY()
	TSubclassOf< class UFGRecipe > Recipe;

	UPROPERTY()
	AActor* UpgradeActor;

	UPROPERTY()
	TArray<uint8> SerializedHologramData;

	UPROPERTY()
	int64 NumBits;

	FConstructHologramMessage() :
		Recipe( nullptr ),
		UpgradeActor(nullptr),
		SerializedHologramData(),
		NumBits( 0 )
	{}

	bool IsUpgradeConstructionMessage() const
	{
		return UpgradeActor != nullptr;
	}

public:
	FORCEINLINE ~FConstructHologramMessage() = default;
};

/**
*
*/
UINTERFACE(Blueprintable)
class FACTORYGAME_API UFGConstructionMessageInterface : public UInterface
{
	GENERATED_BODY()

public:
	FORCEINLINE ~UFGConstructionMessageInterface() = default;
};

/**
*
*/
class FACTORYGAME_API IFGConstructionMessageInterface
{
	GENERATED_BODY()

public:
	virtual void SerializeConstructMessage( FArchive& ar, FNetConstructionID id ) = 0;

	virtual void ClientPreConstructMessageSerialization() {};
	virtual void ClientPostConstructMessageSerialization() {};
	virtual void ServerPreConstructMessageDeserialization() {};
	virtual void ServerPostConstructMessageDeserialization() {};

	/** This is called on server when a hologram has been created from a construct message */
	UFUNCTION( BlueprintNativeEvent )
	void OnConstructMessagedDeserialized();

public:
	FORCEINLINE IFGConstructionMessageInterface() = default;
};

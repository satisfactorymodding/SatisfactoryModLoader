// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGFactoryBlueprintTypes.h"
#include "Components/ActorComponent.h"
#include "FGBlueprintSubsystemReplicationComponent.generated.h"

class AFGBlueprintSubsystem;

enum class EBlueprintSubsystemMessageId : uint32
{
	BlueprintFileDownload = 0x01,
};

struct FBlueprintSubsystemFileDownloadMessage
{
	static constexpr EBlueprintSubsystemMessageId MessageId = EBlueprintSubsystemMessageId::BlueprintFileDownload;
	FBlueprintRecord BlueprintRecord;
	TArray<uint8> FilePayload;
	
	friend FArchive& operator<<(FArchive& Ar, FBlueprintSubsystemFileDownloadMessage& Message);
};

UCLASS(NotBlueprintable, Within = PlayerController)
class FACTORYGAME_API UFGBlueprintSubsystemReplicationComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	// Begin UActorComponent interface
	virtual void BeginPlay() override;
	// End UActorComponent interface

	// Begin AFGBlueprintSubsystem interface
	bool SendBlueprintFileToPlayer(const FString& BlueprintName);
	// End AFGBlueprintSubsystem interface
protected:
	/** Called to initialize on the client once the blueprint subsystem is available */
	void InitializeAsClient();
	
	/** Handles a reliable message */
	void HandleRawMessage(TArray<uint8>&& InMessageData) const;
	/** Sends a a reliable message */
	void SendRawMessage(EBlueprintSubsystemMessageId MessageId, const TFunctionRef<void(FArchive&)>& MessageSerializer) const;

	/** Handles Blueprint File download from the server */
	void ReceiveBlueprintFileDownload(const FBlueprintSubsystemFileDownloadMessage& Message) const;
	
	/** Sends a schematic manager message to the player */
	template<typename T>
	void SendMessage(T& Message)
	{
		SendRawMessage(T::MessageId, [&](FArchive& Ar) { Ar << Message; });
	}

	UPROPERTY()
	AFGBlueprintSubsystem* mBlueprintSubsystem;
};

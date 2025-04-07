// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Serialization/ArchiveUObject.h"

class UPackageMap;
class APlayerController;

/**
 * Archive that will serialize objects as index of their soft object path after they appear once
 */
class FObjectAsReferenceIndexArchive : public FArchiveProxy
{
	bool bAttemptToLoadIfFindFails{false};
	TMap<UObject*, int32> ObjectToSerializedIndexLookup;
	TMap<int32, UObject*> IndexToDeserializedObjectLookup;
	int32 NextObjectIndex{1};
	UPackageMap* PackageMap{};
public:
	FObjectAsReferenceIndexArchive(FArchive& InParent, bool bInAttemptToLoadIfFindFails, UPackageMap* InPackageMap = nullptr);
	FObjectAsReferenceIndexArchive(FArchive& InParent, bool bInAttemptToLoadIfFindFails, const APlayerController* InPlayerController);

	// Begin FArchive Interface
	virtual FArchive& operator<<(UObject*& Value) override;
	virtual FArchive& operator<<(FLazyObjectPtr& Value) override { return FArchiveUObject::SerializeLazyObjectPtr(*this, Value); }
	virtual FArchive& operator<<(FObjectPtr& Value) override { return FArchiveUObject::SerializeObjectPtr(*this, Value); }
	virtual FArchive& operator<<(FSoftObjectPtr& Value) override { return FArchiveUObject::SerializeSoftObjectPtr(*this, Value); }
	virtual FArchive& operator<<(FSoftObjectPath& Value) override { return FArchiveUObject::SerializeSoftObjectPath(*this, Value); }
	virtual FArchive& operator<<(FWeakObjectPtr& Value) override { return FArchiveUObject::SerializeWeakObjectPtr(*this, Value); }
	// End FArchive Interface
};

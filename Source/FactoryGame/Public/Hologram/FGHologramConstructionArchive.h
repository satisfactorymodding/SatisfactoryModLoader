// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Serialization/ArchiveProxy.h"


class AFGHologram;

/** Proxy archive used to serialize object references relative to the root hologram */
class FFGHologramConstructionArchive : public FArchiveProxy
{
private:
	AFGHologram* mOwnerHologram;

public:
	FFGHologramConstructionArchive( AFGHologram* hologram, FArchive& inner );

	virtual FArchive& operator<<(UObject*& Value) override;
	virtual FArchive& operator<<(FObjectPtr& Value) override;
private:
	void HandleObjectReference( UObject*& object );
};

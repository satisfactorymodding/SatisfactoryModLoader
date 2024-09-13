// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Server/FGDSSharedTypes.h"
#include "FGServerAPIDataTypes.generated.h"

class FFGRequestHandlerContext;
class FFGRequestPayload;
class FFGRequestBodyPart;

// Wraps RequestHandlerContext so it can be passed to the handlers through the reflection system
USTRUCT( BlueprintType, meta = ( BlueprintInternalUseOnly = "true" ))
struct FACTORYDEDICATEDSERVER_API FFGRequestHandlerContextWrapper : public FFGImplicitRequestParameterBase
{
	GENERATED_BODY()

	TSharedPtr<FFGRequestHandlerContext> RequestHandlerContext;

	// Operators for conveniently de-referencing the context. Keep in mind that these will assert on nullptr context.
	FFGRequestHandlerContext* operator->() const;
	FFGRequestHandlerContext& operator*() const;
	operator FFGRequestHandlerContext*() const;
};

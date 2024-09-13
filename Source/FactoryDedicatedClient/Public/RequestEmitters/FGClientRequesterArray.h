// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FGClientRequesterArray.generated.h"

class UFGClientDebugRequester;
class UFGClientAuthenticationRequester;
class UFGClientSaveGameRequester;
class UFGClientStateRequester;
class UFGClientManagementRequester;

UCLASS()
class FACTORYDEDICATEDCLIENT_API UFGClientRequesterArray : public UObject
{
	GENERATED_BODY()
public:
	UFGClientRequesterArray();

	FORCEINLINE UFGClientStateRequester* GetStateRequester() const { return mStateRequester; }
	FORCEINLINE UFGClientManagementRequester* GetManagementRequester() const { return mManagementRequester; }
	FORCEINLINE UFGClientSaveGameRequester* GetSaveGameRequester() const { return mSaveGameRequester; }
	FORCEINLINE UFGClientAuthenticationRequester* GetAuthenticationRequester() const { return mAuthenticationRequester; }
	FORCEINLINE UFGClientDebugRequester* GetDebugRequester() const { return mDebugRequester; }
private:
	UPROPERTY()
	UFGClientStateRequester* mStateRequester;

	UPROPERTY()
	UFGClientManagementRequester* mManagementRequester;

	UPROPERTY()
	UFGClientSaveGameRequester* mSaveGameRequester;

	UPROPERTY()
	UFGClientAuthenticationRequester* mAuthenticationRequester;

	UPROPERTY()
	UFGClientDebugRequester* mDebugRequester;
};



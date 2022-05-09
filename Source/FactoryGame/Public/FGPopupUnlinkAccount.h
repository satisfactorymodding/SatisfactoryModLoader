// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGPopupWidgetContent.h"
#include "FGPopupUnlinkAccount.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGPopupUnlinkAccount : public UFGPopupWidgetContent
{
	GENERATED_BODY()

protected:
	UFUNCTION( BlueprintCallable, Category=Online )
	void UnlinkAccount();

	UFUNCTION( BlueprintCallable, Category=Online )
	void LinkAccount();

	UFUNCTION()
	void NativeUnlinkComplete( bool result );

	UFUNCTION( BlueprintImplementableEvent, Category=Online )
	void OnUnlinkComplete( bool result );

	UFUNCTION( BlueprintImplementableEvent, Category=Online )
	void OnWaitForResult();

	UPROPERTY( BlueprintReadOnly, Category=Online )
	bool mUnlinkResult;

	UPROPERTY( BlueprintReadOnly, Category=Online )
	FName mSubsystemToUnlink;
	
};

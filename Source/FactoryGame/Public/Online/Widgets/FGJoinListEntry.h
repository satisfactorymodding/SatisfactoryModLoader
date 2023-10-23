// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "FGJoinListEntry.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGJoinListEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:

	void PresenceUpdated(const class UOnlineFriend* friendObject);

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnEntryReleased() override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;

	virtual bool IsListItemSelectable() const override;

	UFUNCTION(BlueprintImplementableEvent)
	void Update(const class UOnlineFriend* friendObject);

	UFUNCTION(BlueprintImplementableEvent)
	void SelectionStateUpdate(bool selectionState);
};

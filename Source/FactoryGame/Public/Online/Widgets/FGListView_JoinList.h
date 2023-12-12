// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UI/FGListView.h"
#include "FGListView_JoinList.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGListView_JoinList : public UFGListView
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category=FriendList)
	void Populate();
protected:
	virtual void BeginDestroy() override;

	UPROPERTY(BlueprintReadOnly)
	class UOnlineFriendList* mFriendList = nullptr;

private:

	FDelegateHandle mFriendListSortedDelegateHandle;
};

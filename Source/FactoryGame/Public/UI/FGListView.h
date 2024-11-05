// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Components/ListView.h"
#include "CoreMinimal.h"
#include "Widgets/Views/SListView.h"
#include "FGListView.generated.h"


/**
 * Created so we can exposes hidden properties that isn't exposed for Epics UListView.
 * For example the scrollbar style 
 */
UCLASS()
class FACTORYGAME_API UFGListView : public UListView
{
	GENERATED_BODY()

public:
	UFGListView(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style", meta=( DisplayName="Bar Style" ))
	FScrollBarStyle mWidgetBarStyle;

	UFUNCTION( BlueprintCallable, Category=Default )
	UUserWidget* GetEntryWidgetForItem( UObject* item ) const;
	
	virtual TSharedRef<STableViewBase> RebuildListWidget() override;
};

template < typename ItemType >
class FACTORYGAME_API SFGListView : public SListView< ItemType >
{
public:
	void SetBarStyle( const FScrollBarStyle& inBarStyle );

private:
	FScrollBarStyle mWidgetBarStyle;
};

template<typename ItemType>
void SFGListView<ItemType>::SetBarStyle( const FScrollBarStyle& inBarStyle )
{
	mWidgetBarStyle = inBarStyle;
	if( this->ScrollBar )
	{
		this->ScrollBar->SetStyle( &mWidgetBarStyle );
	}
}


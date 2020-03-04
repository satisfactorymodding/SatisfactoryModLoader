// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"
#include "Layout/Margin.h"
#include "Components/SlateWrapperTypes.h"
#include "Components/PanelSlot.h"
#include "Widgets/SBoxPanel.h"

#include "FGListViewSlot.generated.h"

/** The Slot for the UFGListView, contains the widget that is laid out in the list. */
UCLASS()
class FACTORYGAME_API UFGListViewSlot : public UPanelSlot
{
	// MODDING EDIT
	GENERATED_BODY()
	UFGListViewSlot(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
public:
	// UVisual interface
	virtual void ReleaseSlateResources( bool bReleaseChildren ) override;
	// End of UVisual interface

	/** Builds the underlying FSlot for the Slate layout panel. */
	void BuildSlot( TSharedRef< SVerticalBox > verticalBox );

private:
	//@todo Copied TODO from engine, see VerticalBoxSlot.h.
	//TODO UMG Slots should hold weak or shared refs to slots.

	/** A raw pointer to the slot to allow us to adjust the size, padding...etc at runtime. */
	SVerticalBox::FSlot* mSlot;

public:
	FORCEINLINE ~UFGListViewSlot() = default;
};

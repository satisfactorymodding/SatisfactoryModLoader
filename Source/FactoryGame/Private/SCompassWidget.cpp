// This file has been automatically generated by the Unreal Header Implementation tool

#include "SCompassWidget.h"
#include "FGHUD.h"

#if WITH_EDITORONLY_DATA
#endif 
UFGCompassWidget::UFGCompassWidget() : Super() {
	this->CompassAnchorPoint.X = 0.5;
	this->CompassAnchorPoint.Y = 0.5;
	this->CompassWidth = 800.0;
	this->FontInfo.FontObject = nullptr;
	this->FontInfo.FontMaterial = nullptr;
	this->FontInfo.OutlineSettings.bSeparateFillAlpha = false;
	this->FontInfo.OutlineSettings.bApplyOutlineToDropShadows = false;
	this->FontInfo.OutlineSettings.OutlineMaterial = nullptr;
	this->FontInfo.OutlineSettings.OutlineColor = FLinearColor(0.0, 0.0, 0.0, 1.0);
	this->FontInfo.TypefaceFontName = TEXT("None");
	this->FontInfo.Size = 24.0;
	this->FontInfo.SkewAmount = 0.0;
}
TSharedRef<SWidget> UFGCompassWidget::RebuildWidget(){ return Super::RebuildWidget(); }
TArray<FCompassEntry>& UFGCompassWidget::GetCompassEntries(){ return *(new TArray<FCompassEntry>); }
bool UFGCompassWidget::ShouldHideCompass() const{ return bool(); }
AFGHUD* UFGCompassWidget::GetOwningHUD() const{ return nullptr; }
void SCompassWidget::Construct(const FArguments& InArgs, const TWeakObjectPtr<UFGCompassWidget>& OwnerCompassWidget){ }
int32 SCompassWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const{ return int32(); }
FVector2D SCompassWidget::ComputeDesiredSize(float LayoutScaleMultiplier) const{ return FVector2D(); }
FChildren* SCompassWidget::GetChildren(){ return nullptr; }
void SCompassWidget::OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const{ }
void SCompassWidget::DrawEntry(const FVector2f& RootLocation, const FCompassEntry& Entry, const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32& LayerId){ }
void SCompassWidget::DrawEntrySpecialEffect(const FVector2f& RootLocation, const FCompassEntry& Entry, const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32& LayerId){ }
FVector3f SCompassWidget::CalculateBlurParametersFromStrength(float blurStrength){ return FVector3f(); }
void SCompassWidget::UpdateEntryTextRenderData(FCompassEntry& Entry, const FSlateFontInfo& FontInfo){ }

#pragma once
#include "Slate.h"

class SAssetDumperWidget : public SCompoundWidget {
public:
	SLATE_BEGIN_ARGS(SAssetDumperWidget) {}
	SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);
protected:
	//Determines whenever assets of the provided type should be serialized
	TMap<FName, bool> AssetClassSerializationRules;

	TSharedRef<SHorizontalBox> CreateAssetTypesBox();
};
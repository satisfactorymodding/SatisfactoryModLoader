#pragma once

#include "ModMetadataObject.h"
#include "Slate.h"
#include "Interfaces/IPluginManager.h"

class SAlpakitEditModDialog : public SWindow
{
public:
	SLATE_BEGIN_ARGS(SAlpakitEditModDialog) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, TSharedRef<IPlugin> InMod);

private:
	TSharedPtr<IPlugin> Mod;
	UModMetadataObject* MetadataObject = nullptr;
	
	FReply OnOkClicked();
};

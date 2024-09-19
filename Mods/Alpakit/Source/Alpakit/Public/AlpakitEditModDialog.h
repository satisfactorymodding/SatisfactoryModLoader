#pragma once

#include "ModMetadataObject.h"
#include "Interfaces/IPluginManager.h"
#include "Util/SemVersion.h"

class SAlpakitEditModDialog : public SWindow
{
public:
	SLATE_BEGIN_ARGS(SAlpakitEditModDialog) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, TSharedRef<IPlugin> InMod);

	FString GetSMLDependencyVersion() const;
	void SetSMLDependencyVersion(FString Version) const;
	void UpdateGameVersionTarget();

	static FString FormatGameVersionRange(const FVersionRange& Range);

private:
	TSharedPtr<IPlugin> Mod;
	UModMetadataObject* MetadataObject = nullptr;
	FVersion GameVersion;
	FVersionRange ModGameVersionRange;
	FVersionRange TargetGameVersionRange;
	
	FReply OnOkClicked();
};

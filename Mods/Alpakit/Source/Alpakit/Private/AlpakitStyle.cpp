#include "AlpakitStyle.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"
#include "Styling/SlateStyleRegistry.h"

static FName StyleSetName(TEXT("AlpakitStyle"));
TSharedPtr< FSlateStyleSet > FAlpakitStyle::StyleInstance = NULL;

void FAlpakitStyle::Initialize() {
    if (!StyleInstance.IsValid()) {
        StyleInstance = Create();
        FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
    }
}

void FAlpakitStyle::Shutdown() {
    FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
    ensure(StyleInstance.IsUnique());
    StyleInstance.Reset();
}

FName FAlpakitStyle::GetStyleSetName() {
    return StyleSetName;
}

const FVector2D Icon8x8(8.0f, 8.0f);
const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon32x32(32.0f, 32.0f);
const FVector2D Icon40x40(40.0f, 40.0f);
const FVector2D Icon128x128(40.0f, 40.0f);

bool ShouldUseHatIcon() {
    const FDateTime DateTime = FDateTime::Now();
    return (DateTime.GetMonthOfYear() == EMonthOfYear::December && DateTime.GetDay() >= 15) ||
        (DateTime.GetMonthOfYear() == EMonthOfYear::January && DateTime.GetDay() <= 15);
}

#define RootToContentDir Style->RootToContentDir

TSharedRef<FSlateStyleSet> FAlpakitStyle::Create() {
    TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet(StyleSetName));

	Style->SetContentRoot(IPluginManager::Get().FindPlugin(TEXT("Alpakit"))->GetBaseDir() / TEXT("Resources"));

	const FString IconName = ShouldUseHatIcon() ? TEXT("AlpakitHat") : TEXT("Alpakit");
    const FString DevIcon = IconName + TEXT("128");
    const FString ReleaseIcon = IconName + TEXT("Release128");
    Style->Set(TEXT("Alpakit.Icon"), new IMAGE_BRUSH(DevIcon, Icon128x128));
    Style->Set(TEXT("Alpakit.AlpakitDevWindow"), new IMAGE_BRUSH(DevIcon, Icon128x128));
	Style->Set(TEXT("Alpakit.AlpakitReleaseWindow"), new IMAGE_BRUSH(ReleaseIcon, Icon128x128));
	Style->Set(TEXT("Alpakit.AlpakitLogWindow"), new IMAGE_BRUSH(TEXT("AlpakitLog128"), Icon128x128));

	Style->SetContentRoot(FPaths::EngineContentDir() / TEXT("Editor/Slate"));
	Style->SetCoreContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));

    Style->Set("Alpakit.Warning", new IMAGE_BRUSH("Icons/alert", Icon16x16) );
	Style->Set("Alpakit.FolderOpen", new IMAGE_BRUSH("Icons/icon_file_ProjectOpen_16x", Icon16x16));
    return Style;
}

#undef RootToContentDir

void FAlpakitStyle::ReloadTextures() {
    if (FSlateApplication::IsInitialized()) {
        FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
    }
}

const ISlateStyle& FAlpakitStyle::Get() {
    return *StyleInstance;
}

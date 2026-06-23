#include "AlpakitModEntry.h"
#include "Alpakit.h"
#include "AlpakitInstance.h"
#include "AlpakitEditModDialog.h"
#include "AlpakitSettings.h"
#include "AlpakitStyle.h"
#include "ModTargetsConfig.h"
#include "ISourceControlModule.h"
#include "ISourceControlProvider.h"
#include "ISourceControlOperation.h"
#include "ModMetadataObject.h"
#include "SourceControlOperations.h"
#include "Async/Async.h"
#include "Framework/Notifications/NotificationManager.h"
#include "ILauncherProfile.h"
#include "ILauncherServicesModule.h"
#include "ITargetDeviceServicesModule.h"
#include "IUATHelperModule.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "AlpakitModListEntry"

void SAlpakitModEntry::Construct(const FArguments& Args, TSharedRef<IPlugin> InMod, TSharedRef<SAlpakitModEntryList> InOwner) {
    ChildSlot[
        SNew(SHorizontalBox)
        + SHorizontalBox::Slot().AutoWidth() [ Args._Lead.Widget ]
        + SHorizontalBox::Slot().FillWidth(1).VAlign(VAlign_Center)[
            SNew(STextBlock)
            .Text_Lambda([InMod] {
                const FString DisplayText = FString::Printf(TEXT("%s (%s)"), *InMod->GetDescriptor().FriendlyName, *InMod->GetName());
                return FText::FromString(DisplayText);
            })
            .HighlightText_Lambda([InOwner] {
                return FText::FromString(InOwner->GetLastFilter());
            })
        ]
        + SHorizontalBox::Slot().AutoWidth() [ Args._Trail.Widget ]
    ];
}

#undef LOCTEXT_NAMESPACE

#include "AlpakitCommands.h"
#include "AlpakitStyle.h"

#define LOCTEXT_NAMESPACE "FAlpakitModule"

FAlpakitCommands::FAlpakitCommands() : TCommands<FAlpakitCommands>(
    TEXT("Alpakit"),
    NSLOCTEXT("Contexts", "Alpakit", "Alpakit Plugin"),
    NAME_None,
    FAlpakitStyle::GetStyleSetName()) {}

void FAlpakitCommands::RegisterCommands() {
    UI_COMMAND(AlpakitDevWindow, "Alpakit Dev", "Open the alpakit dev window", EUserInterfaceActionType::Button, FInputChord{});
    UI_COMMAND(AlpakitReleaseWindow, "Alpakit Release", "Open the alpakit release window", EUserInterfaceActionType::Button, FInputChord{});
    UI_COMMAND(AlpakitLogWindow, "Alpakit Log", "Open the alpakit log window", EUserInterfaceActionType::Button, FInputChord{});
}

#undef LOCTEXT_NAMESPACE

#pragma once
#include "CoreMinimal.h"

class SML_API FUMGHelper {
public:
    /**
     * Inserts widget at the given index in the panel widget,
     * moving all widgets which occupy given index if necessary
     */
    static void InsertChildAtIndex(class UPanelWidget* PanelWidget, int32 Index, class UWidget* Widget);
};

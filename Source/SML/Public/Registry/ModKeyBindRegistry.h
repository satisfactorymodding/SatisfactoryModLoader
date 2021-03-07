#pragma once
#include "FGInputLibrary.h"
#include "ModKeyBindRegistry.generated.h"

UCLASS()
class SML_API UModKeyBindRegistry : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    /**
     * Register given key mapping and associates it with mod reference provided
     * Action name should be unique and start with "ModReference." prefix to avoid conflicts with other mods
     * This function will throw exception if action name doesn't start with prefix described above
     * You can only register two keys with same name, and one of them should be keyboard and another is gamepad (optional)
     * 
     * @param ModReference reference of the mod this key bind belongs to
     * @param KeyMapping information about KeyMapping being registered. 
     * @param DisplayName Name of the key binding used for options/controls menu
     */
    UFUNCTION(BlueprintCallable)
    static void RegisterModKeyBind(const FString& ModReference, const FInputActionKeyMapping& KeyMapping, const FText& DisplayName);

    /**
     * Registers given axis key mappings and associate them with given mod reference
     * Axis names should be unique and start with "ModReference." prefix to avoid conflicts with other mods
     * This function will throw exception if axis names don't start with prefix described above
     * Both axis mappings should have equal action name, too.
     * FactoryGame requires all axis binds to have 2 keys with opposite directions, and they will be displayed as 2 keys in control options too
     * You can only register two axis binding pairs, and one of them should be keyboard and another is gamepad (optional)
     *
     * @param ModReference reference of the mod this axis bind belongs to
     * @param PositiveAxisMapping information about axis key in positive direction (Scale > 0)
     * @param NegativeAxisMapping information about axis key in negative direction (Scale < 0)
     * @param PositiveDisplayName Name of the positive axis binding for options/controls menu
     * @param NegativeDisplayName Name of the negative axis binding for options/controls menu
     */
    UFUNCTION(BlueprintCallable)
    static void RegisterModAxisBind(const FString& ModReference, const FInputAxisKeyMapping& PositiveAxisMapping, const FInputAxisKeyMapping& NegativeAxisMapping, const FText& PositiveDisplayName, const FText& NegativeDisplayName);
};

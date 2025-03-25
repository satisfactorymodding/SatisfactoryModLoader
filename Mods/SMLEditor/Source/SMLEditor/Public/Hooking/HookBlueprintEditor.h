#pragma once

#include "CoreMinimal.h"
#include "BlueprintEditor.h"
#include "Framework/Commands/Commands.h"

class UHookBlueprint;

class FHookBlueprintEditorCommands : public TCommands<FHookBlueprintEditorCommands>
{
public:
	FHookBlueprintEditorCommands() 
		: TCommands<FHookBlueprintEditorCommands>("HookBlueprintEditor", NSLOCTEXT("Contexts", "HookBlueprintEditor", "Hook Blueprint Editor"), NAME_None, FAppStyle::GetAppStyleSetName()) {
	}
	TSharedPtr<FUICommandInfo> EditHookBlueprintHookGraph;

	virtual void RegisterCommands() override;
};

class SMLEDITOR_API FHookBlueprintEditor : public FBlueprintEditor {
public:
	// Begin FBlueprintEditor interface
	virtual FName GetToolkitFName() const override;
	virtual void CreateDefaultCommands() override;
	virtual FGraphAppearanceInfo GetGraphAppearance(UEdGraph* InGraph) const override;
	virtual UToolMenu* RegisterModeToolbarIfUnregistered(const FName InModeName) override;
	// End FBlueprintEditor interface

	/** Called to initialize and open the hook blueprint editor */
	void InitHookBlueprintEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UHookBlueprint* Blueprint);

	/** Returns currently opened editor for provided blueprint, or nullptr */
	static TSharedPtr<FHookBlueprintEditor> FindEditorForHookBlueprint( const UHookBlueprint* HookBlueprint);

	// Expose protected function to be used from graph schema
	using FBlueprintEditor::GetBoundsForSelectedNodes;
protected:
	/** Opens the blueprint hook graph tab */
	void OpenBlueprintHookGraphTab();
	/** Returns true if hook graph is already open */
	bool IsBlueprintHookGraphTabOpen() const;
};

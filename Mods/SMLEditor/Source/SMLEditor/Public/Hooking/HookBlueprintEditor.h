#pragma once

#include "CoreMinimal.h"
#include "BlueprintEditor.h"
#include "BlueprintEditorModes.h"
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
	virtual void RegisterApplicationModes(const TArray<UBlueprint*>& InBlueprints, bool bShouldOpenInDefaultsMode, bool bNewlyCreated) override;
	virtual void CreateDefaultTabContents(const TArray<UBlueprint*>& InBlueprints) override;
	virtual bool ReparentBlueprint_IsVisible() const override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;
	virtual void RefreshEditors(ERefreshBlueprintEditorReason::Type Reason) override;
	// End FBlueprintEditor interface

	/** Called to initialize and open the hook blueprint editor */
	void InitHookBlueprintEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UHookBlueprint* Blueprint);

	/** Returns currently opened editor for provided blueprint, or nullptr */
	static TSharedPtr<FHookBlueprintEditor> FindEditorForHookBlueprint( const UHookBlueprint* HookBlueprint);

	/** Registers hook blueprint specific items to the toolbar */
	virtual void AddBlueprintHookEditorToolbar(UToolMenu* InMenu);
	
	// Expose protected function to be used from graph schema
	using FBlueprintEditor::GetBoundsForSelectedNodes;

	/** Returns component tree overlay editor widget */
	FORCEINLINE TSharedPtr<class SOverlayComponentTreeEditor> GetComponentTreeOverlayEditor() const { return HookComponentTreeOverlayEditor; }
	FORCEINLINE TSharedPtr<class SWidget> GetOverlayComponentTreeViewport() const { return HookOverlayComponentTreeViewport; }

	/** Returns true if this editor supports editing the overlay component tree */
	virtual bool BlueprintSupportsOverlayComponentTree() const;

	/** Returns the preview actor used for previewing the overlay component tree for this blueprint */
	AActor* GetOverlayPreviewActor() const;
	/** Returns the bounding box of the preview actor. Will return empty bounding box if preview actor is invalid */
	FORCEINLINE FBoxSphereBounds GetOverlayPreviewActorBounds() const { return PreviewActorBounds; }
	
	/** Destroys currently spawned overlay preview actor */
	virtual void DestroyOverlayPreviewActor();
	
	/** Updates the overlay component tree preview actor for this blueprint */
	virtual void UpdateOverlayPreviewActor(UHookBlueprint* InBlueprintObject, bool bForceFullActorUpdate);

	/** Called no update the overlay component tree when nodes are changed */
	virtual void OnOverlayComponentTreeChanged();
protected:
	/** Opens the blueprint hook graph tab */
	void OpenBlueprintHookGraphTab();
	/** Returns true if hook graph is already open */
	bool IsBlueprintHookGraphTabOpen() const;
	/** Creates editor for the component tree overlay */
	void CreateComponentTreeOverlayEditor();

	/** Editor object for the Overlay Component Tree */
	TSharedPtr<class SOverlayComponentTreeEditor> HookComponentTreeOverlayEditor;
	TSharedPtr<SWidget> HookOverlayComponentTreeViewport;
	TWeakObjectPtr<AActor> OverlayPreviewActorWeakPtr;
	FBoxSphereBounds PreviewActorBounds{ForceInit};
};

struct FHookBlueprintComponentTreeEditorSummoner : FWorkflowTabFactory {
	explicit FHookBlueprintComponentTreeEditorSummoner(TSharedPtr<FAssetEditorToolkit> InHostingApp);

	// Begin FWorkflowTabFactory interface
	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;
	// End FWorkflowTabFactory interface
};

struct FHookBlueprintViewportSummoner : FWorkflowTabFactory {
	explicit FHookBlueprintViewportSummoner(TSharedPtr<FAssetEditorToolkit> InHostingApp);

	// Begin FWorkflowTabFactory interface
	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;
	// End FWorkflowTabFactory interface
};

class FHookBlueprintEditorMode : public FBlueprintEditorApplicationMode
{
public:
	explicit FHookBlueprintEditorMode(const TSharedRef<FHookBlueprintEditor>& InHookBlueprintEditor, bool bAllowOverlayComponentTree);
protected:
	// Set of spawnable tabs
	FWorkflowAllowedTabSet TabFactories;
private:
	TWeakObjectPtr<class UHookBlueprint> HookBlueprintPtr;
};

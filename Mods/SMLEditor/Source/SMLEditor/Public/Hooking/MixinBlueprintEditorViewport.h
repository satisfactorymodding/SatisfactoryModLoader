#pragma once

#include "Input/Reply.h"
#include "SEditorViewport.h"
#include "SViewportToolBar.h"
#include "Templates/SharedPointer.h"
#include "Types/SlateEnums.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

class SMixinBlueprintEditorViewportToolBar : public SViewportToolBar {
public:
	SLATE_BEGIN_ARGS(SMixinBlueprintEditorViewportToolBar) {}
		SLATE_ARGUMENT(TWeakPtr<class SMixinBlueprintEditorViewport>, EditorViewport);
	SLATE_END_ARGS()
	void Construct(const FArguments& InArgs);
protected:
	TSharedRef<SWidget> GeneratePreviewMenu() const;
	FText GetCameraMenuLabel() const;
	TSharedRef<SWidget> GenerateCameraMenu() const;
	FText GetViewMenuLabel() const;
	TSharedRef<SWidget> GenerateViewMenu() const;
private:
	TWeakPtr<SMixinBlueprintEditorViewport> EditorViewport;
};

class SMixinBlueprintEditorViewport : public SEditorViewport
{
public:
	SLATE_BEGIN_ARGS(SMixinBlueprintEditorViewport){}
		SLATE_ARGUMENT(TWeakPtr<class FHookBlueprintEditor>, BlueprintEditor)
	SLATE_END_ARGS()
	virtual ~SMixinBlueprintEditorViewport() override;

	void Construct(const FArguments& InArgs);

	void Invalidate() const;
	void EnableRealtimePreview(bool bEnable) const;
	void RequestRefresh(bool bRefreshNow = false);

	// SWidget interface
	virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;
	// End of SWidget interface
	
	void OnComponentSelectionChanged();
	virtual void OnFocusViewportToSelection() override;

	void SetOwnerTab(TSharedRef<SDockTab> Tab);
	TSharedPtr<SDockTab> GetOwnerTab() const;
protected:
	virtual bool IsVisible() const override;
	bool ShouldShowViewportCommands() const;

	/** SEditorViewport interface */
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
	virtual TSharedPtr<SWidget> MakeViewportToolbar() override;
	virtual void BindCommands() override;
private:
	/** One-off active timer to update the preview */
	EActiveTimerReturnType DeferredUpdatePreview(double InCurrentTime, float InDeltaTime);

	/** Blueprint editor that owns this viewport */
	TWeakPtr<FHookBlueprintEditor> OwnerBlueprintEditor;
	/** Viewport client */
	TSharedPtr<class FMixinBlueprintEditorViewportClient> ViewportClient;

	/** Whether the active timer (for updating the preview) is registered */
	bool bIsActiveTimerRegistered{false};
	/** The owner dock tab for this viewport. */
	TWeakPtr<SDockTab> OwnerTab;
};

class FMixinBlueprintEditorViewportClient : public FEditorViewportClient, public TSharedFromThis<FMixinBlueprintEditorViewportClient>
{
public:
	FMixinBlueprintEditorViewportClient(const TWeakPtr<FHookBlueprintEditor>& InBlueprintEditorPtr, FPreviewScene* InPreviewScene, const TSharedRef<SMixinBlueprintEditorViewport>& InSCSEditorViewport);

	// Begin FEditorViewportClient interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void ProcessClick(FSceneView& View, HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY) override;
	virtual bool InputWidgetDelta(FViewport* CurrentViewport, EAxisList::Type CurrentAxis, FVector& Drag, FRotator& Rot, FVector& Scale) override;
	virtual void TrackingStarted(const FInputEventState& InInputState, bool bIsDraggingWidget, bool bNudge) override;
	virtual void TrackingStopped() override;
	virtual UE::Widget::EWidgetMode GetWidgetMode() const override;
	virtual FVector GetWidgetLocation() const override;
	virtual FMatrix GetWidgetCoordSystem() const override;
	virtual int32 GetCameraSpeedSetting() const override;
	virtual void SetCameraSpeedSetting(int32 SpeedSetting) override;
	// End FEditorViewportClient interface

	void ResetCamera();
	void InvalidatePreview();
	bool GetRealtimePreview() const { return IsRealtime(); }
	void ToggleRealtimePreview();
	void FocusViewportToSelection();
	bool GetShowFloor();
	void ToggleShowFloor();
	bool GetShowGrid();
	void ToggleShowGrid();
	AActor* GetPreviewActor() const;
protected:
	/** Weak reference to the editor hosting the viewport */
	TWeakPtr<FHookBlueprintEditor> BlueprintEditorPtr;
	/** Floor static mesh component */
	UStaticMeshComponent* EditorFloorComp;

	/** True if we are currently modifying object transform */
	bool bIsModyingComponentTransform{false};
	/** Nodes that we are currently modifying */
	TArray<TSharedPtr<class FOverlayComponentData>> ComponentNodesBeingModified;
};
#include "Hooking/MixinBlueprintEditorViewport.h"
#include "EditorViewportCommands.h"
#include "EngineUtils.h"
#include "ScopedTransaction.h"
#include "SEditorViewportToolBarMenu.h"
#include "STransformViewportToolbar.h"
#include "SViewportToolBar.h"
#include "UnrealEdGlobals.h"
#include "Components/StaticMeshComponent.h"
#include "Editor/EditorPerProjectUserSettings.h"
#include "Editor/UnrealEdEngine.h"
#include "Editor/Kismet/Private/SCSEditorViewportClient.h"
#include "Framework/Application/SlateApplication.h"
#include "Hooking/HookBlueprintEditor.h"
#include "Hooking/OverlayComponentTreeEditor.h"
#include "Kismet2/ComponentEditorUtils.h"
#include "Materials/Material.h"
#include "Patching/BlueprintHookBlueprint.h"
#include "Settings/LevelEditorViewportSettings.h"
#include "Slate/SceneViewport.h"
#include "ThumbnailRendering/SceneThumbnailInfo.h"
#include "ThumbnailRendering/ThumbnailManager.h"

void SMixinBlueprintEditorViewportToolBar::Construct(const FArguments& InArgs) {
	EditorViewport = InArgs._EditorViewport;
	const FMargin ToolbarSlotPadding(4.0f, 1.0f);
	this->ChildSlot [
		SNew(SBorder)
		.BorderImage(FAppStyle::Get().GetBrush("EditorViewportToolBar.Background"))
		.Cursor(EMouseCursor::Default) [
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot().AutoWidth().Padding(ToolbarSlotPadding) [
				SNew(SEditorViewportToolbarMenu)
				.ParentToolBar(SharedThis(this))
				.Cursor(EMouseCursor::Default)
				.Image("EditorViewportToolBar.OptionsDropdown")
				.OnGetMenuContent(this, &SMixinBlueprintEditorViewportToolBar::GeneratePreviewMenu)
			]
			+SHorizontalBox::Slot().AutoWidth().Padding(ToolbarSlotPadding) [
				SNew(SEditorViewportToolbarMenu)
				.ParentToolBar(SharedThis(this))
				.Label(this, &SMixinBlueprintEditorViewportToolBar::GetCameraMenuLabel)
				.OnGetMenuContent(this, &SMixinBlueprintEditorViewportToolBar::GenerateCameraMenu)
			]
			+SHorizontalBox::Slot().AutoWidth().Padding(ToolbarSlotPadding) [
				SNew( SEditorViewportToolbarMenu)
				.ParentToolBar(SharedThis(this))
				.Cursor(EMouseCursor::Default)
				.Label(this, &SMixinBlueprintEditorViewportToolBar::GetViewMenuLabel)
				.OnGetMenuContent(this, &SMixinBlueprintEditorViewportToolBar::GenerateViewMenu)
			]
			+SHorizontalBox::Slot().Padding(ToolbarSlotPadding).HAlign(HAlign_Right) [
				SNew(STransformViewportToolBar)
				.Viewport(EditorViewport.Pin().ToSharedRef())
				.CommandList(EditorViewport.Pin()->GetCommandList())
			]
		]
	];
	SViewportToolBar::Construct(SViewportToolBar::FArguments());
}

TSharedRef<SWidget> SMixinBlueprintEditorViewportToolBar::GeneratePreviewMenu() const {
	const TSharedPtr<const FUICommandList> CommandList = EditorViewport.IsValid()? EditorViewport.Pin()->GetCommandList() : nullptr;
	FMenuBuilder PreviewOptionsMenuBuilder(true, CommandList);
	
	PreviewOptionsMenuBuilder.BeginSection("BlueprintEditorPreviewOptions", NSLOCTEXT("BlueprintEditor", "PreviewOptionsMenuHeader", "Preview Viewport Options"));
	{
		// TODO: Fixup the floor/grid visibility controls and add a custom command list for them
		PreviewOptionsMenuBuilder.AddMenuEntry(FEditorViewportCommands::Get().ToggleRealTime);
		//PreviewOptionsMenuBuilder.AddMenuEntry(FBlueprintEditorCommands::Get().ShowFloor);
		//PreviewOptionsMenuBuilder.AddMenuEntry(FBlueprintEditorCommands::Get().ShowGrid);
	}
	PreviewOptionsMenuBuilder.EndSection();
	return PreviewOptionsMenuBuilder.MakeWidget();
}

FText SMixinBlueprintEditorViewportToolBar::GetCameraMenuLabel() const {
	if(EditorViewport.IsValid()) {
		return GetCameraMenuLabelFromViewportType(EditorViewport.Pin()->GetViewportClient()->GetViewportType());
	}
	return NSLOCTEXT("BlueprintEditor", "CameraMenuTitle_Default", "Camera");
}

TSharedRef<SWidget> SMixinBlueprintEditorViewportToolBar::GenerateCameraMenu() const {
	const TSharedPtr<const FUICommandList> CommandList = EditorViewport.IsValid() ? EditorViewport.Pin()->GetCommandList(): nullptr;
	FMenuBuilder CameraMenuBuilder(true, CommandList);

	CameraMenuBuilder.AddMenuEntry(FEditorViewportCommands::Get().Perspective);
	CameraMenuBuilder.BeginSection("LevelViewportCameraType_Ortho", NSLOCTEXT("BlueprintEditor", "CameraTypeHeader_Ortho", "Orthographic"));
	{
		CameraMenuBuilder.AddMenuEntry(FEditorViewportCommands::Get().Top);
		CameraMenuBuilder.AddMenuEntry(FEditorViewportCommands::Get().Bottom);
		CameraMenuBuilder.AddMenuEntry(FEditorViewportCommands::Get().Left);
		CameraMenuBuilder.AddMenuEntry(FEditorViewportCommands::Get().Right);
		CameraMenuBuilder.AddMenuEntry(FEditorViewportCommands::Get().Front);
		CameraMenuBuilder.AddMenuEntry(FEditorViewportCommands::Get().Back);
	}
	CameraMenuBuilder.EndSection();
	return CameraMenuBuilder.MakeWidget();
}

FText SMixinBlueprintEditorViewportToolBar::GetViewMenuLabel() const {
	if (const TSharedPtr<SMixinBlueprintEditorViewport> PinnedEditorViewport = EditorViewport.Pin()) {
		switch (PinnedEditorViewport->GetViewportClient()->GetViewMode()) {
			case VMI_Lit: return NSLOCTEXT("BlueprintEditor", "ViewMenuTitle_Lit", "Lit");
			case VMI_Unlit: return NSLOCTEXT("BlueprintEditor", "ViewMenuTitle_Unlit", "Unlit");
			case VMI_BrushWireframe: return NSLOCTEXT("BlueprintEditor", "ViewMenuTitle_Wireframe", "Wireframe");
			case VMI_CollisionVisibility: return NSLOCTEXT("BlueprintEditor", "ViewMenuTitle_CollisionVisibility", "Collision Visibility");
			default: break;
		}
	}
	return NSLOCTEXT("BlueprintEditor", "ViewMenuTitle_Default", "View");
}

TSharedRef<SWidget> SMixinBlueprintEditorViewportToolBar::GenerateViewMenu() const {
	const TSharedPtr<const FUICommandList> CommandList = EditorViewport.IsValid() ? EditorViewport.Pin()->GetCommandList() : nullptr;
	FMenuBuilder ViewMenuBuilder(true, CommandList);

	ViewMenuBuilder.AddMenuEntry(FEditorViewportCommands::Get().LitMode, NAME_None, NSLOCTEXT("BlueprintEditor", "LitModeMenuOption", "Lit"));
	ViewMenuBuilder.AddMenuEntry(FEditorViewportCommands::Get().UnlitMode, NAME_None, NSLOCTEXT("BlueprintEditor", "UnlitModeMenuOption", "Unlit"));
	ViewMenuBuilder.AddMenuEntry(FEditorViewportCommands::Get().WireframeMode, NAME_None, NSLOCTEXT("BlueprintEditor", "WireframeModeMenuOption", "Wireframe"));
	ViewMenuBuilder.AddMenuEntry(FEditorViewportCommands::Get().CollisionVisibility, NAME_None, NSLOCTEXT("BlueprintEditor", "CollisionVisibilityMenuOption", "Visibility Collision"));
	return ViewMenuBuilder.MakeWidget();
}

void SMixinBlueprintEditorViewport::Construct(const FArguments& InArgs) {
	bIsActiveTimerRegistered = false;
	OwnerBlueprintEditor = InArgs._BlueprintEditor;
	SEditorViewport::Construct(SEditorViewport::FArguments());

	// Refresh the preview scene
	RequestRefresh(true);
	// Setup the initial camera position
	if (ViewportClient.IsValid()) {
		ViewportClient->ResetCamera();
	}
}

SMixinBlueprintEditorViewport::~SMixinBlueprintEditorViewport() {
	// Reset this to ensure it's no longer in use after destruction
	if(ViewportClient.IsValid()) {
		ViewportClient->Viewport = nullptr;
	}
}

bool SMixinBlueprintEditorViewport::IsVisible() const {
	// We consider the viewport to be visible if the reference is valid
	return ViewportWidget.IsValid() && SEditorViewport::IsVisible();
}

TSharedRef<FEditorViewportClient> SMixinBlueprintEditorViewport::MakeEditorViewportClient() {
	FPreviewScene* PreviewScene = OwnerBlueprintEditor.Pin()->GetPreviewScene();

	// Construct a new viewport client instance
	ViewportClient = MakeShareable(new FMixinBlueprintEditorViewportClient(OwnerBlueprintEditor, PreviewScene, SharedThis(this)));
	ViewportClient->SetRealtime(true);
	ViewportClient->bSetListenerPosition = false;
	ViewportClient->VisibilityDelegate.BindSP(this, &SMixinBlueprintEditorViewport::IsVisible);

	return ViewportClient.ToSharedRef();
}

TSharedPtr<SWidget> SMixinBlueprintEditorViewport::MakeViewportToolbar() {
	return SNew(SMixinBlueprintEditorViewportToolBar)
		.EditorViewport(SharedThis(this))
		.IsEnabled(FSlateApplication::Get().GetNormalExecutionAttribute());
}

void SMixinBlueprintEditorViewport::BindCommands() {
	// Add editor toolkit commands to the viewport command list
	CommandList->Append(OwnerBlueprintEditor.Pin()->GetToolkitCommands());
	SEditorViewport::BindCommands();
}

void SMixinBlueprintEditorViewport::Invalidate() const {
	ViewportClient->Invalidate();
}

void SMixinBlueprintEditorViewport::EnableRealtimePreview(bool bEnable) const {
	const FText SystemDisplayName = NSLOCTEXT("BlueprintEditor", "RealtimeOverrideMessage_Blueprints", "the active blueprint mode");
	if(bEnable) {
		// Restore the previously-saved realtime setting
		ViewportClient->RemoveRealtimeOverride(SystemDisplayName);
	} else {
		// Disable and store the current realtime setting
		ViewportClient->AddRealtimeOverride(false, SystemDisplayName);
	}
}

void SMixinBlueprintEditorViewport::RequestRefresh(bool bRefreshNow) {
	if(bRefreshNow) {
		// Invalidate preview if we want to refresh now
		if(ViewportClient.IsValid()) {
			ViewportClient->InvalidatePreview();
		}
	} else {
		// Defer the update until the next tick to avoid potentially refreshing while in a middle of an ongoing transaction
		if (!bIsActiveTimerRegistered) {
			bIsActiveTimerRegistered = true;
			RegisterActiveTimer(0.f, FWidgetActiveTimerDelegate::CreateSP(this, &SMixinBlueprintEditorViewport::DeferredUpdatePreview));
		}
	}
}

void SMixinBlueprintEditorViewport::OnComponentSelectionChanged() {
	// When the component selection changes, make sure to invalidate hit proxies to sync with the current selection
	SceneViewport->Invalidate();
}

void SMixinBlueprintEditorViewport::OnFocusViewportToSelection() {
	ViewportClient->FocusViewportToSelection();
}

bool SMixinBlueprintEditorViewport::ShouldShowViewportCommands() const {
	// Hide if actively debugging
	return !GIntraFrameDebuggingGameThread;
}

void SMixinBlueprintEditorViewport::SetOwnerTab(TSharedRef<SDockTab> Tab) {
	OwnerTab = Tab;
}

TSharedPtr<SDockTab> SMixinBlueprintEditorViewport::GetOwnerTab() const {
	return OwnerTab.Pin();
}

FReply SMixinBlueprintEditorViewport::OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) {
	const TSharedPtr<SOverlayComponentTreeEditor> OverlayComponentTreeEditor = OwnerBlueprintEditor.Pin()->GetComponentTreeOverlayEditor();
	return OverlayComponentTreeEditor->TryHandleAssetDragNDropOperation(DragDropEvent);
}

EActiveTimerReturnType SMixinBlueprintEditorViewport::DeferredUpdatePreview(double InCurrentTime, float InDeltaTime) {
	if (ViewportClient.IsValid()) {
		ViewportClient->InvalidatePreview();
	}
	bIsActiveTimerRegistered = false;
	return EActiveTimerReturnType::Stop;
}

FMixinBlueprintEditorViewportClient::FMixinBlueprintEditorViewportClient(const TWeakPtr<FHookBlueprintEditor>& InBlueprintEditorPtr, FPreviewScene* InPreviewScene, const TSharedRef<SMixinBlueprintEditorViewport>& InSCSEditorViewport)
	: FEditorViewportClient(nullptr, InPreviewScene, StaticCastSharedRef<SEditorViewport>(InSCSEditorViewport)), BlueprintEditorPtr(InBlueprintEditorPtr) {
	// Disable advanced render flags and bloom
	EngineShowFlags.DisableAdvancedFeatures();
	// Selectively set particular show flags that we need
	EngineShowFlags.SetSelectionOutline(GetDefault<ULevelEditorViewportSettings>()->bUseSelectionOutline);
	// Set if the grid will be drawn
	DrawHelper.bDrawGrid = GetDefault<UEditorPerProjectUserSettings>()->bSCSEditorShowGrid;

	// now add floor
	EditorFloorComp = NewObject<UStaticMeshComponent>(GetTransientPackage(), TEXT("EditorFloorComp"));
	
	if (UStaticMesh* FloorMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/EditorMeshes/PhAT_FloorBox.PhAT_FloorBox"))) {
		EditorFloorComp->SetStaticMesh(FloorMesh);
	}
	if (UMaterial* Material = LoadObject<UMaterial>(nullptr, TEXT("/Engine/EditorMaterials/PersonaFloorMat.PersonaFloorMat"))) {
		EditorFloorComp->SetMaterial(0, Material);
	}

	EditorFloorComp->SetRelativeScale3D(FVector(3.f, 3.f, 1.f));
	EditorFloorComp->SetVisibility(GetDefault<UEditorPerProjectUserSettings>()->bSCSEditorShowFloor);
	EditorFloorComp->SetCollisionEnabled(GetDefault<UEditorPerProjectUserSettings>()->bSCSEditorShowFloor? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
	PreviewScene->AddComponent(EditorFloorComp, FTransform::Identity);

	// Turn off so that actors added to the world do not have a lifespan (so they will not auto-destroy themselves).
	PreviewScene->GetWorld()->bBegunPlay = false;
	// Set up the default ambient cubemap
	PreviewScene->SetSkyCubemap(GUnrealEd->GetThumbnailManager()->AmbientCubemap);
}

void FMixinBlueprintEditorViewportClient::Tick(float DeltaSeconds) {
	FEditorViewportClient::Tick(DeltaSeconds);

	// Register the selection override delegate for the preview actor components
	if (const AActor* PreviewActor = GetPreviewActor()) {
		for (UActorComponent* Component : PreviewActor->GetComponents()) {
			if (UPrimitiveComponent* PrimComponent = Cast<UPrimitiveComponent>(Component)) {
				if (!PrimComponent->SelectionOverrideDelegate.IsBound()) {
					BlueprintEditorPtr.Pin()->GetComponentTreeOverlayEditor()->SetSelectionOverrideForComponent(PrimComponent);
					PrimComponent->PushSelectionToProxy();
				}
			}
		}
	} else {
		InvalidatePreview();
	}

	// Tick the preview scene world
	if (!GIntraFrameDebuggingGameThread) {
		PreviewScene->GetWorld()->Tick(IsRealtime() ? LEVELTICK_ViewportsOnly : LEVELTICK_TimeOnly, DeltaSeconds);
	}
}

void FMixinBlueprintEditorViewportClient::ProcessClick(FSceneView& View, HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY) {
	FEditorViewportClient::ProcessClick(View, HitProxy, Key, Event, HitX, HitY);

	if (HitProxy && HitProxy->IsA(HActor::StaticGetType())) {
		const HActor* ActorProxy = static_cast<HActor*>(HitProxy);

		// Tell the Overlay Component Tree Editor to select the component we just clicked on in the tree view
		if (ActorProxy && ActorProxy->Actor && ActorProxy->PrimComponent) {
			const bool bMultiSelectionActive = Viewport->KeyState(EKeys::LeftControl) || Viewport->KeyState(EKeys::RightControl);
			if (BlueprintEditorPtr.IsValid()) {
				BlueprintEditorPtr.Pin()->GetComponentTreeOverlayEditor()->SelectNodeForComponent(ActorProxy->PrimComponent, bMultiSelectionActive);
			}
		}
		Invalidate();
	}
}

void FMixinBlueprintEditorViewportClient::TrackingStarted(const FInputEventState& InInputState, bool bIsDraggingWidget, bool bNudge) {
	// Once we start dragging, remember which nodes we are dragging
	if (!bIsModyingComponentTransform && bIsDraggingWidget) {
		const TArray<TSharedPtr<FOverlayComponentData>> SelectedComponentNodes = BlueprintEditorPtr.Pin()->GetComponentTreeOverlayEditor()->GetSelectedNodes();

		// Collect editable nodes that have visualization (e.g. scene components)
		ComponentNodesBeingModified.Empty();
		for (const TSharedPtr<FOverlayComponentData>& ComponentNode : SelectedComponentNodes) {
			if (ComponentNode->IsNodeEditable() && Cast<USceneComponent>(ComponentNode->GetMutableActorComponentTemplate())) {
				ComponentNodesBeingModified.Add(ComponentNode);	
			}
		}
		// We are modifying component transform if we have started dragging at least a single editable node
		bIsModyingComponentTransform = !ComponentNodesBeingModified.IsEmpty();
	}
}

bool FMixinBlueprintEditorViewportClient::InputWidgetDelta(FViewport* CurrentViewport, EAxisList::Type CurrentAxis, FVector& Drag, FRotator& Rot, FVector& Scale) {
	// (mirrored from Level Editor VPC) - we don't scale components when we only have a very small scale change
	FVector ModifiedScale = Scale;
	if (!Scale.IsNearlyZero()) {
		if (GEditor->UsePercentageBasedScaling()) {
			ModifiedScale = Scale * ((GEditor->GetScaleGridSize() / 100.0f) / GEditor->GetGridSize());
		}
	} else {
		ModifiedScale = FVector::ZeroVector;
	}

	// If we are dragging the widget now, apply the delta to the selected components
	AActor* PreviewActor = GetPreviewActor();
	if (bIsModyingComponentTransform && PreviewActor) {

		// Apply delta to the preview components
		for (const TSharedPtr<FOverlayComponentData>& ComponentNode : ComponentNodesBeingModified) {
			USceneComponent* PreviewSceneComponent = Cast<USceneComponent>(BlueprintEditorPtr.Pin()->GetComponentTreeOverlayEditor()->FindComponentInstanceInActor(PreviewActor, ComponentNode));

			// Adjust the deltas as necessary
			FComponentEditorUtils::AdjustComponentDelta(PreviewSceneComponent, Drag, Rot);
			// Apply the delta to the preview component
			GEditor->ApplyDeltaToComponent(PreviewSceneComponent, true, &Drag, &Rot, &ModifiedScale, PreviewSceneComponent->GetRelativeLocation());
		}
		// Invalidate the viewport and return true
		Invalidate();
		return true;
	}
	return false;
}

void FMixinBlueprintEditorViewportClient::TrackingStopped() {
	AActor* PreviewActor = GetPreviewActor();
	if (bIsModyingComponentTransform) {
		// Start the transaction to apply the updated transform to the component templates
		if (PreviewActor != nullptr) {
			const FScopedTransaction ScopedTransaction(NSLOCTEXT("UnrealEd", "ModifyComponents", "Modify Component(s)"));
			
			for (const TSharedPtr<FOverlayComponentData>& ComponentNode : ComponentNodesBeingModified) {
				const USceneComponent* PreviewSceneComponent = Cast<USceneComponent>(BlueprintEditorPtr.Pin()->GetComponentTreeOverlayEditor()->FindComponentInstanceInActor(PreviewActor, ComponentNode));
				USceneComponent* TemplateSceneComponent = Cast<USceneComponent>(ComponentNode->GetMutableActorComponentTemplate());

				// Save the current template component into the transaction buffer and copy the transform changes from the template
				if (PreviewSceneComponent && TemplateSceneComponent) {
					TemplateSceneComponent->Modify();
					TemplateSceneComponent->SetRelativeLocation_Direct( PreviewSceneComponent->GetRelativeLocation() );
					TemplateSceneComponent->SetRelativeRotation_Direct( PreviewSceneComponent->GetRelativeRotation() );
					TemplateSceneComponent->SetRelativeScale3D_Direct( PreviewSceneComponent->GetRelativeScale3D() );
				}
			}
		}

		// Reset the current movable component list
		bIsModyingComponentTransform = false;
		ComponentNodesBeingModified.Empty();
	}
}

UE::Widget::EWidgetMode FMixinBlueprintEditorViewportClient::GetWidgetMode() const {
	TArray<TSharedPtr<FOverlayComponentData>> SelectedComponentNodes = BlueprintEditorPtr.Pin()->GetComponentTreeOverlayEditor()->GetSelectedNodes();
	AActor* PreviewActor = GetPreviewActor();

	// Return the local coord system of the first selected component node preview component
	if (PreviewActor != nullptr && !SelectedComponentNodes.IsEmpty()) {
		if (SelectedComponentNodes[0]->IsNodeEditable() && Cast<USceneComponent>(BlueprintEditorPtr.Pin()->GetComponentTreeOverlayEditor()->FindComponentInstanceInActor(PreviewActor, SelectedComponentNodes[0]))) {
			// Return parent widget mode if it is set, otherwise fallback to Translate
			const UE::Widget::EWidgetMode ParentWidgetMode = FEditorViewportClient::GetWidgetMode();
			return ParentWidgetMode == UE::Widget::EWidgetMode::WM_None ? UE::Widget::EWidgetMode::WM_Translate : ParentWidgetMode;
		}
	}
	// If we do not have an editable scene component selected, do not show the widget
	return UE::Widget::EWidgetMode::WM_None;
}

FVector FMixinBlueprintEditorViewportClient::GetWidgetLocation() const {
	TArray<TSharedPtr<FOverlayComponentData>> SelectedComponentNodes = BlueprintEditorPtr.Pin()->GetComponentTreeOverlayEditor()->GetSelectedNodes();
	AActor* PreviewActor = GetPreviewActor();

	// Return the location of the first selected node preview actor component
	if (PreviewActor != nullptr && !SelectedComponentNodes.IsEmpty()) {
		if (const USceneComponent* SelectedPreviewComponent = Cast<USceneComponent>(BlueprintEditorPtr.Pin()->GetComponentTreeOverlayEditor()->FindComponentInstanceInActor(PreviewActor, SelectedComponentNodes[0]))) {
			return SelectedPreviewComponent->GetComponentLocation();
		}
	}
	return FVector::ZeroVector;
}

FMatrix FMixinBlueprintEditorViewportClient::GetWidgetCoordSystem() const {
	// Attempt to retrieve the selected component instance if in local coordinate system
	if (GetWidgetCoordSystemSpace() == COORD_Local) {
		TArray<TSharedPtr<FOverlayComponentData>> SelectedComponentNodes = BlueprintEditorPtr.Pin()->GetComponentTreeOverlayEditor()->GetSelectedNodes();
		AActor* PreviewActor = GetPreviewActor();

		// Return the local coord system of the first selected component node preview component
		if (PreviewActor != nullptr && !SelectedComponentNodes.IsEmpty()) {
			if (const USceneComponent* SelectedPreviewComponent = Cast<USceneComponent>(BlueprintEditorPtr.Pin()->GetComponentTreeOverlayEditor()->FindComponentInstanceInActor(PreviewActor, SelectedComponentNodes[0]))) {
				return FQuatRotationMatrix(SelectedPreviewComponent->GetComponentQuat());
			}
		}
	}
	// Return identity matrix for world coord system
	return FMatrix::Identity;
}

int32 FMixinBlueprintEditorViewportClient::GetCameraSpeedSetting() const {
	return GetDefault<UEditorPerProjectUserSettings>()->SCSViewportCameraSpeed;
}

void FMixinBlueprintEditorViewportClient::SetCameraSpeedSetting(int32 SpeedSetting) {
	GetMutableDefault<UEditorPerProjectUserSettings>()->SCSViewportCameraSpeed = SpeedSetting;
}

void FMixinBlueprintEditorViewportClient::ResetCamera() {
	constexpr float AutoViewportOrbitCameraTranslate = 256.0f;
	const UBlueprint* Blueprint = BlueprintEditorPtr.Pin()->GetBlueprintObj();
	const FBoxSphereBounds PreviewActorBounds = BlueprintEditorPtr.Pin()->GetOverlayPreviewActorBounds();

	// For now, loosely base default camera positioning on thumbnail preview settings
	// TODO: Implement proper preview renderer for actor mixins
	const USceneThumbnailInfo* ThumbnailInfo = Cast<USceneThumbnailInfo>(Blueprint->ThumbnailInfo);
	if(ThumbnailInfo == nullptr) {
		ThumbnailInfo = USceneThumbnailInfo::StaticClass()->GetDefaultObject<USceneThumbnailInfo>();
	}

	// Clamp zoom to the actor's bounding sphere radius
	double OrbitZoom = ThumbnailInfo->OrbitZoom;
	if (PreviewActorBounds.SphereRadius + OrbitZoom < 0.0) {
		OrbitZoom = -PreviewActorBounds.SphereRadius;
	}

	ToggleOrbitCamera(true);
	{
		double TargetDistance = PreviewActorBounds.SphereRadius;
		if(TargetDistance <= 0.0f) {
			TargetDistance = AutoViewportOrbitCameraTranslate;
		}
		const FRotator ThumbnailAngle(ThumbnailInfo->OrbitPitch, ThumbnailInfo->OrbitYaw, 0.0f);

		SetViewLocationForOrbiting(PreviewActorBounds.Origin);
		SetViewLocation( GetViewLocation() + FVector(0.0f, TargetDistance * 1.5f + OrbitZoom - AutoViewportOrbitCameraTranslate, 0.0f) );
		SetViewRotation( ThumbnailAngle );
	}
	Invalidate();
}

void FMixinBlueprintEditorViewportClient::InvalidatePreview() {
	// Ensure that the editor is valid before continuing
	if(!BlueprintEditorPtr.IsValid()) {
		return;
	}

	UHookBlueprint* Blueprint = Cast<UHookBlueprint>(BlueprintEditorPtr.Pin()->GetBlueprintObj());
	check(Blueprint);
	const bool bIsPreviewActorValid = GetPreviewActor() != nullptr;

	// Create or update the Blueprint actor instance in the preview scene
	BlueprintEditorPtr.Pin()->UpdateOverlayPreviewActor(Blueprint, !bIsPreviewActorValid);
	Invalidate();
}

void FMixinBlueprintEditorViewportClient::ToggleRealtimePreview() {
	SetRealtime(!IsRealtime());
	Invalidate();
}

AActor* FMixinBlueprintEditorViewportClient::GetPreviewActor() const {
	return BlueprintEditorPtr.Pin()->GetOverlayPreviewActor();
}

void FMixinBlueprintEditorViewportClient::FocusViewportToSelection() {
	if(const AActor* PreviewActor = GetPreviewActor()) {
		for (const UActorComponent* PreviewActorComponent : PreviewActor->GetComponents()) {
			const UPrimitiveComponent* SelectedPrimitiveComponent = Cast<UPrimitiveComponent>(PreviewActorComponent);

			// Focus on the first component that we consider selected
			if (SelectedPrimitiveComponent != nullptr && SelectedPrimitiveComponent->SelectionOverrideDelegate.IsBound() && SelectedPrimitiveComponent->SelectionOverrideDelegate.Execute(SelectedPrimitiveComponent)) {
				FocusViewportOnBox(SelectedPrimitiveComponent->Bounds.GetBox());
				return;
			}
		}
		// Focus on the entire actor if no scene component is selected
		FocusViewportOnBox(PreviewActor->GetComponentsBoundingBox(true));
	}
}

bool FMixinBlueprintEditorViewportClient::GetShowFloor()  {
	return GetDefault<UEditorPerProjectUserSettings>()->bSCSEditorShowFloor;
}

void FMixinBlueprintEditorViewportClient::ToggleShowFloor()  {
	UEditorPerProjectUserSettings* Settings = GetMutableDefault<UEditorPerProjectUserSettings>();

	bool bShowFloor = Settings->bSCSEditorShowFloor;
	bShowFloor = !bShowFloor;
	EditorFloorComp->SetVisibility(bShowFloor);
	EditorFloorComp->SetCollisionEnabled(bShowFloor? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);

	Settings->bSCSEditorShowFloor = bShowFloor;
	Settings->PostEditChange();
	Invalidate();
}

bool FMixinBlueprintEditorViewportClient::GetShowGrid() {
	return GetDefault<UEditorPerProjectUserSettings>()->bSCSEditorShowGrid;
}

void FMixinBlueprintEditorViewportClient::ToggleShowGrid()  {
	UEditorPerProjectUserSettings* Settings = GetMutableDefault<UEditorPerProjectUserSettings>();
	bool bShowGrid = Settings->bSCSEditorShowGrid;
	bShowGrid = !bShowGrid;

	DrawHelper.bDrawGrid = bShowGrid;
	Settings->bSCSEditorShowGrid = bShowGrid;
	Settings->PostEditChange();
	Invalidate();
}

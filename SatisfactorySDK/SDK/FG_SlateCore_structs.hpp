#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_CoreUObject_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Enums
//---------------------------------------------------------------------------

// Enum SlateCore.ECheckBoxState
enum class ECheckBoxState : uint8_t
{
	Unchecked                      = 0,
	Checked                        = 1,
	Undetermined                   = 2,
	ECheckBoxState_MAX             = 3
};


// Enum SlateCore.EWidgetClipping
enum class EWidgetClipping : uint8_t
{
	Inherit                        = 0,
	ClipToBounds                   = 1,
	ClipToBoundsWithoutIntersecting = 2,
	ClipToBoundsAlways             = 3,
	OnDemand                       = 4,
	EWidgetClipping_MAX            = 5
};


// Enum SlateCore.ESlateBrushImageType
enum class ESlateBrushImageType : uint8_t
{
	NoImage                        = 0,
	FullColor                      = 1,
	Linear                         = 2,
	ESlateBrushImageType_MAX       = 3
};


// Enum SlateCore.ESlateBrushMirrorType
enum class ESlateBrushMirrorType : uint8_t
{
	NoMirror                       = 0,
	Horizontal                     = 1,
	Vertical                       = 2,
	Both                           = 3,
	ESlateBrushMirrorType_MAX      = 4
};


// Enum SlateCore.ESlateBrushTileType
enum class ESlateBrushTileType : uint8_t
{
	NoTile                         = 0,
	Horizontal                     = 1,
	Vertical                       = 2,
	Both                           = 3,
	ESlateBrushTileType_MAX        = 4
};


// Enum SlateCore.ESlateBrushDrawType
enum class ESlateBrushDrawType : uint8_t
{
	NoDrawType                     = 0,
	Box                            = 1,
	Border                         = 2,
	Image                          = 3,
	ESlateBrushDrawType_MAX        = 4
};


// Enum SlateCore.ESlateColorStylingMode
enum class ESlateColorStylingMode : uint8_t
{
	UseColor_Specified             = 0,
	UseColor_Specified_Link        = 1,
	UseColor_Foreground            = 2,
	UseColor_Foreground_Subdued    = 3,
	UseColor_MAX                   = 4
};


// Enum SlateCore.EUINavigationRule
enum class EUINavigationRule : uint8_t
{
	Escape                         = 0,
	Explicit                       = 1,
	Wrap                           = 2,
	Stop                           = 3,
	Custom                         = 4,
	CustomBoundary                 = 5,
	Invalid                        = 6,
	EUINavigationRule_MAX          = 7
};


// Enum SlateCore.EUINavigation
enum class EUINavigation : uint8_t
{
	Left                           = 0,
	Right                          = 1,
	Up                             = 2,
	Down                           = 3,
	Next                           = 4,
	Previous                       = 5,
	Num                            = 6,
	Invalid                        = 7,
	EUINavigation_MAX              = 8
};


// Enum SlateCore.ESelectInfo
enum class ESelectInfo : uint8_t
{
	OnKeyPress                     = 0,
	OnNavigation                   = 1,
	OnMouseClick                   = 2,
	Direct                         = 3,
	ESelectInfo_MAX                = 4
};


// Enum SlateCore.ETextCommit
enum class ETextCommit : uint8_t
{
	Default                        = 0,
	OnEnter                        = 1,
	OnUserMovedFocus               = 2,
	OnCleared                      = 3,
	ETextCommit_MAX                = 4
};


// Enum SlateCore.ETextShapingMethod
enum class ETextShapingMethod : uint8_t
{
	Auto                           = 0,
	KerningOnly                    = 1,
	FullShaping                    = 2,
	ETextShapingMethod_MAX         = 3
};


// Enum SlateCore.EFontLayoutMethod
enum class EFontLayoutMethod : uint8_t
{
	Metrics                        = 0,
	BoundingBox                    = 1,
	EFontLayoutMethod_MAX          = 2
};


// Enum SlateCore.EFontLoadingPolicy
enum class EFontLoadingPolicy : uint8_t
{
	LazyLoad                       = 0,
	Stream                         = 1,
	Inline                         = 2,
	EFontLoadingPolicy_MAX         = 3
};


// Enum SlateCore.EFontHinting
enum class EFontHinting : uint8_t
{
	Default                        = 0,
	Auto                           = 1,
	AutoLight                      = 2,
	Monochrome                     = 3,
	None                           = 4,
	EFontHinting_MAX               = 5
};


// Enum SlateCore.EFocusCause
enum class EFocusCause : uint8_t
{
	Mouse                          = 0,
	Navigation                     = 1,
	SetDirectly                    = 2,
	Cleared                        = 3,
	OtherWidgetLostFocus           = 4,
	WindowActivate                 = 5,
	EFocusCause_MAX                = 6
};


// Enum SlateCore.EColorVisionDeficiency
enum class EColorVisionDeficiency : uint8_t
{
	NormalVision                   = 0,
	Deuteranope                    = 1,
	Protanope                      = 2,
	Tritanope                      = 3,
	EColorVisionDeficiency_MAX     = 4
};


// Enum SlateCore.EScrollDirection
enum class EScrollDirection : uint8_t
{
	Scroll_Down                    = 0,
	Scroll_Up                      = 1,
	Scroll_MAX                     = 2
};


// Enum SlateCore.EOrientation
enum class EOrientation : uint8_t
{
	Orient_Horizontal              = 0,
	Orient_Vertical                = 1,
	Orient_MAX                     = 2
};


// Enum SlateCore.EMenuPlacement
enum class EMenuPlacement : uint8_t
{
	MenuPlacement_BelowAnchor      = 0,
	MenuPlacement_CenteredBelowAnchor = 1,
	MenuPlacement_BelowRightAnchor = 2,
	MenuPlacement_ComboBox         = 3,
	MenuPlacement_ComboBoxRight    = 4,
	MenuPlacement_MenuRight        = 5,
	MenuPlacement_AboveAnchor      = 6,
	MenuPlacement_CenteredAboveAnchor = 7,
	MenuPlacement_AboveRightAnchor = 8,
	MenuPlacement_MenuLeft         = 9,
	MenuPlacement_Center           = 10,
	MenuPlacement_RightLeftCenter  = 11,
	MenuPlacement_MatchBottomLeft  = 12,
	MenuPlacement_MAX              = 13
};


// Enum SlateCore.EVerticalAlignment
enum class EVerticalAlignment : uint8_t
{
	VAlign_Fill                    = 0,
	VAlign_Top                     = 1,
	VAlign_Center                  = 2,
	VAlign_Bottom                  = 3,
	VAlign_MAX                     = 4
};


// Enum SlateCore.EHorizontalAlignment
enum class EHorizontalAlignment : uint8_t
{
	HAlign_Fill                    = 0,
	HAlign_Left                    = 1,
	HAlign_Center                  = 2,
	HAlign_Right                   = 3,
	HAlign_MAX                     = 4
};


// Enum SlateCore.ENavigationGenesis
enum class ENavigationGenesis : uint8_t
{
	Keyboard                       = 0,
	Controller                     = 1,
	User                           = 2,
	ENavigationGenesis_MAX         = 3
};


// Enum SlateCore.ENavigationSource
enum class ENavigationSource : uint8_t
{
	FocusedWidget                  = 0,
	WidgetUnderCursor              = 1,
	ENavigationSource_MAX          = 2
};


// Enum SlateCore.EButtonPressMethod
enum class EButtonPressMethod : uint8_t
{
	DownAndUp                      = 0,
	ButtonPress                    = 1,
	ButtonRelease                  = 2,
	EButtonPressMethod_MAX         = 3
};


// Enum SlateCore.EButtonTouchMethod
enum class EButtonTouchMethod : uint8_t
{
	DownAndUp                      = 0,
	PreciseTap                     = 1,
	EButtonTouchMethod_MAX         = 2
};


// Enum SlateCore.EButtonClickMethod
enum class EButtonClickMethod : uint8_t
{
	DownAndUp                      = 0,
	MouseDown                      = 1,
	MouseUp                        = 2,
	PreciseClick                   = 3,
	EButtonClickMethod_MAX         = 4
};


// Enum SlateCore.EFontFallback
enum class EFontFallback : uint8_t
{
	FF_NoFallback                  = 0,
	FF_LocalizedFallback           = 1,
	FF_LastResortFallback          = 2,
	FF_Max                         = 3
};


// Enum SlateCore.ESlateCheckBoxType
enum class ESlateCheckBoxType : uint8_t
{
	CheckBox                       = 0,
	ToggleButton                   = 1,
	ESlateCheckBoxType_MAX         = 2
};


// Enum SlateCore.ESlateParentWindowSearchMethod
enum class ESlateParentWindowSearchMethod : uint8_t
{
	ActiveWindow                   = 0,
	MainWindow                     = 1,
	ESlateParentWindowSearchMethod_MAX = 2
};


// Enum SlateCore.EConsumeMouseWheel
enum class EConsumeMouseWheel : uint8_t
{
	WhenScrollingPossible          = 0,
	Always                         = 1,
	Never                          = 2,
	EConsumeMouseWheel_MAX         = 3
};



//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct SlateCore.Geometry
// 0x0038
struct FGeometry
{
	unsigned char                                      UnknownData00[0x38];                                      // 0x0000(0x0038) MISSED OFFSET
};

// ScriptStruct SlateCore.Margin
// 0x0010
struct FMargin
{
	float                                              Left;                                                     // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Top;                                                      // 0x0004(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Right;                                                    // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Bottom;                                                   // 0x000C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct SlateCore.SlateColor
// 0x0028
struct FSlateColor
{
	struct FLinearColor                                SpecifiedColor;                                           // 0x0000(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ESlateColorStylingMode>                ColorUseRule;                                             // 0x0010(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x17];                                      // 0x0011(0x0017) MISSED OFFSET
};

// ScriptStruct SlateCore.SlateBrush
// 0x0088
struct FSlateBrush
{
	unsigned char                                      UnknownData00[0x8];                                       // 0x0000(0x0008) MISSED OFFSET
	struct FVector2D                                   ImageSize;                                                // 0x0008(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FMargin                                     Margin;                                                   // 0x0010(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FSlateColor                                 TintColor;                                                // 0x0020(0x0028) (Edit, BlueprintVisible)
	class UObject*                                     ResourceObject;                                           // 0x0048(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FName                                       ResourceName;                                             // 0x0050(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FBox2D                                      UVRegion;                                                 // 0x0058(0x0014) (ZeroConstructor)
	TEnumAsByte<ESlateBrushDrawType>                   DrawAs;                                                   // 0x006C(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ESlateBrushTileType>                   Tiling;                                                   // 0x006D(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ESlateBrushMirrorType>                 Mirroring;                                                // 0x006E(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ESlateBrushImageType>                  ImageType;                                                // 0x006F(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x10];                                      // 0x0070(0x0010) MISSED OFFSET
	unsigned char                                      bIsDynamicallyLoaded : 1;                                 // 0x0080(0x0001)
	unsigned char                                      bHasUObject : 1;                                          // 0x0080(0x0001) (Deprecated)
	unsigned char                                      UnknownData02[0x7];                                       // 0x0081(0x0007) MISSED OFFSET
};

// ScriptStruct SlateCore.InputEvent
// 0x0018
struct FInputEvent
{
	unsigned char                                      UnknownData00[0x18];                                      // 0x0000(0x0018) MISSED OFFSET
};

// ScriptStruct SlateCore.PointerEvent
// 0x0058 (0x0070 - 0x0018)
struct FPointerEvent : public FInputEvent
{
	unsigned char                                      UnknownData00[0x58];                                      // 0x0018(0x0058) MISSED OFFSET
};

// ScriptStruct SlateCore.CharacterEvent
// 0x0008 (0x0020 - 0x0018)
struct FCharacterEvent : public FInputEvent
{
	unsigned char                                      UnknownData00[0x8];                                       // 0x0018(0x0008) MISSED OFFSET
};

// ScriptStruct SlateCore.KeyEvent
// 0x0020 (0x0038 - 0x0018)
struct FKeyEvent : public FInputEvent
{
	unsigned char                                      UnknownData00[0x20];                                      // 0x0018(0x0020) MISSED OFFSET
};

// ScriptStruct SlateCore.NavigationEvent
// 0x0008 (0x0020 - 0x0018)
struct FNavigationEvent : public FInputEvent
{
	unsigned char                                      UnknownData00[0x8];                                       // 0x0018(0x0008) MISSED OFFSET
};

// ScriptStruct SlateCore.AnalogInputEvent
// 0x0008 (0x0040 - 0x0038)
struct FAnalogInputEvent : public FKeyEvent
{
	unsigned char                                      UnknownData00[0x8];                                       // 0x0038(0x0008) MISSED OFFSET
};

// ScriptStruct SlateCore.FontOutlineSettings
// 0x0028
struct FFontOutlineSettings
{
	int                                                OutlineSize;                                              // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0004(0x0004) MISSED OFFSET
	class UObject*                                     OutlineMaterial;                                          // 0x0008(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                OutlineColor;                                             // 0x0010(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      bSeparateFillAlpha : 1;                                   // 0x0020(0x0001) (Edit, BlueprintVisible)
	unsigned char                                      bApplyOutlineToDropShadows : 1;                           // 0x0020(0x0001) (Edit, BlueprintVisible)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0021(0x0007) MISSED OFFSET
};

// ScriptStruct SlateCore.SlateFontInfo
// 0x0058
struct FSlateFontInfo
{
	class UObject*                                     FontObject;                                               // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UObject*                                     FontMaterial;                                             // 0x0008(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FFontOutlineSettings                        OutlineSettings;                                          // 0x0010(0x0028) (Edit, BlueprintVisible)
	unsigned char                                      UnknownData00[0x10];                                      // 0x0038(0x0010) MISSED OFFSET
	struct FName                                       TypefaceFontName;                                         // 0x0048(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                Size;                                                     // 0x0050(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0054(0x0004) MISSED OFFSET
};

// ScriptStruct SlateCore.SlateWidgetStyle
// 0x0008
struct FSlateWidgetStyle
{
	unsigned char                                      UnknownData00[0x8];                                       // 0x0000(0x0008) MISSED OFFSET
};

// ScriptStruct SlateCore.TableRowStyle
// 0x06B0 (0x06B8 - 0x0008)
struct FTableRowStyle : public FSlateWidgetStyle
{
	struct FSlateBrush                                 SelectorFocusedBrush;                                     // 0x0008(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 ActiveHoveredBrush;                                       // 0x0090(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 ActiveBrush;                                              // 0x0118(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 InactiveHoveredBrush;                                     // 0x01A0(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 InactiveBrush;                                            // 0x0228(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 EvenRowBackgroundHoveredBrush;                            // 0x02B0(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 EvenRowBackgroundBrush;                                   // 0x0338(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 OddRowBackgroundHoveredBrush;                             // 0x03C0(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 OddRowBackgroundBrush;                                    // 0x0448(0x0088) (Edit, BlueprintVisible)
	struct FSlateColor                                 TextColor;                                                // 0x04D0(0x0028) (Edit, BlueprintVisible)
	struct FSlateColor                                 SelectedTextColor;                                        // 0x04F8(0x0028) (Edit, BlueprintVisible)
	struct FSlateBrush                                 DropIndicator_Above;                                      // 0x0520(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 DropIndicator_Onto;                                       // 0x05A8(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 DropIndicator_Below;                                      // 0x0630(0x0088) (Edit, BlueprintVisible)
};

// ScriptStruct SlateCore.SlateSound
// 0x0018
struct FSlateSound
{
	class UObject*                                     ResourceObject;                                           // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x10];                                      // 0x0008(0x0010) MISSED OFFSET
};

// ScriptStruct SlateCore.ButtonStyle
// 0x0270 (0x0278 - 0x0008)
struct FButtonStyle : public FSlateWidgetStyle
{
	struct FSlateBrush                                 Normal;                                                   // 0x0008(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 Hovered;                                                  // 0x0090(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 Pressed;                                                  // 0x0118(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 Disabled;                                                 // 0x01A0(0x0088) (Edit, BlueprintVisible)
	struct FMargin                                     NormalPadding;                                            // 0x0228(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FMargin                                     PressedPadding;                                           // 0x0238(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FSlateSound                                 PressedSlateSound;                                        // 0x0248(0x0018) (Edit, BlueprintVisible)
	struct FSlateSound                                 HoveredSlateSound;                                        // 0x0260(0x0018) (Edit, BlueprintVisible)
};

// ScriptStruct SlateCore.ComboButtonStyle
// 0x0398 (0x03A0 - 0x0008)
struct FComboButtonStyle : public FSlateWidgetStyle
{
	struct FButtonStyle                                ButtonStyle;                                              // 0x0008(0x0278) (Edit, BlueprintVisible)
	struct FSlateBrush                                 DownArrowImage;                                           // 0x0280(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 MenuBorderBrush;                                          // 0x0308(0x0088) (Edit, BlueprintVisible)
	struct FMargin                                     MenuBorderPadding;                                        // 0x0390(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct SlateCore.ComboBoxStyle
// 0x03D0 (0x03D8 - 0x0008)
struct FComboBoxStyle : public FSlateWidgetStyle
{
	struct FComboButtonStyle                           ComboButtonStyle;                                         // 0x0008(0x03A0) (Edit, BlueprintVisible)
	struct FSlateSound                                 PressedSlateSound;                                        // 0x03A8(0x0018) (Edit, BlueprintVisible)
	struct FSlateSound                                 SelectionChangeSlateSound;                                // 0x03C0(0x0018) (Edit, BlueprintVisible)
};

// ScriptStruct SlateCore.EditableTextStyle
// 0x0218 (0x0220 - 0x0008)
struct FEditableTextStyle : public FSlateWidgetStyle
{
	struct FSlateFontInfo                              Font;                                                     // 0x0008(0x0058) (Edit, BlueprintVisible)
	struct FSlateColor                                 ColorAndOpacity;                                          // 0x0060(0x0028) (Edit, BlueprintVisible)
	struct FSlateBrush                                 BackgroundImageSelected;                                  // 0x0088(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 BackgroundImageComposing;                                 // 0x0110(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 CaretImage;                                               // 0x0198(0x0088) (Edit, BlueprintVisible)
};

// ScriptStruct SlateCore.ScrollBarStyle
// 0x04C8 (0x04D0 - 0x0008)
struct FScrollBarStyle : public FSlateWidgetStyle
{
	struct FSlateBrush                                 HorizontalBackgroundImage;                                // 0x0008(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 VerticalBackgroundImage;                                  // 0x0090(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 VerticalTopSlotImage;                                     // 0x0118(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 HorizontalTopSlotImage;                                   // 0x01A0(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 VerticalBottomSlotImage;                                  // 0x0228(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 HorizontalBottomSlotImage;                                // 0x02B0(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 NormalThumbImage;                                         // 0x0338(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 HoveredThumbImage;                                        // 0x03C0(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 DraggedThumbImage;                                        // 0x0448(0x0088) (Edit, BlueprintVisible)
};

// ScriptStruct SlateCore.EditableTextBoxStyle
// 0x07F0 (0x07F8 - 0x0008)
struct FEditableTextBoxStyle : public FSlateWidgetStyle
{
	struct FSlateBrush                                 BackgroundImageNormal;                                    // 0x0008(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 BackgroundImageHovered;                                   // 0x0090(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 BackgroundImageFocused;                                   // 0x0118(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 BackgroundImageReadOnly;                                  // 0x01A0(0x0088) (Edit, BlueprintVisible)
	struct FMargin                                     padding;                                                  // 0x0228(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FSlateFontInfo                              Font;                                                     // 0x0238(0x0058) (Edit, BlueprintVisible)
	struct FSlateColor                                 ForegroundColor;                                          // 0x0290(0x0028) (Edit, BlueprintVisible)
	struct FSlateColor                                 BackgroundColor;                                          // 0x02B8(0x0028) (Edit, BlueprintVisible)
	struct FSlateColor                                 ReadOnlyForegroundColor;                                  // 0x02E0(0x0028) (Edit, BlueprintVisible)
	struct FMargin                                     HScrollBarPadding;                                        // 0x0308(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FMargin                                     VScrollBarPadding;                                        // 0x0318(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FScrollBarStyle                             ScrollBarStyle;                                           // 0x0328(0x04D0) (Edit, BlueprintVisible)
};

// ScriptStruct SlateCore.TextBlockStyle
// 0x01E0 (0x01E8 - 0x0008)
struct FTextBlockStyle : public FSlateWidgetStyle
{
	struct FSlateFontInfo                              Font;                                                     // 0x0008(0x0058) (Edit, BlueprintVisible)
	struct FSlateColor                                 ColorAndOpacity;                                          // 0x0060(0x0028) (Edit, BlueprintVisible)
	struct FVector2D                                   ShadowOffset;                                             // 0x0088(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                ShadowColorAndOpacity;                                    // 0x0090(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FSlateColor                                 SelectedBackgroundColor;                                  // 0x00A0(0x0028) (Edit)
	struct FLinearColor                                HighlightColor;                                           // 0x00C8(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FSlateBrush                                 HighlightShape;                                           // 0x00D8(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 UnderlineBrush;                                           // 0x0160(0x0088) (Edit, BlueprintVisible)
};

// ScriptStruct SlateCore.SpinBoxStyle
// 0x02E0 (0x02E8 - 0x0008)
struct FSpinBoxStyle : public FSlateWidgetStyle
{
	struct FSlateBrush                                 BackgroundBrush;                                          // 0x0008(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 HoveredBackgroundBrush;                                   // 0x0090(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 ActiveFillBrush;                                          // 0x0118(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 InactiveFillBrush;                                        // 0x01A0(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 ArrowsImage;                                              // 0x0228(0x0088) (Edit, BlueprintVisible)
	struct FSlateColor                                 ForegroundColor;                                          // 0x02B0(0x0028)
	struct FMargin                                     TextPadding;                                              // 0x02D8(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct SlateCore.FocusEvent
// 0x0008
struct FFocusEvent
{
	unsigned char                                      UnknownData00[0x8];                                       // 0x0000(0x0008) MISSED OFFSET
};

// ScriptStruct SlateCore.MotionEvent
// 0x0030 (0x0048 - 0x0018)
struct FMotionEvent : public FInputEvent
{
	unsigned char                                      UnknownData00[0x30];                                      // 0x0018(0x0030) MISSED OFFSET
};

// ScriptStruct SlateCore.FontData
// 0x0020
struct FFontData
{
	class FString                                      FontFilename;                                             // 0x0000(0x0010) (ZeroConstructor)
	EFontHinting                                       Hinting;                                                  // 0x0010(0x0001) (ZeroConstructor, IsPlainOldData)
	EFontLoadingPolicy                                 LoadingPolicy;                                            // 0x0011(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x0012(0x0002) MISSED OFFSET
	int                                                SubFaceIndex;                                             // 0x0014(0x0004) (ZeroConstructor, IsPlainOldData)
	class UObject*                                     FontFaceAsset;                                            // 0x0018(0x0008) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct SlateCore.TypefaceEntry
// 0x0028
struct FTypefaceEntry
{
	struct FName                                       Name;                                                     // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FFontData                                   Font;                                                     // 0x0008(0x0020)
};

// ScriptStruct SlateCore.Typeface
// 0x0010
struct FTypeface
{
	TArray<struct FTypefaceEntry>                      Fonts;                                                    // 0x0000(0x0010) (ZeroConstructor)
};

// ScriptStruct SlateCore.CompositeFallbackFont
// 0x0018
struct FCompositeFallbackFont
{
	struct FTypeface                                   Typeface;                                                 // 0x0000(0x0010)
	float                                              ScalingFactor;                                            // 0x0010(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0014(0x0004) MISSED OFFSET
};

// ScriptStruct SlateCore.CompositeSubFont
// 0x0020 (0x0038 - 0x0018)
struct FCompositeSubFont : public FCompositeFallbackFont
{
	TArray<struct FInt32Range>                         CharacterRanges;                                          // 0x0018(0x0010) (ZeroConstructor)
	class FString                                      Cultures;                                                 // 0x0028(0x0010) (ZeroConstructor)
};

// ScriptStruct SlateCore.CompositeFont
// 0x0038
struct FCompositeFont
{
	struct FTypeface                                   DefaultTypeface;                                          // 0x0000(0x0010)
	struct FCompositeFallbackFont                      FallbackTypeface;                                         // 0x0010(0x0018)
	TArray<struct FCompositeSubFont>                   SubTypefaces;                                             // 0x0028(0x0010) (ZeroConstructor)
};

// ScriptStruct SlateCore.CaptureLostEvent
// 0x0008
struct FCaptureLostEvent
{
	unsigned char                                      UnknownData00[0x8];                                       // 0x0000(0x0008) MISSED OFFSET
};

// ScriptStruct SlateCore.WindowStyle
// 0x0FD0 (0x0FD8 - 0x0008)
struct FWindowStyle : public FSlateWidgetStyle
{
	struct FButtonStyle                                MinimizeButtonStyle;                                      // 0x0008(0x0278) (Edit, BlueprintVisible)
	struct FButtonStyle                                MaximizeButtonStyle;                                      // 0x0280(0x0278) (Edit, BlueprintVisible)
	struct FButtonStyle                                RestoreButtonStyle;                                       // 0x04F8(0x0278) (Edit, BlueprintVisible)
	struct FButtonStyle                                CloseButtonStyle;                                         // 0x0770(0x0278) (Edit, BlueprintVisible)
	struct FTextBlockStyle                             TitleTextStyle;                                           // 0x09E8(0x01E8) (Edit, BlueprintVisible)
	struct FSlateBrush                                 ActiveTitleBrush;                                         // 0x0BD0(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 InactiveTitleBrush;                                       // 0x0C58(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 FlashTitleBrush;                                          // 0x0CE0(0x0088) (Edit, BlueprintVisible)
	struct FSlateColor                                 BackgroundColor;                                          // 0x0D68(0x0028) (Edit, BlueprintVisible)
	struct FSlateBrush                                 OutlineBrush;                                             // 0x0D90(0x0088) (Edit, BlueprintVisible)
	struct FSlateColor                                 OutlineColor;                                             // 0x0E18(0x0028) (Edit, BlueprintVisible)
	struct FSlateBrush                                 BorderBrush;                                              // 0x0E40(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 BackgroundBrush;                                          // 0x0EC8(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 ChildBackgroundBrush;                                     // 0x0F50(0x0088) (Edit, BlueprintVisible)
};

// ScriptStruct SlateCore.ScrollBorderStyle
// 0x0110 (0x0118 - 0x0008)
struct FScrollBorderStyle : public FSlateWidgetStyle
{
	struct FSlateBrush                                 TopShadowBrush;                                           // 0x0008(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 BottomShadowBrush;                                        // 0x0090(0x0088) (Edit, BlueprintVisible)
};

// ScriptStruct SlateCore.ScrollBoxStyle
// 0x0220 (0x0228 - 0x0008)
struct FScrollBoxStyle : public FSlateWidgetStyle
{
	struct FSlateBrush                                 TopShadowBrush;                                           // 0x0008(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 BottomShadowBrush;                                        // 0x0090(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 LeftShadowBrush;                                          // 0x0118(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 RightShadowBrush;                                         // 0x01A0(0x0088) (Edit, BlueprintVisible)
};

// ScriptStruct SlateCore.DockTabStyle
// 0x06F8 (0x0700 - 0x0008)
struct FDockTabStyle : public FSlateWidgetStyle
{
	struct FButtonStyle                                CloseButtonStyle;                                         // 0x0008(0x0278) (Edit)
	struct FSlateBrush                                 NormalBrush;                                              // 0x0280(0x0088) (Edit)
	struct FSlateBrush                                 ActiveBrush;                                              // 0x0308(0x0088) (Edit)
	struct FSlateBrush                                 ColorOverlayTabBrush;                                     // 0x0390(0x0088) (Edit)
	struct FSlateBrush                                 ColorOverlayIconBrush;                                    // 0x0418(0x0088) (Edit)
	struct FSlateBrush                                 ForegroundBrush;                                          // 0x04A0(0x0088) (Edit)
	struct FSlateBrush                                 HoveredBrush;                                             // 0x0528(0x0088) (Edit)
	struct FSlateBrush                                 ContentAreaBrush;                                         // 0x05B0(0x0088) (Edit)
	struct FSlateBrush                                 TabWellBrush;                                             // 0x0638(0x0088) (Edit)
	struct FMargin                                     TabPadding;                                               // 0x06C0(0x0010) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              OverlapWidth;                                             // 0x06D0(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x06D4(0x0004) MISSED OFFSET
	struct FSlateColor                                 FlashColor;                                               // 0x06D8(0x0028) (Edit)
};

// ScriptStruct SlateCore.TableColumnHeaderStyle
// 0x04C8 (0x04D0 - 0x0008)
struct FTableColumnHeaderStyle : public FSlateWidgetStyle
{
	struct FSlateBrush                                 SortPrimaryAscendingImage;                                // 0x0008(0x0088) (Edit)
	struct FSlateBrush                                 SortPrimaryDescendingImage;                               // 0x0090(0x0088) (Edit)
	struct FSlateBrush                                 SortSecondaryAscendingImage;                              // 0x0118(0x0088) (Edit)
	struct FSlateBrush                                 SortSecondaryDescendingImage;                             // 0x01A0(0x0088) (Edit)
	struct FSlateBrush                                 NormalBrush;                                              // 0x0228(0x0088) (Edit)
	struct FSlateBrush                                 HoveredBrush;                                             // 0x02B0(0x0088) (Edit)
	struct FSlateBrush                                 MenuDropdownImage;                                        // 0x0338(0x0088) (Edit)
	struct FSlateBrush                                 MenuDropdownNormalBorderBrush;                            // 0x03C0(0x0088) (Edit)
	struct FSlateBrush                                 MenuDropdownHoveredBorderBrush;                           // 0x0448(0x0088) (Edit)
};

// ScriptStruct SlateCore.SplitterStyle
// 0x0110 (0x0118 - 0x0008)
struct FSplitterStyle : public FSlateWidgetStyle
{
	struct FSlateBrush                                 HandleNormalBrush;                                        // 0x0008(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 HandleHighlightBrush;                                     // 0x0090(0x0088) (Edit, BlueprintVisible)
};

// ScriptStruct SlateCore.HeaderRowStyle
// 0x0B68 (0x0B70 - 0x0008)
struct FHeaderRowStyle : public FSlateWidgetStyle
{
	struct FTableColumnHeaderStyle                     ColumnStyle;                                              // 0x0008(0x04D0) (Edit)
	struct FTableColumnHeaderStyle                     LastColumnStyle;                                          // 0x04D8(0x04D0) (Edit)
	struct FSplitterStyle                              ColumnSplitterStyle;                                      // 0x09A8(0x0118) (Edit)
	struct FSlateBrush                                 BackgroundBrush;                                          // 0x0AC0(0x0088) (Edit)
	struct FSlateColor                                 ForegroundColor;                                          // 0x0B48(0x0028) (Edit)
};

// ScriptStruct SlateCore.InlineTextImageStyle
// 0x0090 (0x0098 - 0x0008)
struct FInlineTextImageStyle : public FSlateWidgetStyle
{
	struct FSlateBrush                                 Image;                                                    // 0x0008(0x0088) (Edit)
	int16_t                                            Baseline;                                                 // 0x0090(0x0002) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x6];                                       // 0x0092(0x0006) MISSED OFFSET
};

// ScriptStruct SlateCore.SliderStyle
// 0x0338 (0x0340 - 0x0008)
struct FSliderStyle : public FSlateWidgetStyle
{
	struct FSlateBrush                                 NormalBarImage;                                           // 0x0008(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 HoveredBarImage;                                          // 0x0090(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 DisabledBarImage;                                         // 0x0118(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 NormalThumbImage;                                         // 0x01A0(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 HoveredThumbImage;                                        // 0x0228(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 DisabledThumbImage;                                       // 0x02B0(0x0088) (Edit, BlueprintVisible)
	float                                              BarThickness;                                             // 0x0338(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x033C(0x0004) MISSED OFFSET
};

// ScriptStruct SlateCore.VolumeControlStyle
// 0x05E8 (0x05F0 - 0x0008)
struct FVolumeControlStyle : public FSlateWidgetStyle
{
	struct FSliderStyle                                SliderStyle;                                              // 0x0008(0x0340) (Edit)
	struct FSlateBrush                                 HighVolumeImage;                                          // 0x0348(0x0088) (Edit)
	struct FSlateBrush                                 MidVolumeImage;                                           // 0x03D0(0x0088) (Edit)
	struct FSlateBrush                                 LowVolumeImage;                                           // 0x0458(0x0088) (Edit)
	struct FSlateBrush                                 NoVolumeImage;                                            // 0x04E0(0x0088) (Edit)
	struct FSlateBrush                                 MutedImage;                                               // 0x0568(0x0088) (Edit)
};

// ScriptStruct SlateCore.SearchBoxStyle
// 0x0A88 (0x0A90 - 0x0008)
struct FSearchBoxStyle : public FSlateWidgetStyle
{
	struct FEditableTextBoxStyle                       TextBoxStyle;                                             // 0x0008(0x07F8) (Edit)
	struct FSlateFontInfo                              ActiveFontInfo;                                           // 0x0800(0x0058) (Edit)
	struct FSlateBrush                                 UpArrowImage;                                             // 0x0858(0x0088) (Edit)
	struct FSlateBrush                                 DownArrowImage;                                           // 0x08E0(0x0088) (Edit)
	struct FSlateBrush                                 GlassImage;                                               // 0x0968(0x0088) (Edit)
	struct FSlateBrush                                 ClearImage;                                               // 0x09F0(0x0088) (Edit)
	struct FMargin                                     ImagePadding;                                             // 0x0A78(0x0010) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bLeftAlignButtons;                                        // 0x0A88(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0A89(0x0007) MISSED OFFSET
};

// ScriptStruct SlateCore.ExpandableAreaStyle
// 0x0118 (0x0120 - 0x0008)
struct FExpandableAreaStyle : public FSlateWidgetStyle
{
	struct FSlateBrush                                 CollapsedImage;                                           // 0x0008(0x0088) (Edit)
	struct FSlateBrush                                 ExpandedImage;                                            // 0x0090(0x0088) (Edit)
	float                                              RolloutAnimationSeconds;                                  // 0x0118(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x011C(0x0004) MISSED OFFSET
};

// ScriptStruct SlateCore.ProgressBarStyle
// 0x0198 (0x01A0 - 0x0008)
struct FProgressBarStyle : public FSlateWidgetStyle
{
	struct FSlateBrush                                 BackgroundImage;                                          // 0x0008(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 FillImage;                                                // 0x0090(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 MarqueeImage;                                             // 0x0118(0x0088) (Edit, BlueprintVisible)
};

// ScriptStruct SlateCore.InlineEditableTextBlockStyle
// 0x09E0 (0x09E8 - 0x0008)
struct FInlineEditableTextBlockStyle : public FSlateWidgetStyle
{
	struct FEditableTextBoxStyle                       EditableTextBoxStyle;                                     // 0x0008(0x07F8) (Edit, BlueprintVisible)
	struct FTextBlockStyle                             TextStyle;                                                // 0x0800(0x01E8) (Edit, BlueprintVisible)
};

// ScriptStruct SlateCore.HyperlinkStyle
// 0x0470 (0x0478 - 0x0008)
struct FHyperlinkStyle : public FSlateWidgetStyle
{
	struct FButtonStyle                                UnderlineStyle;                                           // 0x0008(0x0278) (Edit, BlueprintVisible)
	struct FTextBlockStyle                             TextStyle;                                                // 0x0280(0x01E8) (Edit, BlueprintVisible)
	struct FMargin                                     padding;                                                  // 0x0468(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct SlateCore.CheckBoxStyle
// 0x0578 (0x0580 - 0x0008)
struct FCheckBoxStyle : public FSlateWidgetStyle
{
	TEnumAsByte<ESlateCheckBoxType>                    CheckBoxType;                                             // 0x0008(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0009(0x0007) MISSED OFFSET
	struct FSlateBrush                                 UncheckedImage;                                           // 0x0010(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 UncheckedHoveredImage;                                    // 0x0098(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 UncheckedPressedImage;                                    // 0x0120(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 CheckedImage;                                             // 0x01A8(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 CheckedHoveredImage;                                      // 0x0230(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 CheckedPressedImage;                                      // 0x02B8(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 UndeterminedImage;                                        // 0x0340(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 UndeterminedHoveredImage;                                 // 0x03C8(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 UndeterminedPressedImage;                                 // 0x0450(0x0088) (Edit, BlueprintVisible)
	struct FMargin                                     padding;                                                  // 0x04D8(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FSlateColor                                 ForegroundColor;                                          // 0x04E8(0x0028) (Edit, BlueprintVisible)
	struct FSlateColor                                 BorderBackgroundColor;                                    // 0x0510(0x0028) (Edit, BlueprintVisible)
	struct FSlateSound                                 CheckedSlateSound;                                        // 0x0538(0x0018) (Edit, BlueprintVisible)
	struct FSlateSound                                 UncheckedSlateSound;                                      // 0x0550(0x0018) (Edit, BlueprintVisible)
	struct FSlateSound                                 HoveredSlateSound;                                        // 0x0568(0x0018) (Edit, BlueprintVisible)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_MovieSceneTracks_classes.hpp"
#include "FG_SlateCore_classes.hpp"
#include "FG_CoreUObject_classes.hpp"
#include "FG_InputCore_classes.hpp"
#include "FG_Engine_classes.hpp"
#include "FG_MovieScene_classes.hpp"
#include "FG_Slate_classes.hpp"
#include "FG_PropertyPath_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Enums
//---------------------------------------------------------------------------

// Enum UMG.ESlateVisibility
enum class ESlateVisibility : uint8_t
{
	Visible                        = 0,
	Collapsed                      = 1,
	Hidden                         = 2,
	HitTestInvisible               = 3,
	SelfHitTestInvisible           = 4,
	ESlateVisibility_MAX           = 5
};


// Enum UMG.EVirtualKeyboardType
enum class EVirtualKeyboardType : uint8_t
{
	Default                        = 0,
	Number                         = 1,
	Web                            = 2,
	Email                          = 3,
	Password                       = 4,
	AlphaNumeric                   = 5,
	EVirtualKeyboardType_MAX       = 6
};


// Enum UMG.EUMGSequencePlayMode
enum class EUMGSequencePlayMode : uint8_t
{
	Forward                        = 0,
	Reverse                        = 1,
	PingPong                       = 2,
	EUMGSequencePlayMode_MAX       = 3
};


// Enum UMG.EWidgetTickFrequency
enum class EWidgetTickFrequency : uint8_t
{
	Never                          = 0,
	Auto                           = 1,
	EWidgetTickFrequency_MAX       = 2
};


// Enum UMG.EDragPivot
enum class EDragPivot : uint8_t
{
	MouseDown                      = 0,
	TopLeft                        = 1,
	TopCenter                      = 2,
	TopRight                       = 3,
	CenterLeft                     = 4,
	CenterCenter                   = 5,
	CenterRight                    = 6,
	BottomLeft                     = 7,
	BottomCenter                   = 8,
	BottomRight                    = 9,
	EDragPivot_MAX                 = 10
};


// Enum UMG.EDynamicBoxType
enum class EDynamicBoxType : uint8_t
{
	Horizontal                     = 0,
	Vertical                       = 1,
	Wrap                           = 2,
	Overlay                        = 3,
	EDynamicBoxType_MAX            = 4
};


// Enum UMG.ESlateSizeRule
enum class ESlateSizeRule : uint8_t
{
	Automatic                      = 0,
	Fill                           = 1,
	ESlateSizeRule_MAX             = 2
};


// Enum UMG.EWidgetDesignFlags
enum class EWidgetDesignFlags : uint8_t
{
	None                           = 0,
	Designing                      = 1,
	ShowOutline                    = 2,
	ExecutePreConstruct            = 3,
	EWidgetDesignFlags_MAX         = 4
};


// Enum UMG.EBindingKind
enum class EBindingKind : uint8_t
{
	Function                       = 0,
	Property                       = 1,
	EBindingKind_MAX               = 2
};


// Enum UMG.EWidgetGeometryMode
enum class EWidgetGeometryMode : uint8_t
{
	Plane                          = 0,
	Cylinder                       = 1,
	EWidgetGeometryMode_MAX        = 2
};


// Enum UMG.EWidgetBlendMode
enum class EWidgetBlendMode : uint8_t
{
	Opaque                         = 0,
	Masked                         = 1,
	Transparent                    = 2,
	EWidgetBlendMode_MAX           = 3
};


// Enum UMG.EWidgetTimingPolicy
enum class EWidgetTimingPolicy : uint8_t
{
	RealTime                       = 0,
	GameTime                       = 1,
	EWidgetTimingPolicy_MAX        = 2
};


// Enum UMG.EWidgetSpace
enum class EWidgetSpace : uint8_t
{
	World                          = 0,
	Screen                         = 1,
	EWidgetSpace_MAX               = 2
};


// Enum UMG.EWidgetInteractionSource
enum class EWidgetInteractionSource : uint8_t
{
	World                          = 0,
	Mouse                          = 1,
	CenterScreen                   = 2,
	Custom                         = 3,
	EWidgetInteractionSource_MAX   = 4
};



//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct UMG.WidgetTransform
// 0x001C
struct FWidgetTransform
{
	struct FVector2D                                   Translation;                                              // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   Scale;                                                    // 0x0008(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   Shear;                                                    // 0x0010(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Angle;                                                    // 0x0018(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct UMG.EventReply
// 0x00B8
struct FEventReply
{
	unsigned char                                      UnknownData00[0xB8];                                      // 0x0000(0x00B8) MISSED OFFSET
};

// ScriptStruct UMG.NamedSlotBinding
// 0x0010
struct FNamedSlotBinding
{
	struct FName                                       Name;                                                     // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	class UWidget*                                     Content;                                                  // 0x0008(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// ScriptStruct UMG.PaintContext
// 0x0030
struct FPaintContext
{
	unsigned char                                      UnknownData00[0x30];                                      // 0x0000(0x0030) MISSED OFFSET
};

// ScriptStruct UMG.DynamicPropertyPath
// 0x0000 (0x0030 - 0x0030)
struct FDynamicPropertyPath : public FCachedPropertyPath
{

};

// ScriptStruct UMG.AnchorData
// 0x0028
struct FAnchorData
{
	struct FMargin                                     Offsets;                                                  // 0x0000(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FAnchors                                    Anchors;                                                  // 0x0010(0x0010) (Edit, BlueprintVisible)
	struct FVector2D                                   Alignment;                                                // 0x0020(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct UMG.SlateChildSize
// 0x0008
struct FSlateChildSize
{
	float                                              Value;                                                    // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ESlateSizeRule>                        SizeRule;                                                 // 0x0004(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0005(0x0003) MISSED OFFSET
};

// ScriptStruct UMG.ShapedTextOptions
// 0x0003
struct FShapedTextOptions
{
	unsigned char                                      bOverride_TextShapingMethod : 1;                          // 0x0000(0x0001) (Edit)
	unsigned char                                      bOverride_TextFlowDirection : 1;                          // 0x0000(0x0001) (Edit)
	ETextShapingMethod                                 TextShapingMethod;                                        // 0x0001(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	ETextFlowDirection                                 TextFlowDirection;                                        // 0x0002(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct UMG.MovieScene2DTransformMask
// 0x0004
struct FMovieScene2DTransformMask
{
	uint32_t                                           Mask;                                                     // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct UMG.SlateMeshVertex
// 0x003C
struct FSlateMeshVertex
{
	struct FVector2D                                   Position;                                                 // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FColor                                      Color;                                                    // 0x0008(0x0004) (ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   UV0;                                                      // 0x000C(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   UV1;                                                      // 0x0014(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   UV2;                                                      // 0x001C(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   UV3;                                                      // 0x0024(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   UV4;                                                      // 0x002C(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   UV5;                                                      // 0x0034(0x0008) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct UMG.WidgetAnimationBinding
// 0x0028
struct FWidgetAnimationBinding
{
	struct FName                                       WidgetName;                                               // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FName                                       SlotWidgetName;                                           // 0x0008(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FGuid                                       AnimationGuid;                                            // 0x0010(0x0010) (ZeroConstructor, IsPlainOldData)
	bool                                               bIsRootWidget;                                            // 0x0020(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0021(0x0007) MISSED OFFSET
};

// ScriptStruct UMG.DelegateRuntimeBinding
// 0x0058
struct FDelegateRuntimeBinding
{
	class FString                                      ObjectName;                                               // 0x0000(0x0010) (ZeroConstructor)
	struct FName                                       PropertyName;                                             // 0x0010(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FName                                       FunctionName;                                             // 0x0018(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FDynamicPropertyPath                        SourcePath;                                               // 0x0020(0x0030)
	EBindingKind                                       Kind;                                                     // 0x0050(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0051(0x0007) MISSED OFFSET
};

// ScriptStruct UMG.WidgetNavigationData
// 0x0028
struct FWidgetNavigationData
{
	EUINavigationRule                                  Rule;                                                     // 0x0000(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0001(0x0007) MISSED OFFSET
	struct FName                                       WidgetToFocus;                                            // 0x0008(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	TWeakObjectPtr<class UWidget>                      Widget;                                                   // 0x0010(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FScriptDelegate                             CustomDelegate;                                           // 0x0018(0x0014) (ZeroConstructor, InstancedReference)
};

// ScriptStruct UMG.MovieScene2DTransformSectionTemplate
// 0x0468 (0x04B0 - 0x0048)
struct FMovieScene2DTransformSectionTemplate : public FMovieScenePropertySectionTemplate
{
	struct FMovieSceneFloatChannel                     Translation[0x2];                                         // 0x0048(0x00A0)
	struct FMovieSceneFloatChannel                     Rotation;                                                 // 0x0188(0x00A0)
	struct FMovieSceneFloatChannel                     Scale[0x2];                                               // 0x0228(0x00A0)
	struct FMovieSceneFloatChannel                     Shear[0x2];                                               // 0x0368(0x00A0)
	EMovieSceneBlendType                               BlendType;                                                // 0x04A8(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x04A9(0x0003) MISSED OFFSET
	struct FMovieScene2DTransformMask                  Mask;                                                     // 0x04AC(0x0004)
};

// ScriptStruct UMG.MovieSceneMarginSectionTemplate
// 0x0288 (0x02D0 - 0x0048)
struct FMovieSceneMarginSectionTemplate : public FMovieScenePropertySectionTemplate
{
	struct FMovieSceneFloatChannel                     TopCurve;                                                 // 0x0048(0x00A0)
	struct FMovieSceneFloatChannel                     LeftCurve;                                                // 0x00E8(0x00A0)
	struct FMovieSceneFloatChannel                     RightCurve;                                               // 0x0188(0x00A0)
	struct FMovieSceneFloatChannel                     BottomCurve;                                              // 0x0228(0x00A0)
	EMovieSceneBlendType                               BlendType;                                                // 0x02C8(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x02C9(0x0007) MISSED OFFSET
};

// ScriptStruct UMG.MovieSceneWidgetMaterialSectionTemplate
// 0x0010 (0x0060 - 0x0050)
struct FMovieSceneWidgetMaterialSectionTemplate : public FMovieSceneParameterSectionTemplate
{
	TArray<struct FName>                               BrushPropertyNamePath;                                    // 0x0050(0x0010) (ZeroConstructor)
};

// ScriptStruct UMG.RichTextStyleRow
// 0x01E8 (0x01F0 - 0x0008)
struct FRichTextStyleRow : public FTableRowBase
{
	struct FTextBlockStyle                             TextStyle;                                                // 0x0008(0x01E8) (Edit)
};

// ScriptStruct UMG.RichImageRow
// 0x0088 (0x0090 - 0x0008)
struct FRichImageRow : public FTableRowBase
{
	struct FSlateBrush                                 Brush;                                                    // 0x0008(0x0088) (Edit)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

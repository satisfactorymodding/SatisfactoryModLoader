#pragma once
#include "Configuration/Properties/ConfigPropertyColor.h"
#include "CP_Color.generated.h"

UENUM(Blueprinttype)
enum class ECP_ColorWidgetType : uint8
{
	CPFC_Hue UMETA(Displayname = "Hue Slider", Tooltip = "A Horizontal Slider Rotating Colors by HUE"),
	CPFC_Vector3 UMETA(Displayname = "Slider", Tooltip = "RGB Float Input Fields - Alpha = 1"),
	CPFC_Vector4 UMETA(Displayname = "Slider", Tooltip = "RGB + Alpha Input Fields"),
};


UCLASS(EditInlineNew)
class SML_API UCP_Color : public UConfigPropertyColor {
    GENERATED_BODY()
public:


	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayAfter = "DefaultValue"))
		ECP_ColorWidgetType WidgetType;
};

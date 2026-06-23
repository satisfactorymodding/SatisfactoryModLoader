#pragma once
#include "Configuration/Properties/ConfigPropertySection.h"
#include "CP_Section.generated.h"


UENUM(Blueprinttype)
enum class ECP_SectionWidgetType : uint8
{
	CPS_Horizontal UMETA(Displayname = "Horizontal List", Tooltip = "Nested Properties will be presented in a Horizontal Layout (scroll bar used if needed)"),
	CPS_Vertical UMETA(Displayname = "Vertical List", Tooltip = "Nested Properties will be presented in a Vertical Layout"),
};

UCLASS(EditInlineNew, Abstract)
class SML_API UCP_Section : public UConfigPropertySection {
    GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default", meta = (DisplayAfter = "DefaultValue"))
		ECP_SectionWidgetType WidgetType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default", meta = (DisplayAfter = "DefaultValue"))
		bool HasHeader;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Default", meta = (DisplayAfter = "DefaultValue"))
		FText HeaderText;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "Default", meta = (DisplayAfter = "DefaultValue"))
		bool Collapsed;

};
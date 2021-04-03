#include "Toolkit/AssetDumping/AssetDumperWidget.h"
#include "Toolkit/AssetDumping/AssetRegistryViewWidget.h"
#include "Toolkit/AssetTypes/AssetTypeSerializer.h"
#include "Util/GameEditorHelper.h"
#define LOCTEXT_NAMESPACE "SML"

bool StaticAssetDumperExec(UWorld* World, const TCHAR* Command, FOutputDevice& Ar) {
	if (FParse::Command(&Command, TEXT("OpenAssetDumper"))) {
		TSharedRef<SWindow> Window = SNew(SWindow)
                        .Title(LOCTEXT("AssetDumper_Title", "Asset Dumper Settings"))
                        .MinWidth(800).MinHeight(600)
                        .AutoCenter(EAutoCenter::PreferredWorkArea);
		Window->SetContent(SNew(SAssetDumperWidget));

		const TSharedRef<SWindow> ParentWindow = FGameEditorHelper::GetMainWindow().ToSharedRef();
		FSlateApplication::Get().AddWindowAsNativeChild(Window, ParentWindow, true);
		return true;
	}
	return false;
}

void SAssetDumperWidget::Construct(const FArguments& InArgs) {
	ChildSlot[
		SNew(SVerticalBox)
		+SVerticalBox::Slot().AutoHeight()[
			SNew(SExpandableArea)
			.AreaTitle(LOCTEXT("AssetDumper_CatTypes", "Asset Types Filter"))
			.InitiallyCollapsed(true)
			.BodyContent()[
				CreateAssetTypesBox()
			]
		]
		+SVerticalBox::Slot().AutoHeight()[
			SNew(SExpandableArea)
			.AreaTitle(LOCTEXT("AssetDumper_AssetSelection", "Assets Selection"))
			.InitiallyCollapsed(false)
			.MaxHeight(400.0f)
			.BodyContent()[
				SNew(SScrollBox)
				.Orientation(Orient_Vertical)
				.ScrollBarAlwaysVisible(true)
				+SScrollBox::Slot()[
					SNew(SAssetRegistryViewWidget)
				]
			]
		]
	];
}

TSharedRef<SHorizontalBox> SAssetDumperWidget::CreateAssetTypesBox() {
	TSharedRef<SHorizontalBox> AssetTypesHolder = SNew(SHorizontalBox);
	TSharedPtr<SVerticalBox> CurrentVerticalBox;
	int32 AssetTypesStored = 0;
	const int32 MaxAssetTypesPerRow = 8;
	
	for (UAssetTypeSerializer* Serializer : UAssetTypeSerializer::GetAvailableAssetSerializers()) {
		const FName AssetClass = Serializer->GetAssetClass();
		this->AssetClassSerializationRules.Add(AssetClass, Serializer->ShouldSerializeByDefault());

		if (!CurrentVerticalBox.IsValid() || AssetTypesStored >= MaxAssetTypesPerRow) {
			CurrentVerticalBox = SNew(SVerticalBox);
			AssetTypesHolder->AddSlot().Padding(10.0f, 0.0f)[CurrentVerticalBox.ToSharedRef()];
			AssetTypesStored = 0;
		}
		AssetTypesStored++;
		
		CurrentVerticalBox->AddSlot()[
			SNew(SHorizontalBox)
	        +SHorizontalBox::Slot()[
	            SNew(STextBlock)
	            .Text(FText::FromString(AssetClass.ToString()))
	        ]
	        +SHorizontalBox::Slot()[
	            SNew(SCheckBox)
	            .IsChecked_Lambda([this, AssetClass]() {
	                const bool bShouldSerialize = AssetClassSerializationRules.FindChecked(AssetClass);
	                return bShouldSerialize ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
	            })
	            .OnCheckStateChanged_Lambda([this, AssetClass](const ECheckBoxState NewState) {
	                const bool bShouldSerialize = NewState == ECheckBoxState::Checked;
	                this->AssetClassSerializationRules.Add(AssetClass, bShouldSerialize);
	            })
	        ]
        ];
	}
	return AssetTypesHolder;
}

static FStaticSelfRegisteringExec AssetDumperStaticExec(&StaticAssetDumperExec);

#include "ModMetadataObject.h"

#include "Alpakit.h"
#include "PluginDescriptor.h"
#include "PluginReferenceDescriptor.h"
#include "Misc/Paths.h"
#include "Layout/Margin.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Interfaces/IPluginManager.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "DetailCategoryBuilder.h"
#include "SExternalImage.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"

UModMetadataObject::UModMetadataObject(const FObjectInitializer& ObjectInitializer)
{
	Category = TEXT("Modding"); // Group all mods in this category
}

void UModMetadataObject::PopulateFromDescriptor(const FPluginDescriptor& InDescriptor)
{
	Version = InDescriptor.Version;
	VersionName = InDescriptor.VersionName;
	FriendlyName = InDescriptor.FriendlyName;
	Description = InDescriptor.Description;
	// Category = InDescriptor.Category; // Keep "Modding" as set in the ctor
	CreatedBy = InDescriptor.CreatedBy;
	CreatedByURL = InDescriptor.CreatedByURL;
	DocsURL = InDescriptor.DocsURL;
	SupportURL = InDescriptor.SupportURL;
	for (const FPluginReferenceDescriptor& ModReference : InDescriptor.Plugins)
	{
		FModDependencyDescriptorData ModDependency;
		ModDependency.PopulateFromDescriptor(ModReference);
		Dependencies.Add(ModDependency);
	}

	// Since InDescriptor.CachedJson might not contain the freshly written AdditionalFields,
	// we need to read them from the AdditionalFieldsToWrite.
	// We can easily do that by having the descriptor write its data to a temporary json object
	const TSharedRef<FJsonObject> CachedJson = MakeShared<FJsonObject>();
	if (InDescriptor.CachedJson.IsValid()) {
		FJsonObject::Duplicate(InDescriptor.CachedJson, CachedJson);
	}
	InDescriptor.UpdateJson(CachedJson.Get());
	CachedJson->TryGetStringField( TEXT("SemVersion"), SemVersion );
	CachedJson->TryGetStringField( TEXT("GameVersion"), GameVersion );
	CachedJson->TryGetStringField( TEXT("RemoteVersionRange"), RemoteVersionRange );
	CachedJson->TryGetBoolField( TEXT("RequiredOnRemote"), bRequiredOnRemote );
}

void UModMetadataObject::CopyIntoDescriptor(FPluginDescriptor& OutDescriptor)
{
	OutDescriptor.Version = Version;
	OutDescriptor.VersionName = VersionName;
	OutDescriptor.FriendlyName = FriendlyName;
	OutDescriptor.Description = Description;
	OutDescriptor.Category = Category;
	OutDescriptor.CreatedBy = CreatedBy;
	OutDescriptor.CreatedByURL = CreatedByURL;
	OutDescriptor.DocsURL = DocsURL;
	OutDescriptor.SupportURL = SupportURL;
	TArray<FPluginReferenceDescriptor> RemovedMods = OutDescriptor.Plugins;
	for (FModDependencyDescriptorData& Dependency : Dependencies)
	{
		auto DependencyModLambda = [Dependency](FPluginReferenceDescriptor& ModReference){ return ModReference.Name == Dependency.Name; };
		RemovedMods.RemoveAll(DependencyModLambda);
		FPluginReferenceDescriptor* ExistingMod = OutDescriptor.Plugins.FindByPredicate(DependencyModLambda);
		if (ExistingMod)
		{
			TSharedPtr<FJsonObject> DependencyCachedJson = nullptr;
			if (OutDescriptor.CachedJson.IsValid()) {
				const TSharedPtr<FJsonValue>* CachedPluginJson = OutDescriptor.CachedJson->GetArrayField("Plugins").FindByPredicate([Dependency](TSharedPtr<FJsonValue> PluginDep) {
					return PluginDep->AsObject()->GetStringField(TEXT("Name")) == Dependency.Name;
				});
				if (CachedPluginJson) {
					DependencyCachedJson = (*CachedPluginJson)->AsObject();
				}
			}
			Dependency.CopyIntoDescriptor(*ExistingMod, DependencyCachedJson);
		}
		else
		{
			FPluginReferenceDescriptor NewMod;
			Dependency.CopyIntoDescriptor(NewMod, nullptr);
			OutDescriptor.Plugins.Add(NewMod);
		}
	}
	for (FPluginReferenceDescriptor RemovedMod : RemovedMods)
	{
		auto RemovedModLambda = [RemovedMod](FPluginReferenceDescriptor& ModReference){ return ModReference.Name == RemovedMod.Name; };
		OutDescriptor.Plugins.RemoveAll(RemovedModLambda);
	}

	OutDescriptor.AdditionalFieldsToWrite.Add( TEXT("SemVersion"), MakeShared<FJsonValueString>( SemVersion ) );
	OutDescriptor.AdditionalFieldsToWrite.Add( TEXT("GameVersion"), MakeShared<FJsonValueString>( GameVersion ) );
	if (RemoteVersionRange.Len() > 0) {
		OutDescriptor.AdditionalFieldsToWrite.Add( TEXT("RemoteVersionRange"), MakeShared<FJsonValueString>( RemoteVersionRange ) );
	} else {
		OutDescriptor.AdditionalFieldsToWrite.Remove(TEXT("RemoteVersionRange"));
		if (OutDescriptor.CachedJson.IsValid()) {
			OutDescriptor.CachedJson->RemoveField(TEXT("RemoteVersionRange"));
		}
	}
	if (!bRequiredOnRemote) {
		OutDescriptor.AdditionalFieldsToWrite.Add( TEXT("RequiredOnRemote"), MakeShared<FJsonValueBoolean>( bRequiredOnRemote ) );
	} else {
		OutDescriptor.AdditionalFieldsToWrite.Remove(TEXT("RequiredOnRemote"));
		if (OutDescriptor.CachedJson.IsValid()) {
			OutDescriptor.CachedJson->RemoveField(TEXT("RequiredOnRemote"));
		}
	}
}

#if WITH_EDITOR
void UModMetadataObject::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UObject::PostEditChangeProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UModMetadataObject, SemVersion))
	{
		int32 DotIdx = -1;
		if (SemVersion.FindChar('.', DotIdx))
		{
			FString MajorStr = SemVersion.Left(DotIdx);
			Version = FCString::Atoi(*MajorStr);
		}
		else
		{
			Version = 0;
		}
	}
}
#endif

FModDependencyDescriptorData::FModDependencyDescriptorData():
	bEnabled(true),
	bOptional(false),
	bBasePlugin(false)
{
}

void FModDependencyDescriptorData::PopulateFromDescriptor(const FPluginReferenceDescriptor& InDescriptor)
{
	Name = InDescriptor.Name;
	bEnabled = InDescriptor.bEnabled;
	bOptional = InDescriptor.bOptional;

	// Since InDescriptor.CachedJson might not contain the freshly written AdditionalFields,
	// we need to read them from the AdditionalFieldsToWrite.
	// We can easily do that by having the descriptor write its data to a temporary json object
	const TSharedRef<FJsonObject> CachedJson = MakeShared<FJsonObject>();
	if (InDescriptor.CachedJson.IsValid()) {
		FJsonObject::Duplicate(InDescriptor.CachedJson, CachedJson);
	}
	InDescriptor.UpdateJson(CachedJson.Get());
	CachedJson->TryGetStringField( TEXT("SemVersion"), SemVersion );
	CachedJson->TryGetBoolField( TEXT("BasePlugin"), bBasePlugin );
}

void FModDependencyDescriptorData::CopyIntoDescriptor(FPluginReferenceDescriptor& OutDescriptor, TSharedPtr<FJsonObject> CachedJson)
{
	OutDescriptor.Name = Name;
	OutDescriptor.bEnabled = bEnabled;
	OutDescriptor.bOptional = bOptional;

	if (!bBasePlugin) {
		OutDescriptor.AdditionalFieldsToWrite.Add(TEXT("SemVersion"), MakeShared<FJsonValueString>( SemVersion ));
	} else {
		OutDescriptor.AdditionalFieldsToWrite.Remove(TEXT("SemVersion"));
		if (OutDescriptor.CachedJson.IsValid()) {
			OutDescriptor.CachedJson->RemoveField(TEXT("SemVersion"));
		}
		if (CachedJson.IsValid()) {
			CachedJson->RemoveField(TEXT("SemVersion"));
		}
	}
	
	if (bBasePlugin) {
		OutDescriptor.AdditionalFieldsToWrite.Add(TEXT("BasePlugin"), MakeShared<FJsonValueBoolean>( bBasePlugin ));
	} else {
		OutDescriptor.AdditionalFieldsToWrite.Remove(TEXT("BasePlugin"));
		if (OutDescriptor.CachedJson.IsValid()) {
			OutDescriptor.CachedJson->RemoveField(TEXT("BasePlugin"));
		}
		if (CachedJson.IsValid()) {
			CachedJson->RemoveField(TEXT("BasePlugin"));
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

TSharedRef<IDetailCustomization> FModMetadataCustomization::MakeInstance()
{
	return MakeShareable(new FModMetadataCustomization());
}

void FModMetadataCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailBuilder.GetObjectsBeingCustomized(Objects);

	if(Objects.Num() == 1 && Objects[0].IsValid())
	{
		UModMetadataObject* ModMetadata = Cast<UModMetadataObject>(Objects[0].Get());
		if(ModMetadata != nullptr && ModMetadata->TargetIconPath.Len() > 0)
		{
			// Get the current icon path
			FString CurrentIconPath = ModMetadata->TargetIconPath;
			if(!FPaths::FileExists(CurrentIconPath))
			{
				CurrentIconPath = IPluginManager::Get().FindPlugin(TEXT("Alpakit"))->GetBaseDir() / TEXT("Resources") / TEXT("DefaultIcon128.png");
			}

			// Add the customization to edit the icon row
			IDetailCategoryBuilder& ImageCategory = DetailBuilder.EditCategory(TEXT("Icon"));
			const FText IconDesc(NSLOCTEXT("PluginBrowser", "Plugin", "Icon"));
			ImageCategory.AddCustomRow(IconDesc)
			.NameContent()
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.Padding( FMargin( 0, 1, 0, 1 ) )
				.FillWidth(1.0f)
				[
					SNew(STextBlock)
					.Text(IconDesc)
					.Font(DetailBuilder.GetDetailFont())
				]
			]
			.ValueContent()
			.MaxDesiredWidth(500.0f)
			.MinDesiredWidth(100.0f)
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.FillWidth(1.0f)
				.VAlign(VAlign_Center)
				[
					SNew(SExternalImage, CurrentIconPath, ModMetadata->TargetIconPath)
					.FileDescription(IconDesc)
					.MaxDisplaySize(FVector2D(128, 128))
					// .RequiredSize(FIntPoint(128, 128)) // UE wants the image to be 128x128, but that size is not enforced anywhere else
				]
			];
		}
	}
}

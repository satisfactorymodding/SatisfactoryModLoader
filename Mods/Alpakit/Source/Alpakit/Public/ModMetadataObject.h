// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "IDetailCustomization.h"
#include "ModMetadataObject.generated.h"

class IDetailLayoutBuilder;
struct FPluginDescriptor;
struct FPluginReferenceDescriptor;

/** Dependencies Descriptor */
USTRUCT()
struct FModDependencyDescriptorData
{
	GENERATED_BODY()

	FModDependencyDescriptorData();

	/** Mod Reference of the dependency mod */
	UPROPERTY(EditAnywhere, Category = "Details")
	FString Name;

	/** Compatible version range of the mod, it should follow the semver range format */
	UPROPERTY(EditAnywhere, Category = "Details")
	FString SemVersion;

	/** All dependencies must be enabled at runtime */
	UPROPERTY(VisibleAnywhere, Category = "Details")
	bool bEnabled;

	/** Whether this dependency mod is optional, and the game should silently ignore it not being present */
	UPROPERTY(EditAnywhere, Category = "Details")
	bool bOptional;

	/** Whether this dependency mod is a plugin that already exists in the base game */
	UPROPERTY(EditAnywhere, Category = "Details")
	bool bBasePlugin;

	/**
	 * Populate the fields of this object from an existing descriptor.
	 */
	void PopulateFromDescriptor(const FPluginReferenceDescriptor& InDescriptor);

	/**
	 * Copy the metadata fields into a mod descriptor.
	 */
	void CopyIntoDescriptor(FPluginReferenceDescriptor& OutDescriptor, TSharedPtr<FJsonObject> CachedJson);
};

/**
*	We use this object to display mod properties using details view.
*	This is based on UPluginMetadataObject from the PluginBrowser engine plugin.
*/
UCLASS()
class UModMetadataObject : public UObject
{
public:
	GENERATED_BODY()

	/* Default constructor */
	UModMetadataObject(const FObjectInitializer& ObjectInitializer);

	/** Path to this this mod's icon */
	FString TargetIconPath;

	/** The default Unreal Engine Version field. This is set automatically to match the first section of SemVersion */
	UPROPERTY(VisibleAnywhere, Category = "Version")
	int32 Version{};

	/** Name of the version for this mod. Usually you want this to match SemVersion */
	UPROPERTY(EditAnywhere, Category = "Version")
	FString VersionName;

	/** Version number for the mod. Should always increase with new releases, and should follow the semver format. */
	UPROPERTY(EditAnywhere, Category = "Version")
	FString SemVersion;

	/** Version number of the game this mod was built (or was tested) against */
	UPROPERTY(EditAnywhere, Category = "Version")
	FString GameVersion;

	/** Friendly name of the mod */
	UPROPERTY(EditAnywhere, Category = "Details")
	FString FriendlyName;

	/** Description of the mod */
	UPROPERTY(EditAnywhere, Category = "Details")
	FString Description;

	/** This is set automatically to Modding to group mods together */
	UPROPERTY(VisibleAnywhere, Category = "Details")
	FString Category;

	/** The name(s) of the author(s) of the mod */
	UPROPERTY(EditAnywhere, Category = "Details")
	FString CreatedBy;

	/** URL of the author(s) of the mod. Could be a GitHub link for example. This is optional. */
	UPROPERTY(EditAnywhere, Category = "Details")
	FString CreatedByURL;

	/** Documentation URL for the mod. In-game mod list will offer a button to users labeled "Open Documentation", http:// prefix is optional */
	UPROPERTY(EditAnywhere, Category = "Details")
	FString DocsURL;

	/** Support URL for the mod. In-game mod list will offer a button to users labeled "Get Support", http:// prefix is optional */
	UPROPERTY(EditAnywhere, Category = "Details")
	FString SupportURL;

	/** Other mods that are required by the mod */
	UPROPERTY(EditAnywhere, Category = "Dependencies")
	TArray<FModDependencyDescriptorData> Dependencies;

	/** A semver range of accepted versions of the mod on remote clients. If unspecified, it defaults to the current SemVersion */
	UPROPERTY(EditAnywhere, Category = "Remote")
	FString RemoteVersionRange;

	/** Whether this mod accepts being missing on the remote, i.e. behaving as a client-/server-side only mod */
	UPROPERTY(EditAnywhere, Category = "Remote")
	bool bRequiredOnRemote{true};

	/**
	 * Populate the fields of this object from an existing descriptor.
	 */
	void PopulateFromDescriptor(const FPluginDescriptor& InDescriptor);

	/**
	 * Copy the metadata fields into a mod descriptor.
	 */
	void CopyIntoDescriptor(FPluginDescriptor& OutDescriptor);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};

/**
 * Detail customization to allow editing the mod's icon
 */
class FModMetadataCustomization : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
};

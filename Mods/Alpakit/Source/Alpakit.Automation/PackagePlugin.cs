using System;
using System.Collections.Generic;
using System.IO.Compression;
using System.Linq;
using AutomationTool;
using EpicGames.Core;
using UnrealBuildTool;
using AutomationScripts;
using Microsoft.Extensions.Logging;

namespace Alpakit.Automation;

public class PackagePlugin : BuildCookRun
{
	public override void ExecuteBuild()
	{
		var mergeArchive = ParseParam("merge");
		
		var projectParams = SetupParams();
		projectParams.PreModifyDeploymentContextCallback = (ProjectParams, SC) =>
		{
			RemapCookedPluginsContentPaths(ProjectParams, SC);
		};
		projectParams.ModifyDeploymentContextCallback = (ProjectParams, SC) =>
		{
			ModifyModules(ProjectParams, SC);
		};
		
		try
		{
			DoBuildCookRun(projectParams);

			var deploymentContexts = new List<DeploymentContext>();
			if (!projectParams.NoClient)
				deploymentContexts.AddRange(Project.CreateDeploymentContext(projectParams, false, false));
			if (projectParams.DedicatedServer)
				deploymentContexts.AddRange(Project.CreateDeploymentContext(projectParams, true, false));

			foreach (var SC in deploymentContexts)
			{
				ArchiveStagedPlugin(projectParams, SC);
			}

			if (mergeArchive)
			{
				ArchiveMergedStagedPlugin(projectParams, deploymentContexts);
			}

			foreach (var SC in deploymentContexts)
			{
				var copyToGameDirectory = ParseOptionalDirectoryReferenceParam($"CopyToGameDirectory_{SC.FinalCookPlatform}");
				var launchGameType = ParseOptionalEnumParam<LaunchGame.LaunchType>($"LaunchGame_{SC.FinalCookPlatform}");
				var customLaunchPath = ParseOptionalStringParam($"CustomLaunchPath_{SC.FinalCookPlatform}");
				var customLaunchArgs = ParseOptionalStringParam($"CustomLaunchArgs_{SC.FinalCookPlatform}");

				if (copyToGameDirectory != null)
				{
					if (!IsValidGameDir(copyToGameDirectory))
						throw new AutomationException("Invalid game directory specified for CopyToGameDirectory: {0}", copyToGameDirectory);
					DeployStagedPlugin(projectParams, SC, copyToGameDirectory);
				}

				if (launchGameType != null)
					LaunchGame.Launch(launchGameType.Value, customLaunchPath, customLaunchArgs, Logger);
			}
		}
		finally
		{
			if (!projectParams.NoClient)
			{
				var DeployContextList = Project.CreateDeploymentContext(projectParams, false, true);
				foreach (var SC in DeployContextList)
					Project.CleanStagingDirectory(projectParams, SC);
			}

			if (projectParams.DedicatedServer)
			{
				var DeployContextList = Project.CreateDeploymentContext(projectParams, true, true);
				foreach (var SC in DeployContextList)
					Project.CleanStagingDirectory(projectParams, SC);
			}
		}
	}

	private bool IsValidGameDir(DirectoryReference GameDirectory)
	{
		var projectName = ProjectPath.GetFileNameWithoutAnyExtensions();
		var gameModuleDir = DirectoryReference.Combine(GameDirectory, projectName);
		return DirectoryReference.Exists(gameModuleDir);
	}

	protected ProjectParams SetupParams()
	{
		LogInformation("Setting up ProjectParams for {0}", ProjectPath);

		var Params = new ProjectParams
		(
			Command: this,
			RawProjectPath: ProjectPath,
			
			// Alpakit shared configuration
			ClientCookedTargets: GetClientTargetsToCook(),
			Cook: true,
			AdditionalCookerOptions: "-AllowUncookedAssetReferences",
			DLCIncludeEngineContent: false,
			Pak: true,
			Stage: true,
			
			// TODO @SML: I would like to pass an empty based on release version, but the cooker checks against it
			BasedOnReleaseVersion: "SMLNonExistentBasedOnReleaseVersion"
		);
		
		Params.ValidateAndLog();

		return Params;
	}

	private ParamList<string> GetClientTargetsToCook()
	{
		if (!ParseParam("merge"))
		{
			// Only build minimal targets in development mode
			// I don't particularly like hardcoding the FinalCookPlatform here, but there's no other way to get it
			// and there's no native linux client at the moment
			var gameDir = ParseOptionalDirectoryReferenceParam($"CopyToGameDirectory_Windows");
			if (gameDir != null)
			{
				var FactoryGameEGS = FileReference.Combine(gameDir, "FactoryGameEGS.exe");
				var FactoryGameSteam = FileReference.Combine(gameDir, "FactoryGameSteam.exe");
				if (FileReference.Exists(FactoryGameEGS))
				{
					return new ParamList<string>("FactoryGameEGS");
				}

				if (FileReference.Exists(FactoryGameSteam))
				{
					return new ParamList<string>("FactoryGameSteam");
				}
				
				Logger.LogWarning("No game executable found in game directory, building all targets");
			}
		}
		return new ParamList<string>("FactoryGameEGS", "FactoryGameSteam");
	}

	private static void DeployStagedPlugin(ProjectParams ProjectParams, DeploymentContext SC, DirectoryReference GameDir)
	{
		// We only want to archive the staged files of the plugin, not the entire stage directory
		var stagedPluginDirectory = DeploymentContext.ApplyDirectoryRemap(SC, SC.GetStagedFileLocation(ProjectParams.DLCFile));
		var fullStagedPluginDirectory = DirectoryReference.Combine(SC.StageDirectory, stagedPluginDirectory.Directory.Name);

		var projectName = ProjectParams.RawProjectPath.GetFileNameWithoutAnyExtensions();
		
		// Mods go into <GameDir>/<ProjectName>/Mods/<PluginName>
		var gameModsDir = DirectoryReference.Combine(GameDir, projectName, "Mods");
		var pluginName = ProjectParams.DLCFile.GetFileNameWithoutAnyExtensions();
		var modDir = DirectoryReference.Combine(gameModsDir, pluginName);

		if (DirectoryReference.Exists(modDir))
			DirectoryReference.Delete(modDir, true);

		CopyDirectory_NoExceptions(fullStagedPluginDirectory, modDir);
	}

	private static void ArchiveStagedPlugin(ProjectParams ProjectParams, DeploymentContext SC)
	{
		var archiveDirectory = GetArchivedPluginDirectory(ProjectParams);

		var dlcName = ProjectParams.DLCFile.GetFileNameWithoutAnyExtensions();
		
		var zipFileName = $"{dlcName}-{SC.FinalCookPlatform}.zip";

		// We only want to archive the staged files of the plugin, not the entire stage directory
		var stagedPluginDirectory = DeploymentContext.ApplyDirectoryRemap(SC, SC.GetStagedFileLocation(ProjectParams.DLCFile));
		var fullStagedPluginDirectory = DirectoryReference.Combine(SC.StageDirectory, stagedPluginDirectory.Directory.Name);

		CreateZipFromDirectory(fullStagedPluginDirectory, FileReference.Combine(archiveDirectory, zipFileName));
	}
    
	private static void ArchiveMergedStagedPlugin(ProjectParams ProjectParams, List<DeploymentContext> DeploymentContexts)
	{
		var archiveDirectory = GetArchivedPluginDirectory(ProjectParams);

		var dlcName = ProjectParams.DLCFile.GetFileNameWithoutAnyExtensions();
		
		var zipFileName = $"{dlcName}.zip";

		// We only want to archive the staged files of the plugin, not the entire stage directory
		var mergedTempDir = DirectoryReference.Combine(ProjectParams.DLCFile.Directory, "Saved", "ArchiveMerging");
		try
		{
			if (DirectoryReference.Exists(mergedTempDir))
				DirectoryReference.Delete(mergedTempDir, true);
			DirectoryReference.CreateDirectory(mergedTempDir);
			foreach (var SC in DeploymentContexts)
			{
				var stagedPluginDirectory =
					DeploymentContext.ApplyDirectoryRemap(SC, SC.GetStagedFileLocation(ProjectParams.DLCFile));
				var fullStagedPluginDirectory =
					DirectoryReference.Combine(SC.StageDirectory, stagedPluginDirectory.Directory.Name);
				CopyDirectory_NoExceptions(fullStagedPluginDirectory, DirectoryReference.Combine(mergedTempDir, SC.FinalCookPlatform));
			}

			CreateZipFromDirectory(mergedTempDir, FileReference.Combine(archiveDirectory, zipFileName));
		}
		finally
		{
			DirectoryReference.Delete(mergedTempDir, true);
		}
	}

	private static DirectoryReference GetArchivedPluginDirectory(ProjectParams ProjectParams)
	{
		// Plugins will be archived under <Project>/Saved/ArchivedPlugins/<DLCName>
		return DirectoryReference.Combine(ProjectParams.RawProjectPath.Directory, "Saved", "ArchivedPlugins", ProjectParams.DLCFile.GetFileNameWithoutAnyExtensions());
	}
	
	private static void CreateZipFromDirectory(DirectoryReference SourceDirectory, FileReference DestinationFile)
	{
		CreateDirectory(DestinationFile.Directory);
		
		if (FileReference.Exists(DestinationFile))
			FileReference.Delete(DestinationFile);

		ZipFile.CreateFromDirectory(SourceDirectory.FullName, DestinationFile.FullName);
	}

	private static string GetPluginPathRelativeToStageRoot(ProjectParams ProjectParams)
	{
		// All DLC paths are remapped to projectName/Mods/DLCName during RemapCookedPluginsContentPaths, regardless of nesting
		// so the relative stage path is projectName/Mods/DLCName
		var projectName = ProjectParams.RawProjectPath.GetFileNameWithoutAnyExtensions();
		var dlcName = ProjectParams.DLCFile.GetFileNameWithoutAnyExtensions();
		return CombinePaths(projectName, "Mods", dlcName);
	}

	private static void RemapCookedPluginsContentPaths(ProjectParams ProjectParams, DeploymentContext SC) {
		//We need to make sure content paths will be relative to ../../../ProjectRoot/Mods/DLCFilename/Content,
		//because that's what will be used in runtime as a content path for /DLCFilename/ mount point.
		//But both project and engine plugins are actually cooked by different paths:
		//Project plugins expect to be mounted under ../../../ProjectRoot/Plugins/DLCFilename/Content,
		//and engine plugins expect to be mounted under ../../../Engine/Plugins/DLCFilename/Content
		//Since changing runtime content path is pretty complicated and impractical,
		//we remap cooked filenames to match runtime expectations. Since cooked assets only reference other assets
		//using mount point-relative paths, it doesn't need any changes inside of the cooked assets
		//deploymentContext.RemapDirectories.Add(Tuple.Create());

		SC.RemapDirectories.Add(Tuple.Create(
			SC.GetStagedFileLocation(ProjectParams.DLCFile).Directory,
			new StagedDirectoryReference(GetPluginPathRelativeToStageRoot(ProjectParams))
		));
	}

	private void ModifyModules(ProjectParams ProjectParams, DeploymentContext SC)
	{
		foreach (var target in SC.StageTargets)
		{
			// Handle .modules files explicitly by nulling out their BuildId since DLC cooks for mods are supposed to have relaxed compatibility requirements
			var manifests = target.Receipt.BuildProducts.Where((Product => Product.Type == BuildProductType.RequiredResource && Product.Path.GetExtension() == ".modules" && Product.Path.IsUnderDirectory(ProjectParams.DLCFile.Directory)));
			foreach (var manifest in manifests)
			{
				if (!ModuleManifest.TryRead(manifest.Path, out var moduleManifestFile))
					throw new AutomationException(
						$"Unable to read .modules build file at {manifest.Path} for DLC staging");

				// Null out BuildId for Mod DLC cooks because they will be loaded by different game builds potentially
				// The game specifically allows SML as BuildId to be loaded by any game build
				moduleManifestFile.BuildId = "SML";

				var intermediateModuleFilePath = FileReference.Combine(ProjectParams.DLCFile.Directory, "Intermediate",
					"Staging", SC.FinalCookPlatform, manifest.Path.MakeRelativeTo(ProjectParams.DLCFile.Directory));
				var outputFilePath = SC.GetStagedFileLocation(manifest.Path);
				moduleManifestFile.Write(intermediateModuleFilePath);
				SC.StageFile(StagedFileType.NonUFS, intermediateModuleFilePath, outputFilePath);
			}
		}
	}
}

using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using AutomationTool;
using Tools.DotNETCommon;
using UnrealBuildTool;

namespace Alpakit.Automation
{
	public class FactoryGameParams
	{
		public bool CopyToGameDirectory;
		public bool StartGame;
		public string GameDirectory;
		public string LaunchGameURL;
	}

	public class PackagePlugin : BuildCommand
	{

		private static string GetGameLaunchURL(BuildCommand cmd)
		{
			var launchType = cmd.ParseParamValue("LaunchType", "");

			if (cmd.ParseParam("Steam") || launchType.Equals("Steam", StringComparison.InvariantCultureIgnoreCase))
			{
				return "steam://rungameid/526870";
			}

			if (cmd.ParseParam("EpicEA") || launchType.Equals("EpicEA", StringComparison.InvariantCultureIgnoreCase))
			{
				return "com.epicgames.launcher://apps/CrabEA?action=launch&silent=true";
			}

			if (cmd.ParseParam("EpicExp") || launchType.Equals("EpicExp", StringComparison.InvariantCultureIgnoreCase))
			{
				return "com.epicgames.launcher://apps/CrabTest?action=launch&silent=true";
			}

			throw new AutomationException("Game launching requires -LaunchType= or -Steam/EpicEA/EpicExp arguments");
		}

		private static void LaunchGame(BuildCommand cmd)
		{
			if (cmd.ParseParam("LaunchGame"))
			{
				var gameLaunchUrl = GetGameLaunchURL(cmd);
				System.Diagnostics.Process.Start(gameLaunchUrl);
			}
		}

		private static void CopyPluginToTheGameDir(string gameDir, FileReference projectFile, FileReference pluginFile,
			string stagingDir)
		{
			var modsDir = Path.Combine(gameDir, projectFile.GetFileNameWithoutAnyExtensions(), "Mods");
			var projectPluginsFolder =
				new DirectoryReference(Path.Combine(projectFile.Directory.ToString(), "Plugins"));
			var pluginRelativePath = pluginFile.Directory.MakeRelativeTo(projectPluginsFolder);

			var resultPluginDirectory = Path.Combine(modsDir, pluginRelativePath);
			if (DirectoryExists(resultPluginDirectory))
			{
				DeleteDirectory(resultPluginDirectory);
			}

			CreateDirectory(resultPluginDirectory);

			CopyDirectory_NoExceptions(stagingDir, resultPluginDirectory);
		}

		private static ProjectParams GetParams(BuildCommand cmd)
		{
			var projectFileName = cmd.ParseRequiredStringParam("Project");
			LogInformation(projectFileName);

			var pluginName = cmd.ParseRequiredStringParam("PluginName");
			var projectFile = new FileReference(projectFileName);

			var projectParameters = new ProjectParams(
				projectFile,
				cmd,
				ClientTargetPlatforms: new List<TargetPlatformDescriptor>
				{
					new TargetPlatformDescriptor(UnrealTargetPlatform.Win64)
				},
				ClientConfigsToBuild: new List<UnrealTargetConfiguration>
				{
					UnrealTargetConfiguration.Shipping
				},
				Build: false,
				Cook: true,
				Stage: true,
				Pak: true,
				Manifests: false,
				//Need this to allow engine content that wasn't cooked in the base game to be included in the PAK file 
				DLCIncludeEngineContent: true,
				DLCName: pluginName,
				AdditionalCookerOptions: "-CookOnlyPluginAndEngineContent",
				RunAssetNativization: false);

			projectParameters.ValidateAndLog();
			return projectParameters;
		}

		private static void TryUpdateModulesFile(string filePath, string targetBuildId)
		{
			try
			{
				var modulesObject = JsonObject.Read(new FileReference(filePath));
				var modulesSubObject = modulesObject.GetObjectField("Modules");

				using (var writer = new JsonWriter(filePath))
				{
					writer.WriteObjectStart();
					writer.WriteValue("BuildId", targetBuildId);

					writer.WriteObjectStart("Modules");
					foreach (var moduleName in modulesSubObject.KeyNames)
					{
						var modulePath = modulesSubObject.GetStringField(moduleName);
						writer.WriteValue(moduleName, modulePath);
					}

					writer.WriteObjectEnd();
					writer.WriteObjectEnd();
				}
			}
			catch (Exception ex)
			{
				throw new AutomationException("Failed to update modules file '{0}': {1}", filePath, ex.Message);
			}
		}

		private static void UpdateModulesBuildId(string stagingDir, string targetBuildId)
		{
			var foundFiles = FindFiles("*.modules", true, stagingDir);

			foreach (var modulesFile in foundFiles)
			{
				TryUpdateModulesFile(modulesFile, targetBuildId);
			}
		}

		private static IReadOnlyList<DeploymentContext> CreateDeploymentContexts(ProjectParams projectParams)
		{
			var deployContextList = new List<DeploymentContext>();
			if (!projectParams.NoClient)
			{
				deployContextList.AddRange(Project.CreateDeploymentContext(projectParams, false));
			}

			if (projectParams.DedicatedServer)
			{
				deployContextList.AddRange(Project.CreateDeploymentContext(projectParams, true));
			}

			return deployContextList;
		}

		private static void RemapCookedPluginsContentPaths(ProjectParams projectParams, IEnumerable<DeploymentContext> deploymentContexts) {
			foreach (var deploymentContext in deploymentContexts) {
				//We need to make sure content paths will be relative to ../../../ProjectRoot/Mods/DLCFilename/Content,
				//because that's what will be used in runtime as a content path for /DLCFilename/ mount point.
				//But both project and engine plugins are actually cooked by different paths:
				//Project plugins expect to be mounted under ../../../ProjectRoot/Plugins/DLCFilename/Content,
				//and engine plugins expect to be mounted under ../../../Engine/Plugins/DLCFilename/Content
				//Since changing runtime content path is pretty complicated and impractical,
				//we remap cooked filenames to match runtime expectations. Since cooked assets only reference other assets
				//using mount point-relative paths, it doesn't need any changes inside of the cooked assets
				//deploymentContext.RemapDirectories.Add(Tuple.Create());

				var projectName = projectParams.RawProjectPath.GetFileNameWithoutAnyExtensions();
				
				var sourceEngineDirectory = Path.Combine("Engine", "Plugins");
				var sourceProjectDirectory = Path.Combine(projectName, "Plugins");
				var destinationModsDir = Path.Combine(projectName, "Mods");
				deploymentContext.RemapDirectories.Add(Tuple.Create(
					new StagedDirectoryReference(sourceEngineDirectory), 
					new StagedDirectoryReference(destinationModsDir)));
				deploymentContext.RemapDirectories.Add(Tuple.Create(
					new StagedDirectoryReference(sourceProjectDirectory), 
					new StagedDirectoryReference(destinationModsDir)));
			}
		}

		public static void CopyBuildToStagingDirectory(ProjectParams Params, IReadOnlyList<DeploymentContext> deploymentContexts) {
			var platformCares = Params.ClientTargetPlatformInstances[0].RequiresPak(Params);
			var requiresPak = platformCares == Platform.PakType.Always || (Params.Pak && platformCares != Platform.PakType.Never);
			
			if (requiresPak || (Params.Stage && !Params.SkipStage)) {
				LogInformation("********** STAGE COMMAND STARTED **********");

				// clean the staging directories first
				foreach (var sc in deploymentContexts) {
					Project.CreateStagingManifest(Params, sc);
					Project.CleanStagingDirectory(Params, sc);
				}

				foreach (var sc in deploymentContexts) {
					Project.ApplyStagingManifest(Params, sc);
				}

				LogInformation("********** STAGE COMMAND COMPLETED **********");
			}
		}

		private static void PackagePluginProject(IEnumerable<DeploymentContext> deploymentContexts,
			string workingBuildId)
		{
			foreach (var deploymentContext in deploymentContexts)
			{
				//Update .modules files build id to match game's one before packaging
				UpdateModulesBuildId(deploymentContext.StageDirectory.ToString(), workingBuildId);
			}
		}

		private static string GetPluginPathRelativeToStageRoot(ProjectParams projectParams, DeploymentContext SC)
		{
			var projectName = projectParams.RawProjectPath.GetFileNameWithoutAnyExtensions();
			var dlcName = projectParams.DLCFile.GetFileNameWithoutAnyExtensions();
			return Path.Combine(projectName, "Mods", dlcName);
		}

		private static void ArchivePluginProject(ProjectParams projectParams,
			IEnumerable<DeploymentContext> deploymentContexts)
		{
			var baseArchiveDirectory = CombinePaths(Path.GetDirectoryName(projectParams.RawProjectPath.ToString()),
				"Saved", "ArchivedPlugins");

			foreach (var deploymentContext in deploymentContexts)
			{
				var stageRootDirectory = deploymentContext.StageDirectory;
				var relativePluginPath = GetPluginPathRelativeToStageRoot(projectParams, deploymentContext);
				var stagePluginDirectory = Path.Combine(stageRootDirectory.ToString(), relativePluginPath);

				var archiveDirectory = Path.Combine(baseArchiveDirectory, deploymentContext.FinalCookPlatform);
				CreateDirectory(archiveDirectory);

				var zipFilePath = Path.Combine(archiveDirectory,
					projectParams.DLCFile.GetFileNameWithoutAnyExtensions() + ".zip");
				if (FileExists(zipFilePath))
				{
					DeleteFile(zipFilePath);
				}

				ZipFile.CreateFromDirectory(stagePluginDirectory, zipFilePath);
			}
		}

		private static void DeployPluginProject(ProjectParams projectParams,
			IEnumerable<DeploymentContext> deploymentContexts, FactoryGameParams factoryGameParams)
		{
			foreach (var deploymentContext in deploymentContexts)
			{
				if (factoryGameParams.CopyToGameDirectory &&
				    deploymentContext.FinalCookPlatform == "WindowsNoEditor")
				{
					var stageRootDirectory = deploymentContext.StageDirectory;
					var relativePluginPath = GetPluginPathRelativeToStageRoot(projectParams, deploymentContext);
					var stagePluginDirectory = Path.Combine(stageRootDirectory.ToString(), relativePluginPath);

					if (factoryGameParams.GameDirectory == null)
					{
						throw new AutomationException(
							"-CopyToGameDirectory was specified, but no game directory path has been provided");
					}
					
					CopyPluginToTheGameDir(factoryGameParams.GameDirectory, projectParams.RawProjectPath,
						projectParams.DLCFile, stagePluginDirectory);
				}
			}

			if (factoryGameParams.StartGame)
			{
				System.Diagnostics.Process.Start(factoryGameParams.LaunchGameURL);
			}
		}

		private static void CleanStagingDirectories(IEnumerable<DeploymentContext> deploymentContexts)
		{
			foreach (var deploymentContext in deploymentContexts)
			{
				if (DirectoryExists(deploymentContext.StageDirectory.ToString()))
				{
					DeleteDirectory(deploymentContext.StageDirectory);
				}
			}
		}

		public override void ExecuteBuild()
        {
            string gameDir = ParseOptionalStringParam("GameDir");
            if (gameDir != null)
			{
				var bootstrapExePath = Path.Combine(gameDir, "FactoryGame.exe");
				if (!FileExists(bootstrapExePath))
				{
					throw new AutomationException("Provided -GameDir is invalid: '{0}'", gameDir);
				}
			}

			var factoryGameParams = new FactoryGameParams
			{
				GameDirectory = gameDir,
				StartGame = ParseParam("LaunchGame"),
				CopyToGameDirectory = ParseParam("CopyToGameDir")
			};
			if (factoryGameParams.StartGame)
			{
				factoryGameParams.LaunchGameURL = GetGameLaunchURL(this);
			}

			var projectParams = GetParams(this);

			Project.Cook(projectParams);
			var deploymentContexts = CreateDeploymentContexts(projectParams);
			RemapCookedPluginsContentPaths(projectParams, deploymentContexts);

			try
			{
				CopyBuildToStagingDirectory(projectParams, deploymentContexts);
				PackagePluginProject(deploymentContexts, "SML");
				ArchivePluginProject(projectParams, deploymentContexts);
				DeployPluginProject(projectParams, deploymentContexts, factoryGameParams);
			}
			finally
			{
				//Clean staging directories because they confuse cooking commandlet and UBT
				CleanStagingDirectories(deploymentContexts);
			}

			LaunchGame(this);
		}
	}
}
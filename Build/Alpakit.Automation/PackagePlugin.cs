using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Threading;
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

		private static string GetGameLaunchURL(string launchType)
		{
			switch (launchType)
			{
				case "Steam":
					return "steam://rungameid/526870";
				case "SteamDS":
					return "steam://rungameid/1690800";
				case "EpicEA":
					return "com.epicgames.launcher://apps/CrabEA?action=launch&silent=true";
				case "EpicExp":
					return "com.epicgames.launcher://apps/CrabTest?action=launch&silent=true";
				case "EpicDS":
					return "com.epicgames.launcher://apps/CrabDedicatedServer?action=launch&silent=true";
				default:
					throw new AutomationException("Invalid Launch Type {0}", launchType);
			}
		}

		private static void CopyPluginToTheGameDir(string gameDir, FileReference projectFile, FileReference pluginFile,
			string stagingDir)
		{
			var modsDir = Path.Combine(gameDir, projectFile.GetFileNameWithoutAnyExtensions(), "Mods");
			var projectPluginsFolder = new DirectoryReference(Path.Combine(projectFile.Directory.ToString(), "Plugins"));
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
			
			var targets = cmd.ParseParamValues("PluginTarget");
			Console.WriteLine(targets);

			var ClientTargetPlatforms = new List<TargetPlatformDescriptor>();
			var ServerTargetPlatforms = new List<TargetPlatformDescriptor>();

			foreach (var target in targets)
			{
				// Platform_Type
				var split = target.Split('_');
				var platformName = split[0];
				var targetType = split.Length > 1 ? split[1] : null;

				UnrealTargetPlatform platform;
				if (!UnrealTargetPlatform.TryParse(platformName, out platform))
				{
					throw new AutomationException("Invalid platform name {0}", platformName);
				}
				TargetPlatformDescriptor platformDescriptor = new TargetPlatformDescriptor(platform);


				if (targetType == "Client" || string.IsNullOrWhiteSpace(targetType))
				{
					ClientTargetPlatforms.Add(platformDescriptor);
				}
				else if (targetType == "Server")
				{
					ServerTargetPlatforms.Add(platformDescriptor);
				}
				else
				{
					throw new AutomationException("Invalid target type {0}", targetType);
				}
			}

			var projectFile = new FileReference(projectFileName);

			bool Client = false;
			bool DedicatedServer = false;

			if (ClientTargetPlatforms.Count > 0)
					Client = true;

			if (ServerTargetPlatforms.Count > 0)
					DedicatedServer = true;

			var projectParameters = new ProjectParams(
				projectFile,
				cmd,
				
				ClientTargetPlatforms: ClientTargetPlatforms,
				ClientConfigsToBuild: new List<UnrealTargetConfiguration>
				{
					UnrealTargetConfiguration.Shipping
				},
				NoClient: !Client,
				
				ServerTargetPlatforms: ServerTargetPlatforms,
				ServerConfigsToBuild: new List<UnrealTargetConfiguration>
				{
					UnrealTargetConfiguration.Shipping
				},
				DedicatedServer: DedicatedServer,

				Build: false,
				Cook: true,
				Stage: true,
				Pak: true,
				Manifests: false,
				//Need this to allow engine content that wasn't cooked in the base game to be included in the PAK file 
				DLCIncludeEngineContent: true,
				DLCName: pluginName,
				AdditionalCookerOptions: "-CookOnlyPluginAndEngineContent",
				RunAssetNativization: false
			);

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

		private void ArchivePluginProject(ProjectParams projectParams,
			IEnumerable<DeploymentContext> deploymentContexts)
		{
			var baseArchiveDirectory = CombinePaths(Path.GetDirectoryName(projectParams.RawProjectPath.ToString()),
				"Saved", "ArchivedPlugins");

            var archiveDirectory = Path.Combine(baseArchiveDirectory, projectParams.DLCFile.GetFileNameWithoutAnyExtensions());
            CreateDirectory(archiveDirectory);

            var mergeArchive = ParseParam("MergeArchive");

			var mergedDirectory = Path.Combine(archiveDirectory, "merged");
			var mergedArchive = Path.Combine(archiveDirectory, projectParams.DLCFile.GetFileNameWithoutAnyExtensions() + ".zip");

            if (mergeArchive)
            {
                CreateDirectory(mergedDirectory);
				DeleteDirectoryContents(mergedDirectory);
			}

            foreach (var deploymentContext in deploymentContexts)
			{
				var stageRootDirectory = deploymentContext.StageDirectory;
				var relativePluginPath = GetPluginPathRelativeToStageRoot(projectParams, deploymentContext);
				var stagePluginDirectory = Path.Combine(stageRootDirectory.ToString(), relativePluginPath);

				var zipFilePath = Path.Combine(archiveDirectory,
					projectParams.DLCFile.GetFileNameWithoutAnyExtensions() + "-" + deploymentContext.FinalCookPlatform + ".zip");
				if (FileExists(zipFilePath))
				{
					DeleteFile(zipFilePath);
				}

				ZipFile.CreateFromDirectory(stagePluginDirectory, zipFilePath);

				if (mergeArchive)
				{
					CopyDirectory_NoExceptions(stagePluginDirectory, Path.Combine(mergedDirectory, deploymentContext.FinalCookPlatform));
				}
			}

			if (mergeArchive)
            {
	            if (FileExists(mergedArchive))
	            {
		            DeleteFile(mergedArchive);
	            }
                ZipFile.CreateFromDirectory(mergedDirectory, mergedArchive);
				DeleteDirectory(mergedDirectory);
            }
		}

		private static void DeployPluginProject(ProjectParams projectParams,
			IEnumerable<DeploymentContext> deploymentContexts, Dictionary<string, FactoryGameParams> factoryGameTargetParams)
		{
			foreach (var deploymentContext in deploymentContexts)
			{
				FactoryGameParams factoryGameParams;
				if (factoryGameTargetParams.TryGetValue(deploymentContext.FinalCookPlatform, out factoryGameParams))
				{
					if (factoryGameParams.CopyToGameDirectory)
					{
						var stageRootDirectory = deploymentContext.StageDirectory;
						var relativePluginPath = GetPluginPathRelativeToStageRoot(projectParams, deploymentContext);
						var stagePluginDirectory = Path.Combine(stageRootDirectory.ToString(), relativePluginPath);

						if (factoryGameParams.GameDirectory == null)
						{
							throw new AutomationException(
									"-{0}_CopyToGameDirectory was specified, but no game directory path has been provided", deploymentContext.FinalCookPlatform);
						}

						CopyPluginToTheGameDir(factoryGameParams.GameDirectory, projectParams.RawProjectPath,
								projectParams.DLCFile, stagePluginDirectory);
					}

					if (factoryGameParams.StartGame)
					{
						System.Diagnostics.Process.Start(factoryGameParams.LaunchGameURL);
						Thread.Sleep(5000);
					}
				}
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
			var projectParams = GetParams(this);

			Project.Cook(projectParams);
			var deploymentContexts = CreateDeploymentContexts(projectParams);
			RemapCookedPluginsContentPaths(projectParams, deploymentContexts);

            var factoryGameTargetParams = new Dictionary<string, FactoryGameParams>();

            foreach (var deploymentContext in deploymentContexts)
            {
                var factoryGameParams = new FactoryGameParams
                {
                    StartGame = ParseParam(string.Format("{0}_LaunchGame", deploymentContext.FinalCookPlatform)),
                    CopyToGameDirectory = ParseParam(string.Format("{0}_CopyToGameDir", deploymentContext.FinalCookPlatform))
                };
                if (factoryGameParams.CopyToGameDirectory)
                {
                    string gameDir = ParseOptionalStringParam(string.Format("{0}_GameDir", deploymentContext.FinalCookPlatform));
                    if (gameDir == null)
                    {
                        throw new AutomationException("-{0}_CopyToGameDirectory was specified, but no game directory path has been provided", deploymentContext.FinalCookPlatform);
                    }
                    var bootstrapClientExePath = Path.Combine(gameDir, "FactoryGame.exe");
                    var bootstrapServerExePath = Path.Combine(gameDir, "FactoryServer.exe");
                    var bootstrapServerLinuxPath = Path.Combine(gameDir, "FactoryServer.sh");
                    if (!FileExists(bootstrapClientExePath) && !FileExists(bootstrapServerExePath) && !FileExists(bootstrapServerLinuxPath))
                    {
                        throw new AutomationException("Provided -{0}_GameDir is invalid: '{1}'", deploymentContext.FinalCookPlatform, gameDir);
                    }
                    factoryGameParams.GameDirectory = gameDir;
                }
                if (factoryGameParams.StartGame)
                {
                    factoryGameParams.LaunchGameURL = GetGameLaunchURL(ParseRequiredStringParam(string.Format("{0}_LaunchType", deploymentContext.FinalCookPlatform)));
                }

                factoryGameTargetParams.Add(deploymentContext.FinalCookPlatform, factoryGameParams);
            }

			try
			{
				CopyBuildToStagingDirectory(projectParams, deploymentContexts);
				PackagePluginProject(deploymentContexts, "SML");
				ArchivePluginProject(projectParams, deploymentContexts);
				DeployPluginProject(projectParams, deploymentContexts, factoryGameTargetParams);
			}
			finally
			{
                //Clean staging directories because they confuse cooking commandlet and UBT
                CleanStagingDirectories(deploymentContexts);
            }
		}
	}
}
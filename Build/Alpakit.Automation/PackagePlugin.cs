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
		public string GameBuildId;
		public bool CopyToGameDirectory;
		public bool StartGame;
		public string GameDirectory;
		public string LaunchGameURL;
	}

	public class PackagePlugin : BuildCommand {

		private static string GetGameLaunchURL(BuildCommand cmd) {
		    var launchType = cmd.ParseRequiredStringParam("LaunchType");
		    
		    if (cmd.ParseParam("Steam") || launchType.Equals("Steam", StringComparison.InvariantCultureIgnoreCase)) {
			    return "steam://rungameid/526870";
		    }
		    
		    if (cmd.ParseParam("EpicEA") || launchType.Equals("EpicEA", StringComparison.InvariantCultureIgnoreCase)) {
			    return "com.epicgames.launcher://apps/CrabEA?action=launch&silent=true";
		    }
		    
		    if (cmd.ParseParam("EpicExp") || launchType.Equals("EpicExp", StringComparison.InvariantCultureIgnoreCase)) {
			    return "com.epicgames.launcher://apps/CrabTest?action=launch&silent=true";
		    }
		    throw new AutomationException("Game launching requires -LaunchType= or -Steam/EpicEA/EpicExp arguments");
	    }

	    private static void LaunchGame(BuildCommand cmd) {
		    if (cmd.ParseParam("LaunchGame")) {
			    var gameLaunchUrl = GetGameLaunchURL(cmd);
			    System.Diagnostics.Process.Start(gameLaunchUrl);
		    }
	    }

	    private static void CopyPluginToTheGameDir(string gameDir, FileReference projectFile, FileReference pluginFile, string stagingDir) {
		    var modsDir = Path.Combine(gameDir, projectFile.GetFileNameWithoutAnyExtensions(), "Mods");
		    var projectPluginsFolder = new DirectoryReference(Path.Combine(projectFile.Directory.ToString(), "Plugins"));
		    var pluginRelativePath = pluginFile.Directory.MakeRelativeTo(projectPluginsFolder);

		    var resultPluginDirectory = Path.Combine(modsDir, pluginRelativePath);
		    if (DirectoryExists(resultPluginDirectory)) {
			    DeleteDirectory(resultPluginDirectory);
		    }

		    CreateDirectory(resultPluginDirectory);

		    CopyDirectory_NoExceptions(stagingDir, resultPluginDirectory);
	    }

	    private static ProjectParams GetParams(BuildCommand cmd, string basedOnReleaseName) {
		    var projectFileName = cmd.ParseRequiredStringParam("Project");
		    LogInformation(projectFileName);
		    
		    var pluginName = cmd.ParseRequiredStringParam("PluginName");
			var projectFile = new FileReference(projectFileName);

			var projectParameters = new ProjectParams(
				projectFile,
				cmd,
				ClientTargetPlatforms: new List<TargetPlatformDescriptor> {
					new TargetPlatformDescriptor(UnrealTargetPlatform.Win64)
				},
				ClientConfigsToBuild: new List<UnrealTargetConfiguration> {
					UnrealTargetConfiguration.Shipping	
				},
				Build: false,
				Cook: true,
				Stage: true,
				Pak: true,
				Manifests: false,
				//Need this to allow engine content that wasn't cooked in the base game to be included in the PAK file 
				DLCIncludeEngineContent: true,
				BasedOnReleaseVersion: basedOnReleaseName,
				DLCName: pluginName,
				RunAssetNativization: false);

			projectParameters.ValidateAndLog();
			return projectParameters;
		}

	    private static string RetrieveBuildIdFromGame(string gameDir) {
		    var versionFilePath = Path.Combine(gameDir, "Engine", "Binaries", "Win64", "UE4-Win64-Shipping.version");
		    if (!FileExists(versionFilePath)) {
			    throw new AutomationException("Cannot find game version file at '{0}'", versionFilePath);
		    }

		    try {
			    var versionObject = JsonObject.Read(new FileReference(versionFilePath));
			    var buildId = versionObject.GetStringField("BuildId");
			    return buildId;
		    } catch (Exception ex) {
			    throw new AutomationException("Failed to parse version JSON '{0}': {1}", versionFilePath, ex.Message);
		    }
	    }

	    private static void TryUpdateModulesFile(string filePath, string targetBuildId) {
		    try {
			    var modulesObject = JsonObject.Read(new FileReference(filePath));
			    var modulesSubObject = modulesObject.GetObjectField("Modules");

			    using (var writer = new JsonWriter(filePath)) {
				    writer.WriteObjectStart();
				    writer.WriteValue("BuildId", targetBuildId);

				    writer.WriteObjectStart("Modules");
				    foreach (var moduleName in modulesSubObject.KeyNames) {
					    var modulePath = modulesSubObject.GetStringField(moduleName);
					    writer.WriteValue(moduleName, modulePath);
				    }

				    writer.WriteObjectEnd();
				    writer.WriteObjectEnd();
			    }
		    } catch (Exception ex) {
			    throw new AutomationException("Failed to update modules file '{0}': {1}", filePath, ex.Message);
		    }
	    }
	    
	    private static void UpdateModulesBuildId(string stagingDir, string targetBuildId) {
		    var foundFiles = FindFiles("*.modules", true, stagingDir);

		    foreach (var modulesFile in foundFiles) {
			    TryUpdateModulesFile(modulesFile, targetBuildId);
		    }
	    }

	    private static IReadOnlyList<DeploymentContext> CreateDeploymentContexts(ProjectParams projectParams) {
		    var deployContextList = new List<DeploymentContext>();
		    if (!projectParams.NoClient) {
			    deployContextList.AddRange(Project.CreateDeploymentContext(projectParams, false));
		    }
		    if (projectParams.DedicatedServer) {
			    deployContextList.AddRange(Project.CreateDeploymentContext(projectParams, true));
		    }
		    return deployContextList;
	    }

	    private static void PackagePluginProject(IEnumerable<DeploymentContext> deploymentContexts, string workingBuildId) {
		    foreach (var deploymentContext in deploymentContexts) {
			    //Update .modules files build id to match game's one before packaging
			    UpdateModulesBuildId(deploymentContext.StageDirectory.ToString(), workingBuildId);
		    }
	    }

	    private static string GetPluginPathRelativeToStageRoot(ProjectParams projectParams, DeploymentContext SC) {
		    var dlcFile = projectParams.DLCFile;
		    if (dlcFile.IsUnderDirectory(SC.ProjectRoot)) {
			    var pluginFolderRelativeToProjectRoot = dlcFile.Directory.MakeRelativeTo(SC.ProjectRoot);
			    return Path.Combine(projectParams.ShortProjectName, pluginFolderRelativeToProjectRoot);
		    } 
		    
		    if (dlcFile.IsUnderDirectory(SC.EngineRoot)) {
			    var pluginFolderRelativeToEngineRoot = dlcFile.Directory.MakeRelativeTo(SC.EngineRoot);
			    return Path.Combine("Engine", pluginFolderRelativeToEngineRoot);
		    }

		    throw new AutomationException("Plugin file path is not relative to a valid engine/project path: '{0}'",
			    dlcFile.ToString());
	    }

	    private static void ArchivePluginProject(ProjectParams projectParams, IEnumerable<DeploymentContext> deploymentContexts) {
		    var baseArchiveDirectory = CombinePaths(Path.GetDirectoryName(projectParams.RawProjectPath.ToString()), "Saved", "ArchivedPlugins");
		    
		    foreach (var deploymentContext in deploymentContexts) {
			    var stageRootDirectory = deploymentContext.StageDirectory;
			    var relativePluginPath = GetPluginPathRelativeToStageRoot(projectParams, deploymentContext);
			    
			    var stagePluginDirectory = Path.Combine(stageRootDirectory.ToString(), relativePluginPath);

			    var archiveDirectory = Path.Combine(baseArchiveDirectory, deploymentContext.FinalCookPlatform);
			    CreateDirectory(archiveDirectory);
			    
			    var zipFilePath = Path.Combine(archiveDirectory, projectParams.DLCFile.GetFileNameWithoutAnyExtensions() + ".zip");
			    if (FileExists(zipFilePath)) {
				    DeleteFile(zipFilePath);
			    }
			    ZipFile.CreateFromDirectory(stagePluginDirectory, zipFilePath);
		    }
	    }

	    private static void DeployPluginProject(ProjectParams projectParams, IEnumerable<DeploymentContext> deploymentContexts, FactoryGameParams factoryGameParams) {
		    foreach (var deploymentContext in deploymentContexts) {
			    if (factoryGameParams.CopyToGameDirectory &&
			        deploymentContext.FinalCookPlatform == "WindowsNoEditor") {
				   CopyPluginToTheGameDir(factoryGameParams.GameDirectory, projectParams.RawProjectPath, 
					   projectParams.DLCFile, deploymentContext.StageDirectory.ToString());
			    }
		    }

		    if (factoryGameParams.StartGame) {
			    System.Diagnostics.Process.Start(factoryGameParams.LaunchGameURL);
		    }
	    }

	    private static void CleanStagingDirectories(IEnumerable<DeploymentContext> deploymentContexts) {
		    foreach (var deploymentContext in deploymentContexts) {
			    if (DirectoryExists(deploymentContext.StageDirectory.ToString())) {
				    DeleteDirectory(deploymentContext.StageDirectory);
			    }
		    }
	    }

		public override void ExecuteBuild() {
			var gameDir = ParseRequiredStringParam("GameDir");
			var bootstrapExePath = Path.Combine(gameDir, "FactoryGame.exe");
			if (!FileExists(bootstrapExePath)) {
				throw new AutomationException("Provided -GameDir is invalid: '{0}'", gameDir);
			}

			const string releaseName = "FactoryGame_Release";
			var gameBuildVersion = RetrieveBuildIdFromGame(gameDir);
			
			LogInformation("Game Build Id: {0}", gameBuildVersion);
			LogInformation("Target Release: {0}", releaseName);

			var factoryGameParams = new FactoryGameParams {
				GameBuildId = releaseName,
				GameDirectory = gameDir,
				StartGame = ParseParam("LaunchGame"),
				CopyToGameDirectory = ParseParam("CopyToGameDir")
			};
			if (factoryGameParams.StartGame) {
				factoryGameParams.LaunchGameURL = GetGameLaunchURL(this);
			}
			
			var projectParams = GetParams(this, releaseName);

			Project.Cook(projectParams);
			var deploymentContexts = CreateDeploymentContexts(projectParams);

			try {
				Project.CopyBuildToStagingDirectory(projectParams);
				PackagePluginProject(deploymentContexts, gameBuildVersion);
				ArchivePluginProject(projectParams, deploymentContexts);
				DeployPluginProject(projectParams, deploymentContexts, factoryGameParams);
			} finally {
				//Clean staging directories because they confuse cooking commandlet and UBT
				CleanStagingDirectories(deploymentContexts);
			}

			LaunchGame(this);
		}
    }
}
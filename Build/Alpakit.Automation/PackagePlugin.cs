using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Text;
using AutomationTool;
using Tools.DotNETCommon;
using UnrealBuildTool;

namespace Alpakit.Automation
{
    public class PackagePlugin : BuildCommand {

	    private static string GetGameLaunchURL(BuildCommand cmd) {
		    var launchType = cmd.ParseOptionalStringParam("LaunchType");
		    
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

	    private static void CopyPluginToTheGameDir(BuildCommand cmd, FileReference projectFile, FileReference pluginFile, string stagingDir) {
		    if (cmd.ParseParam("CopyToGameDir")) {
			    var gameDir = cmd.ParseRequiredStringParam("GameDir");
			    var bootstrapExePath = Path.Combine(gameDir, "FactoryGame.exe");
			    if (!FileExists(bootstrapExePath)) {
				    throw new AutomationException("Provided -GameDir is invalid: '{0}'", gameDir);
			    }
			    
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
	    }
	    
	    private static ProjectParams GetParams(BuildCommand cmd, string projectFileName, string basedOnReleaseName, out FileReference pluginFile) {
		    // Get the plugin filename
			var pluginPath = cmd.ParseRequiredStringParam("PluginPath");

			// Check it exists
			pluginFile = new FileReference(pluginPath);
			if (!FileReference.Exists(pluginFile)) {
				throw new AutomationException("Plugin '{0}' not found", pluginFile.FullName);
			}
			
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
				DLCName: pluginFile.GetFileNameWithoutAnyExtensions(),
				RunAssetNativization: false);

			projectParameters.ValidateAndLog();
			return projectParameters;
		}

		public override void ExecuteBuild() {
			var projectFileName = ParseParamValue("Project");
			LogInformation(projectFileName);

			const string releaseName = "FactoryGame_Release";

			ProjectParams projectParams = GetParams(this, projectFileName, releaseName, out var pluginFile);
			FileReference projectFile = new FileReference(projectFileName);

			//Get path to where the plugin was staged
			var platformStageDirectory = Path.Combine(projectParams.BaseStageDirectory, "WindowsNoEditor");
			
			//Cleanup Staged folder because it confuses Cooker of plugin type and location
			//TODO honestly sounds like a bug in Cooker which should probably ignore Saved/
			if (Directory.Exists(platformStageDirectory)) {
				Directory.Delete(platformStageDirectory, true);
			}
			
			Project.Cook(projectParams);
			Project.CopyBuildToStagingDirectory(projectParams);
			Project.Package(projectParams);
			Project.Archive(projectParams);
			Project.Deploy(projectParams);
			
			var stagedPluginDir = Path.Combine(platformStageDirectory, 
				projectFile.GetFileNameWithoutAnyExtensions(), 
				pluginFile.Directory.MakeRelativeTo(projectFile.Directory));

			var packagedBuildsDirectory = Path.Combine(pluginFile.Directory.ToString(), "Saved", "PackagedPlugins");
			Directory.CreateDirectory(packagedBuildsDirectory);
			var zipFilePath = Path.Combine(packagedBuildsDirectory, pluginFile.GetFileNameWithoutAnyExtensions()) + ".zip";

			//Package staged directory into the zip
			File.Delete(zipFilePath);
			ZipFile.CreateFromDirectory(stagedPluginDir, zipFilePath);
			
			CopyPluginToTheGameDir(this, projectFile, pluginFile, stagedPluginDir);
			LaunchGame(this);
		}
    }
}
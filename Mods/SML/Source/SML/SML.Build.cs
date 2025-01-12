// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;
using System;
using System.Diagnostics;
using EpicGames.Core;
using Microsoft.Extensions.Logging;

public class SML : ModuleRules
{
    public SML(ReadOnlyTargetRules Target) : base(Target)
    {
        CppStandard = CppStandardVersion.Cpp20;
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;

        //SML transitive dependencies
        PublicDependencyModuleNames.AddRange(new[] {
            "Json",
            "Projects",
            "NetCore",
            "EnhancedInput",
            "GameplayTags"
        });
        
        PrivateDependencyModuleNames.AddRange(new[] {
            "RenderCore",
            "EngineSettings"
        });
        
        PublicDependencyModuleNames.AddRange(new[] {"FactoryGame"});

        //FactoryGame transitive dependencies
        PublicDependencyModuleNames.AddRange(new[] {
            "Core", "CoreUObject",
            "Engine",
            "InputCore",
            "SlateCore", "Slate", "UMG",
        });

        if (Target.bBuildEditor) {
            PublicDependencyModuleNames.Add("UnrealEd");
            PrivateDependencyModuleNames.Add("MainFrame");
        }

        var ThirdPartyFolder = Path.Combine(ModuleDirectory, "../../ThirdParty");
        PublicIncludePaths.Add(Path.Combine(ThirdPartyFolder, "include"));

        var PlatformName = Target.Platform.ToString();
        var LibraryFolder = Path.Combine(ThirdPartyFolder, PlatformName);

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            // https://github.com/satisfactorymodding/funchook/tree/4074c90c1bb4de294eb1dc2519c5830ed96739c0
            PublicAdditionalLibraries.Add(Path.Combine(LibraryFolder, "funchook.lib"));
            // funchook will additionally build distorm 
            PublicAdditionalLibraries.Add(Path.Combine(LibraryFolder, "distorm.lib"));
            // funchook uses GetMappedFileNameA from psapi
            PublicSystemLibraries.Add("psapi.lib");

            // https://github.com/satisfactorymodding/AssemblyAnalyzer/tree/e08ec4402b6e016a9b7aa59ab8c82dd0840e8f98
            PublicAdditionalLibraries.Add(Path.Combine(LibraryFolder, "AssemblyAnalyzer.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(LibraryFolder, "Zydis.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(LibraryFolder, "Zycore.lib"));
        } else if (Target.Platform == UnrealTargetPlatform.Linux) {
            // https://github.com/satisfactorymodding/funchook/tree/4074c90c1bb4de294eb1dc2519c5830ed96739c0
            // Built on windows using the Unreal Engine cross-compile clang toolchain
            PublicAdditionalLibraries.Add(Path.Combine(LibraryFolder, "libfunchook.a"));
            // funchook will additionally build distorm
            PublicAdditionalLibraries.Add(Path.Combine(LibraryFolder, "libdistorm.a"));

            // https://github.com/satisfactorymodding/AssemblyAnalyzer/tree/e08ec4402b6e016a9b7aa59ab8c82dd0840e8f98
            PublicAdditionalLibraries.Add(Path.Combine(LibraryFolder, "libAssemblyAnalyzer.a"));
            PublicAdditionalLibraries.Add(Path.Combine(LibraryFolder, "libZydis.a"));
            PublicAdditionalLibraries.Add(Path.Combine(LibraryFolder, "libZycore.a"));
        }

        AddFactoryGameInfo();
        AddSMLInfo();
    }

    private void AddFactoryGameInfo()
    {
        const string factoryGameVersionRelativePath = "Source/FactoryGame/currentVersion.txt";

        var FactoryGameVersionFile = FileReference.Combine(Target.ProjectFile!.Directory, factoryGameVersionRelativePath);

        // Fallback for when there is no current version file
        if (!File.Exists(FactoryGameVersionFile.FullName))
        {
	        PrivateDefinitions.Add("FACTORYGAME_VERSION=0");
	        PrivateDefinitions.Add("SML_ALLOW_PATCHES_IN_EDITOR=1");
	        PrivateDefinitions.Add("ENABLE_MOD_LOADING_IN_EDITOR=1");
	        return;
        }

        var FactoryGameVersion = File.ReadAllText(FactoryGameVersionFile.FullName);
        PrivateDefinitions.Add($"FACTORYGAME_VERSION={FactoryGameVersion}");
        PrivateDefinitions.Add("SML_ALLOW_PATCHES_IN_EDITOR=0");
    }

    private void AddSMLInfo()
    {
        // Get SML version from SML.uplugin
        var SMLPluginFile = FileReference.Combine(new DirectoryReference(PluginDirectory!), "SML.uplugin");
        var SMLPlugin = PluginDescriptor.FromFile(SMLPluginFile);
        PrivateDefinitions.Add($"SML_VERSION=\"{SMLPlugin.VersionName}\"");
        
        //Collect build metadata from the environment and pass it to C++
        var CurrentBranch = Environment.GetEnvironmentVariable("BRANCH_NAME");
        var BuildId = Environment.GetEnvironmentVariable("BUILD_NUMBER");

        var GithubActionsWorkflow = Environment.GetEnvironmentVariable("GITHUB_WORKFLOW");
        if (!string.IsNullOrEmpty(GithubActionsWorkflow)) {
            CurrentBranch = Environment.GetEnvironmentVariable("GITHUB_REF_NAME");
            BuildId = Environment.GetEnvironmentVariable("GITHUB_RUN_NUMBER");
        }

        if (CurrentBranch == null) {
            RetrieveHeadBranchAndCommitFromGit(Target.ProjectFile!.Directory, out CurrentBranch, out BuildId);
            if (BuildId is { Length: > 8 }) {
                BuildId = BuildId[..8];
            }
        }
        if (CurrentBranch == null || BuildId == null) return;
        var BuildMetadataString = CurrentBranch == "master" ? BuildId : $"{CurrentBranch}.{BuildId}";
        PrivateDefinitions.Add($"SML_BUILD_METADATA=\"{BuildMetadataString}\"");
    }

    private void RetrieveHeadBranchAndCommitFromGit(DirectoryReference RootDir, out string BranchName, out string CommitRef) {
        BranchName = null;
        CommitRef = null;
            
        // First try running git
        try
        {
            var BranchNameProcess = Process.Start(new ProcessStartInfo("git", "rev-parse --abbrev-ref HEAD")
            {
                WorkingDirectory = RootDir.FullName,
                RedirectStandardOutput = true,
                RedirectStandardError = true,
            });
            if (BranchNameProcess != null)
            {
                BranchNameProcess.WaitForExit();
                if (BranchNameProcess.ExitCode == 0)
                    BranchName = BranchNameProcess.StandardOutput.ReadToEnd().Trim();
                else
                    Target.Logger.LogWarning("Failed to run git to retrieve branch name: exit code {0}. Falling back to checking .git folder", BranchNameProcess.ExitCode);
            }
            else
            {
                Target.Logger.LogWarning("Failed to run git to retrieve branch name: Failed to create git process. Falling back to checking .git folder");
            }
        } catch (Exception Ex) { 
            Target.Logger.LogWarning("Failed to run git to retrieve branch name: {0}. Falling back to checking .git folder", Ex.Message);
        }

        try
        {
            var CommitProcess = Process.Start(new ProcessStartInfo("git", "rev-parse HEAD")
            {
                WorkingDirectory = RootDir.FullName,
                RedirectStandardOutput = true,
                RedirectStandardError = true,
            });
            if (CommitProcess != null)
            {
                CommitProcess.WaitForExit();
                if (CommitProcess.ExitCode == 0)
                    CommitRef = CommitProcess.StandardOutput.ReadToEnd().Trim();
                else
                    Target.Logger.LogWarning("Failed to run git to retrieve commit: exit code {0}. Falling back to checking .git folder", CommitProcess.ExitCode);
            }
            else
            {
                Target.Logger.LogWarning("Failed to run git to retrieve commit: Failed to create git process. Falling back to checking .git folder");
            }
        } catch (Exception Ex) {
            Target.Logger.LogWarning("Failed to run git to retrieve commit: {0}. Falling back to checking .git folder", Ex.Message);
        }

        if (CommitRef != null && BranchName != null) return;

        // If either was not found, try parsing the HEAD file manually
        var GitRepository = Path.Combine(RootDir.FullName, ".git");
        if (!Directory.Exists(GitRepository)) {
            return;
        }
        var GitHeadFile = Path.Combine(GitRepository, "HEAD");
        if (!File.Exists(GitHeadFile)) {
            return;
        }

        try {
            var HeadFileContents = File.ReadAllText(GitHeadFile).Replace("\n", "");

            //It is a normal HEAD ref, so its name should be equal to the local branch name
            if (HeadFileContents.StartsWith("ref: refs/heads/")) {
                BranchName = HeadFileContents.Substring(16);
                //Try to resolve commit name directly from the ref file
                var HeadRefFile = Path.Combine(GitRepository, "refs", "heads", BranchName);
                if (!File.Exists(HeadRefFile)) return;

                var HeadRefFileContents = File.ReadAllText(HeadRefFile).Replace("\n", "");
                CommitRef = HeadRefFileContents;
                return;
            }
            Target.Logger.LogWarning("Git HEAD does not refer to a branch, are we in a detached head state? HEAD: {0}", HeadFileContents);
            BranchName = "detached-head";
            CommitRef = HeadFileContents;
        }
        catch (Exception Ex) {
            Target.Logger.LogWarning("Failed to handle git HEAD file at {0}: {1}", GitHeadFile, Ex.Message);
        }
    }
}

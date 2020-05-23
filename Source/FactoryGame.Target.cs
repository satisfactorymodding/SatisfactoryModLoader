// Fill out your copyright notice in the Description page of Project Settings.

using System;
using System.Collections;
using System.Collections.Generic;
using UnrealBuildTool;
using System.IO;
using System.Text;

public class FactoryGameTarget : TargetRules
{
	//Project Directory retrieved from UBT to extract file info
	private static string ProjectDirectory;
	
	public FactoryGameTarget(TargetInfo Target) : base(Target) {
		Type = TargetType.Game;
		//default link type for game is static, but we need modular
		//to get attachable module dll for mod loading
		LinkType = TargetLinkType.Modular;
		//Add your Mod modules here after FactoryGame and SML
		ExtraModuleNames.AddRange(new[] {"FactoryGame", "SML", "ExampleMod"});
		
		//Register exit hook if we are building in Shipping for Win64
		if (Target.Platform != UnrealTargetPlatform.Win64 || Target.Configuration != UnrealTargetConfiguration.Shipping) return;
		ProjectDirectory = Target.ProjectFile.Directory.FullName;
		AppDomain.CurrentDomain.ProcessExit += HandleApplicationExit;
	}

	private static string FindPropertyValueInObject(string Object, string Property) {
		var IsInString = false;
		var RequestedPropertyStarted = false;
		var ResultBuilder = new StringBuilder();
		for (var I = 1; I < Object.Length - 1; I++) {
			var IsComma = Object[I] == ',';
			if (!IsInString && (IsComma || I == 1)) {
				if (RequestedPropertyStarted) break;
				var StartedString = Object.Substring(IsComma ? I + 1 : I);
				if (StartedString.StartsWith(Property) && StartedString[Property.Length] == '=') {
					RequestedPropertyStarted = true;
					I += (Property.Length + (IsComma ? 1 : 0) + 1);
				}
			}

			if (Object[I] == '"' && Object[I - 1] != '\\') {
				IsInString = !IsInString;
				continue;
			}

			if (RequestedPropertyStarted) {
				if (Object[I] != '\\' || Object[I + 1] != '"') 
					ResultBuilder.Append(Object[I]);
			}
		}
		return ResultBuilder.ToString();
	}
	
	static void FindAlpakitSettings(IEnumerable<string> FileLines, out string GamePath, out bool CopyModsToGame, ref List<string> ModModuleNames) {
		GamePath = "";
		CopyModsToGame = false;
		var FoundAlpakitSettings = false;
		foreach (var CurrentLine in FileLines) {
			if (CurrentLine.StartsWith("[")) {
				if (FoundAlpakitSettings) break; //Other section start after required one, break
				//We found it if name equals to the expected one
				FoundAlpakitSettings = CurrentLine == "[/Script/Alpakit.AlpakitSettings]";
				continue;
			}
			if (FoundAlpakitSettings) {
				int SplitIndex = CurrentLine.IndexOf('=');
				if (SplitIndex == -1) continue;
				string PropertyName = CurrentLine.Substring(0, SplitIndex);
				string PropertyValue = CurrentLine.Substring(SplitIndex + 1);
				if (PropertyName == "SatisfactoryGamePath") {
					//(Path="D:/SatisfactoryExperimental")
					GamePath = FindPropertyValueInObject(PropertyValue, "Path");
				} else if (PropertyName == "CopyModsToGame") {
					CopyModsToGame = PropertyValue == "True";
				} else if (PropertyName == "Mods") {
					string ModEnabled = FindPropertyValueInObject(PropertyValue, "Enabled");
					string ModName = FindPropertyValueInObject(PropertyValue, "Name");
					if (ModEnabled == "True")
						ModModuleNames.Add(ModName);
				}
			}
		}
	}

	private static void HandleApplicationExit(object Sender, EventArgs Args) {
		//Abort if compilation failed or already up to date
		if (Environment.ExitCode != 0) return;
		var SavedGameConfigPath = Path.Combine(ProjectDirectory, "Saved/Config/Windows/Game.ini");
		//Abort if we don't have configuration file for alpakit
		if (!File.Exists(SavedGameConfigPath)) return;
		string FileContents;
		try {
			FileContents = File.OpenText(SavedGameConfigPath).ReadToEnd();
		} catch (Exception Ex) {
			Console.WriteLine("Failed to read Game.ini file: {0}", Ex.Message);
			return;
		}
		var SplitLines = FileContents.Split(new[] {Environment.NewLine}, StringSplitOptions.RemoveEmptyEntries);
		List<string> ModDllNames = new List<string>();
		string GamePath;
		bool CopyModsToGame;
		FindAlpakitSettings(SplitLines, out GamePath, out CopyModsToGame, ref ModDllNames);
		Console.WriteLine("Game Dir: {0} Copy Mods: {1}", GamePath, CopyModsToGame);
		if (!string.IsNullOrEmpty(GamePath) && CopyModsToGame && ModDllNames.Count > 0) {
			string BinariesDir = Path.Combine(ProjectDirectory, "Binaries/Win64");
			Console.WriteLine("[Alpakit] Copying mod DLLs to game directory automatically as specified in Alpakit settings");
			CopyModDllToGame(BinariesDir, GamePath, ModDllNames);
		}
	}

	private static bool CopyFileIfExists(string SrcDir, string DstDir, string FileName) {
		var SrcFilePath = Path.Combine(SrcDir, FileName);
		var DestFilePath = Path.Combine(DstDir, FileName);
		bool FileExists = File.Exists(SrcFilePath);
		if (FileExists)
			File.Copy(SrcFilePath, DestFilePath, true);
		return FileExists;
	}

	private static bool IsLoaderModule(string ModuleName) {
		return ModuleName == "SML";
	}
	
	private static void CopyModDllToGame(string BinariesDir, string GamePath, List<string> ModuleNames) {
		string ModsDir = Path.Combine(GamePath, "mods");
		string LoadersDir = Path.Combine(GamePath, "loaders");
		Directory.CreateDirectory(ModsDir);
		Directory.CreateDirectory(LoadersDir);
		foreach (var ModuleName in ModuleNames) {
			//Use correct directory for SML, which is "loaders", not "mods"
			var DllName = String.Format("UE4-{0}-Win64-Shipping.dll", ModuleName);
			var TargetDir = IsLoaderModule(ModuleName) ? LoadersDir : ModsDir;
			if (CopyFileIfExists(BinariesDir, TargetDir, DllName)) {
				//Also carry over PDB file if it exists
				Console.WriteLine("Successfully copied {0} to game mods folder", DllName);
				var PdbFileName = Path.ChangeExtension(DllName, "pdb");
				CopyFileIfExists(BinariesDir, TargetDir, PdbFileName);
			}
		}
	}
}

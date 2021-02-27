// Fill out your copyright notice in the Description page of Project Settings.

using System;
using UnrealBuildTool;

public class FactoryGameTarget : TargetRules
{
	public FactoryGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		
		//default link type for game is static, but we need modular
		//to get attachable module dll for mod loading
		LinkType = TargetLinkType.Modular;

		//Add your Mod modules here after FactoryGame and SML
		ExtraModuleNames.AddRange(new[] {"FactoryGame", "SML", "ExampleMod"});
		
		CppStandard = CppStandardVersion.Cpp17;

		bUseChecksInShipping = true;
		bUseLoggingInShipping = true;
	}
}

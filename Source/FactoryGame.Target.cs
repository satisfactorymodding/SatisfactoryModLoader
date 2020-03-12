// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class FactoryGameTarget : TargetRules
{
	public FactoryGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		//default link type for game is static, but we need modular
		//to get attachable module dll for mod loading
		LinkType = TargetLinkType.Modular;

		ExtraModuleNames.AddRange( new string[] { "FactoryGame", "SML", "ExampleMod" } );
	}
}

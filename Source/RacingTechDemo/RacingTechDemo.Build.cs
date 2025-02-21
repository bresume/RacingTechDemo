// Fill out your copyright notice in the Description page of Project SeRTDings.

using System;
using System.IO;
using UnrealBuildTool;

public class RacingTechDemo : ModuleRules
{
	public RacingTechDemo(ReadOnlyTargetRules Target) : base(Target)
	{
				
		bool bEnableSteamChecks = false; //Check to see if our default platform service is set to steam. We don't want to do steam checks on EGS.
		bool bEnableEosChecks = false; //Check to see if our default platform service is set to EOS. We don't want to do EGS checks on steam.
		string configFilePath = Path.Combine(Target.ProjectFile.Directory.FullName, "Config", "DefaultEngine.ini");
		if (File.Exists(configFilePath))
		{
			string[] configLines = File.ReadAllLines(configFilePath);
			foreach (string line in configLines)
			{
				if (line.StartsWith("DefaultPlatformService=", StringComparison.OrdinalIgnoreCase))
				{
					string service = line.Split('=')[1].Trim();
					if (service == "Steam")
					{
						bEnableSteamChecks = true;
						Console.Write("LogSGCBuild::Steam is enabled.");
					}
					if (service == "EOS")
					{
						bEnableEosChecks = true;
						Console.Write("LogSGCBuild::Steam is enabled.");
					}
					break;
				}
			}
		}

		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"ChaosVehicles", 
			"PhysicsCore",
			"Landscape"
		});
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				
			});

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Slate", "SlateCore"
			});
		
		PrivateDependencyModuleNames.Add("OnlineSubsystem");

		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Linux) || (Target.Platform == UnrealTargetPlatform.Mac))
		{
			PublicDependencyModuleNames.AddRange(new string[] { "Steamworks", "OnlineSubsystemSteam" });
			//PrivateDependencyModuleNames.AddRange(new string[] { "Steamworks", "OnlineSubsystemSteam" });
			PublicIncludePaths.AddRange(new string[] { "../Plugins/Online/OnlineSubsystemSteam/Source/Private" });
			//PrivateIncludePaths.AddRange(new string[] { "../Plugins/Online/OnlineSubsystemSteam/Source/Private" });
		}
		if (bEnableSteamChecks)
		{
			PublicDependencyModuleNames.AddRange(new string[] { "Steamworks", "OnlineSubsystemSteam" });
			PublicIncludePaths.AddRange(new string[] { "../Plugins/Online/OnlineSubsystemSteam/Source/Private" });
			PublicDefinitions.Add("RTD_ENABLE_STEAMCHECKS = 1");
			PublicDefinitions.Add("RTD_PLATFORM_PLAYSTATION = 0");
			PublicDefinitions.Add("RTD_PLATFORM_XBOX = 0");
		}
		else
		{
			PublicDefinitions.Add("RTD_ENABLE_STEAMCHECKS = 0");
			PublicDefinitions.Add("RTD_PLATFORM_PLAYSTATION = 0");
			PublicDefinitions.Add("RTD_PLATFORM_XBOX = 0");
		}
		if (bEnableEosChecks)
		{
			PublicDependencyModuleNames.AddRange(new string[] { "EOSSDK", "OnlineSubsystemEOS" });
			PublicDefinitions.Add("RTD_ENABLE_EOSCHECKS = 1");
			PublicDefinitions.Add("RTD_PLATFORM_PLAYSTATION = 0");
			PublicDefinitions.Add("RTD_PLATFORM_XBOX = 0");
		}
		else
		{
			PublicDefinitions.Add("RTD_ENABLE_EOSCHECKS = 0");
			PublicDefinitions.Add("RTD_PLATFORM_PLAYSTATION = 0");
			PublicDefinitions.Add("RTD_PLATFORM_XBOX = 0");
		}
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
		);

	}
}

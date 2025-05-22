// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Wyrmblood : ModuleRules
{
    public Wyrmblood(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;

        PublicIncludePaths.AddRange(
            new[] {
                "Wyrmblood/Public"
            }
        );

        PrivateIncludePaths.AddRange(
            new[] {
                "Wyrmblood/Private"
                
            }
        );

        PublicDependencyModuleNames.AddRange(new[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "GameplayAbilities",
            "GameplayTags",
            "GameplayTasks",
            "AIModule",
            "NavigationSystem",
            "CommonUI",
            "UMG",
            "Slate",
            "SlateCore",
            "CommonInput"
        });

        PrivateDependencyModuleNames.AddRange(new[]
        {
            "NetCore",
            "RenderCore",
            "DeveloperSettings",
            "PhysicsCore",
            "Chaos",
            "ChaosSolverEngine",
            "RHI",
            "AssetRegistry",
            "ApplicationCore"
        });

        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(new[]
            {
                "UnrealEd",
                "EditorFramework",
                "EditorStyle",
                "EditorSubsystem",
                "Blutility",
                "UMGEditor",
                "AssetTools",
                "ContentBrowser",
                "EditorScriptingUtilities"
            });
        }

        if (Target.Configuration != UnrealTargetConfiguration.Shipping)
        {
            PublicDefinitions.Add("WITH_GAMEPLAY_DEBUGGER=1");
            PublicDependencyModuleNames.Add("GameplayDebugger");
        }
        else
        {
            PublicDefinitions.Add("WITH_GAMEPLAY_DEBUGGER=0");
        }

        bUseUnity = false;
        MinFilesUsingPrecompiledHeaderOverride = 1;
        bUseRTTI = false;
        bEnableExceptions = false;

        DynamicallyLoadedModuleNames.AddRange(new[]
        {
            "OnlineSubsystem",
            "OnlineSubsystemUtils"
        });

        // Uncomment to use additional subsystems like Steam
        // PrivateDependencyModuleNames.Add("OnlineSubsystemSteam");
    }
}

// Copyright Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class MinesweeperPlugin : ModuleRules
	{
		public MinesweeperPlugin(ReadOnlyTargetRules Target) : base(Target)
		{
			PublicIncludePaths.AddRange(
				new string[] {
                }
                );

			PrivateIncludePaths.AddRange(
				new string[] {
                }
                );

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core", "CoreUObject", "Engine", "InputCore", "UMG", "Slate", "SlateCore", "ToolMenus", "UMGEditor", "Blutility", "UnrealEd"
					// ... add other public dependencies that you statically link with here ...
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
                    "Projects",
					// ... add private dependencies that you statically link with here ...
				}
                );

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
					// ... add any modules that your module loads dynamically here ...
				}
				);
		}
	}
}

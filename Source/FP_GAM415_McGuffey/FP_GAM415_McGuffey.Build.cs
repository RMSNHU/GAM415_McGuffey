// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FP_GAM415_McGuffey : ModuleRules
{
	public FP_GAM415_McGuffey(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "Niagara", "ProceduralMeshComponent"});
	}
}

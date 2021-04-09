// Diploma Shooter. Made by Viktor Polyakov IT-5

using UnrealBuildTool;
using System.Collections.Generic;

public class DiplomaShooterTarget : TargetRules
{
	public DiplomaShooterTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "DiplomaShooter" } );
	}
}

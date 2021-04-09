// Diploma Shooter. Made by Viktor Polyakov IT-5

using UnrealBuildTool;
using System.Collections.Generic;

public class DiplomaShooterEditorTarget : TargetRules
{
	public DiplomaShooterEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "DiplomaShooter" } );
	}
}

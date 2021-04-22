// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "AI/DSAICharacter.h"
#include "AI/DSAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ADSAICharacter::ADSAICharacter(const FObjectInitializer& ObjInit) : Super(ObjInit) 
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ADSAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }
}

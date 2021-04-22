// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "AI/DSAICharacter.h"
#include "AI/DSAIController.h"

ADSAICharacter::ADSAICharacter(const FObjectInitializer& ObjInit) : Super(ObjInit) 
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ADSAIController::StaticClass();
}

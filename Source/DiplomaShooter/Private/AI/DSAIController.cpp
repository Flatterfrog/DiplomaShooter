// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "AI/DSAIController.h"
#include "AI/DSAICharacter.h"

void ADSAIController::OnPossess(APawn* InPawn) 
{
    Super::OnPossess(InPawn);

    const auto DSCharacter = Cast<ADSAICharacter>(InPawn);
    if (DSCharacter)
    {
        RunBehaviorTree(DSCharacter->BehaviorTreeAsset);
    }
}
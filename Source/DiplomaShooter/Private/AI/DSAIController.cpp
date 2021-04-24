// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "AI/DSAIController.h"
#include "AI/DSAICharacter.h"
#include "Components/DSAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ADSAIController::ADSAIController() 
{
    DSAIPerceptionComponent = CreateDefaultSubobject<UDSAIPerceptionComponent>("DSPerceptionComponent");
    SetPerceptionComponent(*DSAIPerceptionComponent);
}

void ADSAIController::OnPossess(APawn* InPawn) 
{
    Super::OnPossess(InPawn);

    const auto DSCharacter = Cast<ADSAICharacter>(InPawn);
    if (DSCharacter)
    {
        RunBehaviorTree(DSCharacter->BehaviorTreeAsset);
    }
}

void ADSAIController::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    const auto AimActor = GetFocusOnActor();
    SetFocus(AimActor);
}

AActor* ADSAIController::GetFocusOnActor() const
{
    if (!GetBlackboardComponent()) return nullptr;
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}

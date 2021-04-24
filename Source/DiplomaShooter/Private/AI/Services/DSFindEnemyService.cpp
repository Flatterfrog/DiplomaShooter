// Diploma Shooter. Made by Viktor Polyakov IT-5

#include "AI/Services/DSFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "DSUtils.h"
#include "Components/DSAIPerceptionComponent.h"

UDSFindEnemyService::UDSFindEnemyService() 
{
    NodeName = "Find Enemy";
}

void UDSFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (Blackboard)
    {
        const auto Controller = OwnerComp.GetOwner();
        const auto PerceptionComponent = DSUtils::GetDSPlayerComponent<UDSAIPerceptionComponent>(Controller);
        if (PerceptionComponent)
        {
            Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
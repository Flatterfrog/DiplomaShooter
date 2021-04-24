// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "AI/Services/DSFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "DSUtils.h"
#include "Components/DSWeaponComponent.h"

UDSFireService::UDSFireService() 
{
    NodeName = "Fire";
}

void UDSFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();

    const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
    
    if (Controller)
    {
        const auto WeaponComponent = DSUtils::GetDSPlayerComponent<UDSWeaponComponent>(Controller->GetPawn());
        if (WeaponComponent)
        {
            HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
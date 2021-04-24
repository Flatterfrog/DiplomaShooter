// Diploma Shooter. Made by Viktor Polyakov IT-5

#include "AI/Services/DSChangeWeaponService.h"
#include "Components/DSWeaponComponent.h"
#include "AIController.h"
#include "DSUtils.h"

UDSChangeWeaponService::UDSChangeWeaponService()
{
    NodeName = "Change Weapon";
}

void UDSChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();

    if (Controller)
    {
        const auto WeaponComponent = DSUtils::GetDSPlayerComponent<UDSWeaponComponent>(Controller->GetPawn());
        if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
        {
            WeaponComponent->NextWeapon();
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
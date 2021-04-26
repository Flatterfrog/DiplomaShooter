// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "Components/DSRespawnComponent.h"
#include "DSGameModeBase.h"


UDSRespawnComponent::UDSRespawnComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}

void UDSRespawnComponent::RespawnTimerUpdate() 
{
    if (--RespawnCountDown == 0)
    {
        if (!GetWorld()) return;
        GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

        const auto GameMode = Cast<ADSGameModeBase>(GetWorld()->GetAuthGameMode());
        if (!GameMode) return;

        GameMode->RespawnRequest(Cast<AController>(GetOwner()));

    }
}

void UDSRespawnComponent::Respawn(int32 RespawnTime)
{
    if (!GetWorld()) return;

	RespawnCountDown = RespawnTime;
    GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &UDSRespawnComponent::RespawnTimerUpdate, 1.0f, true);
}

bool UDSRespawnComponent::IsRespawnInProgress() const 
{
    return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}
// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "UI/DSSpectatorWidget.h"
#include "DSUtils.h"
#include "Components/DSRespawnComponent.h"

bool UDSSpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
    const auto RespawnComponent = DSUtils::GetDSPlayerComponent<UDSRespawnComponent>(GetOwningPlayer());
    if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

    CountDownTime = RespawnComponent->GetRespawnCountDown();
    return true;
}
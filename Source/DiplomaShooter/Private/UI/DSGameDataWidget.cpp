// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "UI/DSGameDataWidget.h"
#include "DSGameModeBase.h"
#include "Player/DSPlayerState.h"

 int32 UDSGameDataWidget::GetKillsNum() const 
 {
     const auto PlayerState = GetDSPlayerState();
     return PlayerState ? PlayerState->GetKillsNum() : 0;
 }
int32 UDSGameDataWidget::GetCurrentRoundNum() const 
{
    const auto GameMode = GetDSGameMode();
    return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}
 int32 UDSGameDataWidget::GetTotalRoundsNum() const 
 {
     const auto GameMode = GetDSGameMode();
     return GameMode ? GameMode->GetGameData().RoundsNum : 0;
 }
int32 UDSGameDataWidget::GetRoundSecondsRemaining() const 
{
    const auto GameMode = GetDSGameMode();
    return GameMode ? GameMode->GetRoundSecondsRemaining() : 0;
}

ADSGameModeBase* UDSGameDataWidget::GetDSGameMode() const 
{
    return GetWorld() ? Cast<ADSGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}
ADSPlayerState* UDSGameDataWidget::GetDSPlayerState() const 
{
    return GetOwningPlayer() ? Cast<ADSPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
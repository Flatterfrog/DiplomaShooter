// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "UI/DSGameOverWidget.h"
#include "DSGameModeBase.h"
#include "Player/DSPlayerState.h"
#include "UI/DSPlayerStatRawWidget.h"
#include "Components/VerticalBox.h"
#include "DSUtils.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UDSGameOverWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetWorld())
    {
        const auto GameMode = Cast<ADSGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &UDSGameOverWidget::OnMatchStateChanged);
        }
    }
    if (ResetLevelButton)
    {
        ResetLevelButton->OnClicked.AddDynamic(this, &UDSGameOverWidget::OnResetLevel);
    }
}

void UDSGameOverWidget::OnMatchStateChanged(EDSMatchState State)
{
    if (State == EDSMatchState::GameOver)
    {
        UpdatePlayersStat();
    }
}

void UDSGameOverWidget::UpdatePlayersStat()
{
    if (!GetWorld() || !PlayerStatBox) return;

    PlayerStatBox->ClearChildren();

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;

        const auto PlayerState = Cast<ADSPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;

        const auto PlayerStatRawWidget = CreateWidget<UDSPlayerStatRawWidget>(GetWorld(), PlayerStatRawWidgetClass);
        if (!PlayerStatRawWidget) continue;

        PlayerStatRawWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        PlayerStatRawWidget->SetKills(DSUtils::TextFromInt(PlayerState->GetKillsNum()));
        PlayerStatRawWidget->SetDeaths(DSUtils::TextFromInt(PlayerState->GetDeathsNum()));
        PlayerStatRawWidget->SetTeam(DSUtils::TextFromInt(PlayerState->GetTeamID()));
        PlayerStatRawWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
        PlayerStatRawWidget->SetTeamColor(PlayerState->GetTeamColor());

        PlayerStatBox->AddChild(PlayerStatRawWidget);
    }
}
    void UDSGameOverWidget::OnResetLevel(){
    {
        const auto CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
        UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
    }
}
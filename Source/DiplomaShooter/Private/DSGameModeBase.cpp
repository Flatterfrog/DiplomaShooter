// Diploma Shooter. Made by Viktor Polyakov IT-5

#include "DSGameModeBase.h"
#include "Player/DSBaseCharacter.h"
#include "Player/DSPlayerController.h"
#include "UI/DSGameHUD.h"
#include "AIController.h"
#include "Player/DSPlayerState.h"
#include "DSUtils.h"
#include "Components/DSRespawnComponent.h"
#include "EngineUtils.h"

constexpr static int32 MinRoundTimeForRespawn = 10;

ADSGameModeBase::ADSGameModeBase()
{
    DefaultPawnClass = ADSBaseCharacter::StaticClass();
    PlayerControllerClass = ADSPlayerController::StaticClass();
    HUDClass = ADSGameHUD::StaticClass();
    PlayerStateClass = ADSPlayerState::StaticClass();
}

void ADSGameModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnBots();
    CreateTeamsInfo();

    CurrentRound = 1;
    StartRound();
}

UClass* ADSGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ADSGameModeBase::SpawnBots()
{
    if (!GetWorld()) return;

    for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        const auto DSAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
        RestartPlayer(DSAIController);
    }
}

void ADSGameModeBase::StartRound()
{
    RoundCountDown = GameData.RoundTime;
    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ADSGameModeBase::GameTimerUpdate, 1.0f, true);
}

void ADSGameModeBase::GameTimerUpdate()
{

    if (--RoundCountDown == 0)
    {
        GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);
        if (CurrentRound + 1 <= GameData.RoundsNum)
        {
            ++CurrentRound;
            ResetPlayers();
            StartRound();
        }
        else
        {

            GameOver();
            UE_LOG(LogTemp, Display, TEXT("GAME OVER"));
        }
    }
}

void ADSGameModeBase::ResetPlayers()
{
    if (!GetWorld()) return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    }
}
void ADSGameModeBase::ResetOnePlayer(AController* Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }
    RestartPlayer(Controller);
    SetPlayerColor(Controller);
}

void ADSGameModeBase::CreateTeamsInfo() 
{
    if (!GetWorld()) return;

    int32 TeamID = 1;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;

        const auto PlayerState = Cast<ADSPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;

        PlayerState->SetTeamID(TeamID);
        PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
        SetPlayerColor(Controller);

        TeamID = TeamID == 1 ? 2 : 1;
    }
}
FLinearColor ADSGameModeBase::DetermineColorByTeamID(int32 TeamID) const 
{
    if (TeamID - 1 < GameData.TeamColors.Num())
    {
        return GameData.TeamColors[TeamID - 1];
    }
    return GameData.DefaultTeamColor;
}
void ADSGameModeBase::SetPlayerColor(AController* Controller)
{
    if (!Controller) return;

    const auto Character = Cast<ADSBaseCharacter>(Controller->GetPawn());
    if (!Character) return;

    const auto PlayerState = Cast<ADSPlayerState>(Controller->PlayerState);
    if (!PlayerState) return;

    Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void ADSGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
    const auto KillerPlayerState = KillerController ? Cast<ADSPlayerState>(KillerController->PlayerState) : nullptr;
    const auto VictimPlayerState = VictimController ? Cast<ADSPlayerState>(VictimController->PlayerState) : nullptr;

    if (KillerPlayerState) {
        KillerPlayerState->AddKill();
    }
    if(VictimPlayerState)
    {
        VictimPlayerState->AddDeath();
    }

    StartRespawn(VictimController);
}

void ADSGameModeBase::StartRespawn(AController* Controller)
{
    const auto RespawnAvailable = RoundCountDown > MinRoundTimeForRespawn + GameData.RespawnTime;
    if (!RespawnAvailable) return;

    const auto RespawnComponent = DSUtils::GetDSPlayerComponent<UDSRespawnComponent>(Controller);
    if (!RespawnComponent) return;

    RespawnComponent->Respawn(GameData.RespawnTime);
}

void ADSGameModeBase::RespawnRequest(AController* Controller) 
{
    ResetOnePlayer(Controller);
}

void ADSGameModeBase::GameOver() 
{
    for (auto Pawn : TActorRange<APawn>(GetWorld()))
    {
        if(Pawn)
        {
            Pawn->TurnOff();
            Pawn->DisableInput(nullptr);
        }
    }
}

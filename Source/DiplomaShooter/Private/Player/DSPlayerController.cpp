// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "Player/DSPlayerController.h"
#include "Components/DSRespawnComponent.h"
#include "DSGameModeBase.h"

ADSPlayerController::ADSPlayerController() 
{
    RespawnComponent = CreateDefaultSubobject<UDSRespawnComponent>("RespawnComponent");
}

void ADSPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (GetWorld())
    {
        const auto GameMode = Cast<ADSGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ADSPlayerController::OnMatchStateChanged);
        }
    }
}

void ADSPlayerController::OnMatchStateChanged(EDSMatchState State)
{
    if (State == EDSMatchState::InProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}


void ADSPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    OnNewPawn.Broadcast(InPawn);
}

void ADSPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (!InputComponent) return;
    InputComponent->BindAction("PauseGame", IE_Pressed, this, &ADSPlayerController::OnPauseGame);
}

void ADSPlayerController::OnPauseGame()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->SetPause(this);
}
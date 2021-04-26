// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "Player/DSPlayerController.h"
#include "Components/DSRespawnComponent.h"

ADSPlayerController::ADSPlayerController() 
{
    RespawnComponent = CreateDefaultSubobject<UDSRespawnComponent>("RespawnComponent");
}

void ADSPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    OnNewPawn.Broadcast(InPawn);
}
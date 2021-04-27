// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "Menu/DSMenuPlayerController.h"

void ADSMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;
}
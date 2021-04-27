// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "Menu/DSMenuGameModeBase.h"
#include "Menu/DSMenuPlayerController.h"
#include "Menu/UI/DSMenuHUD.h"

ADSMenuGameModeBase::ADSMenuGameModeBase()
{
    PlayerControllerClass = ADSMenuPlayerController::StaticClass();
    HUDClass = ADSMenuHUD::StaticClass();
}

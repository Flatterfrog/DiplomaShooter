// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "DSGameModeBase.h"
#include "Player/DSBaseCharacter.h"
#include "Player/DSPlayerController.h"
#include "UI/DSGameHUD.h"

ADSGameModeBase::ADSGameModeBase() 
{
    DefaultPawnClass = ADSBaseCharacter::StaticClass();
    PlayerControllerClass = ADSPlayerController::StaticClass();
    HUDClass = ADSGameHUD::StaticClass();
}
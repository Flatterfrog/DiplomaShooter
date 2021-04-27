// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "Menu/UI/DSMenuHUD.h"
#include "Blueprint/UserWidget.h"

void ADSMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if (MenuWidgetClass)
    {
        const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
        if (MenuWidget)
        {
            MenuWidget->AddToViewport();
        }
    }
}
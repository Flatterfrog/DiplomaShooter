// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "UI/DSPauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

void UDSPauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &UDSPauseWidget::OnClearPause);
    }
}

void UDSPauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}
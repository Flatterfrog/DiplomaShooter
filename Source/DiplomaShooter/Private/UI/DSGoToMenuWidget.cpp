// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "UI/DSGoToMenuWidget.h"
#include "Components/Button.h"
#include "DSGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UDSGoToMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GoToMenuButton)
    {
        GoToMenuButton->OnClicked.AddDynamic(this, &UDSGoToMenuWidget::OnGoToMenu);
    }
}

void UDSGoToMenuWidget::OnGoToMenu()
{
    if (!GetWorld()) return;

    const auto DSGameInstance = GetWorld()->GetGameInstance<UDSGameInstance>();
    if (!DSGameInstance) return;

    if (DSGameInstance->GetMenuLevelName().IsNone())
    {
        UE_LOG(LogTemp, Error, TEXT("Menu level name is NONE"));
        return;
    }

    UGameplayStatics::OpenLevel(this, DSGameInstance->GetMenuLevelName());
}
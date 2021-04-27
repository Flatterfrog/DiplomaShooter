// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "Menu/UI/DSMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "DSGameInstance.h"

void UDSMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &UDSMenuWidget::OnStartGame);
    }
}

void UDSMenuWidget::OnStartGame()
{
    if (!GetWorld()) return;

    const auto DSGameInstance = GetWorld()->GetGameInstance<UDSGameInstance>();
    if (!DSGameInstance) return;

    if (DSGameInstance->GetStartupLevelName().IsNone())
    {
        UE_LOG(LogTemp, Error, TEXT("Level name is NONE"));
        return;
    }

    UGameplayStatics::OpenLevel(this, DSGameInstance->GetStartupLevelName());
}

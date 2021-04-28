// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "Menu/UI/DSMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "DSGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/HorizontalBox.h"
#include "Menu/UI/DSLevelItemWidget.h"

void UDSMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &UDSMenuWidget::OnStartGame);
    }

    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &UDSMenuWidget::OnQuitGame);
    }

    InitLevelItems();
}

void UDSMenuWidget::InitLevelItems()
{
    const auto DSGameInstance = GetDSGameInstance();
    if (!DSGameInstance) return;

    checkf(DSGameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty!"));

    if (!LevelItemsBox) return;
    LevelItemsBox->ClearChildren();

    for (auto LevelData : DSGameInstance->GetLevelsData())
    {
        const auto LevelItemWidget = CreateWidget<UDSLevelItemWidget>(GetWorld(), LevelItemWidgetClass);
        if (!LevelItemWidget) continue;

        LevelItemWidget->SetLevelData(LevelData);
        LevelItemWidget->OnLevelSelected.AddUObject(this, &UDSMenuWidget::OnLevelSelected);

        LevelItemsBox->AddChild(LevelItemWidget);
        LevelItemWidgets.Add(LevelItemWidget);
    }

    if (DSGameInstance->GetStartupLevel().LevelName.IsNone())
    {
        OnLevelSelected(DSGameInstance->GetLevelsData()[0]);
    }
    else
    {
        OnLevelSelected(DSGameInstance->GetStartupLevel());
    }
}

void UDSMenuWidget::OnLevelSelected(const FLevelData& Data)
{
    const auto DSGameInstance = GetDSGameInstance();
    DSGameInstance->SetStartupLevel(Data);

    for (auto LevelItemWidget : LevelItemWidgets)
    {
        if (LevelItemWidget)
        {
            const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
            LevelItemWidget->SetSelected(IsSelected);
        }
    }
}

void UDSMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UDSMenuWidget::OnStartGame()
{
    const auto DSGameInstance = GetDSGameInstance();
    if (!DSGameInstance) return;

    UGameplayStatics::OpenLevel(this, DSGameInstance->GetStartupLevel().LevelName);
}

UDSGameInstance* UDSMenuWidget::GetDSGameInstance() const
{
    if (!GetWorld()) return nullptr;
    return GetWorld()->GetGameInstance<UDSGameInstance>();
}
// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "UI/DSGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "DSGameModeBase.h"

void ADSGameHUD::DrawHUD() 
{
    Super::DrawHUD();

 //   DrawCrossHair();

}

void ADSGameHUD::BeginPlay() 
{
    Super::BeginPlay();

    GameWidgets.Add(EDSMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(EDSMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(EDSMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));

    for (auto GameWidgetPair: GameWidgets)
    {
        const auto GameWidget = GameWidgetPair.Value;
        if (!GameWidget) continue;

        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }


    if (GetWorld())
    {
        const auto GameMode = Cast<ADSGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ADSGameHUD::OnMatchStateChanged);
        }
    }

}

void ADSGameHUD::DrawCrossHair() 
{
    
    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

    const float HalfLineSize = 10.0f;
    const float LineThickness = 2.0f;
    const FLinearColor LineColor = FLinearColor::Green;

    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}

void ADSGameHUD::OnMatchStateChanged(EDSMatchState State) 
{
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }

    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }

    UE_LOG(LogTemp, Display, TEXT("Match state changed: %s"), *UEnum::GetValueAsString(State));
}
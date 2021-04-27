// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DSCoreTypes.h"
#include "DSGameHUD.generated.h"

UCLASS()
class DIPLOMASHOOTER_API ADSGameHUD : public AHUD
{
	GENERATED_BODY()

		public:

    virtual void DrawHUD() override;

	protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> GameOverWidgetClass;

	virtual void BeginPlay() override;

	private:

		UPROPERTY()
        TMap<EDSMatchState, UUserWidget*> GameWidgets;

		UPROPERTY()
        UUserWidget* CurrentWidget = nullptr;
    void DrawCrossHair();
    void OnMatchStateChanged(EDSMatchState State);
	
};

// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DSPlayerStatRawWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class DIPLOMASHOOTER_API UDSPlayerStatRawWidget : public UUserWidget
{
	GENERATED_BODY()
	

        public:
    void SetPlayerName(const FText& Text);
    void SetKills(const FText& Text);
    void SetDeaths(const FText& Text);
    void SetTeam(const FText& Text);
    void SetPlayerIndicatorVisibility(bool Visible);

		protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* PlayerNameTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* KillsTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* DeathsTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TeamTextBlock;

    UPROPERTY(meta = (BindWidget))
    UImage* PlayerIndicatorImage;
};

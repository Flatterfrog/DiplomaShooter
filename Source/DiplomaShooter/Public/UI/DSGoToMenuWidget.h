// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DSGoToMenuWidget.generated.h"

class UButton;

UCLASS()
class DIPLOMASHOOTER_API UDSGoToMenuWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* GoToMenuButton;

    virtual void NativeOnInitialized() override;

    private:
    UFUNCTION()
    void OnGoToMenu();
};

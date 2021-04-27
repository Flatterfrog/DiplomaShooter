// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DSPauseWidget.generated.h"

class UButton;

UCLASS()
class DIPLOMASHOOTER_API UDSPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ClearPauseButton;

    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnClearPause();
};

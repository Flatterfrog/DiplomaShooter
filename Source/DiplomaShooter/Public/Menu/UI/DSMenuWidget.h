// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DSMenuWidget.generated.h"

class UButton;

UCLASS()
class DIPLOMASHOOTER_API UDSMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
		protected:
    UPROPERTY(meta = (BindWidget))
    UButton* StartGameButton;

    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnStartGame();
};

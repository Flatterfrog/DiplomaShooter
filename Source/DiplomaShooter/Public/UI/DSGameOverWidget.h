// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DSCoreTypes.h"
#include "DSGameOverWidget.generated.h"


class UVerticalBox;
class UButton;

UCLASS()
class DIPLOMASHOOTER_API UDSGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerStatBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatRawWidgetClass;

    UPROPERTY(meta = (BindWidget))
    UButton* ResetLevelButton;

    virtual void NativeOnInitialized() override;

private:
    void OnMatchStateChanged(EDSMatchState State);
    void UpdatePlayersStat();

       UFUNCTION()
    void OnResetLevel();
};

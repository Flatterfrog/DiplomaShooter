// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DSCoreTypes.h"
#include "DSMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class UDSGameInstance;
class UDSLevelItemWidget;

UCLASS()
class DIPLOMASHOOTER_API UDSMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
		protected:
    UPROPERTY(meta = (BindWidget))
    UButton* StartGameButton;

     UPROPERTY(meta = (BindWidget))
    UButton* QuitGameButton;

     UPROPERTY(meta = (BindWidget))
    UHorizontalBox* LevelItemsBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> LevelItemWidgetClass;

    virtual void NativeOnInitialized() override;

private:

    UPROPERTY()
    TArray<UDSLevelItemWidget*> LevelItemWidgets;

    UFUNCTION()
    void OnStartGame();

     UFUNCTION()
    void OnQuitGame();

     void InitLevelItems();
    void OnLevelSelected(const FLevelData& Data);
    UDSGameInstance* GetDSGameInstance() const;
};

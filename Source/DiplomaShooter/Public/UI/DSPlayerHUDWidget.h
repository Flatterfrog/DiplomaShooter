// Diploma Shooter. Made by Viktor Polyakov IT-5

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DSCoreTypes.h"
#include "DSPlayerHUDWidget.generated.h"

class UProgressBar;

UCLASS()
class DIPLOMASHOOTER_API UDSPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

		public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating() const;


	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnTakeDamage();

	protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthProgressBar;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentColorThreshold = 0.3f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor GoodColor = FLinearColor::White;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor BadColor = FLinearColor::Red;


    virtual void NativeOnInitialized() override;

	private:
    void OnHealthChanged(float Health, float HealthDelta);
	void OnNewPawn(APawn* NewPawn);
    void UpdateHealthBar();
};

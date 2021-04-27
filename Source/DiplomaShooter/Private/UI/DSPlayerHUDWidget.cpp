// Diploma Shooter. Made by Viktor Polyakov IT-5

#include "UI/DSPlayerHUDWidget.h"
#include "Components/DSHealthComponent.h"
#include "Components/DSWeaponComponent.h"
#include "DSUtils.h"

void UDSPlayerHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if(GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UDSPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }
}

void UDSPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
      const auto HealthComponent = DSUtils::GetDSPlayerComponent<UDSHealthComponent>(NewPawn);
    if (HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &UDSPlayerHUDWidget::OnHealthChanged);
    }
   
}


void UDSPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{

    if (HealthDelta < 0.0f)
    {

        OnTakeDamage();
    }
}

float UDSPlayerHUDWidget::GetHealthPercent() const
{
    const auto HealthComponent = DSUtils::GetDSPlayerComponent<UDSHealthComponent>(GetOwningPlayerPawn());
    if (!HealthComponent) return 0.0f;

    return HealthComponent->GetHealthPercent();
}

bool UDSPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{

    const auto WeaponComponent = DSUtils::GetDSPlayerComponent<UDSWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool UDSPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
    const auto WeaponComponent = DSUtils::GetDSPlayerComponent<UDSWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

bool UDSPlayerHUDWidget::IsPlayerAlive() const 
{
    const auto HealthComponent = DSUtils::GetDSPlayerComponent<UDSHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent && !HealthComponent->IsDead();
}


bool UDSPlayerHUDWidget::IsPlayerSpectating() const 
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;

}


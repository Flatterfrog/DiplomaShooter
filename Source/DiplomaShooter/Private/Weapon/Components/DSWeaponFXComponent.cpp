// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "Weapon/Components/DSWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

UDSWeaponFXComponent::UDSWeaponFXComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}

void UDSWeaponFXComponent::PlayImpactFX(const FHitResult& Hit) 
{
    auto Effect = DefaultEffect;

    if (Hit.PhysMaterial.IsValid())
    {
        const auto PhysMat = Hit.PhysMaterial.Get();
        if (EffectsMap.Contains(PhysMat))
        {
            Effect = EffectsMap[PhysMat];
        }
    }

    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}


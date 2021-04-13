// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "Weapon/DSBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ADSBaseWeapon::ADSBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void ADSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}




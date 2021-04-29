// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "Weapon/DSLauncherWeapon.h"
#include "Weapon/DSProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void ADSLauncherWeapon::StartFire() 
{
    MakeShot();
}

void ADSLauncherWeapon::MakeShot() 
{
    if (!GetWorld()) return;

    if (IsAmmoEmpty())
    {
        UGameplayStatics::SpawnSoundAtLocation(GetWorld(), NoAmmoSound, GetActorLocation());
        return;
    }

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    ADSProjectile* Projectile = GetWorld()->SpawnActorDeferred <ADSProjectile>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }
    DecreaseAmmo();
    UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
}
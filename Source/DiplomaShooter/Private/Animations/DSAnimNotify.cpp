// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "Animations/DSAnimNotify.h"

void UDSAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}
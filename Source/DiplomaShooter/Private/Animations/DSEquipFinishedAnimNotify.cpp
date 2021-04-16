// Diploma Shooter. Made by Viktor Polyakov IT-5


#include "Animations/DSEquipFinishedAnimNotify.h"

void UDSEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) 
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);

}
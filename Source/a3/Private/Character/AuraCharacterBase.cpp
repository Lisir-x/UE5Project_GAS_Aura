


#include "Character/AuraCharacterBase.h"


AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	//创建骨骼网格体组件
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	//设置骨骼网格体属性
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);//碰撞属性为无碰撞
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}


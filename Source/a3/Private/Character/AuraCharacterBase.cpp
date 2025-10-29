


#include "Character/AuraCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "a3/a3.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"


AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	//设置胶囊体和网格体碰撞属性
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);	//不生成重叠事件
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);	//生成重叠事件

	//创建骨骼网格体组件
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	//设置骨骼网格体属性
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);//碰撞属性为无碰撞
}

//获取能力系统组件
UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAnimMontage* AAuraCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AAuraCharacterBase::GetCombatSocketLocation()
{
	//先检查武器初始化后返回武器插槽位置
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}

//应用效果到自身
void AAuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	//检查目标能力系统组件和主属性游戏效果是否有效
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	//创建游戏效果上下文句柄
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	//将当前对象设置为效果的源对象
	ContextHandle.AddSourceObject(this);
	//创建游戏效果规格句柄(要应用的游戏效果类,效果等级,上下文句柄)
	const FGameplayEffectSpecHandle SpecHandle =
		GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	//将创建的游戏效果规格应用到目标的ASC上
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

//初始化默认属性
void AAuraCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

//添加角色技能
void AAuraCharacterBase::AddCharacterAbilities()
{
	//创建由能力系统组件转换的Aura能力系统组件
	UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	//添加角色技能
	AuraASC->AddCharacterAbilities(StartupAbilities);
}





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

//死亡逻辑
void AAuraCharacterBase::Die()
{
	//武器分离
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	//死亡多播句柄(调用客户端死亡逻辑)
	MulticastHandleDeath();
}

//死亡多播句柄
void AAuraCharacterBase::MulticastHandleDeath_Implementation()
{
	//设置武器网格体属性
	Weapon->SetSimulatePhysics(true); //启用物理模拟
	Weapon->SetEnableGravity(true);	//启用重力
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly); //仅物理

	//设置自身网格体属性
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block); //阻挡静态世界对象

	//设置胶囊组件属性
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision); //无碰撞
	
	//溶解
	Dissolve();
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
	ApplyEffectToSelf(DefaultResistanceAttributes, 1.f);
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

//溶解逻辑
void AAuraCharacterBase::Dissolve()
{
	//若溶解材质实例有效
	if (IsValid(DissolveMaterialInstance))
	{
		//创建动态材质实例(溶解材质实例)
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		//将自身材质替换为动态材质实例
		GetMesh()->SetMaterial(0, DynamicMatInst);
		//启用溶解时间轴
		StartDissolveTimeline(DynamicMatInst);
	}
	//若武器溶解材质实例有效
	if (IsValid(WeaponDissolveMaterialInstance))
	{
		//创建动态材质实例(武器溶解材质实例)
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
		//将自身材质替换为动态材质实例
		Weapon->SetMaterial(0, DynamicMatInst);
		//启用武器溶解时间轴
		StartWeaponDissolveTimeline(DynamicMatInst);
	}
}


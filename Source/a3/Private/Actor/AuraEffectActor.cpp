


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	//创建场景组件并设置为根组件
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

}

//应用游戏效果蓝图函数
void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	//获取目标的能力系统组件
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!IsValid(TargetASC)) return;

	//检查游戏效果类的初始化
	check(GameplayEffectClass);
	//创建游戏效果上下文句柄
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	//将当前对象设置为效果的源对象
	EffectContextHandle.AddSourceObject(this);
	//创建游戏效果规格句柄(要应用的游戏效果类,效果等级,上下文句柄)
	const FGameplayEffectSpecHandle EffectSpecHandle =
		TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
	//创建活动游戏效果句柄并将创建的效果规格应用到自身的ASC上
	const FActiveGameplayEffectHandle ActiveEffectHandle =
		TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	
	//创建是否为无限效果的标志
	const bool bIsInfinite =  EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	//如果效果是无限的，并且移除策略是在重叠结束时移除效果
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		//将该效果句柄和对应的能力系统组件添加到 ActiveEffectHandles 映射中
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}
}

//开始重叠时
void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

//结束重叠时
void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	//无限效果移除
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		//获取目标的能力系统组件
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;

		//创建一个数组来存储需要移除的效果句柄
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		//遍历 ActiveEffectHandles 映射，查找与目标角色能力系统组件匹配的效果句柄
		for (auto HandlePair : ActiveEffectHandles)
		{
			if (TargetASC == HandlePair.Value)
			{
				//移除目标角色上的指定效果
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				//将需要移除的效果句柄添加到 HandlesToRemove 数组中
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		//遍历 HandlesToRemove 数组，从 ActiveEffectHandles 映射中移除这些效果句柄
		for (auto& Handle : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}

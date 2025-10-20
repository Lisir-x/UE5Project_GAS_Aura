


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

//角色信息设置后
void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	//绑定效果应用回调函数
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::ClientEffectApplied);

}

//添加角色技能
void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const auto AbilityClass : StartupAbilities)
	{
		//创建能力规格
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		//尝试从能力规格中获取能力并转换为Aura游戏能力
		if (const UAuraGameplayAbility* AuraAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
		{
			//获取Aura游戏能力的启动输入标签并添加到能力规格中
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(AuraAbility->StartupInputTag);
			//赋予游戏规格能力
			GiveAbility(AbilitySpec);
		}
	}
}

//按键长按
void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	//输入标签为空则直接返回
	if (!InputTag.IsValid()) return;

	//遍历可激活的能力
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		//检查能力的动态标签是否与输入标签完全匹配
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			//触发与该能力规格相关的输入按下事件
			AbilitySpecInputPressed(AbilitySpec);
			//如果能力当前没有被激活则尝试激活该能力
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

//按键松开
void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	//输入标签为空则直接返回
	if (!InputTag.IsValid()) return;

	//遍历可激活的能力
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		//检查能力的动态标签是否与输入标签完全匹配
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			//触发与该能力规格相关的输入释放事件
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

//效果应用回调函数
void UAuraAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	//创建游戏标签容器并获取所有资产标签
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	//广播效果资产标签多播委托
	EffectAssetTags.Broadcast(TagContainer);
}

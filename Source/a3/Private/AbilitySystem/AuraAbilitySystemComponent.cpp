


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGameplayTags.h"

//角色信息设置后
void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	//绑定效果应用回调函数
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);

}

//效果应用回调函数
void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	//创建游戏标签容器并获取所有资产标签
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	//广播效果资产标签多播委托
	EffectAssetTags.Broadcast(TagContainer);
}

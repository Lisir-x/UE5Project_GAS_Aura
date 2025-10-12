


#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
	//创建能力系统组件
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);	//组件可复制
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed); //复制模式为Mixed

	//创建属性集组件
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
	//设置网络更新频率
	SetNetUpdateFrequency(100.f);
}

//获取能力系统组件
UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

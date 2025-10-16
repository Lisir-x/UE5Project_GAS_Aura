


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "a3/a3.h"

AAuraEnemy::AAuraEnemy()
{
	//设置网格体组件属性
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	//创建能力系统组件
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);	//组件可复制
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal); //复制模式为Minimal

	//创建属性集组件
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

//显示高亮
void AAuraEnemy::HighlightActor()
{
	//网格体和武器显示高亮并设定深度模板值
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

//取消高亮
void AAuraEnemy::UnHighlightActor()
{
	//网格体和武器取消高亮
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 AAuraEnemy::GetPlayerLevel()
{
	return Level;
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	//初始化角色信息
	InitAbilityActorInfo();
}

//初始化角色信息
void AAuraEnemy::InitAbilityActorInfo()
{
	//初始化信息
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	//调用AbilityActorInfoSet函数
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}




#include "Character/AuraEnemy.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "a3/a3.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/Widget/AuraUserWidget.h"

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

	//创建控件组件(血条)
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
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

//获取角色等级
int32 AAuraEnemy::GetPlayerLevel()
{
	return Level;
}

//死亡逻辑
void AAuraEnemy::Die()
{
	//设置生命周期
	SetLifeSpan(LifeSpan);
	Super::Die();
}

//受击反应标签变化回调函数
void AAuraEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	//计数大于0则处于受击反应状态
	bHitReacting = NewCount > 0;
	//根据是否处于受击反应状态来设置最大移动速度
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	//设置角色移动组件的最大移动速度
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	//初始化角色信息
	InitAbilityActorInfo();
	//赋予初始能力
	UAuraAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent);

	//尝试将自身控件组件转换为Aura用户控件并作为控件控制器
	if (UAuraUserWidget* AuraUserWidget = Cast<UAuraUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		AuraUserWidget->SetWidgetController(this);
	}
	//尝试将属性集转换为Aura属性集
	if (UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AttributeSet))
	{
		//绑定属性变化委托回调函数
		//生命值变化
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);
		//最大生命值变化
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

		//注册游戏标签事件监听器并添加受击反应标签变化回调函数
		AbilitySystemComponent->RegisterGameplayTagEvent(FAuraGameplayTags::Get().Effects_HitReact,
			EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&AAuraEnemy::HitReactTagChanged
		);

		//广播当前生命值和最大生命值
		OnHealthChanged.Broadcast(AuraAS->GetHealth());
		OnMaxHealthChanged.Broadcast(AuraAS->GetMaxHealth());
	}
}

//初始化角色信息
void AAuraEnemy::InitAbilityActorInfo()
{
	//初始化信息
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	//调用AbilityActorInfoSet函数
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	//初始化默认属性
	InitializeDefaultAttributes();
}

//初始化默认属性
void AAuraEnemy::InitializeDefaultAttributes() const
{
	//调用蓝图函数库的初始化默认属性函数
	UAuraAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass,
		Level, AbilitySystemComponent);
}




#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	//设置摄像机组件属性
	//角色不跟随控制器旋转
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	//设置角色移动组件属性
	GetCharacterMovement()->bOrientRotationToMovement = true;	//角色朝向移动方向
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f); //每秒旋转速率
	GetCharacterMovement()->bConstrainToPlane = true;	//角色的移动约束在平面上
	GetCharacterMovement()->bSnapToPlaneAtStart = true;	//角色对齐到指定的平面
}

//在服务器上初始化角色信息
void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
	//添加角色技能
	AddCharacterAbilities();
}

//在客户端上初始化角色信息
void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}

int32 AAuraCharacter::GetPlayerLevel()
{
	//创建角色状态
	const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);	//检查初始化
	//调用角色状态内联函数获取角色等级并返回
	return AuraPlayerState->GetPlayerLevel();
}

//初始化角色信息
void AAuraCharacter::InitAbilityActorInfo()
{
	//创建角色状态
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);	//检查初始化
	//获取能力系统组件并初始化角色信息
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	//转为UAuraAbilitySystemComponent并调用AbilityActorInfoSet函数
	Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	//设置能力系统组件和属性集组件
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();

	//尝试将当前控制器转换为AAuraPlayerController
	if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		//尝试将从AAuraPlayerController获取的HUD转换为AAuraHUD
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			//调用InitOverlay函数初始化覆层
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	//初始化默认属性
	InitializeDefaultAttributes();
}




#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	//复制玩家控制器到其他客户端
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);	//检查初始化

	//获取当前本地玩家的增强输入子系统实例
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)	//判断检查
	{
		//添加到增强输入子系统中，优先级为0
		Subsystem->AddMappingContext(AuraContext, 0);
	}

	//设置鼠标光标在屏幕上可见
	bShowMouseCursor = true;
	//设置默认的鼠标光标样式
	DefaultMouseCursor = EMouseCursor::Default;

	//创建输入模式对象
	FInputModeGameAndUI InputModeData;
	//设置鼠标锁定行为为不锁定
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//鼠标光标不会隐藏
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);	//应用设置
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//转换为增强输入组件
	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	//绑定移动
	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	//绑定技能输入操作
	AuraInputComponent->BindAbilityActions(InputConfig, this,
		&ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

//移动函数
void AAuraPlayerController::Move(const FInputActionValue& Value)
{
	//获取输入的二维向量
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	//获取控制器的旋转
	const FRotator Rotation = GetControlRotation();
	//只获取偏航角(Yaw)
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	//根据偏航角获取前方向(Y)和右方向(X)
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	//获取当前控制的Pawn
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		//根据输入向量的X和Y分量分别沿前方向(Y)和右方向(X)移动角色
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

//光标追踪
void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;	//存储射线检测的结果
	//返回第一个被命中的物体的信息
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	//如果没有命中任何物体则直接返回
	if (!CursorHit.bBlockingHit) return;

	//更新命中敌人接口对象
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	/**
	 * 从光标进行射线追踪的几种情况:
	 *  A. LastActor 和 ThisActor 都为空
	 *		-不做任何操作
	 *	B. LastActor 为空且 ThisActor 有效
	 *		-高亮 ThisActor
	 *	C. LastActor 有效且 ThisActor 为空
	 *		-取消高亮 LastActor
	 *	D. LastActor 和 ThisActor 都有效但不相同
	 *		-取消高亮 LastActor 并高亮 ThisActor
	 *	E. LastActor 和 ThisActor 都有效且相同
	 *		-不做任何操作
	 */

	//情况A
	if (!LastActor && !ThisActor) {/*不做任何操作*/}
	//情况B
	else if (!LastActor && ThisActor)
		ThisActor->HighlightActor();
	//情况C
	else if (LastActor && !ThisActor)
		LastActor->UnHighlightActor();
	else
	{
		//情况D
		if (LastActor != ThisActor)
		{
			LastActor->UnHighlightActor();
			ThisActor->HighlightActor();
		}
		//情况E
		else {/*不做任何操作*/}
	}
}

//按下事件回调函数
void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());
}

//松开事件回调函数
void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	//若获取的能力系统组件为空则直接返回
	if (GetASC() == nullptr) return;
	//获取到能力系统组件并执行松开按键处理函数
	GetASC()->AbilityInputTagReleased(InputTag);
}

//长按事件回调函数
void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	//若获取的能力系统组件为空则直接返回
	if (GetASC() == nullptr) return;
	//获取到能力系统组件并执行长按按键处理函数
	GetASC()->AbilityInputTagHeld(InputTag);
}

//获取能力系统组件
UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if (AuraAbilitySystemComponent == nullptr)
	{
		//获取Pawn转换为Aura能力系统组件
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraAbilitySystemComponent;
}

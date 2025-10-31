


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Character.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "UI/Widget/DamageTextComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	//复制玩家控制器到其他客户端
	bReplicates = true;

	//创建样条线组件
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	//光标追踪
	CursorTrace();
	//自动移动
	AutoRun();
}

//显示伤害数字
void AAuraPlayerController::ShowDamageNumber_Implementation(float DamageAmount, ACharacter* TargetCharacter)
{
	//若目标角色有效且存在伤害数字组件类
	if (IsValid(TargetCharacter) && DamageTextComponentClass)
	{
		//创建新的伤害数字组件
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		//注册组件
		DamageText->RegisterComponent();
		//附加到目标角色根组件上
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		//分离组件
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		//设置伤害数字
		DamageText->SetDamageText(DamageAmount);
	}
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
	//绑定Shif键按下和松开操作
	AuraInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &AAuraPlayerController::ShiftPressed);
	AuraInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &AAuraPlayerController::ShiftReleased);
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
	//返回第一个被命中的物体的信息
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	//如果没有命中任何物体则直接返回
	if (!CursorHit.bBlockingHit) return;

	//更新命中敌人接口对象
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	//若上一次和当前命中的对象不一致
	if (LastActor != ThisActor)
	{
		//上一个对象取消高亮显示，当前对象高亮显示
		if (LastActor) LastActor->UnHighlightActor();
	    if (ThisActor) ThisActor->HighlightActor();
	}
}

//按下事件回调函数
void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//左键输入
	if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		//设置是否处于锁定中
		bTargeting = ThisActor ? true : false;
		//设置自动移动中为假
		bAutoRunning = false;
	}
}

//松开事件回调函数
void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	//非左键输入
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		//若获取到能力系统组件则执行松开按键处理函数
		if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
		//否则直接返回
		return;
	}
	
	//若获取到能力系统组件则执行松开按键处理函数
	if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
	
	//未处于锁定中或未按下Shift键，执行点击移动处理
	if (!bTargeting && !bShiftKeyDown)
	{
		//创建并获取Pawn
		const APawn* ControlledPawn = GetPawn();
		//判断点击时间是否小于短按阈值时间且Pawn是否有效
		if (FollowTime < ShortPressThreshold && ControlledPawn)
		{
			//获取从角色本地位置到目标位置的导航路径
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(
				this, ControlledPawn->GetActorLocation(), CachedDestination))
			{
				//先清理样条点
				Spline->ClearSplinePoints();
				//遍历导航路径点
				for (const FVector& PointLoc : NavPath->PathPoints)
				{
					//将路径点绘制成样条点
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
				}
				//取导航路径生成的最后一个点作为目标位置
				CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
				//设置自动移动中为真
				bAutoRunning = true;
			}
		}
		//重置点击时间为0且设置不处于锁定中
		FollowTime = 0.f;
		bTargeting = false;
	}
}

//长按事件回调函数
void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	//非左键输入
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		//若获取到能力系统组件则执行长按按键处理函数
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
		//否则直接返回
		return;
	}

	//处于锁定中或按住Shift键
	if (bTargeting || bShiftKeyDown)
	{
		//若获取到能力系统组件则执行长按按键处理函数
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
	}
	//未处于锁定中，执行长按移动处理
	else
	{
		//设置点击时间
		FollowTime += GetWorld()->GetDeltaSeconds();

		//若有命中则将命中点设置为目标位置
		if (CursorHit.bBlockingHit) CachedDestination = CursorHit.ImpactPoint;

		//创建并尝试获取Pawn
		if (APawn* ControlledPawn = GetPawn())
		{
			//创建角色到目标位置的方向
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			//调用AddMovementInput函数让角色朝移动方向移动
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
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

//自动移动
void AAuraPlayerController::AutoRun()
{
	//若不处于自动移动中则直接返回
	if (!bAutoRunning) return;
	//创建并获取Pawn
	if (APawn* ControlledPawn = GetPawn())
	{
		//找到角色当前位置在样条线上最接近的位置
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(
			ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		//计算该位置的切线方向
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(
			LocationOnSpline, ESplineCoordinateSpace::World);
		//将计算出的方向作为移动输入添加到 Pawn 中，使角色沿着样条线移动
		ControlledPawn->AddMovementInput(Direction);

		//计算样条线上的位置和目标位置之间的距离
		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		//检查该距离是否小于等于自动移动接受半径
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			//自动移动结束，设置bAutoRunning为false
			bAutoRunning = false;
		}
	}
}

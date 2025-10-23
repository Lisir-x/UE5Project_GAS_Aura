

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class USplineComponent;
class UAuraAbilitySystemComponent;
class UAuraInputConfig;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;

UCLASS()
class A3_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();

	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:
	//输入映射上下文
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	//移动输入
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	//Shift键输入
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> ShiftAction;

	//Shift键处理函数(内联函数)
	void ShiftPressed() { bShiftKeyDown = true; }
	void ShiftReleased() { bShiftKeyDown = false; }
	//Shift键是否按下的标志
	bool bShiftKeyDown = false;

	//移动函数
	void Move(const FInputActionValue& Value);

	//光标追踪
	void CursorTrace();
	//存储上一次和当前被命中的敌人接口对象
	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;
	//光标命中结果
	FHitResult CursorHit;

	//输入配置
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	//按下、松开、长按事件回调函数
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	//Aura能力系统组件
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	//获取能力系统组件
	UAuraAbilitySystemComponent* GetASC();

	//目标位置缓存
	FVector CachedDestination = FVector::ZeroVector;
	//点击时间
	float FollowTime = 0.f;
	//短按时间阈值
	float ShortPressThreshold = 0.5f;
	//自动移动中
	bool bAutoRunning = false;
	//锁定中
	bool bTargeting = false;

	//自动移动接受半径
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	//样条线组件
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	//自动移动
	void AutoRun();
};

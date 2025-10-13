

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

//应用效果策略枚举
UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

//移除效果策略枚举
UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class A3_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();
	
protected:
	virtual void BeginPlay() override;

	//应用游戏效果蓝图函数
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	//开始重叠时
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	//结束重叠时
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	//是否移除效果时销毁
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	bool bDestroyOnEffectRemoval = false;
	
	//即时效果类
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	//即时效果应用策略
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	//持续效果类
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	//持续效果应用策略
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	//无限效果类
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	//无限效果应用策略
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	//无限效果移除策略
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	//将游戏效果句柄映射到能力系统组件
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	//角色等级
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	float ActorLevel = 1.f;
};

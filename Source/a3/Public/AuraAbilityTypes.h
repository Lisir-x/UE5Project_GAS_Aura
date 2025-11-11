
#pragma once

#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"

//自定义游戏效果上下文结构体
USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

	//是否暴击、格挡
	bool IsCriticalHit() const { return bIsCriticalHit; }
	bool IsBlockedHit () const { return bIsBlockedHit; }

	//设置暴击、格挡
	void SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	void SetIsBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }
	
	/** 返回用于序列化的实际结构体，子类必须重写此方法！ */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return StaticStruct();
	}
	
	/** 创建此上下文的副本，用于后续修改 */
	virtual FGameplayEffectContext* Duplicate() const
	{
		//创建一个新的游戏效果上下文实例，并将当前实例的内容复制到这个新实例中
		FGameplayEffectContext* NewContext = new FGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			//对命中结果进行深拷贝
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	/** 自定义序列化，子类必须重写此方法 */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
	
protected:
	//格挡标志
	UPROPERTY()
	bool bIsBlockedHit = false;

	//暴击标志
	UPROPERTY()
	bool bIsCriticalHit = false;
	
};

//针对Aura游戏效果上下文的特化模板
template<>
struct TStructOpsTypeTraits<FAuraGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FAuraGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true, //支持网络序列化
		WithCopy = true		//支持复制操作
	};
};



#include "AbilitySystem/MMC/MMC_MaxHealth.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	//要捕获的属性，属性源，是否快照
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false; //false-效果应用时捕获属性；true-效果规格创建时捕获属性

	//属性添加到用来捕获属性的数组
	RelevantAttributesToCapture.Add(VigorDef);
}

//自定义计算函数
float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//从效果规格中捕获所有源和目标标签
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	//将捕获的标签传入用来存储属性的结构体(聚合器评估参数)中
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Vigor = 0.f;
	//获取捕获的属性的数值
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluateParameters, Vigor);
	//限制属性的最低值为0
	Vigor = FMath::Max<float>(Vigor, 0.f);

	//获取角色等级
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 80.f + 2.f * Vigor + 20.f * PlayerLevel;
}

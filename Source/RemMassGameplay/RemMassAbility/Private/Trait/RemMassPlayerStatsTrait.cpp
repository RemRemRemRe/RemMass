// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassPlayerStatsTrait.h"

#include "MassEntityTemplateRegistry.h"
#include "RemMassAbilityLog.h"
#include "RemMassAbilityTags.h"
#include "Engine/CurveTable.h"
#include "Fragment/RemMassAbilityFragments.h"
#include "Macro/RemAssertionMacros.h"
#include "Macro/RemLogMacros.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassPlayerStatsTrait)

void URemMassPlayerStatsTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	RemCheckVariable(CurveTable, return);
	
	BuildContext.AddFragment_GetRef<FRemMassLevelCurveTableFragment>().Value = CurveTable;
	BuildContext.AddFragment<FRemMassExperienceFragment>();

	static const auto ContextString = FString{TEXTVIEW("URemMassPlayerStatsTrait::BuildTemplate")};
	
	const auto* RealCurve = CurveTable->FindCurve(
		Rem::GetDefaultRef<URemMassAbilityTags>().GetRequiredExpToLevelUpTag().GetTagName(), ContextString);

	RemCheckVariable(RealCurve, return;);
	
	BuildContext.AddFragment_GetRef<FRemMassLevelUpExperienceFragment>().Value = RealCurve->Eval(
		BuildContext.AddFragment_GetRef<FRemMassLevelFragment>().Value, std::numeric_limits<float>::max());
}

void URemMassPlayerStatsTrait::ValidateTemplate(FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World) const
{
	Super::ValidateTemplate(BuildContext, World);

	if (!BuildContext.HasTag<FRemMassPlayerTag>())
	{
		REM_LOG_FUNCTION(LogRemMassAbility, Error, TEXT("{0} is required for a player entity"), FRemMassPlayerTag::StaticStruct()->GetName());
	}
}

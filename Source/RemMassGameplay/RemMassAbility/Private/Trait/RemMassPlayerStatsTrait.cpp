// Copyright RemRemRemRe, All Rights Reserved.


#include "Trait/RemMassPlayerStatsTrait.h"

#include "MassEntityTemplateRegistry.h"
#include "RemMassAbilityTags.h"
#include "RemMisc.h"
#include "Engine/CurveTable.h"
#include "Fragment/RemMassAbilityFragments.h"
#include "Macro/RemAssertionMacros.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RemMassPlayerStatsTrait)

void URemMassPlayerStatsTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	RemCheckVariable(CurveTable, return);
	
	BuildContext.AddFragment_GetRef<FRemMassLevelCurveTableFragment>().Value = CurveTable;
	BuildContext.AddFragment<FRemMassExperienceFragment>();

	static const auto ContextString = FString{TEXTVIEW("URemMassPlayerStatsTrait::BuildTemplate")};
	
	const auto* RealCurve = CurveTable->FindCurve(
		Rem::Common::GetDefaultRef<URemMassAbilityTags>().GetRequiredExpToLevelUpTag().GetTagName(), ContextString);

	RemCheckVariable(RealCurve, return;);
	
	BuildContext.AddFragment_GetRef<FRemMassLevelUpExperienceFragment>().Value = RealCurve->Eval(
		BuildContext.AddFragment_GetRef<FRemMassLevelFragment>().Value, std::numeric_limits<float>::max());
}

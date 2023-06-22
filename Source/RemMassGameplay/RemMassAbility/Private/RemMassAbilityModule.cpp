// Copyright RemRemRemRe, All Rights Reserved.

#include "RemMassAbilityModule.h"

class FRemMassAbilityModule : public IRemMassAbilityModule
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FRemMassAbilityModule, RemMassAbility)

void FRemMassAbilityModule::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
	IRemMassAbilityModule::StartupModule();
}

void FRemMassAbilityModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	IRemMassAbilityModule::ShutdownModule();
}

// Copyright RemRemRemRe, All Rights Reserved.

#include "RemMassHUDModule.h"

class FRemMassHUDModule : public IRemMassHUDModule
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FRemMassHUDModule, RemMassHUD)

void FRemMassHUDModule::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
	IRemMassHUDModule::StartupModule();
}

void FRemMassHUDModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	IRemMassHUDModule::ShutdownModule();
}

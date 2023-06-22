// Copyright RemRemRemRe, All Rights Reserved.

#include "RemMassMovementModule.h"

class FRemMassMovementModule : public IRemMassMovementModule
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FRemMassMovementModule, RemMassMovement)

void FRemMassMovementModule::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
	IRemMassMovementModule::StartupModule();
}

void FRemMassMovementModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	IRemMassMovementModule::ShutdownModule();
}

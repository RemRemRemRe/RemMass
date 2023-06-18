// Copyright Epic Games, Inc. All Rights Reserved.

#include "RemMassModule.h"

class FRemMassModule : public IRemMassModule
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FRemMassModule, RemMass)

void FRemMassModule::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
	IRemMassModule::StartupModule();
}

void FRemMassModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	IRemMassModule::ShutdownModule();
}
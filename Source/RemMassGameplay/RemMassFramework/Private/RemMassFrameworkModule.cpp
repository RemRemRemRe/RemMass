// Copyright RemRemRemRe, All Rights Reserved.

#include "RemMassFrameworkModule.h"
#include "Modules/ModuleManager.h"

IRemMassFrameworkModule& IRemMassFrameworkModule::Get()
{
	return FModuleManager::LoadModuleChecked< IRemMassFrameworkModule >( "RemMassFramework" );
}

bool IRemMassFrameworkModule::IsAvailable()
{
	return FModuleManager::Get().IsModuleLoaded( "RemMassFramework" );
}


class FRemMassFrameworkModule : public IRemMassFrameworkModule
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FRemMassFrameworkModule, RemMassFramework)

void FRemMassFrameworkModule::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
	IRemMassFrameworkModule::StartupModule();
}

void FRemMassFrameworkModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	IRemMassFrameworkModule::ShutdownModule();
}

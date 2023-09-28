// Copyright RemRemRemRe, All Rights Reserved.

#include "RemMassInventoryModule.h"
#include "Modules/ModuleManager.h"

IRemMassInventoryModule& IRemMassInventoryModule::Get()
{
	return FModuleManager::LoadModuleChecked< IRemMassInventoryModule >( "RemMassInventory" );
}

bool IRemMassInventoryModule::IsAvailable()
{
	return FModuleManager::Get().IsModuleLoaded( "RemMassInventory" );
}

class FRemMassInventoryModule final : public IRemMassInventoryModule
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FRemMassInventoryModule, RemMassInventory)

void FRemMassInventoryModule::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
	IRemMassInventoryModule::StartupModule();
}

void FRemMassInventoryModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	IRemMassInventoryModule::ShutdownModule();
}

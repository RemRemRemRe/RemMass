// Copyright RemRemRemRe. 2026. All Rights Reserved.

#include "Components/RemMassHUDBinderComponent.h"

#include "Misc/AutomationTest.h"
#include "RemMassHUDEntitySpawnData.h"
#include "Task/RemMassHUDWidgetTask.h"

#if WITH_DEV_AUTOMATION_TESTS

DEFINE_SPEC(FRemMassHUDBindingTest, "Rem.MassHUD.Binding",
    EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter);

void FRemMassHUDBindingTest::Define()
{
    Describe(TEXT("TransformBindings"), [this]
    {
        It(TEXT("should transform bindings to fragments preserving order"), [this]
        {
            FRemMassHUDBinding First;
            First.FragmentTypes.Add(FRemMassHUDBindingFragment::StaticStruct());
            First.Task = TInstancedStruct<FRemMassHUDTask>::Make<FRemMassHUDWidgetTask>();

            FRemMassHUDBinding Second;
            Second.FragmentTypes.Add(FRemMassHUDBindingFragment::StaticStruct());

            const TArray<FRemMassHUDBindingFragment> Fragments = FRemMassHUDBinding::TransformBindings({First, Second});

            TestEqual(TEXT("count"), Fragments.Num(), 2);
            if (Fragments.Num() != 2)
            {
                return;
            }

            TestEqual(TEXT("first fragment types"), Fragments[0].FragmentTypes.Num(), 1);
            TestTrue(TEXT("first task type preserved"),
                Fragments[0].Task.GetScriptStruct() == FRemMassHUDWidgetTask::StaticStruct());
            TestEqual(TEXT("second fragment types"), Fragments[1].FragmentTypes.Num(), 1);
            TestFalse(TEXT("second task empty"), Fragments[1].Task.IsValid());
        });

        It(TEXT("should transform an empty binding list to an empty fragment list"), [this]
        {
            const TArray<FRemMassHUDBindingFragment> Fragments = FRemMassHUDBinding::TransformBindings({});
            TestEqual(TEXT("empty"), Fragments.Num(), 0);
        });

        It(TEXT("should transform a single binding via TransformBinding"), [this]
        {
            FRemMassHUDBinding Binding;
            Binding.FragmentTypes.Add(FRemMassHUDBindingFragment::StaticStruct());

            const FRemMassHUDBindingFragment Fragment = FRemMassHUDBinding::TransformBinding(Binding);
            TestEqual(TEXT("fragment types"), Fragment.FragmentTypes.Num(), 1);
            TestFalse(TEXT("task empty"), Fragment.Task.IsValid());
        });
    });
}

#endif // WITH_DEV_AUTOMATION_TESTS

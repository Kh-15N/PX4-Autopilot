#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/module.h>
#include <px4_platform_common/log.h>
#include <px4_platform_common/tasks.h>

extern "C" __EXPORT int my_module_main(int argc, char *argv[]);

class MyModule : public ModuleBase<MyModule>
{
public:
    static int task_spawn(int argc, char *argv[]);
    static int custom_command(int argc, char *argv[]);
    static int print_usage(const char *reason = nullptr);
    
    void run() override;
};

int MyModule::task_spawn(int argc, char *argv[])
{
    MyModule *instance = new MyModule();
    
    if (instance) {
        _object.store(instance);
        _task_id = task_id_is_work_queue;
        PX4_INFO("Hello cruel world!");
        return PX4_OK;
    } else {
        PX4_ERR("alloc failed");
        return PX4_ERROR;
    }
}

void MyModule::run()
{
    PX4_INFO("My Module started!");
    
    while (!should_exit()) {
        PX4_INFO("My module is running...");
        sleep(1);
    }
    
    PX4_INFO("My Module stopped.");
}

int MyModule::custom_command(int argc, char *argv[])
{
    if (!strcmp(argv[0], "start")) {
        return task_spawn(argc, argv);
    }

    if (!strcmp(argv[0], "status")) {
        if (is_running()) {
            PX4_INFO("my_module is running");
        } else {
            PX4_INFO("my_module is not running");
        }
        return PX4_OK;
    }
    
    return print_usage("unknown command");
}

int MyModule::print_usage(const char *reason)
{
    if (reason) {
        PX4_WARN("%s\n", reason);
    }
    
    PRINT_MODULE_DESCRIPTION(
        R"DESCR_STR(
### Description
My test module
)DESCR_STR");

    PRINT_MODULE_USAGE_NAME("my_module", "driver");
    PRINT_MODULE_USAGE_COMMAND("start");
    PRINT_MODULE_USAGE_DEFAULT_COMMANDS();
    
    return 0;
}

int my_module_main(int argc, char *argv[])
{
    return MyModule::main(argc, argv);
}
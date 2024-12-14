#include "connection_manager/connection_manager.h"
#include "execution_router/execution_router.h"
#include "execution_router/executors/executors.h"
#include "injector.h"

ExecutionRouter execution_router{};
Injector injector;

int main(int argc, char *argv[])
{
    injector.getConfigManager().LoadConfigsFromCommandLineFlags(argc, argv);

    // TODO: Consider moving the binding of executors elsewhere.
    execution_router.Bind("PING", HandlePing);
    execution_router.Bind("WRITE", HandleWrite);
    execution_router.Bind("QUERY", HandleQuery);
    // TODO: Allow for the setting of the port from a flag.
    ConnectionManager cm{8000};
    cm.Start();
    return 0;
}

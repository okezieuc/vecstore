#ifndef VECSTORE_EXECUTORS
#define VECSTORE_EXECUTORS

#include "../../connection_manager/connection_manager_shared.h"
#include "../../transcoder/transcoder.h"

void HandlePing(Request request, Client client);
void HandleWrite(Request request, Client client);

#endif // VECSTORE_EXECUTORS
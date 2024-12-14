#include "executors.h"
#include "injector.h"
#include "shared/exceptions.h"

/*
It is assumed all requests sent to this have been pre-validated
with Transcoder::Validate. Always verify requests before passing
them to be handled here.
*/
void HandleWrite(Request request, Client client)
{
    // we only handle write requests for single vectors
    try
    {
        if (request.get_vcount() != 1)
        {
            // let user know that we only handle queries for storing one vector
            Request res{};
            res.set_command("ERR").set_modifier("WRITE").set_status(901);
            client.Send(Transcoder::Encode(res));
            return;
        }

        // request.get_vectors()[0] is guaranteed to be valid since we assume
        // requests are prevalidated and the codeblock above plus the validatiom
        // requirement that --vcount matches the number of vectors guarantees that
        // there is exactly one vector in the request.
        int key = injector.getStore().Write(request.get_vectors()[0]);

        Request res{};
        res.set_command("DONE").set_modifier("WRITE").set_vcount(1).set_keys({key});
        client.Send(Transcoder::Encode(res));
        return;
    }
    catch (const VecStoreExceptions &e)
    {
        if (e.getError() == VS_ERROR_INVALID_VECTOR_SIZE)
        {
            Request res{};
            res.set_command("ERR").set_modifier("WRITE").set_status(VecStoreError::Get(e.getError()).GetErrorCode());
            client.Send(Transcoder::Encode(res));
            return;
        }
    }
}

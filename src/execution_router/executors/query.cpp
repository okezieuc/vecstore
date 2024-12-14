#include "executors.h"
#include "injector.h"
#include "shared/exceptions.h"

/*
The current implementation for this only returns the keys of the most similar
vectors. In future implementations, we will want to return the similarities too.

It is assumed all requests sent to this have been pre-validated
with Transcoder::Validate. Always verify requests before passing
them to be handled here.
*/
void HandleQuery(Request request, Client client)
{
    try
    {
        std::vector<StoreQueryResponse *> queryResponseData = injector.getStore().Query(request.get_vectors()[0]);
        Request res{};
        res.set_command("DONE").set_modifier("QUERY").set_vcount(queryResponseData.size());

        vector<int> keys;
        for (auto similarEntry : queryResponseData)
            keys.push_back(similarEntry->id);
        res.set_keys(keys);
        client.Send(Transcoder::Encode(res));
        return;
    }

    // TODO: It appears it might be a better option to handle VecStoreExceptions in the execution
    // router. Much later, get back to this, investigate if this is the case, and if so, refactor
    // the code for error handling.
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

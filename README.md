# vecstore
A vector database


## Error Code Translations:
- 400: The server is unable to respond to your request.
- 401: Invalid query. The query is invalid and unparsable. Data might have been provided without relevant flags. Incomplete data might have been sent. It's also possible that the request contains more bytes than the maximum receivable bytes. (See `connection_manager::handle_connection`).
- 402: Invalid query. The query can be parsed but is invalid. it is likely that there are arrays of values that were provided more or fewer values than expected. Only send the amount of data required to exactly describe the request to be made, as described in the protocol.
- 413: The size of the received vector does not match what was expected. This happens when a user tries to store a vector with a dimensionality that does not match the dimensionality of the database.
- 499: An error occured while handling this request.

## 900-Code Translations
900 error codes are used when communicating to clients about errors that occur when a command that should normally be "processable" is received, but is not supported by the present version of the server.
- 901: Only write requests with vcount==1 are supported. Sending a request to write multiple vectors at once is not currently supported.
![round_logo](./img/round_logo.png)

# Round-RPC Specfication

Round is based on [JSON-RPC 2.0][json-rpc], and Round extends the specification to develop distributed system applications as the following.

## Object Field Extentions

Round adds the following original fields to [JSON-RPC 2.0][json-rpc] specification.

| Field | Descripton | Default | Detail |
| - | - | - | - |
| dest | - | - | |
| cond | - | - |  |
| ts | - | - | The field is handled automatically by Round |
| digest | - | (none) | - |

### dest

The dest field specifies a destination node of the request object. The node which is received the request object checks the hash code whether the node should execute the request object.  

```
dest = [ "." | "?" | "*" | SHA256-HASH ]
```

The local node is selected if the dest field is ".", and a random node is selected automatically in the same cluster if the dest field is "?". All node are selected in the cluster when the dest field is "\*".

If the dest field is null, the node which is received the message is selected.

#### Request object

The dest field specifies a destination node of the message. In the current version, the hash code must be genarated using [SHA-256](http://en.wikipedia.org/wiki/SHA-2). If the dest field is not specified, the message is executed by the received node.

```
--> {"jsonrpc": "2.0", "method": "increment_counter", "params": 1, "dest": "xxxxxxxxxxxxxxxx", ....}
```

```
--> {"jsonrpc": "2.0", "method": "increment_counter", "params": 1, "dest": "all", ....}
```

#### Response object

The message is executed if the specified dest code is handled by the received node, otherwise the node doen't executed the message and returns a error object including the detail error code as the following.

```
<-- {"jsonrpc": "2.0", "error": {"code": -32002, "message": "Moved Permanently"}, ....}
```

If the node returns the error object, the cluster might be updated because of adding or removing nodes. To update the current cluster information, Use '[_get_cluster_info](./round_rpc_methods.md)' method for the node to get the latest cluster information.

If the target nodes are two or more nodes, the response object has an array containing the corresponding response objects of each target nodes like batch response of JSON-RPC specification.
```
[
{"jsonrpc": "2.0", "result": 7, "id": "1", "dest": "xxxxxxxxxxxxxxxx", .....},
{"jsonrpc": "2.0", "result": 8, "id": "1", "dest": "xxxxxxxxxxxxxxxx", .....},
{"jsonrpc": "2.0", "result": 6, "id": "1", "dest": "xxxxxxxxxxxxxxxx", .....},
{"jsonrpc": "2.0", "result": 9, "id": "1", "dest": "xxxxxxxxxxxxxxxx", .....},
{"jsonrpc": "2.0", "result": 2, "id": "1", "dest": "xxxxxxxxxxxxxxxx", .....},
]
```

### cond

The field specifies a condition by JavaScript whether the message is executed. In the condition, you can use two variables, 'params' and 'prev_result'.

```
cond = JS_SCRIPT
```

#### Request object

The 'params' is a same variable in the request object ast the following.

```
--> {"jsonrpc": "2.0", "method": "deposit", "params": "{}", "cond": "(0 < params[\"amount\"])" }
```

The 'prev_result' is enabled only when the request message is a batch request. Using the field, you can only execute a request when the previos request is success.

```
--> [
{"jsonrpc": "2.0", "method": "deposit", .... },
{"jsonrpc": "2.0", "method": "withdraw", "cond" : "(prev_result[\"success\"] == \"true\")" , .... },
]
```

### ts (timestamp)

Round adds a timestamp parameter based on [Lamport timestamps][lamport-timestamps] to know the operation causality. In Round, the timestamp parameter is added and controlled automatically.

##### Request object

The parameter has a logical timestamp number of the client. If it is not included it is assumed to be a non-casual request, the logical clock of the requested remote node is not updated.

###### RPC call with timestamp
```
--> {"jsonrpc": "2.0", "method": "increment_counter", "params": 1, "id": 1, "ts": 1}
<-- {"jsonrpc": "2.0", "result": 102, "id": 1, ts:3}
--> {"jsonrpc": "2.0", "method": "increment_counter", "params": 1, "id": 1, "ts": 5}
<-- {"jsonrpc": "2.0", "result": 103, "id": 1, ts:7}
```

###### RPC call without timestamp
```
--> {"jsonrpc": "2.0", "method": "increment_counter", "params": 1, "id": 1}
<-- {"jsonrpc": "2.0", "result": 102, "id": 1, ts:2}
--> {"jsonrpc": "2.0", "method": "increment_counter", "params": 1, "id": 1}
<-- {"jsonrpc": "2.0", "result": 103, "id": 1, ts:2}
```

##### Response object

The all response object has the parameter. The parameter has a logical timestamp number of the remote node.

When the request object has the parameter, the remote node updates the local logical timestamp using the request logical timestamp, and the remote node returns the updated logical timestamp in the response object.

When the request object hasn't the parameter, the remote node does't update the local logical timestamp, and the remote node returns the current timestamp in the response object.

[lamport-timestamps]: http://en.wikipedia.org/wiki/Lamport_timestamps

## Error code

Round added the folloinwg error codes in the  implementation defined range [JSON-RPC][json-rpc]. Round returns the following error code when the specified method couldn't be executed.

| code | message | description |
|-|-|-|
| -32000 | Bad Hash Length | - |
| -32001 | Moved Permanently | - |
| -32010 | Condition Failed | - |
| -32020 | Internal Script Engine Error | - |
| -32021 | Invalid Script Language | - |
| -32022 | Invalid Script Code | - |
| -32023 | Script Runtime Error  | - |

## Asynchronous Request

Round is based on [JSON-RPC over HTTP][json-rpc-http], but Round extends the specification to support asynchronous [RPC][rpc].

### HTTP Header

In addition to standard headers of [JSON-RPC over HTTP][json-rpc-http], Round supports the following extra headers.

#### X-Async-Location

```
X-Aync-Location = locationURI
locationURI = protocol "://" host ":" port
prorocol = "http" | "httpu"
```

The request over HTTPU or HTTPMU SHOULD has this header to receive the result response. If the header is not included in a request message over HTTPU or HTTPMU, the request is recognized as a notification request even if the request has a 'id' member.

### GET

#### encode

The 'params' field must be encorded in [JSON-RPC over HTTP][json-rpc-http]. The encode field disables the encoding to use HTTP command line utilities such as 'curl' command more easily.

```
encode = none"
```

### Response Code

For the asynchronous request, Round returns the following HTTP status code immediately.

| Code | Status | Description |
| - | - | - |
| 202 | Accepted | 'result' member is not inclued |
| 302 | Moved Permanently | - |
| 500 | Internal Server Error | - |

Round doesn't check the request message in more detail. Thus all JSON-RPC errors such as 'Parser Error' are returns into the specified location asynchronously.

The 'result' member is required on success in [JSON-RPC][json-rpc]. However, Round does't include the result member in the immediate response for asynchronous request because the operation is not executed yet.


[rpc]: http://en.wikipedia.org/wiki/Remote_procedure_call
[json-rpc]: http://www.jsonrpc.org/specification
[json-rpc-http]: http://jsonrpc.org/historical/json-rpc-over-http.html


For efficient communication for between the nodes, we will support more efficient remote procedure call like  [BSON](http://bsonspec.org) in the future release.

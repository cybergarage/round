![round_logo](../img/round_logo.png)

## Lua

Round supports Lua. Currently Round provides the following special functions.

| Function | Description |
| --- | --- |
| set_registry(key, value) | Sets the specified key and value into the local node registry. |
| get_registry(key) | Gets a registry by the specified key from the local node registry. |
| post_method(method, params, obj) | Posts a RPC message to the specified node. |
| get_network_state() | Returns all clusters and nodes in the local node. |
| get_cluster_state() | Returns all nodes in the local node. |
| get_node_state()  |Returns the local node status |

The functions returns JSON responses, then you should JSON package such as [JSON4Lua](http://json.luaforge.net) to parse the responses.

### Functions

#### set_registry(key, value)

The set_registry function sets the specified key and value into the local node registry.

##### Parameters

- key : string
- value : string

##### Return values

- true or false

##### Example

The following code shows how to use the set_registry function.

```
key = "name"
val = "Satoshi Konno"
ok = set_registry(key, val)
```

#### get_registry(key)

The get_registry function returns a registry by the specified key from the local node registry.

##### Parameters

- key : string

##### Return values

- first : true or false
- second : a JSON string of the specified registry, or a blank string when the specified registry is not found.

```
{
  "key"  : <string value>
  "value": <string value>,
  "ts"   : <integer value>
  "lts"  : <integer value>
}
```

##### Example

The following code shows how to use the get_registry function.

```
json = require("json") -- JSON4Lua
ok, result = get_registry("name");
if (ok) {
  jsonReg = json.decode(result)
  value = jsonReg["value"]
  .....
}
```

#### post_method(method, params, obj)

The post_method posts a RPC message to the specified node.

##### Parameters

- method : string
- params : string or JSON string
- obj : node hash or the local node is selected when the parameter is not specified or ''

##### Return values

- first : true or false
- second : a JSON string of the specified method result, or  a blank string when the method is failed.

##### Example

The following code shows how to use the post_method function.

```
key = "name"
val = "Satoshi Konno"
ok, result = post_method('get_registry', ''{"key": "name"}', '')
if (ok) {
  .....
}
```

#### get_network_state()

The get_network_state function returns all clusters and nodes which the local node knows.

##### Parameters

This function has no parameter.

##### Return values

- a JSON string of the network state.

Please check `get_network_state` of [RPC Methods](round_rpc_methods.md) to know the response object in more detail.

##### Example

```
json = require("json") -- JSON4Lua
result = get_network_state()
jsonResult = json.decode(result)
clusterCount = #jsonResult["clusters"]
```

#### get_cluster_state()

The get_cluster_state function returns all nodes which the local node knows in the same cluster.

##### Parameters

This function has no parameter.

##### Return values

- a JSON string of the cluster state.

Please check `get_cluster_state` of [RPC Methods](round_rpc_methods.md) to know the response object in more detail.

##### Example

```
json = require("json") -- JSON4Lua
result = get_cluster_state()
jsonResult = json.decode(result)
nodeCount = #jsonResult["cluster"]["nodes"]
```

#### get_node_state()

The get_node_state function returns the local node status.

##### Parameters

This function has no parameter.

##### Return values

- a JSON string of the node state.

Please check `get_node_state` of [RPC Methods](round_rpc_methods.md) to know the response object in more detail.

##### Example

```
json = require("json") -- JSON4Lua
result = get_network_state()
jsonResult = json.decode(result)
nodeAddr = jsonResult["addr"]
nodePort = jsonResult["port"]
nodeHash = jsonResult["hash"]
```

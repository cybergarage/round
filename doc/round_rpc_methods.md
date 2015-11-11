![round_logo](./img/round_logo.png)

# RPC Methods

Round node has some embedded system methods which are added using native or dynamic programming languages as default.

## System Methods

In the system methods, there are two kind of types: the static and dynamic. The static method can't be overriden by developers, but the dynamic method can can be overriden using 'set_method'.

### Static Methods

Round has the following static methods as default. The methods are implemented using the native programming language, developers can't redefine the static methods.

| Type | Name | Description |
| --- | --- | --- |
| Method | set_method | Set a new script method |
| | remove_method | Remove a specified method |
| Route | set_route | Set a new route |
| | remove_route | Remove a specified route |
| Timer | set_timer | Set a new timer |
| | remove_timer | Remove a specified timer |
| Alias | set_alias | Set a alias for the other method |
| | remove_alias | Remove a specified alias |
| Job | post_job | Post a job |

#### set_method

The set_method method sets a new method into the local node.

##### Parameters

```
set_method = "{" name language code encoding "}"

name     = "name" ":" TOKEN
language = "language" ":" supported-language
code     = "code" ":" TOKEN
encoding = "encoding" ":" ("none" | "base64")

supported-language = ("js" | "java" | "tcl" | "lua")
```

##### Return values

The set_method method doesn't return anything when the method is success, otherwise returns a error object.

#### remove_method

The remove_method method removes a specified method from the local node.

##### Parameters

```
remove_method = "{" name "}"

name     = "name" ":" TOKEN
```

##### Return values

The remove_method method doesn't return anything when the method is success, otherwise returns a error object.

#### set_route

The set_route method sets a new route into the local node.

##### Parameters

```
set_route = "{" source destnation [name] [type] [cond] [params] "}"

name       = "name"   ":" TOKEN
source     = "src"    ":" source-object
destnation = "dest"   ":" destnation-object
type       = "type"   ":" ("pipe" | "event")
cond       = "cond"   ":" JS_SCRIPT
params     = "params" ":" "{" *(param) "}"

source-object     = (trigger-name | method-name)
destnation-object = [cluster "."] [node "."] (method-name)
cluster           = ("local" | cluster-name)
node              = ("local" | "all" | "*" | hash-code)
cluster-name      = TOKEN
hash-code         = NODE_HASH
trigger-name      = TOKEN
method-name       = TOKEN

param                      = dest-in-param-name ":" dest-in-param-value-script
dest-in-param-name         = TOKEN
dest-in-param-value-script = JS_SCRIPT
```

##### Return values

The set_route method doesn't return anything when the method is success, otherwise returns a error object.

#### remove_route

The remove_route method removes a specified route from the local node.

##### Parameters

```
set_route = "{" name | (source destnation) "}"

name       = "name"   ":" TOKEN
source     = "src"    ":" source-object
destnation = "dest"   ":" destnation-object

source-object     = (trigger-name | method-name)
destnation-object = [cluster "."] [node "."] (method-name)
cluster           = ("local" | cluster-name)
node              = ("local" | "all" | "*" | hash-code)
cluster-name      = TOKEN
hash-code         = NODE_HASH
trigger-name      = TOKEN
method-name       = TOKEN
```

##### Return values

The remove_route method doesn't return anything when the method is success, otherwise returns a error object.

#### set_timer

The set_timer method sets a new timer into the local node. A trigger event occurs when the specified duration is over, and the timer is removed when the loop parameter is false. Otherwise, a next trigger occurs when the loop parameter is true.

##### Parameters

```
set_timer = "{" name duration [loop] "}"

name           = "name" ":" TOKEN
duration       = "duration" ":" INTEGER (msec)
loop           = "loop" ":" BOOL
```

##### Return values

The set_timer method doesn't return anything when the method is success, otherwise returns a error object.

#### set_alias

The set_alias method sets a new alias of a local method of the local node.

##### Parameters

```
set_alias = "{" name method [defaults]"}"

name     = "name" ":" TOKEN
method   = "method" ":" TOKEN
defaults = "defaults" ":" (json-rpc-params-default | json-rpc-default)*

json-rpc-params-default = "params".TOKEN ":" TOKEN
json-rpc-default        = ("dest" | "quorum" | "cond" | "type") ":" TOKEN
```

The `default-params` are passed into the original method. If the alias is posted with new parameters, the new parameters are added or overrided into the default parameters.

##### Return values

The set_alias method doesn't return anything when the method is success, otherwise returns a error object.

#### remove_alias

The remove_alias method remove a specified alias in the local node.

##### Parameters

```
remove_alias = "{" name "}"

name     = "name" ":" TOKEN
```

##### Return values

The remove_alias method doesn't return anything when the method is success, otherwise returns a error object.

#### post_job

The post_job method exec a specified code in the local node, and returns a result.

##### Parameters

```
post_job = "{" language code encoding "}"

language = "language" ":" supported-language
code     = "code" ":" TOKEN
encoding = "encoding" ":" ("none" | "base64")

supported-language = ("js" | "java" | "tcl" | "lua")
```

##### Return values

The post_job method returns a job result, otherwise returns a error object.

### Native Methods

Round adds the following default native methods. The methods are implemented using the native programming language, but developers can override the default methods using 'set_method'.

| Method Name | Description |
| --- | --- |
| add_node | Start a new node |
| remove_node | Stop a specified node |
| set_registry | Set a new registry into the local node |
| get_registry | Get a registry from the local node |
| remove_registry | Remove a specified registry from the local node |
| get_network_state | Get a cluster list which a specified node knows |
| get_cluster_state | Get a node list which a specified node is belong |
| get_node_state | Get a node information |
| get_node_config | Get the node configuration |
| get_node_stats | Get the node statistics |

#### add_node

The add_node start a new node from the specified node. If a source node is specified, the new node copies the source node configuration.

##### Parameters

```
add_node = "{" [source_node] "}"

source_node = "src" ":" [cluster.] node
cluster     = TOKEN
node        = TOKEN
```

##### Return values

The add_node method doesn't return anything when the method is success, otherwise returns a error object.

#### remove_node

The remove_node stop the specified node.

##### Parameters

The remove_node method has node parameter.

##### Return values

The remove_node method doesn't return anything when the method is success, otherwise returns a error object.

#### set_registry

The set_registry method sets a specified key and value into the local node registry.

##### Parameters

```
set_registry = "{" key value "}"

key   = "key" ":" TOKEN
value = "value" ":" TOKEN
```

##### Return values

The set_registry method doesn't return anything when the method is success, otherwise returns a error object.

#### get_registry

The get_registry method returns a registry by a specified key from the local node registry.

##### Parameters

```
get_registry = "{" key "}"

key = "key" ":" TOKEN
```

##### Return values

The get_registry method a following JSON string, otherwise returns a error object.

```
result = "{" key value timestamp logical_timestamp"}"

key               = "key"   ":" TOKEN
value             = "value" ":" TOKEN
timestamp         = "ts"    ":" NUMBER
logical_timestamp = "lts"   ":" NUMBER
```

#### remove_registry

The remove_registry method remove a specified key from the local node registry.

##### Parameters

```
remove_registry = "{" key "}"

key   = "key" ":" TOKEN
```

##### Return values

The remove_registry method doesn't return anything when the method is success, otherwise returns a error object.

#### get_network_state

The get_network_state method returns a cluster list which the local node knows.

##### Parameters

This method has no parameter.

##### Return values

The get_network_state method returns a following JSON string, otherwise returns a error object.

```
result = { network-state }

network-state = "clusters" ":" (cluster-state)*

cluster-state = "cluster" ":" name nodes

name  = "name"  ":" TOKEN
nodes = "nodes" ":" (node-state)*

node-state = "{" cluster hash ip port state "}"

cluster = "cluster" ":" TOKEN
hash    = "hash"    ":" TOKEN
addr    = "addr"    ":" IPADDR
port    = "port"    ":" NUMBER
state   = "state    ":" ("active" | "stop")
```

#### get_cluster_state

The get_cluster_state method returns all nodes which the local node knows in the same cluster.

##### Parameters

This method has no parameter.

##### Return values

The get_cluster_state method returns a following JSON string, otherwise returns a error object.

```
result = { cluster-state }

cluster-state = "cluster" ":" name nodes

name  = "name"  ":" TOKEN
nodes = "nodes" ":" (node-state)*

node-state = "{" cluster hash ip port state "}"

cluster = "cluster" ":" TOKEN
hash    = "hash"    ":" TOKEN
addr    = "addr"    ":" IPADDR
port    = "port"    ":" NUMBER
state   = "state    ":" ("active" | "stop")
```

#### get_node_state

The get_node_state method returns the local node status.

##### Parameters

This method has no parameter.

##### Return values

The get_node_state method returns a following JSON string, otherwise returns a error object.

```
result = "{" cluster hash ip port state "}"

cluster = "cluster" ":" TOKEN
hash    = "hash"    ":" TOKEN
addr    = "addr"    ":" IPADDR
port    = "port"    ":" NUMBER
state   = "state    ":" ("active" | "stop")
```

## Trigger

| Trigger Name | Perpose | Params | Outputs | Default |
| --- | --- | --- | --- | --- |
| pre_activate | - | - | - | - |
| post_activated | - | - | - | - |
| pre_deactivate | - | - | - | - |
| post_activated | - | - | - | - |
| method_added | - | - | - | - |
| method_removed | - | - | - | - |
| method_updated | - | - | - | - |
| message_received | - | - | - | - |
| message_executed | - | - | - | - |
| log_occurred | - | - | - | - |
| node_added | - | - | - | - |
| node_removed | - | - | - | - |
| node_suspected | - | - | - | - |

![round_logo](../img/round_logo.png)

# Tour of Round

The tour explains main functions of Round using a client utility command, `round`.

To use the utility, start a single node of Round at first:

```
roundd
```

Next, let's start the client utility command:

```
round shell
```

To show all commands of `round`, use `help` command:

```
round> help
```

## Finding Nodes

Immediately after the `round` command is started, the command don't know other nodes in the network.

To find other nodes in the network, use `search` command at first:

```
round> search
```

To show the found nodes in the network, use `list` command:

```
round> list
[round]                   # --> cluster name
  [0] 192.168.100.26:7476 # --> node ipaddr:port
```

The `list` command outputs only a current cluster. Round uses the cluster name, `round`, as default.　Otherwise use `use` command to select a other target cluster:

```
round> use <cluster name>
```

## Executing Jobs

The node is running as a RPC node, and the node can execute any jobs to use `post_job` method. Using the method, the developers can execute any jobs on the node.

In this section, post a simple job which returns a current date using JavaScript:

```
rounc > post_job(0, { "language":"js", "code":"var now = new Date();now.toString();" })
Sat May 02 2015 17:30:17 GMT+0900 (JST)
```

## Adding Methods

The node is running as a programmable RPC node. The node has some embedded default methods such as `post_job`, and the developers can add new methods using `set_method` method.

In this section, add a simple `echo` method which returns the given parameters as it is using JavaScript. To add the `echo` method, use `set_method`:

```
round> set_method(0, { "language":"js", "name":"echo", "code":"function echo(params) {return params;}" })
```

To confirm whether the `echo` method is added, call `echo` method:

```
round> echo(0, "hello")
"hello"
```

## Registry

The node has a local registry to store any key values in the node.

In this section, use the registry function. To set a key value into the registry, use `set_registry` method:

```
round> set_registry(0, {"key":"test", "value":"hello"})
```

To confirm whether the `set_registry` method is success, call `get_registry` method:

```
round> get_registry(0, {"key":"test"})
{"key":"test","lts":xxxxx,"ts":xxxxx,"value":"hello"}
```

## Routing

The node has a route function. Using the route function, the developer can connect some methods like Unix pipes.

In this section, add a simple route function which adds a current date prefix use route function.

```
round> set_method(0, { "language":"js", "name":"echo", "code":"function echo(params) {return params;}" })
round> set_method(0, { "language":"js", "name":"echo_log", "code":"function echo_log(params) {var now = new Date(); return now.toString() + ' : ' + params;}" })
round> set_route(0, {"name":"echo", "src":"echo", "dest":"echo_log"})
```

To confirm whether the route is added, call `echo` method:

```
round> echo(0, "hello")
"Thu Jun 11 2015 01:13:49 GMT+0900 (JST) : hello"
```

## Alias

The alias function supports to create an alias method of defined methods in the local node with default parameters.

In this section, add a simple `hello` alias using a'echo' method which returns the given parameters as it is using JavaScript. To add the `hello` alias, use `set_alias`:

```
round> set_method(0, { "language":"js", "name":"echo", "code":"function echo(params) {return params;}" })
round> set_alias(0, { "name":"hello", "method":"echo", "defaults":"hello" })
```

To confirm whether the `echo` method is added, call `echo` method:

```
round> hello(0)
"hello"
```

## Creating Triggers

The node has some embedded default triggers. In addition to the default triggers, the developers can add user original triggers using `set_timer`.

In this section, create a simple counter which is updated every second:

```
round> set_timer(0, { "name":"", "duration":1.0 })
```

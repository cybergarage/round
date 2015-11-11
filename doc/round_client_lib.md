![round_logo](../img/round_logo.png)

# Client Libraries

The client libraries handles add the following parameters into RPC requests automatically.

- id
- ts (Lamport Timestamp)

The libraries handles the RPC responses and updates local information of Client.

- Clusters
- Nodes in clusters
- Timestamp (Lamport Timestamp)

## JavaScript

Under Development :wink:

## C++

Under Development :wink:

## Java

Under Development :wink:

## Go

Under Development :wink:

## Lua

[JSON4Lua](http://json.luaforge.net)

# Native Interfaces

Round is implemented by C++, you can add static system methods by the native programming language.

## Adding Native Methods

### Sever and Method class

First, create a sub class of Round::Server() to add the native methods. Next, create a sub class of Round::Method() and add the method class using Round::Server::addMethod() in Round::Server::initialize().


```
#include <round/Round.h>

class MyMethod : public Round::Method {
  .....
  bool exec(const Node *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
    .....
  }
}

class MyServer : public Round::Server {
  .....
  void initialize() {
    addMethod(new MyMethod());
  }
}
```

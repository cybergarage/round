![round_logo](../img/round_logo.png)

English / [Japanese](round_overview_jp.md)

# Overview

## What is Round ?

Round is a new open source framework developed for distributed system developers and researchers to build distributed applications and frameworks more easily.

The name "Round" derives from "[Knights of the Round Table](http://en.wikipedia.org/wiki/Round_Table)", meaning that every node in a cluster has an equal role and the cluster has no mater node.

Round is a new basic framework for distributed systems, supports to develop various　distributed frameworks or applications such as the following:

- Consensus Services (Chubby, ZooKeeper, etcd, ...)
- Distributed Frameworks (Hadoop, Storm, Spark ...)
- Distributed File Systems (GFS, HDFS, ...)
- Distributed Database Systems (Dynamo, Cassandra, ...)
- Distributed Resource Managements (Mesos, YARN, ...)

## Design Overview

### Design Principles

Round is designed on the basis of the following principles.

#### Simplicity

Simplicity is the most valued principle. The core module of Round is very simple, and has only minimum functions are implemented.

Orthogonality is another important one as well as simplicity. Considering those principles, no redundancy functions are implemented to keep the core module simple.

Round enables to build distributed services and applications to define the small methods using any programming languages and connect between the methods like pipeline of Unix or Microservices instead of monolithic system.

#### Clarity

The technical specifications of the core functions are clearly defined and released free for users. Basically, the specifications are defined to extend some de facto standard specifications.

The initial version of core functions are implemented with C++, whereas the core module can be done with other programming languages such as Java and Go based on the public specifications.

### Target Scopes

Round's core functions are very small like [Microkernel](http://en.wikipedia.org/wiki/Microkernel), and the all other basic functions to build distributed frameworks or applications are supplied as core modules. Developers can build distributed frameworks or applications using the core functions and modules as the following.

![round_design_scope](img/round_design_scope.png)

Round supplies some useful core modules such as consensus protocols and failure detections for distributed systems as default. In addition, developers can add new original modules for distributed system such as consensus protocol using any programming languages such as JavaScript and Lua.

## Architecture Overview

### Programming Model

Round supports both [message passing model][msgp-model] and [shared memory model][shmem-model] as the parallel distributed programming model. In Round, the message passing model originates in [actor model][actor-model] and [CSP][csp-model] (Communicating Sequential Processes), and the programming model be affected by [Reactive][reactive] and [Aspect-oriented][aspect] programming paradigms.

Round's cluster is consist of several nodes. The each node is an actor of [Lamport model][lamport-model] which has a logical clock and a message queue to receive messages from clients or other nodes.

![Round Programming Model](img/round_programming_model.png)

### Open Standard Protocols

Round is consist of the following open standard network protocols such as [JSON-RPC][json-rpc] and [UPnP][upnp-spec].

![round_protocol](./img/round_protocol.png)

In addition, Round supports several major programming languages such as Java, JavaScript and Lua. Developers can build distributed frameworks and applications using their favorite programming languages.

##  Features

In Round, there are the following features to develop distributed frameworks and applications easily.

### Zeroconf

In typical cloud systems, users have to set some configuration to start distributed services. Round is designed based on Zeroconf not to set any configurations by users.

For example, a node is added into a cluster of Round automatically after the new node is started without configuration. Other nodes in the same network are received event messages when a node is added or removed.

![auto-configuration](img/round_overview_autoconfig.png)

Zeroconf is a tecnology to find services without user configuration. In Round, all new nodes are added into a cluster without special configuration and the nodes are available automatically.

### Decentralized

Basically, Round is a decentralized distributed system framework,
every nodes in a cluster has equal roll, the cluster has no master node.

![round_overview_zeroconf](img/round_overview_decentralized.png)

In addition, Round has a function which elects a leader node to build centric distributed frameworks and applications automatically.

### Autonomous

Each node run as an autonomous actor based on the specified behaviors by developers. The nodes communicates messages to other nodes in the same or other clusters based on the specified behaviors autonomously.

![round_overview_autonomous](img/round_overview_autonomous.png)

Round is a autonomous programming model like [Game of Life][life-game]. The node has the behavior codes itself. The node runs based on the behavior codes and handles any events autonomously.

### Dynamics

Each node is an autonomous and a programmable [RPC][rpc] node.
In Round, you can build distributed frameworks and applications to add behavior scripts and connect events into the scripts dynamically.

![auto-configuration](img/round_overview_programming.png)

Round supports some dynamic programming languages such ad JavaScript and Java, then you can develop distributed system applications using your favorite programming language.

[actor-model]: http://en.wikipedia.org/wiki/Actor_model
[csp]: http://en.wikipedia.org/wiki/Communicating_sequential_processes
[reactive]: http://dl.acm.org/citation.cfm?id=101990
[aspect]: https://en.wikipedia.org/wiki/Aspect-oriented_programming
[df-prog]: http://en.wikipedia.org/wiki/Dataflow_programming
[upnp-spec]: http://upnp.org/sdcps-and-certification/standards/
[json-rpc]: http://www.jsonrpc.org/specification
[java]: https://java.com/
[js-spec]: http://www.ecma-international.org/publications/standards/Ecma-262.htm
[life-game]: http://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
[rpc]: http://en.wikipedia.org/wiki/Remote_procedure_call
[lamport-model]: http://en.wikipedia.org/wiki/Lamport_timestamps
[parallel-model]: http://en.wikipedia.org/wiki/Parallel_programming_model
[msgp-model]: http://en.wikipedia.org/wiki/Message_passing
[shmem-model]: http://en.wikipedia.org/wiki/Shared_memory_(interprocess_communication)
[csp-model]: http://en.wikipedia.org/wiki/Communicating_sequential_processes
[paxos]: http://research.microsoft.com/en-us/um/people/lamport/pubs/paxos-simple.pdf

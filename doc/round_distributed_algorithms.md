![round_logo](../img/round_logo.png)

# Round Distributed Algorithms

Round consists of the following robust distributed algorithms.

## Network Topology

Round's node are connected to one another in a consistent hashing[\[1\]][link-ch-1997] ring. The each node has a hash code, the hash codes are used for ordering of the consistent hashing ring.

## Programming Model

Round is based on message passing model[\[2\]][link-ppmodel] to cooperate with other nodes.

CSP (Communicating Sequential Processes)[\[3\]][link-csp]

## Lamport model

### Logical Clock

Round doesn't handle vector clocks in the RPC call.

## Leader Election

Round is ....., but the cluster has a leader node. The leader node can know that they is a leader in the cluster themself.



- \[1\] [Karger, D.; Lehman, E.; Leighton, T.; Panigrahy, R.; Levine, M.; Lewin, D, Consistent Hashing and Random Trees: Distributed Caching Protocols for Relieving Hot Spots on the World Wide Web, 1997][link-ch-1997]
- \[2\] [Parallel programming model][link-ppmodel]
- \[3\] [Communicating sequential processes][link-csp]

[link-ch-1997]: http://dl.acm.org/citation.cfm?id=258660
[link-ppmodel]: http://en.wikipedia.org/wiki/Parallel_programming_model
[link-csp]: http://en.wikipedia.org/wiki/Communicating_sequential_processes

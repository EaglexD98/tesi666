# Graph Report - .  (2026-06-11)

## Corpus Check
- Corpus is ~1,305 words - fits in a single context window. You may not need a graph.

## Summary
- 39 nodes · 37 edges · 9 communities (6 shown, 3 thin omitted)
- Extraction: 86% EXTRACTED · 14% INFERRED · 0% AMBIGUOUS · INFERRED: 5 edges (avg confidence: 0.82)
- Token cost: 4,760 input · 1,373 output

## Community Hubs (Navigation)
- [[_COMMUNITY_HostAutoConfigurator Lifecycle|HostAutoConfigurator Lifecycle]]
- [[_COMMUNITY_Network Layer Setup (IPv4)|Network Layer Setup (IPv4)]]
- [[_COMMUNITY_Changed File Inventories|Changed File Inventories]]
- [[_COMMUNITY_Modified Framework Overview|Modified Framework Overview]]
- [[_COMMUNITY_Configurator Base Classes|Configurator Base Classes]]
- [[_COMMUNITY_HostAutoConfigurator Header|HostAutoConfigurator Header]]
- [[_COMMUNITY_MyHostAutoConfigurator Header|MyHostAutoConfigurator Header]]
- [[_COMMUNITY_Graphify Instructions|Graphify Instructions]]

## God Nodes (most connected - your core abstractions)
1. `Modified Framework Files Overview` - 5 edges
2. `HostAutoConfigurator::setupNetworkLayer` - 4 edges
3. `handleStartOperation()` - 3 edges
4. `LifecycleOperation` - 3 edges
5. `Changed Framework Files List` - 3 edges
6. `handleMessageWhenUp()` - 2 edges
7. `setupNetworkLayer()` - 2 edges
8. `handleStopOperation()` - 2 edges
9. `handleCrashOperation()` - 2 edges
10. `inet()` - 2 edges

## Surprising Connections (you probably didn't know these)
- `Modified Framework Files Overview` --shares_data_with--> `Changed Framework Files List`  [INFERRED]
  /home/eagle/tesi666/graphify_scope/MODIFIED_FRAMEWORK_FILES.md → /home/eagle/tesi666/graphify_scope/changed_framework_files.txt
- `Changed Framework Files List` --shares_data_with--> `Changed INET Project Files`  [INFERRED]
  /home/eagle/tesi666/graphify_scope/changed_framework_files.txt → /home/eagle/tesi666/graphify_scope/changed_inet_project.txt
- `Changed Framework Files List` --shares_data_with--> `Changed Simu5G Project Files`  [INFERRED]
  /home/eagle/tesi666/graphify_scope/changed_framework_files.txt → /home/eagle/tesi666/graphify_scope/changed_simu5g_project.txt
- `Changed INET Project Files` --shares_data_with--> `Changed INET Relative Files`  [EXTRACTED]
  /home/eagle/tesi666/graphify_scope/changed_inet_project.txt → /home/eagle/tesi666/graphify_scope/changed_inet_rel.txt
- `Changed Simu5G Project Files` --shares_data_with--> `Changed Simu5G Relative Files`  [EXTRACTED]
  /home/eagle/tesi666/graphify_scope/changed_simu5g_project.txt → /home/eagle/tesi666/graphify_scope/changed_simu5g_rel.txt

## Import Cycles
- None detected.

## Communities (9 total, 3 thin omitted)

### Community 0 - "HostAutoConfigurator Lifecycle"
Cohesion: 0.27
Nodes (7): cMessage, handleCrashOperation(), handleMessageWhenUp(), handleStartOperation(), handleStopOperation(), setupNetworkLayer(), LifecycleOperation

### Community 1 - "Network Layer Setup (IPv4)"
Cohesion: 0.40
Nodes (6): HostAutoConfigurator::setupNetworkLayer, IInterfaceTable, IIpv4RoutingTable, Ipv4InterfaceData, Ipv4Route, MyHostAutoConfigurator::setupNetworkLayer

### Community 2 - "Changed File Inventories"
Cohesion: 0.40
Nodes (5): Changed Framework Files List, Changed INET Project Files, Changed INET Relative Files, Changed Simu5G Project Files, Changed Simu5G Relative Files

### Community 3 - "Modified Framework Overview"
Cohesion: 0.50
Nodes (5): Modified Framework Files Overview, Highway NED Simulation, HostAutoConfigurator, MyHostAutoConfigurator, NrCarCustom NED Node

### Community 4 - "Configurator Base Classes"
Cohesion: 0.50
Nodes (3): HostAutoConfigurator, OperationalBase, MyHostAutoConfigurator

## Knowledge Gaps
- **11 isolated node(s):** `cMessage`, `namespace`, `namespace`, `Graphify Project Instructions`, `NrCarCustom NED Node` (+6 more)
  These have ≤1 connection - possible missing edges or undocumented components.
- **3 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Modified Framework Files Overview` connect `Modified Framework Overview` to `Changed File Inventories`?**
  _High betweenness centrality (0.036) - this node is a cross-community bridge._
- **Why does `Changed Framework Files List` connect `Changed File Inventories` to `Modified Framework Overview`?**
  _High betweenness centrality (0.034) - this node is a cross-community bridge._
- **Are the 3 inferred relationships involving `Changed Framework Files List` (e.g. with `Changed INET Project Files` and `Changed Simu5G Project Files`) actually correct?**
  _`Changed Framework Files List` has 3 INFERRED edges - model-reasoned connections that need verification._
- **What connects `cMessage`, `namespace`, `namespace` to the rest of the system?**
  _11 weakly-connected nodes found - possible documentation gaps or missing edges._
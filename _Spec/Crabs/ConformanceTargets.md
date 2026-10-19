# Conformance Targets

The existing capability names distinguish a **Script Automaton** from a
**Crabs / Group Automata** target. They describe what a target supports; the
names alone do not certify an implementation or prove a mathematical theorem.

## Script Automaton

A target supports its declared SCRIPT operation, data-format, and transport
subset without requiring the full Crabs machine. It must state that subset
and test its argument decoding, bounds, errors, and recovery. Lack of Crabs
support is not by itself a certification procedure.

## Crabs / Group Automata

A Crabs target supports the unified ASCII List stack and expression machinery
specified in [ASCII List Chinese Room](ASCIIListChineseRoom.md). Its verification
must exercise the actual machine, not only an isolated BIn/BOut pair:

1. Construct the machine over a fixed Wall and run with dynamic memory disabled.
2. Store and access heterogeneous type-value tuples through the List stack.
3. Distinguish C0 expression controls from typed argument data.
4. Interpret nested map values and call operations referencing stored data.
5. Install and address a Door, pass messages through its actual Slots, and
   verify the owning Room receives and processes them.
6. Verify scope closure and the specified persistent-data effects of cancel,
   clear, and reset.
7. Exercise capacity failures, malformed input, invalid references, and
   bounded recovery without corrupting existing storage.

Optional dynamic growth, Portal backends, concurrency, IPC, and authentication
need separate declared capabilities and appropriate tests. Their presence in
a header or constructor is not proof of working behavior.

## Evidence and current limitations

[_Seams/15.CrabsOp.hxx](../../_Seams/15.CrabsOp.hxx) initializes and scans the
legacy machine; its POD ring regressions cover a narrower boundary.
[_Seams/16.Room.hxx](../../_Seams/16.Room.hxx) constructs Room objects but still
passes messages through a separate raw ring. Neither establishes the full
unified List/Door integration or concurrent IPC conformance.

Documentation consistency checks are not runtime tests. A conformance report
must identify the implementation, build/configuration, platform, test paths,
observed results, and unsupported capabilities. Reset behavior must be tested
as specified, not called an identity or an inverse as a substitute for evidence.
No formal certification process is defined by this page.

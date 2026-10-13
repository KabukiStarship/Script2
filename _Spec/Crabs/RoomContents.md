# Room Contents

A Chinese Room uses the pen-and-paper office metaphor for the Crabs abstract
machine. Its heterogeneous data is held on the ASCII List stack; its operations
interpret and act on that data. The List is not another container beside the
machine. See [ASCII List Chinese Room](ASCIIListChineseRoom.md).

## Walls and the Floor

Walls are contiguous blocks of word-aligned backing memory. They provide space
for the List stack, interpreter metadata, Doors and their Slots, and other
in-memory values. Arrays, Stacks, Lists, Maps, Tables, Books, Dictionaries,
strings, and in-memory Files are typed contents, not automatically additional
Room modules. Filing cabinets and bookshelves are storage metaphors.

A Room starts with one Wall. In the minimum configuration that Wall is fixed,
caller-supplied storage, and the Room requires no dynamic memory. The Floor is
that initial Wall, not a separate module or machine-state object. More memory
may be provided by optional growth or additional Walls; every Wall remains
contiguous. Ownership and relocation are covered in [Autojects](Autojects.md).

## Doors

A Door is a MAP-type interface installed in a Wall. It exposes operations and
one or more Slots leading to another Room or Agent. It is addressable by the
Crabs machine, so an operation may refer to a Door through typed data on the
List stack. The exact Door descriptor and reference layout remain to be
reconciled with the Data specification.

BIn and BOut carry bytes through the Door's Slots. They are not automatically
independent operands on the List stack, nor does their use make the Door
identical to a ring header. Installing a Door must bind its operation interface,
storage, Slot bounds, and lifetime; allocating a ring alone is not sufficient.

A **Front Door** is a known entrance. A **Backdoor** is an entrance not known
to the outside client. Those names do not confer authorization or establish a
security policy. Access control is application-defined; see
[Authentication](Authentication.md).

## Slots, Mirrors, and Windows

A Slot is the abstract ring-buffer/socket used for message transfer. BIn is
its input side and BOut its output side. Use bounds and descriptors for the
chosen format, rather than assuming two different C++ header types may alias
one object. [Protocol Slots](../Protocol/Slots.md) describes the older layouts;
[ASCII List Chinese Room](ASCIIListChineseRoom.md) records the reconciliation
needed before they can serve as an implementation ABI.

Mirrors describe one-way, in-memory expression or IO arrangements. Combining
opposite directions provides a duplex Window. Word-aligned or hashless local
transfer is an explicit endpoint contract, not a blanket guarantee that IPC
is trusted, lossless, or thread-safe.

## Root controls and Portals

DC1 through DC4 are root-scope control hooks. Their operation bindings and
keyboard adapters must agree with the expression protocol; a physical keyboard
is not required by the abstract machine. ESC, cancel, and reset operate on
expression/machine state, not on a separate Floor object.

Portals connect Room endpoints through Doors and Slots. The core describes
in-memory communication; OS and hardware bindings live outside the abstract
machine. See [Portals](Portals.md).

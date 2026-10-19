# Crabs Specification

The **Chinese Room Abstract Stack** (**Crabs**) Machine interprets SCRIPT
expressions over ASCII Data Types. Its heterogeneous data stack is the ASCII
List. The List and machine are one design, not two containers with separate
scanners. Operations can refer to tuples already on the List stack, including
nested map values.

The Chinese Room is the office metaphor for this abstract system: Walls supply
memory, Doors expose operations and communication, and Slots carry messages.
The initial fixed Wall is also called the Floor. There is no separate Floor
module or machine-state object.

## Requirements

1. Use one heterogeneous ASCII List stack for typed data and expression access.
2. Reuse the Crabs scanner and operation machinery for nested map types rather
   than introducing a second data-language implementation.
3. Support 12-bit inline unsigned-character and 12-bit inline signed-integer
   values in the 16-bit ASCII Data Type word. Their exact tags must be reconciled
   with the Data specification before an encoding is assigned.
4. Interpret ASCII C0 expression controls in context; a low-valued datum is not
   automatically an instruction.
5. Support a Room with one fixed, word-aligned, contiguous Wall and no dynamic
   memory. Optional growth uses the memory-management boundary, not a new Floor.
6. Make Doors accessible to machine operations. BIn and BOut are transport
   machinery, not automatically independent operands on the List stack.
7. Keep the machine and in-memory communication abstract. OS and device
   backends belong in CrabsTK or another host integration.
8. Preserve Unicode support, bounded storage, explicit errors, and recovery.
   Physical keyboard, GUI, and serial interfaces adapt to the same abstract
   operation contract; they are not mandatory hardware in the Room.

## Documents

- [ASCII List Chinese Room](ASCIIListChineseRoom.md): architecture, invariants,
  implementation status, and unresolved encoding and lifetime decisions.
- [Room Contents](RoomContents.md): Room, Wall, Floor, Door, and Slot roles.
- [Autojects](Autojects.md): contiguous storage and RAMFactory ownership.
- [Messages](Messages.md): expressions, typed arguments, and persistent data.
- [Expression Mappings](ExpressionMappings.md): nested maps and data references.
- [Portals](Portals.md): abstract Room-to-Room connections and backend boundaries.
- [Authentication](Authentication.md): application authentication boundary.
- [Abnormal Behaviors](AbnormalBehaviors.md): validation and recovery.
- [Conformance Targets](ConformanceTargets.md): capabilities and verification.

These pages specify the clarified design, not a claim that the current C++
implementation has completed the List/machine integration. The implementation
status and remaining cross-directory conflicts are recorded in
[ASCII List Chinese Room](ASCIIListChineseRoom.md).

# Expression Mappings

Crabs expressions operate on the heterogeneous ASCII List stack. They can
construct typed values, enter nested map scopes, resolve keys or indexes, and
call operations using data already stored on that List stack. These are not
separate List and machine languages. See
[ASCII List Chinese Room](ASCIIListChineseRoom.md).

## Stored data and references

A List has type-value tuples and offsets, not intrinsic string keys. A name
such as `stuff` is a binding used by an expression to refer to a List entry.
A Dictionary inside that entry may have its own keys.

For example, the following is a conceptual data structure, not executable
Crabs syntax or a byte layout:

```text
List entry: dictionary value, bound to the name "stuff"
  key "things": nested dictionary value
    key "item1": IUB value 1
    key "item2": ISB value -1

List entry: installed Door value or typed reference
```

Resolving `stuff.things.item1` finds the stored dictionary, enters `things`,
and selects the typed `item1` value. An operation can use that value without
retransmitting the entire dictionary. Its parameter contract determines
whether it receives a copy or an access/reference to the stored datum.

## Nested map operations

- Read the enclosing type and context before interpreting a nested value.
- Reuse the Crabs scanner and scope machinery for nested Maps, Lists, Books,
  Dictionaries, and Tables; a POD round-trip alone does not establish support.
- Validate each key or index, nested extent, descriptor, and reference lifetime.
- Distinguish entering/leaving a map scope from pushing/popping persistent data.
- Check both entry capacity and byte capacity. A rejected insertion reports an
  error and leaves the existing structure valid; it is not a successful silent
  no-op.
- Specify which mutations invalidate bindings and references, including removal
  and storage relocation. Do not promise address stability without a contract.

## Grammar and implementation status

The former example mixed dictionary width names, capacities, delimiters,
function headers, and unresolved syntax. It was not an implementation-verified
grammar and must not allocate operation indexes or type codes.

[Protocol Expressions](../Protocol/Expressions.md) describes the legacy
operation/scoping language, and [Dictionary](../Data/MapTypes/Dictionary.md)
and [List](../Data/MapTypes/List.md) describe the data structures. Concrete
creation, binding, reference, removal, and nested-call syntax must be reconciled
with the unified scanner and demonstrated by integration tests before being
presented as runnable Crabs code.

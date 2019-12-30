# SCRIPT Specification

This document is a Release for Comment (RFC) not an ISO Specification, there are plenty of errors and things we can do better so your comments and criticism are appreciated. If you would like to contribute to this RFC, contributors are welcome on GitHub at <https://github.com/kabuki-starship/script2>.

## Content Table

1. [Overview](./overview/)
    1. [Requirements](./overview/requirements)
    1. [Terminology](./overview/terminology)
    1. [Chinese Room Objects](./overview/chinese_room_objects)
2. [ASCII Data Specification](./data/)
   1. [Data Types](./data/data_types)
   1. [Numbers](./data/numbers)
   1. [Timestamps](./data/timestamps)
   1. [Strings](./data/strings)
   1. [B-Sequences](./data/b-sequences)
   1. [Homo-tuples](./data/homo-tuples)
   1. [Map Types](./data/map_types/)
      1. [Socket](./data/map_types/socket)
      1. [Array](./data/map_types/array)
      1. [Stack](./data/map_types/stack)
      1. [Matrix](./data/map_types/matrix)
	  1. [Loom](./data/map_types/loom)
      1. [Map](./data/map_types/map)
      1. [List](./data/map_types/list)
      1. [Table](./data/map_types/table)
      1. [Book](./data/map_types/book)
      1. [Dictionary](./data/map_types/dictionary)
3. [Universal Addressing Specification](./addressing/)
    1. [Most Longitudinal bit](./addressing/most_longitudinal_bit)
    1. [Universal Address Format](./addressing/universal_address_format)
4. [SCRIPT Protocol Specification](./protocol/)
    1. [Group Automata](./protocol/group_automata)
    1. [Time](./protocol/time)
    1. [Slots](./protocol/slots)
    1. [Expressions](./protocol/expressions)
    1. [Operations](./protocol/operations)
    1. [Generic Handshake](./protocol/generic-handshake)
    1. [Encryption](./protocol/encryption)
    1. [Terminals](./protocol/terminals)
    1. [Quality of Service](./protocol/quality_of_service)
    1. [Congestion Control](./protocol/congestion_control)
    1. [Abnormal Behavior](./protocol/abnormal_behavior)
5. [Crabs Specification](./crabs/)
    1. [Authentication](./crabs/authentication)
    1. [Portals](./crabs/portals)
    1. [Room Contents](./crabs/room_contents)
    1. [Conformance Targets](./crabs/conformance_targets)
    1. [Autojects](./crabs/autojects)
    1. [Messages](./crabs/messages)
    1. [Expression Mappings](./crabs/expression_mappings)

## License

Copyright 2015-9 © [Kabuki Starship™](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.

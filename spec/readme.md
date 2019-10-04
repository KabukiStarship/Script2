# SCRIPT Specification

This document is a Release for Comment (RFC) not an ISO Specification, there are plenty of errors and things we can do better so your comments and criticism are appreciated. If you would like to contribute to this RFC, contributors are welcome on GitHub at <https://github.com/kabuki-starship/Script2™>.

## Content Table

1. [License](#license)
2. [Overview](./overview/readme.md)
    1. [Requirements](./overview/requirements.md)
    1. [Terminology](./overview/terminology.md)
    1. [System Classes](./overview/system_classes.md)
3. [ASCII Data Specification](./data/readme.md)
    1. [Data Types](./data/data_types.md)
    1. [Numbers](./data/numbers.md)
    1. [Timestamps](./data/timestamps.md)
	1. [String](./data/strings.md)
    1. [B-Sequences](./data/b-sequences.md)
    1. [Homo-tuple](./data/vector_types/homo-tuple.md)
    1. [Map Types](./data/map_types/readme.md)
      1. [Vector Types](./data/vector_types/readme.md)
       1. [Array](./data/vector_types/array.md)
       1. [Stack](./data/vector_types/stack.md)
       1. [Map](./data/map_types/map.md)
       1. [List](./data/map_types/list.md)
       1. [Table](./data/map_types/table.md)
       1. [Book](./data/map_types/book.md)
       1. [Dictionary](./data/map_types/dictionary.md)
    1. [Matrix](./data/vector_types/matrix.md)
4. [Universal Addressing Specification](./addressing/readme.md)
    1. [Longitude and Latitude](./addressing/longitude_and_latitude.md)
    1. [Most Longitudinal bit](./addressing/most_longitudinal_bit.md)
    1. [Universal Address Format](./addressing/universal_address_format.md)
5. [SCRIPT Protocol Specification](./protocol/readme.md)
    1. [Group Automata Theorem](./protocol/group_automata_theorem.md)
    1. [Time](./protocol/time.md)
    1. [Slots](./protocol/slots.md)
    1. [Expressions](./protocol/expressions.md)
    1. [Operations](./protocol/operations.md)
    1. [Generic Handshake](./protocol/generic-handshake.md)
    1. [Chinese Room Objects](./protocol/chinese_room_objects.md)
    1. [Profiles](./protocol/profiles.md)
    1. [Encryption](./protocol/encryption.md)
    1. [Terminals](./protocol/terminals.md)
    1. [Quality of Service](./protocol/quality_of_service.md)
    1. [Congestion Control](./protocol/congestion_control.md)
    1. [Abnormal Behavior](./protocol/abnormal_behavior.md)
6. [Crabs Specification](./crabs/readme.md)
    1. [Authentication](./crabs/authentication.md)
    1. [Conformance Targets](./crabs/conformance-targets.md)
    1. [Crabs Interpreters and Compilers](./crabs/interpreters_and_compilers.md)
    1. [Room Contents](./crabs/room_contents.md)

## License

Copyright 2014-9 © [Kabuki Starship™](https://kabukistarship.com); all rights reserved.

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.

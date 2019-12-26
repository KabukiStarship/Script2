# SCRIPT Specification

This document is a Release for Comment (RFC) not an ISO Specification, there are plenty of errors and things we can do better so your comments and criticism are appreciated. If you would like to contribute to this RFC, contributors are welcome on GitHub at <https://github.com/kabuki-starship/script2>.

## Content Table

1. [License](#license)
2. [Overview](./overview/)
    1. [Requirements](./overview/requirements)
    1. [Terminology](./overview/terminology)
    1. [System Classes](./overview/system_classes)
3. [ASCII Data Specification](./data/)
    1. [Data Types](./data/data_types)
    1. [Numbers](./data/numbers)
    1. [Timestamps](./data/timestamps)
	1. [String](./data/strings)
    1. [B-Sequences](./data/b-sequences)
    1. [Homo-tuple](./data/vector_types/homo-tuple)
    1. [Map Types](./data/map_types/)
      1. [Vector Types](./data/vector_types/)
       1. [Array](./data/vector_types/array)
       1. [Stack](./data/vector_types/stack)
       1. [Map](./data/map_types/map)
       1. [List](./data/map_types/list)
       1. [Table](./data/map_types/table)
       1. [Book](./data/map_types/book)
       1. [Dictionary](./data/map_types/dictionary)
    1. [Matrix](./data/vector_types/matrix)
4. [Universal Addressing Specification](./addressing/)
    1. [Longitude and Latitude](./addressing/longitude_and_latitude)
    1. [Most Longitudinal bit](./addressing/most_longitudinal_bit)
    1. [Universal Address Format](./addressing/universal_address_format)
5. [SCRIPT Protocol Specification](./protocol/)
    1. [Group Automata Theorem](./protocol/group_automata_theorem)
    1. [Time](./protocol/time)
    1. [Slots](./protocol/slots)
    1. [Expressions](./protocol/expressions)
    1. [Operations](./protocol/operations)
    1. [Generic Handshake](./protocol/generic-handshake)
    1. [Chinese Room Objects](./protocol/chinese_room_objects)
    1. [Profiles](./protocol/profiles)
    1. [Encryption](./protocol/encryption)
    1. [Terminals](./protocol/terminals)
    1. [Quality of Service](./protocol/quality_of_service)
    1. [Congestion Control](./protocol/congestion_control)
    1. [Abnormal Behavior](./protocol/abnormal_behavior)
6. [Crabs Specification](./crabs/)
    1. [Authentication](./crabs/authentication)
    1. [Conformance Targets](./crabs/conformance-targets)
    1. [Crabs Interpreters and Compilers](./crabs/interpreters_and_compilers)
    1. [Room Contents](./crabs/room_contents)

## License

Copyright 2015-9 © [Kabuki Starship™](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.

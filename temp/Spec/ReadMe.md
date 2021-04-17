# SCRIPT Specification

This document is a Release for Comment (RFC) not an ISO Specification, there are plenty of errors and things we can do better so your comments and criticism are appreciated. If you would like to contribute to this RFC, contributors are welcome on GitHub at <https://github.com/KabukiStarship/script2>.

## Content Table

1. [Overview](./Overview/)
    1. [Requirements](./Overview/Requirements)
    1. [Terminology](./Overview/Terminology)
    1. [Chinese Room Objects](./Overview/ChineseRoomObjects)
2. [ASCII Data Specification](./Data/)
   1. [Data Types](./Data/DataTypes)
   1. [Numbers](./Data/Numbers)
   1. [Timestamps](./Data/Timestamps)
   1. [Strings](./Data/Strings)
   1. [B-Sequences](./Data/BSequences)
   1. [Homo-tuples](./Data/HomoTuples)
   1. [Map Types](./Data/MapTypes/)
      1. [Socket](./Data/MapTypes/Socket)
      1. [Array](./Data/MapTypes/Array)
      1. [Stack](./Data/MapTypes/Stack)
      1. [Matrix](./Data/MapTypes/Matrix)
      1. [Loom](./Data/MapTypes/Loom)
      1. [Map](./Data/MapTypes/Map)
      1. [List](./Data/MapTypes/List)
      1. [Table](./Data/MapTypes/Table)
      1. [Book](./Data/MapTypes/Book)
      1. [Dictionary](./Data/MapTypes/Dictionary)
3. [Universal Addressing Specification](./Addressing/)
    1. [Most Longitudinal bit](./Addressing/MostLongitudinalBit)
    1. [Universal Address Format](./Addressing/UniversalAddressFormat)
4. [SCRIPT Protocol Specification](./Protocol/)
    1. [Group Automata](./Protocol/GroupAutomata)
    1. [Time](./Protocol/Time)
    1. [Slots](./Protocol/Slots)
    1. [Expressions](./Protocol/Expressions)
    1. [Operations](./Protocol/Operations)
    1. [Generic Handshake](./Protocol/Handshake)
    1. [Encryption](./Protocol/Encryption)
    1. [Terminals](./Protocol/Terminals)
    1. [Quality of Service](./Protocol/QualityOfService)
    1. [Congestion Control](./Protocol/CongestionControl)
    1. [Abnormal Behavior](./Protocol/AbnormalBehavior)
5. [Crabs Specification](./Crabs/)
    1. [Authentication](./Crabs/Authentication)
    1. [Portals](./Crabs/Portals)
    1. [Room Contents](./Crabs/RoomContents)
    1. [Conformance Targets](./Crabs/ConformanceTargets)
    1. [Autojects](./Crabs/Autojects)
    1. [Messages](./Crabs/Messages)
    1. [Expression Mappings](./Crabs/ExpressionMappings)

## License

Copyright 2015-21 © [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.

# SCRIPT Specification

This document is a Release for Comment (RFC) not an ISO Specification, there are plenty of errors and things we can do better so your comments and criticism are appreciated. If you would like to contribute to this RFC, contributors are welcome on GitHub at <https://github.com/KabukiStarship/script2>.

## Content Table

1. [Overview](Overview/)
    1. [Requirements](Overview/Requirements.md)
    1. [Terminology](Overview/Terminology.md)
    1. [Chinese Room Objects](Overview/ChineseRoomObjects.md)
2. [ASCII Data Specification](Data/)
   1. [Data Types](Data/DataTypes.md)
   1. [Numbers](Data/Numbers.md)
   1. [Timestamps](Data/Timestamps.md)
   1. [Strings](Data/Strings.md)
   1. [B-Sequences](Data/BSequences.md)
   1. [Homo-tuples](Data/HomoTuples.md)
   1. [Map Types](Data/MapTypes/)
      1. [Socket](Data/MapTypes/Socket.md)
      1. [Array](Data/MapTypes/Array.md)
      1. [Stack](Data/MapTypes/Stack.md)
      1. [Matrix](Data/MapTypes/Matrix.md)
      1. [Loom](Data/MapTypes/Loom.md)
      1. [Map](Data/MapTypes/Map.md)
      1. [List](Data/MapTypes/List.md)
      1. [Table](Data/MapTypes/Table.md)
      1. [Book](Data/MapTypes/Book.md)
      1. [Dictionary](Data/MapTypes/Dictionary.md)
3. [Universal Addressing Specification](Addressing/)
    1. [Most Longitudinal bit](Addressing/MostLongitudinalBit.md)
    1. [Universal Address Format](Addressing/UniversalAddressFormat.md)
4. [SCRIPT Protocol Specification](Protocol/)
    1. [Group Automata](Protocol/GroupAutomata.md)
    1. [Time](Protocol/Time.md)
    1. [Slots](Protocol/Slots.md)
    1. [Expressions](Protocol/Expressions.md)
    1. [Operations](Protocol/Operations.md)
    1. [Generic Handshake](Protocol/Handshake.md)
    1. [Encryption](Protocol/Encryption.md)
    1. [Terminals](Protocol/Terminals.md)
    1. [Quality of Service](Protocol/QualityOfService.md)
    1. [Congestion Control](Protocol/CongestionControl.md)
    1. [Abnormal Behavior](Protocol/AbnormalBehavior.md)
5. [Crabs Specification](Crabs/)
    1. [Authentication](Crabs/Authentication.md)
    1. [Portals](Crabs/Portals.md)
    1. [Room Contents](Crabs/RoomContents.md)
    1. [Conformance Targets](Crabs/ConformanceTargets.md)
    1. [Autojects](Crabs/Autojects.md)
    1. [Messages](Crabs/Messages.md)
    1. [Expression Mappings](Crabs/ExpressionMappings.md)

## License

Copyright 2015-21 © [Kabuki Starship](https://kabukistarship.com).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.

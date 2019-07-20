# [SCRIPT Specification RFC](../readme.md)

## License

Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>; All right reserved (R).

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.

## [SCRIPT Protocol](readme.md)

### Group Automata Theorem

Script, and all formal intelligence, can be recursively defined as follows:

* Let an **automata** be composed of concurrent **automatons**.
* Let a **Chinese Room** be an *Abstract Stack Machine (ASM)* able to reset to the **initial state** and run **automata** with **Script Operations** indexed by a single *Unicode character*.
* Let **A** be a set of states in a *state machine* that composes a **Chinese Room**.
* Let **B** be a set of *abstract parameters* in the form of a *UI1 stream* of **ASCII Data Types**.
* Let * be an *abstract binary operation* on sets **A** and **B**.
* Let **on** be a set of states where a **Chinese Room** is accepting **words**.
* While in the **on** state, **A** = **A** * **B**.
* Syntax changes semantics, thus **A** has no *commutative property*.
* **A** has an *inverse*, **A^(-1)**, in the form of a **Reset Operation**, thus (**A** * **B**)*(**A^(-1)**) = **A**.
* All *ASMs* have *total function*.
* **Conclusion**: **A** has *totality*, *associative*, *identity*, *inverse* *properties* but no *commutative* *property*, thus **A** is **group** in structure proving that the **Chinese Room** is a **Group Automata**, meaning **Many robots acting as one**:
  * *Group Automata*
    * **组自动机**
    * *Zǔ zìdòng jī*
  * *Many robots acting as one*
    * *许多机器人作为一个*
    * *Xǔduō jīqìrén zuòwéi yīgè*

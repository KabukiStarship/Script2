# [SCRIPT Specification](../)

## [Crabs Specification](./)

### Group Automata Monoid Theory and Chinese Room Implementation

#### 1. Mathematical Foundations: Monoids in Formal Mathematics

**Theorem 1 (Monoid Axioms for Group Automata)**. Let **A** be a set of states in a Chinese Room Abstract Stack (Crabs) Machine. Let **B** be a set of abstract parameters in the form of an IUA stream of ASCII Data Types. Let \* be an abstract binary operation on sets **A** and **B**. Then (**A**, *, **e**) forms a monoid if and only if:

1. **Closure**: For all **a** ∈ **A** and **b** ∈ **B**, the result **a** \* **b** ∈ **A**
2. **Associativity**: For all **a** ∈ **A**, **b**, **c** ∈ **B**, (**a** \* **b**) \* **c** = **a** \* (**b** \* **c**)
3. **Identity Element**: There exists **e** ∈ **A** such that for all **a** ∈ **A**, **e** \* **a** = **a** \* **e** = **a**

*Proof Sketch*. The Chinese Room's Abstract Stack Machine (ASM) satisfies these axioms through its stack-based operation model. The identity element corresponds to the **Reset Operation** which returns the machine to its initial state without modifying subsequent operations. Associativity is guaranteed by the stack discipline where operations are applied in strict LIFO order.

**Definition 1 (Free Non-Abelian Monoid F_n)**. Let **Σ** be a finite alphabet of Unicode character indexes (Script Operations). The free non-abelian monoid **F_n** consists of all finite strings over **Σ**, with concatenation as the binary operation and the empty string ε as the identity element.

*Key Property*: In **F_n**, order matters. For generators **a**, **b** ∈ **Σ**, **ab** ≠ **ba** in general. This matches Script's requirement that "Syntax changes semantics" (Group Automata Theorem, Section 16).

**Definition 2 (Free Abelian Monoid A_n)**. Let **Σ** be a finite alphabet. The free abelian monoid **A_n** consists of all formal sums ∑_{s∈Σ} n_s·s where n_s ∈ **ℕ**, with pointwise addition as the binary operation and the zero function as the identity element.

*Key Property*: In **A_n**, generators commute: **ab** = **ba**. This corresponds to a compression strategy where macro definitions can be reordered without changing semantics.

##### 1.1 Compression Theorems (from "Compression is all you need")

**Theorem 2 (Place Notation gives Exponential Expansion)**. For **A_1** = **ℕ** and any integer **b** ≥ 2, the macro set **M** = {**b^j·a** : **j** ≥ 1} has logarithmic density and satisfies:

**b^(s/(b-1)-1)** ≤ **f_{G'}**(s) ≤ **b**·**b^(s/(b-1))**

for all integers **s** ≥ 1. In particular, **f_{G'}**(s) = **Θ**(**b^(s/(b-1))**).

*Interpretation for Crabs*: Using place notation-style macros (e.g., powers of 256 for byte packing), each additional stack slot (**s**) yields exponential expansion in expressivity. This justifies the Crabs machine's ability to achieve Googol-level complexity (10^104 primitive terms) through hierarchical nesting.

**Theorem 3 (Polynomial Density gives Infinite Expansion)**. For any integer **k** ≥ 2, there exists a macro set **M** ⊆ **A_n** such that:

|**M** ∩ **B_G**(r)| ≤ **n**·**r^(1/k)** for all **r** ≥ 1

and

**f_{G'}**(s) = ∞ for all **s** ≥ **n**·**g**(k)

where **g**(k) is the Waring constant (smallest integer such that every nonnegative integer is a sum of at most **g**(k) k-th powers).

*Example*: For **k** = 2, Lagrange's four-square theorem gives **g**(2) = 4. A macro set of squares achieves infinite expansion with just 4 stack slots per generator.

**Theorem 4 (Polynomial Density gives Linear Expansion in F_n)**. For the free non-abelian monoid **F_n** with **n** ≥ 2, let **M** be a macro set with at most **c**·**ℓ^p** macros of each **G**-length **ℓ** ≥ 2. Then there exists a constant **d** = **d**(n,p,c) such that for all integers **s** ≥ 1:

**f_{G'}**(s) < **d**·**s**

*Interpretation*: In non-commutative settings (like Script's operation sequences), polynomially-growing macro sets only yield linear expansion. Superlinear compression requires exponentially-growing macro density.

##### 1.2 Discriminating Between Monoid Models

The MathLib analysis (Section 3 of "Compression is all you need") shows:

- **Unwrapped length** grows exponentially with both **depth** and **wrapped length**
- **Wrapped length** is approximately constant across all depths
- These results are consistent with **A_n** (free abelian) and inconsistent with **F_n** (free non-abelian)

*Conclusion*: Human mathematics occupies a polynomially-growing subset within the exponentially growing space of formal mathematics. The free abelian monoid **A_n** provides an accurate model.

#### 2. Monoid Structure of Script Operations

##### 2.1 Generators and Operations

Let **Σ** = {**σ_1**, **σ_2**, ..., **σ_n**} be the set of Unicode character indexes corresponding to Script Operations:

- ASCII printable characters (32-126): Default operations for arithmetic, logic, control flow
- Control characters (DC1-DC4): Shift, Control, Alt, Pause keyboard shortcuts
- ESC: Interrupt operation that pushes Interrupt Expression onto stack

**Definition 3 (Operation String)**. An operation string is a finite sequence **σ_{i1}σ_{i2}...σ_{ik}** where each **σ_{ij}** ∈ **Σ**. The set of all operation strings forms the free monoid **F**(Σ) under concatenation.

##### 2.2 Monoid Relations for Script

Script imposes additional relations beyond the free monoid structure:

1. **Associativity Relation**: (**ab**)c = a(**bc**) for all operations a, b, c
2. **Identity Relation**: ε·a = a·ε = a where ε is the empty operation sequence
3. **Reset Inverse Relation**: (**A** \* **B**) \* **A^(-1)** = **A** (from Group Automata Theorem)

*Note*: The inverse operation **A^(-1)** corresponds to the **Reset Operation**, which is not a true group inverse but rather a "reset to initial state" operation that satisfies the left-inverse property.

##### 2.3 Commutativity and Non-Commutativity

Script operations do NOT commute in general:

**ab** ≠ **ba**

This follows from the Group Automata Theorem's statement: "Syntax changes semantics, thus **A** has no commutative property."

However, certain operation classes may commute under specific conditions:

- **Whitespace operations** (space character 0x20) may commute with each other
- **Independent register operations** on disjoint memory regions may commute
- **Idempotent operations** satisfy **aa** = **a**

#### 3. Group Automata Chinese Room Architecture

##### 3.1 Machine Model: CRASM

The **Chinese Room Abstract Stack (Crabs) Machine** is defined as a 7-tuple:

**CRASM** = (**Q**, **Σ**, **Γ**, **δ**, **q_0**, **Z_0**, **F**)

Where:
- **Q**: Finite set of machine states
- **Σ**: Input alphabet (Unicode operation indexes)
- **Γ**: Stack alphabet (IUA stream of ASCII Data Types)
- **δ**: Transition function **δ**: Q × (Σ ∪ {ε}) × Γ → P(Q × Γ*)
- **q_0** ∈ Q: Initial state
- **Z_0** ∈ Γ: Initial stack symbol
- **F** ⊆ Q: Accepting states (**on** state from Group Automata Theorem)

##### 3.2 Monoid Action on the Stack

The monoid **M** = (**Σ***, concatenation, ε) acts on the stack **S** via:

**·**: M × S → S
**(σ_{i1}...σ_{ik}) · s** = δ(δ(...δ(δ(q_0, σ_{i1}), σ_{i2})...), σ_{ik})(s)

This action satisfies:
- **ε · s** = s (identity)
- **(ab) · s** = **a · (b · s)** (associativity)

##### 3.3 Chinese Room Components

```
┌─────────────────────────────────────────────────────────────┐
│                    Chinese Room                             │
├─────────────────────────────────────────────────────────────┤
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐    │
│  │   Door   │  │   Wall   │  │   Portal │  │  Interrupt│    │
│  │ (Slot)   │  │(Memory)  │  │ (BSeq)   │  │  Operation│    │
│  └────┬─────┘  └────┬─────┘  └────┬─────┘  └────┬─────┘    │
│       │             │              │              │         │
│       ▼             ▼              ▼              ▼         │
│  ┌──────────────────────────────────────────────────┐      │
│  │            Abstract Stack Machine (ASM)          │      │
│  │  - Operation Stack (LIFO)                        │      │
│  │  - Operand Stack (LIFO)                          │      │
│  │  - Header Stack (for B-Sequence verification)    │      │
│  │  - State Stack (for nested expressions)          │      │
│  └──────────────────────────────────────────────────┘      │
└─────────────────────────────────────────────────────────────┘
```

#### 4. Monoid-Based Protocol Specifications

##### 4.1 Operation Headers and B-Sequences

Each Script Operation has an associated header defining its input/output parameters:

```c
struct Op {
    const char* name;       // Operation name (UTF-8)
    const UIT* in;          // Input kBSQ params or OpFirst
    const UIT* out;         // Output kBSQ params or OpLast
    const char* description;// Doxygen comment (one line)
    wchar_t pop,            // Index of Pop operation
            close,          // Index of Close operation  
            default_op;     // Index of Default operation
    const char* allowed_chars; // Allowed symbols in keys
    const Slot* evaluation;   // Evaluated expression Slot
};
```

**Definition 4 (B-Sequence Header)**. A B-Sequence header is a monoid homomorphism from the free monoid of parameter types to **ℕ^k**:

**φ**: **Σ_param*** → **ℕ^k**
**φ**(τ_1...τ_m) = (n_1, n_2, ..., n_k)

where n_i counts occurrences of type i in the sequence.

##### 4.2 Expression Evaluation as Monoid Morphism

Expression evaluation is a monoid morphism:

**E**: (**Σ_ops***, concat, ε) → (**End**(S), ∘, id)

Where:
- **Σ_ops** is the set of operation indexes
- **End**(S) is the endomorphism monoid of the stack S
- **∘** is function composition (associative)
- **id** is the identity function (identity element)

Properties:
1. **E**(ε) = id (empty expression does nothing)
2. **E**(ab) = **E**(a) ∘ **E**(b) (composition of operations)

##### 4.3 Reset Operation as Identity Element

The **Reset Operation** (**R**) satisfies:

**R**(s) = s_0 for all stack states s

where s_0 is the initial state. This acts as a "zero" element rather than identity in the group sense, but serves as the identity for the monoid of reversible operations.

#### 5. Monoid-Based Virtual Machine Specification

##### 5.1 VM State Monoid

The **VM State Monoid** (**V**, ⊕, **0**) is defined as:

- **V**: Set of all possible VM states (stack configurations, register values, program counters)
- **⊕**: Sequential composition operator
- **0**: Reset state (all stacks empty, registers zeroed, PC at entry point)

**Theorem 5 (VM State Monoid Properties)**. The VM state monoid satisfies:

1. **Associativity**: (**v_1** ⊕ **v_2**) ⊕ **v_3** = **v_1** ⊕ (**v_2** ⊕ **v_3**)
2. **Identity**: **0** ⊕ **v** = **v** ⊕ **0** = **v**
3. **Closure**: **v_1**, **v_2** ∈ **V** ⇒ **v_1** ⊕ **v_2** ∈ **V**

##### 5.2 VM Instructions as Generators

Let **I** = {**i_1**, **i_2**, ..., **i_m**} be the set of VM instructions:

| Instruction | Opcode | Description |
|------------:|:------:|:-------------------------------------------------|
| PUSH        | 0x01   | Push operand onto stack                         |
| POP         | 0x02   | Pop top of stack                                |
| ADD         | 0x03   | Pop two operands, push their sum                |
| SUB         | 0x04   | Pop two operands, push difference               |
| MUL         | 0x05   | Pop two operands, push product                  |
| DIV         | 0x06   | Pop two operands, push quotient                 |
| JMP         | 0x07   | Unconditional jump                              |
| JZ          | 0x08   | Jump if zero                                    |
| CALL        | 0x09   | Call operation (push return address)            |
| RET         | 0x0A   | Return from call                                |
| RESET       | 0xFF   | Reset VM to initial state                       |

The set of all instruction sequences forms the free monoid **F**(I).

##### 5.3 Monoid Congruences for Optimization

Monoid congruences identify equivalent instruction sequences:

- **α**: ADD ADD → MUL (addition can be expressed as repeated increment)
- **β**: PUSH x POP → ε (redundant push/pop elimination)
- **γ**: CALL RET → ε (immediate return after call)

The optimized instruction set is the quotient monoid **F**(I)/≡ where ≡ is the congruence generated by {α, β, γ}.

#### 6. Group Automata Theorem Verification

**Theorem 6 (Group Automata Structure)**. The Chinese Room Abstract Stack Machine implements a Group Automata where:

- **A**: Set of all possible expression evaluation results
- **B**: Set of all possible B-Stream inputs
- ***:*** Binary operation: Expression concatenation with parameter substitution
- **e**: Reset state (empty stack, initial PC)
- **A^(-1)**: Inverse operation sequence (for reversible computations)

*Proof*: 

1. **Closure**: Expression evaluation always produces another valid expression state
2. **Associativity**: Expression concatenation is associative: (a·b)·c = a·(b·c)
3. **Identity**: Reset operation provides identity element
4. **Inverse**: Reversible operations have inverses; non-reversible operations use Reset as pseudo-inverse

**Corollary 1 (String-In-String-Out RPC)**. The monoid structure enables an RPC compiler-optimization design where:

- Input string (B-Stream) ∈ **Σ***
- Operation sequence ∈ **Σ***
- Output string (result) ∈ **Σ***

The monoid homomorphism property ensures:
**E**(input·operations) = **E**(input) ∘ **E**(operations)

This enables partial evaluation and compile-time optimization.

#### 7. Monoid-Based Compression Algorithms

##### 7.1 Macro Definition as Monoid Submonoid

A **macro** is a submonoid **M** ⊆ **F**(Σ) generated by a finite set of operation patterns:

**M** = ⟨**m_1**, **m_2**, ..., **m_k**⟩

where each **m_i** ∈ **F**(Σ) is an operation sequence.

##### 7.2 Expansion Function

The expansion function measures compression effectiveness:

**f_{G'}**(s) = sup{r ∈ **ℕ** : **B_G**(r) ⊆ **B_{G'}**(s)}

Where:
- **B_G**(r) = {w ∈ **F**(Σ) : |w|_G ≤ r} (ball of radius r in generator metric)
- **B_{G'}**(s) = {w ∈ **F**(G') : |w|_{G'} ≤ s} (ball using macros)

##### 7.3 Place Notation Compression

The place notation compression strategy uses the macro set:

**M_bn** = {**b^j·a_i** : 1 ≤ i ≤ n, j ≥ 1}

Where **b** is the base (typically 256 for byte-oriented systems).

This achieves logarithmic density: |**M_bn** ∩ **B_G**(r)| = **O**(log r)

And exponential expansion: **f_{G'}**(s) = **Θ**(b^(s/(n(b-1))))

#### 8. AI Research and Internet Task Force Requirements

##### 8.1 Monoid-Theoretic AI Behavior

AI agents interacting with the Chinese Room should:

1. Recognize monoid structure in operation sequences
2. Identify macro patterns for compression
3. Use expansion theorems to estimate expression complexity
4. Apply PageRank-style analysis on the MathLib dependency graph (monoid homomorphism from MathLib DAG to **A_n**)

##### 8.2 Monoid Homomorphisms for Cross-Language Interop

For multi-language support, define monoid homomorphisms between language-specific operation monoids:

**φ_{L1→L2}**: **F**(Σ_{L1}) → **F**(Σ_{L2})

Such that:
- **φ**(ε) = ε
- **φ**(ab) = **φ**(a)**φ**(b)

Example: C++ to Script translation:

**φ**(return x;) = PUSH(x); RET;

##### 8.3 Monoid-Based Security

Security properties can be expressed as monoid invariants:

- **Invariant 1**: No operation sequence maps a safe state to an unsafe state
- **Invariant 2**: Permission checks form a monoid homomorphism to the power set monoid
- **Invariant 3**: Audit trails are monoid morphisms to (ℤ^+, +, 0)

#### 9. Implementation Checklist for Crabs Machine

##### 9.1 Required Functions (from Crabs.h)

| Function | Purpose | Monoid Role |
|----------|---------|-------------|
| `CrabsInit` | Initialize VM state monoid | Creates identity element |
| `Push` | Push operand onto stack | Generator application |
| `Pop` | Pop operand from stack | Inverse operation (partial) |
| `CrabsReset` | Reset to initial state | Identity element |
| `CrabsScanBIn` | Scan input B-Stream | Monoid word recognition |
| `CrabsClose` | Close expression for execution | Word closure in monoid |
| `CrabsCancel` | Cancel current expression | Truncated word |
| `CrabsClear` | Clear stacks | Reset to identity |

##### 9.2 Protocol Functions

| Function | Purpose |
|----------|---------|
| `Op::evaluation` | Define operation semantics as monoid action |
| `Slot::stream` | B-Stream encoding/decoding |
| `BIn::read` | Input monoid word parsing |
| `BOut::write` | Output monoid word serialization |

##### 9.3 Virtual Machine Components

1. **Operation Stack**: Implements free monoid **F**(Σ)
2. **Operand Stack**: Implements action of monoid on stack states
3. **Header Stack**: Verifies B-Sequence well-formedness (monoid homomorphism check)
4. **State Stack**: Manages nested expression scopes (submonoid tracking)

#### 10. Future Work and Open Questions

##### 10.1 Theoretical Extensions

1. **Quantum Group Automata**: Extend to quantum monoids where operations are unitary operators
2. **Higher-Dimensional Monoids**: Use homotopy type theory for proof-relevant operations
3. **Categorical Monoids**: View CRASM as a single-object category in **Mon**

##### 10.2 Practical Implementations

1. **Monoid-Based Compiler Optimizations**: Use expansion theorems to guide peephole optimization
2. **Automated Macro Discovery**: Mine MathLib for frequently-used operation patterns
3. **Compression-Aware Scheduling**: Prioritize high-compression expressions for parallel execution

##### 10.3 Research Questions

1. What is the precise macro set for human mathematics? (Analogous to finding generators of **A_n** that map to MathLib)
2. Can we quantify "mathematical interest" via monoid compression ratios?
3. Do all useful mathematical theories embed into free abelian monoids, or are non-abelian structures necessary?

#### 11. References

1. Aksenov, V., Bodnia, E., Freedman, M. H., & Mulligan, M. (2026). "Compression is all you need: Modeling Mathematics". arXiv:2603.20396v1 [cs.AI]
2. Jacobson, N. (2009). Basic Algebra I. Dover Publications.
3. Rhoda, B., & Steinberg, B. (2009). A Theory of Finite Semigroups. Springer.
4. Hindman, N., & Strauss, D. (2012). Algebra in the Stone-Čech Compactification. De Gruyter.

#### 12. Appendix: Monoid Theory Reference

##### A.1 Free Monoid Properties

- **Universal Property**: For any monoid **M** and function **f**: Σ → **M**, there exists a unique monoid homomorphism **f̂**: **F**(Σ) → **M** extending **f**
- **Cardinality**: If |Σ| = n > 1, then |**F**(Σ)| is countably infinite
- **Growth Rate**: Ball of radius r has size **O**(n^r)

##### A.2 Free Abelian Monoid Properties

- **Isomorphism**: **A_n** ≅ **ℕ^n** (componentwise addition)
- **Universal Property**: For any abelian monoid **M** and function **f**: Σ → **M**, there exists a unique monoid homomorphism extending **f**
- **Growth Rate**: Ball of radius r has size **O**(r^n) (polynomial)

##### A.3 Grothendieck Group Construction

Given a commutative monoid **M**, the Grothendieck group **K**(M) is constructed as:

**K**(M) = (**M** × **M**) / ~

Where (**a**, **b**) ~ (**c**, **d**) iff ∃**e** ∈ **M**: **a** + **d** + **e** = **b** + **c** + **e**

For **A_n**, **K**( **A_n** ) ≅ **ℤ^n**

##### A.4 Monoid Acts

A left **M**-act is a set **X** with action **·**: M × X → X such that:

1. **e** · x = x for all x ∈ X
2. (**ab**) · x = **a** · (**b** · x) for all a,b ∈ M, x ∈ X

The Chinese Room's stack is a monoid act over the operation monoid.

---

## Requirements

1. The Crabs machine must implement the Group Automata Monoid structure as defined in this specification
2. All Script Operations must satisfy monoid axioms (closure, associativity, identity)
3. The Reset Operation must serve as the identity element for the monoid
4. B-Sequence headers must form monoid homomorphisms to **ℕ^k**
5. Expression evaluation must be a monoid morphism from operation strings to endomorphisms of the stack
6. Macro definitions must be submonoids of the free monoid
7. Compression algorithms must use expansion theorems from "Compression is all you need"
8. The VM state monoid must support sequential composition and identity

**[<< Previous Section: Messages](Messages.md) | [Next Section: Abnormal Behaviors >>](AbnormalBehaviors.md)**

[SCRIPT Specification](../) **>** [Crabs](./)

## License

Copyright [AStarship™](https://astarship.net).

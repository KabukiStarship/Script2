# [ASCII C++ Style Guide](./)

## Content Table

1. [Header Files](HeaderFiles)
   1. [Self-contained Headers](HeaderFiles#self-contained-headers)
   1. [The #define Guard](HeaderFiles#the-define-guard)
   1. [Forward Declarations](HeaderFiles#forward-declarations)
   1. [Inline Functions](HeaderFiles#inline-functions)
   1. [Names and Order of Includes](HeaderFiles#names-and-order-of-includes)
1. [Scoping](Scoping)
   1. [Namespaces](Scoping#namespaces)
   1. [Unnamed Namespaces and Static Variables](Scoping#unnamed-namespaces-and-static-variables)
   1. [Nonmember, Static Member, and Global Functions](Scoping#nonmember-static-member-and-global-functions)
   1. [Local Variables](Scoping#local-variables)
   1. [Static and Global Variables](Scoping#static-and-global-variables)
   1. [thread_local Variables](Scoping#thread-local-variables)
1. [Classes](Classes)
   1. [Doing Work in Constructors](Classes#doing-work-in-constructors)
   1. [Implicit Conversions](Classes#implicit-conversions)
   1. [Copyable and Movable Types](Classes#copyable-and-movable-types)
   1. [Structs vs. Classes](Classes#structs-vs-classes)
   1. [Inheritance](Classes#inheritance)
   1. [Operator Overloading](Classes#operator-overloading)
   1. [Access Control](Classes#-access-control)
   1. [Declaration Order](Classes#declaration-order)
1. [Functions](Functions)
   1. [Output Parameters](Functions#output-parameters)
   1. [Write Short Functions](Functions#write-short-functions)
   1. [Reference Arguments](Functions#reference-arguments)
   1. [Function Overloading](Functions#function-overloading)
   1. [Default Arguments](Functions#default-arguments)
   1. [Trailing Return Type Syntax](Functions#trailing-return-type-syntax)
1. [Other C++ Features](OtherCPPFeatures)
   1. [Rvalue References](OtherCPPFeatures#rvalue-references)
   1. [Friends](OtherCPPFeatures#friends)
   1. [Exceptions](OtherCPPFeatures#exceptions)
   1. [noexcept](OtherCPPFeatures#noexcept)
   1. [Run-Time Type Information (RTTI)](OtherCPPFeatures#run-time-type-information-rtti)
   1. [CastingStreams](OtherCPPFeatures#castingstreams)
   1. [Preincrement and Predecrement](OtherCPPFeatures#preincrement-and-predecrement)
   1. [Use of const](OtherCPPFeatures#use-of-const)
   1. [Use of constexpr](OtherCPPFeatures#use-of-constexpr)
   1. [Integer Types](OtherCPPFeatures#integer-types)
   1. [64-bit Portability](OtherCPPFeatures#64-bit-portability)
   1. [Preprocessor Macros](OtherCPPFeatures#preprocessor-macros)
   1. [0 and nullptr/NULL](OtherCPPFeatures#0-and-nullptr-null)
   1. [sizeof](OtherCPPFeatures#sizeof)
   1. [auto](OtherCPPFeatures#auto)
   1. [Braced Initializer List](OtherCPPFeatures#braced-initializer-list)
   1. [Lambda expressions](OtherCPPFeatures#lambda-expressions)
   1. [Template metaprogramming](OtherCPPFeatures#template-metaprogramming)
   1. [Boost](OtherCPPFeatures#boost)
   1. [std::hash](OtherCPPFeatures#std-hash)
   1. [C++11](OtherCPPFeatures#c-11)
   1. [Nonstandard Extensions](OtherCPPFeatures#nonstandard-extensions)
   1. [Aliases](OtherCPPFeatures#aliases)
1. [Naming](Naming)
   1. [General Naming Rules](Naming#general-naming-rules)
   1. [File Names](Naming#file-names)
   1. [Type Names](Naming#type-names)
   1. [Variable Names](Naming#variable-names)
   1. [Constant Names](Naming#constant-names)
   1. [Function Names](Naming#function-names)
   1. [Namespace Names](Naming#namespace-names)
   1. [Enumerator Names](Naming#enumerator-names)
   1. [Macro Names](Naming#macro-names)
   1. [Exceptions to Naming Rules](Naming#exceptions-to-naming-rules)
1. [Comments](Comments)
   1. [Comment Style](Comments#comment-styles)
   1. [File Comments](Comments#file-comments)
   1. [Class Comments](Comments#class-comments)
   1. [Function Comments](Comments#functions-comments)
   1. [Variable Comments](Comments#variable-comments)
   1. [Implementation Comments](Comments#implementation-comments)
   1. [Punctuation, Spelling and Grammar](Comments#punctuation-spelling-and-grammar)
   1. [TODO Comments](Comments#todo-comments)
   1. [Deprecation Comments](Comments#depreciation-comments)
1. [Formatting](Formatting)
   1. [Line Length](Formatting#line-arguments)
   1. [Non-ASCII Characters](Formatting#non-ascii-characters)
   1. [Spaces vs. Tabs](Formatting#spaces-vs-tabs)
   1. [Function Declarations and Definitions](Formatting#function-declarations-and-definitions)
   1. [Lambda Expressions](Formatting#lambda-expressions)
   1. [Function Calls](Formatting#function-calls)
   1. [Braced Initializer List Format](Formatting#braces-initializer-list-format)
   1. [Conditionals](Formatting#conditionals)
   1. [Loops and Switch Statements](Formatting#loops-and-switch-statements)
   1. [Pointer and Reference Expressions](Formatting#pointer-and-reference-expressions)
   1. [Boolean Expressions](Formatting#boolean-expressions)
   1. [Return Values](Formatting#return-values)
   1. [Variable and Array Initialization](Formatting#variable-and-array-initialization)
   1. [Preprocessor Directives](Formatting#preprocessor-directives)
   1. [Class Format](Formatting#class-format)
   1. [Constructor Initializer Lists](Formatting#constructor-initializer-lists)
   1. [Namespace Formatting](Formatting#namespace-formatting)
   1. [Horizontal Whitespace](Formatting#horizontal-whitespace)
   1. [Vertical Whitespace](Formatting#vertical-whitespace)
1. [Exceptions to the Rules](ExceptionsToTheRules)
   1. [Existing Non-conformant Code](ExceptionsToTheRules#existing-non-conformant-code)
   1. [Windows Code](ExceptionsToTheRules#windows-code)

## Background

The Automaton Standard Code for Information Interchange (ASCII) C++ Style Guide is a combination of the Google C++ Style Guide with the ASCII Data Specification which is a part of  which is a part of the Serial Chinese Room, Interprocess, and Telemetry (SCRIPT) Specification.

C++ is one of the main development languages used by many of Google's open-source projects. As every C++ programmer knows, the language has many powerful features, but this power brings with it complexity, which in turn can make code more bug-prone and harder to read and maintain.

The goal of this guide is to manage this complexity by describing in detail the dos and don'ts of writing C++ code. These rules exist to keep the code base manageable while still allowing coders to use C++ language features productively.

_Style_, also known as readability, is what we call the conventions that govern our C++ code. The term Style is a bit of a misnomer, since these conventions cover far more than just source file formatting.

Most open-source projects developed by Google conform to the requirements in this guide.

Note that this guide is not a C++ tutorial: we assume that the reader is familiar with the language.

The ASCII C++ Style Guide makes heavy use of the ASCII Data Specification. You can find a copy of the the specification at <https://github.com/KabukiStarship/Script2/blob/master/docs/rfc/ascii_data_specification_rfc>.

### Goals of the Style Guide

* Why do we have this document?
  * There are a few core goals that we believe this guide should serve. These are the fundamental **whys** that underlie all of the individual rules. By bringing these ideas to the fore, we hope to ground discussions and make it clearer to our broader community why the rules are in place and why particular decisions have been made. If you understand what goals each rule is serving, it should be clearer to everyone when a rule may be waived (some can be), and what sort of argument or alternative would be necessary to change a rule in the guide.

The goals of the style guide as we currently see them are as follows:

* Style rules should pull their weight
  * The benefit of a style rule must be large enough to justify asking all of our engineers to remember it. The benefit is measured relative to the codebase we would get without the rule, so a rule against a very harmful practice may still have a small benefit if people are unlikely to do it anyway. This principle mostly explains the rules we don’t have, rather than the rules we do: for example, `goto` contravenes many of the following principles, but is already vanishingly rare, so the Style Guide doesn’t discuss it.
* Optimize for the reader, not the writer
  * Our codebase (and most individual components submitted to it) is expected to continue for quite some time. As a result, more time will be spent reading most of our code than writing it. We explicitly choose to optimize for the experience of our average software engineer reading, maintaining, and debugging code in our codebase rather than ease when writing said code. "Leave a trace for the reader" is a particularly common sub-point of this principle: When something surprising or unusual is happening in a snippet of code (for example, transfer of pointer ownership), leaving textual hints for the reader at the point of use is valuable (`std::unique_ptr` demonstrates the ownership transfer unambiguously at the call site).

* Be consistent with existing code
  * Using one style consistently through our codebase lets us focus on other (more important) issues. Consistency also allows for automation: tools that format your code or adjust your `#include`s only work properly when your code is consistent with the expectations of the tooling. In many cases, rules that are attributed to "Be Consistent" boil down to "Just pick one and stop worrying about it"; the potential value of allowing flexibility on these points is outweighed by the cost of having people argue over them.

* Be consistent with the broader C++ community when appropriate
  * Consistency with the way other organizations use C++ has value for the same reasons as consistency within our code base. If a feature in the C++ standard solves a problem, or if some idiom is widely known and accepted, that's an argument for using it. However, sometimes standard features and idioms are flawed, or were just designed without our codebase's needs in mind. In those cases (as described below) it's appropriate to constrain or ban standard features. In some cases we prefer a homegrown or third-party library over a library defined in the C++ Standard, either out of perceived superiority or insufficient value to transition the codebase to the standard interface.

* Avoid surprising or dangerous constructs
  * C++ has features that are more surprising or dangerous than one might think at a glance. Some style guide restrictions are in place to prevent falling into these pitfalls. There is a high bar for style guide waivers on such restrictions, because waiving such rules often directly risks compromising program correctness.

* Avoid constructs that our average C++ programmer would find tricky or hard to maintain
  * C++ has features that may not be generally appropriate because of the complexity they introduce to the code. In widely used code, it may be more acceptable to use trickier language constructs, because any benefits of more complex implementation are multiplied widely by usage, and the cost in understanding the complexity does not need to be paid again when working with new portions of the codebase. When in doubt, waivers to rules of this type can be sought by asking your project leads. This is specifically important for our codebase because code ownership and team membership changes over time: even if everyone that works with some piece of code currently understands it, such understanding is not guaranteed to hold a few years from now.

* Be mindful of our scale
  * With a codebase of 100+ million lines and thousands of engineers, some mistakes and simplifications for one engineer can become costly for many. For instance it's particularly important to avoid polluting the global namespace: name collisions across a codebase of hundreds of millions of lines are difficult to work with and hard to avoid if everyone puts things into the global namespace.

* Concede to optimization when necessary
  * Performance optimizations can sometimes be necessary and appropriate, even when they conflict with the other principles of this document.

The intent of this document is to provide maximal guidance with reasonable restriction. As always, common sense and good taste should prevail. By this we specifically refer to the established conventions of the entire Google C++ community, not just your personal preferences or those of your team. Be skeptical about and reluctant to use clever or unusual constructs: the absence of a prohibition is not the same as a license to proceed. Use your judgment, and if you are unsure, please don't hesitate to ask your project leads to get additional input.

## C++ Version

Currently, code should target C++11, i.e., should not use C++14 or C++17 features. The C++ version targeted by this guide will advance (aggressively) over time.

Code should avoid features that have been removed from the latest language version (currently C++17), as well as the rare cases where code has a different meaning in that latest version. Use of some C++ features is restricted or disallowed. Do not use [non-standard extensions](#Nonstandard_Extensions).

## Overall Takeaway

Use common sense and **BE_CONSISTENT**.

If you are editing code, take a few minutes to look at the code around you and determine its style. If they use spaces around their `if` clauses, you should, too. If their comments have little boxes of stars around them, make your comments have little boxes of stars around them too.

The point of having style guidelines is to have a common vocabulary of coding so people can concentrate on what you are saying, rather than on how you are saying it. We present global style rules here so people know the vocabulary. But local style is also important. If code you add to a file looks drastically different from the existing code around it, the discontinuity throws readers out of their rhythm when they go to read it. Try to avoid this.

OK, enough writing about writing code; the code itself is much more interesting. Have fun!

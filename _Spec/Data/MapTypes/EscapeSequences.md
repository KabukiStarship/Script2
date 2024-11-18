# [SCRIPT Specification](../../)

## [ASCII Data Specification](../)

### [Map Types](./)

### Escape Sequence

An Escape Sequence (ESC) is a sequence of one or more Script Expressions that replaces a B-Sequence and ends with no Operands on the stack. ESC objects may be 8, 16, 32, or 64-bit to represent the Object's Size. Script Expressions may have multiple output parameters and ESC will be evaluated and the socket output, if ESC Operations have the same output signature, may be directly substituted for any BSQ with the same signature.

#### ESC Example

```Script2
Parent.Child1.Foo ("Hello world!", 1, 2, 3); //< () and ',' are optional and
Parent Child1 Foo "Hello world!", 1, 2, 3; //< Pop Operations are programmable.
Parent Child1 Foo "Hello world!" 1 2 3    //< There is no pop instruction here
              Foo "Hello "                //< so this is a _::TStrand<> of Ops.
                  "world!" 1 2
                  3;                      //< The Last 2 Foo calls execute when
                                          //< the ";" operation is read or
Parent {
    Child1 {
        Foo ("Hello world!", 1, 2, 3)
        Foo ("Hello world!", 1, 2, 3)    //< String operations together!
        Bar ("Lets go!")
    }
    Child2 {
        Foo ("Hello world!" 1, 2, 3)
    }
} //< Code won't execute until you close the curly brackets or type ';'
```

**[<< Previous Section:](./) | [Next Section: >>](./)**

## License

Copyright Kabuki Starship <<https://github.com/KabukiStarship/Script2>>.

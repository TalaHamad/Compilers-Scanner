# Compilers-Scanner
This project is the first part of a compiler for the COMP2023 language. The scanner reads a file containing a COMP2023 program and produces a sequence of tokens corresponding to the program's lexemes.

**Scanner Requirements**

The scanner must be able to identify the following lexemes:

* **Comments:** Comments are indicated by double # (##) and contain any characters except a new line. The scanner should recognize comments and strip them from the input; it should not return a comment token.
* **Identifiers:** A sequence of one or more upper-case and lower-case letters, digits, or underscores that does not start with a digit.
* **Reserved words:** Keywords in COMP2023 that cannot be used as identifiers.
* **Integer literals:** A sequence of digits, optionally preceded by a negative sign (-).
* **Strings:** Sequences of characters that contain any character except a double quote " or newline.
* **Operators:** The following one or two-character symbols:

```
() :=   +  ;  =  { }  !=
< >  >= <=
 *
```

**What you will learn**

* How to write regular expressions to describe lexemes.
* How to use and test a file descriptor.
* How to write and test a scanner.
* How to use the Unix utility lex to automatically produce scanners from regular expressions.

# RegExp subset engine

# Reference

## Fundamentals

### Characters

The simplest regular expression is a single literal character, excluding _metacharacters_ `*+?()[]{}|\`. To match a metacharacter, escape it with a backslash: `\*` matches a literal asterisc character.

### Escape Characters

Escaped characters are some meaningful sequence of character flowing a `\` (backslash) character. Escape characters can be either a _character set_ (more on that later) or a _special character_. Escaped metacharacters are special characters

### Special characters

As mentioned earlier, especial character are some combination of symbol flowing a `\`, as of this subset, these are included:

| Escape Sequence      | Escaped Character
| -------------------- | -----------------
| `\n`                 | Newline (ASCII 0x0A)
| `\r`                 | Carriage Return (ASCII 0x0D)
| `\t`                 | Horizontal Tab (ASCII 0x09)
| `\0`                 | Null Terminator (ASCII 0x00)
| `\`_`ooo`_           | Octal Character _`ooo`_
| `\x`_`xx`_           | Hexadecimal Character _`xx`_
| `\u`_`xxxx`_         | Unicode Hexadecimal _`xxxx`_
| `\`_`metacharacter`_ | Escaped Metacharacter, any of `*+?()[]{}\|\`

### Dot Operator

Technically a character set, the dot operator, `.`, matches any character other than a newline.

### Concatenation

Let <code>_e_<sub>0</sub></code> and <code>_e_<sub>0</sub></code> be RegExp, the <code>_e_<sub>0</sub>_e_<sub>1</sub></code> is the _concatenation_ of <code>_e_<sub>0</sub></code> and <code>_e_<sub>1</sub></code>. It matches <code>_e_<sub>0</sub></code> then <code>_e_<sub>1</sub></code>.

### Alternation

Let <code>_e_<sub>0</sub></code> and <code>_e_<sub>0</sub></code> be RegExp, the <code>_e_<sub>0</sub>|_e_<sub>1</sub></code> is the _alternation_ of <code>_e_<sub>0</sub></code> and <code>_e_<sub>1</sub></code>. It matches <code>_e_<sub>0</sub></code> or <code>_e_<sub>1</sub></code>.

## Quantifiers

### Zero or More

The _zero or more_ quantifier, `*`, also known as the Kleene Star. Matches zero or more of the previous expression. Let <code>_e_</code> be a RegExp, then <code>_e_*</code> is quantified by a zero or more quantifier.

### One or More

The _one or more_ quantifier, `+`, also known as the Kleene Plus. Matches zero or more of the previous expression. Let <code>_e_</code> be a RegExp, then <code>_e_+</code> is quantified by a one or more quantifier.

### Zero or One

The _zero or one_ quantifier, `?`, might be understood as a _optional_ matching. Matches zero or one of the previous expression. Let <code>_e_</code> be a RegExp, then <code>_e_?</code> is quantified by a zero or one quantifier.

### Ranged Quantification

## Character Sets

# Grammar

```sgl
<expression>
   : <expression> <expression>     -- Concatenation
   | <expression> '|' <expression> -- Alternation
   | <expression> <quantifier>     -- Quantifier
   | '(' <expression> ')'          -- Group
   | <character set>               -- Character Set
   | <character>                   -- Character
   ;

<quantifier>
   : '?' ['?']
   | '*' ['?']
   | '+' ['?']
   | '{' <number> '}' ['?']
   | '{' <number> [',' [<number>]] '}' ['?']
   ;

<character set>
   : '.'
   | '[' ['^'] (<character> | <character> '-' <character>) * ']'
   ;

<character>: /[^*+?|()[\]{}]/ | '\\' /[*+?|()[\]{}]/;

<number>: /[0-9]+/;
```

# Finite Automaton

A finite automaton will here be defined as

```math
(E, T)
```
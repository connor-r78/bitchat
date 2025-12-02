# Style Guide:

Pull requests should follow this style guide. They will still be reviewed if they do not, but they may take longer to approve.

## Brackets:

Use K&R brackets. Functions have an opening bracket on a new line, nothing else does. Ending brackets always get there own line. Never use brackets where they are unnecssary, even sizeof operators:

```
int size = sizeof foo;
```

Only use parentheses with sizeof(TYPE):
```
int size = sizeof(int);
```

## Comments:

There are no comments in C; however every block in Assembly requires a comment, which should be formatted like:

```
/* [PURPOSE]
// [REGISTER]: input1
// [REGISTER]: input2
// [RETURN] in rax */
```

If you feel the need to write a comment in C, then you are not writing C correctly.

## Indentations

Indentations are two spaces. Never use more than 3 indentations. Case keywords within a switch statement are not indented.

```
switch ( foo ) {
case 1:
  break;
case 2:
  break;
default:
  return 0;
}
```

## Lines:

No line should exceed 80 columns, even Assembly comments. If the comment exceeds 80 columns break up the blocks.

For, while, if, else, else if statements should go on one line if they can fit within this limit:

```
if ( foo ) ++foo;
```

## Naming Conventions:

### Constants:

Use screaming snake case. In C, constants should always be a macro; therefore, they are expanded at compile time and not stored on the stack like variables.

```
#define FOO_FOO_FOO foo
```

### Functions:

Assembly functions use camelCase prefixed with an underscore: ```_camelCase:```

C functions use camelCase: ```void camelCase()```

### File Extensions:

Because file extensions are practically meaningless on Unix-like systems, some people like to get creative. These are the extensions used in this project:

- .bash - Bash script
- .c - C code
- .h - C header files
- .md - markdown files for reference (like this one!)
- .o - object file
- .out - Executable binary
- .s - Assembly code
- .txt - training data (note: not human-readable)

### Headers:

Name a header file the same as its corresponding file, but with a .h extension instead of a .c.

### Variables:

Variables in C should be in camelCase. In some cases, variables can be defined in Assembly. In that case, they should be in _camelCase prefixed with an underscore.

Avoid putting the type of the variable to disambiguate from another variable. Be more descriptive.

The following shorthand names are acceptable for variables:

- i - iteration (only use this in reference to loops); nested loops should be named j, then k.
- idx - index (for variables that are exclusively used for referencing an index within an array)
- j - *see i*
- k - *see i*
- tmp - temporary (for moving data into to be modified)

Never name a variable foo; that is confusing. (It also makes it look like the segment was copied from Stack Overflow).

## Spelling:

Use American English; the codebase does not care if you are British. Unix was invented in this country, and you cannot take it from us.

## Loops:

Infinite loops should be impossible. Put an upper limit on loops that have inputs that may cause them to iterate forever.

exempli gratia:

```
while ( foo < 5 ) foo *= 2;
```

would iterate forever if foo is not non-negative; thus, it should be:

```
int i = 0;
while ( foo < 5 && i < MAX_ITER ) {
  foo *= 2;
  ++i;
}
```

If escaping the loop at the point of MAX_ITER would cause undefined behavior; return a status code:

```
int i = 0;
while ( foo < 5 && i < MAX_ITER ) {
  foo *= 2;
  ++i;
}
if ( i >= MAX_ITER) return LOOP_TERMINATED;
```

Avoid Do While Loops whenever possible.

Case in point:

```
do ++foo;
while ( foo < 5 );
```

is semantically the same as:

```
int i = 0;
while ( foo <= 5 || i < 1 ) {
  ++foo;
  ++i;
}
```

NOTA BENE: The above loops do not a need an upper limit because it is impossible for them to iterate forever given foo is not null.

## Returns:

Every function must return something. For functions where the return is not used directly in the program, return a status code. Assembly functions should almost always store the return value in RAX.

## Status Codes:

`0` means OK. Negative numbers indicate an error; positive numbers indicate that the function returned a value that may be OK, but could lead to an unexpected behaviour.

## Types:

Ideally, only use the largest type required (id est do not define a variable that will only ever need one byte of memory as a `long`). However, do not define that variable as an `unsigned char` instead of an `int` because that does not adequately describe what the variable is for. Save that sort of optimization for Rust.\


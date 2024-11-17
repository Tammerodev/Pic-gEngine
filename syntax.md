## Syntax

### Namespace 

All functions and global variables should use the 'picg' prefix. 

```c
#define PREPROCESSOR_NO_PREFIX

void picg_function() 
{

}

struct picg_some_struct
{
    int picg_variable;
};
```

### File structure
- Header file extension: .h
- Source file extension: .c
- Use the `#pragma once` in the start of a header file
- If a file contains only variables, it is an header file
- Don't include source files. If a header needs functions, they are in a source file that includes the header


### Functions
- Function curly braces start on the next line
- Function name is in snake_case
- Function parameters use camelCase with lower first character
```c
void picg_print_hello(int importantVariable) 
{
    printf("Hello!");
}
```
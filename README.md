# ft_printf

ft_printf must achieve the following mandatory requirements:  
  
* Manage the following conversions: `s`, `p`, `d`, `i`, `o`, `u`, `x`, `c`.
* Manage `%%`
* Manage the flags `#`, `0`, `-`, `+` & `space`
* Manage the minimum field-width
* Manage the precision
* Manage the flags `hh`, `h`, `l`, `ll`.
  
The function must conform to 42's norm.  
The function cannot leak. All errors must be handled carefully. In no way can the function quit in an unexpected manner (Segmentation fault, bus error, double free, etc).  
Allowed functions are `write`, `getloacale`, `malloc`, `free`, `exit` and the three functions of `stdarg`. Everything else is forbidden.
***
### Using the project

Then compile with a program:
```console
gcc -Wall -Werror -Wextra main.c -I./include/ -L./ libftprintf.a
```

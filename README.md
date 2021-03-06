# ArgvHide

C++ program which demonstrates how to cipher argv CLI parameters.


## Motivation

* For a shared Linux PC I want to run a process for which the CLI parameters should be hidden.
* Linux process and parameters could be seen using e.g. `ps aux`
* I do not have root access.
* I do have access to the program's source code (and I can modify an compile it).


## Solution Approach

1. Encipher the CLI parameters using XOR and static password. (Yes, this is a truely easy "encryption", meaning no real encryption!).
2. Modify target program's source code 
   - to understand the ciphered string (decrypt), and
   - restore the original argc and argv


## Example

Instead of:
  `myprogram --param1=secret-value`

I want:
  - `myprogram --token 223675656c65666423683e9c8d9a8bd2797a69717b`
  - or just `myprogram 223675656c65666423683e9c8d9a8bd2797a69717b`
  - or encoded parameter in between like `myprogram --realparam1 --realparam2=foo --bar --token 223675656c65666423683e9c8d9a8bd2797a69717b foobar`


## How To
1. compile `g++ argvhide.cpp -o argvhide`
2. cipher CLI parameters, e.g. `./argvhide -e --param1=secret-value` --> `223675656c65666423683e9c8d9a8bd2797a69717b`
   - everything after the `-e` is taken for the target cipher string
   - the string should be everything you want to have as parameters for the target program
3. modify target program's source to include the code from [example.cpp](example.cpp).
4. compile target program
5. run target program with the ciphered string, e.g.:
   - `myprog 223675656c65666423683e9c8d9a8bd2797a69717b`
   - `myprog --token  223675656c65666423683e9c8d9a8bd2797a69717b`
   - `myprog foo bar --token 223675656c65666423683e9c8d9a8bd2797a69717b huhu`


## License
Copyright (C) 2020 by Ixtalo.  
AGPL3 license.

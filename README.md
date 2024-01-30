# Argument parsing libary 
- Supports:
  - _linux_
  - _win_
  - _mac-os_

**no extra dependencies needed


**Example** _adding arguments_
```c
    arguments_t args;
    arg_init(args, "Argparsing", "1.1.2", 4);
    arg_add(args, 'h', "help", "prints help", 0);
    arg_add(args, 'a', "add", "adds a password to the database", 1);
```

**Example** _parsing _arguments_
```c
    result_set_t parsed_arguments;
    res_init(parsed_arguments);
    arg_parse(args, parsed_arguments, argc, argv);
```

**Auto generated help**
```c
    arg_print_help(args);
```

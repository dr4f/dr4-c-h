# dr4-h-c

[![MIT License](http://img.shields.io/badge/license-MIT-blue.svg?style=flat)](https://github.com/jweinst1/dr4-h/blob/master/LICENSE.md)
![language button](https://img.shields.io/badge/Language-C-orange.svg)
![build button](https://img.shields.io/badge/Build-passing-green.svg)

*A binary, typed, data storage file format*

## Building

To build `dr4-h` examples and test files, run the following commands in your terminal

*Note:* `CMake` is required to build `dr4-h`

```
$ mkdir bin
$ cd bin
$ cmake ..
$ make
```

This will also copy the main header file, `dr4-h.h`, into the binary dir. You can also create a binary dir with a different name.

### Tests

To run the tests for `dr4-h`, run `make test` after the commands above.

### Usage

For some examples how to use `dr4-h`, you can start by running some of the example executables built with the package.

Below is some example usage of implementing a row appender with `dr4-h`.

```
$ ./row_appender 4 foo.dr4
----Data Appending Example-------
Now Creating and Appending 4 rows.
Wrote the row: True,True
To the file foo.dr4
Wrote the row: True,True
To the file foo.dr4
Wrote the row: True,True
To the file foo.dr4
Wrote the row: True,True
To the file foo.dr4
After row appending, file size is now 174
-----Finished Appending Rows to File Example-------
```

After building, a copy of the single file header, `dr4-h.h`, is copied to the binary directory. It has a copy of the license in the comments and all the code you need to use the library, so you can just include it and start using the functions, like in the examples.

Alternatively, you can use the library linkable header, `dr4-h-lib.h`, and link in the static or shared libraries built.

## Guide

dr4 uses a special binary format, where a file is composed of a base-header and a stream of rows. Each row, subsequently contains it's own header-data section and body section. First, let's look at the format of a file.

### File Format

The File format adheres to the following structure, written in BNF-form

```
<dr4-file> ::= <file-header> <file-body>
<file-header> ::= <magic-seq> <version> <reserved-bytes>
<magic-seq> ::= 83 94 121
<version> ::= <u8-int> <u8-int> <u8-int>
<reserved> ::= <u8-int> <u8-int>

<file-body> ::= <row> | <row> <file-body>
<row> ::= <row-header> <row-body> <stop-row>
<row-header> ::= <u32-int> <u32-int> <offset-list>
<offset-list> ::= <u32-int> | <u32-int> <offset-list>
<stop-row> ::= 0

<u32-int> ::= 0-4294967295
<u8-int> ::= 0-255
```

The file body of dr4 files does not have a depednency on size-based information in the file header. Thus, the number of rows in the file can grow indepednetly of modifying it's header.

The `<row-body>` rule defined above carries a much more specialized syntax, one that is still not complete, and will expand in the future. However, the most general form of a row's data can be displayed below.

```
<row-body> ::= <type> <byte-seq>
<type> ::= <u8-int>
<byte-seq> ::= <u8-int> | <u8-int> <byte-seq>

<u8-int> ::= 0-255
```

In the original BNF grammar for the file, the rows possess a component called an *offset list*. This list functions as an array of where the beginning of a field of the row exists in the body. The first member of the offset list is always 0. 

One other important rule is that an "empty" row cannot exist. It must have at least one element.

### API

This single header library is designed to be super light-weight. It doesn't define any library-specific types, it aims to just treat arrays of rows as `void*` for reading and writing. The header, coming pre-packed with safe allocationa and deallocation functions is ready to use for dr4 data handling. 

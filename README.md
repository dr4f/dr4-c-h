# dr4-h

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

After building, a copy of the single file header, `dr4-h.h`, is copied to the binary directory. It has a copy of the license in the comments and all the code you need to use the library, so you can just include it and start using the functions, like in the example.

Alternatively, you can use the library linkable header, `dr4-h-lib.h`, and link in the static or shared libraries built.
<div id="header">
    <p align="center">
      <b>cactus 🌵</b><br>
  	  <span font-size="16px">a cross platform productivity tool.</span><br>
      <span font-size="12px">Made by <a href="http://epmor.app">Ethan</a> with love.</span><br><br>
      <span><a href="https://www.twitter.com/glassofethanol">Twitter</a> | <a href="https://github.com/sponsors/gweithio">Support</a></span><br><br>
    </p>
</div>

### NOTE: Currently this repository is a work in progress

### About

Cactus is a productivity tool written in C99 focused on portability.

### Features

```
- Take Notes that are synced to a SQLite DB
- Creating, updating, deleting and getting a single or all notes
```

### Requirements

```
- CMake, for building and Ninja instead of Makefiles :)
- Conan, for deps
- A C compiler, I use clang specifics in the Cmakefile
```

### Usage

**Creating a Note**

`cactus new <text>`

```bash
$ cactus new "Hello, World!"
```

**Deleting a Note**

`cactus delete <id>`

```bash
$ cactus delete 1
```

**Deleting All Notes**

```bash
$ cactus delete-all
```

**Uodating a Note**

`cactus delete <id> <new text>`

```bash
$ cactus update 23 "New Note Change"
```

**Getting a Note**

`cactus get <id>`

```bash
$ cactus get 10
```

**Getting all Notes**

`cactus get-all`

```bash
$ cactus get-all
```

### Target Platforms (Currently)

```
- Linux
- MacOS
- Windows (Future target)
```

### Building

Will download the deps from Conan building the cmake structure and build the project

```bash
$ ./build.sh
```

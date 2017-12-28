# desu

This is a joke programming language but it works. It is just like brainfuck and sacred. The language is turing complete, so it can solve any computational problem in due time.

## Building, Compiling, and Running

Requires a linux operating system, g++, gcc, and make.

```
make
./desu [file.desu]
./file
```

### Operations:
```
desuwa      Increments byte
desuwah     Decrements byte
desu        Move right
des         Move left
tan         Jump past matching chan if byte is zero
chan        Jumps back to matching tan if byte is non-zero
waifu       Take input
senpai      Output current byte
```

### Example Program:
```
desuwa desuwa desuwa desuwa desuwa desuwa desuwa desuwa
    tan
        desu
        desuwa desuwa desuwa desuwa desuwa
        des
        desuwah
    chan
desu
senpai
```
Output: (

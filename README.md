<h1>desu</h1>

This is a joke programming language but it works. It is just like brainfuck and sacred. The language is turing complete, so it can solve any computational problem in due time.<br>
Requires a linux operating system, gcc, and makefile to build and use.<br>

Operations:<br>
> desuwa      Increments byte<br>
> desuwah     Decrements byte<br>
> desu        Move right<br>
> des         Move left<br>
> tan         Jump past matching chan if byte is zero<br>
> chan        Jumps back to matching tan if byte is non-zero<br>
> waifu       Take input<br>
> senpai      Output current byte<br>

Example Program:<br>
> desuwa desuwa desuwa desuwa desuwa desuwa desuwa desuwa<br>
    > tan <br>
        > desu <br>
        > desuwa desuwa desuwa desuwa desuwa <br>
        > des <br>
        > desuwah <br>
    > chan <br>
> desu <br>
> senpai<br>
Output: (<br>
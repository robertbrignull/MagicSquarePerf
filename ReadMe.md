# Magic squares

This repo contains a number of implementations of algorithms to check if a given sequence of digits forms a [magic square](https://en.wikipedia.org/wiki/Magic_square).
The idea to do this came from an [excellent article](http://wordsandbuttons.online/challenge_your_performance_intuition_with_cpp_magic_squares.html) which aimed to show how our intuition of performance is often wrong and how often a fast but stupid test is better than a slow but intelligent one.

Here I implement nearly all of the methods described in that article, and add a couple of my own.
I was expecting my versions to be faster as when I was reading the article I was wondering why the writer was not doing these things.
It turns out however that both of my methods were slower overall, but at least now we know.

I think I wrote better measurement code than the original article as I attempt to account for the time spend just iterating all the inputs.
This time is quite significant and is measured using a trivial implementation that returns false always.
  
Another improvement is to try with multiple sets of input data.
The original article only used the set of all combinations where every character had an equal chance to be any digit from 1 to 9.
I also try using the set of all permutations where we guarantee that each digit appears precisely once and try all variations.

---

To build, do
```
cmake .
make
```
and then to run, do
```
./magic_squares_perf
```

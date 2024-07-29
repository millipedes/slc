# :zap: Variables and Types
`slc`, as every programming language does, supports variables. For this example
we will be writing to a file called `variables_and_types.slc`. Let's start off
with an easy line:
```
x = 5;
```
Simple enough, now there is a variable `x` which holds the value `1`.  There are
several basic types:
  - integer (32 bit signed).
  - double (64 bit IEEE 754).
  - string (8 bit characters, null terminated).
  - boolean (true/false)
  - shape (see manual).
  - array (composable collections of the above types).

Let's test it out:
```
y = [1, 2.0, "hello world", true, false, rectangle(), x, [ellipse(), 2]];
```

Now that we have some stuff defined we want to access it:
```
draw(y[x]);
draw(y[7][0]);
```

Notice that with composite arrays you can continue to access inner arrays by
appending accessors (i.e. `[x]`).

In this directory there is a more advanced example of using arrays.

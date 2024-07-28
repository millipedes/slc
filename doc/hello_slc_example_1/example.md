# :zap: Hello slc
Before proceeding, please build the `slc` binary.  For instructions on how to do
this see `building.md`.

Let's write our first `slc` program (for this example I will open and write to a
file called `hello_slc.slc`):
```
draw(rectangle());
```
There is a couple of things to notice about this program:
  1) Statements are ended with `;`s to allow for the language to be white-space
  agnostic (i.e. it doesn't matter how much/little white-space there is).
  2) There are defaults for just about everything (in this case rectangle)! The
  reason for this being is that a design goal of `slc` is to have as light a
  mental burden as possible (I hate googling how to x in matplotlib (not a bad
  library just a shortcoming which I have encountered)).

Next let's make our output diagram
```
./slc hello_slc.slc
```

Simple as that! There will now be a picture called `a.png` in the directory you
made your diagram.

Something to notice about your diagram though: it just looks like a quarter of
what you would expect for a rectangle?

This is expected though!  Each primitive in `slc` has defaults and the default
of shapes like a rectangle is to have a center point at `(0, 0)`.  Also notice
that when the user writes a shape directive the resulting image will be
transparent except for the shape (later in this tutorial we will discuss how to
put shapes onto `canvas`s) The coordinates for an `slc` diagram are as follows:
```
________________
|(0,0)         (max, 0)
|
|
|
|
(0, max)       (max, max)
```

Okay, let's make something a little more useful. Let's start by getting the
whole rectangle in frame and making it our favorite color:
```
draw(rectangle(center_x 300.0, center_y 300.0, height 500, width 500, pixel_g 35, pixel_b 66));
```
Neat! Now we have a whole rectangle and its our favorite color!  Some things to
notice:
  1) Our favorite color has a red value of 0, so we didn't need to specify it
  (sensible low mental overhead defaults).
  2) Is the order important? No. For any list in `slc` (broken record here but
  low mental overhead).
  3) There is implicit typing in `slc` so the existence of a `.` in a number
  makes it a double (which is required for point specifications).

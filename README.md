# mypdf

This is my personal development fork of qpdf. It is based on qpdf version 11.9.0. It maintains binary compatibility with
qpdf but otherwise deviates from the rules and conventions of qpdf. A broad outline will be given below, with the
details in MyChangelog.md.

qpdf is copyright (c) 2005-2024 Jay Berkenbilt. For details see NOTICE.md. The qpdf readme can be found in
QPDF-README.md.

The main purpose of this branch is to allow me to develop my thinking about qpdf and the direction in which I would like
to see it develop. This includes testing out the interaction of various ideas. While the purpose of this fork is
personal, comments are welcome.

## Key differences between mypdf and qpdf

### Header files

I am starting to split header files for key objects into separate public and private header files. The key reasons for
this are:

- it simplifies include order

- it allows us to use private class objects in data members

- it declutters some very long header files

  Header files are a major / the main element of the documentation. Cluttering them up with lots of private
  implementation detail makes them more difficult to use as documentation

- it allows separation of the public and private API

Splitting the header files into public and private parts raises the question of whether the member pattern used by qpdf
is appropriate in these circumstances or whether the Members class should be replaced by a full private implementation
class. Arguably this approach has already been adopted by QPDFObjectHandle, which uses QPDFObject as its Members class
augmented with methods, and the JSON class, where

In addition to the split into public and private header files I have added FUTURE header files where the changes I
perceive should happen for qpdf 12 would make header files unreadable if both live and FUTURE versions are included
in the same header file.

### Future changes

Make QPDFObjecthandle accessor methods const where possible.

Treat uninitialized QPDFObjecthandles as null objects. See qpdf PR1179 for a summary of the rationale.

### Programming conventions and style

mypdf deviates from the conventions of qpdf in a number of ways. This partly reflects my personal preferences as mypdf
is my personal 'play' area and partly reflects the two major aims:

- use a more modern , idiomatic style in order to make qpdf more accessible

- make qpdf easier to read and understand. I believe that to make a unit of code easy to understand it is necessary to
  be able to look at the whole unit at the same time. This means that a single function/method should fit onto a single
  screen. While this means than long methods will need to be broken up into smaller methods, it also means that
  unnecessary verbosity should be avoided.

The most obvious deviation from the qpdf house style is that I am moving away from camel-case naming with explicit
getters and setters for methods/functions to standard library style use of underscores. While I prefer this style, this
in itself does not justify using an inconsistent style. What does justify it is that

- moving to typed object handles will require new methods that largely replace existing methods. Trying to come up with
  new names in the existing style would require substantial acrobatics in the invention of new names that would make
  the API more complex and confusing rather than simplifying it. Replacing e.g. getRoot with root is straight-forward
  and predictable as well as making it obvious which one is the new and which one is he legacy method.

- the bread and butter job of qpdf is to manipulate containers such as dictionaries, arrays and trees. It makes sense
  to model the qpdf API on the standard library as far as possible.

The detailed deviations are:

- 'this->' is only used where necessary

- unnecessary brackets and braces are eliminated, in particular:

    - braces around single line 'if' bodies

    - brackets around arithmetic comparisons

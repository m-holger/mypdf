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
  implementation detail makes them more difficult to use as documentation.

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

Treat uninitialized QPDFObjecthandles as null objects. See qpdf PR1179 for a summary of the rational. 



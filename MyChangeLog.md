Change Log
==========


2024-04-15

- Refactor QPDFJob::handleUnderOverlay and related methods. Add convenience class Page (local to QPDFJob) to remove some
  of the boilerplate arising from 0 and 1 based page numbering. Driver for the change is preparation for implementing
  the QPDFAssembler class.

- Refactor QPDFWriter. For detail see qpdf PR1161. Part of the preparation for support of incremental updates.

- Refactor the creation of unresolved objects. For detail see qpdf PR1171. Part of the preparation for support of
  incremental updates.

- Refactor QPDF::parse_xrefEntry. For detail see qpdf PR1170. Part of the preparation for support of incremental
  updates.

2024-04-16

- Refactor resolving unresolved objects. Make unresolved objects responsible for determining their type, copy
  themselves, unparse themselves, etc. instead of leaving object handle responsible for handling this. Unresolved
  objects are uncommon (especially in pdf files with object streams where encountering one unresolved object resolves a
  large number of them) as a first encounter will resolve them.

- In FUTURE, Make QPDFObjectHandle accessor const where possible. This relies on the refactoring of resolving unresolved
  objects.

2024-04-21

- In FUTURE, make QPDFObjectHandle::getTypeName also const (omission in last change).

- In FUTURE, treat uninitialized objects as null objects. . See qpdf PR1179 for a summary of the rational.

Change Log
==========


2024-04-15

- Refactor QPDFJob::handleUnderOverlay and related methods. Add convenience class Page (local to QPDFJob) to remove some
  of the boilerplate arising from 0 and 1 based page numbering. Driver for the change is preparation for implementing
  the QPDFAssembler class.

- Refactor QPDFWriter. For detail see qpdf PR1161. Part of the preparation for support of incremental updates.

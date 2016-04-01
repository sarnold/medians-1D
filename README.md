medians-1D
==========

These are various C routines for doing a 1-dimensional median
search.  QuickSelect and Wirth are the fastest for nominal size
input data, but require a copy of the array in memory.  Torben
is much slower for small data, but operates on a read-only data 
set of arbitrary size (speed difference decreases as data size
gets large).

All the functions take the same input parameters and return the
same output.  The typedef should be changed as appropriate for 
the input data.

Integrates with https://github.com/sarnold/adaptive-median

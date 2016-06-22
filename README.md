medians-1D
==========

[![medians-1D License](https://img.shields.io/badge/license-GPL3-blue.svg?dummy)](https://github.com/sarnold/medians-1D/blob/master/medians-1D/LICENSE)
[![GitHub version](https://badge.fury.io/gh/sarnold%2Fmedians-1D.svg)](https://badge.fury.io/gh/sarnold%2Fmedians-1D)
[![Build Status](https://travis-ci.org/sarnold/medians-1D.svg?branch=master)](https://travis-ci.org/sarnold/medians-1D)
[![Code Climate](https://codeclimate.com/github/sarnold/medians-1D/badges/gpa.svg)](https://codeclimate.com/github/sarnold/medians-1D)
[![Github Issues](http://githubbadges.herokuapp.com/sarnold/medians-1D/issues.svg?style=flat-square&dummy)](https://github.com/sarnold/medians-1D/issues)

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

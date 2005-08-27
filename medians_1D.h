/********************************************************************
 * $RCSfile$
 * CSCI:  utility
 * CSC:  filters
 *
 * Stephen Arnold <stephen.arnold@acm.org> 
 * $Date$
 *
 * These are the optimized C routines for a 1-dimensional median
 * search.  QuickSelect and Wirth are the fastest for nominal size
 * input data, but require a copy of the array in memory.  Torben
 * is much slower in general, but operates on a read-only data set
 * of arbitrary size.
 *
 * $Log$
 * Revision 1.2  2005/08/27 00:29:34  sarnold
 * header and comment cleanup
 *
 * Revision 1.1.1.1  2005/08/26 20:18:07  sarnold
 * initial 1-D median filter demo
 *
 *
 *
 *
 *******************************************************************/

/* Data modified by the QuickSelect and Wirth routines;
   change the type as required. */

typedef float pixelvalue;

/*------------------- Functions: ANSI C prototypes -------------------------*/

pixelvalue torben(pixelvalue a[], int n);

pixelvalue quick_select(pixelvalue a[], int n);

pixelvalue kth_smallest(pixelvalue *, int, int);
/* call the following macro:
 * median_WIRTH(a,n) kth_smallest(a,n,(((n)&1)?((n)/2):(((n)/2)-1)))
 * to get the median using the above function
 */

#define median_WIRTH(a,n) kth_smallest(a,n,(((n)&1)?((n)/2):(((n)/2)-1)))



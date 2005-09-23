/***********************************************************************
 * $RCSfile$
 *
 * $Log$
 * Revision 1.4  2005/09/23 05:50:54  sarnold
 * updated to doxygen-style comments
 *
 * Revision 1.3  2005/08/28 07:03:53  sarnold
 * more fine-tuning
 *
 * Revision 1.2  2005/08/27 00:29:34  sarnold
 * header and comment cleanup
 *
 * Revision 1.1.1.1  2005/08/26 20:18:07  sarnold
 * initial 1-D median filter demo
 *
 * Stephen Arnold <stephen.arnold@acm.org> 
 * Last edit:  $Date$
 *
 ***********************************************************************/

/*! \file medians_1D.h
   \brief Function prototypes for 1-D median search.
  
   These are various C routines for doing a 1-dimensional median
   search.  QuickSelect and Wirth are the fastest for nominal size
   input data, but require a copy of the array in memory.  Torben
   is much slower in general, but operates on a read-only data set
   of arbitrary size.
   
   All the functions take the same input parameters and return the
   same output.  The typedef should be changed as appropriate for 
   the input data.
 */
 
/*! \fn pixelvalue quick_select(pixelvalue a[], int n)
   \brief Quickselect algorithm from Numerical Recipes

   Function  :   quick_select()
    - In     :   array of elements, # of elements in the array
    - Out    :   one element
    - Job    :   find the median element in the array
    - Note   :   chooses the lower median for an even number of elements

	Reference:

	This Quickselect routine is based on the algorithm described in
	"Numerical recipes in C", Second Edition, Cambridge University
	Press, 1992, Section 8.5, ISBN 0-521-43108-5.
	Original code by Nicolas Devillard - 1998. Public domain.
	Modified by Stephen Arnold <stephen.arnold@acm.org> August 2005.

 */

/////////////////////////////////////////////////////////////////////////

/*! \fn pixelvalue kth_smallest(pixelvalue *, int, int)
   \brief Rank-order filter for Wirth's algorithm (requires macro)

   Function  :   kth_smallest()
    - In     :   array of elements, # of elements in the array, rank k
    - Out    :   one element
    - Job    :   find the kth smallest element in the array
    - Note   :   use the median_WIRTH() macro to get the median

        Reference:

        Author: Wirth, Niklaus (1976) Algorithms + data structures = programs,
        Prentice-Hall, Englewood Cliffs, NJ.
	Original code by Nicolas Devillard - 1998. Public domain.
	Modified by Stephen Arnold <stephen.arnold@acm.org> August 2005.

 */

/////////////////////////////////////////////////////////////////////////

/*! \fn pixelvalue torben(pixelvalue a[], int n)
   \brief Torben's algorithm for large read-only data sets

   Function  :   torben()
    - In     :   array of elements, # of elements in the array
    - Out    :   one element
    - Job    :   find the median element in a read-only array of arbitrary size

	Reference:

	This code is public domain.
	Algorithm by Torben Mogensen, original code by N. Devillard.
	Modified by Stephen Arnold <stephen.arnold@acm.org> August 2005.

 */

/////////////////////////////////////////////////////////////////////////

/*! \def median_WIRTH(a,n)
    \brief A macro that returns the median from kth_smallest.
   
    Initial implementation of Wirth's algorithm uses this macro to wrap
    the kth_smallest function.  Need to change to a function.
*/

/*! \var typedef pixelvalue
    \brief Typedef for input data

    This should be changed according to the data being filtered, e.g.,
    filtering 8-bit gray-scale images would use "int".
*/

#ifndef _MEDIANS_1D_H_
#define _MEDIANS_1D_H_

/* Data modified by the QuickSelect and Wirth routines;
   change the typedef below as required. */

typedef float pixelvalue;

pixelvalue quick_select(pixelvalue a[], int n);

pixelvalue kth_smallest(pixelvalue *, int, int);

#define median_WIRTH(a,n) kth_smallest(a,n,(((n)&1)?((n)/2):(((n)/2)-1)))

pixelvalue torben(pixelvalue a[], int n);

#endif

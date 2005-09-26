/***********************************************************************
 * $RCSfile$
 *
 * These are speed-optimized C routines for a 1-dimensional median
 * search.  QuickSelect and Wirth are the fastest for nominal size
 * input data, but require a copy of the array in memory.  Torben
 * is much slower in general, but operates on a read-only data set
 * of arbitrary size.  There are other more optimized routines for
 * hard real-time applications.
 *
 * $Log$
 * Revision 1.7  2005/09/26 02:57:49  sarnold
 * changed macros to functions (makes swig happy)
 *
 * Revision 1.6  2005/09/23 05:50:54  sarnold
 * updated to doxygen-style comments
 *
 * Revision 1.5  2005/09/22 02:14:02  sarnold
 * added swig info and updated make file
 *
 * Revision 1.4  2005/08/28 07:03:53  sarnold
 * more fine-tuning
 *
 * Revision 1.3  2005/08/27 00:29:34  sarnold
 * header and comment cleanup
 *
 * Revision 1.2  2005/08/26 21:29:54  sarnold
 * minor fixes and cleanup
 *
 * Revision 1.1.1.1  2005/08/26 20:18:07  sarnold
 * initial 1-D median filter demo
 *
 * Stephen Arnold <stephen.arnold@acm.org>
 * $Date$
 *
 **********************************************************************/

static const char rcsid[] =
    "$Id";

#include "medians_1D.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//! Pixel-swapping macro
/*! Macro left-over from initial implementation.  Need to change to
    a real function and let the compiler do the work
*/

//! Function implementing basic pixel swapping algorithm
void swap(pixelvalue *a, pixelvalue *b) {
    register pixelvalue t;
    t=*a; *a=*b; *b=t;
    return;
}

//! Function implementing quickselect algorithm
/*!
   Function :   quick_select()
    - In    :   array of elements, # of elements in the array
    - Out   :   one element
*/

pixelvalue
#ifdef __GNUC__
__attribute__((__no_instrument_function__))
#endif
quick_select(pixelvalue a[], int n) {
    int low, high ;
    int median;
    int middle, ll, hh;

    low = 0 ; high = n-1 ; median = (low + high) / 2;
    for (;;) {
        if (high <= low) /* One element only */
            return a[median] ;

        if (high == low + 1) {  /* Two elements only */
            if (a[low] > a[high])
                swap(&a[low], &a[high]) ;
            return a[median] ;
        }

    /* Find median of low, middle and high items; swap into position low */
        middle = (low + high) / 2;
        if (a[middle] > a[high])    swap(&a[middle], &a[high]) ;
        if (a[low] > a[high])       swap(&a[low], &a[high]) ;
        if (a[middle] > a[low])     swap(&a[middle], &a[low]) ;

    /* Swap low item (now in position middle) into position (low+1) */
        swap(&a[middle], &a[low+1]) ;

    /* Nibble from each end towards middle, swapping items when stuck */
        ll = low + 1;
        hh = high;
        for (;;) {
            do ll++; while (a[low] > a[ll]) ;
            do hh--; while (a[hh]  > a[low]) ;

            if (hh < ll)
            break;

            swap(&a[ll], &a[hh]) ;
        }
        
        /* Swap middle item (in position low) back into correct position */
        swap(&a[low], &a[hh]) ;
        
        /* Re-set active partition */
        if (hh <= median)
            low = ll;
        if (hh >= median)
            high = hh - 1;
    }
}   

//! Function implementing kth_smallest() for Wirth macro
/*!
   Function :   kth_smallest()
    - In    :   array of elements, # of elements in the array, rank k
    - Out   :   one element
*/

pixelvalue
#ifdef __GNUC__
__attribute__((__no_instrument_function__))
#endif
kth_smallest(pixelvalue a[], int n, int k) {
    register int i,j,l,m ;
    register pixelvalue x ;

    l=0 ; m=n-1 ;
    while (l<m) {
        x=a[k] ;
        i=l ;
        j=m ;
        do {
            while (a[i]<x) i++ ;
            while (x<a[j]) j-- ;
            if (i<=j) {
                swap(&a[i],&a[j]) ;
                i++ ; j-- ;
            }
        } while (i<=j) ;
        if (j<k) l=i ;
        if (k<i) m=j ;
    }
    return a[k] ;
}

//! Function wrapper for kth_smallest to get Wirth's median
/*!
   Function :   wirth()
    - In    :   array of elements, # of elements in the array
    - Out   :   one element
*/
pixelvalue
#ifdef __GNUC__
__attribute__((__no_instrument_function__))
#endif
wirth(pixelvalue a[], int n) {
    return kth_smallest(a,n,(((n)&1)?((n)/2):(((n)/2)-1)));
}

//! Function implementing Torben's algorithm
/*!
   Function :   torben()
    - In    :   array of elements, # of elements in the array
    - Out   :   one element
*/

pixelvalue
#ifdef __GNUC__
__attribute__((__no_instrument_function__))
#endif
torben(pixelvalue m[], int n) {
    int         i, less, greater, equal, half;
    pixelvalue  min, max, guess, maxltguess, mingtguess;

    half = (n+1)/2 ;
    min = max = m[0] ;
    for (i=1 ; i<n ; i++) {
        if (m[i]<min) min=m[i];
        if (m[i]>max) max=m[i];
    }

    while (1) {
        guess = (min+max)/2;
        less = 0; greater = 0; equal = 0;
        maxltguess = min ;
        mingtguess = max ;
        for (i=0; i<n; i++) {
            if (m[i]<guess) {
                less++;
                if (m[i]>maxltguess) maxltguess = m[i] ;
            } else if (m[i]>guess) {
                greater++;
                if (m[i]<mingtguess) mingtguess = m[i] ;
            } else equal++;
        }
        if (less <= half && greater <= half) break ;
        else if (less>greater) max = maxltguess ;
        else min = mingtguess; 
    }
    if (less >= half) return maxltguess;
    else if (less+equal >= half) return guess;
    else return mingtguess;
}


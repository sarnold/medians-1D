/********************************************************************
 * $RCSfile$
 * CSCI:  utility
 * CSC:  filters
 *
 * Stephen Arnold <stephen.arnold@acm.org>
 * $Date$
 *
 * These are speed-optimized C routines for a 1-dimensional median
 * search.  QuickSelect and Wirth are the fastest for nominal size
 * input data, but require a copy of the array in memory.  Torben
 * is much slower in general, but operates on a read-only data set
 * of arbitrary size.  There are other more optimized routines for
 * hard real-time applications.
 *
 * $Log$
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
 *
 *
 *
 *******************************************************************/
static const char rcsid[] =
    "$Id";

#include "medians_1D.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* This covers the first two functions below (QuickSelect and Wirth). */
/* The Wirth macro is defined in the header file medians_1D.h and the */
/* demo code. */
#ifndef PIX_SWAP
#define PIX_SWAP(a,b) { register pixelvalue t=(a);(a)=(b);(b)=t; }

/*---------------------------------------------------------------------------
   Function :   quick_select()
   In       :   array of elements, # of elements in the array, rank k
   Out      :   one element
   Job      :   find the median element in the array (chooses the lower
   		median for an even number of elements).

	Reference:

	This Quickselect routine is based on the algorithm described in
	"Numerical recipes in C", Second Edition, Cambridge University 
	Press, 1992, Section 8.5, ISBN 0-521-43108-5
	Original code by Nicolas Devillard - 1998. Public domain.
	Modified by Stephen Arnold <stephen.arnold@acm.org> August 2005
 ---------------------------------------------------------------------------*/

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
                PIX_SWAP(a[low], a[high]) ;
            return a[median] ;
        }

    /* Find median of low, middle and high items; swap into position low */
        middle = (low + high) / 2;
        if (a[middle] > a[high])    PIX_SWAP(a[middle], a[high]) ;
        if (a[low] > a[high])       PIX_SWAP(a[low], a[high]) ;
        if (a[middle] > a[low])     PIX_SWAP(a[middle], a[low]) ;

    /* Swap low item (now in position middle) into position (low+1) */
        PIX_SWAP(a[middle], a[low+1]) ;

    /* Nibble from each end towards middle, swapping items when stuck */
        ll = low + 1;
        hh = high;
        for (;;) {
            do ll++; while (a[low] > a[ll]) ;
            do hh--; while (a[hh]  > a[low]) ;

            if (hh < ll)
            break;

            PIX_SWAP(a[ll], a[hh]) ;
        }
        
        /* Swap middle item (in position low) back into correct position */
        PIX_SWAP(a[low], a[hh]) ;
        
        /* Re-set active partition */
        if (hh <= median)
            low = ll;
        if (hh >= median)
            high = hh - 1;
    }
}   

/*---------------------------------------------------------------------------
   Function :   kth_smallest()
   In       :   array of elements, # of elements in the array, rank k
   Out      :   one element
   Job      :   find the kth smallest element in the array
   Notice   :   use the median_WIRTH() macro to get the median. 

           Reference:

              Author: Wirth, Niklaus 
               Title: Algorithms + data structures = programs 
           Publisher: Englewood Cliffs: Prentice-Hall, 1976
	   Original code by Nicolas Devillard - 1998. Public domain.
	   Modified by Stephen Arnold <stephen.arnold@acm.org> August 2005
 ---------------------------------------------------------------------------*/

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
                PIX_SWAP(a[i],a[j]) ;
                i++ ; j-- ;
            }
        } while (i<=j) ;
        if (j<k) l=i ;
        if (k<i) m=j ;
    }
    return a[k] ;
}

#undef PIX_SWAP
#endif

/*---------------------------------------------------------------------------
   Function :   torben()
   In       :   array of elements, # of elements in the array, rank k
   Out      :   one element
   Job      :   find the median element in a read-only array of arbitary
		size.

	Reference:

	The following code is public domain.
	Algorithm by Torben Mogensen, original implementation by N. Devillard.
	Modified by Stephen Arnold <stephen.arnold@acm.org> August 2005
 ---------------------------------------------------------------------------*/

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


/* File : medians_1D.i */
%module medians_1D
%{
/* Put headers and other declarations here */
#define PIX_SWAP(a,b) { register pixelvalue t=(a);(a)=(b);(b)=t; }
#define median_WIRTH(a,n) kth_smallest(a,n,(((n)&1)?((n)/2):(((n)/2)-1)))
typedef float pixelvalue;
%}

extern pixelvalue torben(pixelvalue a[], int n);
extern pixelvalue quick_select(pixelvalue a[], int n);
extern pixelvalue kth_smallest(pixelvalue *, int, int);

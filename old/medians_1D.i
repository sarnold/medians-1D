/* File : medians_1D.i */
%module medians_1D
%{
/* Put headers and other declarations here */
typedef float pixelvalue;
%}

extern pixelvalue quick_select(pixelvalue a[], int n);
extern pixelvalue wirth(pixelvalue a[], int n);
extern pixelvalue torben(pixelvalue a[], int n);

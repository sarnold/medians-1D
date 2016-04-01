#!/bin/env python
import ctypes

class medians1D(object):
  def __init__(self):
    self.cfuncs = ctypes.cdll.LoadLibrary("libmedians_1d.so")

    self.cfuncs.quick_select.argtypes = (ctypes.POINTER(ctypes.c_float), ctypes.c_int)
    self.cfuncs.quick_select.restype = ctypes.c_float

    self.cfuncs.wirth.argtypes = (ctypes.POINTER(ctypes.c_float), ctypes.c_int)
    self.cfuncs.wirth.restype = ctypes.c_float

    self.cfuncs.torben.argtypes = (ctypes.POINTER(ctypes.c_float), ctypes.c_int)
    self.cfuncs.torben.restype = ctypes.c_float

    self.cfuncs.kth_smallest.argtypes = (ctypes.POINTER(ctypes.c_float), ctypes.c_int, ctypes.c_int)
    self.cfuncs.kth_smallest.restype = ctypes.c_float

  def to_float_array(self, values):
    floatArray = ctypes.c_float * len(values)
    float_values = floatArray()
    for i in range(0, len(values)):
      float_values[i] = values[i]

    float_ptr = ctypes.cast(float_values, ctypes.POINTER(ctypes.c_float))

    return float_ptr

  def quick_select(self, values):
    array = self.to_float_array(values)
    array_len = len(values)
    return self.cfuncs.quick_select(array, array_len)
      
  def wirth(self, values):
    array = self.to_float_array(values)
    array_len = len(values)
    return self.cfuncs.wirth(array, array_len)

  def torben(self, values):
    array = self.to_float_array(values)
    array_len = len(values)
    return self.cfuncs.torben(array, array_len)

  def kth_smallest(self, values, k):
    array = self.to_float_array(values)
    array_len = len(values)
    return self.cfuncs.kth_smallest(array, array_len, k)

if __name__ == "__main__":
  import random

  array = []
  for i in range(0,10):
    array.append(2**i + 2.5)
  random.shuffle(array)
  print("array: %s" % array)
  
  algs = medians1D()
  quick_select_result = algs.quick_select(array)
  wirth_result = algs.wirth(array)
  torben_result = algs.torben(array)
  kth_result = algs.kth_smallest(array, 2)
  
  print("quick_select %f, wirth %f, torben %f, kth_smallest(2) %f" %
         (quick_select_result, wirth_result, torben_result, kth_result))

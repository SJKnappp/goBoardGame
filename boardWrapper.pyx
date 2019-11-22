#This is a Cython file and extracts the relevant classes from the C++ header file.

# distutils: language = c++
# distutils: sources = rectangle.cpp

cdef extern from "main.h" namespace "board":
    cdef cppclass piece:
        piece(int, int, int)

cdef class PyPiece:
    cdef Rectangle *thisptr      # hold a C++ instance which we're wrapping
    def __cinit__(self, int x0, int y0, int x1, int y1):
        self.thisptr = new piece(x0, y0, x1, y1)

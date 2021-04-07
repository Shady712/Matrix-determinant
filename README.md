# Matrix-determinant
This code is Gaussian elimination for evaluating the determinant of the provided matrix. This is my first experience of multithreading programming.

# Algorithm
This method of evaluation is much more effective than standard finding of determinant using the definition or recursive implementation. Usage of Gauss elimination does not change the matrix determinant, but makes the process of evaluation of it much easier: the answer is the multiplication of the elements on the main diagonal. Still, the asymptotics of the algorithm is O(n^3) due to the nested for-loops. So, they can be optimised.

# OpenMP
OpenMP is the library for C++ (#include <omp.h>) which allows the usage of pragmas for paralleling the processes. This ability is extremely useful for speeding up the parallel independent calculations, nested loops, etc. Therefore, it is used in this program.

# Optimisation
Pragmas for parallel calculations are used in two parts of the code. Both optimise for-loops. The number of threads is provided with the first command line argument. The worktime of program is tested on rather big input (The size of the matrix is 2000, elements are random). For these tests, graphics are constructed. As a result, you can see that standard one-thread worktime is huge (+-18 secs), while the most positive time is less than 4 secs (with the usage of 11 threads). All the graphics and examples are provided in the Report.pdf file.

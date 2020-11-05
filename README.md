# Approximate Nearest Neighbours LSH
University Assignment: Implement LSH algorithm for d-dimensional images in C++, 
using Lloyd's algorithm and Hypercube & L-Hashtables structures. 
L1 metric: Manhattan.

We can run it like this, from outside of the `src/` folder
`make && ./lsh -d Datasets/dataset -q Datasets/queryset -k 4 -L 1 -o test.txt -N 2 -R 10000`

Or like this to run the cube algorithm
`make && ./cube -d Datasets/dataset -q Datasets/queryset -k 14 -M 10 -probes 5 -o results2.txt -N 5 -R 10000`

Cluster:
`make && ./cluster -i Datasets/dataset -c cluster.conf -o testOutputCluster.txt -complete -m Classic`

**File paths have to be without ""**
_Provided that we have the dataset in the folder ./Datasets/dataset_
_Provided that we have the dataset in the folder ./Datasets/queryset_

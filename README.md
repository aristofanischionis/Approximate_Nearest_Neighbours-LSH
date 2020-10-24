# Search_Cluster_Vectors_CPP
University Assignment: Implement LSH algorithm for d-dimensional vectors in C++

We can run it like this, from outside of the `src/` folder

`make && ./lsh -d Datasets/dataset -q Datasets/queryset -k 4 -L 1 -o results_text.txt -N 2 -R 10000`

Or like this to run the cube algorithm
`make && ./cube -d Datasets/dataset -q Datasets/queryset -k 14 -M 10 -probes 5 -o results2.txt -N 5 -R 10000`

Cluster:
`./cluster -i Datasets/dataset -c cluster.conf -o testOutputCluster.txt -complete -m Classic`

**File paths have to be without ""**
_Provided that we have the dataset in the folder ./Datasets/dataset_

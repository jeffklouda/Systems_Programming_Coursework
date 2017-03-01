Reading 06
==========

**A.** What problem is MapReduce trying to solve?

MapReduce is a model that aims to make data processing and generation more
effictient for large data sets by managing the process on a computer cluster
to allow for parallel processing and greater fault tolerance.

**B.** Describe the three phases of a typical MapReduce workflow.

The three phases of a typical MapReduce workflow are the "map" phase, the
"shuffle" phase, and the "reduce" phase.  In the map phase, "worker" programs
read in data, apply a map function to this data and write the result to 
local disks.  These new "intermediate files" are then redistributed by the
workers based on the output keys produced by the map function.  Finally, 
in the reduce phase, this data is processed per key and the output of that
particular MapReduce operation is produced.

Repository for code to analyze ProtoDUNE quasi-elastic events.

To build the code do 
```
mkdir build
cmake -B build/
cd build
make
```

Dependencies: 
* `cmake v3.15` 
* `ROOT v6.22` 

These were the versions used to build the project, other versions can be tried but there are no guarantees 
it will work.

---
Set the path to the input ROOT file in `config/files.txt`. The TTree format expected is a flattened 
tree and comes from `contrib/ProtoDUNEAnalysisTree_module.cpp`. The module has heavy Larsoft dependencies 
so must be run in in that environment, usually the `dunegpvmXX` machines at Fermilab. This module was
not written by me and is only included as a reference for the tree format.
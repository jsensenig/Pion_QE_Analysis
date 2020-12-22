
---
### Running on Fermilab Grid

When Larsoft and large computing resources are needed the computing 
grid at Fermilab can be used. The `project.py` script can be used for submission
and management of the jobs. An example analysis xml file `my_submission.xml` is 
included in this directory. 

Submit the jobs with xml `my_submission.xml` as such,
```
project.py --xml my_submission.xml --submit
```
To check the results of running the analysis stage,
```
project.py --xml my_submission.xml --stage mergeana --checkana
```
When the analysis step is finished, multiple ROOT files can be merged into a single file using,
```
project.py --xml my_submission.xml --stage mergeana --mergentuple
```

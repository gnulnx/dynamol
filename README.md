# dynamol

This code base has not been maintained in a number of years.  
The code requires QT 3?  I believe to be compiled.
It will also require the Boost C++ libraries which are used to both extend functionality to python as well as embedding the pythogn interpretor for command line scripting.

Yes I really need to bring this project back to life.. and to be fair open sourcing it was the first step in that direction.


Compile Notes:
=============
You must compile with: 
```QMAKE_CXXFLAGS += -stdlib=libc++ -std=c++11```
```QMAKE_LFLAGS += -lc++```

Because the new OSX c++ is libc++ and not libstdc++.
However this failed with lots of errors.  After some digging I found this bug report which
solves the problem

See this issue: https://trac.macports.org/attachment/ticket/44288/issue10910-workaround.txt

I found that from this thread:
https://github.com/BristolTopGroup/AnalysisSoftware/issues/115


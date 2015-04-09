# Dynamol

Dynamol was original a commercial endevour.  The project was abandoned for a number of years (7-8) and has only recently been picked back up.  The goal now is to open source the code.

Dynamol is actually a shell of it's former self though all the original code can still be found in the old_complete directory.  The main Build directory today is just a simple molecular viewer for SDF and PDF files.  It only supports wire frame rendering at this time.

Dyamol was originally fragmented when an effort was made to join forces with PyMol.  Eventually all commercial aspirations of Dynamol faded and the code become very obsolete.  

Today Dynamol is rising from the ashes as an open source project and it's being rebuild from the ground up to have Python be a major component of it.  The original Dynamol did have python both extended and embedded but it was more of an after thought with all the primary code being written in C++.   Today only the computational demanding parts will be written in C++.  Things like reading mol files etc are much easier, and honeslty more robust, to handle on the python side.  Pluse the more code that is developed in python the easier it is to use things like python unit testing.  

So, currently Dynamol isn't all that useable, and honestly the code base is a mess.  :(   Though work has once again resumed, though in a greatly reduced fasion.  If you want to contribute by all means fork the project, make your changes, and submit a PR.

next steps are to get Stick model rendering working.
The get surface and ribbon code working again.
After that Energy minimization and Dynamics Code will be integrated
After that perhaps the SEAL molecular dynamics alighment code...  




Compile Notes (OSX):
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


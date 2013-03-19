CVRA NIOS 2 Code & libraries
============================

To build on Linux (should work on any UNIX, but not tested) :

    cd /path/to/repos/
    mkdir build
    cd build && cmake ..
    make


To build just for a single robot :

    make debra
    make nastya


Contributing
============
If you are from CVRA, ask Antoine to give you commiter access. If you come from an external club
(omg a contributor, welcome!), please open a pull request.

In both cases, it is _really important_ that you configure your Mercurial client to have the right user setting.
We want your user settings to look like this : `FirstName LastName <email@adress.com>`. The `<` and the `>` must
be in the username. This is required by Bitbucket to properly match your account to your commits.

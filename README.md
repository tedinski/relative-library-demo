
This repo is a quick demonstration of how to look up the location of a shared library in Linux.
For example, to be able to load resources from a path in a location relative to that library, rather than using a hardcoded path from root (e.g. `/usr/share/mylib/data`).

## Running the demo

```
make clean all
```

Should build the demo and run it as well.

You should see output like the following:

On OS X:

```
anso: /Users/tedinski/repos/relative-library-demo/libanso.so
me: /Users/tedinski/repos/relative-library-demo/./main
libc: /usr/lib/system/libsystem_c.dylib
```


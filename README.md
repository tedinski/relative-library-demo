
This repo is a quick demonstration of how to figure out where a shared library was loaded from.
This code has been tested on Linux and OS X. (From documentation, I think it will work on Solaris, and the BSDs, but I haven't tested and don't have example output below.)

The idea is to be able to load resources from a path in a location relative to that library, rather than using a hardcoded path from root (e.g. `/usr/share/mylib/data`).
Using this technique, libraries can be installed anywhere instead of requiring a fixed, hard-coded `--prefix`.

## Running the demo

```
make clean all
```

Should build the demo and run it as well.

The final lines of the build should look like this:

On Linux:

```
anso: /home/tedinski/repos/relative-library-demo/libanso.so
me: ./main
libc: /lib/x86_64-linux-gnu/libc.so.6
```

On OS X:

```
anso: /Users/tedinski/repos/relative-library-demo/libanso.so
me: /Users/tedinski/repos/relative-library-demo/./main
libc: /usr/lib/system/libsystem_c.dylib
```

## Explanation

It's not too hard to understand, there's less than 50 lines of code.

In `anso.c` ("an `so`") we see the trick: we use `dladdr` (from `dlfcn.h`, see `man dladdr`, and adding `-ldl` in the makefile) to look up a symbol, and it gives us back information about the shared object it was loaded from.
There's almost nothing to this code, [take a look at that file](anso.c).
Basically, the dynamic linker had to find this file somehow, and we're just asking it to tell us.
Easy peasey.

The complexity shows up only in what we do around this, and what different platforms report back to us.
One of the caveats of `dladdr` is that it looks up the address of the thing you pass in _exactly_, and unless you've compiled with `-fpic` the thing you pass in might not be the function itself, but instead an entry in a jump table that gets populated by the linker.
If you make this mistake, you'll just potentially see an unexpected result (try removing the `CFLAGS` line from the makefile and see for yourself!)

My purpose for this demo is to show this information is readily available and can be used to search for files in relative paths from where a package is installed.
As a result, I also build the executable using `rpath` so it searches next to the executable for shared libraries to load (using `$ORIGIN`).

As we can see from the output, the linux dynamic linker is unhelpful in telling us the full path to the executable, but at least it is helpful when `$ORIGIN` is involved.
This makes it fit for the purpose of letting _libraries_ find their files.
(N.B. if using `LD_LIBRARY_PATH` with a relative path instead of `-rpath $ORIGIN`, you will once again get that relative path echoed back at you, much as linux does for the executable itself.)

## License

Call it public domain, too small to be anything but fair use, MIT, or Apache 2, whichever you prefer.


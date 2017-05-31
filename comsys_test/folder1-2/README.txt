:: COMMAND ::
gcc -shared -Wl,-soname,sort -o sort.so -fPIC sort.c
python sort.py

:: RESULT ::
Elapsed time:  12.6031241417

g++ -o dtest dtest.cpp dprintf.cpp -std=c++0x
ulimit -c unlimited
rm -f core
./dtest
echo
echo 'decoding dprintf.raw'
echo
gdb -q dtest -ex 'py execfile("dprintf.py")' -ex 'dprintf dprintf.raw' -ex q
echo
echo 'decoding core'
echo
gdb -q dtest core -ex 'py execfile("dprintf.py")' -ex 'dprintf' -ex q

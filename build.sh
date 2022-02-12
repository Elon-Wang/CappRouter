gcc -O2 -c graphics.c
c++ -O2 -c draw.cpp
c++ -O2 -c Node.cpp
c++ -O2 -c MyQueue.cpp
c++ -O2 -c MinHeap.cpp
c++ -O2 -c -Wno-unused-result Circuit.cpp
c++ -O2 -c -Wno-unused-result main.cpp
c++ -O2 Node.o MinHeap.o MyQueue.o graphics.o draw.o Circuit.o main.o -o CappRouter -L/usr/openWin/lib -lX11 -lm
echo "finish compiling, try CappRouter now"
echo ""
echo "Usage: ./CappRouter <benchmark-name> --algo=maze,astar [--detail <1-3>]"
echo "example: ./CappRouter misty --algo=maze --detail 2"
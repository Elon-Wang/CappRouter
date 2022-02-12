#include <bits/stdc++.h>
#include "Node.h"
#include "draw.h"
#include "Circuit.h"
#include <sys/time.h>
using namespace std;

int main(int argc, char* argv[]){

    if (argc != 3 && argc != 5 ) {
        printf("Usage: %s <benchmark-name> --algo=maze,astar [--detail <1-3>]\n"
            "Example: %s misty --algo=maze --detail 3\n", argv[0], argv[0]);
        return 0;
    }

    // sscanf(argv[3],"%d",&debug_level);
    // char testBench[15];
    // sscanf(argv[1],"%c",testBench);
    char prefix[15] ="../benchmarks/";
	char postfix[10]   =".infile";
	char fileName[50];
	strcpy(fileName,prefix);
	strcat(fileName,argv[1]);
	strcat(fileName,postfix);

    int algorithm;
    const char* algo_type = strstr(argv[2],"=");
    algo_type++; 
    if(strcmp(algo_type, "maze") == 0) {
        algorithm = 0;
    } else if (strcmp(algo_type, "astar") == 0) {
        algorithm = 1;
    } else {
        printf("invalid algorithm type: %s\n", algo_type);
        assert(false);
    }

    int detail_level = 2;
    if (argc ==5 && strcmp(argv[3], "--detail") == 0) {
        sscanf(argv[4],"%d",&detail_level);  
        assert(detail_level >=1 && detail_level <= 3);
    }


    Circuit cc(algorithm, detail_level);
    // Circuit cc;

    // readin the benchmarks
    if (cc.readFile(fileName) == false) {
        printf("Cannot open file: %s\n",fileName); 
        return 0;
    }
    
    if (detail_level >=2) {
        // show the original probelm graph
        cc.initGraph();
        cc.updateGraph();
    }


    printf("Begin to Route.\n");
    struct timeval start, end;
    gettimeofday(&start,NULL);
    
    // Performing the algorithm
    // and update the graph
    cc.router();
    
    gettimeofday(&end,NULL);
    if (detail_level ==1) {
        double total_time = (double)((end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)); // get the run time by microsecond
        printf("time: %lf us\n", total_time);
    }

    freopen("/dev/tty","r",stdin);
    printf("program exit successfully\n");
    return 0;
}
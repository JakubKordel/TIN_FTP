#include "ErrorDetector.h"


int ErrorDetector::CheckNrOfArgs(int nr_args){
    return arguments.size() == nr_args;
}
//
// Created by John Uiterwyk on 5/31/15.
//

#include "RunResult.h"
#include <sstream>

std::string RunResult::toString() {
 std::string result;

 std::ostringstream fitness;
 fitness << this->bestProgramFitness;
 result.append("Fitness: "+fitness.str()+" ");
 result.append(this->bestProgramString);

 return result;
}

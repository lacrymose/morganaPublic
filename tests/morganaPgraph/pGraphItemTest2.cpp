/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
This file is part of Morgana.
Author: Andrea Villa, andrea.villa81@fastwebnet.it

Morgana is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Morgana is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Morgana. If not, see <http://www.gnu.org/licenses/>.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#include <cmath>
#include <iostream>

#include <boost/mpi.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>

#include "pGraphItem.h"
#include "traitsMpiOptimization.hpp"

// mpirun -np 2 ./bin/morgana

using namespace std;
using namespace boost::mpi;


/*! Run with two processors */
int main(int argc, char *argv[])
{
  environment  env(argc,argv);
  communicator world;
  
  pGraphItem recP;
  
  assert(world.size() == 2);
  
  if(world.rank() == 0)
  {
    pGraphItem P(3);
    P.setCid(1,3);
    P.setCid(2,4);
    P.setCid(3,5);
    
    world.send(1,0,P);
    world.recv(1,1,recP);
  }
  else
  {
    pGraphItem P(2);
    P.setCid(1,6);
    P.setCid(2,7);
    
    world.recv(0,0,recP);
    world.send(0,1,P);
  }
  
  
  world.barrier();
  if(world.rank() == 0)
  {
    cout << "Process: " << world.rank() << " Size: " << world.size() << endl;
    cout << recP << endl;
  }
  
  world.barrier();
  if(world.rank() == 1)
  {
    cout << "Process: " << world.rank() << " Size: " << world.size() << endl;
    cout << recP << endl;
  }
}


/* Pid 0
Process: 0 Size: 2
Num Connected  : 2
Connected Id's : 6 7
*/


/* Pid 1
Process: 1 Size: 2
Num Connected  : 3
Connected Id's : 3 4 5
*/


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
#include <boost/mpi/timer.hpp>

#include "typesInterface.hpp"

#include "pMap.hpp"
#include "pMapItemShare.h"
#include "pMpiOptimization.hpp"
#include "pMapComm.hpp"
#include "pMapGlobalManip.h"
#include "pVect.hpp"
#include "pVectGlobalManip.hpp"

using namespace Teuchos;



//! Run at least with two processors
//! PERFORMANCE--PERFORMANCE--PERFORMANCE--PERFORMANCE
int main(int argc, char *argv[])
{ 
  //Comunication stuff
  environment  env(argc,argv);
  RCP<communicator> world(new communicator);
  
  timer clock;
  
  //Allocations
  typedef pMap<pMapItemShare>          OBJ;
  typedef pMap<pMapItemSendRecv>       SENDRECV;
  typedef pVect<point3d,pMapItemShare> PVECT;
  
  UInt size = world->size();
  UInt pid  = world->rank();
  
  assert(size >= 2);
  
  UInt localSize   = 1000000 / size;           //Change me
  UInt sharingSize = localSize / 10;
  UInt offset;
  point3d P;
  
  pMapItemShare item;
  PVECT sVector;
  
  item.setPid(world->rank());
  
  assert(sharingSize < localSize);
  assert(localSize > (size * sharingSize));
  
  if(world->rank() < int(size-1))
  {
    offset = localSize * pid;
    
    for(UInt i=1; i<=localSize; ++i)
    { 
      item.setLid(i); item.setGid(offset + i);  item.setOwned(true); item.setShared(false);
      P.setX(i);
      
      sVector.push_back(item,P);
    }
    
    for(UInt i=1; i<=sharingSize; ++i)
    { 
      sVector.getMapL(i).setOwned(false); sVector.getMapL(i).setShared(true);
    }
  }
  else
  {
    UInt k=1;
    
    for(UInt Pid=0; Pid < (size-1); Pid++)
    {
      offset = localSize * Pid;
      
      for(UInt i=1; i <= sharingSize; ++i)
      {
	item.setLid(k); item.setGid(offset + i);  item.setOwned(true); item.setShared(true);
	P.setX(i);
	
	sVector.push_back(item,P);
	++k;
      }
    }
  }
  sVector.updateFinder();
  
  
  //Vector checking
  pVectGlobalManip<point3d,pMapItemShare> vectManipulator(world);
  cout << "VectorCheking: " << vectManipulator.check(sVector) << endl;
  
  //Map creation
  SENDRECV mapSend;
  SENDRECV mapRecv;
  
  pMapGlobalManip<pMapItemShare> mapManipulator(world);
  
  clock.restart();
  mapManipulator.createSendRecvMap(sVector.getMapRef(),mapSend,mapRecv);
  cout << "MapCreation - Time: " << clock.elapsed() << endl;
  
  
  //Map checking
  clock.restart();
  pMapGlobalManip<pMapItemSendRecv> checker(world);
  cout << "MapChecking: " << checker.check(mapSend,mapRecv) << endl; 
  cout << "MapChecking - Time: " << clock.elapsed() << endl;
  
  //Data updating
  clock.restart();
  vectManipulator.updateData(sVector,mapSend,mapRecv);
  cout << "VectorUpdating - Time: " << clock.elapsed() << endl;
}

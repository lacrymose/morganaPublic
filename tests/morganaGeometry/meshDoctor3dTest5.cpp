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

#include "typesInterface.hpp"

#include "pMapItem.h"
#include "pMapItemShare.h"

#include "pGraph.hpp"

#include "geoShapes.h"
#include "mesh3d.hpp"
#include "meshDoctor3d.hpp"
#include "printMesh3dHDF5.hpp"

// mpirun -np 2 ./bin/morgana

using namespace std;
using namespace boost::mpi;

int main(int argc, char *argv[])
{
  //Typedefs---------------------------------------------------------------------------------------
  typedef geoElement<linearTetra> GEOELEMENT;
  typedef pMapItemShare           ELMAP;
  typedef pMapItemShare           NODEMAP;
  
  typedef mesh3d<linearTetra,ELMAP,NODEMAP>       MESH3D;
  typedef connect3d<linearTetra,ELMAP,NODEMAP>    CONNECT3D;
  typedef meshDoctor3d<linearTetra,ELMAP,NODEMAP> DOCTOR3D;
  typedef printMesh3dHDF5<linearTetra,ELMAP>      PRINTER3D;
  
  //Alloc------------------------------------------------------------------------------------------
  environment  env(argc,argv);
  communicator world;
  
  assert(world.size() == 2);
  Teuchos::RCP<MESH3D> grid3d(new MESH3D);
  
  //Define grid------------------------------------------------------------------------------------
  if(world.rank() == 0)
  {
    //Nodes
    pVect<point3d,NODEMAP> nodes;
    
    nodes.reserve(5);
    nodes.push_back(point3d(0.0, 0.0, 0.0),NODEMAP(1,1));
    nodes.push_back(point3d(1.0, 0.0, 0.0),NODEMAP(2,2));
    nodes.push_back(point3d(1.0, 1.0, 0.0),NODEMAP(3,3));
    nodes.push_back(point3d(0.0, 1.0, 0.0),NODEMAP(4,4));
    nodes.push_back(point3d(0.5, 0.5, 1.0),NODEMAP(5,5));
    nodes.updateFinder();
    
    //Elements
    GEOELEMENT tet(true);
    pGraph<GEOELEMENT,ELMAP,NODEMAP> elList;
    
    elList.reserve(2);
    
    tet.setGeoId(1); tet(1) = 1; tet(2) = 2; tet(3) = 3; tet(4) = 5;
    elList.push_back(tet, ELMAP(1,1,true,true));
    tet.setGeoId(1); tet(1) = 1; tet(2) = 3; tet(3) = 4; tet(4) = 5;
    elList.push_back(tet, ELMAP(2,2,true,false));
    
    //The grid3d
    grid3d->setNodes(nodes);
    grid3d->setElements(elList);
  }
  else
  {
    //Nodes
    pVect<point3d,NODEMAP> nodes;
    
    nodes.reserve(5);
    nodes.push_back(point3d(0.0, 0.0, 0.0),NODEMAP(1,1));
    nodes.push_back(point3d(1.0, 0.0, 0.0),NODEMAP(2,2));
    nodes.push_back(point3d(1.0, 1.0, 0.0),NODEMAP(3,3));
    nodes.push_back(point3d(0.0, 1.0, 0.0),NODEMAP(4,4));
    nodes.push_back(point3d(0.5, 0.5, 1.0),NODEMAP(5,5));
    nodes.updateFinder();
    
    //Elements
    GEOELEMENT tet(true);
    pGraph<GEOELEMENT,ELMAP,NODEMAP> elList;
    
    elList.reserve(2);
    
    tet.setGeoId(2); tet(1) = 1; tet(2) = 2; tet(3) = 3; tet(4) = 5;
    elList.push_back(tet, ELMAP(1,1,true,false));
    tet.setGeoId(2); tet(1) = 1; tet(2) = 3; tet(3) = 4; tet(4) = 5;
    elList.push_back(tet, ELMAP(2,2,true,true));
    
    //The grid3d
    grid3d->setNodes(nodes);
    grid3d->setElements(elList);
  }
  
  //GeoIds-----------------------------------------------------------------------------------------
  Teuchos::RCP<DOCTOR3D> doctor(new DOCTOR3D(world));
  std::set<UInt> geoSet = doctor->getGeoIds(grid3d);
  
  typedef set<UInt>::iterator ITERATOR;
  
  if(world.rank() == 0)
  {
    for(ITERATOR iter = geoSet.begin(); iter != geoSet.end(); iter++)
    { cout << "id " << *iter << endl; }
  }
}

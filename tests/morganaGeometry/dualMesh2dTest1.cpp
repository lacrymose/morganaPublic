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

#include "pMapItem.h"
#include "pMapItemShare.h"

#include "geoShapes.h"
#include "meshInit2d.hpp"

#include "dualMesh2d.hpp"
#include "printMesh.hpp"

using namespace std;
using namespace boost::mpi;
using namespace Teuchos;


int main(int argc, char *argv[])
{
  environment  env(argc,argv);
  communicator world;
  
  typedef linearTriangle GEOSHAPE2D;
  typedef linearLine     GEOSHAPE1D;
  typedef pMapItemShare  ELMAP;
  typedef pMapItemShare  NODEMAP;
  typedef mesh2d<GEOSHAPE2D,ELMAP,NODEMAP>  MESH2D;
  typedef mesh1d<GEOSHAPE1D,ELMAP,NODEMAP>  MESH1D;
  
  
  string meshFile = "./tests/morganaMeshes/mignon2dC.msh";
  //string meshFile = "./geometries/cubes3d/testCubeA.msh";
  
  meshInit2d<GEOSHAPE2D,ELMAP,NODEMAP> init(world);
  init.gmMesh_to_stdA(meshFile);
  
  
  //Dual mesh
  dualMesh2d<GEOSHAPE2D,ELMAP,NODEMAP> dualGrid(world);
  dualGrid.setMesh2d(init.getGrid2d());
  dualGrid.setConnect2d(init.getConnectGrid2d());
  
  dualGrid.buildDualMesh();
  dualGrid.buildFiniteVolumeData();
  
  //Extract the dual meshes
  MESH2D dualGrid2d = dualGrid.getSubCellMesh();
  MESH1D dualGrid1d = dualGrid.getInterfaceMesh();
  
  
  //Local printing 3d
  string local2d = "localMesh2d_" + num2str(world.rank()) + "pid.inp";
  UInt pid       = world.rank();
  
  printMesh<GEOSHAPE2D,ELMAP,NODEMAP> localPrinter2d;
  localPrinter2d.paraviewLocal(local2d, pid, dualGrid2d);
  
  
  //Local printing 1d
  string local1d = "localMesh1d_" + num2str(world.rank()) + "pid.inp";
  
  printMesh<GEOSHAPE1D,ELMAP,NODEMAP> localPrinter1d;
  localPrinter1d.paraviewLocal(local1d, pid, dualGrid1d);
}

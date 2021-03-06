/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
This file is part of Morgana.
Author: Andrea Villa, andrea.villa81@fastwebnet.it

Morgana is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Morgana is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Morgana. If not, see <http://www.gnu.org/licenses/>.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#include "time.h"
#include <cmath>
#include <iostream>

#include "geoMapSupport3d.hpp"

int main(int argc, char *argv[])
{
  //Geo support tor tretra
  geoMapSupport3d<linearHexa> supporter;
 
  sVect<point3d> points(8); 
  
  points(1) = point3d(1.0,1.0,1.0);
  points(2) = point3d(2.0,1.0,1.0);
  points(3) = point3d(2.0,2.0,1.0);
  points(4) = point3d(1.0,2.0,1.0);
  
  points(5) = point3d(1.0,1.0,2.0);
  points(6) = point3d(2.0,1.0,2.0);
  points(7) = point3d(2.0,2.0,2.0);
  points(8) = point3d(1.0,2.0,2.0);
  
  UInt face = 6;
  point3d Ys(1.0/3.0, 1.0/3.0, 1.0/3.0);
  
  supporter.setPoints(points);
  
  cout << "N: " << supporter.normal(Ys,face) << endl;
}

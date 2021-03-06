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

#include "pMap.hpp"
#include "pMapManip.hpp"

using namespace Teuchos;


/*! Serial run with one processor */
int main(int argc, char *argv[])
{
  typedef pMap<pMapItem> OBJ;
  
  pMapItem  item;
  RCP<OBJ>  mappa(new OBJ);
  
  item.setLid(1);
  item.setGid(5);
  mappa->push_back(item);
  
  item.setLid(2);
  item.setGid(6);
  mappa->push_back(item);
  
  item.setLid(3);
  item.setGid(8);
  mappa->push_back(item);
  
  cout << *mappa << endl;
  
  //Map manipulator
  pMapManip<pMapItem> manip(mappa);
  manip.buildFinder();
  
  item.setLid(0); item.setGid(8);
  cout << "is? " << manip.isItem(item) << endl;
  cout << "lid: " << manip.getLidItem(item) << endl;
  
  item.setLid(0); item.setGid(3);
  cout << "is? " << manip.isItem(item) << endl;
}

/*
pid: 0 lid: 1 gid: 5
pid: 0 lid: 2 gid: 6
pid: 0 lid: 3 gid: 8

is? 1
lid: 3
is? 0
*/

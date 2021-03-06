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

#include "polyDynamicCard.h"
#include "polyDynamic.h"



int main(int argc, char *argv[])
{
  point3d X(1.0,1.0,1.0);
  
  polyDynamicCard card;
  card.addSlot(1,0,0,1.0);
  card.addSlot(0,1,0,1.0);
  card.addSlot(0,0,1,1.0);
  
  polyDynamic polyVal;
  polyVal.setPolyDynamicCard(card);
  cout << "val: " << polyVal.evaluate(X) << endl;
  cout << "gradX: " << polyVal.evaluateGradientX(X) << endl;
  cout << "gradY: " << polyVal.evaluateGradientY(X) << endl;
  cout << "gradZ: " << polyVal.evaluateGradientZ(X) << endl;
}

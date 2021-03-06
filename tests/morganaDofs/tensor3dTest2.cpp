/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
This file is part of Morgana.
Author: Andrea Villa, andrea.villa81@fastwebnet.it

Morgana is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Morgana is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Morgana. If not, see <http://www.gnu.org/licenses/>.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#include "typesInterface.hpp"
#include <cmath>

using namespace std;

int main(int argc, char *argv[])
{
  //Istanziamento tensori
  tensor3d T1, T2;
  
  T1.setIJ(1,1,1.0); T1.setIJ(1,2,2.0); T1.setIJ(1,3,0.5);
  T1.setIJ(2,1,1.5); T1.setIJ(2,2,0.5); T1.setIJ(2,3,0.5);
  T1.setIJ(3,1,1.5); T1.setIJ(3,2,2.0); T1.setIJ(3,3,0.0);
  
  T2.setIJ(1,1,3.0);  T2.setIJ(1,2,1.0);  T2.setIJ(1,3,-2.0);
  T2.setIJ(2,1,0.5);  T2.setIJ(2,2,-0.5); T2.setIJ(2,3,1.0);
  T2.setIJ(3,1,-3.0); T2.setIJ(3,2,0.5);  T2.setIJ(3,3,-1.5);
  
  
  tensor3d T3(T1);
  tensor3d T4, F;
  tensor3d I, Z;
  
  I.setIJ(1,1,1.0);
  I.setIJ(2,2,1.0); 
  I.setIJ(3,3,1.0); 
  
  point3d P, Y, PU;
  P.setX(1.0); P.setY(2.0); P.setZ(3.0);
  
  //Test 1 - Algebra
  cout << "Test 1" << endl;
  F.setIJ(1,1,0.5);  F.setIJ(1,2,3.5);  F.setIJ(1,3,2.0);
  F.setIJ(2,1,2.75); F.setIJ(2,2,1.25); F.setIJ(2,3,0.5);
  F.setIJ(3,1,4.5);  F.setIJ(3,2,3.75); F.setIJ(3,3,0.75);
  
  T4 = T1 * 2.0 - T2 / 2.0 - F;
  bool test1 = (T4.getFrobenius() < 1e-14);
  
  
  //Test 2 - Algebra
  cout << "Test 2" << endl;
  F.setIJ(1,1,3.5);  F.setIJ(1,2,2.25); F.setIJ(1,3,-0.25);
  F.setIJ(2,1,4.75); F.setIJ(2,2,2.00); F.setIJ(2,3,-2.75);
  F.setIJ(3,1,7.00); F.setIJ(3,2,2.50); F.setIJ(3,3,-1.00);
  
  T4 = T1.matrixProduct(T2) + T1 - F;
  bool test2 = (T4.getFrobenius() < 1e-14);
  
  
  //Test 3 - Algebra
  cout << "Test 3" << endl;
  bool test3 = (T1 < T2) && !(T2 < T1) && !(T3 < T1) && !(T1 != T3) && (T1 != T2);
  
  
  //Test 4 - Cayley Hamilton Theorem test	
  cout << "Test 4" << endl;
  tensor3d temp = T1.matrixProduct(T1);
  T4 = temp.matrixProduct(T1) - temp * T1.getFirstInvariant() + T1 * T1.getSecondInvariant() - I * T1.getThirdInvariant();
  bool test4 = !(T4 != Z);
  
  
  //Test 5
  cout << "Test 5" << endl;
  cout << "Circa 3.7749: " << T1.getFrobenius() << endl;
  
  
  //Test 6
  cout << "Test 6" << endl;
  Y = T1.firstIndexSaturation(P);
  PU.setX(8.5); PU.setY(9.0); PU.setZ(1.5);
  bool test6 = !(Y != PU);
  
  
  //Test 7
  cout << "Test 7" << endl;
  Y = T1.secondIndexSaturation(P);
  PU.setX(6.5); PU.setY(4.0); PU.setZ(5.5);
  bool test7 = !(Y != PU);
  
  
  //Test 8
  cout << "Test 8" << endl;
  T3.computeInverse();
  T4 = I - T1.matrixProduct(T3);	
  bool test8 = (T4.getFrobenius() < 1e-14);
  
  
  //Test 9
  cout << "Test 9" << endl;
  T3 = T1;
  T3.transpose();
  T3.transpose();
  bool test9 = !(T1 != T3);
  
  
  cout << test1 << endl;
  cout << test2 << endl;
  cout << test3 << endl;
  cout << test4 << endl;
  cout << test6 << endl;
  cout << test7 << endl;
  cout << test8 << endl;
  cout << test9 << endl;
}

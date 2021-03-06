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

#include "typesInterface.hpp"
#include "traitsMultiply.h"


int main(int argc, char *argv[])
{
  //Variables instantiation
  Real r = 2.0, ro;
  point2d P2(1.0,2.0), P2O;
  point3d P3(1.0,2.0,1.0), P3O;
  
  tensor2d T2, T2O;
  T2.setIJ(1,1,1.0); T2.setIJ(1,2,2.0);
  T2.setIJ(2,1,2.0); T2.setIJ(2,2,3.0);
  
  tensor3d T3, T3O;
  T3.setIJ(1,1,1.0); T3.setIJ(1,2,2.0); T3.setIJ(1,3,1.0);
  T3.setIJ(2,1,2.0); T3.setIJ(2,2,3.0); T3.setIJ(2,3,2.0);
  T3.setIJ(3,1,3.0); T3.setIJ(3,2,1.0); T3.setIJ(3,3,3.0);
  
  stateVector V(2), VO(2);
  V(1) = 1.0;
  V(2) = 2.0;
  
  stateMatrix M(2,2), MO(2,2);
  M(1,1) = 1.0; M(1,2) = 2.0;
  M(2,1) = 3.0; M(2,2) = 1.0;
  
  typedef staticVector<2> STATICVECTOR;
  STATICVECTOR S, SO;
  S(1) = 1.0;
  S(2) = 2.0;
  
  //Traits instantiation
  traitsMultiply<Real,Real>         realToReal;
  traitsMultiply<Real,point2d>      realToPoint2d;
  traitsMultiply<Real,point3d>      realToPoint3d;
  traitsMultiply<Real,tensor2d>     realToTensor2d;
  traitsMultiply<Real,tensor3d>     realToTensor3d;
  traitsMultiply<Real,stateVector>  realToStateVector;
  traitsMultiply<Real,stateMatrix>  realToStateMatrix;
  traitsMultiply<Real,STATICVECTOR> realToStaticVector;
  traitsMultiply<point2d,Real>      point2dToReal;
  traitsMultiply<point2d,point2d>   point2dToPoint2d;
  traitsMultiply<point3d,Real>      point3dToReal;
  traitsMultiply<point3d,point3d>   point3dToPoint3d;
  traitsMultiply<tensor2d,Real>     tensor2dToReal;
  traitsMultiply<tensor3d,Real>     tensor3dToReal;
  traitsMultiply<stateVector,Real>  stateVectorToReal;
  traitsMultiply<stateMatrix,Real>  stateMatrixToReal;
  traitsMultiply<STATICVECTOR,Real> staticVectorToReal;
  
  
  //Direct product
  cout << "%%% Direct product test %%%" << endl;
  
  ro = realToReal.multiply(r,r);
  cout << "Real-Real: " << ro << endl;
  
  P2O = realToPoint2d.multiply(r,P2);
  cout << "Real-Point2d: " << P2O << endl;
  
  P3O = realToPoint3d.multiply(r,P3);
  cout << "Real-Point3d: " << P3O << endl;
  
  T2O = realToTensor2d.multiply(r,T2);
  cout << "Real-Tensor2d: " << T2O << endl;
  
  T3O = realToTensor3d.multiply(r,T3);
  cout << "Real-Tensor3d: " << T3O << endl;
  
  VO = realToStateVector.multiply(r,V);
  cout << "Real-StateVector: " << VO << endl;
  
  MO = realToStateMatrix.multiply(r,M);
  cout << "Real-StateMatrix: " << MO << endl;
  
  SO = realToStaticVector.multiply(r,S);
  cout << "Real-StaticVector: " << SO << endl;
  
  P2O = point2dToReal.multiply(P2,r);
  cout << "Point2d-Real: " << P2O << endl;
  
  T2O = point2dToPoint2d.multiply(P2,P2);
  cout << "Point2d-Point2d: " << T2O << endl;
  
  P3O = point3dToReal.multiply(P3,r);
  cout << "Point3d-Real: " << P3O << endl;
  
  T3O = point3dToPoint3d.multiply(P3,P3);
  cout << "Point3d-Point3d: " << T3O << endl;
  
  T2O = tensor2dToReal.multiply(T2,r);
  cout << "Tensor2d-Real: " << T2O << endl;
  
  T3O = tensor3dToReal.multiply(T3,r);
  cout << "Tensor3d-Real: " << T3O << endl;
  
  VO = stateVectorToReal.multiply(V,r);
  cout << "StateVector-Real: " << VO << endl;
  
  MO = stateMatrixToReal.multiply(M,r);
  cout << "StateMatrix-Real: " << MO << endl;
  
  SO = staticVectorToReal.multiply(S,r);
  cout << "StaticVector-Real: " << SO << endl;
  cout << endl;
  
  
  cout << "%%% Cross product test %%%" << endl;
  point2d P2A(1.0,0.0), P2B(0.0,1.0);
  P3O = point2dToPoint2d.crossProductA(P2A,P2B);
  cout << "Cross P2: " << P3O << endl;
  
  point3d P3A(1.0,0.0,0.0), P3B(0.0,1.0,0.0);
  P3O = point3dToPoint3d.crossProductA(P3A,P3B);
  cout << "Cross P3: " << P3O << endl;
  cout << endl;
  
  
  cout << "%%% Scalar product test %%%" << endl;
  ro = realToReal.scalarProductA(r,r);
  cout << "Scalar - Real: " << ro << endl;
  
  ro = point2dToPoint2d.scalarProductA(P2,P2);
  cout << "Scalar - Point2d: " << ro << endl;
  
  ro = point3dToPoint3d.scalarProductA(P3,P3);
  cout << "Scalar - Point3d: " << ro << endl;
}

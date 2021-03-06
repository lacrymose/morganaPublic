/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
This file is part of Morgana.
Author: Andrea Villa, andrea.villa81@fastwebnet.it

Morgana is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Morgana is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Morgana. If not, see <http://www.gnu.org/licenses/>.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#include "glRule.h"

glRule::
glRule(const UInt & NN)
{
  N = NN;
}

void
glRule::
compute(sVect<Real> & xgl, sVect<Real> & wgl, const Real & toll) const
{
  if(N >= 1)
  {
    //Allocations
    UInt N1 = N + 1;
    Real pi = std::atan(1.0) * 4.0;
    
    //Initialization with the Chebyshev nodes
    stateVector X(N1), Xold(N1), Xdiff(N1);
    stateMatrix P(N1,N1);
    
    for(UInt i=1; i <= N1; ++i)
    {
      X(i) = cos( Real(i-1) * pi / Real(N) );
    }
    
    //Compute
    Xdiff = X - Xold;
    
    while(Xdiff.norm1() >= toll)
    {
      Xold = X;
      
      for(UInt i=1; i <= N1; ++i)
      {
	P(i,1) = 1;
	P(i,2) = X(i);
      }
      
      for(UInt k=2; k <= N; ++k)
      {
	for(UInt i=1; i <= N1; ++i)
	{
	  P(i,k+1) = ( (2*k-1) * X(i) * P(i,k) - (k-1) * P(i,k-1) )/k;
	}
      }
      
      for(UInt i=1; i <= N1; ++i)
      {
	X(i) = Xold(i) - ( X(i) * P(i,N1) - P(i,N) ) / ( N1*P(i,N1) );
      }
      
      Xdiff = X - Xold;
    }
    
    //Output
    xgl.resize(N1);
    wgl.resize(N1);
    
    for(UInt i=1; i <= N1; ++i)
    {
      xgl(N1 -i +1) = (X(i) + 1.0) / 2.0;
      wgl(N1 -i +1) = 1.0 / (N * N1 * pow(P(i,N1),2.0) );
    }
  }
  else
  {
    xgl.resize(1);
    wgl.resize(1);
    
    xgl(1) = 0.5;
    wgl(1) = 1.0;
  }
}
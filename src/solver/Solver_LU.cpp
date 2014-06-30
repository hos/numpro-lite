/*
NumPro: Finite Elements for Research and Teaching
Copyright (C) 2013 Institut fuer Baustatik und Baudynamik
                   Universitaet Stuttgart
                   Malte von Scheven

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Contact:
Dr.-Ing. Malte von Scheven
Institut fuer Baustatik und Baudynamik
Universitaet Stuttgart
Paffenwaldring 7
70550 Stuttgart, Germany

http://www.ibb.uni-stuttgart.de/
mvs@ibb.uni-stuttgart.de

 */



#include "Main.h"
#include "Solver.h"


/** Loesung des LGS a*u=f mit LU-Faktorisierung (LU)
 *
 */
void Solver_LU::solve(
    Matrix&                       _a,                  // Matrix des LGS (i)
    Array1D<double>&              _u,                  // Loesungsvektor (o)
    Array1D<double>&              _f                   // rechte Seite Vektor (i)
)
{

  double sum;

  int n= _a.get_size();
  lu.resize(n,n);
  swap.resize(n);

  for (int i=0;i<n;i++)
    for (int j=0; j<n; j++)
      lu[i][j] = _a.get_entry(i,j);

  for (int i=0;i<n;i++)
    swap[i] = i;

  lu.print("A");


  for (int i=0; i<n; i++) // looping all pivot elements
  {

    // Pivoting (swapping rows)
    double big  = 0.0;
    int    imax = -1;
    for (int ll=i+1; ll<n; ll++) // loop rows below pivot
    {
      if ( fabs(lu[ll][i]) > big )
      {
        big = fabs(lu[ll][i]);
        imax = ll;
      }
    }

    // swap rows i and imax
    if ( imax != -1 && i != imax )
    {
      cout << "Swapping " << i << " and " << imax << endl;
      for (int k=0;k<n;k++)
      {
        double temp = lu[imax][k];
        lu[imax][k] = lu[i][k];
        lu[i][k]    = temp;
      }

      int tempi    = swap[imax];
      swap[imax]  = swap[i];
      swap[i]     = tempi;

    }


    // check the pivot element
    if ( fabs(lu[i][i]) < 1e-12 )
    {
      cout << "LU: singular matrix!" << endl;
      exit(1);
    }

    for (int ll=i+1; ll<n; ll++) // loop rows below pivot
    {
      lu[ll][i] /= lu[i][i];
      for (int k=i+1; k<n; k++)
        lu[ll][k] -= lu[ll][i]*lu[i][k];
    }
  }
  lu.print("LU:");
  swap.print_int("Swap:");
  //_f.print("F:");


  // forward
  for (int i=0; i<n; i++)
  {
    sum = _f[ swap[i] ];
    //sum = _f[i];
    for (int j=0; j<i; j++)
      sum -= lu[i][j] * _u[j];
    _u[i] = sum;
  }


  // backward
  for (int i=n-1; i>=0; i--)
  {
    sum = _u[i];
    for (int j=i+1; j<n; j++)
      sum -= lu[i][j] * _u[j];
    _u[i] = sum/lu[i][i];
  }

  //_u.print("u:");

  return;
}



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
#include <stdexcept>

/** Loesung des LGS a*u=f mit dem konjugierten Gradienten-Verfahren (CG)
 *
 */
void Solver_GS::solve(
    Matrix&                       _a,                  // Matrix des LGS (i)
    Array1D<double>&              _u,                  // Loesungsvektor (o)
    Array1D<double>&              _f                   // rechte Seite Vektor (i)
    )
{

  int n = _a.get_size();
  Array1D<double> y(n);
  
  double norm;
  double sum;
  int ite = 0;

  do {
    norm = 0;
    // x^(k+1) == u
    // x^(k)   == y
    
    // copy new solution to old solution

    for (int j = 0; j < n; j++) 
      y[j] = _u[j];

    for (int i = 0; i < n; i++) {
      // _u[i]
      sum = _f[i];
      // loop all rows above i
      for (int j = 0; j < i; j++) 
        sum -= _a.get_entry(i,j) * _u[j];
      // loop all rows below i
      for (int j = i+1; j < n; j++) 
        sum -= _a.get_entry(i,j) * y[j];

      _u[i] = sum / _a.get_entry(i,i);

      norm += (y[i] - _u[i]) * (y[i] - _u[i]);
    }
    ite++;
    //cout << norm << endl;
  } while (sqrt(norm) > tol_ite && ite < max_ite);

  if (ite == max_ite) {
    throw runtime_error(string("GS: Not converged in max_ite!!"));
  } else {
    cout << "G-S solver converged successfully in " << ite << 
      " iterations with tolerance " << tol_ite << "." << endl; 
  }

  return;
}



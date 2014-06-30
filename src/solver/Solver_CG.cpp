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


/** Loesung des LGS a*u=f mit dem konjugierten Gradienten-Verfahren (CG)
 *
 */
void Solver_CG::solve(
    Matrix&                       _a,                  // Matrix des LGS (i)
    Array1D<double>&              _u,                  // Loesungsvektor (o)
    Array1D<double>&              _f                   // rechte Seite Vektor (i)
    )
{

  int n = _a.get_size();

  double norm;
  unsigned int ite = 0;

  // malte's:
  
  //double norm_r2, norm_r, lambda, beta;
  //Array1D<double> r(n);
  //Array1D<double> p(n);
  //Array1D<double> ap(n);
  //r = _f - _a * _u;
  //norm_r2 = r*r;
  //p = r;

  //do {
    //ap = _a * p;
    //norm_r = norm_r2;
    //lambda = norm_r / (p * ap);

    //// update
    //_u = _u + lambda * p;
    //r = r - lambda * ap;
    //norm_r2 = r * r;

    //beta = norm_r2 / norm_r;
    //p = r + beta * p;

    //ite++;

  //} while (ite < max_ite && sqrt(norm_r2) > tol_ite);

  // mine:

  Array1D<double> r(n);
  Array1D<double> r_old(n);
  Array1D<double> Ap(n);
  Array1D<double> p(n);
  double lambda;
  double beta;

  // calculate initial residual
  // r = b - A*x

  r = _f - _a * _u;
  p = r;
  do {
    Ap = _a * p; 
    lambda = (r * r) / (p * Ap);
    _u = _u + lambda * p;
    r_old = r;
    r = r - lambda * Ap;
    beta = (r * r) / (r_old * r_old);
    p = r + beta * p;

    ite++;
    norm = sqrt(r * r);
  } while (norm > tol_ite && ite < max_ite);

  r.print("r:");
  if (ite == max_ite) {
    throw runtime_error(string("CG: Not converged in max_ite!!"));
  } else {
    cout << "CG solver converged successfully in " << ite << 
      " iterations with tolerance " << tol_ite << "." << endl; 
  }

  return;
}



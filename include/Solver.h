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



#ifndef SOLVER_H_
#define SOLVER_H_



/** abstrakte Klasse zur Beschreibung eines linearen Loesers
 *
 */
class Solver
{


protected:
  bool                            factorized;         // Faktorisierung wurde durchgefuehrt und gespeichert


public:
  /** Default-Konstruktor
   *
   */
  Solver()
  {
    factorized = false;
  };


  virtual ~Solver() {};


  virtual void solve(Matrix& a, Array1D<double>& u, Array1D<double>& f) = 0;


};


#include "Solver_LU.h"
#include "Solver_CG.h"
#include "Solver_GS.h"


#endif /* SOLVER_H_ */

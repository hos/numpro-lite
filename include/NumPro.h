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


#ifndef NUMPRO_H_
#define NUMPRO_H_


#include "Main.h"
class Solver;


/** Die Klasse NumPro fasst alle Informationen einer Simulation zusammen
 *
 */
class NumPro
{

protected:
  Discretization       *discretization;     // Zeiger zur zugehoerigen Diskretisierung

  Solver               *solver;             // Loeser fuer das globale Gleichungssystem
  Matrix               *stiffness_matrix;   // globale Steifigkeitsmatrix

  Array1D<double>       sol;                // Loesungsvektor des gloablen LGS
  Array1D<double>       fext;               // globaler Vektor der aeusseren Kraefte



public:
  /** Konstruktor ohne Parameter
   *
   */
  NumPro();

};


#endif /* NUMPRO_H_ */


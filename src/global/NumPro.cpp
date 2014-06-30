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



#include "NumPro.h"
#include "Discretization.h"
#include "Solver.h"

/** Programmablauf einer normalen Berechnung
 *
 */
NumPro :: NumPro()
{

  // Diskretisierung wird angelegt
  discretization = new Discretization();



  /************************************
   *
   * Löser und Matrix-Format
   *
   ************************************/
  stiffness_matrix = new Matrix_Dense( discretization );
  //solver           = new Solver_LU();
  solver           = new Solver_GS();



  // Allokieren der globalen Vektoren
  sol.resize( discretization->get_num_dof_solve() );
  sol.init();
  fext.resize( discretization->get_num_dof_solve() );
  fext.init();



  printf("\n\n");
  printf("==============================================================\n");
  printf("Solve Static Linear Problem:\n");
  printf("==============================================================\n");


  // lineare Steifigkeitsmatrix und der Vektor der Dirichlet-Kraefte werden assembliert
  discretization->assemble_stalin(stiffness_matrix);


  // Vektor der aeusseren Kraefte wird assembliert
  discretization->assemble_fext(fext);


  // das globale LGS wird geloest */
  solver->solve(*stiffness_matrix, sol, fext);

  fext.print("f:");
  sol.print("u:");

  // die Werte des globalen Loesungsvektors sol werden an die Knoten verteilt
  discretization->disp2node_copy(sol);


  // Rueckrechnung der Spannungen und internen Kraefte fuer alle Elemente
  discretization->cal_stress_lin();

  // Ausgabe der globalen Verschiebungen
  //sol.print();

  // Ausgabe in eine Datei
  discretization->output_msh();
  discretization->output_res();


  return;
}


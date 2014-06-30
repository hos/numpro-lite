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



#include "Matrix.h"
#include "Discretization.h"



/** Konstruktor fuer dense (vollstaendige 2d) Matrix
 *
 */
Matrix_Dense::Matrix_Dense(
    Discretization*               _dis                // Zeiger auf die Diskretisierung (i)
    )
{
  num_eq   = _dis->get_num_dof_solve();

  masked     = false;
  assembled  = false;
  factorized = false;

  value.resize(num_eq, num_eq);
  value.init();

  masked = true;

  return;
}




/** Setzt die Matrix auf leer zurueck
 * Loescht alle Vektoren und setzt alle Groessen auf Null.
 *
 */
void Matrix_Dense::reset()
{
  value.resize(0,0);

  masked     = false;
  assembled  = false;
  factorized = false;

  num_eq     = 0;

  return;
}





/** Alle Komponenten aller Werte der Matrix zu Null setzen
 * die Maske bleibt erhalten
 *
 */
void Matrix_Dense::init()
{
  value.init();
  return;
}




/** Matrix auf dem Bildschirm ausgeben
 *
 */
void Matrix_Dense::print()
{
  printf("Stiffness Matrix:");
  value.print();
  printf("\n");
  return;
}




/** Maske der Matrix auf dem Bildschirm ausgeben
 *
 */
void Matrix_Dense::print_mask()
{
  printf("Mask of Stiffness Matrix:");
  value.print_mask();
  printf("\n");
  return;
}




/** Anzahl der Zeilen/Spalten der Matrix abfragen
 *
 */
int Matrix_Dense::get_size()
{
  return num_eq;
}




/** einen Eintrag in die Matrix hinein addieren
 *
 */
void Matrix_Dense::add_entry(
    int                           _n,                  ///< Zeilennummer (i)
    int                           _m,                  ///< Spaltennummer (i)
    double                        _val                 ///< Wert (i)
    )
{
  value[_n][_m] += _val;
  return;
}




/** Einen Wert aus der Matrix abfragen
 *
 */
double Matrix_Dense::get_entry(
    int                           _n,                  // Zeilennummer
    int                           _m                   // Spaltennummer
    )
{
  return value[_n][_m];
}


//Matrix_Dense Matrix_Dense::operator*(Matrix_Dense& l) {
  
//}


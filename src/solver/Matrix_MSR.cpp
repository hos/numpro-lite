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




/** Konstruktor fuer eine Matrix im MSR_Format
 * Beschreibung des MSR-Formats: siehe Numerik-Vorlesung oder Aztec-Manuel
 *
 */
Matrix_MSR::Matrix_MSR(
    Discretization*               _dis                // Zeiger auf die Diskretisierung (i)
    )
{
  num_eq   = _dis->get_num_dof_solve();


  Array1D< int >                     num_dc;
  Array1D< List < int > >            dc;
  _dis->fill_dof_connect(nnz, num_dc, dc, true);


  masked     = false;
  assembled  = false;
  factorized = false;


  /* allocate A (value) and J (index) */
  index.resize(nnz+1);
  index.init();

  value.resize(nnz+1);
  value.init();


  index[num_eq] = nnz+1;

  /* write values to J */
  int counter = num_eq+1;
  for (int i=0; i<num_eq; i++)
  {
    index[i] = counter;
    for (int j=0;j<num_dc[i]; j++)
    {
      index[counter] = dc[i][j];
      counter++;
    }
  }

  /* PROBE */
  if (counter != nnz+1)
  {
    cout << "ERROR while building the MSR-format!!" << endl;
    exit (1);
  }

  masked = true;

  return;
}




/** Setzt die Matrix auf leer zurueck
 * Loescht alle Vektoren und setzt alle Groessen auf Null.
 *
 */
void Matrix_MSR::reset()
{
  value.resize(0);
  index.resize(0);

  masked     = false;
  assembled  = false;
  factorized = false;

  num_eq   = 0;
  nnz      = 0;

  return;
}




/** einen Eintrag in die Matrix hinein addieren
 *
 */
void Matrix_MSR::add_entry(
    int                           _n,                  // Zeilennummer (i)
    int                           _m,                  // Spaltennummer (i)
    double                        _val                 // Wert (i)
    )
{

  if (_n == _m)
  {
    value[_n] += _val;
    return;
  }

  for (int i=index[_n]; i<index[_n+1]; i++)
    if (index[i] == _m)
    {
      value[ i ] += _val;
      return;
    }

  cout << "Error in MSR format!!";

  return;
}




/** Alle Komponenten aller Werte der Matrix zu Null setzen
 * die Maske bleibt erhalten
 *
 */
void Matrix_MSR::init()
{
  value.init();
  return;
}




/** Matrix als zwei Vektoren auf dem Bildschirm ausgeben
 *
 */
void Matrix_MSR::print()
{
  printf("Stiffness Matrix: (J, A)\n");
  for (int i=0; i<nnz+1; i++)
    printf("%6d  %16.8e\n", index [i], value[i]);
  printf("\n");
  return;
}




/** nicht implementiert!!
 *
 */
void Matrix_MSR::print_mask()
{}




/** Anzahl der Zeilen/Spalten der Matrix abfragen
 *
 */
int Matrix_MSR::get_size()
{
  return num_eq;
}




/** Einen Wert aus der Matrix abfragen
 *
 */
double Matrix_MSR::get_entry(
    int                           _n,                  // Zeilennummer
    int                           _m                   // Spaltennummer
    )
{

  // TODO: get_entry fuer Matrix_MSR

  return 17;

}



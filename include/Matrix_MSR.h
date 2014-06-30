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


#ifndef MATRIX_MSR_H_
#define MATRIX_MSR_H_


/** Klasse zur Beschreibung einer Matrix im MSR_Format
 * Beschreibung des MSR-Formats: siehe Numerik-Vorlesung oder Aztec-Manuel
 *
 */
class Matrix_MSR : public Matrix
{


protected:
  int                             nnz;                // Anzahl der Nicht-Null-Eintraege
  Array1D<double>                 value;              // Vektor der Werte
  Array1D<int>                    index;              // Vektor der Indizes


public:


  /** Default-Konstruktor
   *
   */
  Matrix_MSR()
  {
    nnz         = 0;
    num_eq      = 0;

    masked      = false;
    assembled   = false;
    factorized  = false;
  }



  Matrix_MSR( Discretization *dis);




  /** Destruktor
   *
   */
  ~Matrix_MSR() { }



  
  void create( Discretization *dis);

  void create_MSR(int num_eq, int nnz, int *num_dc, int **dc);

  void reset();
  void init();
  void print();
  void print_mask();
  int  get_size();

  double get_entry(int n, int m);
  void   add_entry(int n, int m, double val);




  /** Matrix-Vektor-Produkt
   * Homework 3
   */
  Array1D<double> operator* (
      const Array1D<double> &     _v                   // Vektor, mit dem multipliziert werden soll (i)
      ) const
  {
    if (_v.get_size() != num_eq) {
      stringstream msg;
      msg << "Number of columns in matrix: "
        << num_eq 
        << " != number of rows in multiplicant vector: " 
        << _v.get_size();
      throw runtime_error(msg.str());
    }

    Array1D<double> result( _v.get_size() );
    result.init();

    for (unsigned int i = 0; i < _v.get_size(); i++) {
      result[i] += value[i] * _v[i];
        for (unsigned int j = index[i]; j < index[i+1]; j++) {
          double column = index[j];
          result[i] += value[j] * _v[column];
        }
    }

    return result;
  };




  /** Vorwaertseinsetzen
   *
   */
  Array1D<double> vorwaerts (
      const Array1D<double> &     _v                   // rechte Seite Vektor (i)
      )
  {
    double sum;

    Array1D<double> result( _v.get_size() );
    result.init();


    // TODO: Vorwaerts-Einsetzen fuer Matrix_MSR


    return result;
  }




  /** Rueckwaertseinsetzen
   *
   */
  Array1D<double> rueckwaerts (
      const Array1D<double> &     _v                   // rechte Seite Vektor (i)
      )
  {
    double sum;

    Array1D<double> result( _v.get_size() );
    result.init();


    // TODO: Rueckwaerts-Einsetzen fuer Matrix_MSR


    return result;
 }


};


#endif /* MATRIX_MSR_H_ */


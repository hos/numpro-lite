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


#ifndef MATRIX_DENSE_H_
#define MATRIX_DENSE_H_


/** Klasse zur Beschreibung einer Matrix im dense-Format
 *
 */
class Matrix_Dense : public Matrix
{

protected:
  Array2D<double>                value;              // Zeiger auf den Inhalt der Matrix


public:


  /** Default-Konstruktor
   *
   */
  Matrix_Dense()
  {
    num_eq      = 0;

    masked      = false;
    assembled   = false;
    factorized  = false;
  }




  Matrix_Dense( Discretization *dis);




  /** Destruktor
   *
   */
  ~Matrix_Dense() {}




  /** Zuweisungsoperator
   *
   */
  Matrix_Dense operator= (
      Matrix_Dense const&         mat2                // rechte Seite fuer die Zuweisung (i)
      )
  {
    if (this == &mat2)
      return *this;

    return *this;
  }




  void create( Discretization *dis);


  void reset();
  void init();
  void print();
  void print_mask();
  int get_size();

  void add_entry(int n, int m, double val);
  double get_entry(int n, int m);




  /** Matrix-Vektor-Produkt
   * Homework 3
   */
  Array1D<double> operator* (
      Array1D<double> const&      v                   ///< Vektor, mit dem multipliziert werden soll (i)
      ) const
  {
    //if (v.get_size() != this->get_size()) 
      //throw;

    Array1D<double> result( v.get_size() );
    result.init();

    for (unsigned int i = 0; i < v.get_size(); i++) {
      for (unsigned int j = 0; j < v.get_size(); j++) {
        result[i] += value[i][j] * v[j];
      }
    }

    return result;
  }




  /** Vorwaertseinsetzen
   *
   */
  Array1D<double> vorwaerts (
      const Array1D<double> &     v                   ///< rechte Seite Vektor (i)
      )
  {
    double sum;

    Array1D<double> result( v.get_size() );
    result.init();


    // TODO: Vorwaerts-Einsetzen fuer Matrix_Dense


    return result;
  }




  /** Rueckwaertseinsetzen
   *
   */
  Array1D<double> rueckwaerts (
      const Array1D<double> &     v                   ///< rechte Seite Vektor (i)
      )
  {
    double sum;

    Array1D<double> result( v.get_size() );
    result.init();

    // TODO: Rueckwaerts-Einsetzen fuer Matrix_Dense


    return result;
  }


};


#endif /* MATRIX_DENSE_H_ */



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


#ifndef MATRIX_H_
#define MATRIX_H_


#include "Main.h"


class Discretization;


/** Abstrakte Klasse zur Beschreibung von Matrizen
 *
 */
class Matrix
{

public:


protected:
  int                     num_eq;

  bool                    masked;
  bool                    assembled;
  bool                    factorized;


public:


  virtual ~Matrix() {};

  virtual void reset() = 0;
  virtual void init() = 0;
  virtual void print() = 0;
  virtual void print_mask() = 0;
  virtual int  get_size() = 0;

  virtual double get_entry(int n, int m) = 0;
  virtual void   add_entry(int n, int m, double val) = 0;


  virtual Array1D<double> operator*   (const Array1D<double> &v) const = 0;
  virtual Array1D<double> vorwaerts   (const Array1D<double> &v) = 0;
  virtual Array1D<double> rueckwaerts (const Array1D<double> &v) = 0;




  /** Setzt den Wert der Eigenschaft 'masked'
   *
   */
  void set_masked(
      bool                        _b                   ///< neuer Wert (i)
      )
  {
    masked = _b;
    return;
  }




  /** Fragt den Wert der Eigenschaft 'masked' ab
   *
   */
  bool get_masked()
  {
    return masked;
  }




  /** Setzt den Wert der Eigenschaft 'assembled'
   *
   */
  void set_assembled(
      bool                        _b                   ///< neuer Wert (i)
      )
  {
    assembled = _b;
    return;
  }




  /** Fragt den Wert der Eigenschaft 'assembled' ab
   *
   */
  bool get_assembled()
  {
    return assembled;
  }




  /** Setzt den Wert der Eigenschaft 'factorized'
   *
   */
  void set_factorized(
      bool                        _b                   ///< neuer Wert (i)
      )
  {
    factorized = _b;
    return;
  }




  /** Fragt den Wert der Eigenschaft 'factorized' ab
   *
   */
  bool get_factorized()
  {
    return factorized;
  }


};


#include "Matrix_Dense.h"
#include "Matrix_MSR.h"


#endif /* MATRIX_H_ */


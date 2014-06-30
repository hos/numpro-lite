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



#ifndef MATERIAL_H_
#define MATERIAL_H_



/** Linear elastisches Material
 *
 */
class Material
{

protected:
  double                     e;                  // E-Modul
  double                     nu;                 // Querdehnzahl

public:

  /** Konstruktor mit Parametern
   *
   */
  Material(
      double                 _e,                  // E-Modul (i)
      double                 _nu                  // Querdehnzahl (i)
  )
{
    this->e      = _e;
    this->nu     = _nu;
}




  /** Funktion zum Berechnen der linearen Materialmatrix in 2D
   *
   */
  void mat2D_lin(
      Array2D<double>&                 _c              ///< Tangenten-Modul (o)
  )
  {

    _c.init();

    // plane_stress:
    double e1=0, e2=0, e3=0;

    e1=e/(1. - nu*nu);
    e2=nu*e1;
    e3=e1*(1. - nu)/2.;

    _c[0][0]=e1;
    _c[0][1]=e2;
    _c[0][2]=0.0;

    _c[1][0]=e2;
    _c[1][1]=e1;
    _c[1][2]=0.0;

    _c[2][0]=0.0;
    _c[2][1]=0.0;
    _c[2][2]=e3;



    // plane_strain:
    /*
    double a1=0, b1=0, c1=0;
    double vor=0;

    vor = e/( (1+nu)*(1-2*nu) );

    a1 = vor * (1-nu);
    b1 = vor * nu;
    c1 = vor * (1-2.0*nu)/2.0;

    _c[0][0]=a1;
    _c[0][1]=b1;
    _c[0][2]=0.0;

    _c[1][0]=b1;
    _c[1][1]=a1;
    _c[1][2]=0.0;

    _c[2][0]=0.0;
    _c[2][1]=0.0;
    _c[2][2]=c1;
    */

    return;
  };


};


#endif /* MATERIAL_H_ */


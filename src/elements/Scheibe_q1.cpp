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




#include "Discretization.h"
#include "Element.h"
#include "Material.h"
#include "Node.h"



/** Konstruktor mit Parametern
 *
 */
Scheibe_q1::Scheibe_q1(
    int                           _id,                      // Nummer des Elements (i)
    int                           _n1,                      // Nummer des 1. Knotens (i)
    int                           _n2,                      // Nummer des 2. Knotens (i)
    int                           _n3,                      // Nummer des 3. Knotens (i)
    int                           _n4,                      // Nummer des 4. Knotens (i)
    Material                     *_mat,                     // Zeiger auf das Material (i)
    Discretization               *_dis
)
{
  this->id = _id;

  this->material      = _mat;

  this->stress.resize(4,3);


  // Pointer: Element to Nodes
  nodes.resize(4);
  nodes[0] = _dis->node_get( _n1 );
  nodes[1] = _dis->node_get( _n2 );
  nodes[2] = _dis->node_get( _n3 );
  nodes[3] = _dis->node_get( _n4 );

  // Pointer: Nodes to Element (this)
  nodes[0]->element_append( this );
  nodes[1]->element_append( this );
  nodes[2]->element_append( this );
  nodes[3]->element_append( this );

}





/** Berechnung der linearen Steifigkeitsmatrix
 *
 */
void Scheibe_q1::stiffness_lin(
    Array2D<double>&              _ele_stiff             // Elementsteifigkeitsmatrix (o)
)
{

  Array2D<double>    c(3,3);
  Array2D<double>    deriv(4,2);
  Array2D<double>    jaco(2,2);
  Array2D<double>    jaco_inv(2,2);
  Array2D<double>    bop(3,8);
  Array2D<double>    bopt(8,3);
  double det;

  _ele_stiff.init();


  // Materialmatrix (konstant im Element)
  material->mat2D_lin(c);


  // 2x2 Gauss points
  Array2D<double> intdata(2,2);
  // positions of the Gauss points
  intdata[0][0] = -1.0/sqrt(3);
  intdata[1][0] = +1.0/sqrt(3);
  // weighting factors of the Gauss points
  intdata[0][1] = 1.0;
  intdata[1][1] = 1.0;


  for (int j=0; j<2; j++)
    for (int l=0; l<2; l++)
    {

      double xi  = intdata[l][0];
      double eta = intdata[j][0];
      double weight_gp  = intdata[l][1]*intdata[j][1];

      // Ableitungen der Formfunctionen
      const double   q14 = 1.0/4.0;
      double         rp,rm,sp,sm;

      rp = 1.0+xi;
      rm = 1.0-xi;
      sp = 1.0+eta;
      sm = 1.0-eta;

      deriv[0][0]=-q14*sm;
      deriv[0][1]=-q14*rm;
      deriv[1][0]= q14*sm;
      deriv[1][1]=-q14*rp;
      deriv[2][0]= q14*sp;
      deriv[2][1]= q14*rp;
      deriv[3][0]=-q14*sp;
      deriv[3][1]= q14*rm;


      // Jacobi Matrix
      jaco.init();

      for (int k=0; k<4; k++)
      {
        jaco[0][0] += deriv[k][0] * nodes[k]->get_x();
        jaco[0][1] += deriv[k][0] * nodes[k]->get_y();
        jaco[1][0] += deriv[k][1] * nodes[k]->get_x();
        jaco[1][1] += deriv[k][1] * nodes[k]->get_y();
      }
      det = jaco[0][0]* jaco[1][1] - jaco[1][0]* jaco[0][1];


      // Inverse der Jacobi-Matrix
      double dum = 1.0/det;
      jaco_inv[0][0] = jaco[1][1]* dum;
      jaco_inv[0][1] =-jaco[0][1]* dum;
      jaco_inv[1][0] =-jaco[1][0]* dum;
      jaco_inv[1][1] = jaco[0][0]* dum;


      // B-Operator
      bop.init();
      for (int i=0; i<4; i++)
      {
        int node_start = i*2;

        bop[0][node_start+0] = jaco_inv[0][0] * deriv[i][0]
                                                         + jaco_inv[0][1] * deriv[i][1];
        bop[1][node_start+1] = jaco_inv[1][0] * deriv[i][0]
                                                         + jaco_inv[1][1] * deriv[i][1];

        bop[2][node_start+0] = bop[1][node_start+1];
        bop[2][node_start+1] = bop[0][node_start+0];
      }

      bopt = bop.transpose();
      _ele_stiff += weight_gp*det*bopt*c*bop;
    }

  return;
}




/** Berechnung der Spannungen
 *
 */
void Scheibe_q1::stress_lin()
{

  Array2D<double>    c(3,3);
  Array2D<double>    deriv(4,2);
  Array2D<double>    jaco(2,2);
  Array2D<double>    jaco_inv(2,2);
  Array2D<double>    bop(3,8);
  Array1D<double>    elem_stress(3);
  double det;

  //stress.resize(4,3);
  stress.init();

  // Materialmatrix (konstant im Element)
  material->mat2D_lin(c);


  // 2x2 Gauss points
  Array2D<double> intdata(2,2);
  // positions of the Gauss points
  intdata[0][0] = -1.0/sqrt(3);
  intdata[1][0] = +1.0/sqrt(3);
  // weighting factors of the Gauss points
  intdata[0][1] = 1.0;
  intdata[1][1] = 1.0;

  // get the displacement vector
  Array1D<double> d(8);
  for (int i = 0; i < 4; i++) {
    d[2*i]   = nodes[i]->get_sol(0);
    d[2*i+1] = nodes[i]->get_sol(1);
  }

  int count = 0;
  for (int j=0; j<2; j++)
    for (int l=0; l<2; l++)
    {

      double xi  = intdata[l][0];
      double eta = intdata[j][0];
      double weight_gp  = intdata[l][1]*intdata[j][1];

      // Ableitungen der Formfunctionen
      const double   q14 = 1.0/4.0;
      double         rp,rm,sp,sm;

      rp = 1.0+xi;
      rm = 1.0-xi;
      sp = 1.0+eta;
      sm = 1.0-eta;

      deriv[0][0]=-q14*sm;
      deriv[0][1]=-q14*rm;
      deriv[1][0]= q14*sm;
      deriv[1][1]=-q14*rp;
      deriv[2][0]= q14*sp;
      deriv[2][1]= q14*rp;
      deriv[3][0]=-q14*sp;
      deriv[3][1]= q14*rm;


      // Jacobi Matrix
      jaco.init();

      for (int k=0; k<4; k++)
      {
        jaco[0][0] += deriv[k][0] * nodes[k]->get_x();
        jaco[0][1] += deriv[k][0] * nodes[k]->get_y();
        jaco[1][0] += deriv[k][1] * nodes[k]->get_x();
        jaco[1][1] += deriv[k][1] * nodes[k]->get_y();
      }
      det = jaco[0][0]* jaco[1][1] - jaco[1][0]* jaco[0][1];


      // Inverse der Jacobi-Matrix
      double dum = 1.0/det;
      jaco_inv[0][0] = jaco[1][1]* dum;
      jaco_inv[0][1] =-jaco[0][1]* dum;
      jaco_inv[1][0] =-jaco[1][0]* dum;
      jaco_inv[1][1] = jaco[0][0]* dum;


      // B-Operator
      bop.init();
      for (int i=0; i<4; i++)
      {
        int node_start = i*2;

        bop[0][node_start+0] = jaco_inv[0][0] * deriv[i][0]
                                                         + jaco_inv[0][1] * deriv[i][1];
        bop[1][node_start+1] = jaco_inv[1][0] * deriv[i][0]
                                                         + jaco_inv[1][1] * deriv[i][1];

        bop[2][node_start+0] = bop[1][node_start+1];
        bop[2][node_start+1] = bop[0][node_start+0];
      }
      
      elem_stress = c * bop * d;

      for (int i=0; i < 3; i++) {
        //cout << elem_stress[i] << endl;
        stress[count][i] = elem_stress[i];
      }
      count++;
    }

  return;
}




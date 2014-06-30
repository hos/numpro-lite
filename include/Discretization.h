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


#ifndef DISCRETIZATION_H_
#define DISCRETIZATION_H_


#include "Main.h"


#include "Node.h"
#include "Element.h"
class Material;


/** beschreibt eine Diskretisierung
 *  aktuell an den Anforderungen einer FE-Diskretisierung orientiert
 *  sollte aber auch fuer andere Diskretisierungen (Particles, etc.) anzuwenden sein.
 *
 */
class Discretization
{


protected:

  List<Node*>                node;               // Liste von Zeigern auf alle Knoten
  List<Element*>             element;            // Liste von zeigern auf alle Elemente
  List<Material*>            material;           // Liste von Zeigern auf alle Materialien

  int                        num_dof_total;      // Anzahl aller Freiheitsgrade
  int                        num_dof_solve;      // Anzahl der zu loesenden Freiheitsgrade (Groesse des globale LGS)
  int                        num_dof_dirich;     // Anzahl der durch Dirichlet-RB festgehaltenen Freiheitsgrade



public:

  Discretization();

  void assign_dofs();

  void assemble_stalin(Matrix *_a);

  void assemble_fext(Array1D<double> &_fext);

  void cal_stress_lin();

  void disp2node_copy(Array1D<double>& _disp);

  void fill_dof_connect(int&  _nnz, Array1D<int>& _num_dof_connect, Array1D< List<int> >& _dof_connect, bool _msr);




  /** Ausgabe des Netzes
   *
   */
  void output_msh()
  {
    ofstream os("numpro_output.msh");

    os << "MESH Scheibe_q1 dimension 2 Elemtype Quadrilateral Nnode 4" << endl;

    os << "coordinates" << endl;
    for(int i=0; i < node.get_size(); i++)
      node[i]->output_msh(os);
    os << "end coordinates" << endl;

    os << "elements" << endl;
    for(int i=0; i < element.get_size(); i++)
      element[i]->output_msh(os);
    os << "end elements" << endl;

    os.close();

    return;
  }




  /** Ausgabe der Ergebnisse
   *
   */
  void output_res()
  {
    ofstream os("numpro_output.res");

    os << "GiD Post Results File 1.0" << endl;

    os << "GaussPoints \"gps_scheibe_q1\" Elemtype Quadrilateral \"Scheibe_q1\"" << endl;
    os << "Number of Gauss Points: 4" << endl;
    os << "Natural Coordinates: Internal" << endl;
    os << "end gausspoints" << endl;

    os << "Result \"displacement\" \"NumPro\" 1 Vector OnNodes" << endl;
    os << "ComponentNames \"comp. x\", \"comp. y\", \"unused\"" << endl;

    os << "values" << endl;
    for(int i=0; i < node.get_size(); i++)
      node[i]->output_res(os);
    os << "end values" << endl;


    os << "Result \"Cauchy\" \"NumPro\" 1.000000 Vector OnGaussPoints \"gps_scheibe_q1\"" << endl;
    os << "ComponentNames \"sigma xx\", \"sigma yy\", \"sigma xy\"" << endl;

    os << "values" << endl;
    for(int i=0; i < element.get_size(); i++)
      element[i]->output_res(os);
    os << "end values" << endl;

    os.close();

    return;
  }



  /** Zeiger auf ein Knoten aus der Knoten-Liste zurueckgegeben
   *
   */
  Node* node_get(
      int                 _i                   // Index des gesuchten Knotens (i)
  )
  {
    return node[_i];
  }




  /** Rueckgabe der Anzahl der zu loesenden Freiheitsgrade
   *
   *  */
  int get_num_dof_solve()
  {
    return num_dof_solve;
  }


};



#endif /* DISCRETIZATION_H_ */


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



#ifndef ELEMENT_H_
#define ELEMENT_H_


#include "Main.h"
#include "Node.h"


class Material;
class Scheibe_q1;

/** Abstrakte Klasse zur Beschreibung von einem finiten Element
 *
 */
class Element
{

protected:
  int                        id;                 // Element-Nummer

  List<int>                  idMatrix;           // ID-Matrix

  List<Node*>                nodes;              // Liste mit Zeigern auf zugehoerige Knoten

  Material                  *material;           // Zeiger auf das verwendete Material

  Array2D<double>            stress;             // Spannungen an jedem GaussPunkt



public:
  virtual ~Element(){};

  virtual void stiffness_lin( Array2D<double>& _ele_stiff) = 0;

  virtual void stress_lin( ) = 0;

  virtual void output_msh(ostream &os) = 0;
  virtual void output_res(ostream &os) = 0;



  /** Rueckgabe des Dirichlet-Flags fuer einen Freiheitsgrad
   *
   */
  bool  get_dirich_flag(
      int                 _i                // Nummer des Freiheitsgrads, in lokaler Elementnummerierung (i)
      )
  {
    /* Umrechnung der Freiheitsgradnummer in Knotennummer und Freiheitsgradnummer am Knoten:
     * dof i   -  lokale Nummerierung aller Freiheitsgrade am Element
     * Knotennummer:   ( i - ( i % 2) ) / 2
     * Dof am Knoten:  i % 2
     */
    int n = ( _i - (_i%2) ) / 2;
    int d  = _i%2;
    return nodes[n]->get_bc_displ(d);
  }




  /** Laenge der ID-Matrix veraendern
   *
   */
  void idMatrix_resize(
      int                         _size                // neue Laenge der ID-Matrix (i)
      )
  {
    idMatrix.resize(_size);
    return;
  }



  /** Element ID abfragen
   *
   */
  int get_id()
  {
    return id;
  }




  /** einen Wert in der ID-Matrix setzen
   *
   */
  void idMatrix_set(
      int                         _i,                  // Position, an der der Wert gesetzt werden soll (i)
      int                         _val                 // Wert, der gesetzt werden soll (i)
      )
  {
    idMatrix[_i] = _val;
    return;
  }





  /** einen Wert aus der ID-Matrix auslesen
   *
   */
  int idMatrix_get(
      int                         _i                   // Position, an der der Wert ausgelesen werden soll (i)
      )
  {
    return idMatrix[_i];
  }




  /** einen Knoten-Zeiger aus der Liste abfragen
   *
   */
  Node* nodes_get(
      int                         _i                   // Position, an der der Zeiger ausgelesen werden soll (i)
      )
  {
    return nodes[_i];
  }


};


#include "Scheibe_q1.h"


#endif /* ELEMENT_H_ */

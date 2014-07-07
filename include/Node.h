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



#ifndef NODE_H_
#define NODE_H_


#include "Main.h"

class Element;


/** Klasse zur Beschreibung von einem FE-Knoten
 *
 */
class Node
{

protected:
  int                        id;                 // Knotennummer

  double                     x[2];               // globale Koordinaten des Knotens
  int                        dof[2];             // Nummern der Freiheitsgrade an diesem Knoten
  double                     sol[2];             // Loesungsvektor an diesem Knoten

  double                     bc_force[2];        // Liste mit aeusseren Kraeften
  int                        bc_displ[2];        // Liste mit flags, ob der dof fdestgehalten ist

  List<Element*>             element;            // Liste mit Zeigern auf die angrenzenden Elemente



public:
  /** Konstruktor mit Parametern
   *
   */
  Node(
      int               _id,                 // Knotennummer (i)
      double            _x,                  // x-Koordinate (i)
      double            _y                   // y-Koordinate (i)
      )
  {
    this->id   = _id;
    this->x[0] = _x;
    this->x[1] = _y;

    for (int i=0; i<2; i++)
    {
      dof[i] = 0;
      sol[i] = 0;
      bc_displ[i] = 0;
      bc_force[i] = 0;
    }
  }




  /** Ausgabe der Knoten-Koordinaten
   *
   */
  void output_msh(ostream &os)
  {
    os << id+1 << "  " << x[0] << "  " << x[1] << "   0.0" << endl;
    return;
  }



  /** Ausgabe der Knoten-Lösungen
   *
   */
  void output_res(ostream &os)
  {
    os << id+1 << " " << sol[0] << "  " << sol[1] << "  0.0" << endl;
    return;
  }



  /** Knoten ID abfragen
   *
   */
  int get_id()
  {
    return id;
  }



  /** Rueckgabe der x-Koordinate
   *
   */
  double get_x()
  {
    return x[0];
  }




  /** Rueckgabe der y-Koordinate
   *
   */
  double get_y()
  {
    return x[1];
  }




  /** Rueckgabe von einem Loesungswert aus sol
   *
   */
  double get_sol(
      int                    _dof                 // Freiheitsgrad (i)
      )
  {
    return  sol[_dof];
  }




  /** Setzen von einem Loesungswert in sol
   *
   */
  void set_sol(
      int                    _dof,                // Freiheitsgrad (i)
      double                 _v                   // Wert (i)
      )
  {
    sol[_dof] = _v;

    return;
  }




  /** Rueckgabe des Dirchlet-Flags fuer einen Freiheitsgrad
   *
   */
  bool get_bc_displ(
      int                    _d                   // Freiheitsgradnummer (i)
      )
  {
    /* pruefen, ob Freiheitsgrad d eine Dirichlet-RB hat */
    if (bc_displ[_d] != 0)
      return true;
    else
      return false;
  }



  /** eine Verschiebungs-RB setzen
   *
   */
  void set_bc_displ(
      int                    _d,                // Freiheitsgrad (i)
      int                    _flag              // neuer Flag (i)
      )
  {
    bc_displ[_d] = _flag;
  }




  /** Rueckgabe des aktuellen Neumann-Werts fuer einen Freiheitsgrad
   *
   */
  double get_bc_force(
      int                    _d                   // Freiheitsgradnummer (i)
      )
  {
    return bc_force[_d];
  }




  /** eine Kraft-RB setzen
   *
   */
  void set_bc_force(
      int                    _d,                  // Freiheitsgradnummer (i)
      double                 _val                 // neuer Wert (i)
      )
  {
    bc_force[_d] = _val;
  }




  /** einen Wert in der Liste der Freiheitsgrade setzen
   *
   */
  void dof_set(
      int                         _i,              // Position, an der der Wert gesetzt werden soll (i)
      int                         _val             // Wert, der gesetzt werden soll (i)
      )
  {
    dof[_i] = _val;
    return;
  }




  /** einen Wert aus der Liste der Freiheitsgrade abfragen
   *
   */
  int dof_get(
      int                         _i              // Position, an der der Wert ausgelesen werden soll (i)
      )
  {
    return dof[_i];
  }




  /**  Zeiger auf ein Elemente aus der Element-Liste abfragen
   *
   */
  Element* element_get(
      int                         _i              // Position, an der der Zeiger ausgelesen werden soll (i)
      )
  {
    return element[_i];
  }




  /** Zeiger auf ein Element, an die Element-Liste anhaengen
   *
   */
  void element_append(
      Element*                    _ele            // Zeiger, der an die Liste angehaengt werden soll (i)
      )
  {
    element.append(_ele);
    return;
  }




  /** Laenge der Liste der Element-Zeiger anfragen
   *
   */
  int element_get_size()
  {
    return element.get_size();
  }


};


#endif /* NODE_H_ */


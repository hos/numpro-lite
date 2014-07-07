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


#ifndef SCHEIBE_Q1_H_
#define SCHEIBE_Q1_H_


/** bilineares Scheibenelement (q1)
 * Viereckselement mit linearen Formfunktionen
 *
 */
class Scheibe_q1 : public Element
{


protected:


public:
  Scheibe_q1();
  Scheibe_q1(int _id, int _n1, int _n2, int _n3, int _n4, Material *_mat, Discretization *_dis);
  ~Scheibe_q1(){};


  void stiffness_lin( Array2D<double>& _ele_stiff );
  void stress_lin();


  /** Ausgabe der Konnektivität in einen Stream
   *
   */
  void output_msh(ostream &os)
  {
    os << id+1;

    for (int i=0; i<4; i++)
      os << "   " << nodes[i]->get_id()+1;

    os << endl;

    return;
  }



  /** Ausgabe der Element-Lösungen in einen Stream
   *
   */
  void output_res(ostream &os)
  {
    os << id+1;
    os << " " << stress[0][0] << " " << stress[0][1] << " " << stress [0][2] << endl;
    os << " " << stress[1][0] << " " << stress[1][1] << " " << stress [1][2] << endl;
    os << " " << stress[3][0] << " " << stress[3][1] << " " << stress [3][2] << endl;
    os << " " << stress[2][0] << " " << stress[2][1] << " " << stress [2][2] << endl;

    return;
  }


};


#endif /* SCHEIBE_Q1_H_ */


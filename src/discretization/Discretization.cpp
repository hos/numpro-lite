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
#include "Node.h"
#include "Element.h"
#include "Material.h"
#include "Solver.h"



/** Diskretisierung vorbereiten
 *  Die Diskretisierung wird fuer die Berechnung vorbereitet.
 *
 */
Discretization::Discretization()
{

  num_dof_dirich = 0;
  num_dof_solve  = 0;
  num_dof_total  = 0;


  printf("\n\n");
  printf("==============================================================\n");
  printf("Input:\n");
  printf("==============================================================\n");

  /************************************
   *
   * Material
   *
   ************************************/
  double youngs, poisson;

  youngs  = 1000;
  poisson = 0.0;

  material.resize(1);
  material[0] = new Material(youngs, poisson);




  /************************************
   *
   * Read geometry data
   *
   ************************************/
  double l_x, l_y;             // length of the domain in x and y direction
  int div_x, div_y;            // number of elements in x and y direction

  l_x    = 10;
  l_y    =  1;
  div_x  =  2;
  div_y  =  1;




  /************************************
   *
   * Nodes
   *
   ************************************/
  printf("%6i Nodes\n",(div_x+1)*(div_y+1));
  node.resize( (div_x+1)*(div_y+1) );

  for (int i=0; i<div_y+1; i++)  // loop all rows (blue)
    for (int j=0; j<div_x+1; j++)  // loop all nodes of one row (green)
      node[ j + (div_x+1)*i ] = new Node( j + (div_x+1)*i , j* l_x/div_x , i*l_y/div_y );




  /************************************
   *
   * Elements
   *
   ************************************/
  printf("%6i Elements\n",(div_x)*(div_y));
  element.resize( (div_x)*(div_y) );


  for (int i=0; i<div_y; i++)  // loop all rows (blue)
    for (int j=0; j<div_x; j++)  // loop all elements of one row (green)
      element[ j+div_x*i ] = new Scheibe_q1( j+div_x*i,
          j+(div_x+1)*i,
          j+(div_x+1)*i + 1,
          j+(div_x+1)*(i+1)+1,
          j+(div_x+1)*(i+1),
          material[0], this);




  /*************************
   *
   * Supports
   *
   * ***********************/
  // linke Kante eingespannt
  for (int i=0; i<div_y+1; i++)
  {
    int id = (div_x+1)*i;
    node[id]->set_bc_displ(0, 1);
    node[id]->set_bc_displ(1, 1);
  }




  /*************************
   *
   * Loads
   *
   * ***********************/
  // Einzellast rechts oben
  int id = ((div_x+1)*(div_y+1))-1;
  double value = 17;
  node[id]->set_bc_force(1, value);





  printf("\n\n");
  printf("==============================================================\n");
  printf("Prepare Discretization:\n");
  printf("==============================================================\n");



  /** - Freiheitsgradnummern werden an die Knoten verteilt */
  assign_dofs();



  return;
}




/** Freiheitsgradnummern an die Knoten verteilen
 *  Zuerst werden Freiheitsgradnummern an freie Freiheitsgrade verteilt,
 *  danach an Freiheitsgrade, die durch Dirichlet-RB gehalten sind.
 *  Im Anschluss wird fuer alle Elemente der Diskretisierung die ID-Matrix
 *  aufgestellt.
 *
 */
void Discretization::assign_dofs()
{
  int counter;

  // Anzahl der Freiheitsgrade zu Null setzen
  num_dof_total   = 0;     // Anzahl aller Freiheitsgrade
  num_dof_solve   = 0;     // Anzahl der zu loesenden Freiheitsgrade (Groesse des globale LGS)
  num_dof_dirich  = 0;     // Anzahl der durch Dirichlet-RB festgehaltenen Freiheitsgrade


  /* Schleife ueber alle Knoten der Diskretisierung:
   * Freiheitsgradnummern werden an freie Freiheitsgrade verteilt */
  for(int i=0; i < node.get_size(); i++)
  {
    Node &act_node = *node[i];

    for (int j=0; j<2; j++)
    {
      if ( !act_node.get_bc_displ(j) )
      {
        act_node.dof_set(j, num_dof_total);
        num_dof_total++;
        num_dof_solve++;
      }
    }
  }



  /* Schleife ueber alle Knoten der Diskretisierung:
   * Freiheitsgradnummern werden an festgehaltene Freiheitsgrade verteilt */
  for(int i=0; i < node.get_size(); i++)
  {
    Node &act_node = *node[i];

    for (int j=0; j<2; j++)
    {
      if ( act_node.get_bc_displ(j) )
      {
        act_node.dof_set(j, num_dof_total);
        num_dof_total++;
        num_dof_dirich++;
      }
    }
  }


  printf("%6i dofs total\n",num_dof_total);
  printf("%6i dofs constrained\n",num_dof_dirich);
  printf("%6i dofs to solve\n",num_dof_solve);


  /* Schleife ueber alle Elemente der Diskretisierung:
   * Aufstellen der ID-Matrix */
  for(int i=0; i < element.get_size(); i++)
  {
    Element &act_element = *element[i];


    // idMatrix wird mit der passenden Groesse allokiert
    act_element.idMatrix_resize( 8 );


    counter = 0;
    // Schleife ueber alle Knoten des aktuellen Elements
    for ( int j = 0; j < 4; j++ )
    {
      Node &act_node = *act_element.nodes_get(j);

      // Schleife ueber alle Freiheitsgrade des aktuellen Knoten
      for (int k=0; k<2; k++)
      {
        act_element.idMatrix_set(counter, act_node.dof_get(k));
        counter++;
      }
    }

  }


  return;
}






/** lineare globale Steifigkeitsmatrix assemblieren
 * - Berechnung der Elementsteifigkeitsmatrizen
 * - Assemblierung in die globale Matrix
 *
 */
void Discretization::assemble_stalin(
    Matrix             *_a                  // globale Steifigkeitsmatrix (o)
)
{

  Array2D<double>       ele_stiff;          // Elementsteifigkeitsmatrix
  ele_stiff.resize(8, 8);


  for (int i=0; i< element.get_size(); i++)
  {
    element[i]->stiffness_lin( ele_stiff );

    for (int k=0; k<8; k++) //columns
    {
    	// this column is a constrained dof
    	if ( element[i]->get_dirich_flag(k) )
    		continue;

        for (int l=0; l<8; l++) //rows
          // this row is NOT a constrained dof
          if ( !element[i]->get_dirich_flag(l) )
        	  _a->add_entry(
        			  element[i]->idMatrix_get(l),
        			  element[i]->idMatrix_get(k),
        			  ele_stiff[l][k] );
    }

  }

  // Flags fuer die Matrix und den Loeser setzen
  _a->set_assembled(true);

  return;
}





/** Berechnung der linearen Spannungen
 *  fuer alle Elemente der Diskretisierung
 *
 */
void Discretization::cal_stress_lin()
{

  // Schleife ueber alle Elemente der Diskretisierung
  for(int i=0; i < element.get_size(); i++)
  {
    // Berechnung der linearen Spannungen
    element[i]->stress_lin( );
  }

  return;
}




/** globalen Vektor der aeusseren Kraefte assemblieren
 * - Berechnung der aeusseren Kraefte fuer jeden Knoten
 * - Assemblierung von F_ext
 *
 */
void Discretization::assemble_fext(
    Array1D<double>    &_fext               // globaler Vektor der aeusseren Kraefte (o)
)
{
	for (int i=0; i<node.get_size(); i++) // looping all nodes in the discretization
	{
		Node &act_node = *node[i];

		for (int j=0; j<2; j++)
		{
			// the dof j is constrained by a displacement bc
			if ( act_node.get_bc_displ(j) )
				continue;

			_fext[ act_node.dof_get(j) ] = act_node.get_bc_force(j);
		}
	}

  return;
}





/** Werte aus einen globalen Loesungsvektor werden in die sol-Vektoren am Knoten kopiert
 *
 */
void Discretization::disp2node_copy(
    Array1D<double>         &_disp           // globaler Loesungsvektor (i)
)
{
  /* Schleife ueber alle Knoten der Diskretisierung */
  for(int i=0; i < node.get_size(); i++)
  {
    Node &act_node = *node[i];

    /* Schleife ueber alle Freiheitsgrade am Knoten */
    for (int j=0; j<2; j++)
    {

      /* pruefen, ob der Freiheitsgrad durch eine Dirichlet-RB gehalten wird */
      if ( !act_node.get_bc_displ(j) )
      {
        /* keine Dirichlet-RB:
         * Wert wird aus dem globalen Loesungsvektor disp kopiert */
        act_node.set_sol(j, _disp[act_node.dof_get(j)] );
      }
      else
      {
        /* Dirichlet-RB */
        act_node.set_sol(j, 0 );
      }

    }
  }

  return;
}






/** Konnektivitaet zwischen den Freiheitsgraden wird ermittelt
 * (Hilfsfunktion fuer  MSR-Matrizen)
 *
 */
void Discretization::fill_dof_connect(
    int&                       _nnz,                 // Anzahl der nicht-Null Eintraege der Matrix (o)
    Array1D<int>&              _num_dof_connect,     // Anzahl der nicht-Null Eintraege pro Zeile (o)
    Array1D< List<int> >&      _dof_connect,         // Spalten der nicht-Null Eintraege fuer jede Zeile (o)
    bool                       _msr                  // Modifikation fuer MSR-Format verwenden (i)
)
{

  int                         counter;

  _nnz = 0;
  _num_dof_connect.resize(num_dof_solve);
  _dof_connect.resize(num_dof_solve);


  /* Alle Zeilen von dof_connect mit der Laenge 20 allokieren und mit -1 initialisieren */
  for(int i=0; i < num_dof_solve; i++)
  {
    _num_dof_connect[i] = 0;
    _dof_connect[i].resize(20);
    _dof_connect[i].reset(-1);
  }



  /* Schleife ueber alle Knoten der Diskretisierung */
  for(int i=0; i < node.get_size(); i++)
  {
    Node &act_node = *node[i];

    /* Schleife ueber alle dofs am Knoten */
    for (int ii=0; ii<2; ii++)
    {

      int actdof = act_node.dof_get(ii);


      /* skip all dirichlet dofs */
      if ( act_node.get_bc_displ(ii) )
        continue;


      /* find all connected dofs */
      /* loop all adjacent elements */
      for (int j=0; j<act_node.element_get_size(); j++)
      {
        Element &act_element = *act_node.element_get(j);

        /* loop all nodes of act_element */
        for (int l = 0; l < 4; l++)
        {

          Node &act_node2 = *act_element.nodes_get(l);
          for (int k=0; k<2; k++)
          {
            /* dirichlet dofs don't matter in the matrix */
            if ( act_node2.get_bc_displ(k) )
              continue;
            /* write dof in dof_patch */
            _dof_connect[actdof].append(act_node2.dof_get(k));
            _num_dof_connect[actdof]++;
          }
        }
      }

    }
  }


  /* Schleife ueber alle Zeilen von dof_connect */
  for(int i=0; i < num_dof_solve; i++)
  {
    /* Schleife ueber alle dofs in der Zeile */
    for (int j=0; j<_num_dof_connect[i]; j++)
    {
      /* aktuelle Spalte ist leer, d.h. = -1 */
      if (_dof_connect[i][j] == -1) continue;


      /* fuer msr den dof der zeile entfernen */
      if (_msr)
        if (_dof_connect[i][j] == i) _dof_connect[i][j] = -1;


      /* dof nummer der aktuellen Spalte */
      int dof = _dof_connect[i][j];


      /* in allen anderen Spalten diesen dof loeschen, auf -1 setzen */
      for (int k=j+1; k<_num_dof_connect[i];k++)
      {
        if (dof == _dof_connect[i][k]) _dof_connect[i][k] = -1;
      }
    }


    int n = _num_dof_connect[i];
    bool vertauscht;
    /* Bubble sort */
    do
    {
      vertauscht = false;
      for (int j=0; j<_num_dof_connect[i]-1; j++)
      {
        if (_dof_connect[i][j] == -1 || (_dof_connect[i][j+1] != -1 && _dof_connect[i][j] > _dof_connect[i][j+1]))
        {
          int tmp             = _dof_connect[i][j+1];
          _dof_connect[i][j+1] = _dof_connect[i][j];
          _dof_connect[i][j]   = tmp;
          vertauscht = true;
        }
      }
      n = n - 1;
    }
    while(vertauscht && n>1);


    counter = _num_dof_connect[i];
    /* count number of dofs in this patch */
    for (int j=0; j<_num_dof_connect[i]; j++)
      if (_dof_connect[i][j] == -1)
      {
        counter = j;
        break;
      }


    _num_dof_connect[i] = counter;
    _dof_connect[i].resize(counter);


    if (_msr)
      counter += 1;

    _nnz += counter;

  }


  return;
}


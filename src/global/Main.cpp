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


#include "Main.h"
#include "NumPro.h"


/** Main-Funktion von NumPro
 *  Programm-Einstieg, Auswertung der Kommandozeilen-Parameter
 *
 */
int main(
    int                           _argc,               // Anzahl der Argumente beim Programm-Aufruf
    char**                        _argv                // Liste der Argumente
)
{


  NumPro                    *numpro=NULL;             // Zeiger auf das einzige NumPro-Objekt


  // printing heading to screen
  printf("\n");
  printf("**************************************************************\n");
  printf("*                                                            *\n");
  printf("*                        N u m P r o                         *\n");
  printf("*                           light                            *\n");
  printf("*                                                            *\n");
  printf("**************************************************************\n");
  printf("*                                                            *\n");
  printf("* Copyright (C) 2013 Institut fuer Baustatik und Baudynamik  *\n");
  printf("*                    Universitaet Stuttgart                  *\n");
  printf("*                    Malte von Scheven                       *\n");
  printf("*                                                            *\n");
  printf("* This program comes with ABSOLUTELY NO WARRANTY!            *\n");
  printf("* This is free software, and you are welcome to redistribute *\n");
  printf("* it under certain conditions.                               *\n");
  printf("* For details see the GNU General Public License:            *\n");
  printf("* <http://www.gnu.org/licenses/>                             *\n");
  printf("*                                                            *\n");
  printf("**************************************************************\n");


  numpro = new NumPro();


  delete numpro;


  printf("\n\n");
  printf("==============================================================\n");
  printf("NumPro finished normally!!\n");
  printf("==============================================================\n");


  return EXIT_SUCCESS;
}



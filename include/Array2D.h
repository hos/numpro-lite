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



#ifndef ARRAY2D_H_
#define ARRAY2D_H_


/** Template-Klasse zur Beschreibung von Matrizen
 *
 */
template < class T>
class Array2D
{

private:
  int                             size_1;             ///< Anzahl Zeilen
  int                             size_2;             ///< Anzahl Spalten
  T*                              data;               ///< Zeiger auf den Inhalt der Matrix


public:


  /** Konstruktor fuer eine Matrix der Groesse Null
   *
   */
  Array2D( )
  {
    size_1 = 0;
    size_2 = 0;
    data   = NULL;
  }




  /** Konstruktor fuer eine Matrix mit gegebener Groesse
   *  Die Daten werden NICHT initialisiert!!
   *
   */
  Array2D(
      int                         s1,                 ///< Anzahl Zeilen (i)
      int                         s2                  ///< Anzahl Spalten (i)
      )
  {
    size_1 = s1;
    size_2 = s2;
    data   = (s1!=0 && s2!=0) ? new T[s1*s2] : NULL;
  }




  /** Kopier-Konstruktor
   *  Erzeugt eine Kopie einer Matrix, der Inhalt wird einzeln kopiert.
   *
   */
  Array2D(
      Array2D&                    src                 ///< Vorlage fuer die Kopie (i)
      )
  {
    size_1 = src.size_1;
    size_2 = src.size_2;
    data   = (src.size_1!=0 && src.size_2!=0) ? new T[src.size_1*src.size_2] : NULL;

    for(int r=0; r<size_1; r++)
      for(int c=0; c<size_2; c++)
        (*this)[r][c] = src[r][c];
  }




  /** Kopier-Konstruktor
   *  Erzeugt eine Kopie eines Vektors, der Inhalt wird einzeln kopiert.
   *
   */
  Array2D(
      Array2D const&              src                 ///< Vorlage fuer die Kopie (i)
      )
  {
    size_1 = src.size_1;
    size_2 = src.size_2;
    data   = (src.size_1!=0 && src.size_2!=0) ? new T[src.size_1*src.size_2] : NULL;

    for(int r=0; r<size_1; r++)
      for(int c=0; c<size_2; c++)
        (*this)[r][c] = src[r][c];
  }




  /** Destruktor
   *  Inhalt wird geloescht.
   *
   */
  ~Array2D()
  {
    if (size_1 != 0 && size_2 != 0)
      delete [] data;
  }




  /** Inhalt wird geloescht.
   *
   */
  void cleanup()
  {
    if (size_1 != 0 && size_2 != 0)
    {
      delete [] data;
      data = NULL;
    }
    size_1 = 0;
    size_2 = 0;

    return;
  }




  /** Zugriffs-Operator
   *  Gibt den Inhalt eines Vektors fuer einen gegebenen Index zurueck.
   *
   */
  inline T* operator[](int i) {return (data + (size_2*i));}
  inline T const*const operator[](int i) const {return (data + (size_2*i));}




  /** Zuweisungs-Operator
   *
   */
  Array2D<T> operator= (
      Array2D<T> const&           v2                  ///< rechte Seite fuer die Zuweisung
      )
  {
    if (this == &v2)
      return *this;

    delete[] data;
    data   = 0;
    size_1 = v2.size_1;
    size_2 = v2.size_2;
    data   = (T*) new  T[size_1*size_2];

    for(int r=0; r<this->size_1; r++)
      for(int s=0; s<this->size_2; s++)
        (*this)[r][s] = v2[r][s];
    return *this;
  }




  /** Additions-Operator +
   *  Addiert den Inhalt von zwei Matrizen.
   *  Es wird geprueft, ob beide Matrizen dieselbe Groesse haben.
   *
   */
  Array2D<T> operator+ (
      Array2D const&              v2                  ///< zweiter Summand (i)
      )
  {
    Array2D<T> result(this->size_1, this->size_2);
    for(int r=0; r<this->size_1; r++)
      for(int s=0; s<this->size_2; s++)
        result[r][s] = (*this)[r][s] + v2[r][s];
    return result;
  }




  /** Additions-Operator +=
   *  Addiert den Inhalt von zwei Matrizen.
   *  Es wird geprueft, ob beide Matrizen dieselbe Groesse haben.
   *
   */
  Array2D<T> operator+= (
      Array2D const&              v2                  ///< zweiter Summand (i)
      )
  {
    for(int r=0; r<this->size_1; r++)
      for(int s=0; s<this->size_2; s++)
        (*this)[r][s] = (*this)[r][s] + v2[r][s];
    return *this;
  }




  /** Subtraktions-Operator -
   *  Subtrahiert den Inhalt von zwei Matrizen.
   *  Es wird geprueft, ob beide Matrizen dieselbe Groesse haben.
   *
   */
  Array2D<T> operator- (
      Array2D const&              v2                  ///< Subtrahend (i)
      )
  {
    Array2D<T> result(this->size_1, this->size_2);
    for(int r=0; r<this->size_1; r++)
      for(int s=0; s<this->size_2; s++)
        result[r][s] = (*this)[r][s] - v2[r][s];
    return result;
  }




  /** Subtraktions-Operator -=
   *  Subtrahiert den Inhalt von zwei Matrizen.
   *  Es wird geprueft, ob beide Matrizen dieselbe Groesse haben.
   *
   */
  Array2D<T> operator-= (
      Array2D const&              v2                  ///< Subtrahend (i)
      )
  {
    for(int r=0; r<this->size_1; r++)
      for(int s=0; s<this->size_2; s++)
        (*this)[r][s] = (*this)[r][s] - v2[r][s];
    return *this;
  }




  /** Multiplikations-Operator *
   *  Es wird geprueft, ob beide Matrizen dieselbe Groesse haben.
   *
   */
  Array2D<T> operator* (
      Array2D const&              v2                  //< rechter Faktor (Multiplikand) (i)
      )
  {
    Array2D<T> result(this->size_1, v2.size_2);
    for(int r=0; r<this->size_1; r++)
      for(int s=0; s<v2.size_2; s++)
      {
        result[r][s] = 0;
        for(int t=0; t<v2.size_1; t++)
          result[r][s] += (*this)[r][t] * v2[t][s];
      }
    return result;
  }




  /** Vorzeichen-Operator -
   *  Negiert alle Eintraege der Matrix.
   *
   */
  Array2D<T> operator- ( )
  {
    Array2D<T> result(this->size_1, this->size_2);
    for(int r=0; r<this->size_1; r++)
      for(int s=0; s<this->size_2; s++)
        result[r][s] = -(*this)[r][s];
    return result;
  }




  // Skalare Multiplikation
  template <class U>
  friend Array2D<U> operator* (double fac, Array2D<U> const& a);




  // Skalare Multiplikation
  template <class U>
  friend Array2D<U> operator* (Array2D<U> const& a, double fac);




  // Vektor Matrix Multiplikation
  template <class U>
  friend Array1D<U> operator* (Array1D<U> const& vec, Array2D<U> const& a);




  // Matrix Vektor Multiplikation
  template <class U>
  friend Array1D<U> operator* ( Array2D<U> const& a, Array1D<U> const& vec);




  /** Groesse der Matrix veraendern
   *  Veraendert die Groesse der Matrix, dabei wird der Inhalt erhalten.
   *  Wird die Matrix verkleinert, kann Inhalt verloren gehen.
   *
   */
  void resize(
      size_t                      s1,                 ///< neue Zeilenanzahl (i)
      size_t                      s2                  ///< neue Spaltenanzahl (i)
      )
  {
    bool save = false;
    T * old_data = NULL;
    int old_s2 = size_2;
    int old_s1 = size_1;

    // save old data
    if (size_1*size_2 > 0)
    {
      old_data = (T*) new  T[size_1*size_2];
      for(int r=0;r<size_1;r++)
        for(int s=0;s<size_2;s++)
        old_data[r*old_s2 + s] = (*this)[r][s];
      save = true;
    }

    delete [] data;
    data   = 0;
    size_1 = s1;
    size_2 = s2;
    data   = (T*) new  T[size_2*size_1];

    // restore old data
    if (save)
    {
      for(int r=0;r<size_1;r++)
        for(int s=0;s<size_2;s++)
          (*this)[r][s] = ( r >= old_s1 || s >= old_s2 ) ? 0 : old_data[r*old_s2 + s];
      delete[] old_data;
    }

    return;
  }




  /** Initialisiert eine Matrix
   *  Es werden alle Eintraege zu Null (0) gesetzt.
   *
   */
  inline void init(T v = 0)
  {
    for(int r=0;r<size_1;++r)
      for(int c=0;c<size_2;++c)
        (*this)[r][c] = v;
    return;
  }




  /** Initialisiert eine Matrix zur Einheitsmatrix
   *  Es werden alle Eintraege zu Null (0) gesetzt und die
   *  Hauptdiagonaleintraege zu Eins.
   *
   */
  inline void set_identity()
  {
    for (int r = 0; r <size_1; r++)
    {
      for(int s = 0; s < size_2; s++)
      {
        if (r == s)
          (*this)[r][s] = 1.0 ;
        else
          (*this)[r][s] = 0.0 ;
      }
    }
    return;
  }




  /** Gibt die Transponierte einer Matrix zurueck
   *
   */
  Array2D<T> transpose ( )
  {
    Array2D<T> result(this->size_2, this->size_1);
    for(int r=0; r<this->size_1; r++)
      for(int s=0; s<this->size_2; s++)
        result[s][r] = (*this)[r][s];
    return result;
  }




  /** Ausgabe der Matrix auf den Bildschirm
   *
   */
  inline void print()
  {
    printf("\n");
    for (int r=0; r<size_1; r++)
    {
      for (int c=0; c<size_2; c++)
        printf("%16.8e  ",(*this)[r][c]);
      printf("\n");
    }
    printf("\n");
  }




  /** Ausgabe der Maske der Matrix auf den Bildschirm
   *  Fuer alle Eintraege deren Betrag groesser als 1e-08 ist,
   *  wird ein 'X' ausgegeben.
   *
   */
  inline void print_mask()
  {
    printf("\n");
    for (int r=0; r<size_1; r++)
    {
      for (int c=0; c<size_2; c++)
        printf("%1s", fabs( (*this)[r][c]) > 1e-8? "X":" " );
    printf("\n");
    }
    printf("\n");
  }




  /** Ausgabe der Matrix auf den Bildschirm
   *
   */
  inline void print(
      char*                       name                ///< Bezeichnung der Matrix (i)
      )
  {
    printf("%s\n",name);
    for (int r=0; r<size_1; r++)
    {
      for (int c=0; c<size_2; c++)
        printf("%16.8e  ",(*this)[r][c]);
      printf("\n");
    }
    printf("\n");
  }




  /** Rueckgabe der Anzahl der Zeilen der Matrix
   *
   */
  int get_size_1() const
  {
    return size_1;
  }




  /** Rueckgabe der Anzahl der Spalten der Matrix
   *
   */
  int get_size_2() const
  {
    return size_2;
  }



  Array2D<T> inverse ( );



};





/** skalare Multiplikation von links
 *  Multipliziert eine Matrix von links mit einem Skalar.
 *  Jeder Eintrag wird mit dem Skalar multipliziert.
 *
 */
template <class U>
Array2D<U> operator*(
    double                        fac,                ///< skalarer Faktor (i)
    Array2D<U> const&             a                   ///< zu multiplizierende Matrix (i)
    )
{
  Array2D<U> result(a.size_1, a.size_2);
  for(int r=0;r<a.size_1;r++)
     for(int s=0;s<a.size_2;s++)
       result[r][s] = fac * a[r][s];
  return result;
}




/** skalare Multiplikation von rechts
 *  Multipliziert eine Matrix von rechts mit einem Skalar.
 *  Jeder Eintrag wird mit dem Skalar multipliziert.
 *
 */
template <class U>
Array2D<U> operator*(
    Array2D<U> const&             a,                  ///< zu multiplizierende Matrix (i)
    double                        fac                 ///< skalarer Faktor (i)
    )
{
  Array2D<U> result(a.size_1, a.size_2);
  for(int r=0;r<a.size_1;r++)
     for(int s=0;s<a.size_2;s++)
       result[r][s] = a[r][s] * fac;
  return result;
}




/** Matrix-Vektor-Multiplikation
 *  Multipliziert eine Matrix von rechts mit einem Vektor.
 *
 */
template <class U>
Array1D<U> operator* (
    Array2D<U> const&             a,                  ///< zu multiplizierende Matrix (i)
    Array1D<U> const&             vec                 ///< Vektor (i)
    )
{
  Array1D<U> result(a.size_1);
  result.init();
  for(int r=0;r<a.size_1;r++)
     for(int s=0;s<a.size_2;s++)
       result[r] += a[r][s] * vec[s];

  return result;
}



#endif /* ARRAY2D_H_ */



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



#ifndef ARRAY1D_H_
#define ARRAY1D_H_


template <class U>
class Array2D;

/** Template-Klasse zur Beschreibung von Vektoren
 *
 *
 */
template <class V>
class Array1D
{

private:
  int                        size;               ///< Groesse des Vektors
  V*                         data;               ///< Zeiger auf den Inhalt des Vektors


public:


  /** Konstruktor fuer einen Vektor der Laenge Null
   *
   */
  Array1D ( )
  {
    size       = 0;
    data       = NULL;
  }




  /** Konstruktor fuer einen Vektor mit gegebener Laenge
   *  Die Daten werden NICHT initialisiert!!
   *
   */
  Array1D (
      int                    s                   ///< Laenge des neuen Vektors (i)
      )
  {
    size       = s;
    data       = (V*) new V[s];
  }




  /** Kopier-Konstruktor
   *  Erzeugt eine Kopie eines Vektors, der Inhalt wird einzeln kopiert.
   *
   */
  Array1D (
      Array1D const&         v2                  ///< Vorlage fuer die Kopie (i)
      )
  {
    size      = v2.get_size();
    data      = (V*) new V[size];

    for(int r=0; r<size; r++)
      (*this)[r] = v2[r];
  }




  /** Destruktor
   *  Inhalt wird geloescht.
   *
   */
  ~Array1D ()
  {
    if (size != 0)
      delete [] data;
  }




  /** Inhalt wird geloescht.
   *
   */
  void cleanup()
  {
    if (size != 0)
    {
      delete [] data;
      data = NULL;
    }
    size = 0;

    return;
  }



  V* get_dataptr()
  {
    return data;
  }



  /** Zugriffs-Operator
   *  Gibt den Inhalt eines Vektors fuer einen gegebenen Index zurueck.
   *  Es wird geprueft, ob die Laenge des Vektors eingehalten wird.
   *
   */
  inline V &operator[](
      int const&             index               ///< Index des gewuenschten Elements (i)
      )
  {
    if (index > size - 1 || index < 0 )
    {
      cerr << "Laufzeitfehler: Vektorindex " << index << " ungueltig!" << endl;
      exit (EXIT_FAILURE);
    }

    return data [ index ];
  }




  /** Zugriffs-Operator
   *  Gibt den Inhalt eines Vektors fuer einen gegebenen Index zurueck.
   *  Es wird geprueft, ob die Laenge des Vektors eingehalten wird.
   *
   */
  inline V &operator[](int const& index) const
  {
    if (index > size - 1) {
      cerr << "Laufzeitfehler: Vektorindex " << index << " ungueltig!" << endl;
      exit (EXIT_FAILURE);
    }

    return data [ index ];
  }




  /** Zuweisungs-Operator
   *
   */
  Array1D<V> operator= (
      Array1D<V> const&      v2                  ///< rechte Seite fuer die Zuweisung (i)
      )
  {
    if (this == &v2)
      return *this;

    delete[] data;
    data   = 0;

    size        = v2.get_size();
    data        = (V*) new  V[size];

    for(int r=0; r<size; r++)
      data[r] = v2[r];
    return *this;
  }




  /** Additions-Operator +
   *  Addiert den Inhalt von zwei Vektoren.
   *  Es wird geprueft, ob beide Vektoren dieselbe Laenge haben.
   *
   */
  Array1D<V> operator+ (
      Array1D<V> const&      v2                  ///< zweiter Summand (i)
      )
  {
    Array1D<V> result(size);
    for(int r=0; r<size; r++)
      result.data[r] = (*this)[r] + v2[r];
    return result;
  }




  /** Additions-Operator +=
   *  Addiert den Inhalt von zwei Vektoren.
   *  Es wird geprueft, ob beide Vektoren dieselbe Laenge haben.
   *
   */
  Array1D<V> operator+= (
      Array1D<V> const&      v2                  ///< zweiter Summand (i)
      )
  {
    for(int r=0; r<size; r++)
      (*this)[r] = (*this)[r] + v2[r];
    return *this;
  }




  /** Subtraktions-Operator -
   *  Subtrahiert den Inhalt von zwei Vektoren.
   *  Es wird geprueft, ob beide Vektoren dieselbe Laenge haben.
   *
   */
  Array1D<V> operator- (
      Array1D<V> const&      v2                  ///< Subtrahend (i)
      )
  {
    Array1D<V> result(size);
    for(int r=0; r<size; r++)
      result.data[r] = (*this)[r] - v2[r];
    return result;
  }




  /** Subtraktions-Operator -=
   *  Subtrahiert den Inhalt von zwei Vektoren.
   *  Es wird geprueft, ob beide Vektoren dieselbe Laenge haben.
   *
   */
  Array1D<V> operator-= (
      Array1D<V> const&      v2                  ///< Subtrahend (i)
      )
  {
    for(int r=0; r<size; r++)
      (*this)[r] = (*this)[r] - v2[r];
    return *this;
  }




  /** Vorzeichen-Operator -
   *  Negiert alle Eintraege des Vektors.
   *
   */
  Array1D<V> operator- ()
  {
    Array1D<V> result(size);
    for(int r=0; r<size; r++)
      result[r] = -(*this)[r];
    return result;
  }




  /** Multiplikations-Operator *
   *  Bildet das Skalar-Produkt von zwei Vektoren.
   *  Es wird geprueft, ob beide Vektoren dieselbe Laenge haben.
   *
   */
  V operator* (
      Array1D<V> const&      v2                  ///< rechter Faktor (Multiplikand) (i)
      )
  {
    V result = 0;
    for(int r=0; r<size; r++)
      result += (*this)[r] * v2[r];
    return result;
  }




  // Skalare Multiplikation
  template <class U>
  friend Array1D<U> operator* (double fac, Array1D<U> const& vec);


  template <class U>
  friend Array1D<U> operator* (Array1D<U> const& vec, double fac);




  /** Laenge des Vektor veraendern
   *  Veraendert die Laenge des Vektors, dabei wird der Inhalt erhalten.
   *  Wird der Vektor verkuerzt, kann Inhalt verloren gehen.
   *
   */
  void resize (
      int                    s                   ///< neue Laenge des Vektors (i)
      )
  {
    /* Fallunterscheidung
     * 1. Groesse bleibt unveraendert s == size
     * 2. Vektor wird laenger oder kuerzer
     */


    if ( s == size )
    {
      // Fall 1: Groesse bleibt unveraendert
      //=====================================

      // nichts zu tun!!
      return;
    }
    else if ( s != size )
    {
      // Fall 2: Liste wird laenger oder kuerzer
      //=========================================


      // alten Inhalt abspeichern
      V* old_data = (V*) new V[size];
      for(int r=0; r<size; r++)
        old_data[r] = data[r];


      // alten Inhalt loeschen
      delete[] data;
      data      = 0;

      // neuen Inhalt anlegen
      data        = (V*) new V[s];


      // alten Inhalt wiederherstellen
      if (size > s)
      {
        // Vektor wird kleiner, Inhalt wird fuer neue Laenge kopiert
        for(int r=0; r<s; r++)
          data[r] = old_data[r];
      }
      else
      {
        // Vektor wird groesser, Inhalt wird fuer alte Laenge kopiert
        for(int r=0; r<size; r++)
          data[r] = old_data[r];
        // neue Eintraege werden initialisiert
        for(int r=size; r<s; r++)
          data[r] = 0;
      }


      // neue Laenge wird gesetzt
      size        = s;

      delete[] old_data;
      return;
    }

  }




  /** Initialisiert einen Vektor
   *  Es werden alle Eintraege zu Null (0) gesetzt.
   *
   */
  inline void init ()
  {
    for(int r=0; r<size; r++)
      (*this)[r] = 0;

    return;
  }




  /** Initialisiert einen Vektor
   *  Es werden alle Eintraege zum gegebenen Wert gesetzt.
   *
   */
  inline void init (
      V                      val                 ///< vorgegebener Wert (i)
  )
  {
    for(int r=0; r<size; r++)
      (*this)[r] = val;

    return;
  }




  /** Ausgabe des Vektors auf den Bildschirm
   *
   */
  inline void print ()
  {
    printf("\n");
    for (int r=0; r<size; r++)
      printf("%16.8e\n",(*this)[r]);
    printf("\n");
    return;
  }




  /** Ausgabe des Vektors auf den Bildschirm
   *
   */
  inline void print_int ()
  {
    printf("\n");
    for (int r=0; r<size; r++)
      printf("%6i\n",(*this)[r]);
    printf("\n");
    return;
  }




  /** Ausgabe des Vektors auf den Bildschirm
   *
   */
  void print (
      char*                  name                ///< Bezeichnung des Vektors (i)
      )
  {
    printf("%s\n",name);
    for (int r=0; r<size; r++)
      printf("%16.8e\n",(*this)[r]);
    printf("\n");
    return;
  }





  /** Ausgabe des Vektors auf den Bildschirm
   *
   */
  void print_int (
      char*                  name                ///< Bezeichnung des Vektors (i)
      )
  {
    printf("%s\n",name);
    for (int r=0; r<size; r++)
      printf("%6i\n",(*this)[r]);
    printf("\n");
    return;
  }




  /** Rueckgabe der Laenge des Vektor
   *
   */
  int get_size() const
  {
    return size;
  }


};


/** skalare Multiplikation von links
 *  Multipliziert einen Vektor von links mit einem Skalar.
 *  Jeder Eintrag wird mit dem Skalar multipliziert.
 *
 */
template <class U>
Array1D<U> operator*(
    double                   fac,                ///< skalarer Faktor (i)
    Array1D<U> const&        vec                 ///< zu multiplizierender Vektor (i)
    )
{
  Array1D<U> result(vec.get_size());
  for(int r=0; r<vec.get_size(); r++)
    result[r] = fac * vec[r];
  return result;
}




/** skalare Multiplikation von rechts
 *  Multipliziert einen Vektor von rechts mit einem Skalar.
 *  Jeder Eintrag wird mit dem Skalar multipliziert.
 *
 */
template <class U>
Array1D<U> operator*(
    Array1D<U> const&        vec,                ///< zu multiplizierender Vektor (i)
    double                   fac                 ///< skalarer Faktor (i)
    )
{
  Array1D<U> result(vec.get_size());
  for(int r=0; r<vec.get_size(); r++)
    result[r] = vec[r] * fac;
  return result;
}

/** Dyadenprodukt aus 2 Vektoren ergibt Array2D */
template <class U>
Array2D<U> operator% (Array1D<U> const& v1, Array1D<U> const& v2)
{
  Array2D<U> result(v1.get_size(),v2.get_size());
  for(int r=0; r<v1.get_size(); r++)
  {
    for(int p=0; p<v2.get_size(); p++)
    {
      result[r][p] = v1[r] * v2[p];
    }
  }
  return result;
}

#endif /* ARRAY1D_H_ */



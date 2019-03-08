#include <iostream>
#include <string>
#include <array>
#include <fstream> // pour les fichiers
#include <sstream> // pour utiliser un string comme un flux


const int MAX_ALPHA = 256;
const int MAX_ETAT = 256;

using T_acceptant = std::array <bool, MAX_ETAT>; // tableau de booléens indicé sur les numéros des états 
using T_ligne = std::array <int, MAX_ALPHA>; // tableau d'entiers
using T_matrice = std::array <T_ligne, MAX_ETAT>; // matrice de transitions: tableau à 2 dimensions indicé sur les numéros des états et sur les indices des caractères dans l'alphabet

struct T_afd  { // automate
  std::string alpha; 		// alphabet : tableau de caractères 'alpha'
  int nb_etats;			// nombre d'états 
  T_acceptant acceptant;		// états acceptants : tableau de booléens 'acceptant' indicé sur les numéros des états (0 .. nb_etats-1)
  T_matrice trans;	// matrice de transitions: tableau à 2 dimensions indicé sur les numéros des états (0 .. nb_etats-1) et sur les indices des caractères dans l'alphabet 'alpha' (0 .. alpha.length()-1)
};

bool lire_AFD(std::ifstream & file, T_afd & autom)
{
  /* Structure du fichier texte :
  * alphabet : suite de caractères sans séparateur
  * nbre d'états N 
  * numéros des états acceptants (séparés par des blancs)
  * matrice de transitions : les colonnes correspondent aux caractères dans l'ordre de l'alphabet
  * 	les lignes correspondent aux états 0 .. N-1
  * l'état 0 est l'état initial
  */
  int i,n;
  std::string ligne;
  
  // lecture alphabet
  std::getline(file,autom.alpha); // lecture d'une ligne entière 
  
  // lecture nombre d'états
  file >> autom.nb_etats; // lecture d'un entier
  std::getline(file,ligne); // passage à la ligne
  
  // initialisation des états acceptants puis lecture
  for (i=0; i<autom.nb_etats; ++i)
    autom.acceptant[i] = false;
  std::getline(file,ligne); // lecture de la ligne entière
  std::istringstream fluxligne(ligne); // on transforme la ligne en un flux
  while (fluxligne >> n) // on lit les entiers de la ligne
  {
    autom.acceptant[n] = true;
  }
  
  // lecture matrice de transitions
  for (i=0; i<autom.nb_etats; ++i)
  {
    for (unsigned int j = 0; j<autom.alpha.length(); ++j)
    {
      file >> autom.trans[i][j];
    }
  }
  
  
  return true;
}


int indice_car(char c, std::string alpha)
{ //retourne l'indice de la 1ère occ. de c dans alpha, ou -1 sinon
  return alpha.find(c);
}

void affich_AFD(T_afd a) {
  //Affichage de l'Alphabet
  std::cout << "Alphabet : " << a.alpha << std::endl;
  //Affichage du Nombre d'états 
  std::cout << "Nombre d'état : " << a.nb_etats << std::endl;
  //Affichage des états acceptants 
  std::cout <<"Etats Acceptants : ";
  for(int i=0;i<a.nb_etats;i++){
    if(a.acceptant[i]){
      std::cout<<i<<" ";
    }
  }
  std::cout<<std::endl;
  //Affichage matrice de transition
  
  std::cout <<"matrice : "<<std::endl;
  std::cout << "  ";
  for(unsigned int i=0; i<a.alpha.size();i++) {
    std::cout << a.alpha[i] << " ";
  }
  std::cout << std::endl;
  for(int i=0;i<a.nb_etats;i++){
    std::cout << i << " ";
    for(int j=0;j<a.alpha.size();j++){
      std::cout << a.trans[i][j]<<" ";
    }
    std::cout<<std::endl;
  }
  
}
// non fonctionel 
bool reconnue (T_afd a, std::string b) {
  int etat = 0;
  /*for(int i=0; i<a.size(); i++){
    if () {
      
      
    }
  }*/
  if (etat == a.acceptant[etat]) {
    return true;
  }
  else if(indice_car(a.alpha, b[0]) != b[0]) {
    return false;
  }
}

int main(int argc, char **argv)
{
  if ( argc < 2 )
  {
    std::cout << "Usage : " << argv[0] << " NOM_DU_FICHIER\n";
    return (EXIT_FAILURE);
  }
  
  std::ifstream f;
  std::string nom_fich = argv[1];
  
  T_afd autom;
  std::string a = "ababab";
  std::string b = "bababa";
  
  f.open(nom_fich, std::ios::in); // ouverture du fichier en lecture
  if (!f)
  {
    std::cout<<"impossible d'ouvrir le fichier"<<std::endl;
    return(EXIT_FAILURE);
  }
  lire_AFD(f,autom);
  f.close();
  
  affich_AFD(autom);
  if (reconnue(autom,a) == false) {
    std::cout << "-1" << std::endl;
  }
  else {
    std::cout << "1" << std::endl;
  }
  if (reconnue(autom,b) == false) {
    std::cout << "-1" << std::endl;
  }
  else {
    std::cout << "1" << std::endl;
  }
  
  return(EXIT_SUCCESS);
}

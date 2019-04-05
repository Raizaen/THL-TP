#include <iostream>
#include <string>
#include <array>
#include <fstream> // pour les fichiers


const int MAX_ALPHA = 256;
const int MAX_ETAT = 256;

using T_acceptant = std::array <bool, MAX_ETAT>; // tableau de booléens indicé sur les numéros des états 
using T_ligne = std::array <int, MAX_ALPHA>; // tableau d'entiers
using T_matrice = std::array <T_ligne, MAX_ETAT>; // matrice de transitions: tableau à 2 dimensions indicé sur les numéros des états et sur les indices des caractères dans l'alphabet

struct T_afd  { // automate
	std::string alpha; 		// alphabet : tableau de caractères 'alpha' 
	T_acceptant acceptant;		// états acceptants : tableau de booléens 'acceptant' indicé sur les numéros des états (0 .. nb_etats-1)
	T_matrice trans;	// matrice de transitions: tableau à 2 dimensions indicé sur les numéros des états (0 .. nb_etats-1) et sur les indices des caractères dans l'alphabet 'alpha' (0 .. alpha.length()-1)
};

/***************************************************************/
/* création de l'AFD					       */
/***************************************************************/

/* fonctions à écrire */ 
bool suffixe(std::string motif, int j, int k, char x)
{ // retourne true si motif[0..j-1] est suffixe de motif[0..k-1]x
  std::string new_motif = "";
  for(int l=0; l<k-1; l++) {
    new_motif += motif[l];
  }
  new_motif += x;
  
  for(int i=0; i<j/*-1*/; i++) {
    if (motif[i] != new_motif[k-j+i+1]) { //problème calcul new_motif
      return 0;
    }
  }
 return 1;
}

int min (int a, int b){
  if(a < b) return a;
  return b;
}


int delta(std::string motif, int k, char x)
{ // retourne l'état obtenu en partant de k et en lisant x
  int j = min(k+1, motif.length());
  
  while (!suffixe(motif, j, k, x)) {
    j--;
  }
  return j;
}

void creer_AFD(std::string motif, T_afd & autom)
{ // création d'un AFD pour sigma*motif
	int i,j, m,n;
	m = motif.length();// taille du motif
	//alphabet : on y met explicitement les lettres du motif, les autres provoquent des transitions vers l'état initial 0
	j=0;
	autom.alpha="";
	for (i=0; i<m; ++i)
	{
		if (autom.alpha.find(motif[i]) == std::string::npos) //retourne l'indice de la 1ère occ. du caractère dans alpha, ou std::string::npos (-1) sinon
		{ 
			autom.alpha += motif[i];
			++j;
		}
	}
	n = j;// taille de alphabet
	std::cout << "Alphabet  : " << autom.alpha << std::endl;
	// initialisation des états acceptants 
	for (i=0; i<m; ++i)
		autom.acceptant[i] = false;
	autom.acceptant[m] = true;
	//  matrice de transitions
	for (i=0; i<m+1; ++i) // les (m+1) états sont numérotés de 0 à m
	{ 
		for (j = 0; j<n; ++j) // les indices des caractères de l'alphabet
		{ 
			autom.trans[i][j] = delta(motif,i,autom.alpha[j]);
			std::cout << "trans[" << i <<"," << j <<"] = " << autom.trans[i][j] << std::endl;
		}
		autom.trans[i][n] = 0; // transitions pour les lettres n'appartenant pas au motif
		std::cout << "trans[" << i <<"," << n <<"] = " << 0 << std::endl;
	}
}

/***************************************************************/
/* recherche du motif en utilisant l'AFD		       */
/***************************************************************/


int indice_car(char c, std::string alpha)
{ //retourne l'indice de c dans alpha, ou alpha.length() sinon
	int res = alpha.find(c); //retourne l'indice de la 1ère occ. de c dans alpha, ou -1 sinon
	if (res != -1)
		return (res);
	else
		return(alpha.length()); // car. n'appartenant pas au motif (donc non référencé dans alpha)
}


/* fonction à écrire */
int recherche_afd(int noligne, std::string texte, T_afd autom)
{ // on recherche toutes les occurrences du motif dans 'texte' grace à l'afd
  // retourne le nombre de "comparaisons" = longueur du texte
  return 1;
}



/***************************************************************/
/* création de l'AFD et recherche du motif 		       */
/***************************************************************/

int recherche_afd_fichier(std::string nom_fich, std::string motif)
{ // recherche toutes les occurences de 'motif' dans le fichier texte 'nom_fich'
  // retourne le nombre de comparaisons effectuées, ou -1 si erreur
	T_afd autom; // l'automate
	std::ifstream f; 
	std::string texte;
	int nb_comp = 0; 		// nombre de comparaisons de caractères effectuées 
	int noligne = 1; 		// numero de ligne

	creer_AFD(motif, autom);

	f.open(nom_fich, std::ios::in); // ouverture du fichier en lecture
	if (!f)
	{
		std::cout << "impossible d'ouvrir le fichier\n";
		return(-1);
	}
	while (std::getline(f,texte)) // lecture d'une ligne entière, retourne NULL si erreur
	{ 
		nb_comp += recherche_afd(noligne,texte,autom);
		noligne++;
	}
	f.close();
	return nb_comp;
}


int main(int argc, char **argv)
{
    	if ( argc < 2 )
	{
	    std::cout << "Usage: "<< argv[0] << " NOM_DU_FICHIER\n";
	    return EXIT_FAILURE;
	}

	std::string nom_fich = argv[1]; // le nom du fichier contenant le texte
	std::string motif;	 // le motif
	int nb_comp; 		// nombre de comparaisons


	std::cout << "Motif ? ";
	//ababc
	std::cin >>  motif;
	nb_comp = recherche_afd_fichier(nom_fich, motif);
	if (nb_comp >= 0 )
		std::cout << "nombre total de comparaisons : " << nb_comp << std::endl;

	return EXIT_SUCCESS;
}

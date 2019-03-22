#include <iostream>
#include <string>
#include <array>
#include <fstream> // pour les fichiers


/********************************************************************************/
/*                             recherche naive	                  							*/
/********************************************************************************/

/*** fonction à écrire
int recherche_naive_g(int noligne, std::string texte, std::string motif)
{
// on recherche toutes les occurrences de 'motif' dans 'texte'
// retourne le nombre de comparaisons

}
***/

int recherche_naive_g(int noligne, std::string texte, std::string motif) {
  
  // on recherche toutes les occurrences de 'motif' dans 'texte'
  // retourne le nombre de comparaisons
  
  int nb_comp_g = 0;
  
  int T = texte.length(), M = motif.length();
  for (int i=0; i<=T-M; i++) {
    int j=0;
    while (j<M && motif[j] == texte[i+j]){
      nb_comp_g++;
      if(j==M-1) std::cout << "G Motif trouvé en: "<< i+1 << ", ligne : " << noligne << std::endl;
      j++;
    
    }
    if (j < M) {
      nb_comp_g++;
    }
  }
  //std::cout << "Nombre d'occurrences du motif : " << j << std::endl;
  return nb_comp_g;
}

int recherche_naive_d(int noligne, std::string texte, std::string motif) {
  
  // on recherche toutes les occurrences de 'motif' dans 'texte'
  // retourne le nombre de comparaisons
  
  int nb_comp_d = 0;
  
  int T = texte.length(), M = motif.length();
  for (int i=0; i<=T-M; i++) {
    int j=M-1;
    while (j>=0 && motif[j] == texte[i+j]){
      nb_comp_d++;
      j--;
      if(j==0) std::cout << "D Motif trouvé en: "<< i+1 << ", ligne : " << noligne << std::endl;
      
    }
    if (j > 0) {
      nb_comp_d++;
    }
  }
  //std::cout << "Nombre d'occurrences du motif : " << j << std::endl;
  return nb_comp_d;
}

long recherche_naive_fichier_g(std::string nom_fich, std::string motif){
// recherche toutes les occurrences de 'motif' dans le fichier texte 'nom_fich'
// retourne le nombre de comparaisons effectuées, ou -1 si erreur

std::ifstream f;
std::string texte;
long nb_comp_g = 0; // nombre de comparaisons de caractères effectuées
int noligne = 1; // numero de ligne

	f.open(nom_fich, std::ios::in); // ouverture du fichier en lecture
	if (!f)
	{
		std::cout << "impossible d'ouvrir le fichier\n";
		return(-1);
	}

	// recherche en examinant le motif à partir de la gauche
	while (std::getline(f,texte))// lecture de la ligne entière, retourne false si erreur
	{
		nb_comp_g += recherche_naive_g(noligne,texte,motif);
		noligne++;
	}
	  
	f.close();
	return nb_comp_g;
}

long recherche_naive_fichier_d(std::string nom_fich, std::string motif){
  // recherche toutes les occurrences de 'motif' dans le fichier texte 'nom_fich'
  // retourne le nombre de comparaisons effectuées, ou -1 si erreur
  
  std::ifstream f;
  std::string texte;
 // nombre de comparaisons de caractères effectuées
  long nb_comp_d = 0;
  int noligne = 1; // numero de ligne
  
  f.open(nom_fich, std::ios::in); // ouverture du fichier en lecture
  if (!f)
  {
    std::cout << "impossible d'ouvrir le fichier\n";
    return(-1);
  }
  
  // recherche en examinant le motif à partir de la gauche
  while (std::getline(f,texte))// lecture de la ligne entière, retourne false si erreur
  {
    nb_comp_d += recherche_naive_d(noligne,texte,motif);
    noligne++;
  }
  
  f.close();
  return nb_comp_d;
}

int main(int argc, char **argv)
{
	if ( argc < 2 )
	{
		std::cout << "Usage: "<< argv[0] << " NOM_DU_FICHIER\n";
		return (EXIT_FAILURE);
	}

	std::string nom_fich = argv[1]; // le nom du fichier contenant le texte
	std::string motif; // le motif
	long nb_comp_g; // nombre de comparaisons
	long nb_comp_d;


	std::cout << "Motif ? ";
	std::getline(std::cin, motif); 
	nb_comp_g = recherche_naive_fichier_g(nom_fich, motif);
	std::cout << std::endl;
	nb_comp_d = recherche_naive_fichier_d(nom_fich, motif);
	std::cout << std::endl;
	if (nb_comp_g >= 0 )
		std::cout << "nombre de comparaisons (gauche/droite): " << nb_comp_g << std::endl;
	if (nb_comp_d >= 0 )
    std::cout << "nombre de comparaisons (droite/gauche):" << nb_comp_d << std::endl;
	return EXIT_SUCCESS;
}

/* oygtuababcyvfstrvsetdyrt
awqxrsetdybknababciftsceqsrdybuftnababcgyhuinc
  azqesababcrsbtzawcetrababctbynuhnsgdnyeqsvtgro
  ababcaqzersdioababctyhsvyuievnoirugvsababcodughvnou */
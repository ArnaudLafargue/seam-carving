#include "image.h"
#include "seam.h"

int main(int argc, char* argv[])
{


    Image<Color> I;
    if(! load(I, argc>1? argv[1]: srcPath("TEST10.png")))
    {
        std::cout << "Echec de lecture d'image" << std::endl;
        return 1;
    }
/*
    Image<byte> Vx(I.width(),I.height());
    Image<byte> Vy(I.width(),I.height());
    Image<byte> E(I.width(),I.height());
    Image<byte> Igrey=imagegrey(I);
    gradient(Igrey,Vx,Vy);


    openWindow(I.width(),I.height());
    display(I);
    click();
    display(Vx);
    click();
    display(Vy);
    click();
    energie(Vx,Vy,E);
    display(E);
    click();
    int seam_value=0;
    display(I);
*/

    // Choisir entre les deux bouts de code ci-dessous pour
    // enlever soit une colonne (1) soit une ligne (2)
    //1
/*
    std::vector<Coords<2>> seam_test=Bellman_vertical(E,seam_value);
    dessine(seam_test);
    std::cout << seam_value;
    click();
    Image<Color> test=ajoute_vertical(I,seam_test);
    display(test);
    click();
*/
    //2
/*
    std::vector<Coords<2>> seam_test=Bellman_horizontal(E,seam_value);
    dessine(seam_test);
    std::cout << seam_value;
    click();

    Image<Color> test=ajoute_horizontal(I,seam_test);
    Window W2 = openWindow(test.width(),test.height());
    setActiveWindow(W2);

    display(test);
    click();

*/



    // Permet de retirer 10 colonnes et 20 lignes de façon
    //"optimisée" , (il faut commenter (1) pour que cela fonctionne)

/*
    openWindow(I.width(),I.height());
    display(I);
    click();
    Image<Color> copie=add(I,50,0);
    Window W2 = openWindow(copie.width(),copie.height());
    setActiveWindow(W2);
    display(copie);
    click();
*/
    openWindow(I.width()+2,I.height());

    Image<Color> test =insertion_vertical(I,2);

    display(test);
    click();

    return 0;
}

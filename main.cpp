#include "image.h"
#include "seam.h"

int main(int argc, char* argv[])
{


    Image<Color> I;
    if(! load(I, argc>1? argv[1]: srcPath("TEST.png")))
    {
        std::cout << "Echec de lecture d'image" << std::endl;
        return 1;
    }

    Image<byte> Vx(I.width(),I.height());
    Image<byte> Vy(I.width(),I.height());
    Image<byte> E(I.width(),I.height());


    gradient(I,Vx,Vy);
    openWindow(I.width(),I.height());
    display(I);
    click();
    display(Vx);
    click();
    display(Vy);
    click();
    energie(Vx,Vy,E);
    display(E);
    click()
    int seam_value=0;
    display(I);
    
    // Choisir entre les deux bouts de code ci-dessous pour 
    // enlever soit une colonne (1) soit une ligne (2)
    //1
    std::vector<Coords<2>> seam_test=Bellman_vertical(E,seam_value);
    dessine(seam_test);
    std::cout << seam_value;
    click();
    Image<Color> test=assemble_vertical(I,seam_test);
    display(test);
    click();
    
    //2
    /*
    std::vector<Coords<2>> seam_test=Bellman_horizontal(E,seam_value);
    dessine(seam_test);
    std::cout << seam_value;
    click();
    Image<Color> test=assemble_horizontal(I,seam_test);
    display(test);
    click();
    */

    
    // Permet de retirer 10 colonnes et 20 lignes de façon 
    //"optimisée" , (il faut commenter (1) pour que cela fonctionne)
    /*
    openWindow(I.width(),I.height());
    display(I);
    click();
    Image<Color> copie=remove(I,10,20);
    Window W2 = openWindow(copie.width(),copie.height());
    setActiveWindow(W2);
    display(copie);
    click();

    */
    return 0;
}

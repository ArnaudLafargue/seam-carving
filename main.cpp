#include "image.h"
#include "seam.h"

int main(int argc, char* argv[])
{


    Image<Color> I;
    if(! load(I, argc>1? argv[1]: srcPath("TEST.png")))// On peut utiliser aussi salon.png ou eiffel.png
    {
        std::cout << "Echec de lecture d'image" << std::endl;
        return 1;
    }

    Image<byte> Vx(I.width(),I.height());
    Image<byte> Vy(I.width(),I.height());
    Image<byte> E(I.width(),I.height());

    gradient(I,Vx,Vy);
    openWindow(I.width(), I.height());
    display(I);
    click();
    display(Vx);
    click();
    display(Vy);
    click();
    energie(Vx,Vy,E);
    display(E);
    click();
/*
    int last_state=0;
    std::vector<Coords<2>> seam_test=Bellman_vertical(E,last_state);
    display(I);
    dessine(seam_test);
    click();
    Image<Color> copie=assemble_vertical(I,seam_test);
    display(copie);
    click();
    */

    Image<Color> I_=Transpose(I);
    Image<Color> copie=remove_vertical(I_,Vx,Vy,60);
    display(I);
    click();
    Window W1 = openWindow(copie.width(), copie.height());
    setActiveWindow(W1);
    display(copie);
    click();




    return 0;
}

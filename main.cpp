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
    int seam_value=0;
    display(I);
    std::vector<Coords<2>> seam_test=Bellman_vertical(E,seam_value);
    dessine(seam_test);
    std::cout << seam_value;
    click();
    Image<Color> test=assemble_horizontal(I,seam_test);
    display(test);
    click();

/*

    int last_state=0;
    std::vector<Coords<2>> seam_test=Bellman_vertical(E,last_state);
    display(It);
    dessine(seam_test);
    click();
    Image<Color> copie=assemble_vertical(It,seam_test);
    display(copie);
    click();

*/
/*
    openWindow(I.width(),I.height());
    display(I);
    Image<byte> Vx(I.width(),I.height());
    Image<byte> Vy(I.width(),I.height());
    gradient(I,Vx,Vy);
    Image<Color> copie=remove_vertical(I,Vx,Vy,10);


    click();
    Window W1 = openWindow(copie.width(),copie.height());
    setActiveWindow(W1);
    display(copie);

    click();
    Image<Color> copie2=remove_horizontal(I,Vx,Vy,10);
    Window W2 = openWindow(copie.width(),copie2.height());
    setActiveWindow(W2);
    display(copie2);
    click();

*/
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

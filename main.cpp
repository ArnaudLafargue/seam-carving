#include "image.h"
#include "seam.h"

int main(int argc, char* argv[])
{


    Image<Color> I;
    if(! load(I, argc>1? argv[1]: srcPath("TEST1.png")))
    {
        std::cout << "Echec de lecture d'image" << std::endl;
        return 1;
    }

    // TEST 1
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
    std::vector<Coords<2>> seam_test=Bellman_vertical(E,seam_value);
    dessine(seam_test);
    click();
    Image<Color> test=assemble_vertical(I,seam_test);
    display(test);
    click();

*/
    // TEST 2

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
    std::vector<Coords<2>> seam_test=Bellman_horizontal(E,seam_value);
    dessine(seam_test);
    click();
    Image<Color> test=assemble_horizontal(I,seam_test);
    display(test);
    click();
*/
    // TEST 3

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
    std::vector<Coords<2>> seam_test=Bellman_vertical(E,seam_value);
    dessine(seam_test);
    click();
    Image<Color> test=addseam_vertical(I,seam_test);
    display(test);
    click();
*/

    // TEST 4
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
    std::vector<Coords<2>> seam_test=Bellman_horizontal(E,seam_value);
    dessine(seam_test);
    click();
    Image<Color> test=addseam_horizontal(I,seam_test);
    display(test);
    click();
*/


    // TEST 5
/*
    openWindow(I.width(),I.height());
    display(I);
    Image<Color> test =remove(I,20,20);
    Window W2=openWindow(test.width(),test.height());
    setActiveWindow(W2);
    display(test);
    click();
*/

    // TEST 6
/*
    openWindow(I.width(),I.height());
    display(I);
    Image<Color> test =addVertical(I,40);
    Window W2=openWindow(test.width(),test.height());
    setActiveWindow(W2);
    display(test);
    click();
*/
    // TEST 7
/*
    openWindow(I.width(),I.height());
    display(I);
    Image<Color> test =addHorizontal(I,40);
    Window W2=openWindow(test.width(),test.height());
    setActiveWindow(W2);
    display(test);
    click();
*/
    return 0;
}

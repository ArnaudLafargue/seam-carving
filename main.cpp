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
    Image<byte> masque_(I.width(),I.height());
    load(masque_,srcPath("TEST12_masque.png"));
    openWindow(masque_.width(),masque_.height());
    display(masque_);
    click();
    Window W3=openWindow(I.width(),I.height());
    setActiveWindow(W3);
    display(I);
    click();
    Image<bool> masque(masque_.width(),masque_.height());
    for (int j=0;j<masque_.width();j++)
    {
        for (int i=0;i<masque_.height();i++)
        {
            if (masque_(j,i)!=255)
                masque(j,i)=true;
            else
                masque(j,i)=false;
        }
    }
    Image<Color> test = objet_removal(I,masque);
    Window W2=openWindow(test.width(),test.height());
    setActiveWindow(W2);
    display(test);
    click();


    // TEST 1
/*
    Image<byte> Vx(I.width(),I.height());
    Image<byte> Vy(I.width(),I.height());
    Image<int> E(I.width(),I.height());
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
    Image<int> E(I.width(),I.height());
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
    display(byte_(E));
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
    Image<int> E(I.width(),I.height());
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
    display(byte_(E));
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
    Image<int> E(I.width(),I.height());
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
    display(byte_(E));
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

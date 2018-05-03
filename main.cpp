#include "image.h"
#include <Imagine/Images.h>

using namespace Imagine;
using namespace std;

int main(int argc, char* argv[]) {
    Image<Color> I;
    const char* ficI = srcPath("demo-image0.jpg");
    if (! load(I, ficI)){
        cout << "Probleme chargement image..." << endl;
        return 1;
    }
    Image<byte> Ir, Ig, Ib;
    Window W = openWindow(I.width(), I.height());
    display(I);
    click();
    load(Ir, Ig, Ib, ficI);
    display(Ir); click();
    display(Ig); click();
    display(Ib); click();
    closeWindow(W);
    return 0;
}

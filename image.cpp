
#include "image.h"
#include <iostream>
const float POURCENT=0.5f;


Image<byte> image_bleue(Image<Color> F)
{
    Image<byte> I(F.width(),F.height());
    for (int i=0;i<F.height();i++)
    {
        for ( int j=0;j<F.width();j++)
        {
            I(j,i)=F(j,i).b();
        }
    }
    return I;
}
Image<byte> image_rouge(Image<Color> F)
{
    Image<byte> I(F.width(),F.height());
    for (int i=0;i<F.height();i++)
    {
        for ( int j=0;j<F.width();j++)
        {
            I(j,i)=F(j,i).r();
        }
    }
    return I;
}

Image<byte> image_vert(Image<Color> F)
{
    Image<byte> I(F.width(),F.height());
    for (int i=0;i<F.height();i++)
    {
        for ( int j=0;j<F.width();j++)
        {
            I(j,i)=F(j,i).g();
        }
    }
    return I;
}

Image<Color> reconstitue(Image<byte>I_r,Image<byte>I_g,Image<byte>I_b)
{
    Image<Color> A(I_r.width(),I_r.height());
    for (int i=0;i<A.height();i++)
    {
        for ( int j=0;j<A.width();j++)
        {
            A(j,i)=Color(I_r(j,i),I_g(j,i),I_b(j,i));
        }
    }
    return A;

}



byte norme2(Color C)
{
    return sqrt((C.r()*C.r()+C.g()*C.g()+C.b()*C.b())/3);
}

void gradient(const Image<Color>& I, Image<Color>& Vx, Image<Color>& Vy)
{
    Image<byte> I_r=image_rouge(I);
    Image<byte> I_g=image_vert(I);
    Image<byte> I_b=image_bleue(I);

    for (int i=0;i<I.height();i++)
    {
        for ( int j=0;j<I.width();j++)
        {
            Coords<2> pos(j,i);
            FVector<Color,2> grad;
            grad.x()=Color(gradient(I_r,pos).x(),gradient(I_g,pos).x(),gradient(I_b,pos).x());
            grad.y()=Color(gradient(I_r,pos).y(),gradient(I_g,pos).y(),gradient(I_b,pos).y());
            Vx(j,i)=grad.x();
            Vy(j,i)=grad.y();
        }
    }
}

void gradient(const Image<Color>& I, Image<byte>& Vx, Image<byte>& Vy)
{

    for (int i=0;i<I.height();i++)
    {
        for ( int j=0;j<I.width();j++)
        {
            Coords<2> pos(j,i);
            FVector<Color,2> grad=gradient(I,pos);
            //Vx(j,i)= std::max(std::max(grad.x().r(),grad.x().g()),grad.x().b());
            //Vy(j,i)= std::max(std::max(grad.y().r(),grad.y().g()),grad.y().b());
            Vx(j,i)= int(sqrt(pow(grad.x().r(),2)+pow(grad.x().g(),2)+pow(grad.x().b(),2))/sqrt(3));
            Vy(j,i)= int(sqrt(pow(grad.y().r(),2)+pow(grad.y().g(),2)+pow(grad.y().b(),2))/sqrt(3));
        }
    }
}

void energie(Image<byte>& Vx, Image<byte>& Vy,Image<byte>& E)
{
    for (int i=0;i<Vx.height();i++)
    {
        for (int j=0;j<Vx.width();j++)
        {
            E(j,i)=(Vx(j,i)+Vy(j,i));
        }
    }
}



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

void gradient(const Image<byte>& I, Image<byte>& Vx, Image<byte>& Vy)
{

    for(int i=0;i<I.height();i++)
    {
        for (int j=0;j<I.width();j++)
        {
            Coords<2> pos(j,i);
            Vx(j,i)=gradient(I,pos).x();
            Vy(j,i)=gradient(I,pos).y();

        }
    }

}

void gradientbis(const Image<byte>& I, Image<byte>& Vx, Image<byte>& Vy)
{
    for (int i=0;i<I.height()-1;i++)
        {
            for ( int j=0;j<I.width()-1;j++)
            {
                Vx(j,i)=abs(I(j+1,i)-I(j,i));
                Vy(j,i)=abs(I(j,i+1)-I(j,i));
            }
        }
        int max_x=Vx(0,0);
        int min_x=Vx(0,0);
        int max_y=Vy(0,0);
        int min_y=Vy(0,0);

        for (int i=0;i<I.height()-1;i++)
        {
            for ( int j=0;j<I.width()-1;j++)
            {
                if (Vx(j,i)>=max_x)
                    max_x=Vx(j,i);
                if (Vy(j,i)>=max_y)
                    max_y=Vy(j,i);
                if (Vx(j,i)<=min_x)
                    min_x=Vx(j,i);
                if (Vy(j,i)<=min_y)
                    min_y=Vy(j,i);
            }
        }


        for (int i=0;i<I.height()-1;i++)
        {
            for ( int j=0;j<I.width()-1;j++)
            {
                Vx(j,i)=byte(255*Vx(j,i)/(max_x-min_x)-255*min_x/(max_x-min_x));
                Vy(j,i)=byte(255*Vy(j,i)/(max_y-min_y)-255*min_y/(max_y-min_y));
            }
        }

        for (int i=0;i<I.height();i++)
        {

            Vx(I.width()-1,i)=Vx(I.width()-2,i);
            Vy(I.width()-1,i)=Vy(I.width()-2,i);
        }
        for (int j=0;j<I.width();j++)
        {
            Vx(j,I.height()-1)=Vx(j,I.height()-2);
            Vy(j,I.height()-1)=Vy(j,I.height()-2);
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
            Vx(j,i)= std::max(std::max(grad.x().r(),grad.x().g()),grad.x().b());
            Vy(j,i)= std::max(std::max(grad.y().r(),grad.y().g()),grad.y().b());
            //Vx(j,i)= int(sqrt(pow(grad.x().r(),2)+pow(grad.x().g(),2)+pow(grad.x().b(),2))/sqrt(3));
            //Vy(j,i)= int(sqrt(pow(grad.y().r(),2)+pow(grad.y().g(),2)+pow(grad.y().b(),2))/sqrt(3));
        }
    }
}

Image<byte> imagegrey(const Image<Color> I)
{

    Image<byte> Igrey(I.width(),I.height());
    for (int i=0;i<I.height();i++)
    {
        for ( int j=0;j<I.width();j++)
        {
            Igrey(j,i)=0.2126*I(j,i).r()+0.7152*I(j,i).g()+0.0722*I(j,i).b();
        }

    }
    return Igrey;
}

void energie(Image<byte>& Vx, Image<byte>& Vy,Image<byte>& E)
{
    for (int i=0;i<Vx.height();i++)
    {
        for (int j=0;j<Vx.width();j++)
        {
            E(j,i)=(Vx(j,i)+Vy(j,i))/2;
        }
    }

/*
    for (int i=0;i<Vx.height();i++)
    {
        E(0,i)=byte(1e10);
        E(Vx.width()-1,i)=byte(1e10);

    }

    for (int j=0;j<Vx.width();j++)
    {
        E(j,0)=byte(1e10);
        E(j,Vx.height()-1)=byte(1e10);
    }

*/
}

void energie(Image<Color>& Vx, Image<Color>& Vy,Image<Color>& E)
{
    for (int i=0;i<Vx.height();i++)
    {
        for (int j=0;j<Vx.width();j++)
        {
            E(j,i)=(Vx(j,i)+Vy(j,i))/2;
        }
    }
}

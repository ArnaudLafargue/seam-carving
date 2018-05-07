
#include "seam.h"
#include "image.h"

Coords<2> p1(1,-1);
Coords<2> p2(0,-1);
Coords<2> p3(-1,-1);
Coords<2> trans(-1,0);

int min (int a , int b , int c)
{
    int L[3]={a,b,c};
    int mini=int(pow(10,8));
    for (int i=0;i<3;i++)
    {
        if (L[i]<=mini)
        {
            mini=L[i];
        }
    }
    return mini;
}

std::vector<Coords<2> > Bellman_vertical(Image<byte> &E,int &last_state)
{
    std::vector<Coords<2>> seam_opt;
    Image<int> bellmann(E.width()+2,E.height());
    for ( int j=1;j<E.width()+1;j++)
        {
             bellmann(j,0)=E(j-1,0);//initialisation
        }
    for (int i=0;i<E.height();i++)
        {
            bellmann(0,i)=int(pow(10,8));
            bellmann(E.width()+1,i)=int(pow(10,8));
        }
    for (int i=1;i<E.height();i++)
    {
        for ( int j=1;j<E.width()+1;j++)
        {
            bellmann(j,i)=E(j-1,i)+min(bellmann(j-1,i-1),bellmann(j,i-1),bellmann(j+1,i-1));
        }
    }

    last_state=0;
    for ( int j=1;j<E.width()+1;j++)// Recherche du M minimum sur la derniere ligne.
    {
        int min=int(INFINITY);

        if (bellmann(j,E.height()-1)<min)
        {
            min = bellmann(j,E.height()-1);
            last_state = j;
        }
    }
    Coords<2> p(last_state,E.height()-1);// Valeur finale obtenue des M
    Coords<2> p_=p+trans;
    seam_opt.push_back(p_);
    for (int i=E.height()-2;i>=0;i--)
    {
        if (bellmann((p+p1).x(),(p+p1).y())<bellmann((p+p2).x(),(p+p2).y()) && bellmann((p+p1).x(),(p+p1).y())<bellmann((p+p3).x(),(p+p3).y()))
        {
           p=p+p1;

        }
        else if (bellmann((p+p2).x(),(p+p2).y())<bellmann((p+p1).x(),(p+p1).y()) && bellmann((p+p2).x(),(p+p2).y())<bellmann((p+p3).x(),(p+p3).y()))
        {
            p=p+p2;
        }
        else
        {
            p=p+p3;
        }
        p_=p+trans;
        seam_opt.push_back(p_);
    }

return seam_opt;
}

void dessine (std::vector<Coords<2>> seam)
{

    int N = seam.size();
    for ( int i=0;i<N;i++)
    {
        fillRect(seam[i],1,1,RED);
    }

}

Image<Color> assemble_vertical(Image<Color> I,std::vector<Coords<2>> seam)
{
    Image<Color> copie(I.width()-1,I.height());
    for (int i=0;i<I.height();i++)
    {
        for ( int j=0;j<seam[i].x();j++)
        {
            copie(j,i)=I(j,i);
        }
        for ( int j=seam[i].x();j<I.width()-1;j++)
        {
            copie(j,i)=I(j+1,i);
        }
    }
    return copie;
}

Image<Color> remove_vertical(Image<Color> I, Image<byte> Vx, Image<byte> Vy, int k)
{

if (k>0)
{
    int last_state=0;
    Image<byte> E(Vx.width(),Vx.height());
    energie(Vx,Vy,E);
    std::vector<Coords<2>> seam =Bellman_vertical(E,last_state);
    Image<Color> I_=assemble_vertical(I,seam);
    Image<byte> Vx_(I_.width(),I_.height());
    Image<byte> Vy_(I_.width(),I_.height());
    gradient(I_,Vx_,Vy_);
    Vx=Vx_;
    Vy=Vy_;
    return remove_vertical(I_,Vx_,Vy_,k-1);
}
else
{
    return I;
}

}

Image<Color> Transpose(Image<Color> I)
{
    Image<Color> t(I.height(),I.width());
    for (int i=0;i<I.height();i++)
    {
        for ( int j=0;j<I.width();j++)
        {
           t(i,j)=I(j,i);
        }

    }
    return t;
}

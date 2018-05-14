
#include "seam.h"
#include "image.h"

Coords<2> p1(1,-1);
Coords<2> p2(0,-1);
Coords<2> p3(-1,-1);
Coords<2> trans(-1,0);
Coords<2> p1_(-1,1);
Coords<2> p2_(-1,0);
Coords<2> p3_(-1,-1);
Coords<2> trans_(0,-1);

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

std::vector<Coords<2>> Bellman_vertical(Image<byte> E,int&seam_value)
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

    int last_state=0;
    int mini=bellmann(1,E.height()-1);
    for ( int j=1;j<E.width()+1;j++)// Recherche du M minimum sur la derniere ligne.
    {
        if (bellmann(j,E.height()-1)<mini)
        {
            mini = bellmann(j,E.height()-1);
            last_state = j;
        }
    }

    Coords<2> p(last_state,E.height()-1);// Valeur finale obtenue des M
    seam_value=bellmann(p.x(),p.y());
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


std::vector<Coords<2>> Bellman_horizontal(Image<byte> E,int &seam_value)
{
    std::vector<Coords<2>> seam_opt;
    Image<int> bellmann(E.width(),E.height()+2);
    for ( int i=1;i<E.height()+1;i++)
        {
             bellmann(0,i)=E(0,i-1);//initialisation
        }
    for (int j=0;j<E.width();j++)
        {
            bellmann(j,0)=int(pow(10,8));
            bellmann(j,E.height()+1)=int(pow(10,8));
        }
    for (int j=1;j<E.width();j++)
    {
        for ( int i=1;i<E.height()+1;i++)
        {
            bellmann(j,i)=E(j,i-1)+min(bellmann(j-1,i-1),bellmann(j-1,i),bellmann(j-1,i+1));
        }
    }

    int last_state=0;
    int mini=bellmann(E.width()-1,1);
    for ( int i=1;i<E.height()+1;i++)// Recherche du M minimum sur la derniere ligne.
    {
        if (bellmann(E.width()-1,i)<mini)
        {
            mini = bellmann(E.width()-1,i);
            last_state = i;
        }
    }

    Coords<2> p(E.width()-1,last_state);// Valeur finale obtenue des M
    seam_value=bellmann(p.x(),p.y());
    Coords<2> p_=p+trans_;
    seam_opt.push_back(p_);

    for (int j=E.width()-2;j>=0;j--)
    {
        if (bellmann((p+p1_).x(),(p+p1_).y())<bellmann((p+p2_).x(),(p+p2_).y()) && bellmann((p+p1_).x(),(p+p1_).y())<bellmann((p+p3_).x(),(p+p3_).y()))
        {
           p=p+p1_;

        }
        else if (bellmann((p+p2_).x(),(p+p2_).y())<bellmann((p+p1_).x(),(p+p1_).y()) && bellmann((p+p2_).x(),(p+p2_).y())<bellmann((p+p3_).x(),(p+p3_).y()))
        {
            p=p+p2_;
        }
        else
        {
            p=p+p3_;
        }
        p_=p+trans_;
        seam_opt.push_back(p_);
    }


return seam_opt;
}



void dessine(std::vector<Coords<2>> seam)
{

    int N = seam.size();
    for ( int i=0;i<N;i++)
    {
        fillRect(seam[i],1,1,RED);
    }

}

Image<Color> assemble_vertical(Image<Color> I, std::vector<Coords<2>> seam)
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

Image<Color> assemble_horizontal(Image<Color> I,std::vector<Coords<2>> seam)
{
    Image<Color> copie(I.width(),I.height()-1);
    for (int j=0;j<I.width();j++)
    {
        for ( int i=0;i<seam[j].y();i++)
        {
            copie(j,i)=I(j,i);
        }

        for ( int i=seam[j].y();i<I.height()-1;i++)
        {
            copie(j,i)=I(j,i+1);
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
    std::vector<Coords<2>> seam = Bellman_vertical(E,last_state);
    int seam_value=0;
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
/*
Image<Color> remove_vert(Image<Color> I,int &seam_value,Image<byte> E)
{
    int last_state=0;
    std::vector<Coords<2>> seam = Bellman_vertical(E,last_state);

    return I_;
}
*/
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


Image<Color> remove(Image<Color> I,int w,int h)
{
   std::cout << "w restant "<< w<<" ;h restant "<<h<<std::endl;
    Image<byte> Vx(I.width(),I.height());
    Image<byte> Vy(I.width(),I.height());
    Image<byte> E(I.width(),I.height());
    gradient(I,Vx,Vy);
    energie(Vx,Vy,E);
    if (w>0 && h>0)
    {
        int seam_value1;
        int seam_value2;
        std::vector<Coords<2>> seam1=Bellman_horizontal(E,seam_value1);
        std::vector<Coords<2>> seam2=Bellman_vertical(E,seam_value2);
        if (seam_value1 > seam_value2)
        {
            Image<Color> I_=assemble_vertical(I,seam2);
            Image<byte> Vx_(I.width()-1,I.height());
            Image<byte> Vy_(I.width()-1,I.height());
            Image<byte> E_(I.width()-1,I.height());
            gradient(I_,Vx_,Vy_);
            energie(Vx_,Vy_,E_);
            return remove(I_,w-1,h);
        }
        else
        {
            Image<Color> I_=assemble_horizontal(I,seam1);
            Image<byte> Vx_(I.width(),I.height()-1);
            Image<byte> Vy_(I.width(),I.height()-1);
            Image<byte> E_(I.width(),I.height()-1);
            gradient(I_,Vx_,Vy_);
            energie(Vx_,Vy_,E_);
            return remove(I_,w,h-1);
        }

    }
    else if(w>0 && h==0)
    {
        int seam_value;
        std::vector<Coords<2>> seam=Bellman_vertical(E,seam_value);
        Image<Color> I_=assemble_vertical(I,seam);
        Image<byte> Vx_(I.width()-1,I.height());
        Image<byte> Vy_(I.width()-1,I.height());
        Image<byte> E_(I.width()-1,I.height());
        gradient(I_,Vx_,Vy_);
        energie(Vx_,Vy_,E_);
        return remove(I_,w-1,h);
    }
    else if(w==0 && h>0)
    {
        int seam_value;
        std::vector<Coords<2>> seam=Bellman_horizontal(E,seam_value);
        Image<Color> I_=assemble_horizontal(I,seam);
        Image<byte> Vx_(I.width(),I.height()-1);
        Image<byte> Vy_(I.width(),I.height()-1);
        Image<byte> E_(I.width(),I.height()-1);
        gradient(I_,Vx_,Vy_);
        energie(Vx_,Vy_,E_);
        return remove(I_,w,h-1);

    }
    else
    {
        return I;
    }

}



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
    int mini=L[0];
    for (int i=1;i<3;i++)
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
            bellmann(0,i)=int(1e8);
            bellmann(E.width()+1,i)=int(1e8);
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
    seam_opt.insert(seam_opt.begin(),p_);

    for (int i=E.height()-2;i>=0;i--)
    {
        if (bellmann((p+p1).x(),(p+p1).y())<=bellmann((p+p2).x(),(p+p2).y()) && bellmann((p+p1).x(),(p+p1).y())<=bellmann((p+p3).x(),(p+p3).y()))
        {
           p=p+p1;

        }
        else if (bellmann((p+p2).x(),(p+p2).y())<=bellmann((p+p1).x(),(p+p1).y()) && bellmann((p+p2).x(),(p+p2).y())<=bellmann((p+p3).x(),(p+p3).y()))
        {
            p=p+p2;
        }
        else
        {
            p=p+p3;
        }
        p_=p+trans;
        seam_opt.insert(seam_opt.begin(),p_);
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
            bellmann(j,0) = int(1e8);
            bellmann(j,E.height()+1) = int(1e8);
        }

    for (int j=1;j<E.width();j++)
    {
        for (int i=1;i<E.height()+1;i++)
        {
            bellmann(j,i)=E(j,i-1)+min(bellmann(j-1,i-1),bellmann(j-1,i),bellmann(j-1,i+1));
        }
    }


    int last_state=0;
    int mini=bellmann(E.width()-1,1);
    for ( int i=2;i<E.height()+1;i++)// Recherche du M minimum sur la derniere ligne.
    {
        if (bellmann(E.width()-1,i)<=mini)
        {
            mini = bellmann(E.width()-1,i);
            last_state = i;
        }
    }

    Coords<2> p(E.width()-1,last_state);// coordonnées finales

    seam_value=bellmann(E.width()-1,last_state);

    Coords<2> p_=p+trans_;

    seam_opt.insert(seam_opt.begin(),p_);
    for (int j=E.width()-2;j>=0;j--)
    {
        if (bellmann((p+p1_).x(),(p+p1_).y())<=bellmann((p+p2_).x(),(p+p2_).y()) && bellmann((p+p1_).x(),(p+p1_).y())<=bellmann((p+p3_).x(),(p+p3_).y()))
        {
           p=p+p1_;

        }
        else if (bellmann((p+p2_).x(),(p+p2_).y())<=bellmann((p+p1_).x(),(p+p1_).y()) && bellmann((p+p2_).x(),(p+p2_).y())<=bellmann((p+p3_).x(),(p+p3_).y()))
        {
            p=p+p2_;
        }
        else
        {
            p=p+p3_;
        }
        p_=p+trans_;
        seam_opt.insert(seam_opt.begin(),p_);
    }

return seam_opt;
}



void dessine(std::vector<Coords<2>> seam)
{

    int N = seam.size();
    for ( int i=0;i<N;i++)
    {
        fillRect(seam[i].x(),seam[i].y(),1,1,RED);
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
Image<Color> ajoute_horizontal(Image<Color> I,std::vector<Coords<2>> seam)
{
    Image<Color> copie(I.width(),I.height()+1);
    for (int j=0;j<I.width();j++)
    {
        for ( int i=0;i<seam[j].y();i++)
        {
            copie(j,i)=I(j,i);

        }

        int r1=I(j,seam[j].y()).r();
        int g1 =I(j,seam[j].y()).g();
        int b1 =I(j,seam[j].y()).b();
        int r2=I(j,seam[j].y()+1).r();
        int g2 =I(j,seam[j].y()+1).g();
        int b2 =I(j,seam[j].y()+1).b();

        copie(j,seam[j].y())= Color((r1+r2)/2,(g1+g2)/2,(b1+b2)/2);

        //std::cout<< r <<" "<<g<< " "<< b<<std::endl;

        for ( int i=seam[j].y()+1;i<copie.height();i++)
        {
            copie(j,i)=I(j,i-1);

        }

    }
    return copie;

}


Image<Color> ajoute_vertical(Image<Color> I,std::vector<Coords<2>> seam)
{
    Image<Color> copie(I.width()+1,I.height());
    for (int i=0;i<I.height();i++)
    {
        for ( int j=0;j < seam[i].x();j++)
        {
            copie(j,i)=I(j,i);
        }

        int r1=I(seam[i].x(),i).r();
        int g1 =I(seam[i].x(),i).g();
        int b1 =I(seam[i].x(),i).b();
        int r2=I(seam[i].x()+1,i).r();
        int g2 =I(seam[i].x()+1,i).g();
        int b2 =I(seam[i].x()+1,i).b();

        copie(seam[i].x(),i)= Color((r1+r2)/2,(g1+g2)/2,(b1+b2)/2);

        //std::cout<< r <<" "<<g<< " "<< b<<std::endl;

        for ( int j = seam[i].x()+1;j < copie.width();j++)
        {
            copie(j,i)=I(j-1,i);

        }

    }
    return copie;

}


Image<Color> add(Image<Color> I,int w,int h)
{
    std::cout << "w restant "<< w<<" ;h restant "<<h<<std::endl;
    Image<byte> Vx(I.width(),I.height());
    Image<byte> Vy(I.width(),I.height());
    Image<byte> E(I.width(),I.height());
    Image<byte> Igrey=imagegrey(I);
    gradient(Igrey,Vx,Vy);
    energie(Vx,Vy,E);
    if (w>0 && h>0)
    {
        int seam_value1;
        int seam_value2;
        std::vector<Coords<2>> seam1=Bellman_horizontal(E,seam_value1);
        std::vector<Coords<2>> seam2=Bellman_vertical(E,seam_value2);
        if (seam_value1 > seam_value2)
        {
            Image<Color> I_=ajoute_vertical(I,seam2);
            Image<byte> Vx_(I.width()+1,I.height());
            Image<byte> Vy_(I.width()+1,I.height());
            Image<byte> E_(I.width()+1,I.height());
            Image<byte> I_grey=imagegrey(I_);
            gradient(I_grey,Vx_,Vy_);
            energie(Vx_,Vy_,E_);
            return add(I_,w-1,h);
        }
        else
        {
            Image<Color> I_=ajoute_horizontal(I,seam1);
            Image<byte> Vx_(I.width(),I.height()+1);
            Image<byte> Vy_(I.width(),I.height()+1);
            Image<byte> E_(I.width(),I.height()+1);
            Image<byte> I_grey=imagegrey(I_);
            gradient(I_grey,Vx_,Vy_);
            energie(Vx_,Vy_,E_);
            return add(I_,w,h-1);
        }

    }
    else if(w>0 && h==0)
    {
        int seam_value;
        std::vector<Coords<2>> seam=Bellman_vertical(E,seam_value);
        Image<Color> I_=ajoute_vertical(I,seam);
        Image<byte> Vx_(I.width()+1,I.height());
        Image<byte> Vy_(I.width()+1,I.height());
        Image<byte> E_(I.width()+1,I.height());
        Image<byte> I_grey=imagegrey(I_);
        gradient(I_grey,Vx_,Vy_);
        energie(Vx_,Vy_,E_);
        return add(I_,w-1,h);
    }
    else if(w==0 && h>0)
    {
        int seam_value;
        std::vector<Coords<2>> seam=Bellman_horizontal(E,seam_value);
        Image<Color> I_=ajoute_horizontal(I,seam);
        Image<byte> Vx_(I.width(),I.height()+1);
        Image<byte> Vy_(I.width(),I.height()+1);
        Image<byte> E_(I.width(),I.height()+1);
        Image<byte> I_grey=imagegrey(I_);
        gradient(I_grey,Vx_,Vy_);
        energie(Vx_,Vy_,E_);
        return add(I_,w,h-1);

    }
    else
    {
        return I;
    }

}
Image<Color> addseam_horizontal(Image<Color> I,std::vector<Coords<2>> seam)
{
    Image <Color> I_(I.width(),I.height()+1);
    for (int j=0;j<I.width();j++)
    {
        int i = seam[j].y();

        if ( i == 0)
        {
            I_(j,i)=I(j,i);
            for (int k=1;k<I.height()+1;k++)
            {
                I_(j,k)=I(j,k-1);
            }
        }
        else
        {
            for ( int k=0;k<i;k++)
            {
                I_(j,k)=I(j,k);
            }
            I_(j,i)=(I(j,i)+I(j,i-1))/2;
            for (int k=i+1;k<I.height()+1;k++)
            {
                I_(j,k)=I(j,k-1);
            }

        }

    }
    return I_;
}



Image<Color> addseam_vertical(Image<Color> I,std::vector<Coords<2>> seam)
{
    Image <Color> I_(I.width()+1,I.height());

    for (int i=0;i<I.height();i++)
    {
        int j = seam[i].x();

        if ( j == 0)
        {
            I_(j,i)=I(j,i);
            for (int k=1;k<I.width()+1;k++)
            {
                I_(k,i)=I(k-1,i);
            }
        }
        else
        {
            for ( int l= 0;l<j;l++)
            {
                assert( l<I_.width() || l<I.width());
                assert( i<I_.height() || i<I.height());
                I_(l,i)=I(l,i);
            }

            int r1=I(j,i).r();
            int r2=I(j-1,i).r();
            int g1=I(j,i).g();
            int g2=I(j-1,i).g();
            int b1=I(j,i).b();
            int b2=I(j-1,i).b();

            I_(j,i)=Color((r1+r2)/2,(g1+g2)/2,(b1+b2)/2);
            for ( int k=j+1;k<I.width()+1;k++)
            {
                I_(k,i)=I(k-1,i);
            }

        }

    }
    return I_;
}

Image<Color> insertion_vertical(Image<Color> I,int n)
{
    Image<Color> Itemp=I;
    std::vector<std::vector<Coords<2>>> liste_seam;
    while (n>0)
    {
        Image<byte> Vx(Itemp.width(),Itemp.height());
        Image<byte> Vy(Itemp.width(),Itemp.height());
        Image<byte> E(Itemp.width(),Itemp.height());
        Image<byte> Igrey_temp=imagegrey(Itemp);
        gradient(Igrey_temp,Vx,Vy);
        energie(Vx,Vy,E);

        int seam_value;
        std::vector<Coords<2>> seam=Bellman_vertical(E,seam_value);
        liste_seam.push_back(seam);
        Image<Color> Itemp2(Itemp.width()-1,Itemp.height());
        Itemp2 = assemble_vertical(Itemp,seam);
        Itemp.~Image();
        Image<Color> Itemp=Itemp2;
        n--;
    }
    n = liste_seam.size();
    while (n>0)
    {
        std::vector<Coords<2>> seam = liste_seam[0];
        Image<Color> Itemp2=addseam_vertical(Itemp,seam);
        if ( liste_seam.size()>1)
        {
            liste_seam = update_seam_vertical(liste_seam,seam);
        }
        Itemp.~Image();
        Image<Color> Itemp=Itemp2;
        n--;

    }

    return Itemp;
}


std::vector<std::vector<Coords<2>>> update_seam_vertical(std::vector<std::vector<Coords<2>>> remaining_seams,std::vector<Coords<2>>current_seam)
{
    std::vector<std::vector<Coords<2>>> output;
    if (remaining_seams.size()<=1)
    {
        Coords<2> test(0,0);
        std::vector<Coords<2>> p;
        p.push_back(test);
        output.push_back(p);
        return output;
    }
    else
    {
        for (int k=1;k<remaining_seams.size();k++)
        {
            std::vector<Coords<2>> seam = remaining_seams[k];
            for ( int l=0;l<seam.size();l++)
            {
                if (current_seam[l].x() <=  seam[l].x())
                {
                    seam[l].x()+=2;
                }
            }
            output.push_back(seam);
        }
    }
    return output;
}

Image<Color> remove(Image<Color> I,int w,int h)
{
    std::cout << "w restant "<< w<<" ;h restant "<<h<<std::endl;
    Image<byte> Vx(I.width(),I.height());
    Image<byte> Vy(I.width(),I.height());
    Image<byte> E(I.width(),I.height());
    Image<byte> Igrey=imagegrey(I);
    gradient(Igrey,Vx,Vy);
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
            Image<byte> I_grey=imagegrey(I_);
            gradient(I_grey,Vx_,Vy_);
            energie(Vx_,Vy_,E_);
            return remove(I_,w-1,h);
        }
        else
        {
            Image<Color> I_=assemble_horizontal(I,seam1);
            Image<byte> Vx_(I.width(),I.height()-1);
            Image<byte> Vy_(I.width(),I.height()-1);
            Image<byte> E_(I.width(),I.height()-1);
            Image<byte> I_grey=imagegrey(I_);
            gradient(I_grey,Vx_,Vy_);
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
        Image<byte> I_grey=imagegrey(I_);
        gradient(I_grey,Vx_,Vy_);
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
        Image<byte> I_grey=imagegrey(I_);
        gradient(I_grey,Vx_,Vy_);
        energie(Vx_,Vy_,E_);
        return remove(I_,w,h-1);

    }
    else
    {
        return I;
    }

}

int valeur(std::vector<Coords<2>> seam,Image<byte> E)
{
    int N=seam.size();
    int value=0;
    for (int i=0;i<N;i++)
    {
        value+=E(seam[i].x(),seam[i].y());
    }
    return value;
}

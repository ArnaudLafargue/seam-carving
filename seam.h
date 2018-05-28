#ifndef SEAM_H
#define SEAM_H
#include <Imagine/Graphics.h>
#include <Imagine/Images.h>
using namespace Imagine;
#include <vector>
#pragma once

std::vector<Coords<2> > Bellman_vertical(Image<byte> E, int &seam_value);
std::vector<Coords<2> > Bellman_horizontal(Image<byte> E, int &seam_value);


void dessine (std::vector<Coords<2>> seam);
int min (int a , int b , int c);

Image<Color> assemble_vertical(Image<Color> I, std::vector<Coords<2>> seam);
Image<Color> assemble_horizontal(Image<Color> I, std::vector<Coords<2>> seam);

Image<Color> ajoute_horizontal(Image<Color> I,std::vector<Coords<2>> seam);
Image<Color> ajoute_vertical(Image<Color> I,std::vector<Coords<2>> seam);


Image<Color> remove(Image<Color> I,int w, int h);

Image<Color> add(Image<Color> I, int w, int h);
Image<Color> addseam_vertical(Image<Color> I,std::vector<Coords<2>> seam);
Image<Color> insertion_vertical(Image<Color> I,int n);
std::vector<std::vector<Coords<2>>> update_seam_vertical(std::vector<std::vector<Coords<2>>> remaining_seams,std::vector<Coords<2>>current_seam);
int valeur(std::vector<Coords<2>> seam,Image<byte> E);


#endif // SEAM_H

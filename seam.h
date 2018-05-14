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

Image<Color> Transpose(Image<Color> I);

Image<Color> remove(Image<Color> I,int w, int h);


#endif // SEAM_H

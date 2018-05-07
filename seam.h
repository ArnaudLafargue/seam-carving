#ifndef SEAM_H
#define SEAM_H
#include <Imagine/Graphics.h>
#include <Imagine/Images.h>
using namespace Imagine;
#include <vector>
#pragma once

std::vector<Coords<2> > Bellman_vertical(Image<byte> &E,int &last_state);
void dessine (std::vector<Coords<2>> seam);
int min (int a , int b , int c);
Image<Color> assemble_vertical(Image<Color> I,std::vector<Coords<2>> seam);
Image<Color> remove_vertical(Image<Color> I, Image<byte> Vx, Image<byte> Vy, int k);
Image<Color> Transpose(Image<Color> I);


#endif // SEAM_H

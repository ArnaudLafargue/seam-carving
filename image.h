#ifndef IMAGE_H
#define IMAGE_H


#pragma once
#include <Imagine/Images.h>
#include <Imagine/Graphics.h>
using namespace Imagine;
void gradient(const Image<byte> &I, Image<byte> &Vx, Image<byte> &Vy);
void gradientbis(const Image<byte>& I, Image<byte>& Vx, Image<byte>& Vy);

Image<byte> image_vert(Image<Color> F);
Image<byte> image_rouge(Image<Color> F);
Image<byte> image_bleue(Image<Color> F);
Image<Color> reconstitue(Image<byte>I_r,Image<byte>I_g,Image<byte>I_b);

void energie(Image<byte> &Vx, Image<byte> &Vy, Image<byte>& E);
void gradient(const Image<Color> &I, Image<byte>& Vx, Image<byte>& Vy);
Image<byte> imagegrey(const Image<Color> I);

#endif // TERRAIN_H

//-----------------------//
// Lucifer Image Library //
// Thomas Liao (2022)    //
//-----------------------//

#include <Lucifer_WriteImage.h>


namespace Lucifer {

int Lucifer_GetBitsPerPixel(Image &Image) {

    return (Image.Size * 8) / (Image.Width * Image.Height);

}

FIBITMAP* Lucifer_CreateFIBitmapFromImage(Image &Image) {
    
    // Allocate New Image
    int BitsPP = (Image.Size * 8) / (Image.Width * Image.Height);
    FIBITMAP* FIImage = FreeImage_Allocate(Image.Width, Image.Height, BitsPP, 0, 0, 0);

    // Copy Image Pixel Data To FIBITMAP
    memcpy(FreeImage_GetBits(FIImage), Image.Bytes.get(), Image.Width * Image.Height * (BitsPP / 8));

    return FIImage;

}


}
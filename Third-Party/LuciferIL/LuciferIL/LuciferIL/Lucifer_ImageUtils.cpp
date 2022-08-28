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
    FIBITMAP* FIImage = FreeImage_Allocate(Image.Width, Image.Height, BitsPP);

    // Copy Image Pixel Data To FIBITMAP
    int ImageMemorySize = Image.Width * Image.Height * (BitsPP / 8);
    int ImageMemorySize2 = FreeImage_GetMemorySize(FIImage);
    int ImageMemorySize3 = Image.Width * Image.Height * BitsPP;
    memcpy(FreeImage_GetBits(FIImage), Image.Bytes.get(), ImageMemorySize2);

    return FIImage;

    

}


}
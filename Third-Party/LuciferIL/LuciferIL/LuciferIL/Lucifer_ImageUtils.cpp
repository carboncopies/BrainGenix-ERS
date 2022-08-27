//-----------------------//
// Lucifer Image Library //
// Thomas Liao (2022)    //
//-----------------------//

#include <Lucifer_WriteImage.h>


namespace Lucifer {

int Lucifer_GetBitsPerPixel(Image &Image) {

    return (Image.Size * 8) / (Image.Width * Image.Height);

}


}
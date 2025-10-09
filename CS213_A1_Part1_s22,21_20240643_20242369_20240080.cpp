// Name : Nourhan Ali Abd El-Moneim Ali ID : 20240643  filters : (2 black & white) & (5 flip ) & (8 crop) & (11 resizing) .
// Name : Nada Ahmed Abd El-Aziz Mohamed  ID : 20242369 filters : (3 invert image ) & (6 rotate image  ) & (9 adding frame) &(12 blur ).
// Name : Eslam Ahmed El-Sayed Mahmoud   ID : 20240080 filters : (1 gray scale ) & (4 merge image  ) & (7 darken and lighten) &( 10 dedect edges )
// drive link (https://drive.google.com/drive/folders/15yH3UAEypeJ_dzASA29MQppOut51jV6q?usp=sharing).
// github repo link (https://github.com/NourhanAli-fcai28/baby-photoshop.git)


#include <iostream>
#include <stdexcept>
#include <fstream>
#include "Image_Class.h"
using namespace std;

Image image;

bool isValidExtension(string filename) {
    string exts[] = {".jpg", ".bmp", ".png"};
    for (string ext : exts) {
        if (filename.size() >= ext.size() &&
            filename.substr(filename.size() - ext.size()) == ext) {
            return true;
        }
    }
    return false;
}

void filter3(Image& image){
    for(int i=0;i< image.width; i++){
        for(int j=0;j< image.height ;j++){
            for(int k=0;k<3 ;k++){
                image(i,j,k) = 255 - image(i,j,k);
            }
        }
    }
}

void filter6_90_degree(Image& image){
    Image rotated(image.height ,image.width);
    for(int j=0;j< image.height; j++){
        for(int i=0;i< image.width;i++){
            for(int k=0;k< 3;k++) {
                rotated(image.height - 1 - j, i, k) = image(i, j, k);
            }
        }
    }
    image = rotated;
}

void filter6_180_degree(Image& image){
    Image rotated(image.width, image.height);
    for(int i=0;i< image.width; i++){
        for(int j=0;j< image.height;j++){
            for(int k=0;k< 3;k++) {
                rotated(image.width - 1 - i, image.height - 1 - j, k)=image(i,j,k);
            }
        }
    }
    image = rotated;
}

void filter6_270_degree(Image& image){
    Image rotated(image.height ,image.width);
    for(int j=0;j< image.height; j++){
        for(int i=0;i< image.width;i++){
            for(int k=0;k< 3;k++) {
                rotated(j, image.width - 1 - i, k) = image(i, j, k);
            }
        }
    }
    image = rotated;
}
void filter9(Image& image) {
    int thickness;
    cout << "Enter frame thickness: ";
    cin >> thickness;
    int frameRed = 0, frameGreen = 0, frameBlue = 0;
    cout << "Enter frame color (RGB , from 0 to 255): ";
    cin >> frameRed >> frameGreen >> frameBlue;
    int newWidth = image.width + 2 * thickness;
    int newHeight = image.height + 2 * thickness;
    Image framed(newWidth, newHeight);
    for (int i = 0; i < newWidth; i++) {
        for (int j = 0; j < newHeight; j++) {
            for (int k = 0; k < 3; k++) {
                if (k==0) {
                    framed(i,j,k) = frameRed;
                }
                else if (k==1) {
                    framed(i,j,k) = frameGreen;
                }
                else if (k==2) {
                    framed(i,j,k) = frameBlue;
                }
            }
        }
    }
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3; k++) {
                framed(i + thickness, j + thickness, k) = image(i, j, k);
            }
        }
    }
    cout << "do you want to decorate it?" << endl;
    string decAnswer;
    cin >> decAnswer;
    if (decAnswer == "yes") {
        cout << "what style do you want " << endl;
        cout << "1 for decorated corner \n" << "2 for inner border" <<endl;
        char style;
        cin >> style;
        if (style == '1') {
            int squareSize = thickness*2;
            int gap = thickness / 2;
            int thinSize = thickness ;
            for (int i = 0; i < squareSize + gap + thinSize; i++) {
                for (int j = 0; j < squareSize + gap + thinSize; j++) {
                    for (int k = 0; k < 3; k++) {
                        if (i < squareSize && j < squareSize) {
                            framed(i, j, k) = 255;
                            framed(newWidth - 1 - i, j, k) = 255;
                            framed(i, newHeight - 1 - j, k) = 255;
                            framed(newWidth - 1 - i, newHeight - 1 - j, k) = 255;
                        }
                        else if (i >= squareSize + gap && i < squareSize + gap + thinSize &&
                    j >= squareSize + gap && j < squareSize + gap + thinSize) {
                            framed(i, j, k) = 255;
                            framed(newWidth - 1 - i, j, k) = 255;
                            framed(i, newHeight - 1 - j, k) = 255;
                            framed(newWidth - 1 - i, newHeight - 1 - j, k) = 255;
                    }

                    }
                }

            }



        }
        else if (style == '2') {
            int innertick =thickness/2;
            int startI = thickness;
            int startJ = thickness;
            for (int i = startI; i < newWidth - startI; i++) {
                for (int t = 0; t < innertick; t++) {
                    for (int k = 0; k < 3; k++) {
                        framed(i, startJ + t, k) = 255;
                        framed(i, newHeight - startJ - t - 1, k) = 255;
                    }
                }
            }
            for (int j = startJ; j < newHeight - startJ; j++) {
                for (int t = 0; t < innertick; t++) {
                    for (int k = 0; k < 3; k++) {
                        framed(startI + t, j, k) = 255;
                        framed(newWidth - startI - t - 1, j, k) = 255;
                    }

                }
            }
        }
    }
    else if (decAnswer=="no"){

    }
    image = framed;
}
void filter12(Image& image, int radius) {
        int width = image.width;
        int height = image.height;
        Image temp(width, height);
        for (int j = 0; j< height; j++) {
            for (int k = 0; k < 3; k++) {
                int sum = 0;
                for (int i = 0;  i<= radius; i++)
                    sum += image(i, j, k);
                temp(0, j, k) = sum / (radius + 1);
                for (int i = 1; i < width; i++) {
                    int left = i - radius - 1;
                    int right = i + radius;
                    if (left >= 0)
                        sum -= image(left, j, k);
                    if (right < width)
                        sum += image(right, j, k);

                    temp(i, j, k) = sum / (min(width, 2 * radius + 1));
                }
            }
        }
        for (int i = 0; i < width; i++) {
            for (int k = 0; k < 3; k++) {
                int sum = 0;
                for (int j = 0; j <= radius; j++) {
                    sum += temp(i, j, k);
                }
                image(i, 0, k) = sum / (radius + 1);
                for (int j = 1; j < height; j++) {
                    int top = j - radius - 1;
                    int bottom = j + radius;
                    if (top >= 0) {
                        sum -= temp(i, top, k);
                    }

                    if (bottom < height) {
                        sum += temp(i, bottom, k);
                    }

                    image(i, j, k) = sum / (min(height, 2 * radius + 1));
                }
            }
        }
    }




int main() {
    Image image;
    string fileName;

    while (true) {
        cout << "do you want to load a new image? (yes or no)" << endl;
        string answer;
        cin >> answer;

        if (answer == "yes") {
            int choice;
            cout<<"press "<<endl;
            cout<<"1 if you want to load an image from a file"<<endl;
            cout<<"2 if you want to construct a blank image "<<endl;
            cout<<"3 if you want to copy another image "<<endl;
            cout<<"4 if you want to exit the program "<<endl;
            cin >> choice;

            if (choice == 1) {
                bool loaded = false;
                while (!loaded) {
                    cout << "Please enter filename with extension: " << endl;
                    cin >> fileName;
                    if (!isValidExtension(fileName)) {
                        cout << "Invalid extension. Please try again.\n";
                        continue;
                    }
                    try {
                        loaded = image.loadNewImage(fileName);
                        if (loaded) {
                            cout << "Image loaded successfully!\n";
                        }
                    } catch (const invalid_argument& e) {
                        cout << e.what() << endl;
                    }
                }
            } else if (choice == 2) {
                cout<<"please enter width and height of the photo  "<<endl;
                int width, height;
                cin >> width >> height;
                image = Image(width, height);
            } else if (choice == 3) {
                Image copiedImage = image;
                cout << "Image copied successfully.\n";
            }

            cout << "filter 1: Grayscale Conversion "<<endl;
            cout << "filter 2: Black and White "<<endl;
            cout << "filter 3: Invert Image "<<endl;
            cout << "filter 4: Merge Images "<<endl;
            cout << "filter 5: Flip Image "<<endl;
            cout << "filter 6: Rotate Image "<<endl;
            cout << "filter 7: Darken and Lighten Image  "<<endl;
            cout << "filter 8: Crop Images "<<endl;
            cout << "filter 9: Adding a Frame to the Picture "<<endl;
            cout << "filter 10: Detect Image Edges "<<endl;
            cout << "filter 11: Resizing Images"<<endl;
            cout << "filter 12: Blur Images "<<endl;

            int number;
            cout << "please enter the number of filter "<<endl;
            cin >> number;

            if (number == 1) {

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int mix = 0;
            for (int k = 0; k < 3; ++k)
            {
                mix += image(i, j, k);
            }
            mix /= 3;
            image(i, j, 0) = mix;
            image(i, j, 1) = mix;
            image(i, j, 2) = mix;
        }
    }
 }
            else if (number == 2) {
                for (int i=0 ; i < image.width ;i++ ) {
                    for (int j=0 ; j < image.height ; j++) {
                        double ave=0;
                        for (int k = 0; k < image.channels; k++) {
                            ave += image(i,j,k);
                        }
                        ave /= 3;
                        if (ave<=128) {
                            for (int k=0 ; k < image.channels ; k++) {
                                image(i,j,k)=0;
                            }
                        } else {
                            for (int k=0 ; k < image.channels ; k++) {
                                image(i,j,k)=255;
                            }
                        }
                    }
                }
            }
            else if (number == 3) {
                filter3(image);
            }
            else if (number == 4) {

    auto resizeImage = [&](const Image& srcImage, int newWidth, int newHeight) {
        Image output(newWidth, newHeight);

        float scaleX = (float)srcImage.width / newWidth;
        float scaleY = (float)srcImage.height / newHeight;

        for (int i = 0; i < newWidth; ++i) {
            for (int j = 0; j < newHeight; ++j) {
                float origX = i * scaleX;
                float origY = j * scaleY;

                for (int k = 0; k < srcImage.channels; ++k) {
                    output(i, j, k) = srcImage((int)origX, (int)origY, k);
                }
            }
        }
        return output;
    };
    string  secondImageName;

    cout << "Enter second image: ";
    cin >> secondImageName;

    Image firstImage(fileName);
    Image secondImage(secondImageName);

    cout << "1 - Resize (smaller)\n2 - Crop (zoom in)\n";
    int option;
    cin >> option;

    int width, height;

    if (option == 1) {
        if (firstImage.width * firstImage.height < secondImage.width * secondImage.height) {
            firstImage = resizeImage(firstImage, secondImage.width, secondImage.height);
        } else {
            secondImage = resizeImage(secondImage, firstImage.width, firstImage.height);
        }
        width = firstImage.width;
        height = firstImage.height;
    }
    else if (option == 2) {
        width = min(firstImage.width, secondImage.width);
        height = min(firstImage.height, secondImage.height);
    }
    else {

    }
    Image merged(width, height);
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            for (int k = 0; k < 3; ++k) {
                merged(i, j, k) = (firstImage(i, j, k) + secondImage(i, j, k)) / 2;
            }
        }
    }
                image = merged;

            }
            else if (number == 5) {
                cout << "press 1 if you want horizontal flip or 2 if you want vertical flip ";
                int flppingchoice;
                cin >> flppingchoice;

                if (flppingchoice == 1) {
                    for (int i = 0; i < image.width / 2; i++) {
                        for (int j = 0; j < image.height; j++) {
                            for (int k = 0; k < image.channels; k++) {
                                swap(image(i, j, k), image(image.width - 1 - i, j, k));
                            }
                        }
                    }
                }
                else if (flppingchoice == 2) {
                    for (int i = 0; i < image.width; i++) {
                        for (int j = 0; j < image.height / 2; j++) {
                            for (int k = 0; k < image.channels; k++) {
                                swap(image(i, j, k), image(i, image.height - 1 - j, k));
                            }
                        }
                    }
                }
            }


            else if (number == 6) {
                cout << "please enter the angle" << endl;
                string angle;
                cin >> angle;
                if (angle =="90") {
                    filter6_90_degree(image);
                } else if (angle =="180") {
                    filter6_180_degree(image);
                } else if (angle =="270") {
                    filter6_270_degree(image);
                }

            }
            else if (number==7) {

    int flppingchoice;
    cout << "Darken (0) or Lighten (1)? ";

    cin >> flppingchoice;
    int picW = image.width;
    int picH = image.height;
    if (flppingchoice == 0) {
        for (int x = 0; x < picW; x++) {
            for (int y = 0; y < picH; y++) {
                for (int c = 0; c < image.channels; c++) {
                    image(x, y, c) = image(x, y, c) * 0.5;
                }
            }
        }
    } else {
        for (int x = 0; x < picW; x++) {
            for (int y = 0; y < picH; y++) {
                for (int c = 0; c < image.channels; c++) {
                    image(x, y, c) = (image(x, y, c) + 255) / 2;
                }
            }
        }
    }
            }
            else if (number==8) {
                int dimX, dimY  , cropX, cropY;
                while (true) {
                    cout << " respect this range:\n";
                    cout << "  Width:  0 --> " << image.width-1 << endl;
                    cout << "  Height: 0 --> " << image.height-1 << endl;
                    cout << "Please enter the starting point dimensions: \n " ;
                    cin >> dimX >> dimY;
                    if (dimX >= 0 && dimY >= 0 && dimX < image.width-1 && dimY < image.height-1){
                        break;
                    } else {
                        cout << " Please enter valid starting dimensions." << endl;
                    }

                }
                while (true) {
                    cout << " respect this range:\n";
                    cout << "  Width:  " << dimX << " --> " << image.width-1 << endl;
                    cout << "  Height: " << dimY << " --> " << image.height-1 << endl;
                    cout << "Please enter the pixels you want to crop till.\n";
                    cin >> cropX >> cropY;
                    if (cropX > dimX && cropY > dimY && cropX <= image.width-1 && cropY <= image.height-1){
                        break;
                    } else {
                        cout << " Invalid crop range! Please enter values within the correct range.\n";
                    }
                }

                int newWidth = cropX - dimX;
                int newHeight = cropY - dimY;
                Image newImage(newWidth, newHeight);
                for (int i = 0; i < newWidth; i++) {
                    for (int j = 0; j < newHeight; j++) {
                        for (int k = 0; k < 3; k++) {
                            newImage(i, j, k) = image(i + dimX, j + dimY, k);
                        }
                    }
                }
                image = newImage;

            }
            else if (number==9) {
                filter9(image);
            }
            else if (number==10) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned int intensity = (image(i, j, 0) + image(i, j, 1) + image(i, j, 2)) / 3;
            int bw = (intensity > 127) ? 255 : 0;
            for (int k = 0; k < 3; k++) {
                image(i, j, k) = bw;
            }
        }
    }
    Image edges(image.width, image.height);
    for (int i = 1; i < image.width - 1; i++) {
        for (int j = 1; j < image.height - 1; j++) {
            int centerPixel = image(i, j, 0);
            if (centerPixel == 0 &&
                image(i - 1, j, 0) == 0 && image(i + 1, j, 0) == 0 &&
                image(i, j - 1, 0) == 0 && image(i, j + 1, 0) == 0) {
                for (int k = 0; k < 3; k++) edges(i, j, k) = 255;
            } else {
                for (int k = 0; k < 3; k++) edges(i, j, k) = centerPixel;
            }
        }
    }
                image = edges;

            }
            else if (number==11) {
                int oldwidth = image.width;
                int oldhigh = image.height;
                int newwidth, newhigh;
                while (true) {
                    cout << "Enter new width and height: ";
                    cin >> newwidth >> newhigh;
                    if (newwidth <= 0 || newhigh <= 0) {
                        cout << "  Invalid dimensions.\n" ;
                    }
                    else break;
                }
                float scaleX = (float)newwidth / oldwidth;
                float scaleY = (float)newhigh / oldhigh;
                Image newImage(newwidth, newhigh);
                for (int i = 0; i < newwidth; i++) {
                    for (int j = 0; j < newhigh; j++) {
                        int oldX = int(i / scaleX);
                        int oldY = int(j / scaleY);
                        if (oldX >= oldwidth) oldX = oldwidth - 1;
                        if (oldY >= oldhigh) oldY = oldhigh - 1;
                        for (int k = 0; k < 3; k++) {
                            newImage(i, j, k) = image(oldX, oldY, k);
                        }
                    }
                }
                image = newImage;

            }
            else if (number==12) {
                int raduis;
                        cout << "Enter radius (greater than 0): ";
                        cin >> raduis;
                        filter12(image,raduis);
            }

        }

        cout << "do you want to save the image ? (yes or no)" << endl;
        string answer2;
        cin >> answer2;
        if (answer2 == "yes") {
            cout << "do you want to save the image in the same file? "<< endl;
            string answer3;
            cin >> answer3;
            if (answer3 == "yes") {
                image.saveImage(fileName);
            } else if (answer3 == "no") {
                cout << "please enter the new file name: "<< endl;
                string newFileName;
                cin >> newFileName;
                if (!isValidExtension(newFileName)) {
                    cout << "Invalid extension. File not saved.\n";
                } else {
                    image.saveImage(newFileName);
                }
            }
        }

        cout << "do you want to exit? (yes or no)" << endl;
        string exitAns;
        cin >> exitAns;
        if (exitAns == "yes") {
            cout << "Exiting program...\n";
            break;
        }
    }
}

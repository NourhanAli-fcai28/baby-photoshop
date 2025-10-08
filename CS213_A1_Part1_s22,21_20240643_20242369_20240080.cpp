// Name : Nourhan Ali Abd El-Moneim Ali ID : 20240643  filters : (2 black & white) & (5 flip ) .
// Name : Nada Ahmed Abd El-Aziz Mohamed  ID : 20242369 filters : (3 invert image ) & (6 rotate image  ).
// Name : Eslam Ahmed El-Sayed Mahmoud   ID : 20240080 filters : (1 gray scale ) & (4 merge image  ) .



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
                Image image(fileName);
                for (int i = 0; i < image.width; ++i) {
                    for (int j = 0; j < image.height; ++j) {
                        unsigned int avg = 0;
                        for (int k = 0; k < 3; ++k) {
                            avg += image(i, j, k);
                        }
                        avg /= 3;
                        image(i, j, 0) = avg;
                        image(i, j, 1) = avg;
                        image(i, j, 2) = avg;
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
                auto resizeImage = [&](const Image& input, int newWidth, int newHeight) {
                    Image output(newWidth, newHeight);
                    float x_ratio = (float)input.width / newWidth;
                    float y_ratio = (float)input.height / newHeight;
                    for (int i = 0; i < newWidth; ++i) {
                        for (int j = 0; j < newHeight; ++j) {
                            float origX = i * x_ratio;
                            float origY = j * y_ratio;
                            for (int k = 0; k < input.channels; ++k) {
                                output(i, j, k) = input((int)origX, (int)origY, k);
                            }
                        }
                    }
                    return output;
                };

                string  file2;
                cout << "Enter second image: ";
                cin >> file2;

                Image image1(fileName);
                Image image2(file2);

                cout << "1-resize smaller\n2-crop bigger\n";
                int choice;
                cin >> choice;
                int width, height;

                if (choice == 1) {
                    if (image1.width * image1.height < image2.width * image2.height) {
                        image1 = resizeImage(image1, image2.width, image2.height);
                    } else {
                        image2= resizeImage(image2, image1.width, image1.height);
                    }
                    width = image1.width;
                    height = image1.height;
                } else if (choice == 2) {
                    width = min(image1.width, image2.width);
                    height = min(image1.height, image2.height);
                } else {
                    return 0;
                }

                Image merged(width, height);
                for (int i = 0; i < width; ++i) {
                    for (int j = 0; j < height; ++j) {
                        for (int k = 0; k < 3; ++k) {
                            merged(i, j, k) = (image1(i, j, k) + image2(i, j, k)) / 2;
                        }
                    }
                }

                string outFile;
                cout << "Enter output image: ";
                cin >> outFile;
                merged.saveImage(outFile);
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
            else if (number==7) {}
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
            else if (number==9) {}
            else if (number==10) {}
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
            else if (number==12) {}

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

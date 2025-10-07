#include <iostream>
#include <stdexcept>
#include "Image_Class.h"
using namespace std;
Image image ;
void filter3(Image& image){
    for(int i=0;i< image.width; i++){
        for(int j=0;j< image.height ;j++){
            unsigned int color1=0,color2=0,color3=0;
            for(int k=0;k<3 ;k++){
                if (k==0) {
                    color1 =image(i,j,k);
                    image(i,j,k)=255-color1;
                }
                else if (k==1) {
                    color2 =image(i,j,k);
                    image(i,j,k)=255-color2;
                }
                else if (k==2) {
                    color3 =image(i,j,k);
                    image(i,j,k)=255-color3;
                }

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
    Image image ;
    string fileName ;
    while (true) {
        cout << "do you want to load a new image? (yes or no)" << endl;
        string answer ;
        cin >> answer;
        int  choice ;
        if (answer == "yes") {
            cout<<"press "<<endl;
            cout<<"1 if you want to load an image from a file"<<endl;
            cout<<"2 if you want to construct a blank image "<<endl;
            cout<<"3 if you want to copy another image "<<endl;
            cout<<"4 if you want to exit the program "<<endl;
            cin>>choice;
            if (choice == 1) {
                bool loaded=false;
                while (!loaded) {
                    cout<<"Please enter filename with extension: "<<endl;
                    cin>>fileName;
                    try {
                        loaded = image.loadNewImage(fileName);
                        if (loaded) {
                            cout << "Image loaded successfully!\n";
                        }
                    }
                    catch (const invalid_argument& e) {
                        cout << e.what() << endl;

                    }
                }
            }
            else if (choice == 2) {
                cout<<"please enter width and height of the photo  "<<endl;
                int width, height;
                cin >> width >> height;
                image = Image(width, height); //ghyrnah l local 3shan .width .h kanu private
            }
            else if (choice == 3) {
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

            cout << "please enter the number of filter "<<endl;
            int number;
            cin >> number;

            if (number==1){

            }
            else if (number==2) {

            }
            else if (number==3) {
                filter3(image);
            }
            else if (number==4) {

            }
            else if (number==5) {

            }
            else if (number==6) {
                cout << "please enter the angle" << endl;
                string angle;
                cin >> angle;
                if (angle =="90") {
                    filter6_90_degree(image);
                }else if (angle =="180") {
                    filter6_180_degree(image);
                }else if (angle =="270") {
                    filter6_270_degree(image);
                }

            }
            else if (number==7) {

            }
            else if (number==8) {

            }
            else if (number==9) {

            }
            else if (number==10) {

            }
            else if (number==11) {

            }
            else if (number==12) {

            }



        }
        else if (answer == "no" || choice==4 ) {
            cout << "do you want to save the image ? (yes or no)" << endl;
            string answer2 ;
            cin >> answer2;
            if (answer2 == "yes") {
                cout << "do you want to save the image in the same file? "<< endl;
                string answer3 ;
                cin >> answer3;
                if (answer3 == "yes") {
                    image.saveImage(fileName);
                }
                else if (answer3 == "no") {
                    cout << "please enter the new file name: "<< endl;
                    string newFileName;
                    cin >> newFileName;
                    image.saveImage(newFileName);
                    break;
                }
            }
        }
    }
}
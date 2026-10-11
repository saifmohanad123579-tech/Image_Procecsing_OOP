void applyGrayscale(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            int r = img.getPixel(i, j, 0);
            int g = img.getPixel(i, j, 1);
            int b = img.getPixel(i, j, 2);

            int gray = (r + g + b) / 3;

            img.setPixel(i, j, 0, gray);
            img.setPixel(i, j, 1, gray);
            img.setPixel(i, j, 2, gray);
        }
    }
}
Image applyFlip(const Image& img, int choice) {
    Image flippedImg(img.width, img.height);

    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            for (int k = 0; k < img.channels; ++k) {
                if (choice == 1) {
                    flippedImg.setPixel(img.width - 1 - i, j, k, img.getPixel(i, j, k));
                }
                else if (choice == 2) {
                    flippedImg.setPixel(i, img.height - 1 - j, k, img.getPixel(i, j, k));
                }
            }
        }
    }
    return flippedImg;
}
void mergeImages(Image& image) {
    string secondImagePath;
    cout << "Enter the path of the second image to merge: ";
    cin >> secondImagePath;

    Image image2(secondImagePath);
    Image resizedImage2(image.width, image.height);
    float widthScale = (float)image2.width / image.width;
    float heightScale = (float)image2.height / image.height;

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int origI = i * widthScale;
            int origJ = j * heightScale;
            for (int k = 0; k < image.channels; k++) {
                resizedImage2(i, j, k) = image2(origI, origJ, k);
            }
        }
    }
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, k) = (image(i, j, k) + resizedImage2(i, j, k)) / 2;
            }
        }
    }
}
void applyWanoSunlightFilter(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int r = image(i, j, 0) + 35;
            int g = image(i, j, 1) + 15;
            int b = image(i, j, 2) - 20;

            image(i, j, 0) = (r > 255) ? 255 : ((r < 0) ? 0 : r);
            image(i, j, 1) = (g > 255) ? 255 : ((g < 0) ? 0 : g);
            image(i, j, 2) = (b > 255) ? 255 : ((b < 0) ? 0 : b);
        }
    }
}
void applySkew(Image& image) {
    double angle;
    cout << "Enter skew angle in degrees (1-80): ";
    cin >> angle;
    if (angle < 1) angle = 1;
    if (angle > 80) angle = 80;

    double tanA = tan(angle * 3.14159265358979 / 180.0);
    int extra = (int)((image.height - 1) * tanA);

    Image skewed(image.width + extra, image.height);

    for (int i = 0; i < skewed.width; i++)
        for (int j = 0; j < skewed.height; j++)
            for (int k = 0; k < 3; k++)
                skewed(i, j, k) = 255;

    for (int j = 0; j < image.height; j++) {
        int offset = (int)((image.height - 1 - j) * tanA);
        for (int i = 0; i < image.width; i++) {
            for (int k = 0; k < 3; k++) {
                skewed(i + offset, j, k) = image(i, j, k);
            }
        }
    }
    image = skewed;
}
void applyOilPainting(Image& image) {
    const int radius = 4;
    const int levels = 20;

    Image result(image.width, image.height);

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int count[levels] = { 0 };
            int sumR[levels] = { 0 }, sumG[levels] = { 0 }, sumB[levels] = { 0 };

            for (int dx = -radius; dx <= radius; dx++) {
                for (int dy = -radius; dy <= radius; dy++) {
                    int x = i + dx, y = j + dy;
                    if (x < 0 || y < 0 || x >= image.width || y >= image.height) continue;

                    int r = image(x, y, 0);
                    int g = image(x, y, 1);
                    int b = image(x, y, 2);

                    int bin = ((r + g + b) / 3) * levels / 256;
                    count[bin]++;
                    sumR[bin] += r;
                    sumG[bin] += g;
                    sumB[bin] += b;
                }
            }

            int best = 0;
            for (int b = 1; b < levels; b++)
                if (count[b] > count[best]) best = b;

            result(i, j, 0) = sumR[best] / count[best];
            result(i, j, 1) = sumG[best] / count[best];
            result(i, j, 2) = sumB[best] / count[best];
        }
    }
    image = result;
}
void applyBlackAndWhite(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            int r = img.getPixel(i, j, 0);
            int g = img.getPixel(i, j, 1);
            int b = img.getPixel(i, j, 2);

            int gray = (r + g + b) / 3;
            int newValue = (gray < 127) ? 0 : 255;

            img.setPixel(i, j, 0, newValue);
            img.setPixel(i, j, 1, newValue);
            img.setPixel(i, j, 2, newValue);
        }
    }
}
Image rotateImage(const Image& img, int angle) {
    Image rotatedImg;

    if (angle == 90) {
        rotatedImg = Image(img.height, img.width);
        for (int i = 0; i < img.width; ++i) {
            for (int j = 0; j < img.height; ++j) {
                for (int k = 0; k < img.channels; ++k) {
                    rotatedImg.setPixel(img.height - 1 - j, i, k, img.getPixel(i, j, k));
                }
            }
        }
    }
    else if (angle == 180) {
        rotatedImg = Image(img.width, img.height);
        for (int i = 0; i < img.width; ++i) {
            for (int j = 0; j < img.height; ++j) {
                for (int k = 0; k < img.channels; ++k) {
                    rotatedImg.setPixel(img.width - 1 - i, img.height - 1 - j, k, img.getPixel(i, j, k));
                }
            }
        }
    }
    else if (angle == 270) {
        rotatedImg = Image(img.height, img.width);
        for (int i = 0; i < img.width; ++i) {
            for (int j = 0; j < img.height; ++j) {
                for (int k = 0; k < img.channels; ++k) {
                    rotatedImg.setPixel(j, img.width - 1 - i, k, img.getPixel(i, j, k));
                }
            }
        }
    }
    else {
        rotatedImg = img;
    }

    return rotatedImg;
}
void detectImageEdges(Image& image) {
    Image grayImage(image.width, image.height);
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int avg = (image(i, j, 0) + image(i, j, 1) + image(i, j, 2)) / 3;
            for (int k = 0; k < image.channels; k++) {
                grayImage(i, j, k) = avg;
            }
        }
    }
    int threshold = 30;
    for (int i = 0; i < image.width - 1; i++) {
        for (int j = 0; j < image.height - 1; j++) {
            int diffX = grayImage(i, j, 0) - grayImage(i + 1, j, 0);
            if (diffX < 0) diffX = -diffX;

            int diffY = grayImage(i, j, 0) - grayImage(i, j + 1, 0);
            if (diffY < 0) diffY = -diffY;

            int edgeVal = (diffX + diffY > threshold) ? 0 : 255;

            for (int k = 0; k < image.channels; k++) {
                image(i, j, k) = edgeVal;
            }
        }
    }
}
void applyOldTVFilter(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            if (j % 4 == 0) {
                for (int k = 0; k < image.channels; k++) {
                    image(i, j, k) = image(i, j, k) * 0.4;
                }
            }
        }
    }
}
void applyPurpleNightWanoFilter(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int r = image(i, j, 0) + 30;
            int g = image(i, j, 1) * 0.6;
            int b = image(i, j, 2) + 50;
            image(i, j, 0) = (r > 255) ? 255 : r;
            image(i, j, 1) = (g < 0) ? 0 : g;
            image(i, j, 2) = (b > 255) ? 255 : b;
        }
    }
}
void cropImage(Image& image) {
    int x, y, newWidth, newHeight;
    cout << "Enter starting X (left position): ";
    cin >> x;
    cout << "Enter starting Y (top position): ";
    cin >> y;
    cout << "Enter new Width: ";
    cin >> newWidth;
    cout << "Enter new Height: ";
    cin >> newHeight;

    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x + newWidth > image.width) newWidth = image.width - x;
    if (y + newHeight > image.height) newHeight = image.height - y;

    Image croppedImage(newWidth, newHeight);

    for (int i = 0; i < newWidth; i++) {
        for (int j = 0; j < newHeight; j++) {
            for (int k = 0; k < image.channels; k++) {
                croppedImage(i, j, k) = image(x + i, y + j, k);
            }
        }
    }

    image = croppedImage;
}
void applyDarkenLighten(Image& img, bool lighten) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            for (int k = 0; k < img.channels; ++k) {
                int val = img.getPixel(i, j, k);
                if (lighten) {
                    val = val + (255 - val) * 0.5;
                }
                else {
                    val = val * 0.5;
                }

                if (val > 255) val = 255;
                if (val < 0) val = 0;

                img.setPixel(i, j, k, val);
            }
        }
    }
}
void applyInvert(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            for (int k = 0; k < img.channels; ++k) {
                int val = img.getPixel(i, j, k);
                img.setPixel(i, j, k, 255 - val);
            }
        }
    }
}
void applyFrame(Image& image)
{
    int choice;
    cout << "Choose the Frame type : \n";
    cout << "1 --> Simple Frame\n";
    cout << "2 --> Fancy Frame\n";
    cout << "Your choice is : ";
    cin >> choice;
    int thickness = 15;
    if (choice == 1)
    {
        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                if (i < thickness || i >= image.width - thickness || j < 15 || j >= image.height - thickness)
                {
                    image(i, j, 0) = 0;
                    image(i, j, 1) = 0;
                    image(i, j, 2) = 255;
                }
            }
        }
    }
    else if (choice == 2)
    {
        for (int i = 0; i < image.width; i++)
        {
            for (int j = 0; j < image.height; j++)
            {
                if (i < thickness || i >= image.width - thickness || j < 15 || j >= image.height - thickness)
                {
                    if ((i >= 5 && i <= 9) || (i >= image.width - 10 && i <= image.width - 6) || (j >= 5 && j <= 9) || (j >= image.height - 10 && j <= image.height - 6))
                    {
                        image(i, j, 0) = 255;
                        image(i, j, 1) = 255;
                        image(i, j, 2) = 255;
                    }
                    else
                    {
                        image(i, j, 0) = 0;
                        image(i, j, 1) = 0;
                        image(i, j, 2) = 255;
                    }

                }

            }
        }
    }

}
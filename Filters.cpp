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

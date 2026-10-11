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
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

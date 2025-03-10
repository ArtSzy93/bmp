﻿#include "function.cpp"


int main(int arc, char * argv[]) {
    // Otwarcie pliku.
    FILE* f = fopen("test.bmp", "rb");

    if (f == nullptr) // Czy otwarty.
    {
        printf("\n\n Can't open the file");
        return -1;
    }

    printf("\n INFORMACJE O BITMAPIE\n\n");

    fread(&File.bfType, sizeof(File.bfType), 1, f);
    printf(" Typ: %x", File.bfType);

    fread(&File.bfSize, sizeof(File.bfSize), 1, f);
    printf("\n Rozmiar pliku: %d bajtow", File.bfSize);

    fread(&File.bfReserved1, sizeof(File.bfReserved1), 1, f);
    printf("\n Zarezerwowane1: %d", File.bfReserved1);

    fread(&File.bfReserved2, sizeof(File.bfReserved2), 1, f);
    printf("\n Zarezerwowane2: %d", File.bfReserved2);

    fread(&File.bfOffBits, sizeof(File.bfOffBits), 1, f);
    printf("\n Pozycja danych obrazkowych: %d", File.bfOffBits);

    printf("\n");

    fseek(f, 14, SEEK_SET);
    fread(&Picture.biSize, sizeof(Picture.biSize), 1, f);
    printf("\n Wielkosc naglowka informacyjnego: %d", Picture.biSize);

    fread(&Picture.biWidth, sizeof(Picture.biWidth), 1, f);
    printf("\n Szerokosc: %d pikseli", Picture.biWidth);

    fread(&Picture.biHeight, sizeof(Picture.biHeight), 1, f);
    printf("\n Wysokosc: %d pikseli", Picture.biHeight);

    fread(&Picture.biPlanes, sizeof(Picture.biPlanes), 1, f);
    printf("\n Liczba platow: %d", Picture.biPlanes);

    fread(&Picture.biBitCount, sizeof(Picture.biBitCount), 1, f);
    printf("\n Liczba bitow na piksel: %d (1, 4, 8, or 24)", Picture.biBitCount);

    fread(&Picture.biCompression, sizeof(Picture.biCompression), 1, f);
    printf("\n Kompresja: %d (0=none, 1=RLE-8, 2=RLE-4)", Picture.biCompression);

    fread(&Picture.biSizeImage, sizeof(Picture.biSizeImage), 1, f);
    printf("\n Rozmiar samego rysunku: %d", Picture.biSizeImage);

    fread(&Picture.biXPelsPerMeter, sizeof(Picture.biXPelsPerMeter), 1, f);
    printf("\n Rozdzielczosc pozioma: %d", Picture.biXPelsPerMeter);

    fread(&Picture.biYPelsPerMeter, sizeof(Picture.biYPelsPerMeter), 1, f);
    printf("\n Rozdzielczosc pionowa: %d", Picture.biYPelsPerMeter);

    fread(&Picture.biClrUsed, sizeof(Picture.biClrUsed), 1, f);
    printf("\n Liczba kolorow w palecie: %d", Picture.biClrUsed);

    fread(&Picture.biClrImportant, sizeof(Picture.biClrImportant), 1, f);
    printf("\n Wazne kolory w palecie: %d", Picture.biClrImportant);
    printf("\n");

    /*************************/

    FILE* w = fopen("negatyw.bmp", "wb");
    if (w == nullptr)
    {
        printf("\n\n Can't open the file");
        return -1;
    }

    fseek(w, 0, SEEK_SET);
    fwrite(&File.bfType, sizeof(File.bfType), 1, w);
    fwrite(&File.bfSize, sizeof(File.bfSize), 1, w);
    fwrite(&File.bfReserved1, sizeof(File.bfReserved1), 1, w);
    fwrite(&File.bfReserved2, sizeof(File.bfReserved2), 1, w);
    fwrite(&File.bfOffBits, sizeof(File.bfOffBits), 1, w);

    fseek(w, 14, SEEK_SET);
    fwrite(&Picture.biSize, sizeof(Picture.biSize), 1, w);
    fwrite(&Picture.biWidth, sizeof(Picture.biWidth), 1, w);
    fwrite(&Picture.biHeight, sizeof(Picture.biHeight), 1, w);
    fwrite(&Picture.biPlanes, sizeof(Picture.biPlanes), 1, w);
    fwrite(&Picture.biBitCount, sizeof(Picture.biBitCount), 1, w);
    fwrite(&Picture.biCompression, sizeof(Picture.biCompression), 1, w);
    fwrite(&Picture.biSizeImage, sizeof(Picture.biSizeImage), 1, w);
    fwrite(&Picture.biXPelsPerMeter, sizeof(Picture.biXPelsPerMeter), 1, w);
    fwrite(&Picture.biYPelsPerMeter, sizeof(Picture.biYPelsPerMeter), 1, w);
    fwrite(&Picture.biClrUsed, sizeof(Picture.biClrUsed), 1, w);
    fwrite(&Picture.biClrImportant, sizeof(Picture.biClrImportant), 1, w);

    fseek(w, sizeof(File.bfOffBits), SEEK_SET);

    int bmpImg;
    for (int i = File.bfOffBits; i < File.bfSize; i++)
    {
        fseek(f, i, SEEK_SET);
        fseek(w, i, SEEK_SET);
        fread(&bmpImg, 3, 1, f);
        bmpImg = INT_MAX - bmpImg; //Tworzymy negatyw
        fwrite(&bmpImg, 3, 1, w);
    }

    printf("\n INFORMACJE O NEGATYWIE \n\n");

    fread(&File.bfType, sizeof(File.bfType), 1, w);
    printf(" Typ: %x", File.bfType);

    fread(&File.bfSize, sizeof(File.bfSize), 1, w);
    printf("\n Rozmiar pliku: %d bajtow", File.bfSize);

    fread(&File.bfReserved1, sizeof(File.bfReserved1), 1, w);
    printf("\n Zarezerwowane1: %d", File.bfReserved1);

    fread(&File.bfReserved2, sizeof(File.bfReserved2), 1, w);
    printf("\n Zarezerwowane2: %d", File.bfReserved2);

    fread(&File.bfOffBits, sizeof(File.bfOffBits), 1, w);
    printf("\n Pozycja danych obrazkowych: %d", File.bfOffBits);

    printf("\n");

    fseek(w, 14, SEEK_SET);
    fread(&Picture.biSize, sizeof(Picture.biSize), 1, w);
    printf("\n Wielkosc naglowka informacyjnego: %d", Picture.biSize);

    fread(&Picture.biWidth, sizeof(Picture.biWidth), 1, w);
    printf("\n Szerokosc: %d pikseli", Picture.biWidth);

    fread(&Picture.biHeight, sizeof(Picture.biHeight), 1, w);
    printf("\n Wysokosc: %d pikseli", Picture.biHeight);

    fread(&Picture.biPlanes, sizeof(Picture.biPlanes), 1, w);
    printf("\n Liczba platow: %d", Picture.biPlanes);

    fread(&Picture.biBitCount, sizeof(Picture.biBitCount), 1, w);
    printf("\n Liczba bitow na piksel: %d (1, 4, 8, or 24)", Picture.biBitCount);

    fread(&Picture.biCompression, sizeof(Picture.biCompression), 1, w);
    printf("\n Kompresja: %d (0=none, 1=RLE-8, 2=RLE-4)", Picture.biCompression);

    fread(&Picture.biSizeImage, sizeof(Picture.biSizeImage), 1, w);
    printf("\n Rozmiar samego rysunku: %d", Picture.biSizeImage);

    fread(&Picture.biXPelsPerMeter, sizeof(Picture.biXPelsPerMeter), 1, w);
    printf("\n Rozdzielczosc pozioma: %d", Picture.biXPelsPerMeter);

    fread(&Picture.biYPelsPerMeter, sizeof(Picture.biYPelsPerMeter), 1, w);
    printf("\n Rozdzielczosc pionowa: %d", Picture.biYPelsPerMeter);

    fread(&Picture.biClrUsed, sizeof(Picture.biClrUsed), 1, w);
    printf("\n Liczba kolorow w palecie: %d", Picture.biClrUsed);

    fread(&Picture.biClrImportant, sizeof(Picture.biClrImportant), 1, w);
    printf("\n Wazne kolory w palecie: %d", Picture.biClrImportant);

    printf("\n");
    fclose(f); // Zamkniecie oryginalu
    fclose(w); // Zamkniecie negatywu

    return 0;
}

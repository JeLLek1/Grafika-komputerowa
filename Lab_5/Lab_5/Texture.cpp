  // Copyright 2020 JeLLek

#include "Texture.h"
#include "App.h"
#include <fstream>

Texture::Texture(std::string fileName, unsigned trianglesCount,
    unsigned framesCount, GLfloat frameTime) {
    this->imWidth = 0;
    this->imHeight = 0;
    this->imComponents = GL_BGR_EXT;
    this->imFormat = GL_RGB8;
    this->currentTime = 0.f;
    this->currentState = 0;

    this->trianglesCount = trianglesCount;
    this->framesCount = framesCount;
    this->frameTime = frameTime;

    // generowanie tekstury
    // (ilość, miejsce przechowywania id wygenerowanych tekstur)
    glGenTextures(1, &this->textureID);

    // wczytanie tekstury
    this->load(fileName);
}

// wczytanie tekstury z pliku
void Texture::load(std::string fileName) {
    // format nagłówka pliku TGA
#pragma pack(1)
    typedef struct {
        GLbyte    idlength;
        GLbyte    colormaptype;
        GLbyte    datatypecode;
        unsigned short    colormapstart;  // NOLINT
        unsigned short    colormaplength;  // NOLINT
        unsigned char     colormapdepth;  // NOLINT
        unsigned short    x_orgin;  // NOLINT
        unsigned short    y_orgin;  // NOLINT
        unsigned short    width;  // NOLINT
        unsigned short    height;  // NOLINT
        GLbyte    bitsperpixel;
        GLbyte    descriptor;
    }TGAHEADER;
#pragma pack(8)

    std::ifstream file;
    TGAHEADER tgaHeader;
    unsigned long lImageSize;  // NOLINT
    short sDepth;  // NOLINT

    file.open(fileName.c_str(), std::ios::binary);
    if (!file.is_open())
        throw "Blad podczas otwierania pliku";

    if (!file.read(reinterpret_cast<char*>(&tgaHeader), sizeof(TGAHEADER)))
        throw "Blad podczas sczytywania nagłówka pliku";

    this->imWidth = tgaHeader.width;
    this->imHeight = tgaHeader.height;
    sDepth = tgaHeader.bitsperpixel / 8;

    if (tgaHeader.bitsperpixel != 8 && tgaHeader.bitsperpixel != 24
        && tgaHeader.bitsperpixel != 32)
        throw "Blad podczas sczytywania nagłówka pliku";

    lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

    GLbyte* txtData = nullptr;
    txtData = new GLbyte[lImageSize];

    if (txtData == nullptr)
        throw "Blad podczas alokacji pamięci dla pliku";

    if (!file.read(reinterpret_cast<char*>(txtData), lImageSize)) {
        delete[] txtData;
        throw "Blad podczas sczytywania danych z pliku";
    }

    switch (sDepth) {
    case 3:
        this->imFormat = GL_BGR_EXT;
        this->imComponents = GL_RGB8;
        break;
    case 4:
        this->imFormat = GL_BGRA_EXT;
        this->imComponents = GL_RGBA8;
        break;
    case 1:
        this->imFormat = GL_LUMINANCE;
        this->imComponents = GL_LUMINANCE8;
        break;
    }

    file.close();

    // wybieranie której tekstury ustawienia się tyczą
    glBindTexture(GL_TEXTURE_2D, this->textureID);

    // Ustalenie trybu teksturowania
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // sposób zmniejszania tekstury
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // sposób zwiększania tekstury
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // uzupełnianie tekstury po przekroczeniu zakresu [0, 1] współrzędnej S
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    // uzupełnianie tekstury po przekroczeniu zakresu [0, 1] współrzędnej T
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // wczytanie tekstury
    glTexImage2D(GL_TEXTURE_2D, 0, this->imComponents, this->imWidth,
        this->imHeight, 0, this->imFormat, GL_UNSIGNED_BYTE, txtData);

    // usunięcie pamięci przydzielonej wczytanemu plikowi
    delete[] txtData;
}

// aktualizacja animacji tekstury
void Texture::update() {
    this->currentTime += App::getInstance()->dt;
    if (this->currentTime >= this->frameTime) {
        unsigned countChanges
            = static_cast<unsigned>(this->currentTime / this->frameTime);
        this->currentTime -= this->frameTime * countChanges;
        this->currentState
            = (this->currentState + countChanges) % this->framesCount;
    }
}

// ustawienie wierzchołka tekstury
void Texture::setTexture(size_t i, unsigned int edge, bool type) {
    GLfloat triangleWidth = 1.f / this->trianglesCount;
    GLfloat triangleHeight = 1.f / this->framesCount;
    GLfloat t = 0.f;
    // przesunięcie animacji
    GLfloat s = triangleHeight * this->currentState;

    i %= this->trianglesCount;
    if (type) {
        switch (edge) {
        case 0:
            t += triangleWidth * i;
            break;
        case 1:
            t += triangleWidth * (i + 1);
            break;
        default:
            t += triangleWidth * i;
            s += triangleHeight;
        }
    } else {
        switch (edge) {
        case 0:
            t += triangleWidth * i;
            s += triangleHeight;
            break;
        case 1:
            t += triangleWidth * (i + 1);
            s += triangleHeight;
            break;
        default:
            t += triangleWidth * (i + 1);
        }
    }

    glTexCoord2f(t, s);
}

// ustawienie aktywnej tekstury
void Texture::bindTexture() {
    glBindTexture(GL_TEXTURE_2D, this->textureID);
}

Texture::~Texture() {
}

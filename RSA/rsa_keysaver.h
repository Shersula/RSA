#ifndef RSA_KEYSAVER_H
#define RSA_KEYSAVER_H

class RSA_KeySaver
{
private:
    unsigned int n;
    unsigned int e;
    unsigned int d;
public:
    RSA_KeySaver(); //Конструктор, пустой
    RSA_KeySaver(unsigned int _n, unsigned int _e, unsigned int _d); //Конструктор, внос ключей в объект

    void GetKey(unsigned int* _n, unsigned int* _e, unsigned int* _d); //Возврат значений ключей

    void SaveKey(const char* FileName); //Сохранение ключей в файл

    void ReadKey(const char* FileName); //Чтение ключей из файла

    void OutKey();
};

#endif // RSA_KEYSAVER_H

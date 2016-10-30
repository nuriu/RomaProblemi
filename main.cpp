#include <iostream>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

// --- dairesel bağlı liste --- //
struct v
{
    int sayi;
    v* sonraki;
};
typedef v asker;

void Listele(asker* ilkEleman)
{
    cout << endl;
    int i = 1;
    asker* s = ilkEleman;

    do
    {
        cout << "   " << i << ". asker: " << s -> sayi << endl;
        i++;
        s = s -> sonraki;
    } while(s != ilkEleman);

    cout << endl;
}

asker* Sil(asker* ilkEleman, int silinecekDeger)
{
    asker* s = ilkEleman;
    asker* gecici;

    if(s -> sayi == silinecekDeger) // silinecek olan eleman ilk elemansa
    {
        // son elemana kadar geliyoruz.
        while (s -> sonraki != ilkEleman)
        {
            s = s -> sonraki;
        }
        // ilkEleman'ı yani ilk'i zincirden çıkarıyoruz.
        s -> sonraki = ilkEleman -> sonraki;
        // ilkEleman'ı siliyoruz.
        free(ilkEleman);
        // geriye yeni ilk eleman olacak olan ikinci elemanı döndürüyoruz.
        return s -> sonraki;
    }
    else // ilk eleman değilse
    {
        // listede aramaya başlıyoruz.
        do
        {
            // silinecek eleman bulunduysa
            if(s -> sonraki -> sayi == silinecekDeger && s -> sonraki != ilkEleman)
            {
                gecici = s -> sonraki;
                s -> sonraki = s -> sonraki -> sonraki;
                free(gecici);
                return ilkEleman;
            }
            else // bulunamadıysa sonraki elemana geçiyoruz.
            {
                s = s -> sonraki;
            }
        } while(s -> sonraki != ilkEleman);
        // silinecek eleman bulunamadıysa
        cout << "Silinecek eleman bulunamadi." << endl;
        return ilkEleman;
    }
}

asker* Ekle(asker* ilkEleman, int eklenecekDeger)
{
    // liste boş ise
    if(ilkEleman == NULL)
    {
        ilkEleman = (asker*) malloc(sizeof(asker));
        ilkEleman -> sonraki = ilkEleman;
        ilkEleman -> sayi = eklenecekDeger;
        return ilkEleman;
    }
    else // liste bir veya daha fazla elemana sahip ise
    {
        asker* s = ilkEleman;
        asker* gecici = (asker*) malloc(sizeof(asker));
        // eklenecek değer ilk elemandan küçükse
        if(ilkEleman -> sayi > eklenecekDeger)
        {
            gecici -> sayi = eklenecekDeger;
            gecici -> sonraki = ilkEleman;
            while (s -> sonraki != ilkEleman)
            {
                s = s -> sonraki;
            }
            s -> sonraki = gecici;
            return gecici;
        }
        else
        {
            // son eleman değilse ve sonraki eleman eklenecek sayidan küçükse
            // eklenecek eleman için doğru aralığı bulmaya çalışıyoruz.
            while(s -> sonraki != ilkEleman && s -> sonraki -> sayi < eklenecekDeger)
            {
                s = s -> sonraki;
            }
            // aralığı bulduktan sonra
            // büyük elemanı geçicinin sonraki işaretine atıyoruz.
            gecici -> sonraki = s -> sonraki;
            // sayimizi ekliyoruz.
            gecici -> sayi = eklenecekDeger;
            // sonraki işaretine elemanı atıyoruz.
            s -> sonraki = gecici;
            return ilkEleman;
        }
    }
}
// --- dairesel bağlı liste --- //


// --- girdiler --- //
int askerSayisi = 0, adimSayisi = 0;

void askerSayisiniAl()
{
    cout << " Asker sayisini girin: ";
    cin >> noskipws >> askerSayisi;

    if (!cin || !askerSayisi)
    {
        cout << "\n\nHATA: Asker sayisi numara olmalidir. Lutfen tekrar giris yapiniz.\n\n" << endl;
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        askerSayisiniAl();
    }
    else if (askerSayisi <= 0)
    {
        cout << "\n\nHATA: Asker sayisi 0'dan buyuk olmalidir. Lutfen tekrar giris yapiniz.\n\n" << endl;
        askerSayisiniAl();
    }
}

void adimSayisiniAl()
{
    cout << " Adim sayisini girin: ";
    cin >> noskipws >> adimSayisi;

    // girdi doğruluğu testi
    if (!cin)
    {
        cout << "\n\nHATA: Adim sayisi numara olmalidir. Lutfen tekrar giris yapiniz.\n\n" << endl;
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        adimSayisiniAl();
    }
    else if (adimSayisi <= 1)
    {
        cout << "\n\nHATA: Adim sayisi 1'den buyuk olmalidir. Lutfen tekrar giris yapiniz.\n\n" << endl;
        adimSayisiniAl();
    }
}

int main()
{
    cout << endl;
    // girdilerimizi alıyoruz.
    askerSayisiniAl();
    adimSayisiniAl();

    cout << endl;
    cout << " Girilen asker sayisi: " << askerSayisi << endl;
    cout << " Girilen adim sayisi: " << adimSayisi << endl;

    // anlık zamanı alıyoruz.
    high_resolution_clock::time_point z1 = high_resolution_clock::now();


    // bağlı listemizi oluşturuyoruz
    asker* ilk = NULL;

    // askerleri ekliyoruz
    for (int i = 0; i < askerSayisi; i++)
    {
        ilk = Ekle(ilk, i + 1);
    }

    // ilk durumu listeliyoruz
    Listele(ilk);

    int adim = 1;
    asker* s = ilk; // sayacımız

    while (askerSayisi >= adimSayisi)
    {
        if (adim % adimSayisi == 0)     // adım sayımızın tam katı olan bir adımdaysak
        {                               // askerimizi bulduk demektir.
            asker* g = s -> sonraki;    // gecicimiz
            ilk = Sil(ilk, s -> sayi);  // askeri siliyoruz
            s = g;                      // kaldığımız yerden devam ediyoruz.
            askerSayisi--;              // asker sayımızı 1 azaltıyoruz.
        }
        else
        {
            s = s -> sonraki;           // sonraki askere geçiyoruz.
        }

        adim++;                         // adımımızı bir arttırıyoruz.
    }


    cout << " Sag kalan askerler; " << endl;
    Listele(ilk);

    cout << endl;

    // anlık zamanı alıyoruz.
    high_resolution_clock::time_point z2 = high_resolution_clock::now();

    // son aldığımız zamandan ilk aldığımız zamanı çıkartıp mikrosaniye cinsine çeviriyoruz.
    auto sure = duration_cast<microseconds>(z2 - z1).count();

    cout <<" Problem " << sure << " mikrosaniyede cozuldu!" << endl;

    cout << endl;
    return 0;
}

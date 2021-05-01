#include <Arduino.h>

unsigned long gecmisZaman = 0;
unsigned long belirlenenZaman = 1000;
unsigned long anlikZaman = 0;

unsigned long ayarlananZaman = 0;
unsigned long zaman = 0;

int butonDurumu = 0;
bool zamanVerisiGeldi = false;

void setup()
{
  Serial.begin(9600);  // Serial Port 9600 boundrate değerinde belirleniyor
  pinMode(13, OUTPUT); // Arduino üzerindeki led 13. pine bağlı olduğu için 13. pin output olarak belirleniyor
  delay(1);
  digitalWrite(13, LOW); // 13. pin başlangıçta LOW olarak belirleniyor
}
void ledOn() { digitalWrite(13, HIGH); } //13. pini aktif edip ledi yakacak olan fonksiyon
void ledOff() { digitalWrite(13, LOW); } //13. pini pasif edip ledi söndürecek olan fonksiyon

void loop()
{

  if (zamanVerisiGeldi) // Zaman verisi geldiğinde true olarak tanımlanan değişken sayesinde if in içerisine giriyor
  {
    anlikZaman = millis();                          // millis fonksiyonu sayesinde Arduinonun anlık zaman verisi anlikZaman değişkenine aktarılıyor
    if (anlikZaman - gecmisZaman >= ayarlananZaman) //anlık zaman ve geçmiş zaman arasındaki fark, belirlenen zamandan büyük veya eşit ise ifin içine girer
    {
      gecmisZaman = anlikZaman; // geçmiş zaman anlık zamana eşitlenir
      // digitalWrite(13, HIGH);   //python ile arduinoda aynı anda serial port açılmadığı için test etmek için 13. pini aktif ettim
      Serial.write('a');        // seri porttan a verisi gönderilir
      zamanVerisiGeldi = false; // zamanVerisiGeldi değişkeni if in kırılması için false olarak ayarlanır
    }
    else //anlık zaman ve geçmiş zaman arasındaki fark, belirlenen zamandan büyük değilse 13. pin pasif edilir (TEST İÇİN KULLANILDI)
    {
      //digitalWrite(13, LOW);
    }
  }
  if (zamanVerisiGeldi == false) // Zaman verisi gelmediği durumda if in içine girer ve geçmiş zamanı anlık zamana eşitler
  {
    gecmisZaman = millis();
  }
}

void serialEvent() // Serial port kesmesini sağlayan fonksiyon
{
  while (Serial.available() > 0) // Serial porttan veri aldığında döngüye giriyor
  {

    zaman = Serial.parseInt();       // okunan ilk değer zaman değişkenine aktarılıyor
    butonDurumu = Serial.parseInt(); // okunan ikinci değer butonDurumu değişkenine aktarılıyorz

    if (Serial.read() == '\n') // gelen veri sonlanmışsa if in içine girer ve buton durumları işitlikleri kontrol eder
    {
      if (butonDurumu == 1) // buton durumu 1 ise ledOn fonksiyonunu çalıştırıyor
      {
        ledOn();
      }
      else if (butonDurumu == 0) // buton durumu 0 ise ledOff fonksiyonunu çalıştırıyor
      {
        ledOff();
      }
      else if (butonDurumu == 2) // buton durumu 2 ise zamanı saymak için kullanılan fonksiyonu çalıştırıyor
      {
        zamanVerisiGeldi = true; // Zaman verisi geldiğinde değişken true olarak tanımlanıyor
        ayarlananZaman = zaman;  // Seri porttan gelen zaman verisi ayarlanan zaman değişkenine eşitlniyor
      }
    }
  }
}

//MEMBACA SENSOR----------------------------------------------------------------------------------------------------------------------------------------------------
/*const int sensorPin = A0;  // Pin analog tempat LM35 terhubung
float suhuCelsius;         // Variabel untuk menyimpan suhu dalam derajat Celsius

void setup() {
  Serial.begin(9600);  // Inisialisasi komunikasi serial
}

void loop() {
  int nilaiAnalog = analogRead(sensorPin);  // Membaca nilai analog dari LM35
  
  // Konversi nilai analog ke tegangan (0 - 1023 menjadi 0 - 5V)
  float tegangan = nilaiAnalog * (5.0 / 1023.0);
  
  // Konversi tegangan menjadi suhu dalam derajat Celsius
  suhuCelsius = tegangan * 100;
  
  // Menampilkan suhu pada Serial Monitor
  Serial.print("Suhu: ");
  Serial.print(suhuCelsius);
  Serial.println(" C");

  delay(1000);  // Tunggu 1 detik sebelum pembacaan berikutnya
}*/



//MEMBUAT KONTROL ON OF BEDASARKAN NILAI SUHU MENGGUNAKAN LOGIKA IF ELSE----------------------------------------------------------------------------------------------
/*
const int sensorPin = A0;  // Pin analog tempat LM35 terhubung
float suhuCelsius;         // Variabel untuk menyimpan suhu dalam derajat Celsius
bool fanOn = false;        // Status kipas

void setup() {
  Serial.begin(9600);      // Inisialisasi komunikasi serial
  pinMode(8, OUTPUT);      // Pin kipas sebagai output
}

void loop() {
  int nilaiAnalog = analogRead(sensorPin);  // Membaca nilai analog dari LM35
  
  // Konversi nilai analog ke tegangan (0 - 1023 menjadi 0 - 5V)
  float tegangan = nilaiAnalog * (5.0 / 1023.0);
  
  // Konversi tegangan menjadi suhu dalam derajat Celsius
  suhuCelsius = tegangan * 100;
  
  // Menampilkan suhu pada Serial Monitor
  Serial.print("Suhu: ");
  Serial.println(suhuCelsius);

  delay(1000);  // Tunggu 1 detik sebelum pembacaan berikutnya

  // Logika On/Off berdasarkan suhu
  if (suhuCelsius > 30 && !fanOn) {
    digitalWrite(8, HIGH);    // Menyalakan kipas
    Serial.println("Kipas: ON");
    fanOn = true;
  } 
  else if (suhuCelsius < 28 && fanOn) {
    digitalWrite(8, LOW);     // Mematikan kipas
    Serial.println("Kipas: OFF");
    fanOn = false;
  }
}
*/




const int sensorPin = A0;  // Pin analog tempat LM35 terhubung
float suhuCelsius;         // Variabel untuk menyimpan suhu dalam derajat Celsius

unsigned long startTimeON = 0;  // Waktu ketika kipas menyala
int fan_status = 0;           // Status kipas

float maxTemp = -1000;        // Inisialisasi suhu maksimum
float minTemp = 1000;         // Inisialisasi suhu minimum

void setup() {
  Serial.begin(9600);         // Inisialisasi komunikasi serial
  pinMode(8, OUTPUT);         // Pin kipas
}

void loop() {
  int nilaiAnalog = analogRead(sensorPin);  // Membaca nilai analog dari LM35
  
  // Konversi nilai analog ke tegangan (0 - 1023 menjadi 0 - 5V)
  float tegangan = nilaiAnalog * (5.0 / 1023.0);
  
  // Konversi tegangan menjadi suhu dalam derajat Celsius
  suhuCelsius = tegangan * 100;
  
  // Menampilkan suhu pada Serial Monitor
  Serial.print("Suhu: ");
  Serial.println(suhuCelsius);

  delay(1000);  // Tunggu 1 detik sebelum pembacaan berikutnya

  // Mengontrol kipas berdasarkan rentang suhu
  if (suhuCelsius > 30 && fan_status == 0) {
    digitalWrite(8, HIGH);    // Menyalakan kipas
    Serial.println("Kipas: ON");
    fan_status = 1;           // Mengubah status kipas menjadi ON
    startTimeON = millis();     // Mencatat waktu kipas menyala
    // Reset maxTemp dan minTemp saat kipas menyala
    maxTemp = suhuCelsius;
    minTemp = suhuCelsius;
  } 


  

  
  else if (fan_status == 1) {
    // Update maxTemp dan minTemp jika kipas sudah menyala
    if (suhuCelsius > maxTemp) {
      maxTemp = suhuCelsius;  // Perbarui maxTemp
    }
    if (suhuCelsius < minTemp) {
      minTemp = suhuCelsius;  // Perbarui minTemp
    }



    // Jika suhu turun di bawah batas, matikan kipas
    if (suhuCelsius < 30) {
      digitalWrite(8, LOW);     // Mematikan kipas
      Serial.println("Kipas: OFF");
      fan_status = 0;           // Mengubah status kipas menjadi OFF

      // Hitung waktu aktif kipas (cooling time) dalam milidetik
      unsigned long coolingTime = millis() - startTimeON;
      Serial.print("Cooling Time: ");
      Serial.print(coolingTime);  // Waktu pendinginan dalam milidetik
      Serial.println(" ms");

      
      // Tampilkan maxTemp dan minTemp saat kipas mati
      Serial.print("MaxTemp: ");
      Serial.println(maxTemp);
      Serial.print("MinTemp: ");
      Serial.println(minTemp);

      // Hitung fluktuasi suhu
      float tempFluctuation = maxTemp - minTemp;
      Serial.print("Fluktuasi Suhu: ");
      Serial.print(tempFluctuation);
      Serial.println(" C");

      // Reset nilai suhu untuk siklus berikutnya
      maxTemp = -1000;  // Setel ulang maxTemp
      minTemp = 1000;   // Setel ulang minTemp
    }
  }
}

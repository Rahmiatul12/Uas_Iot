# Smart Room Monitor
Monitoring suhu dan kelembaban ruangan menggunakan sensor DHT (Digital Humidity and Temperature) yang dihubungkan dengan aplikasi mobile dan MQTT. 

## Penjelasan Program

### Wokwi

Program ini merupakan implementasi teori yang didapatkan selama perkuliahan Internet of Things, rangkaian yang dibuat merupakan rangkaian virtual menggunakan Wokwi IoT simulator (embeed). Rangkaian dibuat menggunakan board ESP32 yang terhubung dengan resistor, led, dan sensor DHT22.

![Rangkaian-Digital-Smart-Room](https://github.com/AlyaniNS/Smart-Room/assets/74224380/1ac1d789-7bd5-4fae-9dc6-c8ac5daa85ff)


### Kodular
Rangkaian digital kemudian dihubungkan dengan aplikasi mobile yang dibuat menggunakan Kodular dengan tampilan sebagai berikut:
![UI-Smart-Room](https://github.com/AlyaniNS/Smart-Room/assets/74224380/c13a78c6-4878-4245-9397-63bb35340962)


Terdapat 2 buah screen dari aplikasi mobile, screen pertama merupakan dashboard untuk monitoring suhu dan kelembaban ruangan yang dilengkapi dengan 2 buah switch untuk masing-masing sensor. Screen yang kedua merupakan nama-nama anggota kelompok. 
Terdapat 5 buah button dalam program ini:
|No| Gambar | Fungsi | 
|--|--------|--------|
| 1|![About-Us-Button](https://github.com/AlyaniNS/Smart-Room/assets/74224380/0581949b-137a-448d-8cf6-88d4c2310a23)|Pindah ke page About Us|
| 2|![Back-Button](https://github.com/AlyaniNS/Smart-Room/assets/74224380/3c11416f-33c3-4be0-8bb7-e2235b98b602)|Pindah ke page Dashboard|
| 3|![Connect-MQTT-Button](https://github.com/AlyaniNS/Smart-Room/assets/74224380/27e388d8-51e3-4839-ac5f-031402aa6095)|Menghubungkan aplikasi ke MQTT|
| 4|![Temperature-Switch](https://github.com/AlyaniNS/Smart-Room/assets/74224380/2b59ec97-f3f8-44eb-83a9-7822165f291b)|Menyalakan dan mematikan sensor temperatur|
| 5|![Humidity-Switch](https://github.com/AlyaniNS/Smart-Room/assets/74224380/6ea5f293-60b2-4ed4-a1c4-f6bdec69dc48)|Menyalakan dan mematikan sensor kelembaban|



![App-Demo](https://github.com/AlyaniNS/Smart-Room/assets/74224380/08940623-0862-44f9-beea-c0afcddeca3d)

Dapat dilihat pada demo aplikasi, ketika sensor temperatur dimatikan, maka sensor kelembaban akan ikut mati, begitu juga sebaliknya. Karena sensor ini berada di 1 sensor yang sama, jadi penggunaannya tidak dapat dipisahkan.

### MQTT
Data yang diperoleh oleh sensor dapat ditampilkan di aplikasi mobile dengan bantuan MQTT. 
- Rangkaian digital yang dibuat menggunakan Wokwi berfungsi sebagai publisher dan subscriber. Sebagai publisher, rangkaian digital mengirimkan informasi nilai temperatur dan kelembaban. Lalu sebagai subscriber, rangkaian digital menerima nilai switch yang dikirimkan oleh aplikasi mobile apakah switch tersebut dinyalakan atau dimatikan.
- Aplikasi mobile bertindak sebagai publisher dan subscriber. Sebagai publisher, aplikasi mobile mengirimkan nilai switch. Lalu sebagai subscriber, aplikasi mobile menerima nilai temperatur dan kelembaban yang dikirimkan oleh rangkaian digital.

Aktivitas publish dan subscribe tersebut dijembatani oleh broker—dalam program ini kami menggunakan broker shiftr.io—sehingga setiap aktivitasnya bisa dikirim dan diterima oleh rangkaian digital maupun aplikasi mobile.

![Shiftr-Visualization](https://github.com/AlyaniNS/Smart-Room/assets/74224380/9c1857bb-fe1c-46c4-970a-fb5be3aded7d)


Data yang diperoleh oleh sensor DHT22 disimpan kedalam database dengan menggunakan webhook yang diatur menggunakan broker.

![Database-Prove](https://github.com/AlyaniNS/Smart-Room/assets/74224380/a786e26e-2bd7-4ad5-8fe6-e3ada7421a63)

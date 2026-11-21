[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TM1929

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/tm1929/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der TM1929 ist ein LED-Treiberbaustein mit Konstantstromregelung, der über eine lineare Stromsteuerung mit 128 Stufen verfügt. Er enthält 18 unabhängige, niederohmige LED-Treiberkanäle, die an jeder Ausgangsstufe einen Konstantstrom von 3–40 mA bereitstellen können. Der TM1929 nutzt die I2C-Bus-Struktur; über entsprechende Code-Einstellungen lässt sich der Strom für jeden Kanal individuell anpassen. Insgesamt stehen 128 Stromstufen zur Verfügung, die einen Bereich von 0 % bis 190 % abdecken. Jeweils drei LEDs teilen sich einen gemeinsamen Freigabeschalter (Enable-Schalter); durch die Steuerung dieses Schaltsignals lässt sich die Helligkeit der einzelnen Farben bei RGB-Beleuchtungen variieren.

LibDriver TM1929 ist ein von LibDriver bereitgestellter, voll ausgestatteter Treiber für den TM1929. Er unterstützt LED-Anzeigen sowie weitere Funktionen. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver TM1929-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver TM1929 IIC.

/test enthält den Testcode des LibDriver TM1929-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver TM1929-Beispielcode.

/doc enthält das LibDriver TM1929-Offlinedokument.

/Datenblatt enthält TM1929-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

#### example basic

```C
#include "driver_tm1929_basic.h"

uint8_t res;
uint8_t j;
uint8_t buffer[18];
uint8_t hex_code = 127;

/* basic init */
res = tm1929_basic_init(TM1929_ADDRESS_0);
if (res != 0)
{
    return 1;
}

...
    
/* make brightness */
for (j = 0; j < 18; j++)
{
    buffer[j] = hex_code;
}
res = tm1929_basic_set_brightness(0, buffer, 18);
if (res != 0)
{
    tm1929_interface_debug_print("tm1929: set brightness failed.\n");
    (void)tm1929_basic_deinit();

    return 1;
}

/* output */
tm1929_interface_debug_print("tm1929: set brightness 0x%02X.\n", hex_code);

...
    
/* deinit */
(void)tm1929_basic_deinit();

return 0;
```
### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/tm1929/index.html](https://www.libdriver.com/docs/tm1929/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.
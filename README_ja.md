[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TM1929

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/tm1929/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

TM1929は、128段階のリニア電流調整機能を備えた定電流LEDドライバ回路です。内部には18個の独立した低インピーダンスLED駆動チャンネルが搭載されており、各出力段で3〜40mAの定電流を供給可能です。TM1929はI2Cバス構造を採用しており、コード設定を通じて各チャンネルの電流値を調整できます。電流調整は0%から190%の範囲で、計128段階の設定が可能です。3つのLEDごとにイネーブルスイッチが割り当てられており、このスイッチ信号を制御することで、RGB各色の明るさを変化させることができます。

LibDriver TM1929は、LibDriverが提供するTM1929向けの多機能ドライバです。LED表示機能に加え、その他の機能も備えています。なお、LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver TM1929のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver TM1929用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver TM1929ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver TM1929プログラミング例が含まれています。

/ docディレクトリには、LibDriver TM1929オフラインドキュメントが含まれています。

/ datasheetディレクトリには、TM1929データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/tm1929/index.html](https://www.libdriver.com/docs/tm1929/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。
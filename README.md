# libj
X68000 XC Library compatible jfctype/jstring functions.

elf2x68k + newlib の環境でも `jstrcmp` や `iskanji` など、XCで提供されている日本語処理関数を使えるようにするための互換ライブラリです。以下のヘッダーファイルで提供される関数群に加えて、`jstricmp`を使うことができます。

- jfctype.h
- jstring.h

なお、これらのヘッダーファイルについては、XC 2.0のオリジナルのヘッダーファイル(一部改変あり)をそのままこのリポジトリに含めてあります。オリジナルは以下のX68000 LIBRARYなどから入手可能です。

- http://retropc.net/x68000/software/sharp/xc21/
# libj
X68000 XC Library compatible jfctype/jstring functions.

elf2x68k + newlib の環境でも `jstrcmp` や `iskanji` など、XCで提供されている日本語処理関数を使えるようにするための互換ライブラリです。以下のヘッダーファイルで提供される関数群に加えて、`jstricmp`を使うことができます。

- jfctype.h
- jstring.h

なお、これらのヘッダーファイルについては、XC 2.1のオリジナルのヘッダーファイル(一部改変あり)をそのままこのリポジトリに含めてあります。オリジナルは以下のX68000 LIBRARYなどから入手可能です。

- http://retropc.net/x68000/software/sharp/xc21/

使う時は、サブモジュールとして組み込むのが簡単です。例えばプロジェクト直下にて以下を実行します。

```
git submodule add https://github.com/tantanGH/libj.git libs/libj
```

以下のようなツリーとなります。

```
my_app/
├── .git/
├── .gitmodules
├── libs/
│   └── libj/
│       ├── include/
│       └── lib/libj.a
└── src/
    ├── main.c
    └── Makefile
```

ヘッダー検索パスとライブラリ検索パスをMakefile内で
```
-I../libs/libj/include
-L../libs/libj/lib
```
のように指定し、`-lj` でリンクできます。

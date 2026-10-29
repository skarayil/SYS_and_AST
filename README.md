# 🌳 Parsing & AST

<div align="center">

![42 School](https://img.shields.io/badge/School-42-black?style=for-the-badge&logo=42)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Parser](https://img.shields.io/badge/Recursive_Descent-Parser-orange?style=for-the-badge)
![Exercises](https://img.shields.io/badge/Exercises-2-success?style=for-the-badge)

**Metni oku. Yapıyı anla. Ağacı kur.**

*`vbc` ve `argo`.*

[Ne Öğreniyorsun?](#-ne-öğreniyorsun) • [Egzersizler](#-egzersizler) • [Kurulum](#-kurulum) • [Temel Kavramlar](#-temel-kavramlar)

</div>

---

## 🎯 Projenin Amacı

<img align="right" alt="Algorithm Animation" width="300" src="https://media3.giphy.com/media/v1.Y2lkPTc5MGI3NjExM29ha2xqaW1jM3k2bHFlZGIyZG1xMXhjYzZncjR3Z3Qxb2RjMW5vZiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/bjC8sdurIYfElHXfxR/giphy.gif">

Bu bölüm tamamen **ayrıştırma (parsing)** ve **soyut sözdizimi ağacı (AST)** üzerinedir. Ham bir metni — bir matematik ifadesini ya da bir JSON girdisini — karakter karakter okuyup bellekte bir **ağaç yapısına** dönüştürmeyi öğrenirsin. Her egzersiz aynı fikri farklı bir problemde uygular:

| Egzersiz | Konu | Kritik Fonksiyonlar |
|----------|------|---------------------|
| `vbc` | Matematik İfadesi Çözümleyici | `parse_expr`, `parse_term`, `parse_factor`, `eval_tree`, `destroy_tree` |
| `argo` | JSON Parser | `getc`, `ungetc`, `parse_value`, `parse_map`, `serialize`, `free_json` |

---

## 🧠 Ne Öğreniyorsun?

### 🔽 Recursive Descent Parsing
Gramerin her kuralı için bir fonksiyon yazmak. Fonksiyonlar birbirini çağırarak iç içe yapıları (parantezler, iç içe map'ler) doğal biçimde çözer.

### 🌲 AST (Abstract Syntax Tree)
Metni doğrudan hesaplamak yerine önce bir ağaç kurmak, sonra o ağacı gezmek. Ağaç bir kez kurulduktan sonra hem değerlendirmek (`vbc`) hem de yeniden yazdırmak (`argo`) mümkündür.

### 👀 Lookahead (İleri Bakış)
Bir sonraki karaktere tüketmeden bakmak: `vbc` içinde `**s` ile, `argo` içinde `getc` + `ungetc` ile yazılan `peek()` ile.

### 🧹 Bellek Yönetimi
Her hata yolunda daha önce ayrılmış belleği doğru sırayla serbest bırakmak. Yarım kalmış bir ağaç sızıntı bırakmamalı.

### ❌ Hata Raporlama
Beklenmeyen bir karakter ya da girdinin erken bitmesi durumunda standart formatta mesaj yazdırmak.

---

## 📂 Egzersizler

### 1️⃣ vbc — Matematik İfadesi Çözümleyici

#### 📝 Görev

```bash
./vbc '3+4*5'    # → 23
```

Argüman olarak verilen ifadeyi hesaplayıp sonucu yazdırır.

- Desteklenen işlemler: `+`, `*` ve parantez `( )`
- Değerler yalnızca tek haneli sayılardır (`0`–`9`)
- Boşluk işlenmez
- Hata durumunda mesaj yazdırılır ve program `1` ile çıkar:
  - `Unexpected token '%c'`
  - `Unexpected end of input`
- İzin verilen fonksiyonlar: `malloc`, `calloc`, `realloc`, `free`, `printf`, `isdigit`, `write`

#### 🔍 Çalışma Mantığı

Gramer, öncelik sırasına göre üç seviyeden oluşur. `*` daha derinde olduğu için `+`'dan önce bağlanır:

```
expr   := term   ( '+' term   )*
term   := factor ( '*' factor )*
factor := '(' expr ')' | digit
```

| Fonksiyon | Görevi |
|-----------|--------|
| `parse_expr` | `+` ile bağlanan terimleri toplar |
| `parse_term` | `*` ile bağlanan faktörleri çarpar |
| `parse_factor` | Parantezli ifadeyi ya da tek rakamı çözer |
| `parse_digit` | Rakamı `VAL` düğümüne çevirir |

`3+4*5` için oluşan ağaç:

```
        (+)
       /   \
     (3)   (*)
          /   \
        (4)   (5)
```

`eval_tree` ağacı özyinelemeli gezer: `ADD` toplar, `MULTI` çarpar, `VAL` kendi değerini döner.

#### 📢 Hata Mesajları

```
Unexpected token '<c>'
Unexpected end of input
```

#### 📁 Dosya Yapısı

```
vbc/
├── vbc.h       # node yapısı, t_nty enum'u, prototipler
├── main.c      # argüman kontrolü, parse → eval → free
├── parse.c     # parse_expr / term / factor / digit
├── eval.c      # eval_tree
├── tree.c      # new_node, destroy_tree
├── error.c     # unexpected, accept, expect
└── Makefile
```

#### ⚠️ Kritik Nokta

> Bir alt ifade hata verdiğinde, o ana kadar kurulmuş **sol ve sağ alt ağaçlar** `destroy_tree` ile serbest bırakılmalıdır. Ayrıca ifade bittiğinde `*s` hâlâ `'\0'` değilse (örneğin `1+2)`), fazlalık karakter `Unexpected token` olarak raporlanır.

#### 🧪 Test

```bash
cd vbc && make
./vbc '(3+4)*5'
./vbc '3+4*5'
./vbc '1+'
./vbc '1+2)'
./vbc '((1+3)*12+(3*(2+6))'
```

Beklenen çıktı:
```
35
23
Unexpected end of input
Unexpected token ')'
Unexpected token '2'
```

---

### 2️⃣ argo — JSON Parser

#### 📝 Görev

```c
int argo(json **dst, FILE *stream);
```

Bir akıştan JSON okuyup `argo.h` içinde tanımlı AST yapısına dönüştürür.

- Başarıda `1`, hatada `-1` döner
- Yalnızca **sayılar**, **string'ler** ve **map'ler** desteklenir
- Sayılar `scanf("%d")` gibi basit `int` değerleridir
- String içinde yalnızca `\\` ve `\"` kaçışları işlenir
- Boşluklar **geçersiz token** sayılır
- Hata durumunda:
  - `Unexpected token '%c'`
  - `Unexpected end of input`
- Çıktı, girdi ile **birebir aynı** olmalıdır (hatalar hariç)

#### 🔍 Çalışma Mantığı

```
          parse_value
              │  peek()
   ┌──────────┼───────────────┐
   │          │               │
  '"'        '{'          '-' veya rakam
   │          │               │
parse_string  parse_map   parse_integer
   │          │  ▲
   │          │  └── her değer için parse_value (özyineleme)
   ▼          ▼
 STRING       MAP            INTEGER
```

AST yapısı bir `union` üzerine kuruludur:

```c
struct s_json
{
    t_type type;            // MAP, INTEGER, STRING
    union {
        int    integer;
        char  *string;
        map    object;      // pair *data + size_t size
    } value;
};
```

`{"a":1,"b":"x"}` için ağaç:

```
MAP
 ├── "a" ──► INTEGER (1)
 └── "b" ──► STRING  ("x")
```

| Fonksiyon | Görevi |
|-----------|--------|
| `peek` | `getc` + `ungetc` ile sonraki karaktere tüketmeden bakar |
| `accept` | Karakter eşleşirse tüketir, `1` döner |
| `expect` | Eşleşmezse hata yazdırır |
| `read_string` | Tırnaklar arası metni, kaçışları çözerek okur (dinamik büyüyen buffer) |
| `parse_map` | `key:value` çiftlerini `,` ile ayırarak okur |
| `add_pair` | `realloc` ile map'e yeni çift ekler |
| `serialize` | AST'yi tekrar JSON olarak `write` ile yazar |
| `free_json` | Ağacı özyinelemeli serbest bırakır |

#### 📁 Dosya Yapısı

```
argo/
├── argo.h        # json, pair, map tipleri ve prototipler
├── main.c        # argo → serialize → free_json
├── argo.c        # argo(): parse_value + sondaki fazlalık kontrolü
├── parse.c       # parse_value / string / integer / map
├── error.c       # peek, unexpected, accept, expect
├── serialize.c   # AST → JSON çıktısı
├── memory.c      # free_json
└── Makefile
```

#### ⚠️ Kritik Nokta

> `{"a":1,}` gibi sondaki virgülde beklenen hata `Unexpected token '}'` olmalıdır: `,` sonrası yeni bir anahtar beklenir, kapanış parantezi değil. Ayrıca parse bittiğinde akışta **hâlâ karakter varsa** (`argo()` içindeki son `peek` kontrolü) bu da hata sayılır ve oluşan ağaç serbest bırakılır.

#### 🧪 Test

```bash
cd argo && make
echo -n '1' | ./argo /dev/stdin
echo -n '"escape! \" "' | ./argo /dev/stdin
echo -n '{"tomatoes":42,"potatoes":234}' | ./argo /dev/stdin
echo -n '{"recursion":{"recursion":"recursion"}}' | ./argo /dev/stdin
echo -n '"unfinished string' | ./argo /dev/stdin
echo -n '{"no value?":}' | ./argo /dev/stdin
echo -n '{"no other value?":1,}' | ./argo /dev/stdin
```

Beklenen çıktı:
```
1
"escape! \" "
{"tomatoes":42,"potatoes":234}
{"recursion":{"recursion":"recursion"}}
Unexpected end of input
Unexpected token '}'
Unexpected token '}'
```

---

## 🚀 Kurulum

### Gereksinimler

- C derleyici: `cc` / `gcc`
- Unix benzeri sistem: Linux, macOS, WSL
- GNU Make

### Derleme

```bash
# Repoyu klonla
git clone https://github.com/skarayil/sys-ast.git
cd sys-ast

# Her egzersizi ayrı ayrı derle
cd vbc  && make && cd ..
cd argo && make && cd ..
```

### Temizlik

```bash
make clean    # object dosyalarını sil
make fclean   # binary + object dosyalarını sil
make re       # temizle ve yeniden derle
```

> Derleme bayrakları: `vbc` için `-Wall -Wextra -Werror`, `argo` için ek olarak `-std=c99`.

---

## 📚 Temel Kavramlar

### Operatör Önceliği Gramerle Çözülür

```c
// parse_expr, '+' için parse_term'i çağırır.
// parse_term, '*' için parse_factor'ı çağırır.
// Daha derindeki kural daha sıkı bağlanır → 3+4*5 = 3+(4*5)
```

### `accept` / `expect` Çifti

```c
if (accept(s, '('))      // varsa tüket, yoksa devam et
    ...
if (!expect(s, ')'))     // zorunlu: yoksa hata yazdır
    ...
```

### `peek` ile Lookahead (argo)

```c
int peek(FILE *stream)
{
    int c = getc(stream);
    if (c != EOF)
        ungetc(c, stream);   // karakteri akışa geri koy
    return (c);
}
```

### Hata Yolunda Temizlik

```c
right = parse_term(s);
if (!right)
{
    destroy_tree(left);      // şimdiye kadar kurulan ağacı bırakma
    return (NULL);
}
```

### Sol Birleşimli Ağaç Kurma

```c
while (accept(s, '+'))
{
    right  = parse_term(s);
    parent = new_node(ADD);
    parent->l = left;        // eski ağaç sol çocuk olur
    parent->r = right;
    left = parent;           // yeni kök
}
```

---

## ⚠️ Yaygın Hatalar

| Hata | Sonuç | Çözüm |
|------|-------|-------|
| Hata yolunda alt ağacı `free` etmemek | Bellek sızıntısı | Her `return (NULL)` öncesi `destroy_tree` çağır |
| Parse sonrası `*s` / `peek` kontrolü yapmamak | `1+2)` gibi girdiler kabul edilir | Ana fonksiyonda kalan karakteri `unexpected` ile raporla |
| `argo`'da boşlukları yok saymak | Geçersiz girdi kabul edilir | Boşluk bir token'dır; `unexpected` ile hata ver |
| Kaçış sonrası karakteri kontrol etmemek | `\n` gibi desteklenmeyen kaçış geçer | `\` sonrası yalnızca `\` ve `"` kabul et |
| `realloc` hatasında eski pointer'ı kaybetmek | Sızıntı | Geçici pointer kullan, başarılıysa ata |
| Sondaki virgülü kabul etmek | `{"a":1,}` geçerli sayılır | `,` sonrası yeni anahtar zorunlu |

---

<div align="center">

*Bu iki egzersizi bitirdiğinde, bir metnin kurallarını koda nasıl dökeceğini,*
*onu bir ağaca nasıl dönüştüreceğini ve hataları nasıl yakalayacağını*
*somut olarak kavramış olacaksın.*

### 👩‍💻 Created by Sude Naz Karayıldırım

**⭐ Eğer bu proje işinize yaradıysa, repo'ya star vermeyi unutmayın!**

[![42 Profile](https://img.shields.io/badge/42%20Profile-skarayil-black?style=flat-square&logo=42&logoColor=white)](https://profile.intra.42.fr/users/skarayil)
[![GitHub](https://img.shields.io/badge/GitHub-skarayil-181717?style=flat-square&logo=github&logoColor=white)](https://github.com/skarayil)

</div>

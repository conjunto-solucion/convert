## Introducción

Este programa inicialmente surgió cuando buscaba una solución al problema de compatibilidad
con Google Docs descrito [aquí](https://forum.manjaro.org/t/issue-with-uploading-a-libreoffice-generated-docx-files-to-google-drive/158702). Decidí que la opción más fácil era convertir todos mis archivos .docx al formato .odt antes de subirlos.

La conversión de un archivo a la vez se puede hacer de manera sencilla con soffice, pero preferí escribir mi propia utilidad que permita convertir múltiples archivos en un mismo comando, y con una sitaxis 
sencilla.

## Compilación

En el directorio principal:

```
$ gcc -o ./convert ./src/convert.c
```

## Uso

```
$ convert <formato destino> <archivo 1> <archivo 2> ... <archivo n>
```

Ejemplo:

`$ convert pdf ./test.docx ./test2.docx`

Creará los archivos test.pdf y test2.pdf en el directorio actual.

## Notas

El programa se vale de LibreOffice para realizar las conversiones.
Es capaz de realizar las conversiones que permita su instalación de LibreOffice (en mi caso LibreOffice 6.4.7.2), tales como:

* Formatos de texto

    .docx → .pdf, .doc, .odt, .txt, .html, .rtf, etc.

    .odt → .pdf, .docx, .doc, .txt, .html, .rtf, etc.

    .doc → .pdf, .docx, .odt, .txt, .html, .rtf, etc.

* Formatos de hoja de cálculo

    .xlsx → .pdf, .ods, .csv, .html, .xls, etc.

    .ods → .pdf, .xlsx, .csv, .html, .xls, etc.

    .xls → .pdf, .xlsx, .ods, .csv, .html, etc.

    .csv → .pdf, .xlsx, .ods, .xls, etc.

* Formatos de presentación

    .pptx → .pdf, .odp, .ppt, etc.

    .odp → .pdf, .pptx, .ppt, etc.

    .ppt → .pdf, .pptx, .odp, etc.

* Formatos gráficos

    .svg → .pdf, .png, .jpg, etc.

    .png → .pdf, .svg, .jpg, etc.

    .jpg → .pdf, .png, .svg, etc.

* Otros formatos

    .html → .pdf, .docx, .odt, etc.

    .txt → .pdf, .docx, .odt, etc.

    .rtf → .pdf, .docx, .odt, etc.

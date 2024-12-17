## Introducción

Este programa inicialmente surgió cuando buscaba una solución al problema de compatibilidad
con Google Docs descrito [aquí](https://forum.manjaro.org/t/issue-with-uploading-a-libreoffice-generated-docx-files-to-google-drive/158702). Decidí que la opción más fácil era convertir todos mis archivos .docx al formato .odt antes de subirlos.

La conversión de un archivo a la vez se puede hacer de manera sencilla con soffice, pero preferí escribir mi propia utilidad que permita convertir múltiples archivos en un mismo comando, y con una sitaxis 
sencilla.

## Compilación

En el directorio principal:

```
$ gcc -o ./convert ./src/convert.c -lm
```

## Uso

```
$ convert <formato destino> <archivo 1> <archivo 2> ... <archivo n>
```

Ejemplo:

`$ convert pdf ./test.docx ./test2.docx`

Creará los archivos test.pdf y test2.pdf en el directorio actual.

## Formatos soportados

El programa se vale de su instalación de LibreOffice para realizar las conversiones, excepto por la conversión de .png a .ico.

### Conversiones con `soffice --convert-to`

* Convierte entre formatos de texto: docx, pdf, doc, odt, txt, html, rtf.

* Convierte entre formatos de hoja de cálculo: xlsx, pdf, ods, csv, html, xls.

* Convierte entre formatos de presentación: .pptx, pdf, odp, ppt.

* Convierte entre formatos gráficos: svg, pdf, png, jpg.

### Otras conversiones

* Convierte png a ico

## Descripción

Convierte entre algunos formatos de archivos.

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

`$ convert pdf ./foo.docx ./bar.odt`

Crea los archivos foo.pdf y bar.pdf en el directorio actual.

## Formatos soportados

### Conversiones con soffice (requiere una instalación de LibreOffice)

* Convierte entre formatos de texto: docx, pdf, doc, odt, txt, html, rtf.

* Convierte entre formatos de hoja de cálculo: xlsx, pdf, ods, csv, html, xls.

* Convierte entre formatos de presentación: .pptx, pdf, odp, ppt.

* Convierte jpg, png y svg a pdf.

### Conversiones de imágenes

* Convierte entre: jpeg, png, tga, bmp.
  
* Convierte png a ico

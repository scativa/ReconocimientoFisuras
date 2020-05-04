# Instalación OpenCV en Linux (MINT)

[OpenCV docs - Installation in Linux](https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html)


## Pasos realizados


```sudo apt-get install build-essential```

```sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev```

```sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev```

Error: *E: No se ha podido localizar el paquete libjasper-dev#.* Reintento con: 


```sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libdc1394-22-dev```

```cd ~/<my_working_directory>``` (~/github/)

```git clone https://github.com/opencv/opencv.git```

```git clone https://github.com/opencv/opencv_contrib.git```

Se copia todo el directorio ~/github/opencv a ~/opencv quedando este último como directorio de trabajo


```mkdir build```
```cd build```
``` ```
``` ```
```cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local -DBUILD_DOCS=TRUE -D BUIL_EXAMPLES=TRUE ..```
 

## Log

seba@Asura:*~$ sudo apt-get install build-essential*
Creando árbol de dependencias
Leyendo la información de estado... Hecho
build-essential ya está en su versión más reciente (12.4ubuntu1).
0 actualizados, 0 nuevos se instalarán, 0 para eliminar y 352 no actualizados.
seba@Asura:~$ sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
Leyendo lista de paquetes... Hecho
Creando árbol de dependencias
Leyendo la información de estado... Hecho
pkg-config ya está en su versión más reciente (0.29.1-0ubuntu2).
cmake ya está en su versión más reciente (3.10.2-1ubuntu2.18.04.1).
Se instalarán los siguientes paquetes adicionales:
  gir1.2-gtk-2.0 gir1.2-harfbuzz-0.0 icu-devtools libatk1.0-dev libavutil-dev
  libcairo-script-interpreter2 libcairo2-dev libexpat1-dev libfontconfig1-dev
  libfreetype6-dev libgdk-pixbuf2.0-dev libglib2.0-dev libglib2.0-dev-bin
  libgraphite2-dev libharfbuzz-dev libharfbuzz-gobject0 libice-dev libicu-dev
  libicu-le-hb-dev libicu-le-hb0 libicu60 libiculx60 libpango1.0-dev libpcre16-3
  libpcre3-dev libpcre32-3 libpcrecpp0v5 libpixman-1-dev libpng-dev
  libpthread-stubs0-dev libsm-dev libswresample-dev libx11-dev libxau-dev
  libxcb-render0-dev libxcb-shm0-dev libxcb1-dev libxcomposite-dev libxcursor-dev
  libxdamage-dev libxdmcp-dev libxext-dev libxfixes-dev libxft-dev libxi-dev
  libxinerama-dev libxml2-utils libxrandr-dev libxrender-dev
  x11proto-composite-dev x11proto-core-dev x11proto-damage-dev x11proto-dev
  x11proto-fixes-dev x11proto-input-dev x11proto-randr-dev x11proto-xext-dev
  x11proto-xinerama-dev xorg-sgml-doctools xtrans-dev zlib1g-dev
Paquetes sugeridos:
  git-daemon-run | git-daemon-sysvinit git-doc git-el git-email git-gui gitk
  gitweb git-cvs git-mediawiki git-svn libcairo2-doc libglib2.0-doc
  libgraphite2-utils libgtk2.0-doc libice-doc icu-doc imagemagick libpango1.0-doc
  libsm-doc libxcb-doc libxext-doc
Paquetes recomendados:
  debhelper libpng-tools libx11-doc
Se instalarán los siguientes paquetes NUEVOS:
  gir1.2-gtk-2.0 gir1.2-harfbuzz-0.0 icu-devtools libatk1.0-dev libavcodec-dev
  libavformat-dev libavutil-dev libcairo-script-interpreter2 libcairo2-dev
  libexpat1-dev libfontconfig1-dev libfreetype6-dev libgdk-pixbuf2.0-dev
  libglib2.0-dev libglib2.0-dev-bin libgraphite2-dev libgtk2.0-dev
  libharfbuzz-dev libharfbuzz-gobject0 libice-dev libicu-dev libicu-le-hb-dev
  libicu-le-hb0 libiculx60 libpango1.0-dev libpcre16-3 libpcre3-dev libpcre32-3
  libpcrecpp0v5 libpixman-1-dev libpng-dev libpthread-stubs0-dev libsm-dev
  libswresample-dev libswscale-dev libx11-dev libxau-dev libxcb-render0-dev
  libxcb-shm0-dev libxcb1-dev libxcomposite-dev libxcursor-dev libxdamage-dev
  libxdmcp-dev libxext-dev libxfixes-dev libxft-dev libxi-dev libxinerama-dev
  libxml2-utils libxrandr-dev libxrender-dev x11proto-composite-dev
  x11proto-core-dev x11proto-damage-dev x11proto-dev x11proto-fixes-dev
  x11proto-input-dev x11proto-randr-dev x11proto-xext-dev x11proto-xinerama-dev
  xorg-sgml-doctools xtrans-dev zlib1g-dev
Se actualizarán los siguientes paquetes:
  git libicu60
2 actualizados, 64 nuevos se instalarán, 0 para eliminar y 350 no actualizados.
Se necesita descargar 40,0 MB de archivos.
Se utilizarán 132 MB de espacio de disco adicional después de esta operación.
¿Desea continuar? [S/n] 
Des:1 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libicu60 amd64 60.2-3ubuntu3.1 [8.054 kB]
Des:2 http://archive.ubuntu.com/ubuntu bionic/main amd64 gir1.2-gtk-2.0 amd64 2.24.32-1ubuntu1 [172 kB]
Des:3 http://archive.ubuntu.com/ubuntu bionic/main amd64 gir1.2-harfbuzz-0.0 amd64 1.7.2-1ubuntu1 [18,6 kB]
Des:4 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 git amd64 1:2.17.1-1ubuntu0.7 [3.915 kB]
Des:5 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 icu-devtools amd64 60.2-3ubuntu3.1 [179 kB]
Des:6 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libglib2.0-dev-bin amd64 2.56.4-0ubuntu0.18.04.6 [102 kB]
Des:7 http://archive.ubuntu.com/ubuntu bionic/main amd64 libpcre16-3 amd64 2:8.39-9 [147 kB]
Des:8 http://archive.ubuntu.com/ubuntu bionic/main amd64 libpcre32-3 amd64 2:8.39-9 [138 kB]
Des:9 http://archive.ubuntu.com/ubuntu bionic/main amd64 libpcrecpp0v5 amd64 2:8.39-9 [15,3 kB]
Des:10 http://archive.ubuntu.com/ubuntu bionic/main amd64 libpcre3-dev amd64 2:8.39-9 [537 kB]
Des:11 http://archive.ubuntu.com/ubuntu bionic/main amd64 zlib1g-dev amd64 1:1.2.11.dfsg-0ubuntu2 [176 kB]
Des:12 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libglib2.0-dev amd64 2.56.4-0ubuntu0.18.04.6 [1.385 kB]
Des:13 http://archive.ubuntu.com/ubuntu bionic/main amd64 libatk1.0-dev amd64 2.28.1-1 [79,9 kB]
Des:14 http://archive.ubuntu.com/ubuntu bionic-updates/universe amd64 libavutil-dev amd64 7:3.4.6-0ubuntu0.18.04.1 [294 kB]
Des:15 http://archive.ubuntu.com/ubuntu bionic-updates/universe amd64 libswresample-dev amd64 7:3.4.6-0ubuntu0.18.04.1 [68,7 kB]
Des:16 http://archive.ubuntu.com/ubuntu bionic-updates/universe amd64 libavcodec-dev amd64 7:3.4.6-0ubuntu0.18.04.1 [5.076 kB]
Des:17 http://archive.ubuntu.com/ubuntu bionic-updates/universe amd64 libavformat-dev amd64 7:3.4.6-0ubuntu0.18.04.1 [1.128 kB]
Des:18 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libcairo-script-interpreter2 amd64 1.15.10-2ubuntu0.1 [53,5 kB]
Des:19 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libexpat1-dev amd64 2.2.5-3ubuntu0.2 [122 kB]
Des:20 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libpng-dev amd64 1.6.34-1ubuntu0.18.04.2 [177 kB]
Des:21 http://archive.ubuntu.com/ubuntu bionic/main amd64 libfreetype6-dev amd64 2.8.1-2ubuntu2 [2.539 kB]
Des:22 http://archive.ubuntu.com/ubuntu bionic/main amd64 libfontconfig1-dev amd64 2.12.6-0ubuntu2 [689 kB]
Des:23 http://archive.ubuntu.com/ubuntu bionic/main amd64 xorg-sgml-doctools all 1:1.11-1 [12,9 kB]
Des:24 http://archive.ubuntu.com/ubuntu bionic/main amd64 x11proto-dev all 2018.4-4 [251 kB]
Des:25 http://archive.ubuntu.com/ubuntu bionic/main amd64 x11proto-core-dev all 2018.4-4 [2.620 B]
Des:26 http://archive.ubuntu.com/ubuntu bionic/main amd64 libxau-dev amd64 1:1.0.8-1 [11,1 kB]
Des:27 http://archive.ubuntu.com/ubuntu bionic/main amd64 libxdmcp-dev amd64 1:1.1.2-3 [25,1 kB]
Des:28 http://archive.ubuntu.com/ubuntu bionic/main amd64 x11proto-input-dev all 2018.4-4 [2.620 B]
Des:29 http://archive.ubuntu.com/ubuntu bionic/main amd64 xtrans-dev all 1.3.5-1 [70,5 kB]
Des:30 http://archive.ubuntu.com/ubuntu bionic/main amd64 libpthread-stubs0-dev amd64 0.3-4 [4.068 B]
Des:31 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libxcb1-dev amd64 1.13-2~ubuntu18.04 [80,0 kB]
Des:32 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libx11-dev amd64 2:1.6.4-3ubuntu0.2 [640 kB]
Des:33 http://archive.ubuntu.com/ubuntu bionic/main amd64 libxrender-dev amd64 1:0.9.10-1 [24,9 kB]
Des:34 http://archive.ubuntu.com/ubuntu bionic/main amd64 x11proto-xext-dev all 2018.4-4 [2.620 B]
Des:35 http://archive.ubuntu.com/ubuntu bionic/main amd64 libxext-dev amd64 2:1.3.3-1 [82,1 kB]
Des:36 http://archive.ubuntu.com/ubuntu bionic/main amd64 libice-dev amd64 2:1.0.9-2 [46,8 kB]
Des:37 http://archive.ubuntu.com/ubuntu bionic/main amd64 libsm-dev amd64 2:1.2.2-1 [16,2 kB]
Des:38 http://archive.ubuntu.com/ubuntu bionic/main amd64 libpixman-1-dev amd64 0.34.0-2 [244 kB]
Des:39 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libxcb-render0-dev amd64 1.13-2~ubuntu18.04 [18,4 kB]
Des:40 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libxcb-shm0-dev amd64 1.13-2~ubuntu18.04 [6.684 B]
Des:41 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libcairo2-dev amd64 1.15.10-2ubuntu0.1 [626 kB]
Des:42 http://archive.ubuntu.com/ubuntu bionic/main amd64 libgdk-pixbuf2.0-dev amd64 2.36.11-2 [46,8 kB]
Des:43 http://archive.ubuntu.com/ubuntu bionic/main amd64 libgraphite2-dev amd64 1.3.11-2 [14,5 kB]
Des:44 http://archive.ubuntu.com/ubuntu bionic/main amd64 libharfbuzz-gobject0 amd64 1.7.2-1ubuntu1 [13,4 kB]
Des:45 http://archive.ubuntu.com/ubuntu bionic/main amd64 libicu-le-hb0 amd64 1.0.3+git161113-4 [14,3 kB]
Des:46 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libiculx60 amd64 60.2-3ubuntu3.1 [19,0 kB]
Des:47 http://archive.ubuntu.com/ubuntu bionic/main amd64 libicu-le-hb-dev amd64 1.0.3+git161113-4 [29,5 kB]
Des:48 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libicu-dev amd64 60.2-3ubuntu3.1 [8.889 kB]
Des:49 http://archive.ubuntu.com/ubuntu bionic/main amd64 libharfbuzz-dev amd64 1.7.2-1ubuntu1 [302 kB]
Des:50 http://archive.ubuntu.com/ubuntu bionic/main amd64 libxft-dev amd64 2.3.2-1 [45,7 kB]
Des:51 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libpango1.0-dev amd64 1.40.14-1ubuntu0.1 [288 kB]
Des:52 http://archive.ubuntu.com/ubuntu bionic/main amd64 x11proto-xinerama-dev all 2018.4-4 [2.628 B]
Des:53 http://archive.ubuntu.com/ubuntu bionic/main amd64 libxinerama-dev amd64 2:1.1.3-1 [8.404 B]
Des:54 http://archive.ubuntu.com/ubuntu bionic/main amd64 x11proto-fixes-dev all 1:2018.4-4 [2.620 B]
Des:55 http://archive.ubuntu.com/ubuntu bionic/main amd64 libxfixes-dev amd64 1:5.0.3-1 [11,0 kB]
Des:56 http://archive.ubuntu.com/ubuntu bionic/main amd64 libxi-dev amd64 2:1.7.9-1 [186 kB]
Des:57 http://archive.ubuntu.com/ubuntu bionic/main amd64 x11proto-randr-dev all 2018.4-4 [2.620 B]
Des:58 http://archive.ubuntu.com/ubuntu bionic/main amd64 libxrandr-dev amd64 2:1.5.1-1 [24,0 kB]
Des:59 http://archive.ubuntu.com/ubuntu bionic/main amd64 libxcursor-dev amd64 1:1.1.15-1 [26,5 kB]
Des:60 http://archive.ubuntu.com/ubuntu bionic/main amd64 x11proto-composite-dev all 1:2018.4-4 [2.620 B]
Des:61 http://archive.ubuntu.com/ubuntu bionic/main amd64 libxcomposite-dev amd64 1:0.4.4-2 [9.136 B]
Des:62 http://archive.ubuntu.com/ubuntu bionic/main amd64 x11proto-damage-dev all 1:2018.4-4 [2.620 B]
Des:63 http://archive.ubuntu.com/ubuntu bionic/main amd64 libxdamage-dev amd64 1:1.1.4-3 [5.028 B]
Des:64 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libxml2-utils amd64 2.9.4+dfsg1-6.1ubuntu1.3 [35,9 kB]
Des:65 http://archive.ubuntu.com/ubuntu bionic/main amd64 libgtk2.0-dev amd64 2.24.32-1ubuntu1 [2.652 kB]
Des:66 http://archive.ubuntu.com/ubuntu bionic-updates/universe amd64 libswscale-dev amd64 7:3.4.6-0ubuntu0.18.04.1 [166 kB]
Descargados 40,0 MB en 17s (2.417 kB/s)                                           
Extrayendo plantillas para los paquetes: 100%
(Leyendo la base de datos ... 337898 ficheros o directorios instalados actualmente.)
Preparando para desempaquetar .../libicu60_60.2-3ubuntu3.1_amd64.deb ...
Desempaquetando libicu60:amd64 (60.2-3ubuntu3.1) sobre (60.2-3ubuntu3) ...
Configurando libicu60:amd64 (60.2-3ubuntu3.1) ...
Seleccionando el paquete gir1.2-gtk-2.0 previamente no seleccionado.
(Leyendo la base de datos ... 337898 ficheros o directorios instalados actualmente.)
Preparando para desempaquetar .../00-gir1.2-gtk-2.0_2.24.32-1ubuntu1_amd64.deb ...
Desempaquetando gir1.2-gtk-2.0 (2.24.32-1ubuntu1) ...
Seleccionando el paquete gir1.2-harfbuzz-0.0:amd64 previamente no seleccionado.
Preparando para desempaquetar .../01-gir1.2-harfbuzz-0.0_1.7.2-1ubuntu1_amd64.deb ...
Desempaquetando gir1.2-harfbuzz-0.0:amd64 (1.7.2-1ubuntu1) ...
Preparando para desempaquetar .../02-git_1%3a2.17.1-1ubuntu0.7_amd64.deb ...
Desempaquetando git (1:2.17.1-1ubuntu0.7) sobre (1:2.17.1-1ubuntu0.4) ...
Seleccionando el paquete icu-devtools previamente no seleccionado.
Preparando para desempaquetar .../03-icu-devtools_60.2-3ubuntu3.1_amd64.deb ...
Desempaquetando icu-devtools (60.2-3ubuntu3.1) ...
Seleccionando el paquete libglib2.0-dev-bin previamente no seleccionado.
Preparando para desempaquetar .../04-libglib2.0-dev-bin_2.56.4-0ubuntu0.18.04.6_amd64.deb ...
Desempaquetando libglib2.0-dev-bin (2.56.4-0ubuntu0.18.04.6) ...
Seleccionando el paquete libpcre16-3:amd64 previamente no seleccionado.
Preparando para desempaquetar .../05-libpcre16-3_2%3a8.39-9_amd64.deb ...
Desempaquetando libpcre16-3:amd64 (2:8.39-9) ...
Seleccionando el paquete libpcre32-3:amd64 previamente no seleccionado.
Preparando para desempaquetar .../06-libpcre32-3_2%3a8.39-9_amd64.deb ...
Desempaquetando libpcre32-3:amd64 (2:8.39-9) ...
Seleccionando el paquete libpcrecpp0v5:amd64 previamente no seleccionado.
Preparando para desempaquetar .../07-libpcrecpp0v5_2%3a8.39-9_amd64.deb ...
Desempaquetando libpcrecpp0v5:amd64 (2:8.39-9) ...
Seleccionando el paquete libpcre3-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../08-libpcre3-dev_2%3a8.39-9_amd64.deb ...
Desempaquetando libpcre3-dev:amd64 (2:8.39-9) ...
Seleccionando el paquete zlib1g-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../09-zlib1g-dev_1%3a1.2.11.dfsg-0ubuntu2_amd64.deb ...
Desempaquetando zlib1g-dev:amd64 (1:1.2.11.dfsg-0ubuntu2) ...
Seleccionando el paquete libglib2.0-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../10-libglib2.0-dev_2.56.4-0ubuntu0.18.04.6_amd64.deb ...
Desempaquetando libglib2.0-dev:amd64 (2.56.4-0ubuntu0.18.04.6) ...
Seleccionando el paquete libatk1.0-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../11-libatk1.0-dev_2.28.1-1_amd64.deb ...
Desempaquetando libatk1.0-dev:amd64 (2.28.1-1) ...
Seleccionando el paquete libavutil-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../12-libavutil-dev_7%3a3.4.6-0ubuntu0.18.04.1_amd64.deb ...
Desempaquetando libavutil-dev:amd64 (7:3.4.6-0ubuntu0.18.04.1) ...
Seleccionando el paquete libswresample-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../13-libswresample-dev_7%3a3.4.6-0ubuntu0.18.04.1_amd64.deb ...
Desempaquetando libswresample-dev:amd64 (7:3.4.6-0ubuntu0.18.04.1) ...
Seleccionando el paquete libavcodec-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../14-libavcodec-dev_7%3a3.4.6-0ubuntu0.18.04.1_amd64.deb ...
Desempaquetando libavcodec-dev:amd64 (7:3.4.6-0ubuntu0.18.04.1) ...
Seleccionando el paquete libavformat-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../15-libavformat-dev_7%3a3.4.6-0ubuntu0.18.04.1_amd64.deb ...
Desempaquetando libavformat-dev:amd64 (7:3.4.6-0ubuntu0.18.04.1) ...
Seleccionando el paquete libcairo-script-interpreter2:amd64 previamente no seleccionado.
Preparando para desempaquetar .../16-libcairo-script-interpreter2_1.15.10-2ubuntu0.1_amd64.deb ...
Desempaquetando libcairo-script-interpreter2:amd64 (1.15.10-2ubuntu0.1) ...
Seleccionando el paquete libexpat1-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../17-libexpat1-dev_2.2.5-3ubuntu0.2_amd64.deb ...
Desempaquetando libexpat1-dev:amd64 (2.2.5-3ubuntu0.2) ...
Seleccionando el paquete libpng-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../18-libpng-dev_1.6.34-1ubuntu0.18.04.2_amd64.deb ...
Desempaquetando libpng-dev:amd64 (1.6.34-1ubuntu0.18.04.2) ...
Seleccionando el paquete libfreetype6-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../19-libfreetype6-dev_2.8.1-2ubuntu2_amd64.deb ...
Desempaquetando libfreetype6-dev:amd64 (2.8.1-2ubuntu2) ...
Seleccionando el paquete libfontconfig1-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../20-libfontconfig1-dev_2.12.6-0ubuntu2_amd64.deb ...
Desempaquetando libfontconfig1-dev:amd64 (2.12.6-0ubuntu2) ...
Seleccionando el paquete xorg-sgml-doctools previamente no seleccionado.
Preparando para desempaquetar .../21-xorg-sgml-doctools_1%3a1.11-1_all.deb ...
Desempaquetando xorg-sgml-doctools (1:1.11-1) ...
Seleccionando el paquete x11proto-dev previamente no seleccionado.
Preparando para desempaquetar .../22-x11proto-dev_2018.4-4_all.deb ...
Desempaquetando x11proto-dev (2018.4-4) ...
Seleccionando el paquete x11proto-core-dev previamente no seleccionado.
Preparando para desempaquetar .../23-x11proto-core-dev_2018.4-4_all.deb ...
Desempaquetando x11proto-core-dev (2018.4-4) ...
Seleccionando el paquete libxau-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../24-libxau-dev_1%3a1.0.8-1_amd64.deb ...
Desempaquetando libxau-dev:amd64 (1:1.0.8-1) ...
Seleccionando el paquete libxdmcp-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../25-libxdmcp-dev_1%3a1.1.2-3_amd64.deb ...
Desempaquetando libxdmcp-dev:amd64 (1:1.1.2-3) ...
Seleccionando el paquete x11proto-input-dev previamente no seleccionado.
Preparando para desempaquetar .../26-x11proto-input-dev_2018.4-4_all.deb ...
Desempaquetando x11proto-input-dev (2018.4-4) ...
Seleccionando el paquete xtrans-dev previamente no seleccionado.
Preparando para desempaquetar .../27-xtrans-dev_1.3.5-1_all.deb ...
Desempaquetando xtrans-dev (1.3.5-1) ...
Seleccionando el paquete libpthread-stubs0-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../28-libpthread-stubs0-dev_0.3-4_amd64.deb ...
Desempaquetando libpthread-stubs0-dev:amd64 (0.3-4) ...
Seleccionando el paquete libxcb1-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../29-libxcb1-dev_1.13-2~ubuntu18.04_amd64.deb ...
Desempaquetando libxcb1-dev:amd64 (1.13-2~ubuntu18.04) ...
Seleccionando el paquete libx11-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../30-libx11-dev_2%3a1.6.4-3ubuntu0.2_amd64.deb ...
Desempaquetando libx11-dev:amd64 (2:1.6.4-3ubuntu0.2) ...
Seleccionando el paquete libxrender-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../31-libxrender-dev_1%3a0.9.10-1_amd64.deb ...
Desempaquetando libxrender-dev:amd64 (1:0.9.10-1) ...
Seleccionando el paquete x11proto-xext-dev previamente no seleccionado.
Preparando para desempaquetar .../32-x11proto-xext-dev_2018.4-4_all.deb ...
Desempaquetando x11proto-xext-dev (2018.4-4) ...
Seleccionando el paquete libxext-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../33-libxext-dev_2%3a1.3.3-1_amd64.deb ...
Desempaquetando libxext-dev:amd64 (2:1.3.3-1) ...
Seleccionando el paquete libice-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../34-libice-dev_2%3a1.0.9-2_amd64.deb ...
Desempaquetando libice-dev:amd64 (2:1.0.9-2) ...
Seleccionando el paquete libsm-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../35-libsm-dev_2%3a1.2.2-1_amd64.deb ...
Desempaquetando libsm-dev:amd64 (2:1.2.2-1) ...
Seleccionando el paquete libpixman-1-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../36-libpixman-1-dev_0.34.0-2_amd64.deb ...
Desempaquetando libpixman-1-dev:amd64 (0.34.0-2) ...
Seleccionando el paquete libxcb-render0-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../37-libxcb-render0-dev_1.13-2~ubuntu18.04_amd64.deb ...
Desempaquetando libxcb-render0-dev:amd64 (1.13-2~ubuntu18.04) ...
Seleccionando el paquete libxcb-shm0-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../38-libxcb-shm0-dev_1.13-2~ubuntu18.04_amd64.deb ...
Desempaquetando libxcb-shm0-dev:amd64 (1.13-2~ubuntu18.04) ...
Seleccionando el paquete libcairo2-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../39-libcairo2-dev_1.15.10-2ubuntu0.1_amd64.deb ...
Desempaquetando libcairo2-dev:amd64 (1.15.10-2ubuntu0.1) ...
Seleccionando el paquete libgdk-pixbuf2.0-dev previamente no seleccionado.
Preparando para desempaquetar .../40-libgdk-pixbuf2.0-dev_2.36.11-2_amd64.deb ...
Desempaquetando libgdk-pixbuf2.0-dev (2.36.11-2) ...
Seleccionando el paquete libgraphite2-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../41-libgraphite2-dev_1.3.11-2_amd64.deb ...
Desempaquetando libgraphite2-dev:amd64 (1.3.11-2) ...
Seleccionando el paquete libharfbuzz-gobject0:amd64 previamente no seleccionado.
Preparando para desempaquetar .../42-libharfbuzz-gobject0_1.7.2-1ubuntu1_amd64.deb ...
Desempaquetando libharfbuzz-gobject0:amd64 (1.7.2-1ubuntu1) ...
Seleccionando el paquete libicu-le-hb0:amd64 previamente no seleccionado.
Preparando para desempaquetar .../43-libicu-le-hb0_1.0.3+git161113-4_amd64.deb ...
Desempaquetando libicu-le-hb0:amd64 (1.0.3+git161113-4) ...
Seleccionando el paquete libiculx60:amd64 previamente no seleccionado.
Preparando para desempaquetar .../44-libiculx60_60.2-3ubuntu3.1_amd64.deb ...
Desempaquetando libiculx60:amd64 (60.2-3ubuntu3.1) ...
Seleccionando el paquete libicu-le-hb-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../45-libicu-le-hb-dev_1.0.3+git161113-4_amd64.deb ...
Desempaquetando libicu-le-hb-dev:amd64 (1.0.3+git161113-4) ...
Seleccionando el paquete libicu-dev previamente no seleccionado.
Preparando para desempaquetar .../46-libicu-dev_60.2-3ubuntu3.1_amd64.deb ...
Desempaquetando libicu-dev (60.2-3ubuntu3.1) ...
Seleccionando el paquete libharfbuzz-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../47-libharfbuzz-dev_1.7.2-1ubuntu1_amd64.deb ...
Desempaquetando libharfbuzz-dev:amd64 (1.7.2-1ubuntu1) ...
Seleccionando el paquete libxft-dev previamente no seleccionado.
Preparando para desempaquetar .../48-libxft-dev_2.3.2-1_amd64.deb ...
Desempaquetando libxft-dev (2.3.2-1) ...
Seleccionando el paquete libpango1.0-dev previamente no seleccionado.
Preparando para desempaquetar .../49-libpango1.0-dev_1.40.14-1ubuntu0.1_amd64.deb ...
Desempaquetando libpango1.0-dev (1.40.14-1ubuntu0.1) ...
Seleccionando el paquete x11proto-xinerama-dev previamente no seleccionado.
Preparando para desempaquetar .../50-x11proto-xinerama-dev_2018.4-4_all.deb ...
Desempaquetando x11proto-xinerama-dev (2018.4-4) ...
Seleccionando el paquete libxinerama-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../51-libxinerama-dev_2%3a1.1.3-1_amd64.deb ...
Desempaquetando libxinerama-dev:amd64 (2:1.1.3-1) ...
Seleccionando el paquete x11proto-fixes-dev previamente no seleccionado.
Preparando para desempaquetar .../52-x11proto-fixes-dev_1%3a2018.4-4_all.deb ...
Desempaquetando x11proto-fixes-dev (1:2018.4-4) ...
Seleccionando el paquete libxfixes-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../53-libxfixes-dev_1%3a5.0.3-1_amd64.deb ...
Desempaquetando libxfixes-dev:amd64 (1:5.0.3-1) ...
Seleccionando el paquete libxi-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../54-libxi-dev_2%3a1.7.9-1_amd64.deb ...
Desempaquetando libxi-dev:amd64 (2:1.7.9-1) ...
Seleccionando el paquete x11proto-randr-dev previamente no seleccionado.
Preparando para desempaquetar .../55-x11proto-randr-dev_2018.4-4_all.deb ...
Desempaquetando x11proto-randr-dev (2018.4-4) ...
Seleccionando el paquete libxrandr-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../56-libxrandr-dev_2%3a1.5.1-1_amd64.deb ...
Desempaquetando libxrandr-dev:amd64 (2:1.5.1-1) ...
Seleccionando el paquete libxcursor-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../57-libxcursor-dev_1%3a1.1.15-1_amd64.deb ...
Desempaquetando libxcursor-dev:amd64 (1:1.1.15-1) ...
Seleccionando el paquete x11proto-composite-dev previamente no seleccionado.
Preparando para desempaquetar .../58-x11proto-composite-dev_1%3a2018.4-4_all.deb ...
Desempaquetando x11proto-composite-dev (1:2018.4-4) ...
Seleccionando el paquete libxcomposite-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../59-libxcomposite-dev_1%3a0.4.4-2_amd64.deb ...
Desempaquetando libxcomposite-dev:amd64 (1:0.4.4-2) ...
Seleccionando el paquete x11proto-damage-dev previamente no seleccionado.
Preparando para desempaquetar .../60-x11proto-damage-dev_1%3a2018.4-4_all.deb ...
Desempaquetando x11proto-damage-dev (1:2018.4-4) ...
Seleccionando el paquete libxdamage-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../61-libxdamage-dev_1%3a1.1.4-3_amd64.deb ...
Desempaquetando libxdamage-dev:amd64 (1:1.1.4-3) ...
Seleccionando el paquete libxml2-utils previamente no seleccionado.
Preparando para desempaquetar .../62-libxml2-utils_2.9.4+dfsg1-6.1ubuntu1.3_amd64.deb ...
Desempaquetando libxml2-utils (2.9.4+dfsg1-6.1ubuntu1.3) ...
Seleccionando el paquete libgtk2.0-dev previamente no seleccionado.
Preparando para desempaquetar .../63-libgtk2.0-dev_2.24.32-1ubuntu1_amd64.deb ...
Desempaquetando libgtk2.0-dev (2.24.32-1ubuntu1) ...
Seleccionando el paquete libswscale-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../64-libswscale-dev_7%3a3.4.6-0ubuntu0.18.04.1_amd64.deb ...
Desempaquetando libswscale-dev:amd64 (7:3.4.6-0ubuntu0.18.04.1) ...
Configurando gir1.2-gtk-2.0 (2.24.32-1ubuntu1) ...
Configurando libavutil-dev:amd64 (7:3.4.6-0ubuntu0.18.04.1) ...
Configurando libglib2.0-dev-bin (2.56.4-0ubuntu0.18.04.6) ...
Configurando libcairo-script-interpreter2:amd64 (1.15.10-2ubuntu0.1) ...
Configurando libpthread-stubs0-dev:amd64 (0.3-4) ...
Configurando xorg-sgml-doctools (1:1.11-1) ...
Configurando libicu-le-hb0:amd64 (1.0.3+git161113-4) ...
Configurando libxml2-utils (2.9.4+dfsg1-6.1ubuntu1.3) ...
Configurando libswscale-dev:amd64 (7:3.4.6-0ubuntu0.18.04.1) ...
Configurando xtrans-dev (1.3.5-1) ...
Configurando gir1.2-harfbuzz-0.0:amd64 (1.7.2-1ubuntu1) ...
Configurando libpixman-1-dev:amd64 (0.34.0-2) ...
Configurando libswresample-dev:amd64 (7:3.4.6-0ubuntu0.18.04.1) ...
Configurando libiculx60:amd64 (60.2-3ubuntu3.1) ...
Configurando libexpat1-dev:amd64 (2.2.5-3ubuntu0.2) ...
Configurando libpcrecpp0v5:amd64 (2:8.39-9) ...
Configurando libpcre32-3:amd64 (2:8.39-9) ...
Configurando icu-devtools (60.2-3ubuntu3.1) ...
Configurando libpcre16-3:amd64 (2:8.39-9) ...
Configurando libgraphite2-dev:amd64 (1.3.11-2) ...
Configurando libharfbuzz-gobject0:amd64 (1.7.2-1ubuntu1) ...
Configurando git (1:2.17.1-1ubuntu0.7) ...
Configurando zlib1g-dev:amd64 (1:1.2.11.dfsg-0ubuntu2) ...
Configurando libpcre3-dev:amd64 (2:8.39-9) ...
Configurando libavcodec-dev:amd64 (7:3.4.6-0ubuntu0.18.04.1) ...
Configurando libglib2.0-dev:amd64 (2.56.4-0ubuntu0.18.04.6) ...
Configurando libavformat-dev:amd64 (7:3.4.6-0ubuntu0.18.04.1) ...
Configurando libpng-dev:amd64 (1.6.34-1ubuntu0.18.04.2) ...
Configurando libfreetype6-dev:amd64 (2.8.1-2ubuntu2) ...
Configurando libfontconfig1-dev:amd64 (2.12.6-0ubuntu2) ...
Configurando libicu-dev (60.2-3ubuntu3.1) ...
Procesando disparadores para libc-bin (2.27-3ubuntu1) ...
Procesando disparadores para doc-base (0.10.8) ...
Processing 3 added doc-base files...
Registering documents with scrollkeeper...
Procesando disparadores para man-db (2.8.3-2ubuntu0.1) ...
Procesando disparadores para libglib2.0-0:amd64 (2.56.4-0ubuntu0.18.04.6) ...
Configurando libatk1.0-dev:amd64 (2.28.1-1) ...
Procesando disparadores para sgml-base (1.29) ...
Configurando x11proto-dev (2018.4-4) ...
Configurando x11proto-damage-dev (1:2018.4-4) ...
Configurando x11proto-xext-dev (2018.4-4) ...
Configurando libxdmcp-dev:amd64 (1:1.1.2-3) ...
Configurando x11proto-xinerama-dev (2018.4-4) ...
Configurando libice-dev:amd64 (2:1.0.9-2) ...
Configurando x11proto-randr-dev (2018.4-4) ...
Configurando libharfbuzz-dev:amd64 (1.7.2-1ubuntu1) ...
Configurando x11proto-input-dev (2018.4-4) ...
Configurando x11proto-composite-dev (1:2018.4-4) ...
Configurando libsm-dev:amd64 (2:1.2.2-1) ...
Configurando x11proto-core-dev (2018.4-4) ...
Configurando libicu-le-hb-dev:amd64 (1.0.3+git161113-4) ...
Configurando x11proto-fixes-dev (1:2018.4-4) ...
Configurando libxau-dev:amd64 (1:1.0.8-1) ...
Configurando libxcb1-dev:amd64 (1.13-2~ubuntu18.04) ...
Configurando libx11-dev:amd64 (2:1.6.4-3ubuntu0.2) ...
Configurando libxfixes-dev:amd64 (1:5.0.3-1) ...
Configurando libxcb-shm0-dev:amd64 (1.13-2~ubuntu18.04) ...
Configurando libxdamage-dev:amd64 (1:1.1.4-3) ...
Configurando libxrender-dev:amd64 (1:0.9.10-1) ...
Configurando libxcb-render0-dev:amd64 (1.13-2~ubuntu18.04) ...
Configurando libxft-dev (2.3.2-1) ...
Configurando libgdk-pixbuf2.0-dev (2.36.11-2) ...
Configurando libxext-dev:amd64 (2:1.3.3-1) ...
Configurando libxinerama-dev:amd64 (2:1.1.3-1) ...
Configurando libxi-dev:amd64 (2:1.7.9-1) ...
Configurando libxcursor-dev:amd64 (1:1.1.15-1) ...
Configurando libxrandr-dev:amd64 (2:1.5.1-1) ...
Configurando libcairo2-dev:amd64 (1.15.10-2ubuntu0.1) ...
Configurando libxcomposite-dev:amd64 (1:0.4.4-2) ...
Configurando libpango1.0-dev (1.40.14-1ubuntu0.1) ...
Configurando libgtk2.0-dev (2.24.32-1ubuntu1) ...

seba@Asura:*~$ sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev*

Leyendo lista de paquetes... Hecho
Creando árbol de dependencias       
Leyendo la información de estado... Hecho
E: No se ha podido localizar el paquete libjasper-dev


seba@Asura:*~$ sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libdc1394-22-dev*

Leyendo lista de paquetes... Hecho
Creando árbol de dependencias       
Leyendo la información de estado... Hecho
libpng-dev ya está en su versión más reciente (1.6.34-1ubuntu0.18.04.2).
fijado libpng-dev como instalado manualmente.
Se instalarán los siguientes paquetes adicionales:
  libjbig-dev libjpeg-turbo8 libjpeg-turbo8-dev libjpeg8-dev liblzma-dev
  libpython-dev libpython2.7 libpython2.7-dev libpython2.7-minimal
  libpython2.7-stdlib libraw1394-dev libtiff5 libtiff5-dev libtiffxx5 python2.7
  python2.7-dev python2.7-minimal
Paquetes sugeridos:
  liblzma-doc libraw1394-doc tbb-examples libtbb-doc gfortran python-nose
  python-numpy-dbg python-numpy-doc python2.7-doc binfmt-support
Paquetes recomendados:
  libraw1394-tools
Se instalarán los siguientes paquetes NUEVOS:
  libdc1394-22-dev libjbig-dev libjpeg-dev libjpeg-turbo8-dev libjpeg8-dev
  liblzma-dev libpython-dev libpython2.7-dev libraw1394-dev libtbb-dev libtbb2
  libtiff-dev libtiff5-dev libtiffxx5 python-dev python-numpy python2.7-dev
Se actualizarán los siguientes paquetes:
  libjpeg-turbo8 libpython2.7 libpython2.7-minimal libpython2.7-stdlib libtiff5
  python2.7 python2.7-minimal
7 actualizados, 17 nuevos se instalarán, 0 para eliminar y 343 no actualizados.
Se necesita descargar 36,8 MB de archivos.
Se utilizarán 58,3 MB de espacio de disco adicional después de esta operación.
¿Desea continuar? [S/n] 
Des:1 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libjpeg-turbo8 amd64 1.5.2-0ubuntu5.18.04.3 [110 kB]
Des:2 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libpython2.7 amd64 2.7.17-1~18.04ubuntu1 [1.053 kB]
Des:3 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libpython2.7-minimal amd64 2.7.17-1~18.04ubuntu1 [335 kB]
Des:4 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libpython2.7-stdlib amd64 2.7.17-1~18.04ubuntu1 [1.915 kB]
Des:5 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 python2.7-minimal amd64 2.7.17-1~18.04ubuntu1 [1.294 kB]
Des:6 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 python2.7 amd64 2.7.17-1~18.04ubuntu1 [248 kB]
Des:7 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libtiff5 amd64 4.0.9-5ubuntu0.3 [153 kB]
Des:8 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libjpeg-turbo8-dev amd64 1.5.2-0ubuntu5.18.04.3 [225 kB]
Des:9 http://archive.ubuntu.com/ubuntu bionic/main amd64 libjpeg8-dev amd64 8c-2ubuntu8 [1.552 B]
Des:10 http://archive.ubuntu.com/ubuntu bionic/main amd64 libjpeg-dev amd64 8c-2ubuntu8 [1.546 B]
Des:11 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libpython2.7-dev amd64 2.7.17-1~18.04ubuntu1 [28,3 MB]
Des:12 http://archive.ubuntu.com/ubuntu bionic/main amd64 libpython-dev amd64 2.7.15~rc1-1 [7.684 B]
Des:13 http://archive.ubuntu.com/ubuntu bionic/main amd64 libraw1394-dev amd64 2.1.2-1 [35,5 kB]
Des:14 http://archive.ubuntu.com/ubuntu bionic/main amd64 libjbig-dev amd64 2.1-3.1build1 [25,2 kB]
Des:15 http://archive.ubuntu.com/ubuntu bionic/main amd64 liblzma-dev amd64 5.2.2-1.3 [145 kB]
Des:16 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libtiffxx5 amd64 4.0.9-5ubuntu0.3 [5.800 B]
Des:17 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libtiff5-dev amd64 4.0.9-5ubuntu0.3 [274 kB]
Des:18 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 libtiff-dev amd64 4.0.9-5ubuntu0.3 [2.260 B]
Des:19 http://archive.ubuntu.com/ubuntu bionic-updates/main amd64 python2.7-dev amd64 2.7.17-1~18.04ubuntu1 [279 kB]
Des:20 http://archive.ubuntu.com/ubuntu bionic/main amd64 python-dev amd64 2.7.15~rc1-1 [1.256 B]
Des:21 http://archive.ubuntu.com/ubuntu bionic/main amd64 python-numpy amd64 1:1.13.3-2ubuntu1 [1.938 kB]
Des:22 http://archive.ubuntu.com/ubuntu bionic/universe amd64 libdc1394-22-dev amd64 2.2.5-1 [109 kB]
Des:23 http://archive.ubuntu.com/ubuntu bionic/universe amd64 libtbb2 amd64 2017~U7-8 [110 kB]
Des:24 http://archive.ubuntu.com/ubuntu bionic/universe amd64 libtbb-dev amd64 2017~U7-8 [231 kB]
Descargados 36,8 MB en 16s (2.304 kB/s)                                           
(Leyendo la base de datos ... 340684 ficheros o directorios instalados actualmente.)
Preparando para desempaquetar .../libjpeg-turbo8_1.5.2-0ubuntu5.18.04.3_amd64.deb ...
Desempaquetando libjpeg-turbo8:amd64 (1.5.2-0ubuntu5.18.04.3) sobre (1.5.2-0ubuntu5.18.04.1) ...
Configurando libjpeg-turbo8:amd64 (1.5.2-0ubuntu5.18.04.3) ...
(Leyendo la base de datos ... 340684 ficheros o directorios instalados actualmente.)
Preparando para desempaquetar .../libpython2.7_2.7.17-1~18.04ubuntu1_amd64.deb ...
Desempaquetando libpython2.7:amd64 (2.7.17-1~18.04ubuntu1) sobre (2.7.15-4ubuntu4~18.04.1) ...
Preparando para desempaquetar .../libpython2.7-minimal_2.7.17-1~18.04ubuntu1_amd64.deb ...
Desempaquetando libpython2.7-minimal:amd64 (2.7.17-1~18.04ubuntu1) sobre (2.7.15-4ubuntu4~18.04.1) ...
Configurando libpython2.7-minimal:amd64 (2.7.17-1~18.04ubuntu1) ...
(Leyendo la base de datos ... 340684 ficheros o directorios instalados actualmente.)
Preparando para desempaquetar .../libpython2.7-stdlib_2.7.17-1~18.04ubuntu1_amd64.deb ...
Desempaquetando libpython2.7-stdlib:amd64 (2.7.17-1~18.04ubuntu1) sobre (2.7.15-4ubuntu4~18.04.1) ...
Configurando libpython2.7-stdlib:amd64 (2.7.17-1~18.04ubuntu1) ...
(Leyendo la base de datos ... 340684 ficheros o directorios instalados actualmente.)
Preparando para desempaquetar .../python2.7-minimal_2.7.17-1~18.04ubuntu1_amd64.deb ...
Desempaquetando python2.7-minimal (2.7.17-1~18.04ubuntu1) sobre (2.7.15-4ubuntu4~18.04.1) ...
Configurando python2.7-minimal (2.7.17-1~18.04ubuntu1) ...
(Leyendo la base de datos ... 340684 ficheros o directorios instalados actualmente.)
Preparando para desempaquetar .../python2.7_2.7.17-1~18.04ubuntu1_amd64.deb ...
Desempaquetando python2.7 (2.7.17-1~18.04ubuntu1) sobre (2.7.15-4ubuntu4~18.04.1) ...
Configurando python2.7 (2.7.17-1~18.04ubuntu1) ...
(Leyendo la base de datos ... 340684 ficheros o directorios instalados actualmente.)
Preparando para desempaquetar .../libtiff5_4.0.9-5ubuntu0.3_amd64.deb ...
Desempaquetando libtiff5:amd64 (4.0.9-5ubuntu0.3) sobre (4.0.9-5ubuntu0.2) ...
Configurando libtiff5:amd64 (4.0.9-5ubuntu0.3) ...
Seleccionando el paquete libjpeg-turbo8-dev:amd64 previamente no seleccionado.
(Leyendo la base de datos ... 340684 ficheros o directorios instalados actualmente.)
Preparando para desempaquetar .../00-libjpeg-turbo8-dev_1.5.2-0ubuntu5.18.04.3_amd64.deb ...
Desempaquetando libjpeg-turbo8-dev:amd64 (1.5.2-0ubuntu5.18.04.3) ...
Seleccionando el paquete libjpeg8-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../01-libjpeg8-dev_8c-2ubuntu8_amd64.deb ...
Desempaquetando libjpeg8-dev:amd64 (8c-2ubuntu8) ...
Seleccionando el paquete libjpeg-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../02-libjpeg-dev_8c-2ubuntu8_amd64.deb ...
Desempaquetando libjpeg-dev:amd64 (8c-2ubuntu8) ...
Seleccionando el paquete libpython2.7-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../03-libpython2.7-dev_2.7.17-1~18.04ubuntu1_amd64.deb ...
Desempaquetando libpython2.7-dev:amd64 (2.7.17-1~18.04ubuntu1) ...
Seleccionando el paquete libpython-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../04-libpython-dev_2.7.15~rc1-1_amd64.deb ...
Desempaquetando libpython-dev:amd64 (2.7.15~rc1-1) ...
Seleccionando el paquete libraw1394-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../05-libraw1394-dev_2.1.2-1_amd64.deb ...
Desempaquetando libraw1394-dev:amd64 (2.1.2-1) ...
Seleccionando el paquete libjbig-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../06-libjbig-dev_2.1-3.1build1_amd64.deb ...
Desempaquetando libjbig-dev:amd64 (2.1-3.1build1) ...
Seleccionando el paquete liblzma-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../07-liblzma-dev_5.2.2-1.3_amd64.deb ...
Desempaquetando liblzma-dev:amd64 (5.2.2-1.3) ...
Seleccionando el paquete libtiffxx5:amd64 previamente no seleccionado.
Preparando para desempaquetar .../08-libtiffxx5_4.0.9-5ubuntu0.3_amd64.deb ...
Desempaquetando libtiffxx5:amd64 (4.0.9-5ubuntu0.3) ...
Seleccionando el paquete libtiff5-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../09-libtiff5-dev_4.0.9-5ubuntu0.3_amd64.deb ...
Desempaquetando libtiff5-dev:amd64 (4.0.9-5ubuntu0.3) ...
Seleccionando el paquete libtiff-dev previamente no seleccionado.
Preparando para desempaquetar .../10-libtiff-dev_4.0.9-5ubuntu0.3_amd64.deb ...
Desempaquetando libtiff-dev (4.0.9-5ubuntu0.3) ...
Seleccionando el paquete python2.7-dev previamente no seleccionado.
Preparando para desempaquetar .../11-python2.7-dev_2.7.17-1~18.04ubuntu1_amd64.deb ...
Desempaquetando python2.7-dev (2.7.17-1~18.04ubuntu1) ...
Seleccionando el paquete python-dev previamente no seleccionado.
Preparando para desempaquetar .../12-python-dev_2.7.15~rc1-1_amd64.deb ...
Desempaquetando python-dev (2.7.15~rc1-1) ...
Seleccionando el paquete python-numpy previamente no seleccionado.
Preparando para desempaquetar .../13-python-numpy_1%3a1.13.3-2ubuntu1_amd64.deb ...
Desempaquetando python-numpy (1:1.13.3-2ubuntu1) ...
Seleccionando el paquete libdc1394-22-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../14-libdc1394-22-dev_2.2.5-1_amd64.deb ...
Desempaquetando libdc1394-22-dev:amd64 (2.2.5-1) ...
Seleccionando el paquete libtbb2:amd64 previamente no seleccionado.
Preparando para desempaquetar .../15-libtbb2_2017~U7-8_amd64.deb ...
Desempaquetando libtbb2:amd64 (2017~U7-8) ...
Seleccionando el paquete libtbb-dev:amd64 previamente no seleccionado.
Preparando para desempaquetar .../16-libtbb-dev_2017~U7-8_amd64.deb ...
Desempaquetando libtbb-dev:amd64 (2017~U7-8) ...
Configurando libraw1394-dev:amd64 (2.1.2-1) ...
Configurando libtbb2:amd64 (2017~U7-8) ...
Configurando libdc1394-22-dev:amd64 (2.2.5-1) ...
Configurando python-numpy (1:1.13.3-2ubuntu1) ...
Configurando libjbig-dev:amd64 (2.1-3.1build1) ...
Configurando libjpeg-turbo8-dev:amd64 (1.5.2-0ubuntu5.18.04.3) ...
Configurando libjpeg8-dev:amd64 (8c-2ubuntu8) ...
Configurando libjpeg-dev:amd64 (8c-2ubuntu8) ...
Configurando libpython2.7:amd64 (2.7.17-1~18.04ubuntu1) ...
Configurando libtiffxx5:amd64 (4.0.9-5ubuntu0.3) ...
Configurando libpython2.7-dev:amd64 (2.7.17-1~18.04ubuntu1) ...
Configurando liblzma-dev:amd64 (5.2.2-1.3) ...
Configurando python2.7-dev (2.7.17-1~18.04ubuntu1) ...
Configurando libtbb-dev:amd64 (2017~U7-8) ...
Configurando libpython-dev:amd64 (2.7.15~rc1-1) ...
Configurando python-dev (2.7.15~rc1-1) ...
Configurando libtiff5-dev:amd64 (4.0.9-5ubuntu0.3) ...
Configurando libtiff-dev (4.0.9-5ubuntu0.3) ...
Procesando disparadores para desktop-file-utils (0.23+linuxmint6) ...
Procesando disparadores para libc-bin (2.27-3ubuntu1) ...
Procesando disparadores para man-db (2.8.3-2ubuntu0.1) ...
Procesando disparadores para gnome-menus (3.13.3-11ubuntu1.1) ...
Procesando disparadores para mime-support (3.60ubuntu1) ...

seba@Asura:*~$ cd github/*

seba@Asura:*~/github$ git clone https://github.com/opencv/opencv.git*

Cloning into 'opencv'...
remote: Enumerating objects: 12, done.
remote: Counting objects: 100% (12/12), done.
remote: Compressing objects: 100% (10/10), done.
remote: Total 273049 (delta 2), reused 5 (delta 2), pack-reused 273037
Receiving objects: 100% (273049/273049), 468.95 MiB | 2.21 MiB/s, done.
Resolving deltas: 100% (190721/190721), done.
Checking out files: 100% (6178/6178), done.

seba@Asura:*~/github$ git clone https://github.com/opencv/opencv_contrib.git*

Cloning into 'opencv_contrib'...
remote: Enumerating objects: 32176, done.
remote: Total 32176 (delta 0), reused 0 (delta 0), pack-reused 32176
Receiving objects: 100% (32176/32176), 129.06 MiB | 1.87 MiB/s, done.
Resolving deltas: 100% (19903/19903), done.


seba@Asura:*~/opencv/build$ cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local -DBUILD_DOCS=TRUE -D BUIL_EXAMPLES=TRUE ..*


-- The CXX compiler identification is GNU 7.4.0
-- The C compiler identification is GNU 7.4.0
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Detected processor: x86_64
-- Found PythonInterp: /usr/bin/python2.7 (found suitable version "2.7.17", minimum required is "2.7") 
-- Found PythonLibs: /usr/lib/x86_64-linux-gnu/libpython2.7.so (found suitable exact version "2.7.17") 
-- Found PythonInterp: /usr/bin/python3 (found suitable version "3.6.9", minimum required is "3.2") 
-- Could NOT find PythonLibs (missing: PYTHON_LIBRARIES PYTHON_INCLUDE_DIRS) (Required is exact version "3.6.9")
-- Looking for ccache - not found
-- Performing Test HAVE_CXX_FSIGNED_CHAR
-- Performing Test HAVE_CXX_FSIGNED_CHAR - Success
-- Performing Test HAVE_C_FSIGNED_CHAR
-- Performing Test HAVE_C_FSIGNED_CHAR - Success
-- Performing Test HAVE_CXX_W
-- Performing Test HAVE_CXX_W - Success
-- Performing Test HAVE_C_W
-- Performing Test HAVE_C_W - Success
-- Performing Test HAVE_CXX_WALL
-- Performing Test HAVE_CXX_WALL - Success
-- Performing Test HAVE_C_WALL
-- Performing Test HAVE_C_WALL - Success
-- Performing Test HAVE_CXX_WERROR_RETURN_TYPE
-- Performing Test HAVE_CXX_WERROR_RETURN_TYPE - Success
-- Performing Test HAVE_C_WERROR_RETURN_TYPE
-- Performing Test HAVE_C_WERROR_RETURN_TYPE - Success
-- Performing Test HAVE_CXX_WERROR_NON_VIRTUAL_DTOR
-- Performing Test HAVE_CXX_WERROR_NON_VIRTUAL_DTOR - Success
-- Performing Test HAVE_C_WERROR_NON_VIRTUAL_DTOR
-- Performing Test HAVE_C_WERROR_NON_VIRTUAL_DTOR - Success
-- Performing Test HAVE_CXX_WERROR_ADDRESS
-- Performing Test HAVE_CXX_WERROR_ADDRESS - Success
-- Performing Test HAVE_C_WERROR_ADDRESS
-- Performing Test HAVE_C_WERROR_ADDRESS - Success
-- Performing Test HAVE_CXX_WERROR_SEQUENCE_POINT
-- Performing Test HAVE_CXX_WERROR_SEQUENCE_POINT - Success
-- Performing Test HAVE_C_WERROR_SEQUENCE_POINT
-- Performing Test HAVE_C_WERROR_SEQUENCE_POINT - Success
-- Performing Test HAVE_CXX_WFORMAT
-- Performing Test HAVE_CXX_WFORMAT - Success
-- Performing Test HAVE_C_WFORMAT
-- Performing Test HAVE_C_WFORMAT - Success
-- Performing Test HAVE_CXX_WERROR_FORMAT_SECURITY
-- Performing Test HAVE_CXX_WERROR_FORMAT_SECURITY - Success
-- Performing Test HAVE_C_WERROR_FORMAT_SECURITY
-- Performing Test HAVE_C_WERROR_FORMAT_SECURITY - Success
-- Performing Test HAVE_CXX_WMISSING_DECLARATIONS
-- Performing Test HAVE_CXX_WMISSING_DECLARATIONS - Success
-- Performing Test HAVE_C_WMISSING_DECLARATIONS
-- Performing Test HAVE_C_WMISSING_DECLARATIONS - Success
-- Performing Test HAVE_CXX_WMISSING_PROTOTYPES
-- Performing Test HAVE_CXX_WMISSING_PROTOTYPES - Failed
-- Performing Test HAVE_C_WMISSING_PROTOTYPES
-- Performing Test HAVE_C_WMISSING_PROTOTYPES - Success
-- Performing Test HAVE_CXX_WSTRICT_PROTOTYPES
-- Performing Test HAVE_CXX_WSTRICT_PROTOTYPES - Failed
-- Performing Test HAVE_C_WSTRICT_PROTOTYPES
-- Performing Test HAVE_C_WSTRICT_PROTOTYPES - Success
-- Performing Test HAVE_CXX_WUNDEF
-- Performing Test HAVE_CXX_WUNDEF - Success
-- Performing Test HAVE_C_WUNDEF
-- Performing Test HAVE_C_WUNDEF - Success
-- Performing Test HAVE_CXX_WINIT_SELF
-- Performing Test HAVE_CXX_WINIT_SELF - Success
-- Performing Test HAVE_C_WINIT_SELF
-- Performing Test HAVE_C_WINIT_SELF - Success
-- Performing Test HAVE_CXX_WPOINTER_ARITH
-- Performing Test HAVE_CXX_WPOINTER_ARITH - Success
-- Performing Test HAVE_C_WPOINTER_ARITH
-- Performing Test HAVE_C_WPOINTER_ARITH - Success
-- Performing Test HAVE_CXX_WSHADOW
-- Performing Test HAVE_CXX_WSHADOW - Success
-- Performing Test HAVE_C_WSHADOW
-- Performing Test HAVE_C_WSHADOW - Success
-- Performing Test HAVE_CXX_WSIGN_PROMO
-- Performing Test HAVE_CXX_WSIGN_PROMO - Success
-- Performing Test HAVE_C_WSIGN_PROMO
-- Performing Test HAVE_C_WSIGN_PROMO - Failed
-- Performing Test HAVE_CXX_WUNINITIALIZED
-- Performing Test HAVE_CXX_WUNINITIALIZED - Success
-- Performing Test HAVE_C_WUNINITIALIZED
-- Performing Test HAVE_C_WUNINITIALIZED - Success
-- Performing Test HAVE_CXX_WSUGGEST_OVERRIDE
-- Performing Test HAVE_CXX_WSUGGEST_OVERRIDE - Success
-- Performing Test HAVE_C_WSUGGEST_OVERRIDE
-- Performing Test HAVE_C_WSUGGEST_OVERRIDE - Failed
-- Performing Test HAVE_CXX_WNO_DELETE_NON_VIRTUAL_DTOR
-- Performing Test HAVE_CXX_WNO_DELETE_NON_VIRTUAL_DTOR - Success
-- Performing Test HAVE_C_WNO_DELETE_NON_VIRTUAL_DTOR
-- Performing Test HAVE_C_WNO_DELETE_NON_VIRTUAL_DTOR - Failed
-- Performing Test HAVE_CXX_WNO_UNNAMED_TYPE_TEMPLATE_ARGS
-- Performing Test HAVE_CXX_WNO_UNNAMED_TYPE_TEMPLATE_ARGS - Failed
-- Performing Test HAVE_C_WNO_UNNAMED_TYPE_TEMPLATE_ARGS
-- Performing Test HAVE_C_WNO_UNNAMED_TYPE_TEMPLATE_ARGS - Failed
-- Performing Test HAVE_CXX_WNO_COMMENT
-- Performing Test HAVE_CXX_WNO_COMMENT - Success
-- Performing Test HAVE_C_WNO_COMMENT
-- Performing Test HAVE_C_WNO_COMMENT - Success
-- Performing Test HAVE_CXX_WIMPLICIT_FALLTHROUGH_3
-- Performing Test HAVE_CXX_WIMPLICIT_FALLTHROUGH_3 - Success
-- Performing Test HAVE_C_WIMPLICIT_FALLTHROUGH_3
-- Performing Test HAVE_C_WIMPLICIT_FALLTHROUGH_3 - Success
-- Performing Test HAVE_CXX_WNO_STRICT_OVERFLOW
-- Performing Test HAVE_CXX_WNO_STRICT_OVERFLOW - Success
-- Performing Test HAVE_C_WNO_STRICT_OVERFLOW
-- Performing Test HAVE_C_WNO_STRICT_OVERFLOW - Success
-- Performing Test HAVE_CXX_FDIAGNOSTICS_SHOW_OPTION
-- Performing Test HAVE_CXX_FDIAGNOSTICS_SHOW_OPTION - Success
-- Performing Test HAVE_C_FDIAGNOSTICS_SHOW_OPTION
-- Performing Test HAVE_C_FDIAGNOSTICS_SHOW_OPTION - Success
-- Performing Test HAVE_CXX_WNO_LONG_LONG
-- Performing Test HAVE_CXX_WNO_LONG_LONG - Success
-- Performing Test HAVE_C_WNO_LONG_LONG
-- Performing Test HAVE_C_WNO_LONG_LONG - Success
-- Performing Test HAVE_CXX_PTHREAD
-- Performing Test HAVE_CXX_PTHREAD - Success
-- Performing Test HAVE_C_PTHREAD
-- Performing Test HAVE_C_PTHREAD - Success
-- Performing Test HAVE_CXX_FOMIT_FRAME_POINTER
-- Performing Test HAVE_CXX_FOMIT_FRAME_POINTER - Success
-- Performing Test HAVE_C_FOMIT_FRAME_POINTER
-- Performing Test HAVE_C_FOMIT_FRAME_POINTER - Success
-- Performing Test HAVE_CXX_FFUNCTION_SECTIONS
-- Performing Test HAVE_CXX_FFUNCTION_SECTIONS - Success
-- Performing Test HAVE_C_FFUNCTION_SECTIONS
-- Performing Test HAVE_C_FFUNCTION_SECTIONS - Success
-- Performing Test HAVE_CXX_FDATA_SECTIONS
-- Performing Test HAVE_CXX_FDATA_SECTIONS - Success
-- Performing Test HAVE_C_FDATA_SECTIONS
-- Performing Test HAVE_C_FDATA_SECTIONS - Success
-- Performing Test HAVE_CXX_MSSE (check file: cmake/checks/cpu_sse.cpp)
-- Performing Test HAVE_CXX_MSSE - Success
-- Performing Test HAVE_CXX_MSSE2 (check file: cmake/checks/cpu_sse2.cpp)
-- Performing Test HAVE_CXX_MSSE2 - Success
-- Performing Test HAVE_CXX_MSSE3 (check file: cmake/checks/cpu_sse3.cpp)
-- Performing Test HAVE_CXX_MSSE3 - Success
-- Performing Test HAVE_CXX_MSSSE3 (check file: cmake/checks/cpu_ssse3.cpp)
-- Performing Test HAVE_CXX_MSSSE3 - Success
-- Performing Test HAVE_CXX_MSSE4_1 (check file: cmake/checks/cpu_sse41.cpp)
-- Performing Test HAVE_CXX_MSSE4_1 - Success
-- Performing Test HAVE_CXX_MPOPCNT (check file: cmake/checks/cpu_popcnt.cpp)
-- Performing Test HAVE_CXX_MPOPCNT - Success
-- Performing Test HAVE_CXX_MSSE4_2 (check file: cmake/checks/cpu_sse42.cpp)
-- Performing Test HAVE_CXX_MSSE4_2 - Success
-- Performing Test HAVE_CXX_MF16C (check file: cmake/checks/cpu_fp16.cpp)
-- Performing Test HAVE_CXX_MF16C - Success
-- Performing Test HAVE_CXX_MFMA
-- Performing Test HAVE_CXX_MFMA - Success
-- Performing Test HAVE_CXX_MAVX (check file: cmake/checks/cpu_avx.cpp)
-- Performing Test HAVE_CXX_MAVX - Success
-- Performing Test HAVE_CXX_MAVX2 (check file: cmake/checks/cpu_avx2.cpp)
-- Performing Test HAVE_CXX_MAVX2 - Success
-- Performing Test HAVE_CXX_MAVX512F (check file: cmake/checks/cpu_avx512.cpp)
-- Performing Test HAVE_CXX_MAVX512F - Success
-- Performing Test HAVE_CXX_MAVX512F_MAVX512CD (check file: cmake/checks/cpu_avx512common.cpp)
-- Performing Test HAVE_CXX_MAVX512F_MAVX512CD - Success
-- Performing Test HAVE_CXX_MAVX512F_MAVX512CD_MAVX512VL_MAVX512BW_MAVX512DQ (check file: cmake/checks/cpu_avx512skx.cpp)
-- Performing Test HAVE_CXX_MAVX512F_MAVX512CD_MAVX512VL_MAVX512BW_MAVX512DQ - Success
-- Performing Test HAVE_CPU_BASELINE_FLAGS
-- Performing Test HAVE_CPU_BASELINE_FLAGS - Success
-- Performing Test HAVE_CPU_DISPATCH_FLAGS_SSE4_1
-- Performing Test HAVE_CPU_DISPATCH_FLAGS_SSE4_1 - Success
-- Performing Test HAVE_CPU_DISPATCH_FLAGS_SSE4_2
-- Performing Test HAVE_CPU_DISPATCH_FLAGS_SSE4_2 - Success
-- Performing Test HAVE_CPU_DISPATCH_FLAGS_FP16
-- Performing Test HAVE_CPU_DISPATCH_FLAGS_FP16 - Success
-- Performing Test HAVE_CPU_DISPATCH_FLAGS_AVX
-- Performing Test HAVE_CPU_DISPATCH_FLAGS_AVX - Success
-- Performing Test HAVE_CPU_DISPATCH_FLAGS_AVX2
-- Performing Test HAVE_CPU_DISPATCH_FLAGS_AVX2 - Success
-- Performing Test HAVE_CPU_DISPATCH_FLAGS_AVX512_SKX
-- Performing Test HAVE_CPU_DISPATCH_FLAGS_AVX512_SKX - Success
-- Performing Test HAVE_CXX_FVISIBILITY_HIDDEN
-- Performing Test HAVE_CXX_FVISIBILITY_HIDDEN - Success
-- Performing Test HAVE_C_FVISIBILITY_HIDDEN
-- Performing Test HAVE_C_FVISIBILITY_HIDDEN - Success
-- Performing Test HAVE_CXX_FVISIBILITY_INLINES_HIDDEN
-- Performing Test HAVE_CXX_FVISIBILITY_INLINES_HIDDEN - Success
-- Performing Test HAVE_C_FVISIBILITY_INLINES_HIDDEN
-- Performing Test HAVE_C_FVISIBILITY_INLINES_HIDDEN - Failed
-- Performing Test HAVE_LINK_AS_NEEDED
-- Performing Test HAVE_LINK_AS_NEEDED - Success
-- Looking for pthread.h
-- Looking for pthread.h - found
-- Looking for posix_memalign
-- Looking for posix_memalign - found
-- Looking for malloc.h
-- Looking for malloc.h - found
-- Looking for memalign
-- Looking for memalign - found
-- Check if the system is big endian
-- Searching 16 bit integer
-- Looking for sys/types.h
-- Looking for sys/types.h - found
-- Looking for stdint.h
-- Looking for stdint.h - found
-- Looking for stddef.h
-- Looking for stddef.h - found
-- Check size of unsigned short
-- Check size of unsigned short - done
-- Using unsigned short
-- Check if the system is big endian - little endian
-- Found ZLIB: /usr/lib/x86_64-linux-gnu/libz.so (found suitable version "1.2.11", minimum required is "1.2.3") 
-- Found JPEG: /usr/lib/x86_64-linux-gnu/libjpeg.so  
-- Found TIFF: /usr/lib/x86_64-linux-gnu/libtiff.so (found version "4.0.9") 
-- Performing Test HAVE_C_STD_C99
-- Performing Test HAVE_C_STD_C99 - Success
-- Performing Test HAVE_C_WNO_UNUSED_VARIABLE
-- Performing Test HAVE_C_WNO_UNUSED_VARIABLE - Success
-- Performing Test HAVE_C_WNO_UNUSED_FUNCTION
-- Performing Test HAVE_C_WNO_UNUSED_FUNCTION - Success
-- Performing Test HAVE_C_WNO_SHADOW
-- Performing Test HAVE_C_WNO_SHADOW - Success
-- Performing Test HAVE_C_WNO_MAYBE_UNINITIALIZED
-- Performing Test HAVE_C_WNO_MAYBE_UNINITIALIZED - Success
-- Performing Test HAVE_C_WNO_MISSING_PROTOTYPES
-- Performing Test HAVE_C_WNO_MISSING_PROTOTYPES - Success
-- Performing Test HAVE_C_WNO_MISSING_DECLARATIONS
-- Performing Test HAVE_C_WNO_MISSING_DECLARATIONS - Success
-- Performing Test HAVE_C_WNO_IMPLICIT_FALLTHROUGH
-- Performing Test HAVE_C_WNO_IMPLICIT_FALLTHROUGH - Success
-- Could NOT find OpenJPEG (minimal suitable version: 2.0, recommended version >= 2.3.1)
-- Could NOT find Jasper (missing: JASPER_LIBRARIES JASPER_INCLUDE_DIR) 
-- Performing Test HAVE_C_WNO_IMPLICIT_FUNCTION_DECLARATION
-- Performing Test HAVE_C_WNO_IMPLICIT_FUNCTION_DECLARATION - Success
-- Performing Test HAVE_C_WNO_UNINITIALIZED
-- Performing Test HAVE_C_WNO_UNINITIALIZED - Success
-- Performing Test HAVE_C_WNO_UNUSED_BUT_SET_PARAMETER
-- Performing Test HAVE_C_WNO_UNUSED_BUT_SET_PARAMETER - Success
-- Performing Test HAVE_C_WNO_UNUSED
-- Performing Test HAVE_C_WNO_UNUSED - Success
-- Performing Test HAVE_C_WNO_SIGN_COMPARE
-- Performing Test HAVE_C_WNO_SIGN_COMPARE - Success
-- Performing Test HAVE_C_WNO_POINTER_COMPARE
-- Performing Test HAVE_C_WNO_POINTER_COMPARE - Success
-- Performing Test HAVE_C_WNO_ABSOLUTE_VALUE
-- Performing Test HAVE_C_WNO_ABSOLUTE_VALUE - Failed
-- Performing Test HAVE_C_WNO_UNUSED_PARAMETER
-- Performing Test HAVE_C_WNO_UNUSED_PARAMETER - Success
-- Performing Test HAVE_C_WNO_STRICT_PROTOTYPES
-- Performing Test HAVE_C_WNO_STRICT_PROTOTYPES - Success
-- Found ZLIB: /usr/lib/x86_64-linux-gnu/libz.so (found version "1.2.11") 
-- Found PNG: /usr/lib/x86_64-linux-gnu/libpng.so (found version "1.6.34") 
-- Looking for /usr/include/libpng/png.h
-- Looking for /usr/include/libpng/png.h - found
-- Looking for semaphore.h
-- Looking for semaphore.h - found
-- Performing Test HAVE_CXX_WNO_SHADOW
-- Performing Test HAVE_CXX_WNO_SHADOW - Success
-- Performing Test HAVE_CXX_WNO_UNUSED
-- Performing Test HAVE_CXX_WNO_UNUSED - Success
-- Performing Test HAVE_CXX_WNO_SIGN_COMPARE
-- Performing Test HAVE_CXX_WNO_SIGN_COMPARE - Success
-- Performing Test HAVE_CXX_WNO_UNDEF
-- Performing Test HAVE_CXX_WNO_UNDEF - Success
-- Performing Test HAVE_CXX_WNO_MISSING_DECLARATIONS
-- Performing Test HAVE_CXX_WNO_MISSING_DECLARATIONS - Success
-- Performing Test HAVE_CXX_WNO_UNINITIALIZED
-- Performing Test HAVE_CXX_WNO_UNINITIALIZED - Success
-- Performing Test HAVE_CXX_WNO_SWITCH
-- Performing Test HAVE_CXX_WNO_SWITCH - Success
-- Performing Test HAVE_CXX_WNO_PARENTHESES
-- Performing Test HAVE_CXX_WNO_PARENTHESES - Success
-- Performing Test HAVE_CXX_WNO_ARRAY_BOUNDS
-- Performing Test HAVE_CXX_WNO_ARRAY_BOUNDS - Success
-- Performing Test HAVE_CXX_WNO_EXTRA
-- Performing Test HAVE_CXX_WNO_EXTRA - Success
-- Performing Test HAVE_CXX_WNO_DEPRECATED_DECLARATIONS
-- Performing Test HAVE_CXX_WNO_DEPRECATED_DECLARATIONS - Success
-- Performing Test HAVE_CXX_WNO_MISLEADING_INDENTATION
-- Performing Test HAVE_CXX_WNO_MISLEADING_INDENTATION - Success
-- Performing Test HAVE_CXX_WNO_DEPRECATED
-- Performing Test HAVE_CXX_WNO_DEPRECATED - Success
-- Performing Test HAVE_CXX_WNO_SUGGEST_OVERRIDE
-- Performing Test HAVE_CXX_WNO_SUGGEST_OVERRIDE - Success
-- Performing Test HAVE_CXX_WNO_INCONSISTENT_MISSING_OVERRIDE
-- Performing Test HAVE_CXX_WNO_INCONSISTENT_MISSING_OVERRIDE - Failed
-- Performing Test HAVE_CXX_WNO_IMPLICIT_FALLTHROUGH
-- Performing Test HAVE_CXX_WNO_IMPLICIT_FALLTHROUGH - Success
-- Performing Test HAVE_CXX_WNO_TAUTOLOGICAL_COMPARE
-- Performing Test HAVE_CXX_WNO_TAUTOLOGICAL_COMPARE - Success
-- Performing Test HAVE_CXX_WNO_MISSING_PROTOTYPES
-- Performing Test HAVE_CXX_WNO_MISSING_PROTOTYPES - Failed
-- Performing Test HAVE_CXX_WNO_REORDER
-- Performing Test HAVE_CXX_WNO_REORDER - Success
-- Performing Test HAVE_CXX_WNO_UNUSED_RESULT
-- Performing Test HAVE_CXX_WNO_UNUSED_RESULT - Success
-- Checking for module 'gtk+-3.0'
--   No package 'gtk+-3.0' found
-- Checking for module 'gtk+-2.0'
--   Found gtk+-2.0, version 2.24.32
-- Checking for module 'gthread-2.0'
--   Found gthread-2.0, version 2.56.4
-- IPPICV: Download: ippicv_2020_lnx_intel64_20191018_general.tgz
-- found Intel IPP (ICV version): 2020.0.0 [2020.0.0 Gold]
-- at: /home/seba/opencv/build/3rdparty/ippicv/ippicv_lnx/icv
-- found Intel IPP Integration Wrappers sources: 2020.0.0
-- at: /home/seba/opencv/build/3rdparty/ippicv/ippicv_lnx/iw
-- Could not find OpenBLAS include. Turning OpenBLAS_FOUND off
-- Could not find OpenBLAS lib. Turning OpenBLAS_FOUND off
-- Could NOT find Atlas (missing: Atlas_CBLAS_INCLUDE_DIR Atlas_CLAPACK_INCLUDE_DIR Atlas_CBLAS_LIBRARY Atlas_BLAS_LIBRARY Atlas_LAPACK_LIBRARY) 
-- Looking for pthread.h
-- Looking for pthread.h - found
-- Looking for pthread_create
-- Looking for pthread_create - found
-- Found Threads: TRUE  
-- A library with BLAS API not found. Please specify library location.
-- LAPACK requires BLAS
-- A library with LAPACK API not found. Please specify library location.
-- Performing Test HAVE_CXX_WNO_UNUSED_PARAMETER
-- Performing Test HAVE_CXX_WNO_UNUSED_PARAMETER - Success
-- Performing Test HAVE_CXX_WNO_UNUSED_LOCAL_TYPEDEFS
-- Performing Test HAVE_CXX_WNO_UNUSED_LOCAL_TYPEDEFS - Success
-- Performing Test HAVE_CXX_WNO_SIGN_PROMO
-- Performing Test HAVE_CXX_WNO_SIGN_PROMO - Success
-- Performing Test HAVE_CXX_WNO_TAUTOLOGICAL_UNDEFINED_COMPARE
-- Performing Test HAVE_CXX_WNO_TAUTOLOGICAL_UNDEFINED_COMPARE - Failed
-- Performing Test HAVE_CXX_WNO_IGNORED_QUALIFIERS
-- Performing Test HAVE_CXX_WNO_IGNORED_QUALIFIERS - Success
-- Performing Test HAVE_CXX_WNO_UNUSED_FUNCTION
-- Performing Test HAVE_CXX_WNO_UNUSED_FUNCTION - Success
-- Performing Test HAVE_CXX_WNO_UNUSED_CONST_VARIABLE
-- Performing Test HAVE_CXX_WNO_UNUSED_CONST_VARIABLE - Success
-- Performing Test HAVE_CXX_WNO_SHORTEN_64_TO_32
-- Performing Test HAVE_CXX_WNO_SHORTEN_64_TO_32 - Failed
-- Performing Test HAVE_CXX_WNO_INVALID_OFFSETOF
-- Performing Test HAVE_CXX_WNO_INVALID_OFFSETOF - Success
-- Performing Test HAVE_CXX_WNO_ENUM_COMPARE_SWITCH
-- Performing Test HAVE_CXX_WNO_ENUM_COMPARE_SWITCH - Failed
-- Could NOT find JNI (missing: JAVA_INCLUDE_PATH JAVA_INCLUDE_PATH2 JAVA_AWT_INCLUDE_PATH) 
-- Could NOT find Pylint (missing: PYLINT_EXECUTABLE) 
-- Could NOT find Flake8 (missing: FLAKE8_EXECUTABLE) 
-- VTK is not found. Please set -DVTK_DIR in CMake to VTK build directory, or to VTK install subdirectory with VTKConfig.cmake file
-- Looking for dlerror in dl
-- Looking for dlerror in dl - found
-- Performing Test HAVE_C_WNO_UNDEF
-- Performing Test HAVE_C_WNO_UNDEF - Success
-- ADE: Download: v0.1.1f.zip
-- OpenCV Python: during development append to PYTHONPATH: /home/seba/opencv/build/python_loader
-- Checking for modules 'libavcodec;libavformat;libavutil;libswscale'
--   Found libavcodec, version 57.107.100
--   Found libavformat, version 57.83.100
--   Found libavutil, version 55.78.100
--   Found libswscale, version 4.8.100
-- Checking for module 'libavresample'
--   No package 'libavresample' found
-- Checking for module 'gstreamer-base-1.0'
--   No package 'gstreamer-base-1.0' found
-- Checking for module 'gstreamer-app-1.0'
--   No package 'gstreamer-app-1.0' found
-- Checking for module 'gstreamer-riff-1.0'
--   No package 'gstreamer-riff-1.0' found
-- Checking for module 'gstreamer-pbutils-1.0'
--   No package 'gstreamer-pbutils-1.0' found
-- Checking for module 'libdc1394-2'
--   Found libdc1394-2, version 2.2.5
-- Allocator metrics storage type: 'long long'
-- Registering hook 'INIT_MODULE_SOURCES_opencv_dnn': /home/seba/opencv/modules/dnn/cmake/hooks/INIT_MODULE_SOURCES_opencv_dnn.cmake
-- opencv_dnn: filter out cuda4dnn source code
-- Performing Test HAVE_CXX_WNO_OVERLOADED_VIRTUAL
-- Performing Test HAVE_CXX_WNO_OVERLOADED_VIRTUAL - Success
-- Performing Test HAVE_CXX_WNO_UNUSED_PRIVATE_FIELD
-- Performing Test HAVE_CXX_WNO_UNUSED_PRIVATE_FIELD - Failed
-- Could NOT find Doxygen (missing: DOXYGEN_EXECUTABLE) 
-- 
-- General configuration for OpenCV 4.3.0-dev =====================================
--   Version control:               unknown
-- 
--   Platform:
--     Timestamp:                   2020-05-04T16:51:20Z
--     Host:                        Linux 4.15.0-64-generic x86_64
--     CMake:                       3.10.2
--     CMake generator:             Unix Makefiles
--     CMake build tool:            /usr/bin/make
--     Configuration:               Release
-- 
--   CPU/HW features:
--     Baseline:                    SSE SSE2 SSE3
--       requested:                 SSE3
--     Dispatched code generation:  SSE4_1 SSE4_2 FP16 AVX AVX2 AVX512_SKX
--       requested:                 SSE4_1 SSE4_2 AVX FP16 AVX2 AVX512_SKX
--       SSE4_1 (16 files):         + SSSE3 SSE4_1
--       SSE4_2 (2 files):          + SSSE3 SSE4_1 POPCNT SSE4_2
--       FP16 (1 files):            + SSSE3 SSE4_1 POPCNT SSE4_2 FP16 AVX
--       AVX (5 files):             + SSSE3 SSE4_1 POPCNT SSE4_2 AVX
--       AVX2 (30 files):           + SSSE3 SSE4_1 POPCNT SSE4_2 FP16 FMA3 AVX AVX2
--       AVX512_SKX (6 files):      + SSSE3 SSE4_1 POPCNT SSE4_2 FP16 FMA3 AVX AVX2 AVX_512F AVX512_COMMON AVX512_SKX
-- 
--   C/C++:
--     Built as dynamic libs?:      YES
--     C++ standard:                11
--     C++ Compiler:                /usr/bin/c++  (ver 7.4.0)
--     C++ flags (Release):         -fsigned-char -W -Wall -Werror=return-type -Werror=non-virtual-dtor -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Wmissing-declarations -Wundef -Winit-self -Wpointer-arith -Wshadow -Wsign-promo -Wuninitialized -Winit-self -Wsuggest-override -Wno-delete-non-virtual-dtor -Wno-comment -Wimplicit-fallthrough=3 -Wno-strict-overflow -fdiagnostics-show-option -Wno-long-long -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections  -msse -msse2 -msse3 -fvisibility=hidden -fvisibility-inlines-hidden -O3 -DNDEBUG  -DNDEBUG
--     C++ flags (Debug):           -fsigned-char -W -Wall -Werror=return-type -Werror=non-virtual-dtor -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Wmissing-declarations -Wundef -Winit-self -Wpointer-arith -Wshadow -Wsign-promo -Wuninitialized -Winit-self -Wsuggest-override -Wno-delete-non-virtual-dtor -Wno-comment -Wimplicit-fallthrough=3 -Wno-strict-overflow -fdiagnostics-show-option -Wno-long-long -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections  -msse -msse2 -msse3 -fvisibility=hidden -fvisibility-inlines-hidden -g  -O0 -DDEBUG -D_DEBUG
--     C Compiler:                  /usr/bin/cc
--     C flags (Release):           -fsigned-char -W -Wall -Werror=return-type -Werror=non-virtual-dtor -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Winit-self -Wpointer-arith -Wshadow -Wuninitialized -Winit-self -Wno-comment -Wimplicit-fallthrough=3 -Wno-strict-overflow -fdiagnostics-show-option -Wno-long-long -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections  -msse -msse2 -msse3 -fvisibility=hidden -O3 -DNDEBUG  -DNDEBUG
--     C flags (Debug):             -fsigned-char -W -Wall -Werror=return-type -Werror=non-virtual-dtor -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Winit-self -Wpointer-arith -Wshadow -Wuninitialized -Winit-self -Wno-comment -Wimplicit-fallthrough=3 -Wno-strict-overflow -fdiagnostics-show-option -Wno-long-long -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections  -msse -msse2 -msse3 -fvisibility=hidden -g  -O0 -DDEBUG -D_DEBUG
--     Linker flags (Release):      -Wl,--exclude-libs,libippicv.a -Wl,--exclude-libs,libippiw.a   -Wl,--gc-sections -Wl,--as-needed  
--     Linker flags (Debug):        -Wl,--exclude-libs,libippicv.a -Wl,--exclude-libs,libippiw.a   -Wl,--gc-sections -Wl,--as-needed  
--     ccache:                      NO
--     Precompiled headers:         NO
--     Extra dependencies:          dl m pthread rt
--     3rdparty dependencies:
-- 
--   OpenCV modules:
--     To be built:                 calib3d core dnn features2d flann gapi highgui imgcodecs imgproc ml objdetect photo python2 stitching ts video videoio
--     Disabled:                    world
--     Disabled by dependency:      -
--     Unavailable:                 java js python3
--     Applications:                tests perf_tests apps
--     Documentation:               NO
--     Non-free algorithms:         NO
-- 
--   GUI: 
--     GTK+:                        YES (ver 2.24.32)
--       GThread :                  YES (ver 2.56.4)
--       GtkGlExt:                  NO
--     VTK support:                 NO
-- 
--   Media I/O: 
--     ZLib:                        /usr/lib/x86_64-linux-gnu/libz.so (ver 1.2.11)
--     JPEG:                        /usr/lib/x86_64-linux-gnu/libjpeg.so (ver 80)
--     WEBP:                        build (ver encoder: 0x020f)
--     PNG:                         /usr/lib/x86_64-linux-gnu/libpng.so (ver 1.6.34)
--     TIFF:                        /usr/lib/x86_64-linux-gnu/libtiff.so (ver 42 / 4.0.9)
--     JPEG 2000:                   build Jasper (ver 1.900.1)
--     OpenEXR:                     build (ver 2.3.0)
--     HDR:                         YES
--     SUNRASTER:                   YES
--     PXM:                         YES
--     PFM:                         YES
-- 
--   Video I/O:
--     DC1394:                      YES (2.2.5)
--     FFMPEG:                      YES
--       avcodec:                   YES (57.107.100)
--       avformat:                  YES (57.83.100)
--       avutil:                    YES (55.78.100)
--       swscale:                   YES (4.8.100)
--       avresample:                NO
--     GStreamer:                   NO
--     v4l/v4l2:                    YES (linux/videodev2.h)
-- 
--   Parallel framework:            pthreads
-- 
--   Trace:                         YES (with Intel ITT)
-- 
--   Other third-party libraries:
--     Intel IPP:                   2020.0.0 Gold [2020.0.0]
--            at:                   /home/seba/opencv/build/3rdparty/ippicv/ippicv_lnx/icv
--     Intel IPP IW:                sources (2020.0.0)
--               at:                /home/seba/opencv/build/3rdparty/ippicv/ippicv_lnx/iw
--     Lapack:                      NO
--     Eigen:                       NO
--     Custom HAL:                  NO
--     Protobuf:                    build (3.5.1)
-- 
--   OpenCL:                        YES (no extra features)
--     Include path:                /home/seba/opencv/3rdparty/include/opencl/1.2
--     Link libraries:              Dynamic load
-- 
--   Python 2:
--     Interpreter:                 /usr/bin/python2.7 (ver 2.7.17)
--     Libraries:                   /usr/lib/x86_64-linux-gnu/libpython2.7.so (ver 2.7.17)
--     numpy:                       /home/seba/.local/lib/python2.7/site-packages/numpy/core/include (ver 1.16.6)
--     install path:                lib/python2.7/dist-packages/cv2/python-2.7
-- 
--   Python (for build):            /usr/bin/python2.7
-- 
--   Java:                          
--     ant:                         NO
--     JNI:                         NO
--     Java wrappers:               NO
--     Java tests:                  NO
-- 
--   Install to:                    /usr/local
-- -----------------------------------------------------------------
-- 
-- Configuring done
-- Generating done
-- Build files have been written to: /home/seba/opencv/build



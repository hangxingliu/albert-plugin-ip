# My Building Recipe

``` bash
rm build -rf;
mkdir build;
cd build;
cmake .. \
	-DCMAKE_INSTALL_PREFIX=/usr \
	-DCMAKE_BUILD_TYPE=Release \
	-DCMAKE_INSTALL_RPATH_USE_LINK_PATH:BOOL=ON \
	-DQt5_DIR=/path/to/Qt5.11.3/5.11.3/gcc_64/lib/cmake/Qt5 \
	-DBUILD_PYTHON=OFF \
	-DBUILD_FILES=OFF \
	-DBUILD_FIREFOXBOOKMARKS=OFF \
	-DBUILD_EXTERNALEXTENSIONS=OFF \
	-DBUILD_QMLBOXMODEL=OFF;
make -j16;

# debug
./bin/albert --plugin-dirs ./lib

# install
sudo make install

# albert will be install to:
#   /usr/bin/albert
#   /usr/lib/x86_64-linux-gnu/albert/plugins/libxxx.so

```

## Developing

Open `CmakeLists.txt` in Qt Creator

Add `-j16` into **Tool arguments** in **Build Step** section.

Add `--plugin-dirs ./../lib` into **Command line arguments** int **Run** page.

## Knowledge

Set `-j16` for make via env varibale.

``` bash
export MAKEFLAGS='-j16'
```

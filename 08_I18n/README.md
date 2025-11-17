# how to build

1. generate system config

```
./autogen.sh
```

2. configure the project

```
./configure --prefix=/usr/local
```

```
make
```

# how to test

```
make install DESTDIR=/tmp/test
```

```
export LANG=ru_RU.utf8

cd /tmp/test/usr/local/bin && ./guessnum
```

translations are located at `po/ru.po`

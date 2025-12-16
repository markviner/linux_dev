# Инструкции по сборке и установке

Все было проверено только на openSUSE Tumbleweed (latest snapshot), поэтому нет
10000% гарантий, чтобы будет работать на вашем дистрибутиве

## Тестовая установка (БЕЗ root)

```bash
cd tplotter
mkdir build
cd build

# Настройка с префиксом /tmp/test
cmake -DCMAKE_INSTALL_PREFIX=/tmp/test ..

# Сборка
make

# Запуск тестов
make test

# Установка в /tmp/test
make install

# Проверка установки
ls -la /tmp/test/bin/
ls -la /tmp/test/lib/
ls -la /tmp/test/include/
ls -la /tmp/test/share/man/man1/
```

### Тестирование установленной программы

```bash
# Добавляем библиотеку в путь
export LD_LIBRARY_PATH=/tmp/test/lib64:$LD_LIBRARY_PATH

# Тестируем программу
/tmp/test/bin/tplotter "sin(x)"
/tmp/test/bin/tplotter "sin(x)" "cos(x)"

# Проверяем man page
man /tmp/test/share/man/man1/tplotter.1

# Проверяем русскую локаль
LANG=ru_RU.UTF-8 /tmp/test/bin/tplotter
LANG=ru_RU.UTF-8 /tmp/test/bin/tplotter "sin(x)"
```

### Деинсталляция из /tmp/test

```bash
cd build
make uninstall

# Проверяем, что файлы удалены
ls /tmp/test/bin/
ls /tmp/test/lib64/
```

## Установка в систему (root)

**ВНИМАНИЕ!** **WARNING!** **УВАГА!** **ACHTUNG!**

Это установит программу в систему. Сначала убедитесь, что тестовая установка
работает!

### Очистка предыдущей сборки

```bash
cd tplotter
rm -rf build
mkdir build
cd build
```

### Сборка для системной установки

```bash
# Настройка для /usr/local (по умолчанию)
cmake ..

# Или явно укажите префикс
cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..
make
make test
```

### Установка от root

```bash
sudo make install
sudo ldconfig
```

### Проверка системной установки

```bash
# Проверяем, что программа в PATH
which tplotter

# Запускаем
tplotter "sin(x)"
tplotter "sin(x)" "cos(x)" "x^2/10"

# Проверяем man page
man tplotter

# Проверяем русскую локаль
LANG=ru_RU.UTF-8 tplotter
LANG=ru_RU.UTF-8 tplotter "sin(x)"

# Проверяем библиотеку
ls -la /usr/local/lib64/libeval.so*
ls -la /usr/local/include/eval.h
```

### Деинсталляция от root

```bash
cd build
sudo make uninstall
sudo ldconfig

# Проверяем, что программа удалена
which tplotter
ls /usr/local/bin/tplotter
```

## Примеры использования

```bash
# Простой синус
tplotter "sin(x)"

# Несколько функций
tplotter "sin(x)" "cos(x)" "tan(x)/10"

# С константами
tplotter "sin(2*pi*x)" "cos(pi*x/2)"

# Квадратичная функция
tplotter "x^2" "x^3/10"

# Экспонента и логарифм
tplotter "exp(x/5)" "ln(x+11)"
```

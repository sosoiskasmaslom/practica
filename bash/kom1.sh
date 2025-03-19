
# Лабороторная работа №9 по информатике

#!/bin/bash

if [ -z $1 ]; then
    echo "Необходимо ввести путь к каталогу"
    exit 1
fi

mkdir $1/PRIM
mkdir $1/PRIM/PRIM1
mkdir $1/PRIM/PRIM2

text="Операционная система – это совокупность программ, предназначенных для организации диалога с пользователем, управления аппаратурой и ресурсами компьютера"

echo $text > $1/PRIM/PRIM1/a.txt
cp $1/PRIM/PRIM1/a.txt $1/PRIM/PRIM1/a1.txt
cat $1/PRIM/PRIM1/a.txt
mv $1/PRIM/PRIM1/a.txt $1/PRIM/PRIM1/a2.txt
cat $1/PRIM/PRIM1/a2.txt

cat $1/PRIM/PRIM1/a1.txt > $1/PRIM/PRIM1/a3.txt 
cat $1/PRIM/PRIM1/a2.txt >> $1/PRIM/PRIM1/a3.txt
cat $1/PRIM/PRIM1/a3.txt

echo "Файлом называется поименованная область на диске" > $1/PRIM/PRIM2/file.txt
cp $1/PRIM/PRIM2/file.txt $1/PRIM/PRIM2/file1.txt
cat $1/PRIM/PRIM2/file.txt
mv $1/PRIM/PRIM2/file.txt $1/PRIM/PRIM2/file2.txt
cat $1/PRIM/PRIM2/file2.txt

cat $1/PRIM/PRIM2/file1.txt > $1/PRIM/PRIM2/file3.txt 
cat $1/PRIM/PRIM2/file2.txt >> $1/PRIM/PRIM2/file3.txt
cat $1/PRIM/PRIM2/file3.txt

read

rm -fr $1/PRIM
clear

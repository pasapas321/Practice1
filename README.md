**Практическое задание для курса "Формальные языки и трансляции". Задача 17.**
==========

Задача
----------
Даны α и слово u ∈ {a, b, c}<sup>*</sup>. Найти длину самого длинного суффикса u, являющегося также суффиксом некоторого слова в L.

Решение
----------
Для каждого рассматриваемого регулярного выражения в структуре RegInfo будем хранить информацию о том, распознается ли ε данным регулярным выражением. Для каждого подотрезка слова u, выясняем, распознается ли он данным регулярным выражением. Также для каждого префикса слова u храним длину наибольшего общего суффикса этого префикса и некоторого слова, распознаваемого регулярным выражением. С помощью динамического программирования получаем звезду Клини, конкатенацию и сумму регулярных выражений.   
# SDiIS-Lab_3

Лабораторная работа №3 по курсу ППвИС. Выполнил: Насточкин Илья Сергеевич. Группа 921702 Тема: Модель железной дороги.

В данной лабораторной работе я использовал библиотеку SFML, так как уже давно хотел с ней поработать. Благодаря ей, я сделал минимальную визуализацию движения поездов по нашей модели. И так же данная библиотека позволяет работать со временем, что позволило мне реализовать автоматическое моделирование движения. 

## Модель ЖД

Сама модель представляет собой взвешенный ориентированный граф.(За это отвечает класс Railway_model) На моменте инициализации мы сперва загружаем станции и их параметры:
- тип станции;
- имя станции;
- номер станции;
- координаты станции на изображении;
- количество пассажиров и грузов на станции;
 
 Представление самого графа я сделал через список смежности. Там у каждой станции, хранятся в структуре номер станции, с которой она соединена, и расстояние до неё.
 
 Станции бывают 3х видов:
 - пассажирские;
 - грузовые;
 - грузо-пассажирские;
 
 ### Поезд
  
 В классе Train существуют 3 вектора:
 
 - Первый, хранит в себе все локомативы нашего поезда. (Добавляя локоматив, мы увеличиваем общую мощность поезда, которая влияет на изменение скорости движения поезда с грузом (Чем больше мощность нашего поезда, тем медленнее снижается его скорость при увеличении массы вагонов или их добавлеении). Так как у локомативов разная максимальная скорость, мы считаем, что максимальной скоростью пустого поезда, является скорость быстрейшего локоматива).
 
 -Второй, хранит в себе все вагоны нашего поезда. (Так как вагоны бывают разных типов, они представляются разными классами, которые наследуются от класса Van. Тут, благодаря полиморфизму и upcasting мы можем храть в одном векторе все типы вагонов(Не знаю, хорошее ли это решение, ведь потом для загрузки и разгрузки наших вагонов мне пришлось обратно приводить их к старому типу). Тут же и высчитывается масса вагона которая состоит из его массы без груза и массы самого груза (В случае пассажирского вагона количество человек умноженное на средний вес человека)).
 
 -Третий, хранит в себе маршрут нашего поезда. В каждом элементе вектора хранится номер станции и действие на этой станции (Действие нужно для того, чтобы получить время ожидания на этой станции)
 
 Так же я создал 2 булиновские переменные:
 	- is_on_station (находится ли поезд на станции);
	- is_on_route = (выполняет ли он маршрут);

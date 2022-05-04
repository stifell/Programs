import math
from decimal import *

#Формула Мадхавы:
def mad(a):
    pi = 0
    op = 0
    for i in range(100): #Используем цикл for,чтобы заменить сумму из формулы
        #Сравниваем найденное значение с точным значением числа pi
        if str(pi)[:a+3] == str(math.pi)[:a+3]: #Сравниваем от 1 до 15 знаков после запятой
            return str(pi)[:a+3]
        else:
            op += d(-1,i)/((2*i+1)*d(3,i)) #Используем формулу Мадхавы
            #Считываем кол-во арифметических операций (возведение в степень и извлечение корня отдельно):
            global size 
            size += 4
        pi = k(12)*op
        size += 1

    return str(pi)[:a+3]

#Формула Беллара:
def bel(a):
    getcontext().prec = 30 #Используем модуль decimal, т.к. при реализации этой формулы возникла проблема
    pi = 0
    op = 0
    t = d(2,6)
    for i in range(100): #Используем цикл for,чтобы заменить сумму из формулы
        #Сравниваем найденное значение с точным значением числа pi
        if str(pi)[:a+3] == str(math.pi)[:a+3]: #Сравниваем от 1 до 15 знаков после запятой
            return str(pi)[:a+3]
        else:
            op1 = Decimal(-(d(2,5))/(4*i+1)) + Decimal(-1/(4*i+3)) + Decimal(d(2,8)/(10*i+1)) + Decimal(-(t)/(10*i+3)) + Decimal(-(4)/(10*i+5)) + Decimal(-(4)/(10*i+7)) + Decimal(1/(10*i+9))
            op += (Decimal(d((-1),i))/Decimal(d(2,10*i)))*(op1) #Используем формулу Беллара
            #Считываем кол-во арифметических операций (возведение в степень отдельно):
            global size
            size += 29
        pi = op*1/t
        size += 1
    return str(pi)[:a+3]

#Функция для возведения в степень:
def d(a,b): 
    c = a
    if b == 0:
        return 1
    for i in range(b-1):
        a *= c
        global size
        size += 1
    return a

#Функция для извлечения корня:
def k(a):
    if a < 0:
        return
    else:
        global size
        size += 1
        return a**0.5

a = int(input('Number of simbols after comma: ')) #Вводим кол-во знаков после запятой с клавиатуры
size = 0 #Переменная для считывания кол-во арифметических операций
for i in range(a):
    size = 0
    print(mad(i))
    print ("Pi number first method:", size, '\n')

    size = 0
    print (bel(i))
    print ("Pi number second method:", size, '\n \n')


// ConsoleApplication29.cpp : Defines the entry point for the console application.
//
// Хирьянов ООП С++ Лекция 6
#include "stdafx.h"
#include<iostream>
#include<string>
//int8_t absolute(int8_t x) {
//	std::cout << "int8_t   ";
//	return (x < 0)? -x: x;
//}
//int16_t absolute(int16_t x) {
//	std::cout << "int16_t   ";
//	return (x < 0) ? -x : x;
//}
// вместо нескольких реализаций - шаблон:
template <typename T> // описание шаблона нужно и при объявлении, и при описание тела функции
T absolute(T x);

template <typename T>
T absolute(T x){
	return (x < 0) ? -x : x;
}
template <int number>
// функция сообщает, сколько раз ее вызвали 
void self_counter() {
	static int32_t counter = 0;
	counter++;
	std::cout << "called(number  "<<number <<")  " << counter << " times\n";
}


template <typename DataType>
//шаблон структура
struct tNode {
	DataType data;
	tNode* next;
};
// для работы с произвольным типом функцию сделаем шаблонной
// теперб tNode - это не имя типа. полное имя tNode<DataType>
template <typename DataType>
tNode<DataType>* insert_node(tNode<DataType> *p_begin, DataType data) {
	tNode<DataType> *p = new tNode<DataType>;
	p->data = data;
	p->next = p_begin;
	return p;
}

// case 3

template <typename DataType>
struct List {
	tNode<DataType> *begin; // указатель на начало.
	int size;
};
template <typename DataType>

void list_init(List<DataType> &L) {
	L.begin = nullptr;
	L.size = 0;
}
template <typename DataType>
// Если создавать шаблоны функций в отдельных файлах, то нельза разносить заголовки 
// и реализации шаблонных функциий, тк компилятору будет недостаточно информации
// шаблон функции помещают в header
void list_insert(List<DataType> &L, const DataType &value) {
		L.size ++;
		L.begin = insert_node(L.begin, value);
}
template <typename DataType>
void list_print(const List<DataType> &L, std::ostream &out) {
	tNode<DataType> *p = L.begin;
	while (p) {
		out << p->data << '\t';
		p = p->next;

	}	
}
template <typename DataType>
void list_destroy(List<DataType> &L) {
	tNode<DataType> *p = L.begin;
	tNode<DataType> *prev;
	while (p) {
		prev = p;
		p = p->next;
		delete prev;
	}
	L.size = 0;
	L.begin = nullptr;
}

//double absolute(double x) {
//	return (x < 0.) ? -x : x;
//}

int main(int a)
{
	
	//std::cin >> a;
//	std::cout << "\n";

	switch (a) {
	case 1: {int8_t x8 = 2;
		int16_t x16 = -1;
		int32_t x32 = -1;
		int64_t x64 = -1;
		double xd = -1.1;
		float xf = -1.1f;
		char c = 20;
		// Идея - сделать функцию, которая будет едина для всех типов - то и есть 
		std::cout << absolute(x8) << '\n'; // cout интрпртрт int8_t как тип char и выводит его как  значок
		std::cout << absolute(c) << '\n'; // видим, что для char можно вызвать и int8_t и double функцию. есть только реал-ии для Int8_t, double
		// при этоv когда только много int-реал-ий такой проблемы нет
		std::cout << absolute(x16) << '\n';
		std::cout << absolute(x32) << '\n';
		std::cout << absolute(x64) << '\n';
		std::cout << absolute(xd) << '\n'; // существует несколько вариантов на одном уровне приведения типов (3. стандартное приведение)
		//std::cout << absolute("aaa") << '\n';

										   // можно ли сделать так, чтобы было только одно описание функции? для любого типа данных
		// Да, для этого создадим шаблон функции
		// явное инст-ие
		std::cout << absolute<int32_t>(-8.3) << '\n'; // вручную указываем приведение типов и при вызове мы явно указываем, что absolute вызываем для типа int32_t
		break;
	}
	case 2:{
	
	//	self_counter();// ошибка, тк не может вычислить какой шаблон вызываь (нет типа)
		self_counter<1>(); // явным обрахом вызываем реализацию 1
		self_counter<1>();
		self_counter<2>();// явным обрахом вызываем реализацию 1
		// тк мы вызываем разные реализации, то стат перемнная counter в них тоже разная.
		// при компиляции им присваивается разный статический адрес
		self_counter<1>();
		self_counter<2>();
	}
	case 3: {
		tNode<std::string> *p_begin = nullptr;
		p_begin = insert_node(p_begin, std::string("Hello"));
		p_begin = insert_node(p_begin, std::string("world"));
		p_begin = insert_node(p_begin, std::string("first"));
		tNode<std::string> *p = p_begin;
		while (p) {
			std::cout << p->data << '\n';
			p = p->next;
		}
		break;
	}
	case 4: {
		List<std::string> str_list;
		list_init(str_list);
		list_insert(str_list, std::string("Hello"));
		list_insert(str_list, std::string("world"));
		list_insert(str_list, std::string("first"));
		list_print(str_list, std::cout);
		list_destroy(str_list);

		break;
	}

	}
	return 0;
}


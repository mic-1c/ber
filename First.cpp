
#include <iostream>
#include "berutils.h"
#include "tests.h"

#include <ctime>
#include <cstdint>


uint8_t getNewByte() // имитация пользовательской функции получения очередного байта данных
{
	return rand() % 255;
}
uint32_t getPacketSize() // имитация пользовательской функции получения размера очередного пакета
{
	return rand() % 20 + 5;
}




uint32_t main()
{
	setlocale(LC_ALL, "ru");
	
	// 1 задание 
	
	const uint32_t SizeBuffer = 200; // размер буфера памяти
	
	uint8_t MemoryBuffer[SizeBuffer] {}; // Указатель на буфер памяти 


	ber::utils::FillingParams params{
		MemoryBuffer,
		SizeBuffer,
		&getPacketSize,
		&getNewByte,
		{} ,
		0
	};

	ber::utils::completonMemoryArea(params);

	// 2 задание 

	uint8_t MemoryBufferNew[SizeBuffer]{}; // Указатель на второй буфер памяти 
	
	ber::utils::CompareParams compare{
		MemoryBuffer,
		MemoryBufferNew,
		params.packetParams,
		{},
		params.countBlock
	};

	ber::utils::compareMemoryAreas(compare);
	
	// проверим работу функций ber::utils::completonMemoryArea() и ber::utils::compareMemoryAreas();

	const uint32_t SizePack = 11; // рекомендуемый размер пакета
	const uint32_t ErrCount = 5; // количество специально испорченых бит
	uint8_t memoryBufferAudit[SizeBuffer]{}; // Указатель на первый буфер памяти 
	uint8_t memoryBufferNewAudit[SizeBuffer]{}; // Указатель на второй буфер памяти 
	uint32_t listErrors[ErrCount]{}; // ссылка на список испорченых бит

	ber::test::CheckParams checkParams{
		memoryBufferAudit,
		memoryBufferNewAudit,
		SizeBuffer,
		listErrors
	};
	ber::test::checkBerUtil(checkParams, SizePack, ErrCount);
	
	system("pause");
	return 0;
}


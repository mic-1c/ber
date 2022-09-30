#pragma once

#include <cstdint>

constexpr uint32_t MaxListSize = 100;

namespace ber {

	namespace utils {

		struct PacketParams {
			uint32_t packetOffsets[MaxListSize];	// Список смещений адресов пакетов
			uint32_t packetSizes[MaxListSize];		// Список размеров пакетов
		};

		struct ErrorParams {
			uint32_t goodByte;				// Количество байт без ошибок
			uint32_t lostByte;				// Количество байт с ошибками
			uint32_t lostBit;				// Количество ошибочных бит
		}; 

		/*
		 * Cтруктура для заполнения буфера памяти пакетами
		 */
		struct FillingParams {
			uint8_t* bufferData;			// ссылка на буфер памяти
			const uint32_t BufferSize;		// размер буфера памяти
			uint32_t(*getPacketSize)();		// Ссылка на пользовательскую функцию получить размер пакета
			uint8_t(*getNewByte)();			// Ссылка на пользовательскую функцию получить новый байт данных
			PacketParams packetParams;		// Списки размеров и смещений адресов пакетов
			uint32_t countBlock;			// Количество пакетов в буфере памяти
		}; 

		/*
		 * структура для сравнения двух буферов
		 */
		struct CompareParams {
			const uint8_t* BufferData;				// ссылка на эталонный буфер памяти
			const uint8_t* BufferNew;				// ссылка на проверяемый буфер памяти
			PacketParams packetParams;	// Списки размеров и смещений адресов пакетов
			ErrorParams errorParams;		// результаты проверки
			uint32_t countBlock;			// Количество пакетов в буфере памяти
		}; // структура для сравнения двух буферов

		/*
		 * заполнение буфера памяти пакетами данных (Задание1)
		 */
		void completonMemoryArea(FillingParams& fillingParams); 

		/*
		 * Сравнение двух буферов памяти с пакетами данных (Задание 2)
		 */
		void compareMemoryAreas(CompareParams& compareParams);

	}

}

#pragma once

#include <cstdint>
#include "berutils.h"

namespace ber {

	namespace test {


		/*
		* структура для проверочных функций
		*/
		struct CheckParams {
			uint8_t* bufferData;				// ссылка на эталонный буфер памяти
			uint8_t* bufferNew;				// ссылка на проверяемый буфер памяти
			const uint32_t BufferSize;		// размер буфера памяти
			uint32_t* listErrors;				// ссылка на список испорченых бит
		};

		/*
		 * Проверка правильности заполнения буфера памяти (анализ смещений)
		 * и Проверка правильности сравнения буферов памяти
		 */
		void checkBerUtil(CheckParams& checkParams, const uint32_t PacketSize, const uint32_t ErrCount);
	}
}
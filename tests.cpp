#include "tests.h"
#include <ctime>	
#include <iostream> 

namespace ber {

	namespace test {

		uint32_t minPacketSize;
		uint32_t maxPacketSize;

		uint8_t getNewByteAudit()
		{
			return rand() % 255;
		}
		uint32_t getPacketSizeAudit()
		{
			uint32_t curSize = rand() % 4 + minPacketSize;
			return curSize > 1 ? curSize : 2;
		}

		void checkBerUtil(CheckParams& checkParams, const uint32_t PacketSize, const uint32_t ErrCount)
		{
			srand(time(NULL));
			maxPacketSize = (PacketSize + 3) / 4 * 4;
			minPacketSize = maxPacketSize - 3;

			ber::utils::FillingParams fillingParams{
				checkParams.bufferData,
				checkParams.BufferSize,
				&getPacketSizeAudit,
				&getNewByteAudit,
				{} ,
				0
			};

			ber::utils::completonMemoryArea(fillingParams);

			printf("%s \t %u \n\n", "Ожидаемое смещение - ", maxPacketSize);
			bool testOk = true;

			for (uint32_t i = 1; i < fillingParams.countBlock; i++)
			{
				printf("%s \t", "Пакет № - ");
				printf("%u \t", i);
				printf("%u \t", fillingParams.packetParams.packetSizes[i]);
				printf("%u \t", fillingParams.packetParams.packetOffsets[i - 1]);
				printf("%u \t", fillingParams.packetParams.packetOffsets[i]);
				printf("%u \t", fillingParams.packetParams.packetOffsets[i] - fillingParams.packetParams.packetOffsets[i - 1]);
				if ((fillingParams.packetParams.packetOffsets[i] - fillingParams.packetParams.packetOffsets[i - 1]) == maxPacketSize)
				{
					printf("%s \n", "OK");
				}
				else
				{
					printf("%s \n", "ERROR");
					testOk = false;
				}
			}
			if (testOk)
			{
				printf("\n");
				printf("%s \n\n", "Тест заполнения буфера памяти завершен УСПЕШНО.");
			}
			else
			{
				printf("\n");
				printf("%s \n\n", "Тест заполнения буфера памяти завершен С ОШИБКАМИ.");
			}

			memcpy(checkParams.bufferNew, checkParams.bufferData, checkParams.BufferSize);


			uint32_t bitPointer = 0;
			uint32_t curPacket = 0;
			uint32_t curSizePacket = 0;
			uint32_t k = 0; // 
			bool isFound = false;

			while (k < ErrCount)
			{
				curPacket = rand() % fillingParams.countBlock;
				bitPointer = fillingParams.packetParams.packetOffsets[curPacket];
				curSizePacket = fillingParams.packetParams.packetSizes[curPacket];
				bitPointer += rand() % curSizePacket;
				bitPointer *= 10;
				bitPointer += rand() % 8;

				if (k == 0)
				{
					checkParams.listErrors[k] = bitPointer;
					printf("%u \t", checkParams.listErrors[k]);
					k++;
				}
				else
				{
					isFound = false;
					for (uint32_t i = 0; i < k; i++)
					{
						if (bitPointer == checkParams.listErrors[i])
						{
							isFound = true;
							break;
						}
					}
					if (!isFound)
					{
						checkParams.listErrors[k] = bitPointer;
						printf("%u \t", checkParams.listErrors[k]);
						k++;
					}
				}
			}
			printf("\n\n");

			uint8_t curByte = 0;
			uint32_t curBit = 0;

			for (uint32_t i = 0; i < ErrCount; i++)
			{
				curByte = checkParams.bufferNew[checkParams.listErrors[i] / 10];
				curBit = checkParams.listErrors[i] % 10;

				printf("%u \t", curByte);
				curByte ^= 1UL << curBit;
				printf("%u \n", curByte);
				checkParams.bufferNew[checkParams.listErrors[i] / 10] = curByte;
			}

			ber::utils::CompareParams compareParams{
				checkParams.bufferData,
				checkParams.bufferNew,
				fillingParams.packetParams,
				{},
				fillingParams.countBlock
			};

			printf("%s \n", "");
			printf("%s \t", "Испорчено бит - ");
			printf("%u \n\n", ErrCount);

			ber::utils::compareMemoryAreas(compareParams);

			printf("%s \t", "Обнаружено испорченых бит - ");
			printf("%u \n\n", compareParams.errorParams.lostBit);

			if (ErrCount == compareParams.errorParams.lostBit)
			{
				printf("\n");
				printf("%s \n\n", "Тест поиска испорченых бит завершен УСПЕШНО.");
			}
			else
			{
				printf("\n");
				printf("%s \n\n", "Тест поиска испорченых бит завершен С ОШИБКАМИ.");
			}
		}
	}
}


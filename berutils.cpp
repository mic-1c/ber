#include "berutils.h"
#include <iostream>	

namespace ber {

	namespace utils {

		void completonMemoryArea(FillingParams& fillingParams) 
		{
			uint8_t newByte;
			uint32_t currentSize; // размер очередного пакета
			uint32_t currentSizeWithNull; // размер очередного пакета c добиванием N/U
			uint8_t* ptBufferData = fillingParams.bufferData; // начальный адрес блока памяти
			uint32_t currentOffset = 0;		// Текущее смещение
			uint32_t freeSize = fillingParams.BufferSize;

			while ((freeSize != 0) && (fillingParams.countBlock <= MaxListSize))
			{
				currentSize = fillingParams.getPacketSize();
				currentSizeWithNull = (currentSize + sizeof(uint32_t) - 1) / sizeof(uint32_t) * sizeof(uint32_t); 

				if (currentSizeWithNull <= freeSize)
				{
					if (fillingParams.countBlock < MaxListSize)
					{
						fillingParams.packetParams.packetSizes[fillingParams.countBlock] = currentSize;	
						fillingParams.packetParams.packetOffsets[fillingParams.countBlock] = currentOffset;	
					}

					for (uint32_t i = 0; i < currentSizeWithNull; i++)
					{
						if (i == 0)
						{
							ptBufferData[currentOffset + i] = fillingParams.countBlock;
							fillingParams.countBlock++;
						}
						else
						{
							if (i > currentSize - 1)
							{
								newByte = NULL;
								ptBufferData[currentOffset + i] = newByte;
							}
							else
							{
								newByte = fillingParams.getNewByte();
								ptBufferData[currentOffset + i] = newByte;
							}
						}
					}
					currentOffset += currentSizeWithNull; 
					freeSize -= currentSizeWithNull;
				}
				else
				{
					freeSize = 0;
				}
			}
		}

		void compareMemoryAreas(CompareParams& compareParams)
		{
			uint8_t firstByte = 0;
			uint8_t secondByte = 0;
			uint8_t xOrByte = 0;
			const uint8_t* ptBufferData = compareParams.BufferData; // начальный адрес эталонного блока памяти
			const uint8_t* ptBufferNew = compareParams.BufferNew;	// начальный адрес нового блока памяти
			uint32_t CurrentOffset = 0;		// Текущее смещение

			compareParams.errorParams.lostBit = 0;
			compareParams.errorParams.lostByte = 0;

			for (uint32_t i = 0; i < compareParams.countBlock; i++)
			{
				CurrentOffset = compareParams.packetParams.packetOffsets[i];
				for (uint32_t j = 0; j < compareParams.packetParams.packetSizes[i]; j++)
				{
					firstByte = ptBufferData[CurrentOffset + j];
					secondByte = ptBufferNew[CurrentOffset + j];
					xOrByte = firstByte ^ secondByte;

					if (xOrByte != 0)
					{
						compareParams.errorParams.lostByte++;
						for (uint32_t k = 0; k < 8; k++)
						{
							compareParams.errorParams.lostBit += (xOrByte >> k) & 0x1;
						}
					}
					else
					{
						compareParams.errorParams.goodByte++;
					}
				}
			}
		}
	}
}
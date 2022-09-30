#pragma once

#include <cstdint>

constexpr uint32_t MaxListSize = 100;

namespace ber {

	namespace utils {

		struct PacketParams {
			uint32_t packetOffsets[MaxListSize];	// ������ �������� ������� �������
			uint32_t packetSizes[MaxListSize];		// ������ �������� �������
		};

		struct ErrorParams {
			uint32_t goodByte;				// ���������� ���� ��� ������
			uint32_t lostByte;				// ���������� ���� � ��������
			uint32_t lostBit;				// ���������� ��������� ���
		}; 

		/*
		 * C�������� ��� ���������� ������ ������ ��������
		 */
		struct FillingParams {
			uint8_t* bufferData;			// ������ �� ����� ������
			const uint32_t BufferSize;		// ������ ������ ������
			uint32_t(*getPacketSize)();		// ������ �� ���������������� ������� �������� ������ ������
			uint8_t(*getNewByte)();			// ������ �� ���������������� ������� �������� ����� ���� ������
			PacketParams packetParams;		// ������ �������� � �������� ������� �������
			uint32_t countBlock;			// ���������� ������� � ������ ������
		}; 

		/*
		 * ��������� ��� ��������� ���� �������
		 */
		struct CompareParams {
			const uint8_t* BufferData;				// ������ �� ��������� ����� ������
			const uint8_t* BufferNew;				// ������ �� ����������� ����� ������
			PacketParams packetParams;	// ������ �������� � �������� ������� �������
			ErrorParams errorParams;		// ���������� ��������
			uint32_t countBlock;			// ���������� ������� � ������ ������
		}; // ��������� ��� ��������� ���� �������

		/*
		 * ���������� ������ ������ �������� ������ (�������1)
		 */
		void completonMemoryArea(FillingParams& fillingParams); 

		/*
		 * ��������� ���� ������� ������ � �������� ������ (������� 2)
		 */
		void compareMemoryAreas(CompareParams& compareParams);

	}

}
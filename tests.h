#pragma once

#include <cstdint>
#include "berutils.h"

namespace ber {

	namespace test {


		/*
		* ��������� ��� ����������� �������
		*/
		struct CheckParams {
			uint8_t* bufferData;				// ������ �� ��������� ����� ������
			uint8_t* bufferNew;				// ������ �� ����������� ����� ������
			const uint32_t BufferSize;		// ������ ������ ������
			uint32_t* listErrors;				// ������ �� ������ ���������� ���
		};

		/*
		 * �������� ������������ ���������� ������ ������ (������ ��������)
		 * � �������� ������������ ��������� ������� ������
		 */
		void checkBerUtil(CheckParams& checkParams, const uint32_t PacketSize, const uint32_t ErrCount);
	}
}
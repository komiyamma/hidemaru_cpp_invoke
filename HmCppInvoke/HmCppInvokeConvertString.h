#pragma once
/*
 * Copyright (c) 2021 Akitsugu Komiyama
 * under the MIT License
 */

#include <string>

namespace Hidemaru {
	namespace Text {
		class Encoding {
		public:
			/// <summary>
			/// �ustring�^��utf8�v���uwstring�^��utf16�v��
			/// </summary>
			static std::wstring utf8_to_utf16(const std::string& text);

			/// <summary>
			/// �uwstring�^��utf16�v���ustring�^��utf8�v��
			/// </summary>
			static std::string utf16_to_utf8(const std::wstring& text);

			/// <summary>
			/// �ustring�^��cp932�v���uwstring�^��utf16�v��
			/// <para>(���m�ɂ�932�ł͂Ȃ��V�X�e��OEM�R�[�h�y�[�W�BWindows���{�ꃂ�[�h����932)</para>
			/// </summary>
			static std::wstring cp932_to_utf16(const std::string& text);

			/// <summary>
			/// �uwstring�^��utf16�v���ustring�^��cp932�v��
			/// <para>(���m�ɂ�932�ł͂Ȃ��V�X�e��OEM�R�[�h�y�[�W�BWindows���{�ꃂ�[�h����932)</para>
			/// </summary>
			static std::string utf16_to_cp932(const std::wstring& text);
		};
	}
}